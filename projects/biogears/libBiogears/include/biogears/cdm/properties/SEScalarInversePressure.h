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
class BIOGEARS_API InversePressureUnit : public CCompoundUnit {
public:
  InversePressureUnit(const char* u);
  InversePressureUnit(const std::string& u);

  virtual ~InversePressureUnit() = default;

  static bool IsValidUnit(const char* unit);
  static bool IsValidUnit(const std::string& unit);
  static const InversePressureUnit& GetCompoundUnit(const char* unit);
  static const InversePressureUnit& GetCompoundUnit(const std::string& unit);

  static const InversePressureUnit Inverse_Pa;
  static const InversePressureUnit Inverse_mmHg;
  static const InversePressureUnit Inverse_cmH2O;
  static const InversePressureUnit Inverse_atm;
};

class BIOGEARS_API SEScalarInversePressure : public SEScalarQuantity<InversePressureUnit> {
friend io::Property;
public:
  SEScalarInversePressure() = default;
  virtual ~SEScalarInversePressure() = default;
};
}
