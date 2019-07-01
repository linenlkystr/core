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
enum class SESubstanceState {
  Invalid = -1,
  Anesthetic = 0,
  Antibiotic,
  Ion,
  Opioid,
  ReversalAgent,
  Sedative
};
enum class SESubstanceIonicState {
  Invalid = -1,
  WeakBase = 0,
  Base,
  Acid,
  Neutral
};
enum class SESubstanceBindingProtein {
  Invalid = -1,
  Albumin = 0,
  Lipoprotein,
  AAG
};
enum class SECharge {
  Invalid = -1,
  Positive = 0,
  Negative,
  Neutral
};
enum class SESubstanceClass {
  Invalid = -1,
  Anesthetic = 0,
  Antibiotic,
  Ion,
  Opioid,
  ReversalAgent,
  Sedative
};
}