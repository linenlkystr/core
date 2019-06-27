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
#include <biogears/schema/cdm/Properties.hxx>

namespace biogears {
class BIOGEARS_API PressurePerVolumeUnit : public CCompoundUnit {
public:
  PressurePerVolumeUnit(const char* u);
  PressurePerVolumeUnit(const std::string& u);

  virtual ~PressurePerVolumeUnit() = default;

  static bool IsValidUnit(const char* unit);
  static bool IsValidUnit(const std::string& unit);
  static const PressurePerVolumeUnit& GetCompoundUnit(const char* unit);
  static const PressurePerVolumeUnit& GetCompoundUnit(const std::string& unit);

  static const PressurePerVolumeUnit mmHg_Per_mL;
  static const PressurePerVolumeUnit cmH2O_Per_mL;
};

class BIOGEARS_API SEScalarPressurePerVolume : public SEScalarQuantity<PressurePerVolumeUnit> {
friend io::PropertyIoDelegate;
public:
  SEScalarPressurePerVolume() = default;
  virtual ~SEScalarPressurePerVolume() = default;
};
}
