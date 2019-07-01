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

#include "../../utils/io/Property.h"
#include <biogears/cdm/circuit/fluid/SEFluidCircuitPath.h>
namespace biogears {
SEFluidCircuitPath::SEFluidCircuitPath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const char* name)
  : SECircuitPath<SEScalarVolumePerTime, SEScalarFlowResistance, SEScalarFlowCompliance, SEScalarFlowInertance, SEScalarPressure, SEScalarVolume>(src, tgt, std::string{ name })
  , m_FluidSourceNode(src)
  , m_FluidTargetNode(tgt)
{
}
SEFluidCircuitPath::SEFluidCircuitPath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name)
  : SECircuitPath<SEScalarVolumePerTime, SEScalarFlowResistance, SEScalarFlowCompliance, SEScalarFlowInertance, SEScalarPressure, SEScalarVolume>(src, tgt, name)
  , m_FluidSourceNode(src)
  , m_FluidTargetNode(tgt)
{
}
SEFluidCircuitPath::~SEFluidCircuitPath()
{
  Clear();
}

void SEFluidCircuitPath::Clear()
{
  SECircuitPath::Clear();
}

bool SEFluidCircuitPath::Load(const CDM::FluidCircuitPathData& in)
{
  SECircuitPath::Load(in);

  if (in.Resistance().present())
    io::Property::Marshall(in.Resistance(), GetResistance());
  if (in.NextResistance().present())
    io::Property::Marshall(in.NextResistance(), GetNextResistance());
  if (in.ResistanceBaseline().present())
    io::Property::Marshall(in.ResistanceBaseline(), GetResistanceBaseline());
  if (in.Compliance().present())
    io::Property::Marshall(in.Compliance(), GetCompliance());
  if (in.NextCompliance().present())
    io::Property::Marshall(in.NextCompliance(), GetNextCompliance());
  if (in.ComplianceBaseline().present())
    io::Property::Marshall(in.ComplianceBaseline(), GetComplianceBaseline());
  if (in.Inertance().present())
    io::Property::Marshall(in.Inertance(), GetInertance());
  if (in.NextInertance().present())
    io::Property::Marshall(in.NextInertance(), GetNextInertance());
  if (in.InertanceBaseline().present())
    io::Property::Marshall(in.InertanceBaseline(), GetInertanceBaseline());
  if (in.Flow().present())
    io::Property::Marshall(in.Flow(), GetFlow());
  if (in.NextFlow().present())
    io::Property::Marshall(in.NextFlow(), GetNextFlow());
  if (in.FlowSource().present())
    io::Property::Marshall(in.FlowSource(), GetFlowSource());
  if (in.NextFlowSource().present())
    io::Property::Marshall(in.NextFlowSource(), GetNextFlowSource());
  if (in.FlowSourceBaseline().present())
    io::Property::Marshall(in.FlowSourceBaseline(), GetFlowSourceBaseline());
  if (in.PressureSource().present())
    io::Property::Marshall(in.PressureSource(), GetPressureSource());
  if (in.NextPressureSource().present())
    io::Property::Marshall(in.NextPressureSource(), GetNextPressureSource());
  if (in.PressureSourceBaseline().present())
    io::Property::Marshall(in.PressureSourceBaseline(), GetPressureSourceBaseline());
  if (in.ValveBreakdownPressure().present())
    io::Property::Marshall(in.ValveBreakdownPressure(), GetValveBreakdownPressure());

  return HasValidElements();
}
CDM::FluidCircuitPathData* SEFluidCircuitPath::Unload() const
{
  CDM::FluidCircuitPathData* data = new CDM::FluidCircuitPathData();
  Unload(*data);
  return data;
}
void SEFluidCircuitPath::Unload(CDM::FluidCircuitPathData& data) const
{
  SECircuitPath::Unload(data);
  if (HasResistance())
    io::Property::UnMarshall(*m_Resistance, data.Resistance());
  if (HasNextResistance())
    io::Property::UnMarshall(*m_NextResistance, data.NextResistance());
  if (HasResistanceBaseline())
    io::Property::UnMarshall(*m_ResistanceBaseline, data.ResistanceBaseline());
  if (HasCompliance())
    io::Property::UnMarshall(*m_Capacitance, data.Compliance());
  if (HasNextCompliance())
    io::Property::UnMarshall(*m_NextCapacitance, data.NextCompliance());
  if (HasComplianceBaseline())
    io::Property::UnMarshall(*m_CapacitanceBaseline, data.ComplianceBaseline());
  if (HasInertance())
    io::Property::UnMarshall(*m_Inductance, data.Inertance());
  if (HasNextInertance())
    io::Property::UnMarshall(*m_NextInductance, data.NextInertance());
  if (HasInertanceBaseline())
    io::Property::UnMarshall(*m_InductanceBaseline, data.InertanceBaseline());
  if (HasFlow())
    io::Property::UnMarshall(*m_Flux, data.Flow());
  if (HasNextFlow())
    io::Property::UnMarshall(*m_NextFlux, data.NextFlow());
  if (HasFlowSource())
    io::Property::UnMarshall(*m_FluxSource, data.FlowSource());
  if (HasNextFlowSource())
    io::Property::UnMarshall(*m_NextFluxSource, data.NextFlowSource());
  if (HasFlowSourceBaseline())
    io::Property::UnMarshall(*m_FluxSourceBaseline, data.FlowSourceBaseline());
  if (HasPressureSource())
    io::Property::UnMarshall(*m_PotentialSource, data.PressureSource());
  if (HasNextPressureSource())
    io::Property::UnMarshall(*m_NextPotentialSource, data.NextPressureSource());
  if (HasPressureSourceBaseline())
    io::Property::UnMarshall(*m_PotentialSourceBaseline, data.PressureSourceBaseline());
  if (HasValveBreakdownPressure())
    io::Property::UnMarshall(*m_ValveBreakdownPotential, data.ValveBreakdownPressure());
}

////////////////////////////////
// Fluid Resistance Types//
////////////////////////////////

bool SEFluidCircuitPath::HasResistance() const
{
  return SECircuitPath::HasResistance();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetResistance()
{
  return SECircuitPath::GetResistance();
}
double SEFluidCircuitPath::GetResistance(const FlowResistanceUnit& unit) const
{
  if (m_Resistance == nullptr)
    return SEScalar::dNaN();
  return m_Resistance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextResistance() const
{
  return SECircuitPath::HasNextResistance();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetNextResistance()
{
  return SECircuitPath::GetNextResistance();
}
double SEFluidCircuitPath::GetNextResistance(const FlowResistanceUnit& unit) const
{
  if (m_NextResistance == nullptr)
    return SEScalar::dNaN();
  return m_NextResistance->GetValue(unit);
}
bool SEFluidCircuitPath::HasResistanceBaseline() const
{
  return SECircuitPath::HasResistanceBaseline();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetResistanceBaseline()
{
  return SECircuitPath::GetResistanceBaseline();
}
double SEFluidCircuitPath::GetResistanceBaseline(const FlowResistanceUnit& unit) const
{
  if (m_ResistanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_ResistanceBaseline->GetValue(unit);
}

//////////////////////////////////
// Fluid Capacitance Types //
//////////////////////////////////

bool SEFluidCircuitPath::HasCompliance() const
{
  return HasCapacitance();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetCompliance()
{
  return GetCapacitance();
}
double SEFluidCircuitPath::GetCompliance(const FlowComplianceUnit& unit) const
{
  if (m_Capacitance == nullptr)
    return SEScalar::dNaN();
  return m_Capacitance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextCompliance() const
{
  return HasNextCapacitance();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetNextCompliance()
{
  return GetNextCapacitance();
}
double SEFluidCircuitPath::GetNextCompliance(const FlowComplianceUnit& unit) const
{
  if (m_NextCapacitance == nullptr)
    return SEScalar::dNaN();
  return m_NextCapacitance->GetValue(unit);
}
bool SEFluidCircuitPath::HasComplianceBaseline() const
{
  return HasCapacitanceBaseline();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetComplianceBaseline()
{
  return GetCapacitanceBaseline();
}
double SEFluidCircuitPath::GetComplianceBaseline(const FlowComplianceUnit& unit) const
{
  if (m_CapacitanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_CapacitanceBaseline->GetValue(unit);
}

/////////////////////////////////
// Fluid Inductance Types //
/////////////////////////////////

bool SEFluidCircuitPath::HasInertance() const
{
  return HasInductance();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetInertance()
{
  return GetInductance();
}
double SEFluidCircuitPath::GetInertance(const FlowInertanceUnit& unit) const
{
  if (m_Inductance == nullptr)
    return SEScalar::dNaN();
  return m_Inductance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextInertance() const
{
  return HasNextInductance();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetNextInertance()
{
  return GetNextInductance();
}
double SEFluidCircuitPath::GetNextInertance(const FlowInertanceUnit& unit) const
{
  if (m_NextInductance == nullptr)
    return SEScalar::dNaN();
  return m_NextInductance->GetValue(unit);
}
bool SEFluidCircuitPath::HasInertanceBaseline() const
{
  return HasInductanceBaseline();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetInertanceBaseline()
{
  return GetInductanceBaseline();
}
double SEFluidCircuitPath::GetInertanceBaseline(const FlowInertanceUnit& unit) const
{
  if (m_InductanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_InductanceBaseline->GetValue(unit);
}

///////////////////////////
// Fluid Flux Types //
///////////////////////////
bool SEFluidCircuitPath::HasFlow() const
{
  return HasFlux();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlow()
{
  return GetFlux();
}
double SEFluidCircuitPath::GetFlow(const VolumePerTimeUnit& unit) const
{
  if (m_Flux == nullptr)
    return SEScalar::dNaN();
  return m_Flux->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextFlow() const
{
  return HasNextFlux();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetNextFlow()
{
  return GetNextFlux();
}
double SEFluidCircuitPath::GetNextFlow(const VolumePerTimeUnit& unit) const
{
  if (m_NextFlux == nullptr)
    return SEScalar::dNaN();
  return m_NextFlux->GetValue(unit);
}
bool SEFluidCircuitPath::HasFlowSource() const
{
  return HasFluxSource();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlowSource()
{
  return GetFluxSource();
}
double SEFluidCircuitPath::GetFlowSource(const VolumePerTimeUnit& unit) const
{
  if (m_FluxSource == nullptr)
    return SEScalar::dNaN();
  return m_FluxSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextFlowSource() const
{
  return HasNextFluxSource();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetNextFlowSource()
{
  return GetNextFluxSource();
}
double SEFluidCircuitPath::GetNextFlowSource(const VolumePerTimeUnit& unit) const
{
  if (m_NextFluxSource == nullptr)
    return SEScalar::dNaN();
  return m_NextFluxSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasFlowSourceBaseline() const
{
  return HasFluxSourceBaseline();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlowSourceBaseline()
{
  return GetFluxSourceBaseline();
}
double SEFluidCircuitPath::GetFlowSourceBaseline(const VolumePerTimeUnit& unit) const
{
  if (m_FluxSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_FluxSourceBaseline->GetValue(unit);
}

////////////////////////////////
// Fluid Potential Types //
////////////////////////////////
bool SEFluidCircuitPath::HasPressureSource() const
{
  return HasPotentialSource();
}
SEScalarPressure& SEFluidCircuitPath::GetPressureSource()
{
  return GetPotentialSource();
}
double SEFluidCircuitPath::GetPressureSource(const PressureUnit& unit) const
{
  if (m_PotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextPressureSource() const
{
  return HasNextPotentialSource();
}
SEScalarPressure& SEFluidCircuitPath::GetNextPressureSource()
{
  return GetNextPotentialSource();
}
double SEFluidCircuitPath::GetNextPressureSource(const PressureUnit& unit) const
{
  if (m_NextPotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_NextPotentialSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasPressureSourceBaseline() const
{
  return HasPotentialSourceBaseline();
}
SEScalarPressure& SEFluidCircuitPath::GetPressureSourceBaseline()
{
  return GetPotentialSourceBaseline();
}
double SEFluidCircuitPath::GetPressureSourceBaseline(const PressureUnit& unit) const
{
  if (m_PotentialSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSourceBaseline->GetValue(unit);
}
bool SEFluidCircuitPath::HasValveBreakdownPressure() const
{
  return HasValveBreakdownPotential();
}
SEScalarPressure& SEFluidCircuitPath::GetValveBreakdownPressure()
{
  return GetValveBreakdownPotential();
}
double SEFluidCircuitPath::GetValveBreakdownPressure(const PressureUnit& unit) const
{
  if (m_ValveBreakdownPotential == nullptr)
    return SEScalar::dNaN();
  return m_ValveBreakdownPotential->GetValue(unit);
}
}