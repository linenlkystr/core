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
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEOxygenTankPressureLoss.h>

#include <biogears/cdm/properties/SEScalar0To1.h>

namespace biogears {
SEOxygenTankPressureLoss::SEOxygenTankPressureLoss()
  : SEAnesthesiaMachineAction()
{
  m_State = SEOnOff::Off;
}
//----------------------------------------------------------------------------------
SEOxygenTankPressureLoss::~SEOxygenTankPressureLoss()
{
  Clear();
}
//----------------------------------------------------------------------------------
void SEOxygenTankPressureLoss::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  m_State = SEOnOff::Invalid;
}
//----------------------------------------------------------------------------------
bool SEOxygenTankPressureLoss::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid();
}
//----------------------------------------------------------------------------------
bool SEOxygenTankPressureLoss::IsActive() const
{
  return m_State == SEOnOff::On;
}
//----------------------------------------------------------------------------------
void SEOxygenTankPressureLoss::SetActive(bool b)
{
  m_State = b ? SEOnOff::On : SEOnOff::Off;
}
//----------------------------------------------------------------------------------
void SEOxygenTankPressureLoss::ToString(std::ostream& str) const
{
  str << "Anesthesia Machine Action : Oxygen Tank Pressure Loss";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tState: " << IsActive();
  str << std::flush;
}
//----------------------------------------------------------------------------------
}