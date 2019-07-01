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
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEInspiratoryValveLeak.h>

#include <biogears/cdm/properties/SEScalar0To1.h>

namespace biogears {
SEInspiratoryValveLeak::SEInspiratoryValveLeak()
  : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}
//----------------------------------------------------------------------------------
SEInspiratoryValveLeak::~SEInspiratoryValveLeak()
{
  Clear();
}
//----------------------------------------------------------------------------------
void SEInspiratoryValveLeak::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}
//----------------------------------------------------------------------------------
bool SEInspiratoryValveLeak::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}
//----------------------------------------------------------------------------------
bool SEInspiratoryValveLeak::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}
//----------------------------------------------------------------------------------
bool SEInspiratoryValveLeak::HasSeverity() const
{
  return m_Severity != nullptr;
}
//----------------------------------------------------------------------------------
SEScalar0To1& SEInspiratoryValveLeak::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}
//----------------------------------------------------------------------------------
void SEInspiratoryValveLeak::ToString(std::ostream& str) const
{
  str << "Anesthesia Machine Action : Inspiratory Valve Leak";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :";
  HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}
//----------------------------------------------------------------------------------
}