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

#include <biogears/cdm/properties/SEScalarTimeMassPerVolume.h>

namespace biogears {
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::s_g_Per_L("s g/L");
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::min_kg_Per_L("min kg/L");
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::hr_kg_Per_L("hr kg/L");
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::s_g_Per_mL("s g/mL");
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::s_kg_Per_mL("s kg/mL");
const TimeMassPerVolumeUnit TimeMassPerVolumeUnit::min_kg_Per_uL("min kg/uL");

TimeMassPerVolumeUnit::TimeMassPerVolumeUnit(const char* u)
  : TimeMassPerVolumeUnit(std::string{ u })
{
}
//-------------------------------------------------------------------------------
TimeMassPerVolumeUnit::TimeMassPerVolumeUnit(const std::string& u)
  : CCompoundUnit(u)
{
}
//-------------------------------------------------------------------------------
CDM::ScalarTimeMassPerVolumeData* SEScalarTimeMassPerVolume::Unload() const
{
  if (!IsValid())
    return nullptr;
  CDM::ScalarTimeMassPerVolumeData* data(new CDM::ScalarTimeMassPerVolumeData());
  SEScalarQuantity::Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------
bool TimeMassPerVolumeUnit::IsValidUnit(const char* unit)
{
  if (strcmp(s_g_Per_L.GetString(), unit) == 0)
    return true;
  if (strcmp(min_kg_Per_L.GetString(), unit) == 0)
    return true;
  if (strcmp(hr_kg_Per_L.GetString(), unit) == 0)
    return true;
  if (strcmp(s_g_Per_mL.GetString(), unit) == 0)
    return true;
  if (strcmp(s_kg_Per_mL.GetString(), unit) == 0)
    return true;
  if (strcmp(min_kg_Per_uL.GetString(), unit) == 0)
    return true;
  return false;
}
//-------------------------------------------------------------------------------
bool TimeMassPerVolumeUnit::IsValidUnit(const std::string& unit)
{
  return IsValidUnit(unit.c_str());
}
//-------------------------------------------------------------------------------
const TimeMassPerVolumeUnit& TimeMassPerVolumeUnit::GetCompoundUnit(const char* unit)
{
  if (strcmp(s_g_Per_L.GetString(), unit) == 0)
    return s_g_Per_L;
  if (strcmp(min_kg_Per_L.GetString(), unit) == 0)
    return min_kg_Per_L;
  if (strcmp(hr_kg_Per_L.GetString(), unit) == 0)
    return hr_kg_Per_L;
  if (strcmp(s_g_Per_mL.GetString(), unit) == 0)
    return s_g_Per_mL;
  if (strcmp(s_kg_Per_mL.GetString(), unit) == 0)
    return s_kg_Per_mL;
  if (strcmp(min_kg_Per_uL.GetString(), unit) == 0)
    return min_kg_Per_uL;
  std::stringstream err;
  err << unit << " is not a valid TimeMassPerVolume unit";
  throw CommonDataModelException(err.str());
}
//-------------------------------------------------------------------------------
const TimeMassPerVolumeUnit& TimeMassPerVolumeUnit::GetCompoundUnit(const std::string& unit)
{
  return GetCompoundUnit(unit.c_str());
}
//-------------------------------------------------------------------------------
}