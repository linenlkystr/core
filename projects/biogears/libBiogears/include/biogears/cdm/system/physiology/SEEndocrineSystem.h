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
#include <biogears/cdm/system/SESystem.h>

IO_DECL(Physiology)

namespace biogears {
class SEScalarFraction;
class SEScalarMass;
class MassUnit;
class SEScalarTemperature;
class TemperatureUnit;
class SEScalarAmountPerTime;
class AmountPerTimeUnit;
class SEScalarPressure;
class PressureUnit;
class SEScalarMassPerTime;
class MassPerTimeUnit;
class SEScalarPower;
class PowerUnit;

class BIOGEARS_API SEEndocrineSystem : public SESystem {
  friend class io::Physiology;

public:
  SEEndocrineSystem(Logger* logger);
  ~SEEndocrineSystem() override;

  static size_t TypeHash() { return reinterpret_cast<size_t>(&TypeHash); }
  static constexpr char const * const  TypeTag() { return "SEEndocrineSystem"; }
  const char* classname() const override { return TypeTag(); }
  size_t hash_code() const override { return TypeHash(); }

  void Clear() override; // Deletes all members

  const SEScalar* GetScalar(const char* name) override;
  const SEScalar* GetScalar(const std::string& name) override;

  Tree<const char*> GetPhysiologyRequestGraph() const override;

  bool HasInsulinSynthesisRate() const;
  SEScalarAmountPerTime& GetInsulinSynthesisRate();
  double GetInsulinSynthesisRate(const AmountPerTimeUnit& unit) const;

  bool HasGlucagonSynthesisRate() const;
  SEScalarAmountPerTime& GetGlucagonSynthesisRate();
  double GetGlucagonSynthesisRate(const AmountPerTimeUnit& unit) const;

protected:
  SEScalarAmountPerTime* m_InsulinSynthesisRate;
  SEScalarAmountPerTime* m_GlucagonSynthesisRate;
};
}