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
#include <biogears/cdm/patient/actions/SEBurnWound.h>

#include <biogears/cdm/properties/SEScalarTypes.h>
#include <biogears/schema/cdm/PatientActions.hxx>

#include "../../utils/io/PropertyIoDelegate.h"
namespace biogears {

SEBurnWound::SEBurnWound()
  : SEPatientAction()
{
  m_Inflammation = false; //When the burn wound is constructed, the corresponding inflammation state has not been established
  m_TBSA = nullptr; //User input, size of wound measured by total body surface area
}

SEBurnWound::~SEBurnWound()
{
  Clear();
}

void SEBurnWound::Clear()
{
  SEPatientAction::Clear();
  m_Inflammation = false;
  SAFE_DELETE(m_TBSA);
}

bool SEBurnWound::IsValid() const
{
  return SEPatientAction::IsValid() && HasTotalBodySurfaceArea();
}

bool SEBurnWound::IsActive() const
{
  return IsValid() ? !(m_TBSA->GetValue() < ZERO_APPROX) : false;
}

bool SEBurnWound::HasTotalBodySurfaceArea() const
{
  return m_TBSA == nullptr ? false : m_TBSA->IsValid();
}

SEScalar0To1& SEBurnWound::GetTotalBodySurfaceArea()
{
  if (m_TBSA == nullptr)
    m_TBSA = new SEScalar0To1();
  return *m_TBSA;
}

bool SEBurnWound::HasInflammation() const
{
  return m_Inflammation;
}

void SEBurnWound::SetInflammation(bool activate)
{
  m_Inflammation = activate;
}

void SEBurnWound::ToString(std::ostream& str) const
{
  str << "Patient Action : Burn Wound";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tTotal Body Surface Area:  ";
  str << *m_TBSA;
  str << std::flush;
}
}