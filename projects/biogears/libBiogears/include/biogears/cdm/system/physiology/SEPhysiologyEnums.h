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

#include <ostream>

namespace biogears {

enum class SEInflammationSource {
  Invalid = -1,
  Burn = 0,
  Hemorrhage,
  Pathogen
};

enum class SEHeartRhythm {
  Invalid = -1,
  Asystole = 0,
  NormalSinus
};

inline std::ostream& operator<<(std::ostream& os, const SEInflammationSource& e)
{
  switch (e) {
    case SEInflammationSource::Burn: os << "Burn"; break;
    case SEInflammationSource::Hemorrhage: os << "Hemorrhage"; break;
    case SEInflammationSource::Pathogen: os << "Pathogen"; break;
  default:
    os << "Invalid";
  }
  return os;
}
inline std::ostream& operator<<(std::ostream& os, const SEHeartRhythm& e)
{
  switch (e) {
    case SEHeartRhythm::Asystole: os << "Asystole"; break;
    case SEHeartRhythm::NormalSinus: os << "NormalSinus"; break;
  default:
    os << "Invalid";
  }
  return os;
}
}
