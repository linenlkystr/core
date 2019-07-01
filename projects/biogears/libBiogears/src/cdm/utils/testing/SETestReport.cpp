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
#include <fstream>

#include <biogears/cdm/utils/testing/SETestReport.h>
#include <biogears/schema/cdm/TestReport.hxx>
#include <biogears/cdm/utils/FileUtils.h>

namespace biogears {
SETestReport::SETestReport(Logger* logger)
  : Loggable(logger)
{
}
//-----------------------------------------------------------------------------
SETestReport::~SETestReport()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SETestReport::Clear()
{
  DELETE_VECTOR(m_testSuite);
}
//-----------------------------------------------------------------------------
void SETestReport::Reset()
{
}
//-----------------------------------------------------------------------------
bool SETestReport::WriteFile(const std::string& fileName)
{
  xml_schema::namespace_infomap map;
  map[""].name = "uri:/mil/tatrc/physiology/datamodel";
  map[""].schema = "BioGears.xsd";

  try {
    std::ofstream outFile;
    outFile.open(ResolvePath(fileName));
    std::unique_ptr<CDM::TestReportData> unloaded = Unload();
    CDM::TestReport(outFile, *unloaded, map);
  } catch (const xml_schema::exception& e) {
    Error(e.what());
    return false;
  }
  return true;
}
//-----------------------------------------------------------------------------
SETestSuite& SETestReport::CreateTestSuite()
{
  SETestSuite* suite = new SETestSuite(GetLogger());
  m_testSuite.push_back(suite);
  return *suite;
}
//-----------------------------------------------------------------------------
const std::vector<SETestSuite*>& SETestReport::GetTestSuites() const
{
  return m_testSuite;
}
//-----------------------------------------------------------------------------
}
