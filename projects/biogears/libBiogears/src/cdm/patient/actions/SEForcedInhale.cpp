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
#include <biogears/cdm/patient/actions/SEForcedInhale.h>

#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarTime.h>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {
SEForcedInhale::SEForcedInhale()
  : SEConsciousRespirationCommand()
{
  m_InspiratoryCapacityFraction = nullptr;
  m_Period = nullptr;
}

SEForcedInhale::~SEForcedInhale()
{
  Clear();
}

void SEForcedInhale::Clear()
{
  SEConsciousRespirationCommand::Clear();
  SAFE_DELETE(m_InspiratoryCapacityFraction);
  SAFE_DELETE(m_Period);
}

bool SEForcedInhale::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid() && HasInspiratoryCapacityFraction() && HasPeriod();
}

bool SEForcedInhale::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

bool SEForcedInhale::Load(const CDM::ForcedInhaleData& in)
{
  SEConsciousRespirationCommand::Load(in);
  io::PropertyIoDelegate::Marshall(in.InspiratoryCapacityFraction(), GetInspiratoryCapacityFraction());
  io::PropertyIoDelegate::Marshall(in.Period(), GetPeriod());
  return true;
}

CDM::ForcedInhaleData* SEForcedInhale::Unload() const
{
  CDM::ForcedInhaleData* data(new CDM::ForcedInhaleData());
  Unload(*data);
  return data;
}

void SEForcedInhale::Unload(CDM::ForcedInhaleData& data) const
{
  SEConsciousRespirationCommand::Unload(data);
  if (m_InspiratoryCapacityFraction != nullptr) {
    io::PropertyIoDelegate::UnMarshall(*m_InspiratoryCapacityFraction, data.InspiratoryCapacityFraction());
  }
  if (m_Period != nullptr) {
    io::PropertyIoDelegate::UnMarshall(*m_Period, data.Period());
  }
}

bool SEForcedInhale::HasInspiratoryCapacityFraction() const
{
  return m_InspiratoryCapacityFraction == nullptr ? false : m_InspiratoryCapacityFraction->IsValid();
}
SEScalar0To1& SEForcedInhale::GetInspiratoryCapacityFraction()
{
  if (m_InspiratoryCapacityFraction == nullptr){}
    m_InspiratoryCapacityFraction = new SEScalar0To1();
  return *m_InspiratoryCapacityFraction;
}

bool SEForcedInhale::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEForcedInhale::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}

void SEForcedInhale::ToString(std::ostream& str) const
{
  str << "Forced Inhale";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tInspiratoryCapacityFraction: ";
  HasInspiratoryCapacityFraction() ? str << *m_InspiratoryCapacityFraction : str << "NaN";
  str << "\n\tPeriod: ";
  HasPeriod() ? str << *m_Period : str << "NaN";
  str << std::flush;
}
}