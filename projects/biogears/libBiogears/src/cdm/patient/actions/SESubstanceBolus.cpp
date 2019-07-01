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
#include <biogears/cdm/patient/actions/SESubstanceBolus.h>

#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/substance/SESubstance.h>

namespace biogears {
SESubstanceBolus::SESubstanceBolus(const SESubstance& substance)
  : SESubstanceAdministration()
  , m_Substance(substance)
{
  m_AdminRoute = SEBolusAdministration::Invalid;
  m_Dose = nullptr;
  m_Concentration = nullptr;
}

SESubstanceBolus::~SESubstanceBolus()
{
  Clear();
}

void SESubstanceBolus::Clear()
{
  SESubstanceAdministration::Clear();
  m_AdminRoute = SEBolusAdministration::Invalid;
  SAFE_DELETE(m_Dose);
  SAFE_DELETE(m_Concentration);
  // m_Substance=nullptr; Keeping mapping!!
}

bool SESubstanceBolus::IsValid() const
{
  return SESubstanceAdministration::IsValid() && HasDose() && HasConcentration() && HasAdminRoute();
}

bool SESubstanceBolus::IsActive() const
{
  return IsValid();
}

SEBolusAdministration SESubstanceBolus::GetAdminRoute() const
{
  return m_AdminRoute;
}
void SESubstanceBolus::SetAdminRoute(SEBolusAdministration route)
{
  m_AdminRoute = route;
}
bool SESubstanceBolus::HasAdminRoute() const
{
  return m_AdminRoute == (SEBolusAdministration::Invalid) ? false : true;
}
void SESubstanceBolus::InvalidateAdminRoute()
{
  m_AdminRoute = SEBolusAdministration::Invalid;
}

bool SESubstanceBolus::HasDose() const
{
  return m_Dose == nullptr ? false : m_Dose->IsValid();
}
SEScalarVolume& SESubstanceBolus::GetDose()
{
  if (m_Dose == nullptr)
    m_Dose = new SEScalarVolume();
  return *m_Dose;
}

bool SESubstanceBolus::HasConcentration() const
{
  return m_Concentration == nullptr ? false : m_Concentration->IsValid();
}
SEScalarMassPerVolume& SESubstanceBolus::GetConcentration()
{
  if (m_Concentration == nullptr)
    m_Concentration = new SEScalarMassPerVolume();
  return *m_Concentration;
}

SESubstance& SESubstanceBolus::GetSubstance() const
{
  return (SESubstance&)m_Substance;
}

void SESubstanceBolus::ToString(std::ostream& str) const
{
  str << "Patient Action : Substance Bolus";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tDose: ";
  HasDose() ? str << *m_Dose : str << "No Dose Set";
  str << "\n\tConcentration: ";
  HasConcentration() ? str << *m_Concentration : str << "NaN";
  str << "\n\tSubstance: " << m_Substance.GetName();
  str << "\n\tAdministration Route: ";
  HasAdminRoute() ? str << GetAdminRoute() : str << "Not Set";
  str << std::flush;
}


SESubstanceBolusState::SESubstanceBolusState(const SESubstance& sub)
  : m_substance(sub)
{
  m_elapsedTime.SetValue(0, TimeUnit::s);
  m_administeredDose.SetValue(0, VolumeUnit::mL);
}
SESubstanceBolusState::~SESubstanceBolusState()
{
}

}