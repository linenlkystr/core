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

IO_DECL(PatientNutrition)

namespace biogears {
class SEPatient;
class SEScalar;
class SEScalarMass;
class MassUnit;
class SEScalarMassPerTime;
class MassPerTimeUnit;
class SEScalarVolume;
class VolumeUnit;

class BIOGEARS_API SENutrition : public Loggable {
  friend class io::PatientNutrition;

public:
  SENutrition(Logger* logger);
  virtual ~SENutrition();

  virtual void Clear();


public:
  const SEScalar* GetScalar(const char* name);
  const SEScalar* GetScalar(const std::string& name);

  void Load(const char* nutritionFile);
  void Load(const std::string& nutritionFile);

  void Increment(const SENutrition& from);

  virtual std::string GetName() const;
  virtual const char* GetName_cStr() const;
  virtual void SetName(const char* name);
  virtual void SetName(const std::string& name);
  virtual bool HasName() const;
  virtual void InvalidateName();

  virtual bool HasCarbohydrate() const;
  virtual SEScalarMass& GetCarbohydrate();
  virtual double GetCarbohydrate(const MassUnit& unit) const;

  virtual bool HasCarbohydrateDigestionRate() const;
  virtual SEScalarMassPerTime& GetCarbohydrateDigestionRate();
  virtual double GetCarbohydrateDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasFat() const;
  virtual SEScalarMass& GetFat();
  virtual double GetFat(const MassUnit& unit) const;

  virtual bool HasFatDigestionRate() const;
  virtual SEScalarMassPerTime& GetFatDigestionRate();
  virtual double GetFatDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasProtein() const;
  virtual SEScalarMass& GetProtein();
  virtual double GetProtein(const MassUnit& unit) const;

  virtual bool HasProteinDigestionRate() const;
  virtual SEScalarMassPerTime& GetProteinDigestionRate();
  virtual double GetProteinDigestionRate(const MassPerTimeUnit& unit) const;

  virtual bool HasSodium() const;
  virtual SEScalarMass& GetSodium();
  virtual double GetSodium(const MassUnit& unit) const;

  virtual bool HasCalcium() const;
  virtual SEScalarMass& GetCalcium();
  virtual double GetCalcium(const MassUnit& unit) const;

  virtual bool HasWater() const;
  virtual SEScalarVolume& GetWater();
  virtual double GetWater(const VolumeUnit& unit) const;

  virtual double GetWeight(const MassUnit& unit) const;

  virtual void ToString(std::ostream& str) const;

protected:
  std::string m_Name;
  SEScalarMass* m_Carbohydrate;
  SEScalarMassPerTime* m_CarbohydrateDigestionRate;
  SEScalarMass* m_Fat;
  SEScalarMassPerTime* m_FatDigestionRate;
  SEScalarMass* m_Protein;
  SEScalarMassPerTime* m_ProteinDigestionRate;
  SEScalarMass* m_Calcium;
  SEScalarMass* m_Sodium;
  SEScalarVolume* m_Water;
};

inline std::ostream& operator<<(std::ostream& out, const SENutrition& n)
{
  n.ToString(out);
  return out;
}
}