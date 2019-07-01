/**************************************************************************************
Copyright 2019 Applied Research Associates, Inc.
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

namespace biogears {

enum class SEAnesthesiaMachineEvent {
  Invalid = -1,
  OxygenBottle1Exhausted = 0,
  OxygenBottle2Exhausted,
  ReliefValveActive
};

enum class SEAnesthesiaMachineOxygenSource {
  Invalid = -1,
  Wall = 0,
  BottleOne,
  BottleTwo
};
enum class SEAnesthesiaMachinePrimaryGas {
  Invalid = -1,
  Air = 0,
  Nitrogen
};

enum class SEAnesthesiaMachineConnection {
  Invalid = -1,
  Off = 0,
  Mask,
  Tube
};
}