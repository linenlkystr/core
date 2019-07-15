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
#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>

#include <biogears/cdm/substance/SESubstanceManager.h>

#include "cdm/utils/io/cdm/Scenario.h"
#include "cdm/utils/io/cdm/Property.h"

namespace biogears {
SEDataRequestManager::SEDataRequestManager(Logger* logger)
  : Loggable(logger)
  , m_SamplesPerSecond(1.0)
  , m_ResultsFile("")

{
  m_DefaultDecimalFormatting = nullptr;
  m_OverrideDecimalFormatting = nullptr;
  Clear();
}
//-----------------------------------------------------------------------------
SEDataRequestManager::~SEDataRequestManager()
{
  Clear();
}
//-----------------------------------------------------------------------------
const char* SEDataRequestManager::GetResultsFilename_cStr() const
{
  return m_ResultsFile.c_str();
}
//-----------------------------------------------------------------------------
std::string SEDataRequestManager::GetResultsFilename() const
{
  return m_ResultsFile;
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::SetResultsFilename(const char* name)
{
  m_ResultsFile = name;
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::SetResultsFilename(const std::string& name)
{
  m_ResultsFile = name;
}
//-----------------------------------------------------------------------------
std::string SEDataRequestManager::GetWorkingDir() const
{
  return m_WorkingDir;
}
//-----------------------------------------------------------------------------
const char* SEDataRequestManager::GetWorkingDir_cStr() const
{
  return m_WorkingDir.c_str();
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::SetWorkingDir(const char* name)
{
  m_WorkingDir = name;
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::SetWorkingDir(const std::string& name)
{
  m_WorkingDir = name;
}
//-----------------------------------------------------------------------------
std::string SEDataRequestManager::GetResovedFilePath() const { return m_WorkingDir + m_ResultsFile; }
//-----------------------------------------------------------------------------
void SEDataRequestManager::Clear()
{
  m_SamplesPerSecond = 0; // Sample every time step
  DELETE_VECTOR(m_Requests);
  SAFE_DELETE(m_DefaultDecimalFormatting);
  SAFE_DELETE(m_OverrideDecimalFormatting);
}
//-----------------------------------------------------------------------------
bool SEDataRequestManager::HasDefaultDecimalFormatting() const
{
  return m_DefaultDecimalFormatting != nullptr;
}
//-----------------------------------------------------------------------------
SEDecimalFormat& SEDataRequestManager::GetDefaultDecimalFormatting()
{
  if (m_DefaultDecimalFormatting == nullptr)
    m_DefaultDecimalFormatting = new SEDecimalFormat();
  return *m_DefaultDecimalFormatting;
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::RemoveDefaultDecimalFormatting()
{
  SAFE_DELETE(m_DefaultDecimalFormatting);
}
//-----------------------------------------------------------------------------
bool SEDataRequestManager::HasOverrideDecimalFormatting() const
{
  return m_OverrideDecimalFormatting != nullptr;
}
//-----------------------------------------------------------------------------
SEDecimalFormat& SEDataRequestManager::GetOverrideDecimalFormatting()
{
  if (m_OverrideDecimalFormatting == nullptr)
    m_OverrideDecimalFormatting = new SEDecimalFormat();
  return *m_OverrideDecimalFormatting;
}
//-----------------------------------------------------------------------------
void SEDataRequestManager::RemoveOverrideDecimalFormatting()
{
  SAFE_DELETE(m_OverrideDecimalFormatting);
}
//-----------------------------------------------------------------------------
SEEnvironmentDataRequest& SEDataRequestManager::CreateEnvironmentDataRequest(const SEDecimalFormat* dfault)
{
  SEEnvironmentDataRequest* dr = new SEEnvironmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SEEquipmentDataRequest& SEDataRequestManager::CreateEquipmentDataRequest(const SEDecimalFormat* dfault)
{
  SEEquipmentDataRequest* dr = new SEEquipmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SEPatientDataRequest& SEDataRequestManager::CreatePatientDataRequest(const SEDecimalFormat* dfault)
{
  SEPatientDataRequest* dr = new SEPatientDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SEPhysiologyDataRequest& SEDataRequestManager::CreatePhysiologyDataRequest(const SEDecimalFormat* dfault)
{
  SEPhysiologyDataRequest* dr = new SEPhysiologyDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SESubstanceDataRequest& SEDataRequestManager::CreateSubstanceDataRequest(const SEDecimalFormat* dfault)
{
  SESubstanceDataRequest* dr = new SESubstanceDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SEGasCompartmentDataRequest& SEDataRequestManager::CreateGasCompartmentDataRequest(const SEDecimalFormat* dfault)
{
  SEGasCompartmentDataRequest* dr = new SEGasCompartmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SELiquidCompartmentDataRequest& SEDataRequestManager::CreateLiquidCompartmentDataRequest(const SEDecimalFormat* dfault)
{
  SELiquidCompartmentDataRequest* dr = new SELiquidCompartmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SEThermalCompartmentDataRequest& SEDataRequestManager::CreateThermalCompartmentDataRequest(const SEDecimalFormat* dfault)
{
  SEThermalCompartmentDataRequest* dr = new SEThermalCompartmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
SETissueCompartmentDataRequest& SEDataRequestManager::CreateTissueCompartmentDataRequest(const SEDecimalFormat* dfault)
{
  SETissueCompartmentDataRequest* dr = new SETissueCompartmentDataRequest(dfault);
  m_Requests.push_back(dr);
  return *dr;
}
//-----------------------------------------------------------------------------
}