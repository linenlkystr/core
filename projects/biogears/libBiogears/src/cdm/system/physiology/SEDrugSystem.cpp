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
#include <biogears/cdm/system/physiology/SEDrugSystem.h>

#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarLength.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/container/Tree.tci.h>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {

constexpr char idBronchodilationLevel[] = "BronchodilationLevel";
constexpr char idHeartRateChange[] = "HeartRateChange";
constexpr char idMeanBloodPressureChange[] = "MeanBloodPressureChange";
constexpr char idNeuromuscularBlockLevel[] = "NeuromuscularBlockLevel";
constexpr char idPulsePressureChange[] = "PulsePressureChange";
constexpr char idRespirationRateChange[] = "RespirationRateChange";
constexpr char idSedationLevel[] = "SedationLevel";
constexpr char idTidalVolumeChange[] = "TidalVolumeChange";
constexpr char idTubularPermeabilityChange[] = "TubularPermeabilityChange";
constexpr char idCentralNervousResponse[] = "CentralNervousResponse";
constexpr char idPupillaryResponse[] = "PupillaryResponse";

SEDrugSystem::SEDrugSystem(Logger* logger)
  : SESystem(logger)
{
  m_BronchodilationLevel = nullptr;
  m_HeartRateChange = nullptr;
  m_MeanBloodPressureChange = nullptr;
  m_NeuromuscularBlockLevel = nullptr;
  m_PulsePressureChange = nullptr;
  m_PupillaryResponse = nullptr;
  m_RespirationRateChange = nullptr;
  m_SedationLevel = nullptr;
  m_TidalVolumeChange = nullptr;
  m_TubularPermeabilityChange = nullptr;
  m_CentralNervousResponse = nullptr;
}
//-------------------------------------------------------------------------------

SEDrugSystem::~SEDrugSystem()
{
  Clear();
}
//-------------------------------------------------------------------------------

void SEDrugSystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_BronchodilationLevel);
  SAFE_DELETE(m_HeartRateChange);
  SAFE_DELETE(m_MeanBloodPressureChange);
  SAFE_DELETE(m_NeuromuscularBlockLevel);
  SAFE_DELETE(m_PulsePressureChange);
  SAFE_DELETE(m_PupillaryResponse);
  SAFE_DELETE(m_RespirationRateChange);
  SAFE_DELETE(m_SedationLevel);
  SAFE_DELETE(m_TidalVolumeChange);
  SAFE_DELETE(m_TubularPermeabilityChange);
  SAFE_DELETE(m_CentralNervousResponse);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::Load(const CDM::DrugSystemData& in)
{
  SESystem::Load(in);

  if (in.BronchodilationLevel().present())
    io::PropertyIoDelegate::Marshall(in.BronchodilationLevel(), GetBronchodilationLevel());
  if (in.HeartRateChange().present())
    io::PropertyIoDelegate::Marshall(in.HeartRateChange(), GetHeartRateChange());
  if (in.MeanBloodPressureChange().present())
    io::PropertyIoDelegate::Marshall(in.MeanBloodPressureChange(), GetMeanBloodPressureChange());
  if (in.NeuromuscularBlockLevel().present())
    io::PropertyIoDelegate::Marshall(in.NeuromuscularBlockLevel(), GetNeuromuscularBlockLevel());
  if (in.PulsePressureChange().present())
    io::PropertyIoDelegate::Marshall(in.PulsePressureChange(), GetPulsePressureChange());
  if (in.PupillaryResponse().present())
    GetPupillaryResponse().Load(in.PupillaryResponse().get());
  if (in.RespirationRateChange().present())
    io::PropertyIoDelegate::Marshall(in.RespirationRateChange(), GetRespirationRateChange());
  if (in.SedationLevel().present())
    io::PropertyIoDelegate::Marshall(in.SedationLevel(), GetSedationLevel());
  if (in.TidalVolumeChange().present())
    io::PropertyIoDelegate::Marshall(in.TidalVolumeChange(), GetTidalVolumeChange());
  if (in.TubularPermeabilityChange().present())
    io::PropertyIoDelegate::Marshall(in.TubularPermeabilityChange(), GetTubularPermeabilityChange());
  if (in.CentralNervousResponse().present())
    io::PropertyIoDelegate::Marshall(in.CentralNervousResponse(), GetCentralNervousResponse());

  return true;
}
//-------------------------------------------------------------------------------
const SEScalar* SEDrugSystem::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-------------------------------------------------------------------------------
const SEScalar* SEDrugSystem::GetScalar(const std::string& name)
{
  if (name == idBronchodilationLevel)
    return &GetBronchodilationLevel();
  if (name == idHeartRateChange)
    return &GetHeartRateChange();
  if (name == idMeanBloodPressureChange)
    return &GetMeanBloodPressureChange();
  if (name == idNeuromuscularBlockLevel)
    return &GetNeuromuscularBlockLevel();
  if (name == idPulsePressureChange)
    return &GetPulsePressureChange();
  if (name == idRespirationRateChange)
    return &GetRespirationRateChange();
  if (name == idSedationLevel)
    return &GetSedationLevel();
  if (name == idTidalVolumeChange)
    return &GetTidalVolumeChange();
  if (name == idTubularPermeabilityChange)
    return &GetTubularPermeabilityChange();
  if (name == idCentralNervousResponse)
    return &GetCentralNervousResponse();

  size_t split = name.find('-');
  if (split != name.npos) {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == idPupillaryResponse)
      return GetPupillaryResponse().GetScalar(prop);
  }

  return nullptr;
}
//-------------------------------------------------------------------------------

CDM::DrugSystemData* SEDrugSystem::Unload() const
{
  CDM::DrugSystemData* data = new CDM::DrugSystemData();
  Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------

void SEDrugSystem::Unload(CDM::DrugSystemData& data) const
{
  SESystem::Unload(data);

  if (m_BronchodilationLevel != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_BronchodilationLevel, data.BronchodilationLevel());
  if (m_HeartRateChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_HeartRateChange, data.HeartRateChange());
  if (m_MeanBloodPressureChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_MeanBloodPressureChange, data.MeanBloodPressureChange());
  if (m_NeuromuscularBlockLevel != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_NeuromuscularBlockLevel, data.NeuromuscularBlockLevel());
  if (m_PulsePressureChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_PulsePressureChange, data.PulsePressureChange());
  if (m_PupillaryResponse != nullptr)
    data.PupillaryResponse(std::unique_ptr<CDM::PupillaryResponseData>(m_PupillaryResponse->Unload()));
  if (m_RespirationRateChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_RespirationRateChange, data.RespirationRateChange());
  if (m_SedationLevel != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_SedationLevel, data.SedationLevel());
  if (m_TidalVolumeChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_TidalVolumeChange, data.TidalVolumeChange());
  if (m_TubularPermeabilityChange != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_TubularPermeabilityChange, data.TubularPermeabilityChange());
  if (m_CentralNervousResponse != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_CentralNervousResponse, data.CentralNervousResponse());
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasBronchodilationLevel() const
{
  return m_BronchodilationLevel == nullptr ? false : m_BronchodilationLevel->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFraction& SEDrugSystem::GetBronchodilationLevel()
{
  if (m_BronchodilationLevel == nullptr)
    m_BronchodilationLevel = new SEScalarFraction();
  return *m_BronchodilationLevel;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetBronchodilationLevel() const
{
  if (m_BronchodilationLevel == nullptr)
    return SEScalar::dNaN();
  return m_BronchodilationLevel->GetValue();
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasHeartRateChange() const
{
  return m_HeartRateChange == nullptr ? false : m_HeartRateChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFrequency& SEDrugSystem::GetHeartRateChange()
{
  if (m_HeartRateChange == nullptr)
    m_HeartRateChange = new SEScalarFrequency();
  return *m_HeartRateChange;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetHeartRateChange(const FrequencyUnit& unit) const
{
  if (m_HeartRateChange == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateChange->GetValue(unit);
}

bool SEDrugSystem::HasMeanBloodPressureChange() const
{
  return m_MeanBloodPressureChange == nullptr ? false : m_MeanBloodPressureChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SEDrugSystem::GetMeanBloodPressureChange()
{
  if (m_MeanBloodPressureChange == nullptr)
    m_MeanBloodPressureChange = new SEScalarPressure();
  return *m_MeanBloodPressureChange;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetMeanBloodPressureChange(const PressureUnit& unit) const
{
  if (m_MeanBloodPressureChange == nullptr)
    return SEScalar::dNaN();
  return m_MeanBloodPressureChange->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasNeuromuscularBlockLevel() const
{
  return m_NeuromuscularBlockLevel == nullptr ? false : m_NeuromuscularBlockLevel->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFraction& SEDrugSystem::GetNeuromuscularBlockLevel()
{
  if (m_NeuromuscularBlockLevel == nullptr)
    m_NeuromuscularBlockLevel = new SEScalarFraction();
  return *m_NeuromuscularBlockLevel;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetNeuromuscularBlockLevel() const
{
  if (m_NeuromuscularBlockLevel == nullptr)
    return SEScalar::dNaN();
  return m_NeuromuscularBlockLevel->GetValue();
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasPulsePressureChange() const
{
  return m_PulsePressureChange == nullptr ? false : m_PulsePressureChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarPressure& SEDrugSystem::GetPulsePressureChange()
{
  if (m_PulsePressureChange == nullptr)
    m_PulsePressureChange = new SEScalarPressure();
  return *m_PulsePressureChange;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetPulsePressureChange(const PressureUnit& unit) const
{
  if (m_PulsePressureChange == nullptr)
    return SEScalar::dNaN();
  return m_PulsePressureChange->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasPupillaryResponse() const
{
  return (m_PupillaryResponse != nullptr);
}
//-------------------------------------------------------------------------------
SEPupillaryResponse& SEDrugSystem::GetPupillaryResponse()
{
  if (m_PupillaryResponse == nullptr)
    m_PupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_PupillaryResponse;
}
//-------------------------------------------------------------------------------
const SEPupillaryResponse* SEDrugSystem::GetPupillaryResponse() const
{
  return m_PupillaryResponse;
}
//-------------------------------------------------------------------------------
void SEDrugSystem::RemovePupillaryResponse()
{
  SAFE_DELETE(m_PupillaryResponse);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasRespirationRateChange() const
{
  return m_RespirationRateChange == nullptr ? false : m_RespirationRateChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFrequency& SEDrugSystem::GetRespirationRateChange()
{
  if (m_RespirationRateChange == nullptr)
    m_RespirationRateChange = new SEScalarFrequency();
  return *m_RespirationRateChange;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetRespirationRateChange(const FrequencyUnit& unit) const
{
  if (m_RespirationRateChange == nullptr)
    return SEScalar::dNaN();
  return m_RespirationRateChange->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasSedationLevel() const
{
  return m_SedationLevel == nullptr ? false : m_SedationLevel->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFraction& SEDrugSystem::GetSedationLevel()
{
  if (m_SedationLevel == nullptr)
    m_SedationLevel = new SEScalarFraction();
  return *m_SedationLevel;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetSedationLevel() const
{
  if (m_SedationLevel == nullptr)
    return SEScalar::dNaN();
  return m_SedationLevel->GetValue();
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasTidalVolumeChange() const
{
  return m_TidalVolumeChange == nullptr ? false : m_TidalVolumeChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarVolume& SEDrugSystem::GetTidalVolumeChange()
{
  if (m_TidalVolumeChange == nullptr)
    m_TidalVolumeChange = new SEScalarVolume();
  return *m_TidalVolumeChange;
}

double SEDrugSystem::GetTidalVolumeChange(const VolumeUnit& unit) const
{
  if (m_TidalVolumeChange == nullptr)
    return SEScalar::dNaN();
  return m_TidalVolumeChange->GetValue(unit);
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasTubularPermeabilityChange() const
{
  return m_TubularPermeabilityChange == nullptr ? false : m_TubularPermeabilityChange->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarFraction& SEDrugSystem::GetTubularPermeabilityChange()
{
  if (m_TubularPermeabilityChange == nullptr)
    m_TubularPermeabilityChange = new SEScalarFraction();
  return *m_TubularPermeabilityChange;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetTubularPermeabilityChange() const
{
  if (m_TubularPermeabilityChange == nullptr)
    return SEScalar::dNaN();
  return m_TubularPermeabilityChange->GetValue();
}
//-------------------------------------------------------------------------------

bool SEDrugSystem::HasCentralNervousResponse() const
{
  return m_CentralNervousResponse == nullptr ? false : m_CentralNervousResponse->IsValid();
}
//-------------------------------------------------------------------------------

SEScalarFraction& SEDrugSystem::GetCentralNervousResponse()
{
  if (m_CentralNervousResponse == nullptr)
    m_CentralNervousResponse = new SEScalarFraction();
  return *m_CentralNervousResponse;
}
//-------------------------------------------------------------------------------
double SEDrugSystem::GetCentralNervousResponse() const
{
  if (m_CentralNervousResponse == nullptr)
    return SEScalar::dNaN();
  return m_CentralNervousResponse->GetValue();
}
//-------------------------------------------------------------------------------
Tree<const char*> SEDrugSystem::GetPhysiologyRequestGraph() const
{
  return Tree<const char*>{ classname() }
    .emplace_back(idBronchodilationLevel)
    .emplace_back(idHeartRateChange)
    .emplace_back(idMeanBloodPressureChange)
    .emplace_back(idNeuromuscularBlockLevel)
    .emplace_back(idPulsePressureChange)
    .emplace_back(idRespirationRateChange)
    .emplace_back(idSedationLevel)
    .emplace_back(idTidalVolumeChange)
    .emplace_back(idTubularPermeabilityChange)
    .emplace_back(idCentralNervousResponse);
}
}