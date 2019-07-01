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
#include <biogears/cdm/substance/SESubstance.h>

IO_DECL(SubstanceQuantity)

namespace biogears {
class BIOGEARS_API SESubstanceQuantity : public Loggable {
  friend class io::SubstanceQuantity;

public:
  SESubstanceQuantity(SESubstance& sub)
    : Loggable(sub.GetLogger())
    , m_Substance(sub){};

  virtual ~SESubstanceQuantity() override = default;

  virtual void Clear() = 0; //clear memory
  virtual void Invalidate() = 0;

public:
  virtual SESubstance& GetSubstance() const { return m_Substance; }

  virtual const SEScalar* GetScalar(const char* name) = 0;
  virtual const SEScalar* GetScalar(const std::string& name) = 0;

protected:
  SESubstance& m_Substance;
};
}