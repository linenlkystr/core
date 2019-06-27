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
#include <biogears/cdm/system/environment/SEActiveHeating.h>

#include <biogears/cdm/properties/SEScalarArea.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
#include <biogears/cdm/substance/SESubstanceManager.h>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {
SEActiveHeating::SEActiveHeating(Logger* logger)
  : Loggable(logger)
{
  m_Power = nullptr;
  m_SurfaceArea = nullptr;
  m_SurfaceAreaFraction = nullptr;
}
//-----------------------------------------------------------------------------
SEActiveHeating::~SEActiveHeating()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SEActiveHeating::Clear()
{
  SAFE_DELETE(m_Power);
  SAFE_DELETE(m_SurfaceArea);
  SAFE_DELETE(m_SurfaceAreaFraction);
}
//-----------------------------------------------------------------------------
void SEActiveHeating::Reset()
{
  Clear();
}
//-----------------------------------------------------------------------------
const SEScalar* SEActiveHeating::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SEActiveHeating::GetScalar(const std::string& name)
{
  if (name.compare("Power") == 0)
    return &GetPower();
  if (name.compare("SurfaceArea") == 0)
    return &GetSurfaceArea();
  if (name.compare("SurfaceAreaFraction") == 0)
    return &GetSurfaceAreaFraction();
  return nullptr;
}
//-----------------------------------------------------------------------------
bool SEActiveHeating::Load(const CDM::ActiveHeatingData& in)
{
  io::PropertyIoDelegate::Marshall(in.Power(), GetPower());
  if (in.SurfaceArea().present()) {
    io::PropertyIoDelegate::Marshall(in.SurfaceArea(), GetSurfaceArea());
  }
  if (in.SurfaceAreaFraction().present()) {
    io::PropertyIoDelegate::Marshall(in.SurfaceAreaFraction(), GetSurfaceAreaFraction());
  }
  return true;
}
//-----------------------------------------------------------------------------
CDM::ActiveHeatingData* SEActiveHeating::Unload() const
{
  CDM::ActiveHeatingData* data = new CDM::ActiveHeatingData();
  Unload(*data);
  return data;
}
//-----------------------------------------------------------------------------
void SEActiveHeating::Unload(CDM::ActiveHeatingData& data) const
{
  io::PropertyIoDelegate::UnMarshall(*m_Power, data.Power());
  if (HasSurfaceArea()) {
    io::PropertyIoDelegate::UnMarshall(*m_SurfaceArea, data.SurfaceArea());
  }
  if (HasSurfaceAreaFraction()) {
    io::PropertyIoDelegate::UnMarshall(*m_SurfaceAreaFraction, data.SurfaceAreaFraction());
  }
}
//-----------------------------------------------------------------------------
bool SEActiveHeating::HasPower() const
{
  return m_Power == nullptr ? false : m_Power->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarPower& SEActiveHeating::GetPower()
{
  if (m_Power == nullptr)
    m_Power = new SEScalarPower();
  return *m_Power;
}
//-----------------------------------------------------------------------------
double SEActiveHeating::GetPower(const PowerUnit& unit) const
{
  if (m_Power == nullptr)
    return SEScalar::dNaN();
  return m_Power->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SEActiveHeating::HasSurfaceArea() const
{
  return m_SurfaceArea == nullptr ? false : m_SurfaceArea->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarArea& SEActiveHeating::GetSurfaceArea()
{
  if (m_SurfaceArea == nullptr)
    m_SurfaceArea = new SEScalarArea();
  return *m_SurfaceArea;
}
//-----------------------------------------------------------------------------
double SEActiveHeating::GetSurfaceArea(const AreaUnit& unit) const
{
  if (m_SurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceArea->GetValue(unit);
}
//-----------------------------------------------------------------------------
bool SEActiveHeating::HasSurfaceAreaFraction() const
{
  return m_SurfaceAreaFraction == nullptr ? false : m_SurfaceAreaFraction->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarFraction& SEActiveHeating::GetSurfaceAreaFraction()
{
  if (m_SurfaceAreaFraction == nullptr)
    m_SurfaceAreaFraction = new SEScalarFraction();
  return *m_SurfaceAreaFraction;
}
//-----------------------------------------------------------------------------
double SEActiveHeating::GetSurfaceAreaFraction() const
{
  if (m_SurfaceAreaFraction == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceAreaFraction->GetValue();
}
//-----------------------------------------------------------------------------
void SEActiveHeating::ToString(std::ostream& str) const
{
  str << "Active Heating :";
  str << "\n\tPower :";
  HasPower() ? str << *m_Power : str << "NaN";
  str << "\n\tSurfaceArea :";
  HasSurfaceArea() ? str << *m_SurfaceArea : str << "NaN";
  str << "\n\tSurfaceAreaFraction :";
  HasSurfaceAreaFraction() ? str << *m_SurfaceAreaFraction : str << "NaN";
  str << std::flush;
}
//-----------------------------------------------------------------------------
}