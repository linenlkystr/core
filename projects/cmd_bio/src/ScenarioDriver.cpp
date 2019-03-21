//**********************************************************************************
//Copyright 2015 Applied Research Associates, Inc.
//Licensed under the Apache License, Version 2.0 (the "License"); you may not use
//this file except in compliance with the License.You may obtain a copy of the License
//at :
//http://www.apache.org/licenses/LICENSE-2.0
//Unless required by applicable law or agreed to in writing, software distributed under
//the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//CONDITIONS OF ANY KIND, either express or implied.See the License for the
//specific language governing permissions and limitations under the License.
//**************************************************************************************
#include <biogears/cdm/utils/DataTrack.h>
#include <biogears/cdm/utils/FileUtils.h>
#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/engine/Controller/Scenario/BioGearsScenario.h>
#include <biogears/engine/Controller/Scenario/BioGearsScenarioExec.h>

#include "ScenarioDriver.h"
#include "utils/string-helpers.h"
#include <iostream>
#include <string>

//
namespace biogears {
int runScenario(const std::string& patient, std::string XMLString);

//-------------------------------------------------------------------------------
ScenarioDriver::ScenarioDriver(size_t thread_count)
  : _pool(thread_count)
{
}
//-------------------------------------------------------------------------------
ScenarioDriver::~ScenarioDriver()
{
}
//-------------------------------------------------------------------------------
//!
//! \brief Iterates through patientFiles, creates a lambda function for each item, and passes those functions to a thread pool
//!
void ScenarioDriver::LoadPatients(std::vector<std::string> files, std::string xml)
{
  for (auto& patient : files) {
    std::function<void()> work = [=]() { biogears::runScenario(patient,  xml); };
    _pool.queue_work(work);
  }
}

void ScenarioDriver::LoadScenarios(std::vector<std::string> files)
{
  for (auto& patient : files) {
    std::function<void()> work = [=]() { biogears::runScenario("StandardMale.xml", patient); };
    _pool.queue_work(work);
  }
}

//-------------------------------------------------------------------------------

//!
//! \brief creates a BioGearsScenarioExec object and executes the scenario
//! \param patient : the name of the patient being used for the scenario
//! \param XMLString : a path to the xml scenario being used
//! \return int 0 if no exceptions were encountered, otherwise 1
//!
int runScenario(const std::string& patient, std::string XMLString)
{
  std::string patientXML(trim(patient));

  std::string patientLog = "-" + patientXML;
  patientLog = findAndReplace(patientLog, ".xml", ".log");

  std::string patientResults = "-" + patientXML;
  patientResults = findAndReplace(patientResults, ".xml", "Results.csv");

  std::string logFile(trim(patient));
  std::string outputFile(trim(patient));
  logFile = findAndReplace(logFile, ".xml", "Results.log");
  outputFile = findAndReplace(outputFile, ".xml", "Results.csv");

  std::unique_ptr<PhysiologyEngine> eng;
  try {
    eng = CreateBioGearsEngine(logFile);
  } catch (std::exception e) {
    std::cout << e.what();
    return 1;
  }
  DataTrack* trk = &eng->GetEngineTrack()->GetDataTrack();
  BioGearsScenario sce(eng->GetSubstanceManager());
  sce.Load(trim(XMLString));
  sce.GetInitialParameters().SetPatientFile(trim(patientXML));

  BioGearsScenarioExec* exec = new BioGearsScenarioExec(*eng);
  exec->Execute(sce, outputFile, nullptr);
  delete exec;

  return 0;
}
//-------------------------------------------------------------------------------
//!
//! \brief thread pool begins execution of tasks in queue
//!
void ScenarioDriver::run()
{
  _pool.start();
}
//-------------------------------------------------------------------------------
//!
//! \brief stops execution of tasks in queue
//!
void ScenarioDriver::stop()
{
  _pool.stop();
}
//-------------------------------------------------------------------------------
//!
//! \brief stops the thread pool if the work queue is empty
//! \return true if the work queue is empty, false otherwise
//!
bool ScenarioDriver::stop_if_empty()
{
  return _pool.stop_if_empty();
}
//-------------------------------------------------------------------------------
//!
//! \brief joins threads in thread pool
//!
void ScenarioDriver::join()
{
  _pool.join();
}
} // namespace biogears
