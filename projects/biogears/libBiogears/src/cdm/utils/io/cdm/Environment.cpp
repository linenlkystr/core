#include "Environment.h"

#include "Environment.h"
#include "EnvironmentConditions.h"
#include "Property.h"
#include "Substance.h"
#include "System.h"

#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarPower.h>0

#include <biogears/cdm/system/environment/SEActiveCooling.h>
#include <biogears/cdm/system/environment/SEActiveHeating.h>
#include <biogears/cdm/system/environment/SEAppliedTemperature.h>
#include <biogears/cdm/system/environment/SEEnvironment.h>
#include <biogears/cdm/system/environment/conditions/SEEnvironmentCondition.h>
#include <biogears/cdm/system/environment/conditions/SEInitialEnvironment.h>

#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceConcentration.h>
#include <biogears/cdm/substance/SESubstanceFraction.h>
#include <biogears/cdm/substance/SESubstanceManager.h>

namespace biogears {
namespace io {
  //class SEEnvironmentalConditions
  void Environment::Marshall(const CDM::EnvironmentalConditionsData& in, SEEnvironmentalConditions& out)
  {
    out.Clear();
    if (in.Name().present()) {
      out.m_Name = in.Name().get();
    }
    if (in.SurroundingType().present()) {
      out.m_SurroundingType = in.SurroundingType().get();
    }
    io::Property::Marshall(in.AirDensity(), out.GetAirDensity());
    io::Property::Marshall(in.AirVelocity(), out.GetAirVelocity());
    io::Property::Marshall(in.AmbientTemperature(), out.GetAmbientTemperature());
    io::Property::Marshall(in.AtmosphericPressure(), out.GetAtmosphericPressure());
    io::Property::Marshall(in.ClothingResistance(), out.GetClothingResistance());
    io::Property::Marshall(in.Emissivity(), out.GetEmissivity());
    io::Property::Marshall(in.MeanRadiantTemperature(), out.GetMeanRadiantTemperature());
    io::Property::Marshall(in.RelativeHumidity(), out.GetRelativeHumidity());
    io::Property::Marshall(in.RespirationAmbientTemperature(), out.GetRespirationAmbientTemperature());

    SESubstance* sub;
    for (const CDM::SubstanceFractionData& sfData : in.AmbientGas()) {
      sub = out.m_Substances.GetSubstance(sfData.Name());
      if (sub == nullptr) {
        throw CommonDataModelException("Substance not found : " + sfData.Name());
      }
      if (sub->GetState() != CDM::enumSubstanceState::Gas) {
        throw CommonDataModelException("Substance not gas : " + sfData.Name());
      }
      SESubstanceFraction* sf = new SESubstanceFraction(*sub);
      io::Substance::Marshall(sfData, *sf);
      out.m_AmbientGases.push_back(sf);
      out.m_cAmbientGases.push_back(sf);
    }

    for (const CDM::SubstanceConcentrationData& scData : in.AmbientAerosol()) {
      sub = out.m_Substances.GetSubstance(scData.Name());
      if (sub == nullptr) {
        throw CommonDataModelException("Substance not found : " + scData.Name());
      }
      if (sub->GetState() != CDM::enumSubstanceState::Solid && sub->GetState() != CDM::enumSubstanceState::Liquid) {
        throw CommonDataModelException("Substance not a liquid or solid : " + scData.Name());
      }
      SESubstanceConcentration* sc = new SESubstanceConcentration(*sub);
      io::Substance::Marshall(scData, *sc);
      out.m_AmbientAerosols.push_back(sc);
      out.m_cAmbientAerosols.push_back(sc);
    }
  }
  //----------------------------------------------------------------------------------
  void Environment::UnMarshall(const SEEnvironmentalConditions& in, CDM::EnvironmentalConditionsData& out)
  {
    if (in.HasName()) {
      out.Name(in.m_Name);
    } else {
      out.Name("Local Environment Conditions");
    }
    if (in.HasSurroundingType()) {
      out.SurroundingType(in.m_SurroundingType);
    }
    if (in.m_AirDensity != nullptr) {
      io::Property::UnMarshall(*in.m_AirDensity, out.AirDensity());
    }
    if (in.m_AirVelocity != nullptr) {
      io::Property::UnMarshall(*in.m_AirVelocity, out.AirVelocity());
    }
    if (in.m_AmbientTemperature != nullptr) {
      io::Property::UnMarshall(*in.m_AmbientTemperature, out.AmbientTemperature());
    }
    if (in.m_AtmosphericPressure != nullptr) {
      io::Property::UnMarshall(*in.m_AtmosphericPressure, out.AtmosphericPressure());
    }
    if (in.m_ClothingResistance != nullptr) {
      io::Property::UnMarshall(*in.m_ClothingResistance, out.ClothingResistance());
    }
    if (in.m_Emissivity != nullptr) {
      io::Property::UnMarshall(*in.m_Emissivity, out.Emissivity());
    }
    if (in.m_MeanRadiantTemperature != nullptr) {
      io::Property::UnMarshall(*in.m_MeanRadiantTemperature, out.MeanRadiantTemperature());
    }
    if (in.m_RelativeHumidity != nullptr) {
      io::Property::UnMarshall(*in.m_RelativeHumidity, out.RelativeHumidity());
    }
    if (in.m_RespirationAmbientTemperature != nullptr) {
      io::Property::UnMarshall(*in.m_RespirationAmbientTemperature, out.RespirationAmbientTemperature());
    }

    for (SESubstanceFraction* sf : in.m_AmbientGases) {
      auto sfData = std::make_unique<CDM::SubstanceFractionData>();
      io::Substance::UnMarshall(*sf, *sfData);
      out.AmbientGas().push_back(std::move(sfData));
    }

    for (SESubstanceConcentration* sc : in.m_AmbientAerosols) {
      auto scData = std::make_unique<CDM::SubstanceConcentrationData>();
      io::Substance::UnMarshall(*sc, *scData);
      out.AmbientAerosol().push_back(std::move(scData));
    }
  }
  //----------------------------------------------------------------------------------
  //class SEActiveHeating
  void Environment::Marshall(const CDM::ActiveHeatingData& in, SEActiveHeating& out)
  {
    io::Property::Marshall(in.Power(), out.GetPower());
    io::Property::Marshall(in.SurfaceArea(), out.GetSurfaceArea());
    io::Property::Marshall(in.SurfaceAreaFraction(), out.GetSurfaceAreaFraction());
  }
  //----------------------------------------------------------------------------------
  void Environment::UnMarshall(const SEActiveHeating& in, CDM::ActiveHeatingData& out)
  {
    io::Property::UnMarshall(*in.m_Power, out.Power());
    if (in.HasSurfaceArea()) {
      io::Property::UnMarshall(*in.m_SurfaceArea, out.SurfaceArea());
    }
    if (in.HasSurfaceAreaFraction()) {
      io::Property::UnMarshall(*in.m_SurfaceAreaFraction, out.SurfaceAreaFraction());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEActiveCooling
  void Environment::Marshall(const CDM::ActiveCoolingData& in, SEActiveCooling& out)
  {
    io::Property::Marshall(in.Power(), out.GetPower());
    io::Property::Marshall(in.SurfaceArea(), out.GetSurfaceArea());
    io::Property::Marshall(in.SurfaceAreaFraction(), out.GetSurfaceAreaFraction());
  }
  //----------------------------------------------------------------------------------
  void Environment::UnMarshall(const SEActiveCooling& in, CDM::ActiveCoolingData& out)
  {
    if (in.HasPower()) {
      io::Property::UnMarshall(*in.m_Power, out.Power());
    }
    if (in.HasSurfaceArea()) {
      io::Property::UnMarshall(*in.m_SurfaceArea, out.SurfaceArea());
    }
    if (in.HasSurfaceAreaFraction()) {
      io::Property::UnMarshall(*in.m_SurfaceAreaFraction, out.SurfaceAreaFraction());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEAppliedTemperature
  void Environment::Marshall(const CDM::AppliedTemperatureData& in, SEAppliedTemperature& out)
  {
    out.Clear();
    if (in.State().present()) {
      out.m_State = in.State().get();
    }
    io::Property::Marshall(in.Temperature(), out.GetTemperature());
    io::Property::Marshall(in.SurfaceArea(), out.GetSurfaceArea());
    io::Property::Marshall(in.SurfaceAreaFraction(), out.GetSurfaceAreaFraction());
  }
  //----------------------------------------------------------------------------------
  void Environment::UnMarshall(const SEAppliedTemperature& in, CDM::AppliedTemperatureData& out)
  {
    if (in.HasTemperature()) {
      io::Property::UnMarshall(*in.m_Temperature, out.Temperature());
    }
    if (in.HasSurfaceArea()) {
      io::Property::UnMarshall(*in.m_SurfaceArea, out.SurfaceArea());
    }
    if (in.HasSurfaceAreaFraction()) {
      io::Property::UnMarshall(*in.m_SurfaceAreaFraction, out.SurfaceAreaFraction());
    }
    out.State(in.m_State);
  }
  //----------------------------------------------------------------------------------
  //class SEEnvironment
  void Environment::Marshall(const CDM::EnvironmentData& in, SEEnvironment& out)
  {
    io::System::Marshall(static_cast<const CDM::SystemData&>(in), static_cast<SESystem&>(out));

    if (in.Name().present()) {
      out.m_Name = in.Name().get();
    } else {
      out.m_Name = "Local Environment";
    }
      io::Environment::Marshall(in.ActiveHeating(), out.GetActiveHeating());
      io::Environment::Marshall(in.ActiveCooling(), out.GetActiveCooling());
      io::Environment::Marshall(in.AppliedTemperature(), out.GetAppliedTemperature());
      io::EnvironmentConditions::Marshall(in.Conditions(), out.GetConditions());
      io::Property::Marshall(in.ConvectiveHeatLoss(), out.GetConvectiveHeatLoss());
      io::Property::Marshall(in.ConvectiveHeatTranferCoefficient(), out.GetConvectiveHeatTranferCoefficient());
      io::Property::Marshall(in.EvaporativeHeatLoss(), out.GetEvaporativeHeatLoss());
      io::Property::Marshall(in.EvaporativeHeatTranferCoefficient(), out.GetEvaporativeHeatTranferCoefficient());
      io::Property::Marshall(in.RadiativeHeatLoss(), out.GetRadiativeHeatLoss());
      io::Property::Marshall(in.RadiativeHeatTranferCoefficient(), out.GetRadiativeHeatTranferCoefficient());
      io::Property::Marshall(in.RespirationHeatLoss(), out.GetRespirationHeatLoss());
      io::Property::Marshall(in.SkinHeatLoss(), out.GetSkinHeatLoss());

    out.StateChange();
  }
  //----------------------------------------------------------------------------------
  void Environment::UnMarshall(const SEEnvironment& in, CDM::EnvironmentData& out)
  {

    io::System::UnMarshall(static_cast<const SESystem&>(in), static_cast<CDM::SystemData&>(out));

    if (in.HasName()) {
      out.Name(in.m_Name);
    } else {
      out.Name("Unknown Environment");
    }

    if (in.HasActiveHeating() && in.m_ActiveHeating->GetPower().IsPositive()) {
      io::Environment::UnMarshall(in.m_ActiveHeating, out.ActiveHeating());
    }
    if (in.HasActiveCooling() && in.m_ActiveCooling->GetPower().IsPositive()) {
      io::Environment::UnMarshall(in.m_ActiveCooling, out.ActiveCooling());
    }
    if (in.HasAppliedTemperature()) {
      io::Environment::UnMarshall(in.m_AppliedTemperature, out.AppliedTemperature());
    }
    if (in.HasConditions()) {
      io::EnvironmentConditions::UnMarshall(in.GetConditions(), out.Conditions());
    }

    if (in.m_ConvectiveHeatLoss != nullptr) {
      io::Property::UnMarshall(*in.m_ConvectiveHeatLoss, out.ConvectiveHeatLoss());
    }
    if (in.m_ConvectiveHeatTranferCoefficient != nullptr) {
      io::Property::UnMarshall(*in.m_ConvectiveHeatTranferCoefficient, out.ConvectiveHeatTranferCoefficient());
    }
    if (in.m_EvaporativeHeatLoss != nullptr) {
      io::Property::UnMarshall(*in.m_EvaporativeHeatLoss, out.EvaporativeHeatLoss());
    }
    if (in.m_EvaporativeHeatTranferCoefficient != nullptr) {
      io::Property::UnMarshall(*in.m_EvaporativeHeatTranferCoefficient, out.EvaporativeHeatTranferCoefficient());
    }
    if (in.m_RadiativeHeatLoss != nullptr) {
      io::Property::UnMarshall(*in.m_RadiativeHeatLoss, out.RadiativeHeatLoss());
    }
    if (in.m_RadiativeHeatTranferCoefficient != nullptr) {
      io::Property::UnMarshall(*in.m_RadiativeHeatTranferCoefficient, out.RadiativeHeatTranferCoefficient());
    }
    if (in.m_RespirationHeatLoss != nullptr) {
      io::Property::UnMarshall(*in.m_RespirationHeatLoss, out.RespirationHeatLoss());
    }
    if (in.m_SkinHeatLoss != nullptr) {
      io::Property::UnMarshall(*in.m_SkinHeatLoss, out.SkinHeatLoss());
    }
  }
  //----------------------------------------------------------------------------------
}
}