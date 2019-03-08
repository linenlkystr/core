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
#include <biogears/cdm/substance/NULLSubstanceManager.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
//External Includes
#include <dirent.h>
//Project Includes
#include <biogears/cdm/Serializer.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/utils/FileUtils.h>
#include <biogears/cdm/utils/unitconversion/UnitConversionEngine.h>

namespace biogears {
NULLSubstanceManager::NULLSubstanceManager(Logger* logger)
  : SESubstanceManager(logger)
{}
//-----------------------------------------------------------------------------
NULLSubstanceManager::~NULLSubstanceManager()
{}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::Clear()
{
  return;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::Reset()
{
  return;
}
//-----------------------------------------------------------------------------
/**
 * TRANSFERS OWNERSHIP TO THE MANAGER
 */
void NULLSubstanceManager::AddSubstance(SESubstance& substance)
{
  // SESubstance* s;
  // for (unsigned int i = 0; i < m_Substances.size(); i++) {
  //   s = m_Substances.at(i);
  //   if (s == &substance)
  //     return;
  // }  
  m_Substances.push_back(&substance);
}
//-----------------------------------------------------------------------------
SESubstance* NULLSubstanceManager::GetSubstance(const char* name) const
{
  return GetSubstance(std::string{ name });
}
//-----------------------------------------------------------------------------
SESubstance* NULLSubstanceManager::GetSubstance(const std::string& name) const
{
  return m_Substances[0];
}
//-----------------------------------------------------------------------------
const std::vector<SESubstance*>& NULLSubstanceManager::GetSubstances() const
{
  return m_Substances;
}
//-----------------------------------------------------------------------------
bool NULLSubstanceManager::IsActive(const SESubstance& substance) const
{
  return true;
}
//-----------------------------------------------------------------------------
const std::vector<SESubstance*>& NULLSubstanceManager::GetActiveSubstances() const
{
  return m_ActiveSubstances;  
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::AddActiveSubstance(SESubstance& substance)
{  
  // if (IsActive(substance))
  //   return;
  // if (substance.GetState() == CDM::enumSubstanceState::Gas)
  //   m_ActiveGases.push_back(&substance);
  // if (substance.GetState() == CDM::enumSubstanceState::Liquid)
  //   m_ActiveLiquids.push_back(&substance);
  m_ActiveSubstances.push_back(&substance);
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::RemoveActiveSubstance(const SESubstance& substance)
{
  // Took out a bunch of lines
  return;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::RemoveActiveSubstances(const std::vector<SESubstance*>& substances)
{
  // Took out a bunch of lines
  return;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::RemoveActiveSubstances()
{
  // Took out a bunch of lines
  return;
}
//-----------------------------------------------------------------------------
const std::vector<SESubstance*>& NULLSubstanceManager::GetActiveGases() const
{
  return m_ActiveGases;
}
//-----------------------------------------------------------------------------
const std::vector<SESubstance*>& NULLSubstanceManager::GetActiveLiquids() const
{
  return m_ActiveLiquids;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::AddCompound(SESubstanceCompound& compound)
{
  // SESubstanceCompound* c;
  // for (unsigned int i = 0; i < m_Compounds.size(); i++) {
  //   c = m_Compounds.at(i);
  //   if (c == &compound)
  //     return;
  // }  
  m_Compounds.push_back(&compound);
}
//-----------------------------------------------------------------------------
SESubstanceCompound* NULLSubstanceManager::GetCompound(const char* name) const
{
  return m_Compounds[0];
}
//-----------------------------------------------------------------------------
SESubstanceCompound* NULLSubstanceManager::GetCompound(const std::string& name) const
{
  return m_Compounds[0];
}
//-----------------------------------------------------------------------------
const std::vector<SESubstanceCompound*>& NULLSubstanceManager::GetCompounds() const
{
  return m_Compounds;
}
//-----------------------------------------------------------------------------
bool NULLSubstanceManager::IsActive(const SESubstanceCompound& compound) const
{
  return true;
}
//-----------------------------------------------------------------------------
const std::vector<SESubstanceCompound*>& NULLSubstanceManager::GetActiveCompounds() const
{
  return m_ActiveCompounds;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::AddActiveCompound(SESubstanceCompound& compound)
{
  m_ActiveCompounds.push_back(&compound);
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::RemoveActiveCompound(SESubstanceCompound& compound)
{
  return;
}
//-----------------------------------------------------------------------------
void NULLSubstanceManager::RemoveActiveCompounds(const std::vector<SESubstanceCompound*>& compounds)
{
  return;
}
//-----------------------------------------------------------------------------
SESubstance* NULLSubstanceManager::ReadSubstanceFile(const char* xmlFile)
{
  return ReadSubstanceFile(std::string{ xmlFile });
}
//-----------------------------------------------------------------------------
SESubstance* NULLSubstanceManager::ReadSubstanceFile(const std::string& xmlFile)
{
  // So this function (and it's overload) stayed the same because I think they need to return something
  std::stringstream ss;
  CDM::ObjectData* obj;

  SESubstance* sub;
  CDM::SubstanceData* subData;

  std::unique_ptr<CDM::ObjectData> data;

  obj = nullptr;
  sub = nullptr;
  subData = nullptr;

  data = Serializer::ReadFile(xmlFile, GetLogger());
  //ss.str("");
  //ss<<"Reading substance file : ./substances/"<<xmlFile;
  //Info(ss);
  obj = data.get();

  subData = dynamic_cast<CDM::SubstanceData*>(obj);
  if (subData != nullptr) {
    sub = new SESubstance(GetLogger());
    sub->Load(*subData);
    return sub;
  }
  ss.str("");
  /// \error Substance file could not be read in
  ss << "Substance file could not be read in : ./substances/" << xmlFile;
  Error(ss, "NULLSubstanceManager::ReadSubstanceFile");
  return nullptr;
}
//-----------------------------------------------------------------------------
bool NULLSubstanceManager::LoadSubstanceDirectory()
{
  bool succeed = true;
  Clear();
  std::stringstream ss;
  DIR* dir;
  struct dirent* ent;

  ScopedFileSystemLock lock;

  std::string workingDirectory = GetCurrentWorkingDirectory();

#if defined(_WIN32)
  dir = opendir("./substances/");
#else
  dir = opendir(std::string(workingDirectory + std::string("/substances/")).c_str());
#endif

  if (dir != nullptr) {
    CDM::ObjectData* obj;

    SESubstance* sub;
    CDM::SubstanceData* subData;

    SESubstanceCompound* compound;
    CDM::SubstanceCompoundData* compoundData;

    std::unique_ptr<CDM::ObjectData> data;

    while ((ent = readdir(dir)) != nullptr) {
      obj = nullptr;
      sub = nullptr;
      subData = nullptr;
      ss.str("");
      ss << workingDirectory << "/substances/" << ent->d_name;
      if (!IsDirectory(ent) && strlen(ent->d_name) > 2) {
        data = Serializer::ReadFile(ss.str(), GetLogger());
        ss.str("");
        ss << "Reading substance file : ./substances/" << ent->d_name;
        Debug(ss);
        obj = data.release();
        subData = dynamic_cast<CDM::SubstanceData*>(obj);
        if (subData != nullptr) {
          sub = new SESubstance(GetLogger());
          sub->Load(*subData);
          AddSubstance(*sub);
          m_OriginalSubstanceData[sub] = subData;
          continue;
        }
        compoundData = dynamic_cast<CDM::SubstanceCompoundData*>(obj);
        if (compoundData != nullptr) { // Save this off and process it till later, once all substances are read
          compound = new SESubstanceCompound(GetLogger());
          m_OriginalCompoundData[compound] = compoundData;
          AddCompound(*compound);
          continue;
        }
        Error("Unknown Type");
        succeed = false;
      }
    } // Done with directory search
    // Ok, now let's load up our compounds
    for (auto itr : m_OriginalCompoundData)
      itr.first->Load((const CDM::SubstanceCompoundData&)*itr.second, *this);

    return succeed;

    closedir(dir);
    return succeed;
  } else {
    ss << "Unable to read files" << std::ends;
    Error(ss);
    succeed = false;
    return succeed;
  }
}
//-----------------------------------------------------------------------------
}