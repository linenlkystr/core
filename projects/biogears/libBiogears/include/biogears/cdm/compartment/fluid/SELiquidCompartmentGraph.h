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
#include <biogears/cdm/compartment/SECompartmentTransportGraph.h>
#include <biogears/cdm/substance/SESubstanceTransport.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartmentLink.h>

IO_DECL(Compartment)
namespace biogears {
class SECompartmentManager;
class BIOGEARS_API SELiquidCompartmentGraph : public SECompartmentTransportGraph<SELiquidTransportGraph, SELiquidTransportVertex, SELiquidTransportEdge, SELiquidCompartment, SELiquidCompartmentLink> {
  friend class SECompartmentManager;
  friend class io::Compartment;

protected:
  SELiquidCompartmentGraph(const char* name, Logger* logger);
  SELiquidCompartmentGraph(const std::string& name, Logger* logger);

public:
  virtual ~SELiquidCompartmentGraph() override;

  void AddGraph(SELiquidCompartmentGraph& graph);
  
protected:
  void BalanceByIntensive() override;
};
}