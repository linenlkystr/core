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
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/exports.h>

#include <biogears/cdm/substance/SESubstanceEnums.h>

IO_DECL(Substance)

namespace biogears {
class BIOGEARS_API SESubstancePhysicochemicals : public Loggable {
  friend class io::Substance;

public:
  SESubstancePhysicochemicals(Logger* logger);
  virtual ~SESubstancePhysicochemicals();

  virtual void Clear();
  virtual bool IsValid() const;

  virtual const SEScalar* GetScalar(const char* name);
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasAcidDissociationConstant() const;
  virtual SEScalar& GetAcidDissociationConstant();
  virtual double GetAcidDissociationConstant() const;

  virtual SESubstanceBindingProtein GetBindingProtein() const;
  virtual void SetBindingProtein(SESubstanceBindingProtein state);
  virtual bool HasBindingProtein() const;
  virtual void InvalidateBindingProtein();

  virtual bool HasBloodPlasmaRatio() const;
  virtual SEScalar& GetBloodPlasmaRatio();
  virtual double GetBloodPlasmaRatio() const;

  virtual bool HasFractionUnboundInPlasma() const;
  virtual SEScalarFraction& GetFractionUnboundInPlasma();
  virtual double GetFractionUnboundInPlasma() const;

  virtual SESubstanceIonicState GetIonicState() const;
  virtual void SetIonicState(SESubstanceIonicState state);
  virtual bool HasIonicState() const;
  virtual void InvalidateIonicState();

  virtual bool HasLogP() const;
  virtual SEScalar& GetLogP();
  virtual double GetLogP() const;

  virtual bool HasOralAbsorptionRateConstant() const;
  virtual SEScalar& GetOralAbsorptionRateConstant();
  virtual double GetOralAbsorptionRateConstant() const;

protected:
  SEScalar* m_AcidDissociationConstant;
  SESubstanceBindingProtein m_BindingProtein;
  SEScalar* m_BloodPlasmaRatio;
  SEScalarFraction* m_FractionUnboundInPlasma;
  SESubstanceIonicState m_IonicState;
  SEScalar* m_LogP;
  SEScalar* m_OralAbsorptionRateConstant;
};
}