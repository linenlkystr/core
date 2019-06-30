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
#include <biogears/cdm/scenario/SEAction.h>


namespace biogears {
SEAction::SEAction()
  : Loggable()
{
  m_Comment = "";
}
//-----------------------------------------------------------------------------
SEAction::~SEAction()
{
  Clear();
}
//-----------------------------------------------------------------------------
void SEAction::Clear()
{
  m_Comment = "";
}
//-----------------------------------------------------------------------------
const char* SEAction::GetComment() const
{
  return m_Comment.c_str();
}
//-----------------------------------------------------------------------------
void SEAction::SetComment(const char* comment)
{
  m_Comment = comment;
}
//-----------------------------------------------------------------------------
void SEAction::SetComment(const std::string& comment)
{
  m_Comment = comment;
}
//-----------------------------------------------------------------------------
bool SEAction::HasComment() const
{
  return m_Comment.empty() ? false : true;
}
//-----------------------------------------------------------------------------
void SEAction::InvalidateComment()
{
  m_Comment = "";
}
//-----------------------------------------------------------------------------
const char* SEAction::ToString() const
{
  std::stringstream ss;
  this->ToString(ss);
  m_StringRepresnetation = ss.str();
  return m_StringRepresnetation.c_str();
}
//-----------------------------------------------------------------------------
}