/**************************************************************************************
Copyright 2019 Applied Research Associates, Inc.
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
#include <memory>

#include "biogears/cdm/CommonDataModel.h"
#include <biogears/exports.h>

#include <biogears/cdm/circuit/SECircuit.h>
#include <biogears/cdm/circuit/SECircuitNode.h>
#include <biogears/cdm/circuit/SECircuitPath.h>
#include <biogears/schema/cdm/Circuit.hxx>

namespace biogears {
template <CIRCUIT_TEMPLATE>
class SECircuit;
template <CIRCUIT_NODE_TEMPLATE>
class SECircuitNode;
template <CIRCUIT_PATH_TEMPLATE>
class SECircuitPath;
class SEElectricalCircuit;
class SEElectricalCircuitNode;
class SEElectricalCircuitPath;
class SEFluidCircuit;
class SEFluidCircuitNode;
class SEFluidCircuitPath;
class SEThermalCircuit;
class SEThermalCircuitNode;
class SEThermalCircuitPath;
class SECircuitManager;

#define CDM_CIRCUIT_UNMARSHAL_HELPER(xsd, func)                                      \
  if (m_##func) {                                                                    \
    xsd.func(std::make_unique<std::remove_reference<decltype(xsd.func())>::type>()); \
    io::PropertyIoDelegate::UnMarshall(*m_##func, xsd.func());                       \
  }
namespace io {
  class BIOGEARS_PRIVATE_API CircuitIoDelegate {
  public:
    //template <typename SE, typename XSD>  option
    template <typename SE, typename XSD>
    static void Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out);
    template <typename SE, typename XSD>
    static void UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out);
    //class SECircuit
    template <CIRCUIT_TEMPLATE>
    static void Marshall(const CDM::CircuitData& in, SECircuit<CIRCUIT_TYPES>& out);
    template <CIRCUIT_TEMPLATE>
    static void UnMarshall(const SECircuit<CIRCUIT_TYPES>& in, CDM::CircuitData& out);
    //class SECircuitNode
    template <CIRCUIT_NODE_TEMPLATE>
    static void Marshall(const CDM::CircuitNodeData& in, SECircuitNode<CIRCUIT_NODE_TYPES>& out);
    template <CIRCUIT_NODE_TEMPLATE>
    static void UnMarshall(const SECircuitNode<CIRCUIT_NODE_TYPES>& in, CDM::CircuitNodeData& out);
    //class SECircuitPath
    template <CIRCUIT_PATH_TEMPLATE>
    static void Marshall(const CDM::CircuitPathData& in, SECircuitPath<CIRCUIT_PATH_TYPES>& out);
    template <CIRCUIT_PATH_TEMPLATE>
    static void UnMarshall(const SECircuitPath<CIRCUIT_PATH_TYPES>& in, CDM::CircuitPathData& out);
    //class SEElectricalCircuit
    static void Marshall(const CDM::ElectricalCircuitData& in, SEElectricalCircuit& out);
    static void UnMarshall(const SEElectricalCircuit& in, CDM::ElectricalCircuitData& out);
    //class SEElectricalCircuitNode
    static void Marshall(const CDM::ElectricalCircuitNodeData& in, SEElectricalCircuitNode& out);
    static void UnMarshall(const SEElectricalCircuitNode& in, CDM::ElectricalCircuitNodeData& out);
    //class SEElectricalCircuitPath
    static void Marshall(const CDM::ElectricalCircuitPathData& in, SEElectricalCircuitPath& out);
    static void UnMarshall(const SEElectricalCircuitPath& in, CDM::ElectricalCircuitPathData& out);
    //class SEFluidCircuit
    static void Marshall(const CDM::FluidCircuitData& in, SEFluidCircuit& out);
    static void UnMarshall(const SEFluidCircuit& in, CDM::FluidCircuitData& out);
    //class SEFluidCircuitNode
    static void Marshall(const CDM::FluidCircuitNodeData& in, SEFluidCircuitNode& out);
    static void UnMarshall(const SEFluidCircuitNode& in, CDM::FluidCircuitNodeData& out);
    //class SEFluidCircuitPath
    static void Marshall(const CDM::FluidCircuitPathData& in, SEFluidCircuitPath& out);
    static void UnMarshall(const SEFluidCircuitPath& in, CDM::FluidCircuitPathData& out);
    //class SEThermalCircuit
    static void Marshall(const CDM::ThermalCircuitData& in, SEThermalCircuit& out);
    static void UnMarshall(const SEThermalCircuit& in, CDM::ThermalCircuitData& out);
    //class SEThermalCircuitNode
    static void Marshall(const CDM::ThermalCircuitNodeData& in, SEThermalCircuitNode& out);
    static void UnMarshall(const SEThermalCircuitNode& in, CDM::ThermalCircuitNodeData& out);
    //class SEThermalCircuitPath
    static void Marshall(const CDM::ThermalCircuitPathData& in, SEThermalCircuitPath& out);
    static void UnMarshall(const SEThermalCircuitPath& in, CDM::ThermalCircuitPathData& out);
    //class SECircuitManager
    static void Marshall(const CDM::CircuitManagerData& in, SECircuitManager& out);
    static void UnMarshall(const SECircuitManager& in, CDM::CircuitManagerData& out);
  };
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void CircuitIoDelegate::Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out)
  {
    if (!option_in.present()) {
      out.Invalidate();
    } else {
      Marshall(option_in.get(), out);
    }
  }
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void CircuitIoDelegate::UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out)
  {
    auto item = std::make_unique<XSD>();
    UnMarshall(in, *item);
    option_out.set(*item);
  }
  //class SECircuit
  template <CIRCUIT_TEMPLATE>
  void CircuitIoDelegate::Marshall(const CDM::CircuitData& in, SECircuit<CIRCUIT_TYPES>& out)
  {
  }
  //----------------------------------------------------------------------------------
  template <CIRCUIT_TEMPLATE>
  void CircuitIoDelegate::UnMarshall(const SECircuit<CIRCUIT_TYPES>& in, CDM::CircuitData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SECircuitNode
  template <CIRCUIT_NODE_TEMPLATE>
  void CircuitIoDelegate::Marshall(const CDM::CircuitNodeData& in, SECircuitNode<CIRCUIT_NODE_TYPES>& out)
  {
  }
  //----------------------------------------------------------------------------------
  template <CIRCUIT_NODE_TEMPLATE>
  void CircuitIoDelegate::UnMarshall(const SECircuitNode<CIRCUIT_NODE_TYPES>& in, CDM::CircuitNodeData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SECircuitPath
  template <CIRCUIT_PATH_TEMPLATE>
  void CircuitIoDelegate::Marshall(const CDM::CircuitPathData& in, SECircuitPath<CIRCUIT_PATH_TYPES>& out)
  {
  }
  //----------------------------------------------------------------------------------
  template <CIRCUIT_PATH_TEMPLATE>
  void CircuitIoDelegate::UnMarshall(const SECircuitPath<CIRCUIT_PATH_TYPES>& in, CDM::CircuitPathData& out)
  {
  }
  //----------------------------------------------------------------------------------
} // Namespace IO
} //Namespace Biogears
