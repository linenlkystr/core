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
#include <biogears/cdm/patient/actions/SEPupillaryResponse.h>

#include <biogears/cdm/properties/SEScalarNeg1To1.h>


namespace biogears {
SEPupillaryResponse::SEPupillaryResponse(Logger* logger)
  : m_ReactivityModifier(nullptr)
  , m_ShapeModifier(nullptr)
  , m_SizeModifier(nullptr)
{
}
//-----------------------------------------------------------------------------
SEPupillaryResponse::~SEPupillaryResponse()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SEPupillaryResponse::Clear()
{
  SAFE_DELETE(m_ReactivityModifier);
  SAFE_DELETE(m_ShapeModifier);
  SAFE_DELETE(m_SizeModifier);
}
//-----------------------------------------------------------------------------
const SEScalar* SEPupillaryResponse::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-----------------------------------------------------------------------------
const SEScalar* SEPupillaryResponse::GetScalar(const std::string& name)
{
  if (name.compare("ReactivityModifier") == 0)
    return &GetReactivityModifier();
  if (name.compare("ShapeModifier") == 0)
    return &GetShapeModifier();
  if (name.compare("SizeModifier") == 0)
    return &GetSizeModifier();
  return nullptr;
}
//-----------------------------------------------------------------------------
bool SEPupillaryResponse::HasReactivityModifier() const
{
  return m_ReactivityModifier == nullptr ? false : m_ReactivityModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarNeg1To1& SEPupillaryResponse::GetReactivityModifier()
{
  if (m_ReactivityModifier == nullptr) {
    m_ReactivityModifier = new SEScalarNeg1To1();
  }

  return *m_ReactivityModifier;
}
//-----------------------------------------------------------------------------
double SEPupillaryResponse::GetReactivityModifier() const
{
  if (m_ReactivityModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_ReactivityModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SEPupillaryResponse::HasShapeModifier() const
{
  return m_ShapeModifier == nullptr ? false : m_ShapeModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarNeg1To1& SEPupillaryResponse::GetShapeModifier()
{
  if (m_ShapeModifier == nullptr) {
    m_ShapeModifier = new SEScalarNeg1To1();
  }

  return *m_ShapeModifier;
}
//-----------------------------------------------------------------------------
double SEPupillaryResponse::GetShapeModifier() const
{
  if (m_ShapeModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_ShapeModifier->GetValue();
}
//-----------------------------------------------------------------------------
bool SEPupillaryResponse::HasSizeModifier() const
{
  return m_SizeModifier == nullptr ? false : m_SizeModifier->IsValid();
}
//-----------------------------------------------------------------------------
SEScalarNeg1To1& SEPupillaryResponse::GetSizeModifier()
{
  if (m_SizeModifier == nullptr) {
    m_SizeModifier = new SEScalarNeg1To1();
  }

  return *m_SizeModifier;
}
//-----------------------------------------------------------------------------
double SEPupillaryResponse::GetSizeModifier() const
{
  if (m_SizeModifier == nullptr) {
    return SEScalar::dNaN();
  }

  return m_SizeModifier->GetValue();
}
//-----------------------------------------------------------------------------
}