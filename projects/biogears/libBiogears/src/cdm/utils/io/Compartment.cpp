#include "Compartment.h"

#include "Property.h"
#include "Substance.h"
#include "SubstanceQuantity.h"

#include <biogears/cdm/circuit/fluid/SEFluidCircuitNode.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceManager.h>

#include <biogears/cdm/compartment/SECompartment.h>
#include <biogears/cdm/compartment/SECompartmentLink.h>
#include <biogears/cdm/compartment/SECompartmentManager.h>
#include <biogears/cdm/compartment/fluid/SEFluidCompartment.h>
#include <biogears/cdm/compartment/fluid/SEFluidCompartmentLink.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartment.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartmentGraph.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartmentLink.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartment.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartmentGraph.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartmentLink.h>
#include <biogears/cdm/compartment/thermal/SEThermalCompartment.h>
#include <biogears/cdm/compartment/thermal/SEThermalCompartmentLink.h>
#include <biogears/cdm/compartment/tissue/SETissueCompartment.h>

namespace biogears {
namespace io {
  //class SECompartment
  void Compartment::Marshall(const CDM::CompartmentData& in, SECompartment& out)
  {
    out.Clear();
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SECompartment& in, CDM::CompartmentData& out)
  {
    out.Name(in.m_Name);
  }
  //----------------------------------------------------------------------------------
  //class SECompartmentLink
  void Compartment::Marshall(const CDM::CompartmentLinkData& in, SECompartmentLink& out)
  {
    out.Clear();
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SECompartmentLink& in, CDM::CompartmentLinkData& out)
  {
    out.Name(in.m_Name);
  }
  //----------------------------------------------------------------------------------
  //class SEFluidCompartment
  template <FLUID_COMPARTMENT_TEMPLATE>
  void Compartment::Marshall(const CDM::FluidCompartmentData& in, SEFluidCompartment<FLUID_COMPARTMENT_TYPES>& out, SECircuitManager* circuits)
  {
    Marshall(static_cast<const CDM::CompartmentData&>(in), static_cast<SECompartment&>(out));
    if (!in.Child().empty())
      return;
    else if (!in.Node().empty()) {
      if (circuits == nullptr) {
        throw CommonDataModelException("Compartment is mapped to circuit nodes, but no circuit manager was provided, cannot load");
      }
      for (const auto name : in.Node()) {
        SEFluidCircuitNode* node = circuits->GetFluidNode(name);
        if (node == nullptr) {
          throw CommonDataModelException("Compartment is mapped to circuit node, " + std::string{ name } + ", but provided circuit manager did not have that node");
        }
        out.MapNode(*node);
      }
    } else { // Only load these if you don't have children or nodes
      if (in.Pressure().present()) {
        io::Property::Marshall(in.Pressure(), out.GetPressure());
      }
      if (in.Volume().present()) {
        io::Property::Marshall(in.Volume(), out.GetVolume());
      }
    }
  }
  //----------------------------------------------------------------------------------
  template <FLUID_COMPARTMENT_TEMPLATE>
  void Compartment::UnMarshall(const SEFluidCompartment<FLUID_COMPARTMENT_TYPES>& in, CDM::FluidCompartmentData& out)
  {
    SECompartment::Unload(data);
    for (auto child : in.m_FluidChildren) {
      out.Child().push_back(child->GetName());
    }
    for (auto nodes : in.m_Nodes.GetNodes()) {
      out.Node().push_back(nodes->GetName());
    }
    // Even if you have children or nodes, I am unloading everything, this makes the xml actually usefull...
    if (in.HasInFlow()) {
      io::Property::UnMarshall(in.GetInFlow(), out.InFlow());
    }
    if (in.HasOutFlow()) {
      io::Property::UnMarshall(in.GetOutFlow(), out.OutFlow());
    }
    if (in.HasPressure()) {
      io::Property::UnMarshall(in.GetPressure(), out.Pressure());
    }
    if (in.HasVolume()) {
      io::Property::UnMarshall(in.GetVolume(), out.Volume());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEFluidCompartmentLink

  template <FLUID_COMPARTMENT_LINK_TEMPLATE>
  void Compartment::Marshall(const CDM::FluidCompartmentLinkData& in, SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>& out, SECircuitManager* circuits)
  {
    Marshall(static_cast<const CDM::CompartmentLinkData&>(in), static_cast<SECompartmentLink&>(out));
    if (in.Path().present()) {
      if (circuits == nullptr) {
        throw CommonDataModelException("Link is mapped to circuit path, " + std::string{ in.Path().get() } + ", but no circuit manager was provided, cannot load");
      }
      SEFluidCircuitPath* path = circuits->GetFluidPath(in.Path().get());
      if (path == nullptr) {
        throw CommonDataModelException("Link is mapped to circuit path, " + std::string{ in.Path().get() } + ", but provided circuit manager did not have that path");
      }
      out.MapPath(*path);
    } else {
      if (in.Flow().present())
        io::Property::Marshall(in.Flow(), GetFlow());
    }
  }
  //----------------------------------------------------------------------------------
  template <FLUID_COMPARTMENT_LINK_TEMPLATE>
  void Compartment::UnMarshall(const SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>& in, CDM::FluidCompartmentLinkData& out)
  {
    UnMarshall(static_cast<const SECompartmentLink&>(in), static_cast<CDM::CompartmentLinkData&>(out));
    out.SourceCompartment(in.m_SourceCmpt.GetName());
    out.TargetCompartment(in.m_TargetCmpt.GetName());
    if (in.m_Path != nullptr)
      out.Path(in.m_Path->GetName());
    // Even if you have a path, I am unloading everything, this makes the xml actually usefull...
    if (in.HasFlow())
      io::Property::UnMarshall(GetFlow(), out.Flow());
  }
  //----------------------------------------------------------------------------------
  //class SEGasCompartment
  void Compartment::Marshall(const CDM::GasCompartmentData& in, SEGasCompartment& out, SESubstanceManager& subMgr, SECircuitManager* circuits)
  {
    Marshall(static_cast<const CDM::FluidCompartmentData>(in), static_cast<SEFluidCompartment<SEGasCompartmentLink, SEGasTransportVertex, SEGasTransportSubstance, SEGasSubstanceQuantity>&>(out), circuits);
    if (in.Child().empty()) {
      for (const CDM::GasSubstanceQuantityData& d : in.SubstanceQuantity()) {
        SESubstance* sub = subMgr.GetSubstance(d.Substance());
        if (sub == nullptr) {
          throw CommonDataModelException("Could not find a substance for " + std::string{ d.Substance() });
        }
        io::SubstanceQuantity::Marshall(d, out.CreateSubstanceQuantity(*sub));
        ;
      }
    }
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SEGasCompartment& in, CDM::GasCompartmentData& out)
  {
    UnMarshall(static_cast<const SEFluidCompartment<SEGasCompartmentLink, SEGasTransportVertex, SEGasTransportSubstance, SEGasSubstanceQuantity>&>(in), static_cast<CDM::FluidCompartmentData&>(out));
    for (SEGasSubstanceQuantity* subQ : in.m_SubstanceQuantities) {
      auto gsqData = CDM::GasSubstanceQuantityData();
      io::SubstanceQuantity::UnMarshall(*subQ, gsqData);
      out.SubstanceQuantity().push_back(gsqData);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEGasCompartmentLink
  void Compartment::Marshall(const CDM::GasCompartmentLinkData& in, SEGasCompartmentLink& out)
  {
    Marshall(static_cast<const CDM::CompartmentLinkData&>(in), static_cast<SECompartmentLink&>(out));
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SEGasCompartmentLink& in, CDM::GasCompartmentLinkData& out)
  {
    UnMarshall(static_cast<const SECompartmentLink&>(in), static_cast<CDM::GasCompartmentLinkData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEGasCompartmentGraph
  void Compartment::Marshall(const CDM::GasCompartmentGraphData& in, SEGasCompartmentGraph& out, SECompartmentManager& cmptMgr)
  {
    out.m_Name = in.Name();
    for (auto name : in.Compartment()) {
      SEGasCompartment* cmpt = cmptMgr.GetGasCompartment(name);
      if (cmpt == nullptr) {
        throw CommonDataModelException("Could not find compartment " + std::string{ name } + " for graph " + out.m_Name);
      }
      out.AddCompartment(*cmpt);
    }
    for (auto name : in.Link()) {
      SEGasCompartmentLink* link = cmptMgr.GetGasLink(name);
      if (link == nullptr) {
        throw CommonDataModelException("Could not find link " + std::string{ name } + " for graph " + out.m_Name);
      }
      out.AddLink(*link);
    }
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SEGasCompartmentGraph& in, CDM::GasCompartmentGraphData& out)
  {
    out.Name(in.m_Name);
    for (SEGasCompartment* cmpt : in.m_Compartments)
      out.Compartment().push_back(cmpt->GetName());
    for (SEGasCompartmentLink* link : in.m_CompartmentLinks)
      out.Link().push_back(link->GetName());
  }
  //----------------------------------------------------------------------------------
  //class SELiquidCompartment
  void Compartment::Marshall(const CDM::LiquidCompartmentData& in, SELiquidCompartment& out, SESubstanceManager& subMgr, SECircuitManager* circuits)
  {

    Marshall(static_cast<const CDM::FluidCompartmentData&>(in), static_cast<SEFluidCompartment<SELiquidCompartmentLink, SELiquidTransportVertex, SELiquidTransportSubstance, SELiquidSubstanceQuantity>&>(out), circuits);
    if (in.Child().empty()) {
      for (const CDM::LiquidSubstanceQuantityData& d : in.SubstanceQuantity()) {
        SESubstance* sub = subMgr.GetSubstance(d.Substance());
        if (sub == nullptr) {
          throw CommonDataModelException("Could not find a substance for " + std::string{ d.Substance() });
        }
        io::SubstanceQuantity::Marshall(d, out.CreateSubstanceQuantity(*sub));
      }
      if (in.pH().present()) {
        io::Property::Marshall(in.pH(), out.GetPH());
      }
      if (in.WaterVolumeFraction().present()) {
        io::Property::Marshall(in.WaterVolumeFraction(), out.GetWaterVolumeFraction());
      }
    }
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SELiquidCompartment& in, CDM::LiquidCompartmentData& out)
  {
    UnMarshall(static_cast<const SEFluidCompartment<SELiquidCompartmentLink, SELiquidTransportVertex, SELiquidTransportSubstance, SELiquidSubstanceQuantity>&>(in), static_cast<CDM::FluidCompartmentData&>(out));
    for (SELiquidSubstanceQuantity* subQ : in.m_SubstanceQuantities) {
      auto lqsData = CDM::LiquidSubstanceQuantityData();
      io::SubstanceQuantity::UnMarshall(*subQ,lqsData);
      out.SubstanceQuantity().push_back(lqsData);
    }
    if (in.HasPH()) {
      io::Property::UnMarshall(in.GetPH(), out.pH());
    }
    if (in.HasWaterVolumeFraction()) {
      io::Property::UnMarshall(in.GetWaterVolumeFraction(), out.WaterVolumeFraction());
    }
  }
  //----------------------------------------------------------------------------------
  //class SELiquidCompartmentLink
  void Compartment::Marshall(const CDM::LiquidCompartmentLinkData& in, SELiquidCompartmentLink& out)
  {
    Marshall(static_cast<const CDM::FluidCompartmentLinkData&>(in), static_cast<SEFluidCompartmentLink<SELiquidTransportEdge, SELiquidTransportVertex, SELiquidCompartment>&>(out));
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SELiquidCompartmentLink& in, CDM::LiquidCompartmentLinkData& out)
  {
    UnMarshall(static_cast<const SEFluidCompartmentLink<SELiquidTransportEdge, SELiquidTransportVertex, SELiquidCompartment>&>(in), static_cast<CDM::FluidCompartmentLinkData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SELiquidCompartmentGraph
  void Compartment::Marshall(const CDM::LiquidCompartmentGraphData& in, SELiquidCompartmentGraph& out, SECompartmentManager& cmptMgr)
  {
    out.m_Name = in.Name();
    for (auto name : in.Compartment()) {
      SELiquidCompartment* cmpt = cmptMgr.GetLiquidCompartment(name);
      if (cmpt == nullptr) {
        throw CommonDataModelException("Could not find compartment " + std::string{ name } + " for graph " + out.m_Name);
        
      }
      out.AddCompartment(*cmpt);
    }
    for (auto name : in.Link()) {
      SELiquidCompartmentLink* link = cmptMgr.GetLiquidLink(name);
      if (link == nullptr) {
        throw CommonDataModelException("Could not find link " + std::string{ name } + " for graph " + out.m_Name);
  
      }
      out.AddLink(*link);
    }
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SELiquidCompartmentGraph& in, CDM::LiquidCompartmentGraphData& out)
  {
    out.Name(in.m_Name);
    for (SELiquidCompartment* cmpt : in.m_Compartments)
      out.Compartment().push_back(cmpt->GetName());
    for (SELiquidCompartmentLink* link : in.m_CompartmentLinks)
      out.Link().push_back(link->GetName());
  }
  //----------------------------------------------------------------------------------
  //class SETissueCompartment
  void Compartment::Marshall(const CDM::TissueCompartmentData& in, SETissueCompartment& out)
  {
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SETissueCompartment& in, CDM::TissueCompartmentData& out)
  {
    
  }
  //----------------------------------------------------------------------------------
  //SETissueCompartment
  void Compartment::UnMarshall(const SETissueCompartment& in, CDM::TissueCompartmentData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SEThermalCompartment
  void Compartment::Marshall(const CDM::ThermalCompartmentData& in, SEThermalCompartment& out)
  {
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SEThermalCompartment& in, CDM::ThermalCompartmentData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SEThermalCompartmentLink
  void Compartment::Marshall(const CDM::ThermalCompartmentLinkData& in, SEThermalCompartmentLink& out)
  {
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SEThermalCompartmentLink& in, CDM::ThermalCompartmentLinkData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SECompartmentManager
  void Compartment::Marshall(const CDM::CompartmentManagerData& in, SECompartmentManager& out)
  {
  }
  //----------------------------------------------------------------------------------
  void Compartment::UnMarshall(const SECompartmentManager& in, CDM::CompartmentManagerData& out)
  {
  }
  //----------------------------------------------------------------------------------
}
}