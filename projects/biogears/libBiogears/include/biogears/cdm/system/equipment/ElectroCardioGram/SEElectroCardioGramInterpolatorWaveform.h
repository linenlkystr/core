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
#include <biogears/exports.h>

#include <biogears/cdm/system/physiology/SEPhysiologyEnums.h>

IO_DECL(ElectroCardioGram)

namespace biogears {
class TimeUnit;

class BIOGEARS_API SEElectroCardioGramInterpolatorWaveform : public Loggable {
  friend class io::ElectroCardioGram;

public:
  SEElectroCardioGramInterpolatorWaveform(Logger* logger);
  virtual ~SEElectroCardioGramInterpolatorWaveform();

  virtual void Clear(); // Deletes all members

  virtual bool HasLeadNumber() const;
  virtual unsigned int GetLeadNumber() const;
  virtual void SetLeadNumber(unsigned int n);
  virtual void InvalidateLeadNumber();

  virtual SEHeartRhythm GetRhythm() const;
  virtual void SetRhythm(SEHeartRhythm name);
  virtual bool HasRhythm() const;
  virtual void InvalidateRhythm();

  virtual bool HasData() const;
  virtual SEFunctionElectricPotentialVsTime& GetData();
  virtual const SEFunctionElectricPotentialVsTime* GetData() const;

  virtual bool HasTimeStep() const;
  virtual SEScalarTime& GetTimeStep();
  virtual double GetTimeStep(const TimeUnit& unit) const;

  virtual std::vector<unsigned int>& GetActiveIndicies() { return m_ActiveIndicies; }

protected:
  unsigned int m_LeadNumber;
  SEHeartRhythm m_Rhythm;
  SEScalarTime* m_TimeStep;
  SEFunctionElectricPotentialVsTime* m_Data;
  std::vector<unsigned int> m_ActiveIndicies;
};
}