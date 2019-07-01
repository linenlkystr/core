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
#include <biogears/cdm/properties/SEScalarQuantity.h>

namespace biogears {
class BIOGEARS_API VolumeUnit : public CCompoundUnit {
public:
  VolumeUnit(const char* u);
  VolumeUnit(const std::string& u);

  virtual ~VolumeUnit() = default;

  static bool IsValidUnit(const char* unit);
  static bool IsValidUnit(const std::string& unit);
  static const VolumeUnit& GetCompoundUnit(const char* unit);
  static const VolumeUnit& GetCompoundUnit(const std::string& unit);

  static const VolumeUnit L;
  static const VolumeUnit dL;
  static const VolumeUnit mL;
  static const VolumeUnit m3;
  static const VolumeUnit uL;
};

class BIOGEARS_API SEScalarVolume : public SEScalarQuantity<VolumeUnit> {
friend io::Property;
public:
  SEScalarVolume() = default;
  virtual ~SEScalarVolume() = default;
};
}
