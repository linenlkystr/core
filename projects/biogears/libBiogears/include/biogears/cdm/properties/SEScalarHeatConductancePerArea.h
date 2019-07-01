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
class BIOGEARS_API HeatConductancePerAreaUnit : public CCompoundUnit {
public:
  HeatConductancePerAreaUnit(const char* u);
  HeatConductancePerAreaUnit(const std::string& u);

  virtual ~HeatConductancePerAreaUnit() = default;

  static bool IsValidUnit(const char* unit);
  static bool IsValidUnit(const std::string& unit);
  static const HeatConductancePerAreaUnit& GetCompoundUnit(const char* unit);
  static const HeatConductancePerAreaUnit& GetCompoundUnit(const std::string& unit);

  static const HeatConductancePerAreaUnit W_Per_m2_K;
  static const HeatConductancePerAreaUnit W_Per_m2_C;
  static const HeatConductancePerAreaUnit BTU_Per_hr_ft2_C;
};

class BIOGEARS_API SEScalarHeatConductancePerArea : public SEScalarQuantity<HeatConductancePerAreaUnit> {
friend io::Property;
public:
  SEScalarHeatConductancePerArea() = default;
  virtual ~SEScalarHeatConductancePerArea() = default;
};
}