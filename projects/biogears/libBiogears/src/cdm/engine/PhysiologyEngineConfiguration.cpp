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
#include <biogears/cdm/engine/PhysiologyEngineConfiguration.h>

#include <biogears/cdm/Serializer.h>
#include <biogears/cdm/engine/PhysiologyEngineDynamicStabilization.h>
#include <biogears/cdm/engine/PhysiologyEngineTimedStabilization.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/system/equipment/ElectroCardioGram/SEElectroCardioGramInterpolator.h>

#include "../../cdm/utils/io/EngineConfiguration.h"
namespace biogears {
PhysiologyEngineConfiguration::PhysiologyEngineConfiguration(Logger* logger)
  : Loggable(logger)
{
  m_Merge = false;
  m_ECGInterpolator = nullptr;
  m_StabilizationCriteria = nullptr;
  m_TimedStabilizationCriteria = nullptr;
  m_DynamicStabilizationCriteria = nullptr;
  m_TimeStep = nullptr;
  m_WritePatientBaselineFile = CDM::enumOnOff::value(-1);
}

//-----------------------------------------------------------------------------
PhysiologyEngineConfiguration::~PhysiologyEngineConfiguration()
{
  Clear();
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::Clear()
{
  SAFE_DELETE(m_ECGInterpolator);
  RemoveStabilizationCriteria();
  SAFE_DELETE(m_TimeStep);

  m_WritePatientBaselineFile = CDM::enumOnOff::value(-1);
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::Merge(const PhysiologyEngineConfiguration& from)
{
  m_Merge = true;
  auto pecData = CDM::PhysiologyEngineConfigurationData();
  io::EngineConfiguration::UnMarshall(from, pecData);
  io::EngineConfiguration::Marshall(pecData, *this);
  m_Merge = false;
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::Load(const char* file)
{
   Load(std::string{ file });
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::Load(const std::string& file)
{
  // if file does not exist, we stick with defaults

  CDM::PhysiologyEngineConfigurationData* pData;
  std::unique_ptr<CDM::ObjectData> data;

  data = Serializer::ReadFile(file, GetLogger());
  pData = dynamic_cast<CDM::PhysiologyEngineConfigurationData*>(data.get());
  if (pData == nullptr) {
    std::stringstream ss;
    ss << "Configuration file : " << file << " not found, using default configuration" << std::endl;
    Info(ss);
    throw CommonDataModelException(ss.str());
  }
  io::EngineConfiguration::Marshall(*pData, *this);
}
//-----------------------------------------------------------------------------
bool PhysiologyEngineConfiguration::HasECGInterpolator() const
{
  return m_ECGInterpolator != nullptr;
}
//-----------------------------------------------------------------------------
SEElectroCardioGramInterpolator& PhysiologyEngineConfiguration::GetECGInterpolator()
{
  if (m_ECGInterpolator == nullptr)
    m_ECGInterpolator = new SEElectroCardioGramInterpolator(GetLogger());
  return *m_ECGInterpolator;
}
//-----------------------------------------------------------------------------
const SEElectroCardioGramInterpolator* PhysiologyEngineConfiguration::GetECGInterpolator() const
{
  return m_ECGInterpolator;
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::RemoveECGInterpolator()
{
  SAFE_DELETE(m_ECGInterpolator);
}
//-----------------------------------------------------------------------------
bool PhysiologyEngineConfiguration::HasStabilizationCriteria() const
{
  return m_StabilizationCriteria != nullptr;
}
//-----------------------------------------------------------------------------
PhysiologyEngineStabilization* PhysiologyEngineConfiguration::GetStabilizationCriteria()
{
  return m_StabilizationCriteria;
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::RemoveStabilizationCriteria()
{
  SAFE_DELETE(m_TimedStabilizationCriteria);
  SAFE_DELETE(m_DynamicStabilizationCriteria);
  m_StabilizationCriteria = nullptr; // Generic pointer used to point to one of the above pointers
}
//-----------------------------------------------------------------------------
bool PhysiologyEngineConfiguration::HasTimedStabilizationCriteria() const
{
  return m_TimedStabilizationCriteria != nullptr;
}
//-----------------------------------------------------------------------------
PhysiologyEngineTimedStabilization& PhysiologyEngineConfiguration::GetTimedStabilizationCriteria()
{
  RemoveDynamicStabilizationCriteria();
  if (m_TimedStabilizationCriteria == nullptr) {
    m_TimedStabilizationCriteria = new PhysiologyEngineTimedStabilization(GetLogger());
    m_StabilizationCriteria = m_TimedStabilizationCriteria;
  }
  return *m_TimedStabilizationCriteria;
}
//-----------------------------------------------------------------------------
const PhysiologyEngineTimedStabilization* PhysiologyEngineConfiguration::GetTimedStabilizationCriteria() const
{
  return m_TimedStabilizationCriteria;
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::RemoveTimedStabilizationCriteria()
{
  if (m_StabilizationCriteria == m_TimedStabilizationCriteria)
    m_StabilizationCriteria = nullptr;
  SAFE_DELETE(m_TimedStabilizationCriteria);
}
//-----------------------------------------------------------------------------
bool PhysiologyEngineConfiguration::HasDynamicStabilizationCriteria() const
{
  return m_DynamicStabilizationCriteria != nullptr;
}
//-----------------------------------------------------------------------------
PhysiologyEngineDynamicStabilization& PhysiologyEngineConfiguration::GetDynamicStabilizationCriteria()
{
  RemoveTimedStabilizationCriteria();
  if (m_DynamicStabilizationCriteria == nullptr) {
    m_DynamicStabilizationCriteria = new PhysiologyEngineDynamicStabilization(GetLogger());
    m_StabilizationCriteria = m_DynamicStabilizationCriteria;
  }
  return *m_DynamicStabilizationCriteria;
}
//-----------------------------------------------------------------------------
const PhysiologyEngineDynamicStabilization* PhysiologyEngineConfiguration::GetDynamicStabilizationCriteria() const
{
  return m_DynamicStabilizationCriteria;
}
//-----------------------------------------------------------------------------
void PhysiologyEngineConfiguration::RemoveDynamicStabilizationCriteria()
{
  if (m_StabilizationCriteria == m_DynamicStabilizationCriteria)
    m_StabilizationCriteria = nullptr;
  SAFE_DELETE(m_DynamicStabilizationCriteria);
}
//-----------------------------------------------------------------------------
bool PhysiologyEngineConfiguration::HasTimeStep() const
{
  return m_TimeStep == nullptr ? false : m_TimeStep->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarTime& PhysiologyEngineConfiguration::GetTimeStep()
{
  if (m_TimeStep == nullptr)
    m_TimeStep = new SEScalarTime();
  return *m_TimeStep;
}
//-----------------------------------------------------------------------------
double PhysiologyEngineConfiguration::GetTimeStep(const TimeUnit& unit) const
{
  if (m_TimeStep == nullptr)
    return SEScalar::dNaN();
  return m_TimeStep->GetValue(unit);
}
}