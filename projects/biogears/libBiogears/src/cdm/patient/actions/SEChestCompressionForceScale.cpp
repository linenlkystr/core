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

#include <biogears/cdm/patient/actions/SEChestCompressionForceScale.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarTime.h>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {
SEChestCompressionForceScale::SEChestCompressionForceScale()
  : SEChestCompression()
{
  m_ForceScale = nullptr;
  m_ForcePeriod = nullptr;
}

SEChestCompressionForceScale::~SEChestCompressionForceScale()
{
  Clear();
}

void SEChestCompressionForceScale::Clear()
{
  SEChestCompression::Clear();
  SAFE_DELETE(m_ForceScale);
  SAFE_DELETE(m_ForcePeriod);
}

bool SEChestCompressionForceScale::IsValid() const
{
  return SEChestCompression::IsValid() && HasForceScale();
}

bool SEChestCompressionForceScale::IsActive() const
{
  return IsValid() ? !m_ForceScale->IsZero() : false;
}

bool SEChestCompressionForceScale::Load(const CDM::ChestCompressionForceScaleData& in)
{
  SEChestCompression::Load(in);

  io::PropertyIoDelegate::Marshall(in.ForceScale(), GetForceScale());
  if (in.ForcePeriod().present())
    io::PropertyIoDelegate::Marshall(in.ForcePeriod(), GetForcePeriod());
  return true;
}

CDM::ChestCompressionForceScaleData* SEChestCompressionForceScale::Unload() const
{
  CDM::ChestCompressionForceScaleData* data(new CDM::ChestCompressionForceScaleData());
  Unload(*data);
  return data;
}

void SEChestCompressionForceScale::Unload(CDM::ChestCompressionForceScaleData& data) const
{
  SEChestCompression::Unload(data);
  if (m_ForceScale != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_ForceScale, data.ForceScale());
  if (m_ForcePeriod != nullptr)
    io::PropertyIoDelegate::UnMarshall(*m_ForcePeriod, data.ForcePeriod());
}

bool SEChestCompressionForceScale::HasForceScale() const
{
  return m_ForceScale == nullptr ? false : m_ForceScale->IsValid();
}
SEScalar0To1& SEChestCompressionForceScale::GetForceScale()
{
  if (m_ForceScale == nullptr)
    m_ForceScale = new SEScalar0To1();
  return *m_ForceScale;
}

bool SEChestCompressionForceScale::HasForcePeriod() const
{
  return m_ForcePeriod == nullptr ? false : m_ForcePeriod->IsValid();
}
SEScalarTime& SEChestCompressionForceScale::GetForcePeriod()
{
  if (m_ForcePeriod == nullptr)
    m_ForcePeriod = new SEScalarTime();
  return *m_ForcePeriod;
}

void SEChestCompressionForceScale::ToString(std::ostream& str) const
{
  str << "Patient Action : Chest Compression";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tForceScale: ";
  HasForceScale() ? str << *m_ForceScale : str << "NaN";
  str << "\n\tForcePeriod: ";
  HasForcePeriod() ? str << *m_ForcePeriod : str << "NaN";
  str << std::flush;
}
}