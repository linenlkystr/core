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

#include <biogears/cdm/properties/SEScalarTime.h>

#include <biogears/cdm/utils/testing/SETestCase.h>


namespace biogears {
SETestCase::SETestCase(Logger* logger)
  : Loggable(logger)
{
  SETestCase("default", logger);
}
//-----------------------------------------------------------------------------
SETestCase::SETestCase(const std::string& name, Logger* logger)
  : Loggable(logger)
{
  m_Name = name;
}
//-----------------------------------------------------------------------------
SETestCase::~SETestCase()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SETestCase::Clear()
{
  m_Failure.clear();
  DELETE_VECTOR(m_CaseEqualsErrors);
}
//-----------------------------------------------------------------------------
void SETestCase::Reset()
{
  m_Failure.clear();
  m_Duration.SetValue(0, TimeUnit::s);
  DELETE_VECTOR(m_CaseEqualsErrors);
}
//-----------------------------------------------------------------------------
void SETestCase::SetName(const std::string& Name)
{
  m_Name = Name;
}
//-----------------------------------------------------------------------------
std::string SETestCase::GetName() const
{
  return m_Name;
}
//-----------------------------------------------------------------------------
const char* SETestCase::GetName_cStr() const
{
  return m_Name.c_str();
}
//-----------------------------------------------------------------------------
SEScalarTime& SETestCase::GetDuration()
{
  return m_Duration;
}
//-----------------------------------------------------------------------------
void SETestCase::AddFailure(std::stringstream& err)
{
  AddFailure(err.str());
  err.str("");
  err.clear();
}
//-----------------------------------------------------------------------------
void SETestCase::AddFailure(const std::string& err)
{
  m_Failure.push_back(err);
  Error(err);
}
//-----------------------------------------------------------------------------
const std::vector<std::string>& SETestCase::GetFailures()
{
  return m_Failure;
}
//-----------------------------------------------------------------------------
SETestErrorStatistics& SETestCase::CreateErrorStatistic()
{
  SETestErrorStatistics* err = new SETestErrorStatistics(GetLogger());
  m_CaseEqualsErrors.push_back(err);
  return *err;
}
//-----------------------------------------------------------------------------
const std::vector<SETestErrorStatistics*>& SETestCase::GetErrorStatistics() const
{
  return m_CaseEqualsErrors;
}
//-----------------------------------------------------------------------------
}