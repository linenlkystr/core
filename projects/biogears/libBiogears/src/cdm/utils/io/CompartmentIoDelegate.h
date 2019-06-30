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

#include <biogears/schema/cdm/Compartment.hxx>

namespace biogears {

class SECompartment;
class SECompartmentLink;
class SECompartmentGraph;
class SEFluidCompartment;
class SEFluidCompartmentLink;
class SEFluidCompartmentGraph;
class SEGasCompartment;
class SEGasCompartmentLink;
class SEGasCompartmentGraph;
class SELiquidCompartment;
class SELiquidCompartmentLink;
class SELiquidCompartmentGraph;
class SETissueCompartment;
class SEThermalCompartment;
class SEThermalCompartmentLink;
class SEElectricalCompartment;
class SEElectricalCompartmentLink;
class SECompartmentManager;

#define CDM_COMPARTMENT_UNMARSHAL_HELPER(xsd, func)                                      \
  if (m_##func) {                                                                    \
    xsd.func(std::make_unique<std::remove_reference<decltype(xsd.func())>::type>()); \
    io::PropertyIoDelegate::UnMarshall(*m_##func, xsd.func());                       \
  }
namespace io {
  class BIOGEARS_PRIVATE_API CompartmentIoDelegate {
  public:
    //template <typename SE, typename XSD>  option
    template <typename SE, typename XSD>
    static void Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out);
    template <typename SE, typename XSD>
    static void UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out);
    //class SECompartment
    static void Marshall(const CDM::CompartmentData& in, SECompartment& out);
    static void UnMarshall(const SECompartment& in, CDM::CompartmentData& out);
    //class SECompartmentLink
    static void Marshall(const CDM::CompartmentLinkData& in, SECompartmentLink& out);
    static void UnMarshall(const SECompartmentLink& in, CDM::CompartmentLinkData& out);
    //class SECompartmentGraph
    static void Marshall(const CDM::CompartmentGraphData& in, SECompartmentGraph& out);
    static void UnMarshall(const SECompartmentGraph& in, CDM::CompartmentGraphData& out);
    //class SEFluidCompartment
    static void Marshall(const CDM::FluidCompartmentData& in, SEFluidCompartment& out);
    static void UnMarshall(const SEFluidCompartment& in, CDM::FluidCompartmentData& out);
    //class SEFluidCompartmentLink
    static void Marshall(const CDM::FluidCompartmentLinkData& in, SEFluidCompartmentLink& out);
    static void UnMarshall(const SEFluidCompartmentLink& in, CDM::FluidCompartmentLinkData& out);
    //class SEFluidCompartmentGraph
    static void Marshall(const CDM::FluidCompartmentGraphData& in, SEFluidCompartmentGraph& out);
    static void UnMarshall(const SEFluidCompartmentGraph& in, CDM::FluidCompartmentGraphData& out);
    //class SEGasCompartment
    static void Marshall(const CDM::DecimalFormatData& in, SEGasCompartment& out);
    static void UnMarshall(const SEGasCompartment& in, CDM::DecimalFormatData& out);
    //class SEGasCompartmentLink
    static void Marshall(const CDM::GasCompartmentLinkData& in, SEGasCompartmentLink& out);
    static void UnMarshall(const SEGasCompartmentLink& in, CDM::GasCompartmentLinkData& out);
    //class SEGasCompartmentGraph
    static void Marshall(const CDM::GasCompartmentGraphData& in, SEGasCompartmentGraph& out);
    static void UnMarshall(const SEGasCompartmentGraph& in, CDM::GasCompartmentGraphData& out);
    //class SELiquidCompartment
    static void Marshall(const CDM::DecimalFormatData& in, SELiquidCompartment& out);
    static void UnMarshall(const SELiquidCompartment& in, CDM::DecimalFormatData& out);
    //class SELiquidCompartmentLink
    static void Marshall(const CDM::DecimalFormatData& in, SELiquidCompartmentLink& out);
    static void UnMarshall(const SELiquidCompartmentLink& in, CDM::DecimalFormatData& out);
    //class SELiquidCompartmentGraph
    static void Marshall(const CDM::LiquidCompartmentGraphData& in, SELiquidCompartmentGraph& out);
    static void UnMarshall(const SELiquidCompartmentGraph& in, CDM::LiquidCompartmentGraphData& out);
    //class SETissueCompartment
    static void Marshall(const CDM::TissueCompartmentData& in, SETissueCompartment& out);
    static void UnMarshall(const SETissueCompartment& in, CDM::TissueCompartmentData& out);
    //class SEThermalCompartment
    static void Marshall(const CDM::ThermalCompartmentData& in, SEThermalCompartment& out);
    static void UnMarshall(const SEThermalCompartment& in, CDM::ThermalCompartmentData& out);
    //class SEThermalCompartmentLink
    static void Marshall(const CDM::ThermalCompartmentLinkData& in, SEThermalCompartmentLink& out);
    static void UnMarshall(const SEThermalCompartmentLink& in, CDM::ThermalCompartmentLinkData& out);
    //class SEElectricalCompartment
    static void Marshall(const CDM::ElectricalCompartmentData& in, SEElectricalCompartment& out);
    static void UnMarshall(const SEElectricalCompartment& in, CDM::ElectricalCompartmentData& out);
    //class SEElectricalCompartmentLink
    static void Marshall(const CDM::ElectricalCompartmentLinkData& in, SEElectricalCompartmentLink& out);
    static void UnMarshall(const SEElectricalCompartmentLink& in, CDM::ElectricalCompartmentLinkData& out);
    //class SECompartmentManager
    static void Marshall(const CDM::CompartmentManagerData& in, SECompartmentManager& out);
    static void UnMarshall(const SECompartmentManager& in, CDM::CompartmentManagerData& out);
  };
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void CompartmentIoDelegate::Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out)
  {
    if (!option_in.present()) {
      out.Invalidate();
    } else {
      Marshall(option_in.get(), out);
    }
  }
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void CompartmentIoDelegate::UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out)
  {
    auto item = std::make_unique<XSD>();
    UnMarshall(in, *item);
    option_out.set(*item);
  }
} // Namespace IO
} //Namespace Biogears
