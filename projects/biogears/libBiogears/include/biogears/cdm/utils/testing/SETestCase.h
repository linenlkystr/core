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

#pragma once
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/utils/testing/SETestErrorStatistics.h>

IO_DECL(TestReport)

namespace biogears {
class SETestSuite;

class BIOGEARS_API SETestCase : public Loggable {
  friend SETestSuite;
  friend io::TestReport;

protected:
  SETestCase(Logger* logger);
  SETestCase(const std::string& name, Logger* logger);

public:
  virtual ~SETestCase();

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

public:
  void SetName(const std::string& name);
  std::string GetName() const;
  const char* GetName_cStr() const;
  SEScalarTime& GetDuration();
  void AddFailure(std::stringstream& msg);
  void AddFailure(const std::string& err);
  const std::vector<std::string>& GetFailures();

  SETestErrorStatistics& CreateErrorStatistic();
  const std::vector<SETestErrorStatistics*>& GetErrorStatistics() const;

protected:
  std::string m_Name;
  SEScalarTime m_Duration;

  std::vector<std::string> m_Failure;
  std::vector<SETestErrorStatistics*> m_CaseEqualsErrors;
};
}