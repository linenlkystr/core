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
#include <biogears/cdm/patient/actions/SEPatientAction.h>

IO_DECL(PatientActions)

namespace biogears {
class SEScalarVolumePerTime;

class BIOGEARS_API SEPericardialEffusion : public SEPatientAction {
  friend class io::PatientActions;

public:
  SEPericardialEffusion();
  virtual ~SEPericardialEffusion() override;

  static constexpr const char* TypeTag() { return "SEPericardialEffusion"; };
  const char* classname() const override { return TypeTag(); }

  virtual void Clear() override; //clear memory

  virtual bool IsValid() const override;
  virtual bool IsActive() const override;

public:
  virtual bool HasEffusionRate() const;
  virtual SEScalarVolumePerTime& GetEffusionRate();

  virtual void ToString(std::ostream& str) const override;

protected:
  SEScalarVolumePerTime* m_EffusionRate;
};
}