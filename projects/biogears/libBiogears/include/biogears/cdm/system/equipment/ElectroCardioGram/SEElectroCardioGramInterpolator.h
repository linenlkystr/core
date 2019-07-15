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

#include <biogears/cdm/system/physiology/SEPhysiologyEnums.h>

IO_DECL(ElectroCardioGram)

namespace biogears {
class SEElectroCardioGramInterpolatorWaveform;
class SEScalarElectricPotential;

class BIOGEARS_API SEElectroCardioGramInterpolator : public Loggable {
  friend class io::ElectroCardioGram;

public:
  SEElectroCardioGramInterpolator(Logger* logger);
  virtual ~SEElectroCardioGramInterpolator();

  virtual void Clear(); // Deletes all members

  virtual bool LoadWaveforms(const char* file, const SEScalarTime* timeStep = nullptr);
  virtual bool LoadWaveforms(const std::string& file, const SEScalarTime* timeStep = nullptr);
  
  virtual void Interpolate(const SEScalarTime& timeStep);
  virtual bool StartNewCycle(SEHeartRhythm rhythm);
  virtual void CalculateWaveformsElectricPotential();

  // These are where the interpolator will put the interpolated electric potential data for each lead when you call CalculateWaveformsElectricPotential
  // You must have a waveform for the lead of the current rhythm for these scalars to be populated
  virtual bool CanInterpolateLeadPotential(unsigned int lead, SEHeartRhythm rhythm) const;
  virtual void SetLeadElectricPotential(unsigned int lead, SEScalarElectricPotential& ep);

  virtual bool HasWaveform(unsigned int lead, SEHeartRhythm rhythm) const;
  virtual SEElectroCardioGramInterpolatorWaveform& GetWaveform(unsigned int lead, SEHeartRhythm rhythm);
  virtual const SEElectroCardioGramInterpolatorWaveform* GetWaveform(unsigned int lead, SEHeartRhythm rhythm) const;
  virtual void RemoveWaveform(unsigned int lead, SEHeartRhythm rhythm);

protected:
  virtual void Interpolate(SEElectroCardioGramInterpolatorWaveform& waveform, const SEScalarTime& timeStep);

  std::map<unsigned int, SEScalarElectricPotential*> m_Leads;
  std::map<unsigned int, std::map<SEHeartRhythm, SEElectroCardioGramInterpolatorWaveform*>> m_Waveforms;
};
}