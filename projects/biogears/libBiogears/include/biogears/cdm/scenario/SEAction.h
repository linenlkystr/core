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
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/exports.h>

IO_DECL(Scenario)

namespace biogears {
class SESubstanceManager;

class BIOGEARS_API SEAction : public Loggable {
  friend io::Scenario;

public:
  virtual const char* classname() const = 0;

  SEAction();
  virtual ~SEAction();

  virtual void Clear(); // Deletes all members

  /** Test if the action has all data it needs */
  virtual bool IsValid() const { return true; }
  /** Actions can be turned off or on with various data combinations
  *  This method will encapsulate that logic in a single function */
  virtual bool IsActive() const { return IsValid(); }

public:
  virtual const char* GetComment() const;
  virtual void SetComment(const char* comment);
  virtual void SetComment(const std::string& comment);
  virtual bool HasComment() const;
  virtual void InvalidateComment();

  virtual void ToString(std::ostream& str) const = 0;
  virtual const char* ToString() const;
 
protected:
  std::string m_Comment;
  mutable std::string m_StringRepresnetation; //<Cached Value of the last called to ToString();
};

inline std::ostream& operator<<(std::ostream& out, const SEAction& a)
{
  a.ToString(out);
  return out;
}
}