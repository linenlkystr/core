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
#include <biogears/cdm/system/physiology/SENervousSystem.h>
#include <biogears/engine/Controller/BioGearsSystem.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

namespace biogears {
class SESubstance;
class BioGears;
class SEPatient;
/**
 * @brief 
 * The nervous class holds models of the peripheral and central nervous system. Currently, on the baroreceptor reflex is modeled.
 */
class BIOGEARS_API Nervous : public SENervousSystem, public BioGearsSystem {
  friend class BioGears;
  friend class BioGearsEngineTest;

protected:
  Nervous(BioGears& bg);
  BioGears& m_data;

public:
  virtual ~Nervous() override;

  static size_t TypeHash() { return reinterpret_cast<size_t>(&TypeHash); }
  static constexpr char const * const  TypeTag() { return "Nervous"; }
  const char* classname() const override { return TypeTag(); }
  size_t hash_code() const override { return TypeHash(); }

  void Clear() override;

  // Set members to a stable homeostatic state
  void Initialize() override;

  // Load a state
  virtual bool Load(const CDM::BioGearsNervousSystemData& in);
  virtual CDM::BioGearsNervousSystemData* Unload() const override;

protected:
  virtual void Unload(CDM::BioGearsNervousSystemData& data) const;

  // Set pointers and other member variables common to both homeostatic initialization and loading a state
  void SetUp() override;

public:
  void AtSteadyState() override;
  void PreProcess() override;
  void Process() override;
  void PostProcess() override;

protected:
  void BaroreceptorFeedback();
  void CheckPainStimulus();
  void CheckNervousStatus();
  void ChemoreceptorFeedback();
  void SetPupilEffects();

  // Serializable member variables (Set in Initialize and in schema)
  double m_ArterialOxygenSetPoint_mmHg; /// \todo Aaron these should be baselines.
  double m_ArterialCarbonDioxideSetPoint_mmHg;
  double m_CentralVentilationDelta_L_Per_min;
  double m_ChemoreceptorFiringRate_Hz;
  double m_ChemoreceptorFiringRateSetPoint_Hz;
  double m_PeripheralBloodGasInteractionBaseline_Hz;
  double m_PeripheralVentilationDelta_L_Per_min;

  // Stateless member variable (Set in SetUp())
  bool m_FeedbackActive;
  double m_dt_s;
  SESubstance* m_Succinylcholine;
  SESubstance* m_Sarin;
  SEPatient* m_Patient;
  bool m_blockActive;
  double m_painStimulusDuration_s;
  double m_painVASDuration_s;
  double m_painVAS;
  double m_painStimulus;

  // Configuration fractions representing the amount by which each quantity can change due to baroreceptors;
  double m_normalizedGammaHeartRate;
  double m_normalizedGammaElastance;
  double m_normalizedGammaCompliance;
  double m_normalizedGammaResistance;
  double m_normalizedAlphaHeartRate;
  double m_normalizedAlphaElastance;
  double m_normalizedAlphaCompliance;
  double m_normalizedAlphaResistance;
  double m_normalizedBetaHeartRate;

};
}