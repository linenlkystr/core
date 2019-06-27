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

#include "../../utils/io/PropertyIoDelegate.h"
#include <biogears/cdm/circuit/electrical/SEElectricalCircuitPath.h>
namespace biogears {
SEElectricalCircuitPath::SEElectricalCircuitPath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const char* name)
  : SECircuitPath<SEScalarElectricCurrent, SEScalarElectricResistance, SEScalarElectricCapacitance, SEScalarElectricInductance, SEScalarElectricPotential, SEScalarElectricCharge>(src, tgt, name)
  , m_ElectricalSourceNode(src)
  , m_ElectricalTargetNode(tgt)
{
}
SEElectricalCircuitPath::SEElectricalCircuitPath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name)
  : SECircuitPath<SEScalarElectricCurrent, SEScalarElectricResistance, SEScalarElectricCapacitance, SEScalarElectricInductance, SEScalarElectricPotential, SEScalarElectricCharge>(src, tgt, name)
  , m_ElectricalSourceNode(src)
  , m_ElectricalTargetNode(tgt)
{
}
SEElectricalCircuitPath::~SEElectricalCircuitPath()
{
}

void SEElectricalCircuitPath::Clear()
{
  SECircuitPath::Clear();
}

bool SEElectricalCircuitPath::Load(const CDM::ElectricalCircuitPathData& in)
{
  SECircuitPath::Load(in);
  if (in.Resistance().present())
    io::PropertyIoDelegate::Marshall(in.Resistance(), GetResistance());
  if (in.NextResistance().present())
    io::PropertyIoDelegate::Marshall(in.NextResistance(), GetNextResistance());
  if (in.ResistanceBaseline().present())
    io::PropertyIoDelegate::Marshall(in.ResistanceBaseline(), GetResistanceBaseline());
  if (in.Capacitance().present())
    io::PropertyIoDelegate::Marshall(in.Capacitance(), GetCapacitance());
  if (in.NextCapacitance().present())
    io::PropertyIoDelegate::Marshall(in.NextCapacitance(), GetNextCapacitance());
  if (in.CapacitanceBaseline().present())
    io::PropertyIoDelegate::Marshall(in.CapacitanceBaseline(), GetCapacitanceBaseline());
  if (in.Inductance().present())
    io::PropertyIoDelegate::Marshall(in.Inductance(), GetInductance());
  if (in.NextInductance().present())
    io::PropertyIoDelegate::Marshall(in.NextInductance(), GetNextInductance());
  if (in.InductanceBaseline().present())
    io::PropertyIoDelegate::Marshall(in.InductanceBaseline(), GetInductanceBaseline());
  if (in.Current().present())
    io::PropertyIoDelegate::Marshall(in.Current(), GetCurrent());
  if (in.NextCurrent().present())
    io::PropertyIoDelegate::Marshall(in.NextCurrent(), GetNextCurrent());
  if (in.CurrentSource().present())
    io::PropertyIoDelegate::Marshall(in.CurrentSource(), GetCurrentSource());
  if (in.NextCurrentSource().present())
    io::PropertyIoDelegate::Marshall(in.NextCurrentSource(), GetNextCurrentSource());
  if (in.CurrentSourceBaseline().present())
    io::PropertyIoDelegate::Marshall(in.CurrentSourceBaseline(), GetCurrentSourceBaseline());
  if (in.VoltageSource().present())
    io::PropertyIoDelegate::Marshall(in.VoltageSource(), GetVoltageSource());
  if (in.NextVoltageSource().present())
    io::PropertyIoDelegate::Marshall(in.NextVoltageSource(), GetNextVoltageSource());
  if (in.VoltageSourceBaseline().present())
    io::PropertyIoDelegate::Marshall(in.VoltageSourceBaseline(), GetVoltageSourceBaseline());
  if (in.ValveBreakdownVoltage().present())
    io::PropertyIoDelegate::Marshall(in.ValveBreakdownVoltage(), GetValveBreakdownVoltage());

  return HasValidElements();
}
CDM::ElectricalCircuitPathData* SEElectricalCircuitPath::Unload() const
{
  CDM::ElectricalCircuitPathData* data = new CDM::ElectricalCircuitPathData();
  Unload(*data);
  return data;
}
void SEElectricalCircuitPath::Unload(CDM::ElectricalCircuitPathData& data) const
{
  SECircuitPath::Unload(data);
  if (HasResistance())
    io::PropertyIoDelegate::UnMarshall(*m_Resistance, data.Resistance());
  if (HasNextResistance())
    io::PropertyIoDelegate::UnMarshall(*m_NextResistance, data.NextResistance());
  if (HasResistanceBaseline())
    io::PropertyIoDelegate::UnMarshall(*m_ResistanceBaseline, data.ResistanceBaseline());
  if (HasCapacitance())
    io::PropertyIoDelegate::UnMarshall(*m_Capacitance, data.Capacitance());
  if (HasNextCapacitance())
    io::PropertyIoDelegate::UnMarshall(*m_NextCapacitance, data.NextCapacitance());
  if (HasCapacitanceBaseline())
    io::PropertyIoDelegate::UnMarshall(*m_CapacitanceBaseline, data.CapacitanceBaseline());
  if (HasInductance())
    io::PropertyIoDelegate::UnMarshall(*m_Inductance, data.Inductance());
  if (HasNextInductance())
    io::PropertyIoDelegate::UnMarshall(*m_NextInductance, data.NextInductance());
  if (HasInductanceBaseline())
    io::PropertyIoDelegate::UnMarshall(*m_InductanceBaseline, data.InductanceBaseline());
  if (HasCurrent())
    io::PropertyIoDelegate::UnMarshall(*m_Flux, data.Current());
  if (HasNextCurrent())
    io::PropertyIoDelegate::UnMarshall(*m_NextFlux, data.NextCurrent());
  if (HasCurrentSource())
    io::PropertyIoDelegate::UnMarshall(*m_FluxSource, data.CurrentSource());
  if (HasNextCurrentSource())
    io::PropertyIoDelegate::UnMarshall(*m_NextFluxSource, data.NextCurrentSource());
  if (HasCurrentSourceBaseline())
    io::PropertyIoDelegate::UnMarshall(*m_FluxSourceBaseline, data.CurrentSourceBaseline());
  if (HasVoltageSource())
    io::PropertyIoDelegate::UnMarshall(*m_PotentialSource, data.VoltageSource());
  if (HasNextVoltageSource())
    io::PropertyIoDelegate::UnMarshall(*m_NextPotentialSource, data.NextVoltageSource());
  if (HasVoltageSourceBaseline())
    io::PropertyIoDelegate::UnMarshall(*m_PotentialSourceBaseline, data.VoltageSourceBaseline());
  if (HasValveBreakdownVoltage())
    io::PropertyIoDelegate::UnMarshall(*m_ValveBreakdownPotential, data.ValveBreakdownVoltage());
}

////////////////////////////////
// Electrical Resistance Types//
////////////////////////////////

bool SEElectricalCircuitPath::HasResistance() const
{
  return SECircuitPath::HasResistance();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetResistance()
{
  return SECircuitPath::GetResistance();
}
double SEElectricalCircuitPath::GetResistance(const ElectricResistanceUnit& unit) const
{
  if (m_Resistance == nullptr)
    return SEScalar::dNaN();
  return m_Resistance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextResistance() const
{
  return SECircuitPath::HasNextResistance();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetNextResistance()
{
  return SECircuitPath::GetNextResistance();
}
double SEElectricalCircuitPath::GetNextResistance(const ElectricResistanceUnit& unit) const
{
  if (m_NextResistance == nullptr)
    return SEScalar::dNaN();
  return m_NextResistance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasResistanceBaseline() const
{
  return SECircuitPath::HasResistanceBaseline();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetResistanceBaseline()
{
  return SECircuitPath::GetResistanceBaseline();
}
double SEElectricalCircuitPath::GetResistanceBaseline(const ElectricResistanceUnit& unit) const
{
  if (m_ResistanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_ResistanceBaseline->GetValue(unit);
}

//////////////////////////////////
// Electrical Capacitance Types //
//////////////////////////////////

bool SEElectricalCircuitPath::HasCapacitance() const
{
  return SECircuitPath::HasCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetCapacitance()
{
  return SECircuitPath::GetCapacitance();
}
double SEElectricalCircuitPath::GetCapacitance(const ElectricCapacitanceUnit& unit) const
{
  if (m_Capacitance == nullptr)
    return SEScalar::dNaN();
  return m_Capacitance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCapacitance() const
{
  return SECircuitPath::HasNextCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetNextCapacitance()
{
  return SECircuitPath::GetNextCapacitance();
}
double SEElectricalCircuitPath::GetNextCapacitance(const ElectricCapacitanceUnit& unit) const
{
  if (m_NextCapacitance == nullptr)
    return SEScalar::dNaN();
  return m_NextCapacitance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCapacitanceBaseline() const
{
  return SECircuitPath::HasCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetCapacitanceBaseline()
{
  return SECircuitPath::GetCapacitance();
}
double SEElectricalCircuitPath::GetCapacitanceBaseline(const ElectricCapacitanceUnit& unit) const
{
  if (m_CapacitanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_CapacitanceBaseline->GetValue(unit);
}

/////////////////////////////////
// Electrical Inductance Types //
/////////////////////////////////

bool SEElectricalCircuitPath::HasInductance() const
{
  return SECircuitPath::HasInductance();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetInductance()
{
  return SECircuitPath::GetInductance();
}
double SEElectricalCircuitPath::GetInductance(const ElectricInductanceUnit& unit) const
{
  if (m_Inductance == nullptr)
    return SEScalar::dNaN();
  return m_Inductance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextInductance() const
{
  return SECircuitPath::HasNextInductance();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetNextInductance()
{
  return SECircuitPath::GetNextInductance();
}
double SEElectricalCircuitPath::GetNextInductance(const ElectricInductanceUnit& unit) const
{
  if (m_NextInductance == nullptr)
    return SEScalar::dNaN();
  return m_NextInductance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasInductanceBaseline() const
{
  return SECircuitPath::HasInductanceBaseline();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetInductanceBaseline()
{
  return SECircuitPath::GetInductanceBaseline();
}
double SEElectricalCircuitPath::GetInductanceBaseline(const ElectricInductanceUnit& unit) const
{
  if (m_InductanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_InductanceBaseline->GetValue(unit);
}

///////////////////////////
// Electrical Flux Types //
///////////////////////////
bool SEElectricalCircuitPath::HasCurrent() const
{
  return HasFlux();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrent()
{
  return GetFlux();
}
double SEElectricalCircuitPath::GetCurrent(const ElectricCurrentUnit& unit) const
{
  if (m_Flux == nullptr)
    return SEScalar::dNaN();
  return m_Flux->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCurrent() const
{
  return HasNextFlux();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetNextCurrent()
{
  return GetNextFlux();
}
double SEElectricalCircuitPath::GetNextCurrent(const ElectricCurrentUnit& unit) const
{
  if (m_NextFlux == nullptr)
    return SEScalar::dNaN();
  return m_NextFlux->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCurrentSource() const
{
  return HasFluxSource();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrentSource()
{
  return GetFluxSource();
}
double SEElectricalCircuitPath::GetCurrentSource(const ElectricCurrentUnit& unit) const
{
  if (m_FluxSource == nullptr)
    return SEScalar::dNaN();
  return m_FluxSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCurrentSource() const
{
  return HasNextFluxSource();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetNextCurrentSource()
{
  return GetNextFluxSource();
}
double SEElectricalCircuitPath::GetNextCurrentSource(const ElectricCurrentUnit& unit) const
{
  if (m_NextFluxSource == nullptr)
    return SEScalar::dNaN();
  return m_NextFluxSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCurrentSourceBaseline() const
{
  return HasFluxSourceBaseline();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrentSourceBaseline()
{
  return GetFluxSourceBaseline();
}
double SEElectricalCircuitPath::GetCurrentSourceBaseline(const ElectricCurrentUnit& unit) const
{
  if (m_FluxSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_FluxSourceBaseline->GetValue(unit);
}

////////////////////////////////
// Electrical Potential Types //
////////////////////////////////
bool SEElectricalCircuitPath::HasVoltageSource() const
{
  return HasPotentialSource();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetVoltageSource()
{
  return GetPotentialSource();
}
double SEElectricalCircuitPath::GetVoltageSource(const ElectricPotentialUnit& unit) const
{
  if (m_PotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextVoltageSource() const
{
  return HasNextPotentialSource();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetNextVoltageSource()
{
  return GetNextPotentialSource();
}
double SEElectricalCircuitPath::GetNextVoltageSource(const ElectricPotentialUnit& unit) const
{
  if (m_NextPotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_NextPotentialSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasVoltageSourceBaseline() const
{
  return HasPotentialSourceBaseline();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetVoltageSourceBaseline()
{
  return GetPotentialSourceBaseline();
}
double SEElectricalCircuitPath::GetVoltageSourceBaseline(const ElectricPotentialUnit& unit) const
{
  if (m_PotentialSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSourceBaseline->GetValue(unit);
}
bool SEElectricalCircuitPath::HasValveBreakdownVoltage() const
{
  return HasValveBreakdownPotential();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetValveBreakdownVoltage()
{
  return GetValveBreakdownPotential();
}
double SEElectricalCircuitPath::GetValveBreakdownVoltage(const ElectricPotentialUnit& unit) const
{
  if (m_ValveBreakdownPotential == nullptr)
    return SEScalar::dNaN();
  return m_ValveBreakdownPotential->GetValue(unit);
}
}