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
#include <biogears/cdm/patient/actions/SEExercise.h>

#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>


namespace biogears {
SEExercise::SEExercise()
  : SEPatientAction()
{
  m_Intensity = nullptr;
  m_DesiredWorkRate = nullptr;
}
//----------------------------------------------------------------------------------
SEExercise::~SEExercise()
{
  Clear();
}
//----------------------------------------------------------------------------------
void SEExercise::Clear()
{
  SEPatientAction::Clear();
  SAFE_DELETE(m_Intensity);
  SAFE_DELETE(m_DesiredWorkRate)
}
//----------------------------------------------------------------------------------
bool SEExercise::IsValid() const
{
  return SEPatientAction::IsValid() && (HasDesiredWorkRate() || HasIntensity());
}
//----------------------------------------------------------------------------------
bool SEExercise::IsActive() const
{
  if (HasIntensity()) {
    return !m_Intensity->IsZero();
  } else if (HasDesiredWorkRate()) {
    return !m_DesiredWorkRate->IsZero();
  } else {
    return false;
  }
}
//----------------------------------------------------------------------------------
bool SEExercise::HasIntensity() const
{
  return m_Intensity == nullptr ? false : m_Intensity->IsValid();
}
//----------------------------------------------------------------------------------
SEScalar0To1& SEExercise::GetIntensity()
{
  if (m_Intensity == nullptr)
    m_Intensity = new SEScalar0To1();
  return *m_Intensity;
}
//----------------------------------------------------------------------------------
bool SEExercise::HasDesiredWorkRate() const
{
  return m_DesiredWorkRate == nullptr ? false : m_DesiredWorkRate->IsValid();
}
//----------------------------------------------------------------------------------
SEScalar& SEExercise::GetDesiredWorkRate()
{
  if (m_DesiredWorkRate == nullptr)
    m_DesiredWorkRate = new SEScalar();
  return *m_DesiredWorkRate;
}
//----------------------------------------------------------------------------------
void SEExercise::ToString(std::ostream& str) const
{
  str << "Patient Action : Exercise";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  if (HasIntensity()) {
    str << "\n\tIntensity: ";
    HasIntensity() ? str << *m_Intensity : str << "NaN";
  } else if (HasDesiredWorkRate()) {
    str << "\n\tDesired Work Rate: ";
    HasDesiredWorkRate() ? str << *m_DesiredWorkRate : str << "NaN";
  } else {
    str << "No input for intensity or desired work rate";
  }
  str << std::flush;
}
//----------------------------------------------------------------------------------
}