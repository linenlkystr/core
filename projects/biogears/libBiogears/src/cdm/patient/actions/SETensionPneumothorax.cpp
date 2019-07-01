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
  m_Type = SEPneumothoraxType::Invalid;
  m_Side = SESide::Invalid;
  m_Severity = nullptr;
}

SETensionPneumothorax::~SETensionPneumothorax()
{
  Clear();
}

void SETensionPneumothorax::Clear()
{
  SEPatientAction::Clear();
  m_Type = SEPneumothoraxType::Invalid;
  m_Side = SESide::Invalid;
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

SEPneumothoraxType SETensionPneumothorax::GetType() const
{
  return m_Type;
}
void SETensionPneumothorax::SetType(SEPneumothoraxType Type)
{
  m_Type = Type;
}
bool SETensionPneumothorax::HasType() const
{
  return m_Type != (SEPneumothoraxType::Invalid);
}
void SETensionPneumothorax::InvalidateType()
{
  m_Type = SEPneumothoraxType::Invalid;
}

SESide SETensionPneumothorax::GetSide() const
{
  return m_Side;
}
void SETensionPneumothorax::SetSide(SESide Side)
{
  m_Side = Side;
}
bool SETensionPneumothorax::HasSide() const
{
  return m_Side != (SESide::Invalid);
}
void SETensionPneumothorax::InvalidateSide()
{
  m_Side = SESide::Invalid;
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

void SETensionPneumothorax::ToString(std::ostream& ss) const
{
  ss << "Patient Action : Tension Pneumothorax";
  if (HasComment())
    ss << "\n\tComment: " << m_Comment;
  ss << "\n\tSeverity: ";
  HasSeverity() ? ss << *m_Severity : ss << "NaN";
  ss << "\n\tType: ";
  HasType() ? ss << GetType() : ss << "Not Set";
  ss << "\n\tSide: ";
  HasSide() ? ss << GetSide() : ss << "Not Set";
  ss << std::flush;
}
}