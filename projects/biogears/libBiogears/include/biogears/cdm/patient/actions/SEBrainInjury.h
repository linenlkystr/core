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
class SEScalar0To1;

class BIOGEARS_API SEBrainInjury : public SEPatientAction {
  friend class io::PatientActions;

public:
  SEBrainInjury();
  virtual ~SEBrainInjury() override;

  static constexpr const char* TypeTag() { return "SEBrainInjury"; };
  const char* classname() const override { return TypeTag(); }

  virtual void Clear() override;

  virtual bool IsValid() const override;
  virtual bool IsActive() const override;

public:
  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual CDM::enumBrainInjuryType::value GetType() const;
  virtual void SetType(CDM::enumBrainInjuryType::value t);
  virtual bool HasType() const;
  virtual void InvalidateType();

  virtual void ToString(std::ostream& str) const override;

protected:
  SEScalar0To1* m_Severity;
  CDM::enumBrainInjuryType::value m_Type;
};
}