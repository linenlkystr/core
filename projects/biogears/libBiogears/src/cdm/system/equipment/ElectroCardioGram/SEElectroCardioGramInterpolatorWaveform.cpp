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

#include <biogears/cdm/properties/SEFunctionElectricPotentialVsTime.h>
#include <biogears/cdm/properties/SEScalarElectricPotential.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/system/equipment/ElectroCardioGram/SEElectroCardioGramInterpolatorWaveform.h>

namespace biogears {
SEElectroCardioGramInterpolatorWaveform::SEElectroCardioGramInterpolatorWaveform(Logger* logger)
  : Loggable(logger)
{
  m_TimeStep = nullptr;
  m_Data = nullptr;
  m_Rhythm = SEHeartRhythm::Invalid;
  m_LeadNumber = 0;
}

SEElectroCardioGramInterpolatorWaveform::~SEElectroCardioGramInterpolatorWaveform()
{
  Clear();
}

void SEElectroCardioGramInterpolatorWaveform::Clear()
{
  m_LeadNumber = 0;
  m_Rhythm = SEHeartRhythm::Invalid;
  SAFE_DELETE(m_TimeStep);
  SAFE_DELETE(m_Data);
  m_ActiveIndicies.clear();
}

unsigned int SEElectroCardioGramInterpolatorWaveform::GetLeadNumber() const
{
  return m_LeadNumber;
}
void SEElectroCardioGramInterpolatorWaveform::SetLeadNumber(unsigned int n)
{
  m_LeadNumber = n;
}
bool SEElectroCardioGramInterpolatorWaveform::HasLeadNumber() const
{
  return m_LeadNumber == 0 ? false : true;
}
void SEElectroCardioGramInterpolatorWaveform::InvalidateLeadNumber()
{
  m_LeadNumber = 0;
}

SEHeartRhythm SEElectroCardioGramInterpolatorWaveform::GetRhythm() const
{
  return m_Rhythm;
}
void SEElectroCardioGramInterpolatorWaveform::SetRhythm(SEHeartRhythm rhythm)
{
  m_Rhythm = rhythm;
}
bool SEElectroCardioGramInterpolatorWaveform::HasRhythm() const
{
  return m_Rhythm != SEHeartRhythm::Invalid;
}
void SEElectroCardioGramInterpolatorWaveform::InvalidateRhythm()
{
  m_Rhythm = SEHeartRhythm::Invalid;
}

bool SEElectroCardioGramInterpolatorWaveform::HasData() const
{
  return m_Data == nullptr ? false : m_Data->IsValid();
}
SEFunctionElectricPotentialVsTime& SEElectroCardioGramInterpolatorWaveform::GetData()
{
  if (m_Data == nullptr)
    m_Data = new SEFunctionElectricPotentialVsTime();
  return *m_Data;
}
const SEFunctionElectricPotentialVsTime* SEElectroCardioGramInterpolatorWaveform::GetData() const
{
  return m_Data;
}

bool SEElectroCardioGramInterpolatorWaveform::HasTimeStep() const
{
  return m_TimeStep == nullptr ? false : m_TimeStep->IsValid();
}
SEScalarTime& SEElectroCardioGramInterpolatorWaveform::GetTimeStep()
{
  if (m_TimeStep == nullptr)
    m_TimeStep = new SEScalarTime();
  return *m_TimeStep;
}
double SEElectroCardioGramInterpolatorWaveform::GetTimeStep(const TimeUnit& unit) const
{
  if (m_TimeStep == nullptr)
    return SEScalar::dNaN();
  return m_TimeStep->GetValue(unit);
}
}