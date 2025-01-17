/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
#include <biogears/cdm/patient/actions/SEHemorrhage.h>

#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/schema/cdm/Properties.hxx>

namespace biogears {
SEHemorrhage::SEHemorrhage()
  : SEPatientAction()
{
  m_Compartment = ""; //User input, location of hemorrhage
  //m_MCIS;
  m_InitialRate = nullptr; //User input, initial rate of bleeding
  m_BleedResistance = nullptr; //Maps input to resistance on bleeding path from specified compartment
}
//-----------------------------------------------------------------------------
SEHemorrhage::~SEHemorrhage()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SEHemorrhage::Clear()
{
  SEPatientAction::Clear();
  m_Compartment = "";
  m_MCIS.clear();
  organMap.clear();
  SAFE_DELETE(m_InitialRate);
  SAFE_DELETE(m_BleedResistance);
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::IsValid() const
{
  return SEPatientAction::IsValid() && HasCompartment() && HasInitialRate();
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::IsActive() const
{
  return IsValid() ? !(m_InitialRate->GetValue(VolumePerTimeUnit::mL_Per_min) <= ZERO_APPROX) : false;
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::Load(const CDM::HemorrhageData& in)
{
  SEPatientAction::Load(in);
  m_Compartment = in.Compartment();
  GetInitialRate().Load(in.InitialRate());
  //Place compartments in torso in a map so that we don't get too messy with nested conditionals.  Each vector is digits 2-4 of the MCIS code
  organMap["VenaCava"] = std::vector<unsigned int>{ 6, 6, 0 };
  organMap["LeftLung"] = std::vector<unsigned int>{ 7, 1, 0 };
  organMap["RightLung"] = std::vector<unsigned int>{ 7, 1, 0 };
  organMap["Myocardium"] = std::vector<unsigned int>{ 7, 2, 0 };
  organMap["Liver"] = std::vector<unsigned int>{ 8, 1, 0 };
  organMap["Spleen"] = std::vector<unsigned int>{ 8, 2, 0 };
  organMap["Splanchnic"] = std::vector<unsigned int>{ 8, 3, 0 };
  organMap["LeftKidney"] = std::vector<unsigned int>{ 8, 4, 0 };
  organMap["RightKidney"] = std::vector<unsigned int>{ 8, 4, 0 };
  organMap["SmallIntestine"] = std::vector<unsigned int>{ 8, 5, 0 };
  organMap["LargeIntestine"] = std::vector<unsigned int>{ 8, 6, 0 };
  SetMCIS();

  return true;
}
//-----------------------------------------------------------------------------
CDM::HemorrhageData* SEHemorrhage::Unload() const
{
  CDM::HemorrhageData* data(new CDM::HemorrhageData());
  Unload(*data);
  return data;
}
//-----------------------------------------------------------------------------
void SEHemorrhage::Unload(CDM::HemorrhageData& data) const
{
  SEPatientAction::Unload(data);
  if (HasCompartment())
    data.Compartment(m_Compartment);
  if (HasInitialRate())
    data.InitialRate(std::unique_ptr<CDM::ScalarVolumePerTimeData>(m_InitialRate->Unload()));
}
//-----------------------------------------------------------------------------
void SEHemorrhage::SetMCIS()
{
  bool found = false;
  //Scale initial bleeding rate by a max value of 250 mL/min-->this would cause hypovolemic shock in 10 minutes assuming blood volume = 5L
  //Max this our "worst case"
  double flowScale_mL_Per_min = 250.0;
  int sev = 0;
  if (m_InitialRate->GetValue(VolumePerTimeUnit::mL_Per_min) > flowScale_mL_Per_min) {
    sev = 5;
  } else {
    sev = (int)ceil(5.0 * m_InitialRate->GetValue(VolumePerTimeUnit::mL_Per_min) / flowScale_mL_Per_min);
  }

  m_MCIS.push_back(sev);
  if (m_Compartment == "Brain") {
    m_MCIS.insert(m_MCIS.end(), { 1, 6, 1, 0 });
    found = true;
  } else if (m_Compartment == "Aorta") {
    m_MCIS.insert(m_MCIS.end(), { 2, 6, 4, 0 });
    found = true;
  } else if (m_Compartment == "LeftArm" || m_Compartment == "RightArm") {
    m_MCIS.insert(m_MCIS.end(), { 3, 0, 0, 0 });
    found = true;
  } else if (m_Compartment == "LeftLeg" || m_Compartment == "RightLeg") {
    m_MCIS.insert(m_MCIS.end(), { 4, 0, 0, 0 });
    found = true;
  } else {
    m_MCIS.push_back(2);
    //This inserts the code of integers stored in the organ map (associated with the compartment) at the end of the mcis vector
    m_MCIS.insert(m_MCIS.end(), organMap[m_Compartment].begin(), organMap[m_Compartment].end());
    found = true;
  }
  if (!found) {
    SetComment("Could not find compartment, defaulting to Aorta");
    m_MCIS.insert(m_MCIS.end(), { 2, 6, 4, 0 });
  }
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::HasMCIS() const
{
  return !m_MCIS.empty();
}
//-----------------------------------------------------------------------------
const char* SEHemorrhage::GetCompartment_cStr() const
{
  return m_Compartment.c_str();
}
//-----------------------------------------------------------------------------
std::string SEHemorrhage::GetCompartment() const
{
  return m_Compartment;
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::HasCompartment() const
{
  return !m_Compartment.empty();
}
//-----------------------------------------------------------------------------
void SEHemorrhage::SetCompartment(const char* name)
{
  return SetCompartment(std::string{ name });
}
//-----------------------------------------------------------------------------
void SEHemorrhage::SetCompartment(const std::string& name)
{
  m_Compartment = name;
}
//-----------------------------------------------------------------------------
void SEHemorrhage::InvalidateCompartment()
{
  m_Compartment = "";
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::HasInitialRate() const
{
  return m_InitialRate == nullptr ? false : true;
}
//-----------------------------------------------------------------------------
SEScalarVolumePerTime& SEHemorrhage::GetInitialRate()
{
  if (m_InitialRate == nullptr)
    m_InitialRate = new SEScalarVolumePerTime();
  return *m_InitialRate;
}
//-----------------------------------------------------------------------------
bool SEHemorrhage::HasBleedResistance() const
{
  return m_BleedResistance == nullptr ? false : true;
}
//-----------------------------------------------------------------------------
SEScalarFlowResistance& SEHemorrhage::GetBleedResistance()
{
  if (m_BleedResistance == nullptr) {
    m_BleedResistance = new SEScalarFlowResistance();
  }
  return *m_BleedResistance;
}
//-----------------------------------------------------------------------------
void SEHemorrhage::ToString(std::ostream& str) const
{
  if (m_InitialRate->GetValue(VolumePerTimeUnit::mL_Per_min) < ZERO_APPROX) {
    str << "Patient Action : Stop Hemorrhage";
    if (HasComment())
      str << "\n\tComment: ";
    str << m_Comment;
    str << "\n\tCompartment: ";
    HasCompartment() ? str << GetCompartment() : str << "No Compartment Set";
  } else {
    str << "Patient Action : Hemorrhage";
    if (HasComment())
      str << "\n\tComment: " << m_Comment;
    str << "\n\tInitial Bleeding Rate:  ";
    str << *m_InitialRate;
    str << "\n\tCompartment: ";
    HasCompartment() ? str << GetCompartment() : str << "No Compartment Set";
    str << "\n\tInjury Code: ";
    for (int i : m_MCIS)
      str << i;
  }
  str << std::flush;
}
//-----------------------------------------------------------------------------
}