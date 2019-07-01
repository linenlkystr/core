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
#pragma once
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEAnesthesiaMachineAction.h>

IO_DECL(AnesthesiaActions)

namespace biogears {
class SEScalar0To1;

class BIOGEARS_API SEOxygenTankPressureLoss : public SEAnesthesiaMachineAction {
  friend class io::AnesthesiaActions;

public:
  SEOxygenTankPressureLoss();
  virtual ~SEOxygenTankPressureLoss() override;

  static constexpr const char* TypeTag() { return "SEOxygenTankPressureLoss"; };
  const char* classname() const override { return TypeTag(); }

  virtual void Clear() override;

  virtual bool IsValid() const override;
  virtual bool IsActive() const override;
  virtual void SetActive(bool b);
  virtual void ToString(std::ostream& str) const override;

protected:
  CDM::enumOnOff::value m_State;
};
}