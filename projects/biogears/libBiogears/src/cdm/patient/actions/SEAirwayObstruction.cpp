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
#include <biogears/cdm/patient/actions/SEAirwayObstruction.h>

#include <biogears/cdm/properties/SEScalar0To1.h>

namespace biogears {
SEAirwayObstruction::SEAirwayObstruction()
  : SEPatientAction()
{
  m_Severity = nullptr;
}

SEAirwayObstruction::~SEAirwayObstruction()
{
  Clear();
}

void SEAirwayObstruction::Clear()
{

  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEAirwayObstruction::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEAirwayObstruction::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

bool SEAirwayObstruction::HasSeverity() const
{
  return m_Severity == nullptr ? false : m_Severity->IsValid();
}

SEScalar0To1& SEAirwayObstruction::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEAirwayObstruction::ToString(std::ostream& str) const
{
  str << "Patient Action : Airway Obstruction";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity: ";
  HasSeverity() ? str << *m_Severity : str << "Not Set";
  str << std::flush;
}
}