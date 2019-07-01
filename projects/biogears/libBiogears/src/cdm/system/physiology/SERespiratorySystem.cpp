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
#include <biogears/cdm/system/physiology/SERespiratorySystem.h>

#include <biogears/cdm/properties/SEScalarArea.h>
#include <biogears/cdm/properties/SEScalarFlowCompliance.h>
#include <biogears/cdm/properties/SEScalarFlowResistance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/container/Tree.tci.h>

#include "../../utils/io/Property.h"
namespace biogears {
  constexpr char idAlveolarArterialGradient[] = "AlveolarArterialGradient";
  constexpr char idCarricoIndex[] = "CarricoIndex";
  constexpr char idEndTidalCarbonDioxideFraction[] = "EndTidalCarbonDioxideFraction";
  constexpr char idEndTidalCarbonDioxidePressure[] = "EndTidalCarbonDioxidePressure";
  constexpr char idExpiratoryFlow[] = "ExpiratoryFlow";
  constexpr char idInspiratoryExpiratoryRatio[] = "InspiratoryExpiratoryRatio";
  constexpr char idInspiratoryFlow[] = "InspiratoryFlow";
  constexpr char idPulmonaryCompliance[] = "PulmonaryCompliance";
  constexpr char idPulmonaryResistance[] = "PulmonaryResistance";
  constexpr char idRespirationDriverPressure[] = "RespirationDriverPressure";
  constexpr char idRespirationMusclePressure[] = "RespirationMusclePressure";
  constexpr char idRespirationRate[] = "RespirationRate";
  constexpr char idSpecificVentilation[] = "SpecificVentilation";
  constexpr char idTargetPulmonaryVentilation[] = "TargetPulmonaryVentilation";
  constexpr char idTidalVolume[] = "TidalVolume";
  constexpr char idTotalAlveolarVentilation[] = "TotalAlveolarVentilation";
  constexpr char idTotalDeadSpaceVentilation[] = "TotalDeadSpaceVentilation";
  constexpr char idTotalLungVolume[] = "TotalLungVolume";
  constexpr char idTotalPulmonaryVentilation[] = "TotalPulmonaryVentilation";
  constexpr char idTranspulmonaryPressure[] = "TranspulmonaryPressure";
SERespiratorySystem::SERespiratorySystem(Logger* logger)
  : SESystem(logger)
{
  m_AlveolarArterialGradient = nullptr;
  m_CarricoIndex = nullptr;
  m_EndTidalCarbonDioxideFraction = nullptr;
  m_EndTidalCarbonDioxidePressure = nullptr;
  m_ExpiratoryFlow = nullptr;
  m_InspiratoryExpiratoryRatio = nullptr;
  m_InspiratoryFlow = nullptr;
  m_PulmonaryCompliance = nullptr;
  m_PulmonaryResistance = nullptr;
  m_RespirationDriverPressure = nullptr;
  m_RespirationMusclePressure = nullptr;
  m_RespirationRate = nullptr;
  m_SpecificVentilation = nullptr;
  m_TargetPulmonaryVentilation = nullptr;
  m_TidalVolume = nullptr;
  m_TotalAlveolarVentilation = nullptr;
  m_TotalDeadSpaceVentilation = nullptr;
  m_TotalLungVolume = nullptr;
  m_TotalPulmonaryVentilation = nullptr;
  m_TranspulmonaryPressure = nullptr;
}
//-------------------------------------------------------------------------------

SERespiratorySystem::~SERespiratorySystem()
{
  Clear();
}
//-------------------------------------------------------------------------------

void SERespiratorySystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_AlveolarArterialGradient);
  SAFE_DELETE(m_CarricoIndex);
  SAFE_DELETE(m_EndTidalCarbonDioxideFraction);
  SAFE_DELETE(m_EndTidalCarbonDioxidePressure);
  SAFE_DELETE(m_ExpiratoryFlow);
  SAFE_DELETE(m_InspiratoryExpiratoryRatio);
  SAFE_DELETE(m_InspiratoryFlow);
  SAFE_DELETE(m_PulmonaryCompliance);
  SAFE_DELETE(m_PulmonaryResistance);
  SAFE_DELETE(m_RespirationDriverPressure);
  SAFE_DELETE(m_RespirationMusclePressure);
  SAFE_DELETE(m_RespirationRate);
  SAFE_DELETE(m_TargetPulmonaryVentilation);
  SAFE_DELETE(m_TidalVolume);
  SAFE_DELETE(m_TotalAlveolarVentilation);
  SAFE_DELETE(m_TotalDeadSpaceVentilation);
  SAFE_DELETE(m_TotalLungVolume);
  SAFE_DELETE(m_TotalPulmonaryVentilation);
  SAFE_DELETE(m_TranspulmonaryPressure);
}
//-------------------------------------------------------------------------------
const SEScalar* SERespiratorySystem::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-------------------------------------------------------------------------------
const SEScalar* SERespiratorySystem::GetScalar(const std::string& name)
{
  if (name == idAlveolarArterialGradient)
    return &GetAlveolarArterialGradient();
  if (name == idCarricoIndex)
    return &GetCarricoIndex();
  if (name == idEndTidalCarbonDioxideFraction)
    return &GetEndTidalCarbonDioxideFraction();
  if (name == idEndTidalCarbonDioxidePressure)
    return &GetEndTidalCarbonDioxidePressure();
  if (name == idExpiratoryFlow)
    return &GetExpiratoryFlow();
  if (name == idInspiratoryExpiratoryRatio)
    return &GetInspiratoryExpiratoryRatio();
  if (name == idInspiratoryFlow)
    return &GetInspiratoryFlow();
  if (name == idPulmonaryCompliance)
    return &GetPulmonaryCompliance();
  if (name == idPulmonaryResistance)
    return &GetPulmonaryResistance();
  if (name == idRespirationDriverPressure)
    return &GetRespirationDriverPressure();
  if (name == idRespirationMusclePressure)
    return &GetRespirationMusclePressure();
  if (name == idRespirationRate)
    return &GetRespirationRate();
  if (name == idSpecificVentilation)
    return &GetSpecificVentilation();
  if (name == idTargetPulmonaryVentilation)
    return &GetTargetPulmonaryVentilation();
  if (name == idTidalVolume)
    return &GetTidalVolume();
  if (name == idTotalAlveolarVentilation)
    return &GetTotalAlveolarVentilation();
  if (name == idTotalDeadSpaceVentilation)
    return &GetTotalDeadSpaceVentilation();
  if (name == idTotalLungVolume)
    return &GetTotalLungVolume();
  if (name == idTotalPulmonaryVentilation)
    return &GetTotalPulmonaryVentilation();
  if (name == idTranspulmonaryPressure)
    return &GetTranspulmonaryPressure();
  return nullptr;
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasAlveolarArterialGradient() const
{
  return m_AlveolarArterialGradient == nullptr ? false : m_AlveolarArterialGradient->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetAlveolarArterialGradient()
{
  if (m_AlveolarArterialGradient == nullptr)
    m_AlveolarArterialGradient = new SEScalarPressure();
  return *m_AlveolarArterialGradient;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetAlveolarArterialGradient(const PressureUnit& unit) const
{
  if (m_AlveolarArterialGradient == nullptr)
    return SEScalar::dNaN();
  return m_AlveolarArterialGradient->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasCarricoIndex() const
{
  return m_CarricoIndex == nullptr ? false : m_CarricoIndex->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetCarricoIndex()
{
  if (m_CarricoIndex == nullptr)
    m_CarricoIndex = new SEScalarPressure();
  return *m_CarricoIndex;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetCarricoIndex(const PressureUnit& unit) const
{
  if (m_CarricoIndex == nullptr)
    return SEScalar::dNaN();
  return m_CarricoIndex->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasEndTidalCarbonDioxideFraction() const
{
  return m_EndTidalCarbonDioxideFraction == nullptr ? false : m_EndTidalCarbonDioxideFraction->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFraction& SERespiratorySystem::GetEndTidalCarbonDioxideFraction()
{
  if (m_EndTidalCarbonDioxideFraction == nullptr)
    m_EndTidalCarbonDioxideFraction = new SEScalarFraction();
  return *m_EndTidalCarbonDioxideFraction;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetEndTidalCarbonDioxideFraction() const
{
  if (m_EndTidalCarbonDioxideFraction == nullptr)
    return SEScalar::dNaN();
  return m_EndTidalCarbonDioxideFraction->GetValue();
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasEndTidalCarbonDioxidePressure() const
{
  return m_EndTidalCarbonDioxidePressure == nullptr ? false : m_EndTidalCarbonDioxidePressure->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetEndTidalCarbonDioxidePressure()
{
  if (m_EndTidalCarbonDioxidePressure == nullptr)
    m_EndTidalCarbonDioxidePressure = new SEScalarPressure();
  return *m_EndTidalCarbonDioxidePressure;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetEndTidalCarbonDioxidePressure(const PressureUnit& unit) const
{
  if (m_EndTidalCarbonDioxidePressure == nullptr)
    return SEScalar::dNaN();
  return m_EndTidalCarbonDioxidePressure->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasExpiratoryFlow() const
{
  return m_ExpiratoryFlow == nullptr ? false : m_ExpiratoryFlow->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetExpiratoryFlow()
{
  if (m_ExpiratoryFlow == nullptr)
    m_ExpiratoryFlow = new SEScalarVolumePerTime();
  return *m_ExpiratoryFlow;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetExpiratoryFlow(const VolumePerTimeUnit& unit) const
{
  if (m_ExpiratoryFlow == nullptr)
    return SEScalar::dNaN();
  return m_ExpiratoryFlow->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasInspiratoryExpiratoryRatio() const
{
  return m_InspiratoryExpiratoryRatio == nullptr ? false : m_InspiratoryExpiratoryRatio->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SERespiratorySystem::GetInspiratoryExpiratoryRatio()
{
  if (m_InspiratoryExpiratoryRatio == nullptr)
    m_InspiratoryExpiratoryRatio = new SEScalar();
  return *m_InspiratoryExpiratoryRatio;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetInspiratoryExpiratoryRatio() const
{
  if (m_InspiratoryExpiratoryRatio == nullptr)
    return SEScalar::dNaN();
  return m_InspiratoryExpiratoryRatio->GetValue();
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasInspiratoryFlow() const
{
  return m_InspiratoryFlow == nullptr ? false : m_InspiratoryFlow->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetInspiratoryFlow()
{
  if (m_InspiratoryFlow == nullptr)
    m_InspiratoryFlow = new SEScalarVolumePerTime();
  return *m_InspiratoryFlow;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetInspiratoryFlow(const VolumePerTimeUnit& unit) const
{
  if (m_InspiratoryFlow == nullptr)
    return SEScalar::dNaN();
  return m_InspiratoryFlow->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasPulmonaryCompliance() const
{
  return m_PulmonaryCompliance == nullptr ? false : m_PulmonaryCompliance->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFlowCompliance& SERespiratorySystem::GetPulmonaryCompliance()
{
  if (m_PulmonaryCompliance == nullptr)
    m_PulmonaryCompliance = new SEScalarFlowCompliance();
  return *m_PulmonaryCompliance;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetPulmonaryCompliance(const FlowComplianceUnit& unit) const
{
  if (m_PulmonaryCompliance == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryCompliance->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasPulmonaryResistance() const
{
  return m_PulmonaryResistance == nullptr ? false : m_PulmonaryResistance->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFlowResistance& SERespiratorySystem::GetPulmonaryResistance()
{
  if (m_PulmonaryResistance == nullptr)
    m_PulmonaryResistance = new SEScalarFlowResistance();
  return *m_PulmonaryResistance;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetPulmonaryResistance(const FlowResistanceUnit& unit) const
{
  if (m_PulmonaryResistance == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryResistance->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasRespirationDriverPressure() const
{
  return m_RespirationDriverPressure == nullptr ? false : m_RespirationDriverPressure->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetRespirationDriverPressure()
{
  if (m_RespirationDriverPressure == nullptr)
    m_RespirationDriverPressure = new SEScalarPressure();
  return *m_RespirationDriverPressure;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetRespirationDriverPressure(const PressureUnit& unit) const
{
  if (m_RespirationDriverPressure == nullptr)
    return SEScalar::dNaN();
  return m_RespirationDriverPressure->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasRespirationMusclePressure() const
{
  return m_RespirationMusclePressure == nullptr ? false : m_RespirationMusclePressure->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetRespirationMusclePressure()
{
  if (m_RespirationMusclePressure == nullptr)
    m_RespirationMusclePressure = new SEScalarPressure();
  return *m_RespirationMusclePressure;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetRespirationMusclePressure(const PressureUnit& unit) const
{
  if (m_RespirationMusclePressure == nullptr)
    return SEScalar::dNaN();
  return m_RespirationMusclePressure->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasRespirationRate() const
{
  return m_RespirationRate == nullptr ? false : m_RespirationRate->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFrequency& SERespiratorySystem::GetRespirationRate()
{
  if (m_RespirationRate == nullptr)
    m_RespirationRate = new SEScalarFrequency();
  return *m_RespirationRate;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetRespirationRate(const FrequencyUnit& unit) const
{
  if (m_RespirationRate == nullptr)
    return SEScalar::dNaN();
  return m_RespirationRate->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasSpecificVentilation() const
{
  return m_SpecificVentilation == nullptr ? false : m_SpecificVentilation->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SERespiratorySystem::GetSpecificVentilation()
{
  if (m_SpecificVentilation == nullptr)
    m_SpecificVentilation = new SEScalar();
  return *m_SpecificVentilation;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetSpecificVentilation() const
{
  if (m_SpecificVentilation == nullptr)
    return SEScalar::dNaN();
  return m_SpecificVentilation->GetValue();
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasTargetPulmonaryVentilation() const
{
  return m_TargetPulmonaryVentilation == nullptr ? false : m_TargetPulmonaryVentilation->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetTargetPulmonaryVentilation()
{
  if (m_TargetPulmonaryVentilation == nullptr)
    m_TargetPulmonaryVentilation = new SEScalarVolumePerTime();
  return *m_TargetPulmonaryVentilation;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTargetPulmonaryVentilation(const VolumePerTimeUnit& unit) const
{
  if (m_TargetPulmonaryVentilation == nullptr)
    return SEScalar::dNaN();
  return m_TargetPulmonaryVentilation->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasTidalVolume() const
{
  return m_TidalVolume == nullptr ? false : m_TidalVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SERespiratorySystem::GetTidalVolume()
{
  if (m_TidalVolume == nullptr)
    m_TidalVolume = new SEScalarVolume();
  return *m_TidalVolume;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTidalVolume(const VolumeUnit& unit) const
{
  if (m_TidalVolume == nullptr)
    return SEScalar::dNaN();
  return m_TidalVolume->GetValue(unit);
}

bool SERespiratorySystem::HasTotalAlveolarVentilation() const
{
  return m_TotalAlveolarVentilation == nullptr ? false : m_TotalAlveolarVentilation->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetTotalAlveolarVentilation()
{
  if (m_TotalAlveolarVentilation == nullptr)
    m_TotalAlveolarVentilation = new SEScalarVolumePerTime();
  return *m_TotalAlveolarVentilation;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTotalAlveolarVentilation(const VolumePerTimeUnit& unit) const
{
  if (m_TotalAlveolarVentilation == nullptr)
    return SEScalar::dNaN();
  return m_TotalAlveolarVentilation->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasTotalDeadSpaceVentilation() const
{
  return m_TotalDeadSpaceVentilation == nullptr ? false : m_TotalDeadSpaceVentilation->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetTotalDeadSpaceVentilation()
{
  if (m_TotalDeadSpaceVentilation == nullptr)
    m_TotalDeadSpaceVentilation = new SEScalarVolumePerTime();
  return *m_TotalDeadSpaceVentilation;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTotalDeadSpaceVentilation(const VolumePerTimeUnit& unit) const
{
  if (m_TotalDeadSpaceVentilation == nullptr)
    return SEScalar::dNaN();
  return m_TotalDeadSpaceVentilation->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasTotalLungVolume() const
{
  return m_TotalLungVolume == nullptr ? false : m_TotalLungVolume->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SERespiratorySystem::GetTotalLungVolume()
{
  if (m_TotalLungVolume == nullptr)
    m_TotalLungVolume = new SEScalarVolume();
  return *m_TotalLungVolume;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTotalLungVolume(const VolumeUnit& unit) const
{
  if (m_TotalLungVolume == nullptr)
    return SEScalar::dNaN();
  return m_TotalLungVolume->GetValue(unit);
}

bool SERespiratorySystem::HasTotalPulmonaryVentilation() const
{
  return m_TotalPulmonaryVentilation == nullptr ? false : m_TotalPulmonaryVentilation->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolumePerTime& SERespiratorySystem::GetTotalPulmonaryVentilation()
{
  if (m_TotalPulmonaryVentilation == nullptr)
    m_TotalPulmonaryVentilation = new SEScalarVolumePerTime();
  return *m_TotalPulmonaryVentilation;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTotalPulmonaryVentilation(const VolumePerTimeUnit& unit) const
{
  if (m_TotalPulmonaryVentilation == nullptr)
    return SEScalar::dNaN();
  return m_TotalPulmonaryVentilation->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SERespiratorySystem::HasTranspulmonaryPressure() const
{
  return m_TranspulmonaryPressure == nullptr ? false : m_TranspulmonaryPressure->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SERespiratorySystem::GetTranspulmonaryPressure()
{
  if (m_TranspulmonaryPressure == nullptr)
    m_TranspulmonaryPressure = new SEScalarPressure();
  return *m_TranspulmonaryPressure;
}
//-------------------------------------------------------------------------------
double SERespiratorySystem::GetTranspulmonaryPressure(const PressureUnit& unit) const
{
  if (m_TranspulmonaryPressure == nullptr)
    return SEScalar::dNaN();
  return m_TranspulmonaryPressure->GetValue(unit);
}
//-------------------------------------------------------------------------------
Tree<const char*> SERespiratorySystem::GetPhysiologyRequestGraph() const
{
  return Tree<const char*>{classname()}
    .emplace_back(idAlveolarArterialGradient)
    .emplace_back(idCarricoIndex)
    .emplace_back(idEndTidalCarbonDioxideFraction)
    .emplace_back(idEndTidalCarbonDioxidePressure)
    .emplace_back(idExpiratoryFlow)
    .emplace_back(idInspiratoryExpiratoryRatio)
    .emplace_back(idInspiratoryFlow)
    .emplace_back(idPulmonaryCompliance)
    .emplace_back(idPulmonaryResistance)
    .emplace_back(idRespirationDriverPressure)
    .emplace_back(idRespirationMusclePressure)
    .emplace_back(idRespirationRate)
    .emplace_back(idSpecificVentilation)
    .emplace_back(idTargetPulmonaryVentilation)
    .emplace_back(idTidalVolume)
    .emplace_back(idTotalAlveolarVentilation)
    .emplace_back(idTotalDeadSpaceVentilation)
    .emplace_back(idTotalLungVolume)
    .emplace_back(idTotalPulmonaryVentilation)
    .emplace_back(idTranspulmonaryPressure)
  ;
}
}