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
#include <biogears/cdm/substance/SESubstancePharmacokinetics.h>

namespace biogears {
SESubstancePharmacokinetics::SESubstancePharmacokinetics(Logger* logger)
  : Loggable(logger)
{
  m_Physicochemicals = nullptr;
}
//-----------------------------------------------------------------------------
SESubstancePharmacokinetics::~SESubstancePharmacokinetics()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SESubstancePharmacokinetics::Clear()
{
  SAFE_DELETE(m_Physicochemicals);
  DELETE_MAP_SECOND(m_TissueKinetics);
  m_TissueKinetics.clear();
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacokinetics::IsValid() const
{
  if (HasPhysicochemicals())
    return true;
  if (HasTissueKinetics())
    return true;
  return false;
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePharmacokinetics::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SESubstancePharmacokinetics::GetScalar(const std::string& name)
{
  if (HasPhysicochemicals())
    return GetPhysicochemicals().GetScalar(name);
  // I did not support for getting a specific tissue kinetic scalar due to lack of coffee
  return nullptr;
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacokinetics::HasPhysicochemicals() const
{
  return m_Physicochemicals == nullptr ? false : m_Physicochemicals->IsValid();
}
//-----------------------------------------------------------------------------
SESubstancePhysicochemicals& SESubstancePharmacokinetics::GetPhysicochemicals()
{
  if (m_Physicochemicals == nullptr)
    m_Physicochemicals = new SESubstancePhysicochemicals(GetLogger());
  return *m_Physicochemicals;
}
//-----------------------------------------------------------------------------
const SESubstancePhysicochemicals* SESubstancePharmacokinetics::GetPhysicochemicals() const
{
  return m_Physicochemicals;
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacokinetics::HasTissueKinetics() const
{
  return m_TissueKinetics.size() > 0;
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacokinetics::HasTissueKinetics(const char* name) const
{
  return HasTissueKinetics(std::string{ name });
}
//-----------------------------------------------------------------------------
bool SESubstancePharmacokinetics::HasTissueKinetics(const std::string& name) const
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return true;
  return false;
}
//-----------------------------------------------------------------------------
SESubstanceTissuePharmacokinetics& SESubstancePharmacokinetics::GetTissueKinetics(const char* name)
{
  return GetTissueKinetics(std::string{ name });
}
//-----------------------------------------------------------------------------
SESubstanceTissuePharmacokinetics& SESubstancePharmacokinetics::GetTissueKinetics(const std::string& name)
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return *(idx->second);
  SESubstanceTissuePharmacokinetics* fx = new SESubstanceTissuePharmacokinetics(name, GetLogger());
  m_TissueKinetics[name] = fx;
  return *fx;
}
//-----------------------------------------------------------------------------
const SESubstanceTissuePharmacokinetics* SESubstancePharmacokinetics::GetTissueKinetics(const char* name) const
{
  return GetTissueKinetics(std::string{ name });
}
//-----------------------------------------------------------------------------
const SESubstanceTissuePharmacokinetics* SESubstancePharmacokinetics::GetTissueKinetics(const std::string& name) const
{
  auto idx = m_TissueKinetics.find(name);
  if (idx != m_TissueKinetics.end())
    return (idx->second);
  return nullptr;
}
//-----------------------------------------------------------------------------
void SESubstancePharmacokinetics::RemoveTissueKinetics(const char* name)
{
  m_TissueKinetics.erase(name);
}
//-----------------------------------------------------------------------------
void SESubstancePharmacokinetics::RemoveTissueKinetics(const std::string& name)
{
  m_TissueKinetics.erase(name);
}
//-----------------------------------------------------------------------------
}