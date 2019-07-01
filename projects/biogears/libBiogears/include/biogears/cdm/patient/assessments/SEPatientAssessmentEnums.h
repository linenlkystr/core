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

enum class SEPresenceIndicator {
  Invalid = -1,
  Positive = 0,
  Negative
};
enum class SEClarityIndicator {
  Invalid = -1,
  Clear = 0,
  SlightlyCloudy,
  Cloudy,
  Turbid
};
enum class SEUrineColor {
  Invalid = -1,
  PaleYellow = 0,
  Yellow,
  DarkYellow
};
enum class SEMicroscopicObservationType {
  Invalid = -1,
  LowPowerField = 0,
  HighPowerField
};
enum class SEMicroscopicObservationAmount {
  Invalid = -1,
  Few = 0,
  Moderate,
  Many
};
}
