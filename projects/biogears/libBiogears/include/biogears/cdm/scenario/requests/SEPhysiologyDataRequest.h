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
#include <biogears/cdm/scenario/requests/SEDataRequest.h>

IO_DECL(Scenario)
namespace biogears {
class SEDataRequestManager;

class BIOGEARS_API SEPhysiologyDataRequest : public SEDataRequest {
  friend class SEDataRequestManager;
  friend class io::Scenario;

protected:
  SEPhysiologyDataRequest(const SEDecimalFormat* dfault = nullptr);

public:
  virtual ~SEPhysiologyDataRequest();

  virtual void Clear(); //clear memory


public:
protected:
};
}