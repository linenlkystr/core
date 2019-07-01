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
#include <biogears/cdm/patient/actions/SETensionPneumothorax.h>

#include <biogears/cdm/properties/SEScalar0To1.h>

namespace biogears {
SETensionPneumothorax::SETensionPneumothorax()
  : SEPatientAction()
{
  m_Type = (CDM::enumPneumothoraxType::value)-1;
  m_Side = (CDM::enumSide::value)-1;
  m_Severity = nullptr;
}

SETensionPneumothorax::~SETensionPneumothorax()
{
  Clear();
}

void SETensionPneumothorax::Clear()
{
  SEPatientAction::Clear();
  m_Type = (CDM::enumPneumothoraxType::value)-1;
  m_Side = (CDM::enumSide::value)-1;
  SAFE_DELETE(m_Severity);
}

bool SETensionPneumothorax::IsValid() const
{
  return SEPatientAction::IsValid() && HasType() && HasSide() && HasSeverity();
}

bool SETensionPneumothorax::IsActive() const
{
  return IsValid();
}

CDM::enumPneumothoraxType::value SETensionPneumothorax::GetType() const
{
  return m_Type;
}
void SETensionPneumothorax::SetType(CDM::enumPneumothoraxType::value Type)
{
  m_Type = Type;
}
bool SETensionPneumothorax::HasType() const
{
  return m_Type == ((CDM::enumPneumothoraxType::value)-1) ? false : true;
}
void SETensionPneumothorax::InvalidateType()
{
  m_Type = (CDM::enumPneumothoraxType::value)-1;
}

CDM::enumSide::value SETensionPneumothorax::GetSide() const
{
  return m_Side;
}
void SETensionPneumothorax::SetSide(CDM::enumSide::value Side)
{
  m_Side = Side;
}
bool SETensionPneumothorax::HasSide() const
{
  return m_Side == ((CDM::enumSide::value)-1) ? false : true;
}
void SETensionPneumothorax::InvalidateSide()
{
  m_Side = (CDM::enumSide::value)-1;
}

bool SETensionPneumothorax::HasSeverity() const
{
  return m_Severity == nullptr ? false : m_Severity->IsValid();
}
SEScalar0To1& SETensionPneumothorax::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SETensionPneumothorax::ToString(std::ostream& str) const
{
  str << "Patient Action : Tension Pneumothorax";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity: ";
  HasSeverity() ? str << *m_Severity : str << "NaN";
  str << "\n\tType: ";
  HasType() ? str << GetType() : str << "Not Set";
  str << "\n\tSide: ";
  HasSide() ? str << GetSide() : str << "Not Set";
  str << std::flush;
}
}