#include "PropertyIoDelegate.h"

#include <biogears/schema/cdm/Properties.hxx>

#include <biogears/cdm/properties/SEDecimalFormat.h>
#include <biogears/cdm/properties/SEFunction.h>
#include <biogears/cdm/properties/SEFunctionElectricPotentialVsTime.h>
#include <biogears/cdm/properties/SEFunctionVolumeVsTime.h>
#include <biogears/cdm/properties/SEHistogramFractionVsLength.h>
#include <biogears/cdm/properties/SEScalarAmount.h>
#include <biogears/cdm/properties/SEScalarAreaPerTimePressure.h>
#include <biogears/cdm/properties/SEScalarElectricCapacitance.h>
#include <biogears/cdm/properties/SEScalarElectricCharge.h>
#include <biogears/cdm/properties/SEScalarElectricCurrent.h>
#include <biogears/cdm/properties/SEScalarElectricInductance.h>
#include <biogears/cdm/properties/SEScalarElectricPotential.h>
#include <biogears/cdm/properties/SEScalarElectricResistance.h>
#include <biogears/cdm/properties/SEScalarEnergyPerAmount.h>
#include <biogears/cdm/properties/SEScalarEnergyPerMass.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitance.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerAmount.h>
#include <biogears/cdm/properties/SEScalarHeatConductance.h>
#include <biogears/cdm/properties/SEScalarHeatConductancePerArea.h>
#include <biogears/cdm/properties/SEScalarHeatInductance.h>
#include <biogears/cdm/properties/SEScalarInversePressure.h>
#include <biogears/cdm/properties/SEScalarInverseVolume.h>
#include <biogears/cdm/properties/SEScalarMassPerMass.h>
#include <biogears/cdm/properties/SEScalarPowerPerAreaTemperatureToTheFourth.h>
#include <biogears/cdm/properties/SEScalarTypes.h>
#include <biogears/cdm/properties/SEScalarVolumePerPressure.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeMass.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimePressure.h>

#include "biogears/cdm/properties/SEHistogram.h"
#include <biogears/cdm/CommonDataModel.h>

#if defined(BIOGEARS_THROW_READONLY_EXCEPTIONS)
#define READ_ONLY_CHECK() \
  if (out.m_readOnly)     \
    throw CommonDataModelException("Scalar is marked read-only");
#else
#define READ_ONLY_CHECK() \
  if (out.m_readOnly)     \
    return;
#endif

namespace biogears {
namespace io {
  //class SEDecimalFormat
  void PropertyIoDelegate::Marshall(const CDM::DecimalFormatData& in, SEDecimalFormat& out)
  {
    out.Reset();
    if (in.DecimalFormat().present()) {
      if (in.DecimalFormat().get() == CDM::enumDecimalFormat::FixedMantissa)
        out.m_Notation = DecimalNotation::Fixed;
      else if (in.DecimalFormat().get() == CDM::enumDecimalFormat::SignificantDigits)
        out.m_Notation = DecimalNotation::Scientific;
    }
    if (in.Precision().present())
      out.m_Precision = in.Precision().get();
  }
  void PropertyIoDelegate::UnMarshall(const SEDecimalFormat& in, CDM::DecimalFormatData& out)
  {
    out.Precision(static_cast<CDM::DecimalFormatData::Precision_type>(in.m_Precision));
    switch (in.m_Notation) {
    case DecimalNotation::Default:
    case DecimalNotation::Fixed: {
      out.DecimalFormat(CDM::enumDecimalFormat::FixedMantissa);
      break;
    }
    case DecimalNotation::Scientific: {
      out.DecimalFormat(CDM::enumDecimalFormat::SignificantDigits);
      break;
    }
    }
  }
  //class SEFunctionElectricPotentialVsTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::FunctionElectricPotentialVsTimeData& in, SEFunctionElectricPotentialVsTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::FunctionData const&>(in), static_cast<SEFunction&>(out));
    if (out.SEFunction::Load(in))
      throw CommonDataModelException("Unable to Marshall SEFunctionElectricPotentialVsTime with Given");
    out.m_TimeUnit = &TimeUnit::GetCompoundUnit(in.IndependentUnit().get());
    out.m_ElectricPotentialUnit = &ElectricPotentialUnit::GetCompoundUnit(in.DependentUnit().get());
  }
  void PropertyIoDelegate::UnMarshall(const SEFunctionElectricPotentialVsTime& in, CDM::FunctionElectricPotentialVsTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEFunction const&>(in), static_cast<CDM::FunctionData&>(out));
    out.IndependentUnit(in.m_TimeUnit->GetString());
    out.DependentUnit(in.m_ElectricPotentialUnit->GetString());
  }
  //class SEFunction-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::FunctionData& in, SEFunction& out)
  {
    out.Clear();
    for (auto& dv : in.Dependent().DoubleList()) {
      out.m_Dependent.push_back(dv);
    }
    for (auto& iv : in.Independent().DoubleList()) {
      out.m_Independent.push_back(iv);
    }
  }
  void PropertyIoDelegate::UnMarshall(const SEFunction& in, CDM::FunctionData& out)
  {
    out.Dependent(std::make_unique<CDM::DoubleArray>());
    out.Dependent().DoubleList(std::make_unique<CDM::DoubleList>());
    out.Independent(std::make_unique<CDM::DoubleArray>());
    out.Independent().DoubleList(std::make_unique<CDM::DoubleList>());
    for (auto& dv : in.m_Dependent) {
      out.Dependent().DoubleList().push_back(dv);
    }
    for (auto& iv : in.m_Independent) {
      out.Independent().DoubleList().push_back(iv);
    }
  }
  //class SEFunctionVolumeVsTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::FunctionVolumeVsTimeData& in, SEFunctionVolumeVsTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::FunctionData const&>(in), static_cast<SEFunction&>(out));
    if (out.SEFunction::Load(in))
      throw CommonDataModelException("Unable to Marshall SEFunctionElectricPotentialVsTime with Given");
    out.m_TimeUnit = &TimeUnit::GetCompoundUnit(in.IndependentUnit().get());
    out.m_VolumeUnit = &VolumeUnit::GetCompoundUnit(in.DependentUnit().get());
  }
  void PropertyIoDelegate::UnMarshall(const SEFunctionVolumeVsTime& in, CDM::FunctionVolumeVsTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEFunction const&>(in), static_cast<CDM::FunctionData&>(out));
    out.IndependentUnit(in.m_TimeUnit->GetString());
    out.DependentUnit(in.m_VolumeUnit->GetString());
  }
  //class SEHistogramFractionVsLength-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::HistogramFractionVsLengthData& in, SEHistogramFractionVsLength& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::HistogramData const&>(in), static_cast<SEHistogram&>(out));
    if (out.SEHistogram::Load(in))
      throw CommonDataModelException("Unable to Marshall SEFunctionElectricPotentialVsTime with Given");
    out.m_LengthUnit = &LengthUnit::GetCompoundUnit(in.IndependentUnit().get());
   
  }
  void PropertyIoDelegate::UnMarshall(const SEHistogramFractionVsLength& in, CDM::HistogramFractionVsLengthData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEHistogram const&>(in), static_cast<CDM::HistogramData&>(out));
    out.IndependentUnit(in.m_LengthUnit->GetString());
  }
  //class SEHistogram-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::HistogramData& in, SEHistogram& out)
  {
    out.Clear();
    for (auto& dv : in.Dependent().DoubleList())
      out.m_Dependent.push_back(dv);
    for (auto& iv : in.Independent().DoubleList())
      out.m_Independent.push_back(iv);
  }
  void PropertyIoDelegate::UnMarshall(const SEHistogram& in, CDM::HistogramData& out)
  {
    out.Dependent(std::unique_ptr<CDM::DoubleList>(new CDM::DoubleList()));
    out.Dependent().DoubleList(std::unique_ptr<CDM::DoubleList>(new CDM::DoubleList()));
    out.Independent(std::unique_ptr<CDM::DoubleList>(new CDM::DoubleList()));
    out.Independent().DoubleList(std::unique_ptr<CDM::DoubleList>(new CDM::DoubleList()));
    for (auto& dv : in.m_Dependent)
      out.Dependent().DoubleList().push_back(dv);
    for (auto& iv : in.m_Independent)
      out.Independent().DoubleList().push_back(iv);
  }
  //class SEScalar0To1-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::Scalar0To1Data& in, SEScalar0To1& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalar&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalar0To1& in, CDM::Scalar0To1Data& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalar const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarAmount-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAmountData& in, SEScalarAmount& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AmountUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarAmount& in, CDM::ScalarAmountData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AmountUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarAmountPerMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAmountPerMassData& in, SEScalarAmountPerMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AmountPerMassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarAmountPerMass& in, CDM::ScalarAmountPerMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AmountPerMassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarAmountPerTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAmountPerTimeData& in, SEScalarAmountPerTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AmountPerTimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarAmountPerTime& in, CDM::ScalarAmountPerTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AmountPerTimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarAmountPerVolume-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAmountPerVolumeData& in, SEScalarAmountPerVolume& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AmountPerVolumeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarAmountPerVolume& in, CDM::ScalarAmountPerVolumeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AmountPerVolumeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAreaData& in, SEScalarArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarArea& in, CDM::ScalarAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarAreaPerTimePressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarAreaPerTimePressureData& in, SEScalarAreaPerTimePressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<AreaPerTimePressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarAreaPerTimePressure& in, CDM::ScalarAreaPerTimePressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<AreaPerTimePressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricCapacitance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricCapacitanceData& in, SEScalarElectricCapacitance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricCapacitanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricCapacitance& in, CDM::ScalarElectricCapacitanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricCapacitanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricCharge-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricChargeData& in, SEScalarElectricCharge& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricChargeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricCharge& in, CDM::ScalarElectricChargeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricChargeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricCurrent-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricCurrentData& in, SEScalarElectricCurrent& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricCurrentUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricCurrent& in, CDM::ScalarElectricCurrentData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricCurrentUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricInductance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricInductanceData& in, SEScalarElectricInductance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricInductanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricInductance& in, CDM::ScalarElectricInductanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricInductanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricPotential-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricPotentialData& in, SEScalarElectricPotential& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricPotentialUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricPotential& in, CDM::ScalarElectricPotentialData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricPotentialUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarElectricResistance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarElectricResistanceData& in, SEScalarElectricResistance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ElectricResistanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarElectricResistance& in, CDM::ScalarElectricResistanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ElectricResistanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarEnergy-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarEnergyData& in, SEScalarEnergy& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<EnergyUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarEnergy& in, CDM::ScalarEnergyData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<EnergyUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarEnergyPerAmount-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarEnergyPerAmountData& in, SEScalarEnergyPerAmount& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<EnergyPerAmountUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarEnergyPerAmount& in, CDM::ScalarEnergyPerAmountData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<EnergyPerAmountUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarEnergyPerMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarEnergyPerMassData& in, SEScalarEnergyPerMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<EnergyPerMassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarEnergyPerMass& in, CDM::ScalarEnergyPerMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<EnergyPerMassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFlowCompliance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFlowComplianceData& in, SEScalarFlowCompliance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<FlowComplianceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFlowCompliance& in, CDM::ScalarFlowComplianceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<FlowComplianceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFlowElastance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFlowElastanceData& in, SEScalarFlowElastance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<FlowElastanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFlowElastance& in, CDM::ScalarFlowElastanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<FlowElastanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFlowInertance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFlowInertanceData& in, SEScalarFlowInertance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<FlowInertanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFlowInertance& in, CDM::ScalarFlowInertanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<FlowInertanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFlowResistance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFlowResistanceData& in, SEScalarFlowResistance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<FlowResistanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFlowResistance& in, CDM::ScalarFlowResistanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<FlowResistanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarForce-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarForceData& in, SEScalarForce& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<ForceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarForce& in, CDM::ScalarForceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<ForceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFraction-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFractionData& in, SEScalarFraction& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalar&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFraction& in, CDM::ScalarFractionData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalar const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarFrequency-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarFrequencyData& in, SEScalarFrequency& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<FrequencyUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarFrequency& in, CDM::ScalarFrequencyData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<FrequencyUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalar-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarData& in, SEScalar& out)
  {
    READ_ONLY_CHECK()
    out.Clear();
    out.SEProperty::Load(in);
    out.m_value = in.value();
    if (in.unit().present()) {
      std::string u = in.unit().get();
      if (!("unitless" == u || "" == u || u.empty())) {
        throw CommonDataModelException("CDM::Scalar API is intended to be unitless, You are trying to load a ScalarData with a unit defined");
      }
    }
    out.m_readOnly = in.readOnly();
  }
  void PropertyIoDelegate::UnMarshall(const SEScalar& in, CDM::ScalarData& out)
  {
    out.value(in.m_value);
    out.readOnly(in.m_readOnly);
  }
  //class SEScalarHeatCapacitance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatCapacitanceData& in, SEScalarHeatCapacitance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatCapacitanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatCapacitance& in, CDM::ScalarHeatCapacitanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatCapacitanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatCapacitancePerAmount-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatCapacitancePerAmountData& in, SEScalarHeatCapacitancePerAmount& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatCapacitancePerAmountUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatCapacitancePerAmount& in, CDM::ScalarHeatCapacitancePerAmountData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatCapacitancePerAmountUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatCapacitancePerMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatCapacitancePerMassData& in, SEScalarHeatCapacitancePerMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatCapacitancePerMassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatCapacitancePerMass& in, CDM::ScalarHeatCapacitancePerMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatCapacitancePerMassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatConductance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatConductanceData& in, SEScalarHeatConductance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatConductanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatConductance& in, CDM::ScalarHeatConductanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatConductanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatConductancePerArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatConductancePerAreaData& in, SEScalarHeatConductancePerArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatConductancePerAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatConductancePerArea& in, CDM::ScalarHeatConductancePerAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatConductancePerAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatInductance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatInductanceData& in, SEScalarHeatInductance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatInductanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatInductance& in, CDM::ScalarHeatInductanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatInductanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatResistanceArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatResistanceAreaData& in, SEScalarHeatResistanceArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatResistanceAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatResistanceArea& in, CDM::ScalarHeatResistanceAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatResistanceAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarHeatResistance-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarHeatResistanceData& in, SEScalarHeatResistance& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<HeatResistanceUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarHeatResistance& in, CDM::ScalarHeatResistanceData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<HeatResistanceUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarInversePressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarInversePressureData& in, SEScalarInversePressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<InversePressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarInversePressure& in, CDM::ScalarInversePressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<InversePressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarInverseVolume-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarInverseVolumeData& in, SEScalarInverseVolume& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<InverseVolumeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarInverseVolume& in, CDM::ScalarInverseVolumeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<InverseVolumeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarLength-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarLengthData& in, SEScalarLength& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<LengthUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarLength& in, CDM::ScalarLengthData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<LengthUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarLengthPerTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarLengthPerTimeData& in, SEScalarLengthPerTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<LengthPerTimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarLengthPerTime& in, CDM::ScalarLengthPerTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<LengthPerTimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarLengthPerTimePressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarLengthPerTimePressureData& in, SEScalarLengthPerTimePressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<LengthPerTimePressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarLengthPerTimePressure& in, CDM::ScalarLengthPerTimePressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<LengthPerTimePressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassData& in, SEScalarMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMass& in, CDM::ScalarMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMassPerAmount-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassPerAmountData& in, SEScalarMassPerAmount& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassPerAmountUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMassPerAmount& in, CDM::ScalarMassPerAmountData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassPerAmountUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMassPerAreaTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassPerAreaTimeData& in, SEScalarMassPerAreaTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassPerAreaTimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMassPerAreaTime& in, CDM::ScalarMassPerAreaTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassPerAreaTimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMassPerMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassPerMassData& in, SEScalarMassPerMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassPerMassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMassPerMass& in, CDM::ScalarMassPerMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassPerMassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMassPerTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassPerTimeData& in, SEScalarMassPerTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassPerTimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMassPerTime& in, CDM::ScalarMassPerTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassPerTimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarMassPerVolume-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarMassPerVolumeData& in, SEScalarMassPerVolume& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<MassPerVolumeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarMassPerVolume& in, CDM::ScalarMassPerVolumeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<MassPerVolumeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarNeg1To1-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarNeg1To1Data& in, SEScalarNeg1To1& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalar&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarNeg1To1& in, CDM::ScalarNeg1To1Data& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalar const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarOsmolality-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarOsmolalityData& in, SEScalarOsmolality& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<OsmolalityUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarOsmolality& in, CDM::ScalarOsmolalityData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<OsmolalityUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarOsmolarity-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarOsmolarityData& in, SEScalarOsmolarity& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<OsmolarityUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarOsmolarity& in, CDM::ScalarOsmolarityData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<OsmolarityUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarPower-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPowerData& in, SEScalarPower& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PowerUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPower& in, CDM::ScalarPowerData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PowerUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarPowerPerAreaTemperatureToTheFourth-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPowerPerAreaTemperatureToTheFourthData& in, SEScalarPowerPerAreaTemperatureToTheFourth& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PowerPerAreaTemperatureToTheFourthUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPowerPerAreaTemperatureToTheFourth& in, CDM::ScalarPowerPerAreaTemperatureToTheFourthData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PowerPerAreaTemperatureToTheFourthUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarPressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPressureData& in, SEScalarPressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPressure& in, CDM::ScalarPressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarPressurePerVolume-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPressurePerVolumeData& in, SEScalarPressurePerVolume& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PressurePerVolumeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPressurePerVolume& in, CDM::ScalarPressurePerVolumeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PressurePerVolumeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScaMlarPressureTimePerArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPressureTimePerAreaData& in, SEScalarPressureTimePerArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PressureTimePerAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPressureTimePerArea& in, CDM::ScalarPressureTimePerAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PressureTimePerAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarPressureTimePerVolumeArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarPressureTimePerVolumeAreaData& in, SEScalarPressureTimePerVolumeArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<PressureTimePerVolumeAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarPressureTimePerVolumeArea& in, CDM::ScalarPressureTimePerVolumeAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<PressureTimePerVolumeAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarTemperature-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarTemperatureData& in, SEScalarTemperature& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<TemperatureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarTemperature& in, CDM::ScalarTemperatureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<TemperatureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarTimeData& in, SEScalarTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<TimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarTime& in, CDM::ScalarTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<TimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolume-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumeData& in, SEScalarVolume& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolume& in, CDM::ScalarVolumeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerPressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerPressureData& in, SEScalarVolumePerPressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerPressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerPressure& in, CDM::ScalarVolumePerPressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerPressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerTimeArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerTimeAreaData& in, SEScalarVolumePerTimeArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerTimeAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerTimeArea& in, CDM::ScalarVolumePerTimeAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerTimeAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerTime-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerTimeData& in, SEScalarVolumePerTime& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerTimeUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerTime& in, CDM::ScalarVolumePerTimeData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerTimeUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerTimeMass-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerTimeMassData& in, SEScalarVolumePerTimeMass& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerTimeMassUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerTimeMass& in, CDM::ScalarVolumePerTimeMassData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerTimeMassUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerTimePressureArea-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerTimePressureAreaData& in, SEScalarVolumePerTimePressureArea& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerTimePressureAreaUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerTimePressureArea& in, CDM::ScalarVolumePerTimePressureAreaData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerTimePressureAreaUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
  //class SEScalarVolumePerTimePressure-------------------------------------------------
  void PropertyIoDelegate::Marshall(const CDM::ScalarVolumePerTimePressureData& in, SEScalarVolumePerTimePressure& out)
  {
    PropertyIoDelegate::Marshall(static_cast<CDM::ScalarData const&>(in), static_cast<SEScalarQuantity<VolumePerTimePressureUnit>&>(out));
  }
  void PropertyIoDelegate::UnMarshall(const SEScalarVolumePerTimePressure& in, CDM::ScalarVolumePerTimePressureData& out)
  {
    PropertyIoDelegate::UnMarshall(static_cast<SEScalarQuantity<VolumePerTimePressureUnit> const&>(in), static_cast<CDM::ScalarData&>(out));
  }
}
}
