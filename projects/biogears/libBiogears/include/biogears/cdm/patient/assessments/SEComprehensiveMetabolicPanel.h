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

IO_DECL(PatientAssessments)

namespace biogears {
class SEBloodChemistrySystem;
class SEScalarMassPerVolume;
class SEScalarAmountPerVolume;

class BIOGEARS_API SEComprehensiveMetabolicPanel : public SEPatientAssessment {
  friend class io::PatientAssessments;

public:
  SEComprehensiveMetabolicPanel(Logger* logger);
  virtual ~SEComprehensiveMetabolicPanel();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  bool HasAlbumin() const;
  SEScalarMassPerVolume& GetAlbumin();

  bool HasALP() const;
  SEScalarMassPerVolume& GetALP();

  bool HasALT() const;
  SEScalarMassPerVolume& GetALT();

  bool HasAST() const;
  SEScalarMassPerVolume& GetAST();

  bool HasBUN() const;
  SEScalarMassPerVolume& GetBUN();

  bool HasCalcium() const;
  SEScalarMassPerVolume& GetCalcium();

  bool HasChloride() const;
  SEScalarAmountPerVolume& GetChloride();

  bool HasCO2() const;
  SEScalarAmountPerVolume& GetCO2();

  bool HasCreatinine() const;
  SEScalarMassPerVolume& GetCreatinine();

  bool HasGlucose() const;
  SEScalarMassPerVolume& GetGlucose();

  bool HasPotassium() const;
  SEScalarAmountPerVolume& GetPotassium();

  bool HasSodium() const;
  SEScalarAmountPerVolume& GetSodium();

  bool HasTotalBilirubin() const;
  SEScalarMassPerVolume& GetTotalBilirubin();

  bool HasTotalProtein() const;
  SEScalarMassPerVolume& GetTotalProtein();

protected:
  SEScalarMassPerVolume* m_Albumin;
  SEScalarMassPerVolume* m_ALP;
  SEScalarMassPerVolume* m_ALT;
  SEScalarMassPerVolume* m_AST;
  SEScalarMassPerVolume* m_BUN;
  SEScalarMassPerVolume* m_Calcium;
  SEScalarAmountPerVolume* m_Chloride;
  SEScalarAmountPerVolume* m_CO2;
  SEScalarMassPerVolume* m_Creatinine;
  SEScalarMassPerVolume* m_Glucose;
  SEScalarAmountPerVolume* m_Potassium;
  SEScalarAmountPerVolume* m_Sodium;
  SEScalarMassPerVolume* m_TotalBilirubin;
  SEScalarMassPerVolume* m_TotalProtein;
};
}