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
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include "biogears/cdm/properties/SEScalarMassPerAmount.h"

IO_DECL(PatientAssessments)

namespace biogears {
class SEScalarFraction;
class SEScalarMassPerVolume;
class SEScalarAmountPerVolume;
class SEScalarMassPerAmount;

class BIOGEARS_API SECompleteBloodCount : public SEPatientAssessment {
  friend class io::PatientAssessments;

public:
  SECompleteBloodCount(Logger* logger);
  virtual ~SECompleteBloodCount();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  virtual bool HasHematocrit() const;
  virtual SEScalarFraction& GetHematocrit();

  virtual bool HasHemoglobin() const;
  virtual SEScalarMassPerVolume& GetHemoglobin();

  virtual bool HasPlateletCount() const;
  virtual SEScalarAmountPerVolume& GetPlateletCount();

  virtual bool HasMeanCorpuscularHemoglobin() const;
  virtual SEScalarMassPerAmount& GetMeanCorpuscularHemoglobin();

  virtual bool HasMeanCorpuscularHemoglobinConcentration() const;
  virtual SEScalarMassPerVolume& GetMeanCorpuscularHemoglobinConcentration();

  virtual bool HasMeanCorpuscularVolume() const;
  virtual SEScalarVolume& GetMeanCorpuscularVolume();

  virtual bool HasRedBloodCellCount() const;
  virtual SEScalarAmountPerVolume& GetRedBloodCellCount();

  virtual bool HasWhiteBloodCellCount() const;
  virtual SEScalarAmountPerVolume& GetWhiteBloodCellCount();

protected:
  SEScalarFraction* m_Hematocrit;
  SEScalarMassPerVolume* m_Hemoglobin;
  SEScalarAmountPerVolume* m_PlateletCount;
  SEScalarMassPerAmount* m_MeanCorpuscularHemoglobin;
  SEScalarMassPerVolume* m_MeanCorpuscularHemoglobinConcentration;
  SEScalarVolume* m_MeanCorpuscularVolume;
  SEScalarAmountPerVolume* m_RedBloodCellCount;
  SEScalarAmountPerVolume* m_WhiteBloodCellCount;
};
}