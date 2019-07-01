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
#include <biogears/cdm/substance/SESubstanceClearance.h>

#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarMassPerTime.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeMass.h>

namespace biogears {
SESubstanceClearance::SESubstanceClearance(Logger* logger)
  : Loggable(logger)
{
  m_hasSystemic = false;
  m_ChargeInBlood = SECharge::Invalid;
  m_FractionExcretedInFeces = nullptr;
  m_FractionExcretedInUrine = nullptr;
  m_FractionMetabolizedInGut = nullptr;
  m_FractionUnboundInPlasma = nullptr;
  m_GlomerularFilterability = nullptr;
  m_IntrinsicClearance = nullptr;
  m_RenalDynamic = SERenalDynamic::Invalid;
  m_RenalClearance = nullptr;
  m_RenalReabsorptionRatio = nullptr;
  m_RenalTransportMaximum = nullptr;
  m_RenalFiltrationRate = nullptr;
  m_RenalReabsorptionRate = nullptr;
  m_RenalExcretionRate = nullptr;
  m_SystemicClearance = nullptr;
}
//-----------------------------------------------------------------------------
SESubstanceClearance::~SESubstanceClearance()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SESubstanceClearance::Clear()
{
  m_hasSystemic = false;
  m_ChargeInBlood = SECharge::Invalid;
  SAFE_DELETE(m_FractionExcretedInFeces);
  SAFE_DELETE(m_FractionExcretedInUrine);
  SAFE_DELETE(m_FractionMetabolizedInGut);
  SAFE_DELETE(m_FractionUnboundInPlasma);
  SAFE_DELETE(m_GlomerularFilterability);
  SAFE_DELETE(m_IntrinsicClearance);
  m_RenalDynamic = SERenalDynamic::Invalid;
  SAFE_DELETE(m_RenalClearance);
  SAFE_DELETE(m_RenalReabsorptionRatio);
  SAFE_DELETE(m_RenalTransportMaximum);
  SAFE_DELETE(m_RenalFiltrationRate);
  SAFE_DELETE(m_RenalReabsorptionRate);
  SAFE_DELETE(m_RenalExcretionRate);
  SAFE_DELETE(m_SystemicClearance);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::IsValid() const
{
  if (HasSystemic()) {
    if (!HasFractionExcretedInFeces()) {
      return false;
    }
    if (!HasFractionUnboundInPlasma()) {
      return false;
    }
    if (!HasIntrinsicClearance()) {
      return false;
    }
    if (!HasRenalClearance()) {
      return false;
    }
    if (!HasSystemicClearance()) {
      return false;
    }
  }

  if (HasRenalDynamic()) {
    if (GetRenalDynamic() == SERenalDynamic::Regulation) {
      if (!HasChargeInBlood()) {
        return false;
      }
      if (!HasFractionUnboundInPlasma()) {
        return false;
      }
      if (!HasRenalReabsorptionRatio()) {
        return false;
      }
      if (!HasRenalTransportMaximum()) {
        return false;
      }
    } else if (GetRenalDynamic() == SERenalDynamic::Clearance) {
      if (!HasRenalClearance()) {
        return false;
      }
    } else {
      return false;
    }
  }
  return true;
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstanceClearance::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstanceClearance::GetScalar(const std::string& name)
{
  if (name == "FractionExcretedInFeces") {
    return &GetFractionExcretedInFeces();
  }
  if (name == "FractionExcretedInUrine") {
    return &GetFractionExcretedInUrine();
  }
  if (name == "FractionMetabolizedInGut") {
    return &GetFractionMetabolizedInGut();
  }
  if (name == "FractionUnboundInPlasma") {
    return &GetFractionUnboundInPlasma();
  }
  if (name == "IntrinsicClearance") {
    return &GetIntrinsicClearance();
  }
  if (name == "GlomerularFilterability") {
    return &GetGlomerularFilterability();
  }
  if (name == "RenalClearance") {
    return &GetRenalClearance();
  }
  if (name == "RenalReabsorptionRatio") {
    return &GetRenalReabsorptionRatio();
  }
  if (name == "RenalTransportMaximum") {
    return &GetRenalTransportMaximum();
  }
  if (name == "RenalFiltrationRate") {
    return &GetRenalFiltrationRate();
  }
  if (name == "RenalReabsorptionRate") {
    return &GetRenalReabsorptionRate();
  }
  if (name == "RenalExcretionRate") {
    return &GetRenalExcretionRate();
  }
  if (name == "SystemicClearance") {
    return &GetSystemicClearance();
  }

  return nullptr;
}
//-----------------------------------------------------------------------------
SECharge SESubstanceClearance::GetChargeInBlood() const
{
  return m_ChargeInBlood;
}
//-----------------------------------------------------------------------------
void SESubstanceClearance::SetChargeInBlood(SECharge c)
{
  m_ChargeInBlood = c;
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasChargeInBlood() const
{
  return m_ChargeInBlood != SECharge::Invalid;
}
//-----------------------------------------------------------------------------
void SESubstanceClearance::InvalidateChargeInBlood()
{
  m_ChargeInBlood = SECharge::Invalid;
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasFractionExcretedInFeces() const
{
  return (m_FractionExcretedInFeces == nullptr) ? false : m_FractionExcretedInFeces->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstanceClearance::GetFractionExcretedInFeces()
{
  if (m_FractionExcretedInFeces == nullptr) {
    m_FractionExcretedInFeces = new SEScalarFraction();
  }
  return *m_FractionExcretedInFeces;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetFractionExcretedInFeces() const
{
  if (m_FractionExcretedInFeces == nullptr) {
    return SEScalar::dNaN();
  }
  return m_FractionExcretedInFeces->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasFractionExcretedInUrine() const
{
  return (m_FractionExcretedInUrine == nullptr) ? false : m_FractionExcretedInUrine->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstanceClearance::GetFractionExcretedInUrine()
{
  if (m_FractionExcretedInUrine == nullptr) {
    m_FractionExcretedInUrine = new SEScalarFraction();
  }
  return *m_FractionExcretedInUrine;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetFractionExcretedInUrine() const
{
  if (m_FractionExcretedInUrine == nullptr) {
    return SEScalar::dNaN();
  }
  return m_FractionExcretedInUrine->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasFractionMetabolizedInGut() const
{
  return (m_FractionMetabolizedInGut == nullptr) ? false : m_FractionMetabolizedInGut->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstanceClearance::GetFractionMetabolizedInGut()
{
  if (m_FractionMetabolizedInGut == nullptr) {
    m_FractionMetabolizedInGut = new SEScalarFraction();
  }
  return *m_FractionMetabolizedInGut;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetFractionMetabolizedInGut() const
{
  if (m_FractionMetabolizedInGut == nullptr) {
    return SEScalar::dNaN();
  }
  return m_FractionMetabolizedInGut->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasFractionUnboundInPlasma() const
{
  return (m_FractionUnboundInPlasma == nullptr) ? false : m_FractionUnboundInPlasma->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SESubstanceClearance::GetFractionUnboundInPlasma()
{
  if (m_FractionUnboundInPlasma == nullptr) {
    m_FractionUnboundInPlasma = new SEScalarFraction();
  }
  return *m_FractionUnboundInPlasma;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetFractionUnboundInPlasma() const
{
  if (m_FractionUnboundInPlasma == nullptr) {
    return SEScalar::dNaN();
  }
  return m_FractionUnboundInPlasma->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasIntrinsicClearance() const
{
  return (m_IntrinsicClearance == nullptr) ? false : m_IntrinsicClearance->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarVolumePerTimeMass& SESubstanceClearance::GetIntrinsicClearance()
{
  if (m_IntrinsicClearance == nullptr) {
    m_IntrinsicClearance = new SEScalarVolumePerTimeMass();
  }
  return *m_IntrinsicClearance;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetIntrinsicClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_IntrinsicClearance == nullptr) {
    return SEScalar::dNaN();
  }
  return m_IntrinsicClearance->GetValue(unit);
}
//-----------------------------------------------------------------------------
SERenalDynamic SESubstanceClearance::GetRenalDynamic() const
{
  return m_RenalDynamic;
}
//-----------------------------------------------------------------------------
void SESubstanceClearance::SetRenalDynamic(SERenalDynamic d)
{
  m_RenalDynamic = d;
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalDynamic() const
{
  return m_RenalDynamic == ((SERenalDynamic)-1) ? false : true;
}
//-----------------------------------------------------------------------------
void SESubstanceClearance::InvalidateRenalDynamic()
{
  m_RenalDynamic = (SERenalDynamic)-1;
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalClearance() const
{
  return (m_RenalClearance == nullptr) ? false : m_RenalClearance->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarVolumePerTimeMass& SESubstanceClearance::GetRenalClearance()
{
  if (m_RenalClearance == nullptr) {
    m_RenalClearance = new SEScalarVolumePerTimeMass();
  }
  return *m_RenalClearance;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_RenalClearance == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalClearance->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalReabsorptionRatio() const
{
  return (m_RenalReabsorptionRatio == nullptr) ? false : m_RenalReabsorptionRatio->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstanceClearance::GetRenalReabsorptionRatio()
{
  if (m_RenalReabsorptionRatio == nullptr) {
    m_RenalReabsorptionRatio = new SEScalar();
  }
  return *m_RenalReabsorptionRatio;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalReabsorptionRatio() const
{
  if (m_RenalReabsorptionRatio == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalReabsorptionRatio->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalTransportMaximum() const
{
  return (m_RenalTransportMaximum == nullptr) ? false : m_RenalTransportMaximum->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarMassPerTime& SESubstanceClearance::GetRenalTransportMaximum()
{
  if (m_RenalTransportMaximum == nullptr) {
    m_RenalTransportMaximum = new SEScalarMassPerTime();
  }
  return *m_RenalTransportMaximum;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalTransportMaximum(const MassPerTimeUnit& unit) const
{
  if (m_RenalTransportMaximum == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalTransportMaximum->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalFiltrationRate() const
{
  return (m_RenalFiltrationRate == nullptr) ? false : m_RenalFiltrationRate->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarMassPerTime& SESubstanceClearance::GetRenalFiltrationRate()
{
  if (m_RenalFiltrationRate == nullptr) {
    m_RenalFiltrationRate = new SEScalarMassPerTime();
  }
  return *m_RenalFiltrationRate;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalFiltrationRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalFiltrationRate == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalFiltrationRate->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalReabsorptionRate() const
{
  return (m_RenalReabsorptionRate == nullptr) ? false : m_RenalReabsorptionRate->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarMassPerTime& SESubstanceClearance::GetRenalReabsorptionRate()
{
  if (m_RenalReabsorptionRate == nullptr) {
    m_RenalReabsorptionRate = new SEScalarMassPerTime();
  }
  return *m_RenalReabsorptionRate;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalReabsorptionRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalReabsorptionRate == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalReabsorptionRate->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasRenalExcretionRate() const
{
  return (m_RenalExcretionRate == nullptr) ? false : m_RenalExcretionRate->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarMassPerTime& SESubstanceClearance::GetRenalExcretionRate()
{
  if (m_RenalExcretionRate == nullptr) {
    m_RenalExcretionRate = new SEScalarMassPerTime();
  }
  return *m_RenalExcretionRate;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetRenalExcretionRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalExcretionRate == nullptr) {
    return SEScalar::dNaN();
  }
  return m_RenalExcretionRate->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasGlomerularFilterability() const
{
  return (m_GlomerularFilterability == nullptr) ? false : m_GlomerularFilterability->IsValid();
}
//-----------------------------------------------------------------------------
SEScalar& SESubstanceClearance::GetGlomerularFilterability()
{
  if (m_GlomerularFilterability == nullptr) {
    m_GlomerularFilterability = new SEScalar();
  }
  return *m_GlomerularFilterability;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetGlomerularFilterability() const
{
  if (m_GlomerularFilterability == nullptr) {
    return SEScalar::dNaN();
  }
  return m_GlomerularFilterability->GetValue();
}
//-----------------------------------------------------------------------------
bool SESubstanceClearance::HasSystemicClearance() const
{
  return (m_SystemicClearance == nullptr) ? false : m_SystemicClearance->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarVolumePerTimeMass& SESubstanceClearance::GetSystemicClearance()
{
  if (m_SystemicClearance == nullptr) {
    m_SystemicClearance = new SEScalarVolumePerTimeMass();
  }
  return *m_SystemicClearance;
}
//-----------------------------------------------------------------------------
double SESubstanceClearance::GetSystemicClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_SystemicClearance == nullptr) {
    return SEScalar::dNaN();
  }
  return m_SystemicClearance->GetValue(unit);
}
//-----------------------------------------------------------------------------
}