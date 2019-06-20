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

#include <biogears/schema/cdm/Substance.hxx>

#include <biogears/cdm/substance/SESubstanceAerosolization.h>
#include <biogears/cdm/substance/SESubstanceClearance.h>
#include <biogears/cdm/substance/SESubstancePharmacodynamics.h>
#include <biogears/cdm/substance/SESubstancePharmacokinetics.h>

CDM_BIND_DECL(SubstanceData) 

namespace biogears {
class SEScalarMass;
class MassUnit;
class SEScalarMassPerAmount;
class MassPerAmountUnit;
class SEScalarVolumePerTimePressure;
class VolumePerTimePressureUnit;
class SEScalarInversePressure;
class InversePressureUnit;
class SEScalarMassPerAreaTime;
class MassPerAreaTimeUnit;
class SESubstancePharmacodynamics;
class SEScalarElectricResistance;
class ElectricResistanceUnit;
class SEScalarVolumePerTime;
class VolumePerTimeUnit;
class SEScalarPressure;
class PressureUnit;

class BIOGEARS_API SESubstance : public Loggable {
public:
  SESubstance(Logger* logger);
  SESubstance(const SESubstance&) = delete;
  SESubstance(SESubstance&&);
  SESubstance& operator=(const SESubstance&) = delete;
  SESubstance& operator=(SESubstance&&) noexcept;
  virtual ~SESubstance();

  virtual void Clear();

  virtual const SEScalar* GetScalar(const char* name);
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool Load(const CDM::SubstanceData& in);
  virtual CDM::SubstanceData* Unload() const;

protected:
  virtual void Unload(CDM::SubstanceData& data) const;

public:
  virtual std::string GetName() const;
  virtual const char* GetName_cStr() const;
  virtual void SetName(const char* name);
  virtual void SetName(const std::string& name);
  virtual bool HasName() const;
  virtual void InvalidateName();

  virtual CDM::enumSubstanceState::value GetState() const;
  virtual void SetState(CDM::enumSubstanceState::value state);
  virtual bool HasState() const;
  virtual void InvalidateState();

  virtual CDM::enumSubstanceClass::value GetClassification() const;
  virtual void SetClassification(CDM::enumSubstanceClass::value subClass);
  virtual bool HasClassification() const;
  virtual void InvalidateClassification();

  virtual bool HasDensity() const;
  virtual SEScalarMassPerVolume& GetDensity();
  virtual double GetDensity(const MassPerVolumeUnit& unit) const noexcept;

  virtual bool HasMolarMass() const;
  virtual SEScalarMassPerAmount& GetMolarMass();
  virtual double GetMolarMass(const MassPerAmountUnit& unit) const noexcept;

  // Diffusion-ish
  virtual bool HasMaximumDiffusionFlux() const;
  virtual SEScalarMassPerAreaTime& GetMaximumDiffusionFlux();
  virtual double GetMaximumDiffusionFlux(const MassPerAreaTimeUnit& unit) const noexcept;

  virtual bool HasMichaelisCoefficient() const;
  virtual SEScalar& GetMichaelisCoefficient();
  virtual double GetMichaelisCoefficient() const noexcept;

  virtual bool HasMembraneResistance() const;
  virtual SEScalarElectricResistance& GetMembraneResistance();
  virtual double GetMembraneResistance(const ElectricResistanceUnit& unit) const noexcept;

  // Liquid-ish
  virtual bool HasAerosolization() const;
  virtual SESubstanceAerosolization& GetAerosolization();
  virtual const SESubstanceAerosolization* GetAerosolization() const;

  virtual bool HasBloodConcentration() const;
  virtual SEScalarMassPerVolume& GetBloodConcentration();
  virtual double GetBloodConcentration(const MassPerVolumeUnit& unit) const noexcept;

  virtual bool HasMassInBody() const;
  virtual SEScalarMass& GetMassInBody();
  virtual double GetMassInBody(const MassUnit& unit) const noexcept;

  virtual bool HasMassInBlood() const;
  virtual SEScalarMass& GetMassInBlood();
  virtual double GetMassInBlood(const MassUnit& unit) const noexcept;

  virtual bool HasMassInTissue() const;
  virtual SEScalarMass& GetMassInTissue();
  virtual double GetMassInTissue(const MassUnit& unit) const noexcept;

  virtual bool HasPlasmaConcentration() const;
  virtual SEScalarMassPerVolume& GetPlasmaConcentration();
  virtual double GetPlasmaConcentration(const MassPerVolumeUnit& unit) const noexcept;

  virtual bool HasEffectSiteConcentration() const;
  virtual SEScalarMassPerVolume& GetEffectSiteConcentration();
  virtual double GetEffectSiteConcentration(const MassPerVolumeUnit& unit) const noexcept;

  virtual bool HasSystemicMassCleared() const;
  virtual SEScalarMass& GetSystemicMassCleared();
  virtual double GetSystemicMassCleared(const MassUnit& unit) const noexcept;

  virtual bool HasTissueConcentration() const;
  virtual SEScalarMassPerVolume& GetTissueConcentration();
  virtual double GetTissueConcentration(const MassPerVolumeUnit& unit) const noexcept;

  // Gas-ish
  virtual bool HasAlveolarTransfer() const;
  virtual SEScalarVolumePerTime& GetAlveolarTransfer();
  virtual double GetAlveolarTransfer(const VolumePerTimeUnit& unit) const noexcept;

  virtual bool HasDiffusingCapacity() const;
  virtual SEScalarVolumePerTimePressure& GetDiffusingCapacity();
  virtual double GetDiffusingCapacity(const VolumePerTimePressureUnit& unit) const noexcept;

  virtual bool HasEndTidalFraction() const;
  virtual SEScalarFraction& GetEndTidalFraction();
  virtual double GetEndTidalFraction() const noexcept;

  virtual bool HasEndTidalPressure() const;
  virtual SEScalarPressure& GetEndTidalPressure();
  virtual double GetEndTidalPressure(const PressureUnit& unit) const noexcept;

  virtual bool HasRelativeDiffusionCoefficient() const;
  virtual SEScalar& GetRelativeDiffusionCoefficient();
  virtual double GetRelativeDiffusionCoefficient() const noexcept;

  virtual bool HasSolubilityCoefficient() const;
  virtual SEScalarInversePressure& GetSolubilityCoefficient();
  virtual double GetSolubilityCoefficient(const InversePressureUnit& unit) const noexcept;

  virtual bool HasClearance() const;
  virtual SESubstanceClearance& GetClearance();
  virtual const SESubstanceClearance* GetClearance() const;


  virtual bool HasPK() const;
  virtual SESubstancePharmacokinetics& GetPK();
  virtual const SESubstancePharmacokinetics* GetPK() const;


  virtual bool HasPD() const;
  virtual SESubstancePharmacodynamics& GetPD();
  virtual const SESubstancePharmacodynamics* GetPD() const;


protected:
  struct Implementation;
  std::unique_ptr<Implementation> m_impl;
};
}