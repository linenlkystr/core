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
#include <biogears/cdm/system/physiology/SETissueSystem.h>

#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarElectricPotential.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/container/Tree.tci.h>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {
  constexpr char idCarbonDioxideProductionRate[] = "CarbonDioxideProductionRate";
  constexpr char idDehydrationFraction[] = "DehydrationFraction";
  constexpr char idExtracellularFluidVolume[] = "ExtracellularFluidVolume";
  constexpr char idExtravascularFluidVolume[] = "ExtravascularFluidVolume";
  constexpr char idIntracellularFluidPH[] = "IntracellularFluidPH";
  constexpr char idIntracellularFluidVolume[] = "IntracellularFluidVolume";
  constexpr char idTotalBodyFluidVolume[] = "TotalBodyFluidVolume";
  constexpr char idOxygenConsumptionRate[] = "OxygenConsumptionRate";
  constexpr char idRespiratoryExchangeRatio[] = "RespiratoryExchangeRatio";
  constexpr char idLiverInsulinSetPoint[] = "LiverInsulinSetPoint";
  constexpr char idLiverGlucagonSetPoint[] = "LiverGlucagonSetPoint";
  constexpr char idMuscleInsulinSetPoint[] = "MuscleInsulinSetPoint";
  constexpr char idMuscleGlucagonSetPoint[] = "MuscleGlucagonSetPoint";
  constexpr char idFatInsulinSetPoint[] = "FatInsulinSetPoint";
  constexpr char idFatGlucagonSetPoint[] = "FatGlucagonSetPoint";
  constexpr char idLiverGlycogen[] = "LiverGlycogen";
  constexpr char idMuscleGlycogen[] = "MuscleGlycogen";
  constexpr char idStoredProtein[] = "StoredProtein";
  constexpr char idStoredFat[] = "StoredFat";


SETissueSystem::SETissueSystem(Logger* logger)
  : SESystem(logger)
{
  m_CarbonDioxideProductionRate = nullptr;
  m_DehydrationFraction = nullptr;
  m_ExtracellularFluidVolume = nullptr;
  m_ExtravascularFluidVolume = nullptr;
  m_IntracellularFluidVolume = nullptr;
  m_TotalBodyFluidVolume = nullptr;
  m_IntracellularFluidPH = nullptr;
  m_OxygenConsumptionRate = nullptr;
  m_RespiratoryExchangeRatio = nullptr;
  m_LiverInsulinSetPoint = nullptr;
  m_LiverGlucagonSetPoint = nullptr;
  m_MuscleInsulinSetPoint = nullptr;
  m_MuscleGlucagonSetPoint = nullptr;
  m_FatInsulinSetPoint = nullptr;
  m_FatGlucagonSetPoint = nullptr;
  m_LiverGlycogen = nullptr;
  m_MuscleGlycogen = nullptr;
  m_StoredProtein = nullptr;
  m_StoredFat = nullptr;
}
//-------------------------------------------------------------------------------
SETissueSystem::~SETissueSystem()
{
  Clear();
}
//-------------------------------------------------------------------------------
void SETissueSystem::Clear()
{
  SAFE_DELETE(m_CarbonDioxideProductionRate);
  SAFE_DELETE(m_DehydrationFraction);
  SAFE_DELETE(m_ExtracellularFluidVolume);
  SAFE_DELETE(m_ExtravascularFluidVolume);
  SAFE_DELETE(m_IntracellularFluidVolume);
  SAFE_DELETE(m_TotalBodyFluidVolume);
  SAFE_DELETE(m_IntracellularFluidPH);
  SAFE_DELETE(m_OxygenConsumptionRate);
  SAFE_DELETE(m_RespiratoryExchangeRatio);
  SAFE_DELETE(m_LiverInsulinSetPoint);
  SAFE_DELETE(m_LiverGlucagonSetPoint);
  SAFE_DELETE(m_MuscleInsulinSetPoint);
  SAFE_DELETE(m_MuscleGlucagonSetPoint);
  SAFE_DELETE(m_FatInsulinSetPoint);
  SAFE_DELETE(m_FatGlucagonSetPoint);
  SAFE_DELETE(m_LiverGlycogen);
  SAFE_DELETE(m_MuscleGlycogen);
  SAFE_DELETE(m_StoredProtein);
  SAFE_DELETE(m_StoredFat);
}
//-------------------------------------------------------------------------------
const SEScalar* SETissueSystem::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-------------------------------------------------------------------------------
const SEScalar* SETissueSystem::GetScalar(const std::string& name)
{
  if (name == idCarbonDioxideProductionRate)
    return &GetCarbonDioxideProductionRate();
  if (name == idDehydrationFraction)
    return &GetDehydrationFraction();
  if (name == idExtracellularFluidVolume)
    return &GetExtracellularFluidVolume();
  if (name == idExtravascularFluidVolume)
    return &GetExtravascularFluidVolume();
  if (name == idIntracellularFluidPH)
    return &GetIntracellularFluidPH();
  if (name == idIntracellularFluidVolume)
    return &GetIntracellularFluidVolume();
  if (name == idTotalBodyFluidVolume)
    return &GetTotalBodyFluidVolume();
  if (name == idOxygenConsumptionRate)
    return &GetOxygenConsumptionRate();
  if (name == idRespiratoryExchangeRatio)
    return &GetRespiratoryExchangeRatio();
  if (name == idLiverInsulinSetPoint)
    return &GetLiverInsulinSetPoint();
  if (name == idLiverGlucagonSetPoint)
    return &GetLiverGlucagonSetPoint();
  if (name == idMuscleInsulinSetPoint)
    return &GetMuscleInsulinSetPoint();
  if (name == idMuscleGlucagonSetPoint)
    return &GetMuscleGlucagonSetPoint();
  if (name == idFatInsulinSetPoint)
    return &GetFatInsulinSetPoint();
  if (name == idFatGlucagonSetPoint)
    return &GetFatGlucagonSetPoint();
  if (name == idLiverGlycogen)
    return &GetLiverGlycogen();
  if (name == idMuscleGlycogen)
    return &GetMuscleGlycogen();
  if (name == idStoredProtein)
    return &GetStoredProtein();
  if (name == idStoredFat)
    return &GetStoredFat();

  return nullptr;
}
//-------------------------------------------------------------------------------
bool SETissueSystem::Load(const CDM::TissueSystemData& in)
{
  SESystem::Load(in);
  if (in.CarbonDioxideProductionRate().present())
    io::PropertyIoDelegate::Marshall(in.CarbonDioxideProductionRate(), GetCarbonDioxideProductionRate());
  if (in.DehydrationFraction().present())
      io::PropertyIoDelegate::Marshall(in.DehydrationFraction(), GetDehydrationFraction());
  if (in.ExtracellularFluidVolume().present())
      io::PropertyIoDelegate::Marshall(in.ExtracellularFluidVolume(), GetExtracellularFluidVolume());
  if (in.ExtravascularFluidVolume().present())
      io::PropertyIoDelegate::Marshall(in.ExtravascularFluidVolume(), GetExtravascularFluidVolume());
  if (in.IntracellularFluidPH().present())
      io::PropertyIoDelegate::Marshall(in.IntracellularFluidPH(), GetIntracellularFluidPH());
  if (in.IntracellularFluidVolume().present())
      io::PropertyIoDelegate::Marshall(in.IntracellularFluidVolume(), GetIntracellularFluidVolume());
  if (in.TotalBodyFluidVolume().present())
      io::PropertyIoDelegate::Marshall(in.TotalBodyFluidVolume(), GetTotalBodyFluidVolume());
  if (in.OxygenConsumptionRate().present())
      io::PropertyIoDelegate::Marshall(in.OxygenConsumptionRate(), GetOxygenConsumptionRate());
  if (in.RespiratoryExchangeRatio().present())
    io::PropertyIoDelegate::Marshall(in.RespiratoryExchangeRatio(), GetRespiratoryExchangeRatio());
  if (in.LiverInsulinSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.LiverInsulinSetPoint(), GetLiverInsulinSetPoint());
  if (in.LiverGlucagonSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.LiverGlucagonSetPoint(), GetLiverGlucagonSetPoint());
  if (in.MuscleInsulinSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.MuscleInsulinSetPoint(), GetMuscleInsulinSetPoint());
  if (in.MuscleGlucagonSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.MuscleGlucagonSetPoint(), GetMuscleGlucagonSetPoint());
  if (in.FatInsulinSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.FatInsulinSetPoint(), GetFatInsulinSetPoint());
  if (in.FatGlucagonSetPoint().present())
      io::PropertyIoDelegate::Marshall(in.FatGlucagonSetPoint(), GetFatGlucagonSetPoint());
  if (in.LiverGlycogen().present())
      io::PropertyIoDelegate::Marshall(in.LiverGlycogen(), GetLiverGlycogen());
  if (in.MuscleGlycogen().present())
    io::PropertyIoDelegate::Marshall(in.MuscleGlycogen(), GetMuscleGlycogen());
  if (in.StoredProtein().present())
      io::PropertyIoDelegate::Marshall(in.StoredProtein(), GetStoredProtein());
  if (in.StoredFat().present())
      io::PropertyIoDelegate::Marshall(in.StoredFat(), GetStoredFat());

  return true;
}
//-------------------------------------------------------------------------------
CDM::TissueSystemData* SETissueSystem::Unload() const
{
  CDM::TissueSystemData* data = new CDM::TissueSystemData();
  Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------
void SETissueSystem::Unload(CDM::TissueSystemData& data) const
{
  if (m_CarbonDioxideProductionRate != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_CarbonDioxideProductionRate, data.CarbonDioxideProductionRate());
  if (m_DehydrationFraction != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_DehydrationFraction, data.DehydrationFraction());
  if (m_ExtracellularFluidVolume != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_ExtracellularFluidVolume, data.ExtracellularFluidVolume());
  if (m_ExtravascularFluidVolume != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_ExtravascularFluidVolume, data.ExtravascularFluidVolume());
  if (m_IntracellularFluidPH != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_IntracellularFluidPH, data.IntracellularFluidPH());
  if (m_IntracellularFluidVolume != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_IntracellularFluidVolume, data.IntracellularFluidVolume());
  if (m_TotalBodyFluidVolume != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_TotalBodyFluidVolume, data.TotalBodyFluidVolume());
  if (m_OxygenConsumptionRate != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_OxygenConsumptionRate, data.OxygenConsumptionRate());
  if (m_RespiratoryExchangeRatio != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_RespiratoryExchangeRatio, data.RespiratoryExchangeRatio());
  if (m_LiverInsulinSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_LiverInsulinSetPoint, data.LiverInsulinSetPoint());
  if (m_LiverGlucagonSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_LiverGlucagonSetPoint, data.LiverGlucagonSetPoint());
  if (m_MuscleInsulinSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_MuscleInsulinSetPoint, data.MuscleInsulinSetPoint());
  if (m_MuscleGlucagonSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_MuscleGlucagonSetPoint, data.MuscleGlucagonSetPoint());
  if (m_FatInsulinSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_FatInsulinSetPoint, data.FatInsulinSetPoint());
  if (m_FatGlucagonSetPoint != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_FatGlucagonSetPoint, data.FatGlucagonSetPoint());
  if (m_LiverGlycogen != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_LiverGlycogen, data.LiverGlycogen());
  if (m_MuscleGlycogen != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_MuscleGlycogen, data.MuscleGlycogen());
  if (m_StoredProtein != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_StoredProtein, data.StoredProtein());
  if (m_StoredFat != nullptr)
      io::PropertyIoDelegate::UnMarshall(*m_StoredFat, data.StoredFat());

  SESystem::Unload(data);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasCarbonDioxideProductionRate() const
{
  return m_CarbonDioxideProductionRate == nullptr ? false : m_CarbonDioxideProductionRate->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SETissueSystem::GetCarbonDioxideProductionRate()
{
  if (m_CarbonDioxideProductionRate == nullptr)
    m_CarbonDioxideProductionRate = new SEScalarVolumePerTime();
  return *m_CarbonDioxideProductionRate;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetCarbonDioxideProductionRate(const VolumePerTimeUnit& unit) const
{
  if (m_CarbonDioxideProductionRate == nullptr)
    return SEScalar::dNaN();
  return m_CarbonDioxideProductionRate->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasDehydrationFraction() const
{
  return m_DehydrationFraction == nullptr ? false : m_DehydrationFraction->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar0To1& SETissueSystem::GetDehydrationFraction()
{
  if (m_DehydrationFraction == nullptr)
    m_DehydrationFraction = new SEScalar0To1();
  return *m_DehydrationFraction;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetDehydrationFraction() const
{
  if (m_DehydrationFraction == nullptr)
    return SEScalar::dNaN();
  return m_DehydrationFraction->GetValue();
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasExtracellularFluidVolume() const
{
  return m_ExtracellularFluidVolume == nullptr ? false : m_ExtracellularFluidVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SETissueSystem::GetExtracellularFluidVolume()
{
  if (m_ExtracellularFluidVolume == nullptr)
    m_ExtracellularFluidVolume = new SEScalarVolume();
  return *m_ExtracellularFluidVolume;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetExtracellularFluidVolume(const VolumeUnit& unit) const
{
  if (m_ExtracellularFluidVolume == nullptr)
    return SEScalar::dNaN();
  return m_ExtracellularFluidVolume->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasExtravascularFluidVolume() const
{
  return m_ExtravascularFluidVolume == nullptr ? false : m_ExtravascularFluidVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SETissueSystem::GetExtravascularFluidVolume()
{
  if (m_ExtravascularFluidVolume == nullptr)
    m_ExtravascularFluidVolume = new SEScalarVolume();
  return *m_ExtravascularFluidVolume;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetExtravascularFluidVolume(const VolumeUnit& unit) const
{
  if (m_ExtravascularFluidVolume == nullptr)
    return SEScalar::dNaN();
  return m_ExtravascularFluidVolume->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasIntracellularFluidVolume() const
{
  return m_IntracellularFluidVolume == nullptr ? false : m_IntracellularFluidVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SETissueSystem::GetIntracellularFluidVolume()
{
  if (m_IntracellularFluidVolume == nullptr)
    m_IntracellularFluidVolume = new SEScalarVolume();
  return *m_IntracellularFluidVolume;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetIntracellularFluidVolume(const VolumeUnit& unit) const
{
  if (m_IntracellularFluidVolume == nullptr)
    return SEScalar::dNaN();
  return m_IntracellularFluidVolume->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasTotalBodyFluidVolume() const
{
  return m_TotalBodyFluidVolume == nullptr ? false : m_TotalBodyFluidVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SETissueSystem::GetTotalBodyFluidVolume()
{
  if (m_TotalBodyFluidVolume == nullptr)
    m_TotalBodyFluidVolume = new SEScalarVolume();
  return *m_TotalBodyFluidVolume;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetTotalBodyFluidVolume(const VolumeUnit& unit) const
{
  if (m_TotalBodyFluidVolume == nullptr)
    return SEScalar::dNaN();
  return m_TotalBodyFluidVolume->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasIntracellularFluidPH() const
{
  return m_IntracellularFluidPH == nullptr ? false : m_IntracellularFluidPH->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SETissueSystem::GetIntracellularFluidPH()
{
  if (m_IntracellularFluidPH == nullptr)
    m_IntracellularFluidPH = new SEScalar();
  return *m_IntracellularFluidPH;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetIntracellularFluidPH() const
{
  if (m_IntracellularFluidPH == nullptr)
    return SEScalar::dNaN();
  return m_IntracellularFluidPH->GetValue();
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasOxygenConsumptionRate() const
{
  return m_OxygenConsumptionRate == nullptr ? false : m_OxygenConsumptionRate->IsValid();
}
  //-------------------------------------------------------------------------------
SEScalarVolumePerTime& SETissueSystem::GetOxygenConsumptionRate()
{
  if (m_OxygenConsumptionRate == nullptr)
    m_OxygenConsumptionRate = new SEScalarVolumePerTime();
  return *m_OxygenConsumptionRate;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetOxygenConsumptionRate(const VolumePerTimeUnit& unit) const
{
  if (m_OxygenConsumptionRate == nullptr)
    return SEScalar::dNaN();
  return m_OxygenConsumptionRate->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasRespiratoryExchangeRatio() const
{
  return m_RespiratoryExchangeRatio == nullptr ? false : m_RespiratoryExchangeRatio->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SETissueSystem::GetRespiratoryExchangeRatio()
{
  if (m_RespiratoryExchangeRatio == nullptr)
    m_RespiratoryExchangeRatio = new SEScalar();
  return *m_RespiratoryExchangeRatio;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetRespiratoryExchangeRatio() const
{
  if (m_RespiratoryExchangeRatio == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryExchangeRatio->GetValue();
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasLiverInsulinSetPoint() const
{
  return m_LiverInsulinSetPoint == nullptr ? false : m_LiverInsulinSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarAmountPerVolume& SETissueSystem::GetLiverInsulinSetPoint()
{
  if (m_LiverInsulinSetPoint == nullptr)
    m_LiverInsulinSetPoint = new SEScalarAmountPerVolume();
  return *m_LiverInsulinSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetLiverInsulinSetPoint(const AmountPerVolumeUnit& unit) const
{
  if (m_LiverInsulinSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_LiverInsulinSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasLiverGlucagonSetPoint() const
{
  return m_LiverGlucagonSetPoint == nullptr ? false : m_LiverGlucagonSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMassPerVolume& SETissueSystem::GetLiverGlucagonSetPoint()
{
  if (m_LiverGlucagonSetPoint == nullptr)
    m_LiverGlucagonSetPoint = new SEScalarMassPerVolume();
  return *m_LiverGlucagonSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetLiverGlucagonSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_LiverGlucagonSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_LiverGlucagonSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasMuscleInsulinSetPoint() const
{
  return m_MuscleInsulinSetPoint == nullptr ? false : m_MuscleInsulinSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarAmountPerVolume& SETissueSystem::GetMuscleInsulinSetPoint()
{
  if (m_MuscleInsulinSetPoint == nullptr)
    m_MuscleInsulinSetPoint = new SEScalarAmountPerVolume();
  return *m_MuscleInsulinSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetMuscleInsulinSetPoint(const AmountPerVolumeUnit& unit) const
{
  if (m_MuscleInsulinSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_MuscleInsulinSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasMuscleGlucagonSetPoint() const
{
  return m_MuscleGlucagonSetPoint == nullptr ? false : m_MuscleGlucagonSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMassPerVolume& SETissueSystem::GetMuscleGlucagonSetPoint()
{
  if (m_MuscleGlucagonSetPoint == nullptr)
    m_MuscleGlucagonSetPoint = new SEScalarMassPerVolume();
  return *m_MuscleGlucagonSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetMuscleGlucagonSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_MuscleGlucagonSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_MuscleGlucagonSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasFatInsulinSetPoint() const
{
  return m_FatInsulinSetPoint == nullptr ? false : m_FatInsulinSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarAmountPerVolume& SETissueSystem::GetFatInsulinSetPoint()
{
  if (m_FatInsulinSetPoint == nullptr)
    m_FatInsulinSetPoint = new SEScalarAmountPerVolume();
  return *m_FatInsulinSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetFatInsulinSetPoint(const AmountPerVolumeUnit& unit) const
{
  if (m_FatInsulinSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_FatInsulinSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasFatGlucagonSetPoint() const
{
  return m_FatGlucagonSetPoint == nullptr ? false : m_FatGlucagonSetPoint->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMassPerVolume& SETissueSystem::GetFatGlucagonSetPoint()
{
  if (m_FatGlucagonSetPoint == nullptr)
    m_FatGlucagonSetPoint = new SEScalarMassPerVolume();
  return *m_FatGlucagonSetPoint;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetFatGlucagonSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_FatGlucagonSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_FatGlucagonSetPoint->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasLiverGlycogen() const
{
  return m_LiverGlycogen == nullptr ? false : m_LiverGlycogen->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMass& SETissueSystem::GetLiverGlycogen()
{
  if (m_LiverGlycogen == nullptr)
    m_LiverGlycogen = new SEScalarMass();
  return *m_LiverGlycogen;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetLiverGlycogen(const MassUnit& unit) const
{
  if (m_LiverGlycogen == nullptr)
    return SEScalar::dNaN();
  return m_LiverGlycogen->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasMuscleGlycogen() const
{
  return m_MuscleGlycogen == nullptr ? false : m_MuscleGlycogen->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMass& SETissueSystem::GetMuscleGlycogen()
{
  if (m_MuscleGlycogen == nullptr)
    m_MuscleGlycogen = new SEScalarMass();
  return *m_MuscleGlycogen;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetMuscleGlycogen(const MassUnit& unit) const
{
  if (m_MuscleGlycogen == nullptr)
    return SEScalar::dNaN();
  return m_MuscleGlycogen->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasStoredProtein() const
{
  return m_StoredProtein == nullptr ? false : m_StoredProtein->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMass& SETissueSystem::GetStoredProtein()
{
  if (m_StoredProtein == nullptr)
    m_StoredProtein = new SEScalarMass();
  return *m_StoredProtein;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetStoredProtein(const MassUnit& unit) const
{
  if (m_StoredProtein == nullptr)
    return SEScalar::dNaN();
  return m_StoredProtein->GetValue(unit);
}
//-------------------------------------------------------------------------------
bool SETissueSystem::HasStoredFat() const
{
  return m_StoredFat == nullptr ? false : m_StoredFat->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarMass& SETissueSystem::GetStoredFat()
{
  if (m_StoredFat == nullptr)
    m_StoredFat = new SEScalarMass();
  return *m_StoredFat;
}
//-------------------------------------------------------------------------------
double SETissueSystem::GetStoredFat(const MassUnit& unit) const
{
  if (m_StoredFat == nullptr)
    return SEScalar::dNaN();
  return m_StoredFat->GetValue(unit);
}
//-------------------------------------------------------------------------------
Tree<const char*> SETissueSystem::GetPhysiologyRequestGraph() const
{
  return Tree<const char*>{classname()}
  .emplace_back(idCarbonDioxideProductionRate)
  .emplace_back(idDehydrationFraction)
  .emplace_back(idExtracellularFluidVolume)
  .emplace_back(idExtravascularFluidVolume)
  .emplace_back(idIntracellularFluidPH)
  .emplace_back(idIntracellularFluidVolume)
  .emplace_back(idTotalBodyFluidVolume)
  .emplace_back(idOxygenConsumptionRate)
  .emplace_back(idRespiratoryExchangeRatio)
  .emplace_back(idLiverInsulinSetPoint)
  .emplace_back(idLiverGlucagonSetPoint)
  .emplace_back(idMuscleInsulinSetPoint)
  .emplace_back(idMuscleGlucagonSetPoint)
  .emplace_back(idFatInsulinSetPoint)
  .emplace_back(idFatGlucagonSetPoint)
  .emplace_back(idLiverGlycogen)
  .emplace_back(idMuscleGlycogen)
  .emplace_back(idStoredProtein)
  .emplace_back(idStoredFat)
  ;
}
}