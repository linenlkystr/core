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
inline std::ostream& operator<<(std::ostream& os, const SEAnesthesiaMachineEvent& e)
{
  switch (e) {
  case SEAnesthesiaMachineEvent::OxygenBottle1Exhausted:
    os << "OxygenBottle1Exhausted";
    break;
  case SEAnesthesiaMachineEvent::OxygenBottle2Exhausted:
    os << "OxygenBottle2Exhausted";
    break;
  case SEAnesthesiaMachineEvent::ReliefValveActive:
    os << "ReliefValveActive";
    break;
  default:
    os << "Invalid";
  }
  return os;
}
inline std::ostream& operator<<(std::ostream& os, const SEAnesthesiaMachineOxygenSource& e)
{
  switch (e) {
  case SEAnesthesiaMachineOxygenSource::Wall:
    os << "Wall";
    break;
  case SEAnesthesiaMachineOxygenSource::BottleOne:
    os << "BottleOne";
    break;
  case SEAnesthesiaMachineOxygenSource::BottleTwo:
    os << "BottleTwo";
    break;
  default:
    os << "Invalid";
  }
  return os;
}
inline std::ostream& operator<<(std::ostream& os, const SEAnesthesiaMachinePrimaryGas& e)
{
  switch (e) {
  case SEAnesthesiaMachinePrimaryGas::Air:
    os << "Air";
    break;
  case SEAnesthesiaMachinePrimaryGas::Nitrogen:
    os << "Nitrogen";
    break;
  default:
    os << "Invalid";
  }
  return os;
}
inline std::ostream& operator<<(std::ostream& os, const SEAnesthesiaMachineConnection& e)
{
  switch (e) {
  case SEAnesthesiaMachineConnection::Off:
    os << "Off";
    break;
  case SEAnesthesiaMachineConnection::Mask:
    os << "Mask";
    break;
  case SEAnesthesiaMachineConnection::Tube:
    os << "Tube";
    break;
  default:
    os << "Invalid";
  }
  return os;
}
}