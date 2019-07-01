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
#include <biogears/cdm/substance/SESubstancePhysicochemicals.h>

namespace biogears {
SESubstancePhysicochemicals::SESubstancePhysicochemicals(Logger* logger)
  : Loggable(logger)
{
  m_AcidDissociationConstant = nullptr;
  m_BindingProtein = SESubstanceBindingProtein::Invalid;
  m_BloodPlasmaRatio = nullptr;
  m_FractionUnboundInPlasma = nullptr;
  m_IonicState = SESubstanceIonicState::Invalid;
  m_LogP = nullptr;
  m_OralAbsorptionRateConstant = nullptr;
}
//-----------------------------------------------------------------------------
SESubstancePhysicochemicals::~SESubstancePhysicochemicals()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SESubstancePhysicochemicals::Clear()
{
  SAFE_DELETE(m_AcidDissociationConstant);
  m_BindingProtein = SESubstanceBindingProtein::Invalid;
  SAFE_DELETE(m_BloodPlasmaRatio);
  SAFE_DELETE(m_FractionUnboundInPlasma);
  m_IonicState = SESubstanceIonicState::Invalid;
  SAFE_DELETE(m_LogP);
  SAFE_DELETE(m_OralAbsorptionRateConstant);
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::IsValid() const
{
  return HasAcidDissociationConstant()
    && HasBindingProtein()
    && HasBloodPlasmaRatio()
    && HasFractionUnboundInPlasma()
    && HasIonicState()
    && HasLogP();
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePhysicochemicals::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePhysicochemicals::GetScalar(const std::string& name)
{
  if (name == "AcidDissociationConstant") {
    return &GetAcidDissociationConstant();
  }
  if (name == "BloodPlasmaRatio") {
    return &GetBloodPlasmaRatio();
  }
  if (name == "FractionUnboundInPlasma") {
    return &GetFractionUnboundInPlasma();
  }
  if (name == "LogP") {
    return &GetLogP();
  }
  if (name == "OralAbsorptionRateConstant") {
    return &GetOralAbsorptionRateConstant();
  }

  return nullptr;
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasAcidDissociationConstant() const
{
  return (m_AcidDissociationConstant == nullptr) ? false : m_AcidDissociationConstant->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstancePhysicochemicals::GetAcidDissociationConstant()
{
  if (m_AcidDissociationConstant == nullptr) {
    m_AcidDissociationConstant = new SEScalar();
  }
  return *m_AcidDissociationConstant;
}
//-----------------------------------------------------------------------------
double SESubstancePhysicochemicals::GetAcidDissociationConstant() const
{
  if (m_AcidDissociationConstant == nullptr) {
    return SEScalar::dNaN();
  }
  return m_AcidDissociationConstant->GetValue();
}
//-----------------------------------------------------------------------------
SESubstanceBindingProtein SESubstancePhysicochemicals::GetBindingProtein() const
{
  return m_BindingProtein;
}
//-----------------------------------------------------------------------------
void SESubstancePhysicochemicals::SetBindingProtein(SESubstanceBindingProtein protein)
{
  m_BindingProtein = protein;
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasBindingProtein() const
{
  return m_BindingProtein != (SESubstanceBindingProtein::Invalid);
}
//-----------------------------------------------------------------------------
void SESubstancePhysicochemicals::InvalidateBindingProtein()
{
  m_BindingProtein = SESubstanceBindingProtein::Invalid;
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasBloodPlasmaRatio() const
{
  return (m_BloodPlasmaRatio == nullptr) ? false : m_BloodPlasmaRatio->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstancePhysicochemicals::GetBloodPlasmaRatio()
{
  if (m_BloodPlasmaRatio == nullptr) {
    m_BloodPlasmaRatio = new SEScalar();
  }
  return *m_BloodPlasmaRatio;
}
//-----------------------------------------------------------------------------
double SESubstancePhysicochemicals::GetBloodPlasmaRatio() const
{
  if (m_BloodPlasmaRatio == nullptr) {
    return SEScalar::dNaN();
  }
  return m_BloodPlasmaRatio->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasFractionUnboundInPlasma() const
{
  return (m_FractionUnboundInPlasma == nullptr) ? false : m_FractionUnboundInPlasma->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstancePhysicochemicals::GetFractionUnboundInPlasma()
{
  if (m_FractionUnboundInPlasma == nullptr) {
    m_FractionUnboundInPlasma = new SEScalarFraction();
  }
  return *m_FractionUnboundInPlasma;
}
//-----------------------------------------------------------------------------
double SESubstancePhysicochemicals::GetFractionUnboundInPlasma() const
{
  if (m_FractionUnboundInPlasma == nullptr) {
    return SEScalar::dNaN();
  }
  return m_FractionUnboundInPlasma->GetValue();
}
//-----------------------------------------------------------------------------
SESubstanceIonicState SESubstancePhysicochemicals::GetIonicState() const
{
  return m_IonicState;
}
//-----------------------------------------------------------------------------
void SESubstancePhysicochemicals::SetIonicState(SESubstanceIonicState state)
{
  m_IonicState = state;
}
bool SESubstancePhysicochemicals::HasIonicState() const
{
  return m_IonicState != (SESubstanceIonicState::Invalid);
}
//-----------------------------------------------------------------------------
void SESubstancePhysicochemicals::InvalidateIonicState()
{
  m_IonicState = SESubstanceIonicState::Invalid;
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasLogP() const
{
  return (m_LogP == nullptr) ? false : m_LogP->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstancePhysicochemicals::GetLogP()
{
  if (m_LogP == nullptr) {
    m_LogP = new SEScalar();
  }
  return *m_LogP;
}
//-----------------------------------------------------------------------------
double SESubstancePhysicochemicals::GetLogP() const
{
  if (m_LogP == nullptr) {
    return SEScalar::dNaN();
  }
  return m_LogP->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstancePhysicochemicals::HasOralAbsorptionRateConstant() const
{
  return (m_OralAbsorptionRateConstant == nullptr) ? false : m_OralAbsorptionRateConstant->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstancePhysicochemicals::GetOralAbsorptionRateConstant()
//-----------------------------------------------------------------------------
{
  if (m_OralAbsorptionRateConstant == nullptr) {
    m_OralAbsorptionRateConstant = new SEScalar();
  }
  return *m_OralAbsorptionRateConstant;
}
double SESubstancePhysicochemicals::GetOralAbsorptionRateConstant() const
{
  if (m_OralAbsorptionRateConstant == nullptr) {
    return SEScalar::dNaN();
  }
  return m_OralAbsorptionRateConstant->GetValue();
}
//-----------------------------------------------------------------------------
}