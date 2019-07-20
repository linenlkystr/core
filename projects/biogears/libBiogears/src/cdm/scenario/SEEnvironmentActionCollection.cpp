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
#include <biogears/cdm/scenario/SEEnvironmentActionCollection.h>

#include <biogears/cdm/properties/SEScalarHeatConductancePerArea.h>
#include <biogears/cdm/substance/SESubstanceFraction.h>

#include <biogears/schema/cdm/Environment.hxx>
#include <biogears/schema/cdm/EnvironmentActions.hxx>

namespace biogears {
SEEnvironmentActionCollection::SEEnvironmentActionCollection(SESubstanceManager& substances)
  : Loggable(substances.GetLogger())
  , m_Substances(substances)
{
  m_Change = nullptr;
  m_ThermalApplication = nullptr;
}

SEEnvironmentActionCollection::~SEEnvironmentActionCollection()
{
  Clear();
}

void SEEnvironmentActionCollection::Clear()
{
  RemoveChange();
  RemoveThermalApplication();
}

bool SEEnvironmentActionCollection::ProcessAction(const SEEnvironmentAction& action)
{
  if (!IsValid(action))
    return false;


  const auto change = dynamic_cast<const SEEnvironmentChange*>(&action);
  if (change != nullptr) {
    if (m_Change == nullptr)
      m_Change = new SEEnvironmentChange(m_Substances);
    io::EnvironmentActions::Copy(*change,*m_Change);
    return IsValid(*m_Change);
  }

  const auto thermal = dynamic_cast<const SEThermalApplication*>(&action);
  if (thermal != nullptr) {
    if (m_ThermalApplication == nullptr)
      m_ThermalApplication = new SEThermalApplication();
    m_ThermalApplication->Load(*thermal);
    if (!m_ThermalApplication->IsActive()) {
      RemoveThermalApplication();
      return true;
    }
    return IsValid(*m_ThermalApplication);
  }

  /// \error Unsupported Action
  Error("Unsupported Action");
  return false;
}

bool SEEnvironmentActionCollection::IsValid(const SEEnvironmentAction& action)
{
  if (!action.IsValid()) {
    Error("Invalid Inhaler Environment Action");
    return false;
  }
  return true;
}

bool SEEnvironmentActionCollection::HasChange() const
{
  return m_Change == nullptr ? false : true;
}
SEEnvironmentChange* SEEnvironmentActionCollection::GetChange() const
{
  return m_Change;
}
void SEEnvironmentActionCollection::RemoveChange()
{
  m_Change = nullptr;
}

bool SEEnvironmentActionCollection::HasThermalApplication() const
{
  return m_ThermalApplication != nullptr;
}
SEThermalApplication* SEEnvironmentActionCollection::GetThermalApplication() const
{
  return m_ThermalApplication;
}
void SEEnvironmentActionCollection::RemoveThermalApplication()
{
  SAFE_DELETE(m_ThermalApplication);
}
}