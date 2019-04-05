#ifndef BIOGEARS_STATE_GENERATOR_H
#define BIOGEARS_STATE_GENERATOR_H
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
#include <biogears/threading/runnable.h>
#include <biogears/threading/thread_pool.h>

namespace biogears {
class ScenarioDriver : biogears::Runnable {
public:
  ScenarioDriver(size_t thread_count);
  ScenarioDriver(const ScenarioDriver&) = delete;
  ScenarioDriver(ScenarioDriver&&) = default;
  ~ScenarioDriver() override;

  void LoadPatients(std::vector<std::string> patients, std::string xml);
  void LoadScenarios(std::vector<std::string> patients);

  void run() override;
  void stop() override;
  bool stop_if_empty();
  void join() override;

private:
  ThreadPool _pool;
};
} //namespace biogears

#endif //BIOGEARS_STATE_GENERATOR_H