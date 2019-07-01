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

#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/substance/SESubstancePharmacodynamics.h>
#include <biogears/schema/cdm/Properties.hxx>
#include <biogears/schema/cdm/Substance.hxx>

#include "../utils/io/Property.h"
namespace biogears {
SESubstancePharmacodynamics::SESubstancePharmacodynamics(Logger* logger)
  : Loggable(logger)
{
  m_Bronchodilation = nullptr;
  m_DiastolicPressureModifier = nullptr;
  m_EC50 = nullptr;
  m_EMaxShapeParameter = nullptr;
  m_HeartRateModifier = nullptr;
  m_NeuromuscularBlock = nullptr;
  m_PupillaryResponse = nullptr;
  m_RespirationRateModifier = nullptr;
  m_Sedation = nullptr;
  m_SystolicPressureModifier = nullptr;
  m_TidalVolumeModifier = nullptr;
  m_TubularPermeabilityModifier = nullptr;
  m_CentralNervousModifier = nullptr;
  m_EffectSiteRateConstant = nullptr;
}
//-----------------------------------------------------------------------------
SESubstancePharmacodynamics::~SESubstancePharmacodynamics()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SESubstancePharmacodynamics::Clear()
{
  SAFE_DELETE(m_Bronchodilation);
  SAFE_DELETE(m_DiastolicPressureModifier);
  SAFE_DELETE(m_EC50);
  SAFE_DELETE(m_EMaxShapeParameter);
  SAFE_DELETE(m_HeartRateModifier);
  SAFE_DELETE(m_NeuromuscularBlock);
  SAFE_DELETE(m_PupillaryResponse);
  SAFE_DELETE(m_RespirationRateModifier);
  SAFE_DELETE(m_Sedation);
  SAFE_DELETE(m_SystolicPressureModifier);
  SAFE_DELETE(m_TidalVolumeModifier);
  SAFE_DELETE(m_TubularPermeabilityModifier);
  SAFE_DELETE(m_CentralNervousModifier);
  SAFE_DELETE(m_EffectSiteRateConstant);
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::IsValid() const
{
  if (!HasBronchodilation())
    return false;
  if (!HasDiastolicPressureModifier())
    return false;
  if (!HasEC50())
    return false;
  if (!HasEMaxShapeParameter())
    return false;
  if (!HasHeartRateModifier())
    return false;
  if (!HasNeuromuscularBlock())
    return false;
  if (!HasPupillaryResponse())
    return false;
  if (!HasRespirationRateModifier())
    return false;
  if (!HasSedation())
    return false;
  if (!HasSystolicPressureModifier())
    return false;
  if (!HasTidalVolumeModifier())
    return false;
  if (!HasTubularPermeabilityModifier())
    return false;
  if (!HasCentralNervousModifier())
    return false;
  if (!HasEffectSiteRateConstant())
    return false;
  return true;
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePharmacodynamics::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePharmacodynamics::GetScalar(const std::string& name)
{
  if (name == "Bronchodilation")
    return &GetBronchodilation();
  if (name == "DiastolicPressureModifier")
    return &GetDiastolicPressureModifier();
  if (name == "EC50")
    return &GetEC50();
  if (name == "EMaxShapeParameter")
    return &GetEMaxShapeParameter();
  if (name == "HeartRateModifier")
    return &GetHeartRateModifier();
  if (name == "NeuromuscularBlock")
    return &GetNeuromuscularBlock();
  if (name == "RespirationRateModifier")
    return &GetRespirationRateModifier();
  if (name == "Sedation")
    return &GetSedation();
  if (name == "SystolicPressureModifier")
    return &GetSystolicPressureModifier();
  if (name == "TidalVolumeModifier")
    return &GetTidalVolumeModifier();
  if (name == "TubularPermeabilityModifier")
    return &GetTubularPermeabilityModifier();
  if (name == "CentralNervousModifier")
    return &GetCentralNervousModifier();
  if (name == "EffectSiteRateConstant")
    return &GetEffectSiteRateConstant();

  return GetPupillaryResponse().GetScalar(name);
}
//-----------------------------------------------------------------------------
void SESubstancePharmacodynamics::CalculateDerived()
{
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasBronchodilation() const
{
  return (m_Bronchodilation == nullptr) ? false : m_Bronchodilation->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetBronchodilation()
{
  if (m_Bronchodilation == nullptr) {
    m_Bronchodilation = new SEScalarFraction();
  }

  return *m_Bronchodilation;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetBronchodilation() const
{
  if (m_Bronchodilation == nullptr) {
    return SEScalar::dNaN();
  }

  return m_Bronchodilation->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasDiastolicPressureModifier() const
{
  return (m_DiastolicPressureModifier == nullptr) ? false : m_DiastolicPressureModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetDiastolicPressureModifier()
{
  if (m_DiastolicPressureModifier == nullptr) {
    m_DiastolicPressureModifier = new SEScalarFraction();
  }

  return *m_DiastolicPressureModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetDiastolicPressureModifier() const
{
  if (m_DiastolicPressureModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_DiastolicPressureModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasEC50() const
{
  return (m_EC50 == nullptr) ? false : m_EC50->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarMassPerVolume& SESubstancePharmacodynamics::GetEC50()
{
  if (m_EC50 == nullptr) {
    m_EC50 = new SEScalarMassPerVolume();
  }

  return *m_EC50;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetEC50(const MassPerVolumeUnit& unit) const
{
  if (m_EC50 == nullptr) {
    return SEScalar::dNaN();
  }

  return m_EC50->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasEMaxShapeParameter() const
{
  return (m_EMaxShapeParameter == nullptr) ? false : m_EMaxShapeParameter->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstancePharmacodynamics::GetEMaxShapeParameter()
{
  if (m_EMaxShapeParameter == nullptr) {
    m_EMaxShapeParameter = new SEScalar();
  }

  return *m_EMaxShapeParameter;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetEMaxShapeParameter() const
{
  if (m_EMaxShapeParameter == nullptr) {
    return SEScalar::dNaN();
  }

  return m_EMaxShapeParameter->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasHeartRateModifier() const
{
  return (m_HeartRateModifier == nullptr) ? false : m_HeartRateModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetHeartRateModifier()
{
  if (m_HeartRateModifier == nullptr) {
    m_HeartRateModifier = new SEScalarFraction();
  }

  return *m_HeartRateModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetHeartRateModifier() const
{
  if (m_HeartRateModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_HeartRateModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasNeuromuscularBlock() const
{
  return (m_NeuromuscularBlock == nullptr) ? false : m_NeuromuscularBlock->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetNeuromuscularBlock()
{
  if (m_NeuromuscularBlock == nullptr) {
    m_NeuromuscularBlock = new SEScalarFraction();
  }

  return *m_NeuromuscularBlock;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetNeuromuscularBlock() const
{
  if (m_NeuromuscularBlock == nullptr) {
    return SEScalar::dNaN();
  }

  return m_NeuromuscularBlock->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasPupillaryResponse() const
{
  return (m_PupillaryResponse != nullptr);
}
//-----------------------------------------------------------------------------
SEPupillaryResponse& SESubstancePharmacodynamics::GetPupillaryResponse()
{
  if (m_PupillaryResponse == nullptr) {
    m_PupillaryResponse = new SEPupillaryResponse(GetLogger());
  }

  return *m_PupillaryResponse;
}
//-----------------------------------------------------------------------------
const SEPupillaryResponse* SESubstancePharmacodynamics::GetPupillaryResponse() const
{
  return m_PupillaryResponse;
}
//-----------------------------------------------------------------------------
void SESubstancePharmacodynamics::RemovePupillaryResponse()
{
  SAFE_DELETE(m_PupillaryResponse);
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasRespirationRateModifier() const
{
  return (m_RespirationRateModifier == nullptr) ? false : m_RespirationRateModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetRespirationRateModifier()
{
  if (m_RespirationRateModifier == nullptr) {
    m_RespirationRateModifier = new SEScalarFraction();
  }

  return *m_RespirationRateModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetRespirationRateModifier() const
{
  if (m_RespirationRateModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_RespirationRateModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasSedation() const
{
  return (m_Sedation == nullptr) ? false : m_Sedation->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetSedation()
{
  if (m_Sedation == nullptr) {
    m_Sedation = new SEScalarFraction();
  }

  return *m_Sedation;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetSedation() const
{
  if (m_Sedation == nullptr)
    return SEScalar::dNaN();
  return m_Sedation->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasSystolicPressureModifier() const
{
  return (m_SystolicPressureModifier == nullptr) ? false : m_SystolicPressureModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetSystolicPressureModifier()
{
  if (m_SystolicPressureModifier == nullptr) {
    m_SystolicPressureModifier = new SEScalarFraction();
  }

  return *m_SystolicPressureModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetSystolicPressureModifier() const
{
  if (m_SystolicPressureModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_SystolicPressureModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasTidalVolumeModifier() const
{
  return (m_TidalVolumeModifier == nullptr) ? false : m_TidalVolumeModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetTidalVolumeModifier()
{
  if (m_TidalVolumeModifier == nullptr) {
    m_TidalVolumeModifier = new SEScalarFraction();
  }

  return *m_TidalVolumeModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetTidalVolumeModifier() const
{
  if (m_TidalVolumeModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_TidalVolumeModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasTubularPermeabilityModifier() const
{
  return (m_TubularPermeabilityModifier == nullptr) ? false : m_TubularPermeabilityModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetTubularPermeabilityModifier()
{
  if (m_TubularPermeabilityModifier == nullptr)
    m_TubularPermeabilityModifier = new SEScalarFraction();
  return *m_TubularPermeabilityModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetTubularPermeabilityModifier() const
{
  if (m_TubularPermeabilityModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_TubularPermeabilityModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasCentralNervousModifier() const
{
  return (m_CentralNervousModifier == nullptr) ? false : m_CentralNervousModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePharmacodynamics::GetCentralNervousModifier()
{
  if (m_CentralNervousModifier == nullptr) {
    m_CentralNervousModifier = new SEScalarFraction();
  }

  return *m_CentralNervousModifier;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetCentralNervousModifier() const
{
  if (m_CentralNervousModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_CentralNervousModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacodynamics::HasEffectSiteRateConstant() const
{
  return (m_EffectSiteRateConstant == nullptr) ? false : m_EffectSiteRateConstant->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFrequency& SESubstancePharmacodynamics::GetEffectSiteRateConstant()
{
  if (m_EffectSiteRateConstant == nullptr) {
    m_EffectSiteRateConstant = new SEScalarFrequency();
  }

  return *m_EffectSiteRateConstant;
}
//-----------------------------------------------------------------------------
double SESubstancePharmacodynamics::GetEffectSiteRateConstant(const FrequencyUnit& unit) const
{
  if (m_EffectSiteRateConstant == nullptr)
    return SEScalar::dNaN();
  return m_EffectSiteRateConstant->GetValue(unit);
}
//-----------------------------------------------------------------------------
}