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


#include <biogears/cdm/utils/testing/SETestSuite.h>
#include <biogears/schema/cdm/Properties.hxx>
#include <biogears/schema/cdm/TestReport.hxx>

#include "../../utils/io/Property.h"
namespace biogears {
SETestSuite::SETestSuite(Logger* logger)
  : Loggable(logger)
{
  m_Performed = true;
  m_Name = "";
}

SETestSuite::~SETestSuite()
{
  Clear();
}

void SETestSuite::Clear()
{
  DELETE_VECTOR(m_SuiteEqualError);
  DELETE_VECTOR(m_TestCase);
}

void SETestSuite::Reset()
{
  for (unsigned int i = 0; i < m_TestCase.size(); i++) {
    m_TestCase.at(i)->Reset();
  }
  m_Performed = false;
  m_Name = "";
}

void SETestSuite::SetName(const std::string& Name)
{
  m_Name = Name;
}

std::string SETestSuite::GetName() const
{
  return m_Name;
}

const char* SETestSuite::GetName_cStr() const
{
  return m_Name.c_str();
}
void SETestSuite::PerformSuite(bool performed)
{
  m_Performed = performed;
}

bool SETestSuite::PerformedSuite()
{
  return m_Performed;
}

const SEScalarTime& SETestSuite::GetDuration() const
{
  double time = 0;
  for (unsigned int i = 0; i < m_TestCase.size(); i++)
    time += m_TestCase.at(i)->GetDuration().GetValue(TimeUnit::s);
  m_Time.SetValue(time, TimeUnit::s);
  return m_Time;
}

std::vector<std::string>& SETestSuite::GetRequirements()
{
  return m_Requirements;
}

SETestCase& SETestSuite::CreateTestCase()
{
  SETestCase* test = new SETestCase(GetLogger());
  m_TestCase.push_back(test);
  return *test;
}

const std::vector<SETestCase*>& SETestSuite::GetTestCases() const
{
  return m_TestCase;
}

int SETestSuite::GetNumberOfErrors() const
{
  size_t count = 0;

  for (size_t i = 0; i < m_TestCase.size(); i++) {
    count += m_TestCase.at(i)->GetFailures().size();
  }

  return static_cast<int>(count); //Major Possibility of a clamp
}

int SETestSuite::GetNumberOfTests() const
{
  int count = 0;

  for (unsigned int i = 0; i < m_TestCase.size(); i++) {
    count++;
  }

  return count;
}
}