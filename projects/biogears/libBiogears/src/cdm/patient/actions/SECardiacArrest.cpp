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

#include <biogears/cdm/patient/actions/SECardiacArrest.h>

namespace biogears {
SECardiacArrest::SECardiacArrest()
  : SEPatientAction()
{
  m_State = CDM::enumOnOff::Off;
}

SECardiacArrest::~SECardiacArrest()
{
  Clear();
}

void SECardiacArrest::Clear()
{
  SEPatientAction::Clear();
  m_State = CDM::enumOnOff::Off;
}

bool SECardiacArrest::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SECardiacArrest::IsActive() const
{
  return IsValid() && m_State == CDM::enumOnOff::On;
}

void SECardiacArrest::SetActive(bool b)
{
  m_State = b ? CDM::enumOnOff::On : CDM::enumOnOff::Off;
}

void SECardiacArrest::ToString(std::ostream& str) const
{
  str << "Patient Action : Cardiac Arrest";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tState: " << IsActive();
  str << std::flush;
}
}