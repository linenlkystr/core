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
#include <biogears/cdm/scenario/SEAnesthesiaMachineActionCollection.h>

#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>

#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachineChamber.h>
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h>

#include "../utils/io/cdm/AnesthesiaActions.h"
#include "../utils/io/cdm/Scenario.h"
#include <biogears/schema/cdm/AnesthesiaActions.hxx>

namespace biogears {
SEAnesthesiaMachineActionCollection::SEAnesthesiaMachineActionCollection(SESubstanceManager& substances)
  : Loggable(substances.GetLogger())
  , m_Substances(substances)
{
  m_Configuration = nullptr;

  m_OxygenTankPressureLoss = nullptr;
  m_OxygenWallPortPressureLoss = nullptr;

  m_ExpiratoryValveLeak = nullptr;
  m_ExpiratoryValveObstruction = nullptr;
  m_InspiratoryValveLeak = nullptr;
  m_InspiratoryValveObstruction = nullptr;
  m_MaskLeak = nullptr;
  m_SodaLimeFailure = nullptr;
  m_TubeCuffLeak = nullptr;
  m_VaporizerFailure = nullptr;
  m_VentilatorPressureLoss = nullptr;
  m_YPieceDisconnect = nullptr;
}
//-------------------------------------------------------------------------------
SEAnesthesiaMachineActionCollection::~SEAnesthesiaMachineActionCollection()
{
  Clear();
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::Clear()
{
  // State
  RemoveConfiguration();
  // Incidents
  RemoveOxygenTankPressureLoss();
  RemoveOxygenWallPortPressureLoss();
  // Failures
  RemoveExpiratoryValveLeak();
  RemoveExpiratoryValveObstruction();
  RemoveInspiratoryValveLeak();
  RemoveInspiratoryValveObstruction();
  RemoveMaskLeak();
  RemoveSodaLimeFailure();
  RemoveTubeCuffLeak();
  RemoveVaporizerFailure();
  RemoveVentilatorPressureLoss();
  RemoveYPieceDisconnect();
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::Unload(std::vector<CDM::ActionData*>& to)
{
  io::AnesthesiaActions::UnMarshall(*this, to);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::ProcessAction(const SEAnesthesiaMachineAction& action)
{

  if (auto config = dynamic_cast<const SEAnesthesiaMachineConfiguration*>(&action)) {
    if (m_Configuration == nullptr)
      m_Configuration = new SEAnesthesiaMachineConfiguration(m_Substances);
    m_Configuration->operator=(*config);
    return IsValid(*m_Configuration);
  }

  auto O2Tank = dynamic_cast<const SEOxygenTankPressureLoss*>(&action);
  if (O2Tank != nullptr) {
    if (m_OxygenTankPressureLoss == nullptr)
      m_OxygenTankPressureLoss = new SEOxygenTankPressureLoss();
    m_OxygenTankPressureLoss->operator=(*O2Tank);
    if (!m_OxygenTankPressureLoss->IsActive()) {
      RemoveOxygenTankPressureLoss();
      return true;
    }
    return IsValid(*m_OxygenTankPressureLoss);
  }

  auto O2Wall = dynamic_cast<const SEOxygenWallPortPressureLoss*>(&action);
  if (O2Wall != nullptr) {
    if (m_OxygenWallPortPressureLoss == nullptr)
      m_OxygenWallPortPressureLoss = new SEOxygenWallPortPressureLoss();
    m_OxygenWallPortPressureLoss->operator=(*O2Wall);
    if (!m_OxygenWallPortPressureLoss->IsActive()) {
      RemoveOxygenWallPortPressureLoss();
      return true;
    }
    return IsValid(*m_OxygenWallPortPressureLoss);
  }

  auto eLeak = dynamic_cast<const SEExpiratoryValveLeak*>(&action);
  if (eLeak != nullptr) {
    if (m_ExpiratoryValveLeak == nullptr)
      m_ExpiratoryValveLeak = new SEExpiratoryValveLeak();
    m_ExpiratoryValveLeak->operator=(*eLeak);
    if (!m_ExpiratoryValveLeak->IsActive()) {
      RemoveExpiratoryValveLeak();
      return true;
    }
    return IsValid(*m_ExpiratoryValveLeak);
  }

  auto eOb = dynamic_cast<const SEExpiratoryValveObstruction*>(&action);
  if (eOb != nullptr) {
    if (m_ExpiratoryValveObstruction == nullptr)
      m_ExpiratoryValveObstruction = new SEExpiratoryValveObstruction();
    m_ExpiratoryValveObstruction->operator=(*eOb);
    if (!m_ExpiratoryValveObstruction->IsActive()) {
      RemoveExpiratoryValveObstruction();
      return true;
    }
    return IsValid(*m_ExpiratoryValveObstruction);
  }

  auto iLeak = dynamic_cast<const SEInspiratoryValveLeak*>(&action);
  if (iLeak != nullptr) {
    if (m_InspiratoryValveLeak == nullptr)
      m_InspiratoryValveLeak = new SEInspiratoryValveLeak();
    m_InspiratoryValveLeak->operator=(*iLeak);
    if (!m_InspiratoryValveLeak->IsActive()) {
      RemoveInspiratoryValveLeak();
      return true;
    }
    return IsValid(*m_InspiratoryValveLeak);
  }

  auto iOb = dynamic_cast<const SEInspiratoryValveObstruction*>(&action);
  if (iOb != nullptr) {
    if (m_InspiratoryValveObstruction == nullptr)
      m_InspiratoryValveObstruction = new SEInspiratoryValveObstruction();
    m_InspiratoryValveObstruction->operator=(*iOb);
    if (!m_InspiratoryValveObstruction->IsActive()) {
      RemoveInspiratoryValveObstruction();
      return true;
    }
    return IsValid(*m_InspiratoryValveObstruction);
  }

  auto mask = dynamic_cast<const SEMaskLeak*>(&action);
  if (mask != nullptr) {
    if (m_MaskLeak == nullptr)
      m_MaskLeak = new SEMaskLeak();
    m_MaskLeak->operator=(*mask);
    if (!m_MaskLeak->IsActive()) {
      RemoveMaskLeak();
      return true;
    }
    return IsValid(*m_MaskLeak);
  }

  auto soda = dynamic_cast<const SESodaLimeFailure*>(&action);
  if (soda != nullptr) {
    if (m_SodaLimeFailure == nullptr)
      m_SodaLimeFailure = new SESodaLimeFailure();
    m_SodaLimeFailure->operator=(*soda);
    if (!m_SodaLimeFailure->IsActive()) {
      RemoveSodaLimeFailure();
      return true;
    }
    return IsValid(*m_SodaLimeFailure);
  }

  auto tube = dynamic_cast<const SETubeCuffLeak*>(&action);
  if (tube != nullptr) {
    if (m_TubeCuffLeak == nullptr)
      m_TubeCuffLeak = new SETubeCuffLeak();
    m_TubeCuffLeak->operator=(*tube);
    if (!m_TubeCuffLeak->IsActive()) {
      RemoveTubeCuffLeak();
      return true;
    }
    return IsValid(*m_TubeCuffLeak);
  }

  auto vFail = dynamic_cast<const SEVaporizerFailure*>(&action);
  if (vFail != nullptr) {
    if (m_VaporizerFailure == nullptr)
      m_VaporizerFailure = new SEVaporizerFailure();
    m_VaporizerFailure->operator=(*vFail);
    if (!m_VaporizerFailure->IsActive()) {
      RemoveVaporizerFailure();
      return true;
    }
    return IsValid(*m_VaporizerFailure);
  }

  auto vLoss = dynamic_cast<const SEVentilatorPressureLoss*>(&action);
  if (vLoss != nullptr) {
    if (m_VentilatorPressureLoss == nullptr)
      m_VentilatorPressureLoss = new SEVentilatorPressureLoss();
    m_VentilatorPressureLoss->operator=(*vLoss);
    if (!m_VentilatorPressureLoss->IsActive()) {
      RemoveVentilatorPressureLoss();
      return true;
    }
    return IsValid(*m_VentilatorPressureLoss);
  }

  auto Y = dynamic_cast<const SEYPieceDisconnect*>(&action);
  if (Y != nullptr) {
    if (m_YPieceDisconnect == nullptr)
      m_YPieceDisconnect = new SEYPieceDisconnect();
    m_YPieceDisconnect->operator=(*Y);
    if (!m_YPieceDisconnect->IsActive()) {
      RemoveYPieceDisconnect();
      return true;
    }
    return IsValid(*m_YPieceDisconnect);
  }
  /// \error Unsupported Action
  Error("Unsupported Action");
  return false;
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::IsValid(const SEAnesthesiaMachineAction& action)
{
  if (!action.IsValid()) {
    Error("Invalid Anesthesia Machine Action");
    return false;
  }
  return true;
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasConfiguration() const
{
  return m_Configuration == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEAnesthesiaMachineConfiguration* SEAnesthesiaMachineActionCollection::GetConfiguration() const
{
  return m_Configuration;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveConfiguration()
{
  SAFE_DELETE(m_Configuration);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasOxygenTankPressureLoss() const
{
  return m_OxygenTankPressureLoss == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEOxygenTankPressureLoss* SEAnesthesiaMachineActionCollection::GetOxygenTankPressureLoss() const
{
  return m_OxygenTankPressureLoss;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveOxygenTankPressureLoss()
{
  SAFE_DELETE(m_OxygenTankPressureLoss);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasOxygenWallPortPressureLoss() const
{
  return m_OxygenWallPortPressureLoss == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEOxygenWallPortPressureLoss* SEAnesthesiaMachineActionCollection::GetOxygenWallPortPressureLoss() const
{
  return m_OxygenWallPortPressureLoss;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveOxygenWallPortPressureLoss()
{
  SAFE_DELETE(m_OxygenWallPortPressureLoss);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasExpiratoryValveLeak() const
{
  return m_ExpiratoryValveLeak == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEExpiratoryValveLeak* SEAnesthesiaMachineActionCollection::GetExpiratoryValveLeak() const
{
  return m_ExpiratoryValveLeak;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveExpiratoryValveLeak()
{
  SAFE_DELETE(m_ExpiratoryValveLeak);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasExpiratoryValveObstruction() const
{
  return m_ExpiratoryValveObstruction == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEExpiratoryValveObstruction* SEAnesthesiaMachineActionCollection::GetExpiratoryValveObstruction() const
{
  return m_ExpiratoryValveObstruction;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveExpiratoryValveObstruction()
{
  SAFE_DELETE(m_ExpiratoryValveObstruction);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasInspiratoryValveLeak() const
{
  return m_InspiratoryValveLeak == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEInspiratoryValveLeak* SEAnesthesiaMachineActionCollection::GetInspiratoryValveLeak() const
{
  return m_InspiratoryValveLeak;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveInspiratoryValveLeak()
{
  SAFE_DELETE(m_InspiratoryValveLeak);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasInspiratoryValveObstruction() const
{
  return m_InspiratoryValveObstruction == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEInspiratoryValveObstruction* SEAnesthesiaMachineActionCollection::GetInspiratoryValveObstruction() const
{
  return m_InspiratoryValveObstruction;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveInspiratoryValveObstruction()
{
  SAFE_DELETE(m_InspiratoryValveObstruction);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasMaskLeak() const
{
  return m_MaskLeak == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEMaskLeak* SEAnesthesiaMachineActionCollection::GetMaskLeak() const
{
  return m_MaskLeak;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveMaskLeak()
{
  SAFE_DELETE(m_MaskLeak);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasSodaLimeFailure() const
{
  return m_SodaLimeFailure == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SESodaLimeFailure* SEAnesthesiaMachineActionCollection::GetSodaLimeFailure() const
{
  return m_SodaLimeFailure;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveSodaLimeFailure()
{
  SAFE_DELETE(m_SodaLimeFailure);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasTubeCuffLeak() const
{
  return m_TubeCuffLeak == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SETubeCuffLeak* SEAnesthesiaMachineActionCollection::GetTubeCuffLeak() const
{
  return m_TubeCuffLeak;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveTubeCuffLeak()
{
  SAFE_DELETE(m_TubeCuffLeak);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasVaporizerFailure() const
{
  return m_VaporizerFailure == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEVaporizerFailure* SEAnesthesiaMachineActionCollection::GetVaporizerFailure() const
{
  return m_VaporizerFailure;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveVaporizerFailure()
{
  SAFE_DELETE(m_VaporizerFailure);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasVentilatorPressureLoss() const
{
  return m_VentilatorPressureLoss == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEVentilatorPressureLoss* SEAnesthesiaMachineActionCollection::GetVentilatorPressureLoss() const
{
  return m_VentilatorPressureLoss;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveVentilatorPressureLoss()
{
  SAFE_DELETE(m_VentilatorPressureLoss);
}
//-------------------------------------------------------------------------------
bool SEAnesthesiaMachineActionCollection::HasYPieceDisconnect() const
{
  return m_YPieceDisconnect == nullptr ? false : true;
}
//-------------------------------------------------------------------------------
SEYPieceDisconnect* SEAnesthesiaMachineActionCollection::GetYPieceDisconnect() const
{
  return m_YPieceDisconnect;
}
//-------------------------------------------------------------------------------
void SEAnesthesiaMachineActionCollection::RemoveYPieceDisconnect()
{
  SAFE_DELETE(m_YPieceDisconnect);
}
//-------------------------------------------------------------------------------
}