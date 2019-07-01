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
#include <biogears/engine/Controller/BioGearsConfiguration.h>

#include <biogears/cdm/Serializer.h>
#include <biogears/cdm/engine/PhysiologyEngineDynamicStabilization.h>
#include <biogears/cdm/engine/PhysiologyEngineTimedStabilization.h>
#include <biogears/cdm/patient/SENutrition.h>
#include <biogears/cdm/properties/SEScalarArea.h>
#include <biogears/cdm/properties/SEScalarAreaPerTimePressure.h>
#include <biogears/cdm/properties/SEScalarElectricResistance.h>
#include <biogears/cdm/properties/SEScalarEnergyPerAmount.h>
#include <biogears/cdm/properties/SEScalarEnergyPerMass.h>
#include <biogears/cdm/properties/SEScalarFlowElastance.h>
#include <biogears/cdm/properties/SEScalarFlowResistance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerAmount.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerMass.h>
#include <biogears/cdm/properties/SEScalarHeatConductance.h>
#include <biogears/cdm/properties/SEScalarHeatResistance.h>
#include <biogears/cdm/properties/SEScalarInverseVolume.h>
#include <biogears/cdm/properties/SEScalarLength.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerAmount.h>
#include <biogears/cdm/properties/SEScalarMassPerTime.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarPowerPerAreaTemperatureToTheFourth.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeArea.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimePressureArea.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/system/environment/SEEnvironmentalConditions.h>
#include <biogears/cdm/system/equipment/ElectroCardioGram/SEElectroCardioGramInterpolator.h>
#include <biogears/cdm/utils/FileUtils.h>

#include "../../cdm/utils/io/Property.h"
namespace biogears {

BioGearsConfiguration::BioGearsConfiguration(SESubstanceManager& substances)
  : PhysiologyEngineConfiguration(substances.GetLogger())
  , m_Substances(substances)
  // Barorecptors
  , m_ResponseSlope(nullptr)
  , m_HeartRateDistributedTimeDelay(nullptr)
  , m_HeartElastanceDistributedTimeDelay(nullptr)
  , m_SystemicResistanceDistributedTimeDelay(nullptr)
  , m_VenousComplianceDistributedTimeDelay(nullptr)
  , m_NormalizedHeartRateIntercept(nullptr)
  , m_NormalizedHeartRateSympatheticSlope(nullptr)
  , m_NormalizedHeartRateParasympatheticSlope(nullptr)
  , m_NormalizedHeartElastanceIntercept(nullptr)
  , m_NormalizedHeartElastanceSympatheticSlope(nullptr)
  , m_NormalizedResistanceIntercept(nullptr)
  , m_NormalizedResistanceSympatheticSlope(nullptr)
  , m_NormalizedComplianceIntercept(nullptr)
  , m_NormalizedComplianceParasympatheticSlope(nullptr)
  // Blood Chemistry
  , m_MeanCorpuscularHemoglobin(nullptr)
  , m_MeanCorpuscularVolume(nullptr)
  , m_StandardDiffusionDistance(nullptr)
  , m_StandardOxygenDiffusionCoefficient(nullptr)
  // Cardiovascular
  , m_LeftHeartElastanceMaximum(nullptr)
  , m_LeftHeartElastanceMinimum(nullptr)
  , m_MinimumBloodVolumeFraction(nullptr)
  , m_RightHeartElastanceMaximum(nullptr)
  , m_RightHeartElastanceMinimum(nullptr)
  , m_StandardPulmonaryCapillaryCoverage(nullptr)
  // Circuit
  , m_CardiovascularOpenResistance(nullptr)
  , m_DefaultClosedElectricResistance(nullptr)
  , m_DefaultClosedFlowResistance(nullptr)
  , m_DefaultClosedHeatResistance(nullptr)
  , m_DefaultOpenElectricResistance(nullptr)
  , m_DefaultOpenFlowResistance(nullptr)
  , m_DefaultOpenHeatResistance(nullptr)
  , m_MachineClosedResistance(nullptr)
  , m_MachineOpenResistance(nullptr)
  , m_RespiratoryClosedResistance(nullptr)
  , m_RespiratoryOpenResistance(nullptr)
  // Constants
  , m_OxygenMetabolicConstant(nullptr)
  , m_StefanBoltzmann(nullptr)
  , m_UniversalGasConstant(nullptr)
  // Drugs
  , m_PDEnabled(CDM::enumOnOff::value(-1))
  // Energy
  , m_BodySpecificHeat(nullptr)
  , m_CarbondDioxideProductionFromOxygenConsumptionConstant(nullptr)
  , m_CoreTemperatureLow(nullptr)
  , m_CoreTemperatureHigh(nullptr)
  , m_DeltaCoreTemperatureLow(nullptr)
  , m_EnergyPerATP(nullptr)
  , m_SweatHeatTransfer(nullptr)
  , m_VaporizationEnergy(nullptr)
  , m_VaporSpecificHeat(nullptr)
  // Environment
  , m_AirDensity(nullptr)
  , m_AirSpecificHeat(nullptr)
  , m_MolarMassOfDryAir(nullptr)
  , m_MolarMassOfWaterVapor(nullptr)
  , m_InitialEnvironmentalConditions(nullptr)
  , m_WaterDensity(nullptr)
  // Gastrointestinal
  , m_CalciumDigestionRate(nullptr)
  , m_CalciumAbsorptionFraction(nullptr)
  , m_CarbohydrateAbsorptionFraction(nullptr)
  , m_DefaultCarbohydrateDigestionRate(nullptr)
  , m_DefaultFatDigestionRate(nullptr)
  , m_DefaultProteinDigestionRate(nullptr)
  , m_DefaultStomachContents(nullptr)
  , m_FatAbsorptionFraction(nullptr)
  , m_ProteinToUreaFraction(nullptr)
  , m_WaterDigestionRate(nullptr)
  // Nervous
  , m_PupilDiameterBaseline(nullptr)
  // Renal
  , m_RenalEnabled(CDM::enumOnOff::value(-1))
  , m_PlasmaSodiumConcentrationSetPoint(nullptr)
  , m_PeritubularPotassiumConcentrationSetPoint(nullptr)
  , m_LeftGlomerularFluidPermeabilityBaseline(nullptr)
  , m_LeftGlomerularFilteringSurfaceAreaBaseline(nullptr)
  , m_LeftTubularReabsorptionFluidPermeabilityBaseline(nullptr)
  , m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline(nullptr)
  , m_MaximumAfferentResistance(nullptr)
  , m_MinimumAfferentResistance(nullptr)
  , m_RightGlomerularFluidPermeabilityBaseline(nullptr)
  , m_RightGlomerularFilteringSurfaceAreaBaseline(nullptr)
  , m_RightTubularReabsorptionFluidPermeabilityBaseline(nullptr)
  , m_RightTubularReabsorptionFilteringSurfaceAreaBaseline(nullptr)
  , m_TargetSodiumDelivery(nullptr)
  // Respiratory
  , m_CentralControllerCO2PressureSetPoint(nullptr)
  , m_CentralVentilatoryControllerGain(nullptr)
  , m_PeripheralControllerCO2PressureSetPoint(nullptr)
  , m_PeripheralVentilatoryControllerGain(nullptr)
  , m_PleuralComplianceSensitivity(nullptr)
  , m_PulmonaryVentilationRateMaximum(nullptr)
  , m_VentilationTidalVolumeIntercept(nullptr)
  , m_VentilatoryOcclusionPressure(nullptr)
  // Tissue
  , m_TissueEnabled(CDM::enumOnOff::value(-1))
{
}

BioGearsConfiguration::~BioGearsConfiguration()
{
  Clear();
}

void BioGearsConfiguration::Clear()
{
  PhysiologyEngineConfiguration::Clear();

  // Barorecptors
  SAFE_DELETE(m_ResponseSlope);
  SAFE_DELETE(m_HeartRateDistributedTimeDelay);
  SAFE_DELETE(m_HeartElastanceDistributedTimeDelay);
  SAFE_DELETE(m_SystemicResistanceDistributedTimeDelay);
  SAFE_DELETE(m_VenousComplianceDistributedTimeDelay);
  SAFE_DELETE(m_NormalizedHeartRateIntercept);
  SAFE_DELETE(m_NormalizedHeartRateSympatheticSlope);
  SAFE_DELETE(m_NormalizedHeartRateParasympatheticSlope);
  SAFE_DELETE(m_NormalizedHeartElastanceIntercept);
  SAFE_DELETE(m_NormalizedHeartElastanceSympatheticSlope);
  SAFE_DELETE(m_NormalizedResistanceIntercept);
  SAFE_DELETE(m_NormalizedResistanceSympatheticSlope);
  SAFE_DELETE(m_NormalizedComplianceIntercept);
  SAFE_DELETE(m_NormalizedComplianceParasympatheticSlope);

  // Blood Chemistry
  SAFE_DELETE(m_MeanCorpuscularHemoglobin);
  SAFE_DELETE(m_MeanCorpuscularVolume);
  SAFE_DELETE(m_StandardDiffusionDistance);
  SAFE_DELETE(m_StandardOxygenDiffusionCoefficient);

  // Cardiovascular
  SAFE_DELETE(m_LeftHeartElastanceMaximum);
  SAFE_DELETE(m_LeftHeartElastanceMinimum);
  SAFE_DELETE(m_MinimumBloodVolumeFraction);
  SAFE_DELETE(m_RightHeartElastanceMaximum);
  SAFE_DELETE(m_RightHeartElastanceMinimum);
  SAFE_DELETE(m_StandardPulmonaryCapillaryCoverage);

  // Circuit
  SAFE_DELETE(m_CardiovascularOpenResistance);
  SAFE_DELETE(m_DefaultClosedElectricResistance);
  SAFE_DELETE(m_DefaultClosedFlowResistance);
  SAFE_DELETE(m_DefaultClosedHeatResistance);
  SAFE_DELETE(m_DefaultOpenElectricResistance);
  SAFE_DELETE(m_DefaultOpenFlowResistance);
  SAFE_DELETE(m_DefaultOpenHeatResistance);
  SAFE_DELETE(m_MachineClosedResistance);
  SAFE_DELETE(m_MachineOpenResistance);
  SAFE_DELETE(m_RespiratoryClosedResistance);
  SAFE_DELETE(m_RespiratoryOpenResistance);

  // Constants
  SAFE_DELETE(m_OxygenMetabolicConstant);
  SAFE_DELETE(m_StefanBoltzmann);
  SAFE_DELETE(m_UniversalGasConstant);

  // Drugs
  m_PDEnabled = CDM::enumOnOff::value(-1);

  // Energy
  SAFE_DELETE(m_BodySpecificHeat);
  SAFE_DELETE(m_CarbondDioxideProductionFromOxygenConsumptionConstant);
  SAFE_DELETE(m_CoreTemperatureLow);
  SAFE_DELETE(m_CoreTemperatureHigh);
  SAFE_DELETE(m_DeltaCoreTemperatureLow);
  SAFE_DELETE(m_EnergyPerATP);
  SAFE_DELETE(m_SweatHeatTransfer);
  SAFE_DELETE(m_VaporizationEnergy);
  SAFE_DELETE(m_VaporSpecificHeat);

  // Environment
  SAFE_DELETE(m_AirDensity);
  SAFE_DELETE(m_AirSpecificHeat);
  SAFE_DELETE(m_MolarMassOfDryAir);
  SAFE_DELETE(m_MolarMassOfWaterVapor);
  SAFE_DELETE(m_InitialEnvironmentalConditions);
  SAFE_DELETE(m_WaterDensity);

  // Gastrointestinal
  SAFE_DELETE(m_CalciumDigestionRate);
  SAFE_DELETE(m_CalciumAbsorptionFraction);
  SAFE_DELETE(m_CarbohydrateAbsorptionFraction);
  SAFE_DELETE(m_DefaultCarbohydrateDigestionRate);
  SAFE_DELETE(m_DefaultFatDigestionRate);
  SAFE_DELETE(m_DefaultProteinDigestionRate);
  SAFE_DELETE(m_DefaultStomachContents);
  SAFE_DELETE(m_FatAbsorptionFraction);
  SAFE_DELETE(m_ProteinToUreaFraction);
  SAFE_DELETE(m_WaterDigestionRate);

  // Nervous
  SAFE_DELETE(m_PupilDiameterBaseline);

  // Renal
  m_RenalEnabled = CDM::enumOnOff::value(-1);
  SAFE_DELETE(m_PlasmaSodiumConcentrationSetPoint);
  SAFE_DELETE(m_PeritubularPotassiumConcentrationSetPoint);
  SAFE_DELETE(m_LeftGlomerularFluidPermeabilityBaseline);
  SAFE_DELETE(m_LeftGlomerularFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_LeftTubularReabsorptionFluidPermeabilityBaseline);
  SAFE_DELETE(m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_MaximumAfferentResistance);
  SAFE_DELETE(m_MinimumAfferentResistance);
  SAFE_DELETE(m_RightGlomerularFluidPermeabilityBaseline);
  SAFE_DELETE(m_RightGlomerularFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_RightTubularReabsorptionFluidPermeabilityBaseline);
  SAFE_DELETE(m_RightTubularReabsorptionFilteringSurfaceAreaBaseline);
  SAFE_DELETE(m_TargetSodiumDelivery);

  // Respiratory
  SAFE_DELETE(m_CentralControllerCO2PressureSetPoint);
  SAFE_DELETE(m_CentralVentilatoryControllerGain);
  SAFE_DELETE(m_PeripheralControllerCO2PressureSetPoint);
  SAFE_DELETE(m_PeripheralVentilatoryControllerGain);
  SAFE_DELETE(m_PleuralComplianceSensitivity);
  SAFE_DELETE(m_PulmonaryVentilationRateMaximum);
  SAFE_DELETE(m_VentilationTidalVolumeIntercept);
  SAFE_DELETE(m_VentilatoryOcclusionPressure);

  //Tissue
  m_TissueEnabled = CDM::enumOnOff::value(-1);
}

void BioGearsConfiguration::Initialize()
{
  Clear();
  m_WritePatientBaselineFile = CDM::enumOnOff::Off;

  // Reset to default values
  GetECGInterpolator().LoadWaveforms("ecg/StandardECG.xml");
  GetTimeStep().SetValue(1.0 / 50.0, TimeUnit::s);
  GetDynamicStabilizationCriteria().Load("config/DynamicStabilization.xml");
  //GetTimedStabilizationCriteria().Load("config/TimedStabilization.xml");
  m_StabilizationCriteria->TrackStabilization(CDM::enumOnOff::Off); // Turn on to include stabilization tracking for debugging

  // Baroreceptors
  GetResponseSlope().SetValue(12.0); //nu
  GetHeartRateDistributedTimeDelay().SetValue(20.0, TimeUnit::s);
  GetHeartElastanceDistributedTimeDelay().SetValue(20.0, TimeUnit::s);
  GetSystemicResistanceDistributedTimeDelay().SetValue(30.0, TimeUnit::s);
  GetVenousComplianceDistributedTimeDelay().SetValue(60.0, TimeUnit::s);
  GetNormalizedHeartRateIntercept().SetValue(0.26); //Gamma Heart Rate
  GetNormalizedHeartRateSympatheticSlope().SetValue(1.73); //Alpha Heart Rate
  GetNormalizedHeartRateParasympatheticSlope().SetValue(0.25); //Beta Heart Rate
  GetNormalizedHeartElastanceIntercept().SetValue(0.95); //Gamma Heart Elastance
  GetNormalizedHeartElastanceSympatheticSlope().SetValue(0.1); //Alpha Elastance
  GetNormalizedResistanceIntercept().SetValue(0.4); //Gamma Resistance
  GetNormalizedResistanceSympatheticSlope().SetValue(1.2); //Alpha Resistance
  GetNormalizedComplianceIntercept().SetValue(0.7); //Gamma Compliance
  GetNormalizedComplianceParasympatheticSlope().SetValue(0.6); //Alpha Compliance

  //Blood Chemistry
  GetMeanCorpuscularVolume().SetValue(9.e-8, VolumeUnit::uL); // Guyton p419
  GetMeanCorpuscularHemoglobin().SetValue(29, MassPerAmountUnit::pg_Per_ct);
  GetStandardDiffusionDistance().SetValue(0.0006, LengthUnit::mm);
  GetStandardOxygenDiffusionCoefficient().SetValue(0.00000000246, AreaPerTimePressureUnit::cm2_Per_min_mmHg);

  // Cardiovascular
  GetLeftHeartElastanceMaximum().SetValue(2.49, FlowElastanceUnit::mmHg_Per_mL);
  GetLeftHeartElastanceMinimum().SetValue(0.049, FlowElastanceUnit::mmHg_Per_mL);
  GetMinimumBloodVolumeFraction().SetValue(0.70); // \Boron2017Medical p583  This is fraction which triggers hypovolemic shock
  GetRightHeartElastanceMaximum().SetValue(0.523, FlowElastanceUnit::mmHg_Per_mL);
  GetRightHeartElastanceMinimum().SetValue(0.0243, FlowElastanceUnit::mmHg_Per_mL);
  GetStandardPulmonaryCapillaryCoverage().SetValue(0.70);

  // Circuits
  GetCardiovascularOpenResistance().SetValue(100.0, FlowResistanceUnit::mmHg_s_Per_mL);
  GetDefaultOpenElectricResistance().SetValue(1E100, ElectricResistanceUnit::Ohm);
  GetDefaultOpenFlowResistance().SetValue(1E100, FlowResistanceUnit::Pa_s_Per_m3);
  GetDefaultOpenHeatResistance().SetValue(1E100, HeatResistanceUnit::K_Per_W);
  GetDefaultClosedElectricResistance().SetValue(1E-100, ElectricResistanceUnit::Ohm);
  GetDefaultClosedFlowResistance().SetValue(1E-100, FlowResistanceUnit::Pa_s_Per_m3);
  GetDefaultClosedHeatResistance().SetValue(1E-100, HeatResistanceUnit::K_Per_W);
  GetMachineClosedResistance().SetValue(1E-3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetMachineOpenResistance().SetValue(1E3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetRespiratoryClosedResistance().SetValue(1E-3, FlowResistanceUnit::cmH2O_s_Per_L);
  GetRespiratoryOpenResistance().SetValue(1E3, FlowResistanceUnit::cmH2O_s_Per_L);

  // Constants
  GetOxygenMetabolicConstant().SetValue(9.0);
  GetStefanBoltzmann().SetValue(5.670367E-8, PowerPerAreaTemperatureToTheFourthUnit::W_Per_m2_K4); //http://physics.nist.gov/cuu/Constants/
  GetUniversalGasConstant().SetValue(8.3144621, HeatCapacitancePerAmountUnit::J_Per_K_mol); //http://physics.nist.gov/cuu/Constants/

  // Drugs
  m_PDEnabled = CDM::enumOnOff::On;

  // Energy
  GetBodySpecificHeat().SetValue(0.83, HeatCapacitancePerMassUnit::kcal_Per_K_kg);
  GetCarbondDioxideProductionFromOxygenConsumptionConstant().SetValue(0.8);
  GetCoreTemperatureLow().SetValue(36.8, TemperatureUnit::C);
  GetCoreTemperatureHigh().SetValue(37.1, TemperatureUnit::C);
  GetDeltaCoreTemperatureLow().SetValue(1.8, TemperatureUnit::C);
  GetEnergyPerATP().SetValue(11.5, EnergyPerAmountUnit::kcal_Per_mol); //Under standard conditions, it's 7.3 kcal/mol, but under intracellular conditions, it should be around 11.5
  GetSweatHeatTransfer().SetValue(0.20833, HeatConductanceUnit::kcal_Per_K_s);
  GetVaporizationEnergy().SetValue(2260.0, EnergyPerMassUnit::kJ_Per_kg);
  GetVaporSpecificHeat().SetValue(1.890, HeatCapacitancePerMassUnit::kJ_Per_K_kg);

  // Environment
  GetAirDensity().SetValue(1.225, MassPerVolumeUnit::kg_Per_m3);
  GetAirSpecificHeat().SetValue(1.0035, HeatCapacitancePerMassUnit::kJ_Per_K_kg);
  GetMolarMassOfDryAir().SetValue(0.028964, MassPerAmountUnit::kg_Per_mol);
  GetMolarMassOfWaterVapor().SetValue(0.018016, MassPerAmountUnit::kg_Per_mol);
  GetInitialEnvironmentalConditions().Load("environments/Standard.xml");
  GetWaterDensity().SetValue(1000, MassPerVolumeUnit::kg_Per_m3); //Because water density changes with temperature, and this refers to room temperature water, you should use GeneralMath::CalculateWaterDensity() instead

  // Gastrointestinal
  GetCalciumAbsorptionFraction().SetValue(0.25); // Net fractional calcium absorption is 24.9 ± 12.4% (Hunt and Johnson 2007)
  GetCalciumDigestionRate().SetValue(2.7, MassPerTimeUnit::mg_Per_min); // Wasserman1992Intestinal
  GetCarbohydrateAbsorptionFraction().SetValue(0.80); // Guyton p790
  GetDefaultCarbohydrateDigestionRate().SetValue(0.5, MassPerTimeUnit::g_Per_min); // Guyton (About 4.25hr to digest the carbs in default meal)
  GetDefaultFatDigestionRate().SetValue(0.055, MassPerTimeUnit::g_Per_min); // Guyton (About 8hr to digest the fat in the default meal)
  GetDefaultProteinDigestionRate().SetValue(0.071, MassPerTimeUnit::g_Per_min); // Dangin2001Digestion (About 5hr to digest the protein in the default meal)
  GetDefaultStomachContents().Load("nutrition/NoMacros.xml"); // Refs are in the data spreadsheet
  GetFatAbsorptionFraction().SetValue(0.248); // Guyton p797 and the recommended daily value for saturated fat intake according to the AHA //TODO: Add this reference
  // We should be making 30 grams of urea per 100 grams of protein haussinger1990nitrogen
  GetProteinToUreaFraction().SetValue(0.405); // BUT, We should excrete 24.3 g/day on average. Guyton p 328. With an average intake of 60 g/day, that works out to approximately 40%.
  GetWaterDigestionRate().SetValue(0.417, VolumePerTimeUnit::mL_Per_s); // Peronnet2012Pharmacokinetic, Estimated from 300mL H20 being absorbed in 9.5-12m

  // Nervous
  GetPupilDiameterBaseline().SetValue(4, LengthUnit::mm);

  // Renal
  m_RenalEnabled = CDM::enumOnOff::On;
  GetPlasmaSodiumConcentrationSetPoint().SetValue(3.23, MassPerVolumeUnit::mg_Per_mL);
  GetPeritubularPotassiumConcentrationSetPoint().SetValue(0.0185, MassPerVolumeUnit::g_Per_dL);
  GetLeftGlomerularFluidPermeabilityBaseline().SetValue(3.67647, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetLeftGlomerularFilteringSurfaceAreaBaseline().SetValue(2.0, AreaUnit::m2);
  GetLeftTubularReabsorptionFluidPermeabilityBaseline().SetValue(2.91747, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline().SetValue(2.5, AreaUnit::m2);
  GetMaximumAfferentResistance().SetValue(11.2, FlowResistanceUnit::mmHg_s_Per_mL); //11.2
  GetMinimumAfferentResistance().SetValue(2.2, FlowResistanceUnit::mmHg_s_Per_mL); //2.1
  GetRightGlomerularFluidPermeabilityBaseline().SetValue(3.67647, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  GetRightGlomerularFilteringSurfaceAreaBaseline().SetValue(2.0, AreaUnit::m2);
  GetRightTubularReabsorptionFluidPermeabilityBaseline().SetValue(2.91747, VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2);
  //GetRightTubularReabsorptionFluidPermeabilityBaseline().SetValue(1.0, VolumePerTimePressureAreaUnit::mL_Per_min_Per_mmHg_Per_m2);
  GetRightTubularReabsorptionFilteringSurfaceAreaBaseline().SetValue(2.5, AreaUnit::m2);
  GetTargetSodiumDelivery().SetValue(0.201, MassPerTimeUnit::g_Per_min);

  // Respiratory
  GetCentralControllerCO2PressureSetPoint().SetValue(35.5, PressureUnit::mmHg);
  GetCentralVentilatoryControllerGain().SetValue(1.44); //How much to add to the amplitude when the CO2 is off
  GetPeripheralControllerCO2PressureSetPoint().SetValue(35.5, PressureUnit::mmHg);
  GetPeripheralVentilatoryControllerGain().SetValue(30.24); //How much to add to the amplitude when the CO2 is off
  GetPleuralComplianceSensitivity().SetValue(5.0, InverseVolumeUnit::Inverse_L);
  GetPulmonaryVentilationRateMaximum().SetValue(150.0, VolumePerTimeUnit::L_Per_min);
  GetVentilationTidalVolumeIntercept().SetValue(0.3, VolumeUnit::L);
  GetVentilatoryOcclusionPressure().SetValue(0.75, PressureUnit::cmH2O); //This increases the absolute max driver pressure

  // Tissue
  m_TissueEnabled = CDM::enumOnOff::On;
}

void BioGearsConfiguration::Merge(const PhysiologyEngineConfiguration& from)
{
  const BioGearsConfiguration* bgConfig = dynamic_cast<const BioGearsConfiguration*>(&from);
  if (bgConfig != nullptr)
    Merge(*bgConfig);
  else
    PhysiologyEngineConfiguration::Merge(from);
}

void BioGearsConfiguration::Merge(const BioGearsConfiguration& from)
{
  m_Merge = true;
  CDM_COPY((&from), this);
  m_Merge = false;
}

bool BioGearsConfiguration::Load(const std::string& file)
{
  // if file does not exist, we stick with defaults

  CDM::BioGearsConfigurationData* pData;
  std::unique_ptr<CDM::ObjectData> data;

  data = Serializer::ReadFile(file, GetLogger());
  pData = dynamic_cast<CDM::BioGearsConfigurationData*>(data.get());
  if (pData == nullptr) {
    std::stringstream ss;
    ss << "Configuration file : " << file << " not found, using default configuration" << std::endl;
    Info(ss);
    return true;
  }
  return Load(*pData);
}

bool BioGearsConfiguration::Load(const CDM::PhysiologyEngineConfigurationData& from)
{
  const CDM::BioGearsConfigurationData* bgConfig = dynamic_cast<const CDM::BioGearsConfigurationData*>(&from);
  if (bgConfig != nullptr)
    return Load(*bgConfig);
  else
    return PhysiologyEngineConfiguration::Load(from);
}

bool BioGearsConfiguration::Load(const CDM::BioGearsConfigurationData& in)
{
  PhysiologyEngineConfiguration::Load(in);

  //Barorecptors
  if (in.BaroreceptorConfiguration().present()) {
    const CDM::BaroreceptorConfigurationData& config = in.BaroreceptorConfiguration().get();
    if (config.ResponseSlope().present())
      io::Property::Marshall(config.ResponseSlope(), GetResponseSlope());
    io::Property::Marshall(config.HeartRateDistributedTimeDelay(), GetHeartRateDistributedTimeDelay());
    if (config.HeartElastanceDistributedTimeDelay().present())
      io::Property::Marshall(config.HeartElastanceDistributedTimeDelay(), GetHeartElastanceDistributedTimeDelay());
    if (config.SystemicResistanceDistributedTimeDelay().present())
      io::Property::Marshall(config.SystemicResistanceDistributedTimeDelay(), GetSystemicResistanceDistributedTimeDelay());
    if (config.VenousComplianceDistributedTimeDelay().present())
      io::Property::Marshall(config.VenousComplianceDistributedTimeDelay(), GetVenousComplianceDistributedTimeDelay());
    if (config.NormalizedHeartRateIntercept().present())
      io::Property::Marshall(config.NormalizedHeartRateIntercept(), GetNormalizedHeartRateIntercept());
    if (config.NormalizedHeartRateSympatheticSlope().present())
      io::Property::Marshall(config.NormalizedHeartRateSympatheticSlope(), GetNormalizedHeartRateSympatheticSlope());
    if (config.NormalizedHeartRateParasympatheticSlope().present())
      io::Property::Marshall(config.NormalizedHeartRateParasympatheticSlope(), GetNormalizedHeartRateParasympatheticSlope());
    if (config.NormalizedHeartElastanceIntercept().present())
      io::Property::Marshall(config.NormalizedHeartElastanceIntercept(), GetNormalizedHeartElastanceIntercept());
    if (config.NormalizedHeartElastanceSympatheticSlope().present())
      io::Property::Marshall(config.NormalizedHeartElastanceSympatheticSlope(), GetNormalizedHeartElastanceSympatheticSlope());
    if (config.NormalizedResistanceIntercept().present())
      io::Property::Marshall(config.NormalizedResistanceIntercept(), GetNormalizedResistanceIntercept());
    if (config.NormalizedResistanceSympatheticSlope().present())
      io::Property::Marshall(config.NormalizedResistanceSympatheticSlope(), GetNormalizedResistanceSympatheticSlope());
    if (config.NormalizedComplianceIntercept().present())
      io::Property::Marshall(config.NormalizedComplianceIntercept(), GetNormalizedComplianceIntercept());
    if (config.NormalizedComplianceParasympatheticSlope().present())
      io::Property::Marshall(config.NormalizedComplianceParasympatheticSlope(), GetNormalizedComplianceParasympatheticSlope());
  }

  // Blood Chemistry
  if (in.BloodChemistryConfiguration().present()) {
    const CDM::BloodChemistryConfigurationData& config = in.BloodChemistryConfiguration().get();
    if (config.MeanCorpuscularVolume().present())
      io::Property::Marshall(config.MeanCorpuscularVolume(), GetMeanCorpuscularVolume());
    if (config.MeanCorpuscularHemoglobin().present())
      io::Property::Marshall(config.MeanCorpuscularHemoglobin(), GetMeanCorpuscularHemoglobin());
    if (config.StandardDiffusionDistance().present())
      io::Property::Marshall(config.StandardDiffusionDistance(), GetStandardDiffusionDistance());
    if (config.StandardOxygenDiffusionCoefficient().present())
      io::Property::Marshall(config.StandardOxygenDiffusionCoefficient(), GetStandardOxygenDiffusionCoefficient());
  }

  // Cardiovascular
  if (in.CardiovascularConfiguration().present()) {
    const CDM::CardiovascularConfigurationData& config = in.CardiovascularConfiguration().get();
    if (config.LeftHeartElastanceMaximum().present())
      io::Property::Marshall(config.LeftHeartElastanceMaximum(), GetLeftHeartElastanceMaximum());
    if (config.LeftHeartElastanceMinimum().present())
      io::Property::Marshall(config.LeftHeartElastanceMinimum(), GetLeftHeartElastanceMinimum());
    if (config.MinimumBloodVolumeFraction().present())
      io::Property::Marshall(config.MinimumBloodVolumeFraction(), GetMinimumBloodVolumeFraction());
    if (config.RightHeartElastanceMaximum().present())
      io::Property::Marshall(config.RightHeartElastanceMaximum(), GetRightHeartElastanceMaximum());
    if (config.RightHeartElastanceMinimum().present())
      io::Property::Marshall(config.RightHeartElastanceMinimum(), GetRightHeartElastanceMinimum());
    if (config.StandardPulmonaryCapillaryCoverage().present())
      io::Property::Marshall(config.StandardPulmonaryCapillaryCoverage(), GetStandardPulmonaryCapillaryCoverage());
  }

  // Circuit
  if (in.CircuitConfiguration().present()) {
    const CDM::CircuitConfigurationData& config = in.CircuitConfiguration().get();
    if (config.CardiovascularOpenResistance().present())
      io::Property::Marshall(config.CardiovascularOpenResistance(), GetCardiovascularOpenResistance());
    if (config.DefaultOpenElectricResistance().present())
      io::Property::Marshall(config.DefaultOpenElectricResistance(), GetDefaultOpenElectricResistance());
    if (config.DefaultOpenFlowResistance().present())
      io::Property::Marshall(config.DefaultOpenFlowResistance(), GetDefaultOpenFlowResistance());
    if (config.DefaultOpenHeatResistance().present())
      io::Property::Marshall(config.DefaultOpenHeatResistance(), GetDefaultOpenHeatResistance());
    if (config.DefaultClosedElectricResistance().present())
      io::Property::Marshall(config.DefaultClosedElectricResistance(), GetDefaultClosedElectricResistance());
    if (config.DefaultClosedFlowResistance().present())
      io::Property::Marshall(config.DefaultClosedFlowResistance(), GetDefaultClosedFlowResistance());
    if (config.DefaultClosedHeatResistance().present())
      io::Property::Marshall(config.DefaultClosedHeatResistance(), GetDefaultClosedHeatResistance());
    if (config.MachineClosedResistance().present())
      io::Property::Marshall(config.MachineClosedResistance(), GetMachineClosedResistance());
    if (config.MachineOpenResistance().present())
      io::Property::Marshall(config.MachineOpenResistance(), GetMachineOpenResistance());
    if (config.RespiratoryClosedResistance().present())
      io::Property::Marshall(config.RespiratoryClosedResistance(), GetRespiratoryClosedResistance());
    if (config.RespiratoryOpenResistance().present())
      io::Property::Marshall(config.RespiratoryOpenResistance(), GetRespiratoryOpenResistance());
  }

  // Constants
  if (in.ConstantsConfiguration().present()) {
    const CDM::ConstantsConfigurationData& config = in.ConstantsConfiguration().get();
    if (config.OxygenMetabolicConstant().present())
      io::Property::Marshall(config.OxygenMetabolicConstant(), GetOxygenMetabolicConstant());
    if (config.StefanBoltzmann().present())
      io::Property::Marshall(config.StefanBoltzmann(), GetStefanBoltzmann());
    if (config.UniversalGasConstant().present())
      io::Property::Marshall(config.UniversalGasConstant(), GetUniversalGasConstant());
  }

  // Drugs
  if (in.DrugsConfiguration().present()) {
    const CDM::DrugsConfigurationData& config = in.DrugsConfiguration().get();
    if (config.PDModel().present())
      UsePDModel(config.PDModel().get());
  }

  // Energy
  if (in.EnergyConfiguration().present()) {
    const CDM::EnergyConfigurationData& config = in.EnergyConfiguration().get();
    if (config.BodySpecificHeat().present())
      io::Property::Marshall(config.BodySpecificHeat(), GetBodySpecificHeat());
    if (config.CoreTemperatureLow().present())
      io::Property::Marshall(config.CoreTemperatureLow(), GetCoreTemperatureLow());
    if (config.CoreTemperatureHigh().present())
      io::Property::Marshall(config.CoreTemperatureHigh(), GetCoreTemperatureHigh());
    if (config.DeltaCoreTemperatureLow().present())
      io::Property::Marshall(config.DeltaCoreTemperatureLow(), GetDeltaCoreTemperatureLow());
    if (config.EnergyPerATP().present())
      io::Property::Marshall(config.EnergyPerATP(), GetEnergyPerATP());
    if (config.SweatHeatTransfer().present())
      io::Property::Marshall(config.SweatHeatTransfer(), GetSweatHeatTransfer());
    if (config.VaporizationEnergy().present())
      io::Property::Marshall(config.VaporizationEnergy(), GetVaporizationEnergy());
    if (config.VaporSpecificHeat().present())
      io::Property::Marshall(config.VaporSpecificHeat(), GetVaporSpecificHeat());
  }

  // Environment
  if (in.EnvironmentConfiguration().present()) {
    const CDM::EnvironmentConfigurationData& config = in.EnvironmentConfiguration().get();
    if (config.AirDensity().present())
      io::Property::Marshall(config.AirDensity(), GetAirDensity());
    if (config.AirSpecificHeat().present())
      io::Property::Marshall(config.AirSpecificHeat(), GetAirSpecificHeat());
    if (config.MolarMassOfDryAir().present())
      io::Property::Marshall(config.MolarMassOfDryAir(), GetMolarMassOfDryAir());
    if (config.MolarMassOfWaterVapor().present())
      io::Property::Marshall(config.MolarMassOfWaterVapor(), GetMolarMassOfWaterVapor());
    if (config.InitialEnvironmentalConditionsFile().present()) {
      if (!GetInitialEnvironmentalConditions().Load(config.InitialEnvironmentalConditionsFile().get())) {
        Error("Unable to load InitialEnvironmentalConditions file");
        return false;
      }
    } else if (config.InitialEnvironmentalConditions().present()) {
      if (!GetInitialEnvironmentalConditions().Load(config.InitialEnvironmentalConditions().get())) {
        Error("Unable to load InitialEnvironmentalConditions");
        return false;
      }
    }
    if (config.WaterDensity().present())
      io::Property::Marshall(config.WaterDensity(), GetWaterDensity());
  }

  // Gastrointestinal
  if (in.GastrointestinalConfiguration().present()) {
    const CDM::GastrointestinalConfigurationData& config = in.GastrointestinalConfiguration().get();
    if (config.CalciumAbsorptionFraction().present())
      io::Property::Marshall(config.CalciumAbsorptionFraction(), GetCalciumAbsorptionFraction());
    if (config.CalciumDigestionRate().present())
      io::Property::Marshall(config.CalciumDigestionRate(), GetCalciumDigestionRate());
    if (config.CarbohydrateAbsorptionFraction().present())
      io::Property::Marshall(config.CarbohydrateAbsorptionFraction(), GetCarbohydrateAbsorptionFraction());
    if (config.DefaultCarbohydrateDigestionRate().present())
      io::Property::Marshall(config.DefaultCarbohydrateDigestionRate(), GetDefaultCarbohydrateDigestionRate());
    if (config.DefaultFatDigestionRate().present())
      io::Property::Marshall(config.DefaultFatDigestionRate(), GetDefaultFatDigestionRate());
    if (config.DefaultProteinDigestionRate().present())
      io::Property::Marshall(config.DefaultProteinDigestionRate(), GetDefaultProteinDigestionRate());
    if (config.DefaultStomachContentsFile().present()) {
      if (!GetDefaultStomachContents().Load(config.DefaultStomachContentsFile().get())) {
        Error("Unable to load Standard Stomach Contents file");
        return false;
      }
    } else if (config.DefaultStomachContents().present()) {
      if (!GetDefaultStomachContents().Load(config.DefaultStomachContents().get())) {
        Error("Unable to load Standard Stomach Contents");
        return false;
      }
    }
    // Use default rate if they are not set
    {
      if (m_DefaultStomachContents->HasCarbohydrate() && !m_DefaultStomachContents->HasCarbohydrateDigestionRate())
        m_DefaultStomachContents->GetCarbohydrateDigestionRate().Set(GetDefaultCarbohydrateDigestionRate());
      if (m_DefaultStomachContents->HasFat() && !m_DefaultStomachContents->HasFatDigestionRate())
        m_DefaultStomachContents->GetFatDigestionRate().Set(GetDefaultFatDigestionRate());
      if (m_DefaultStomachContents->HasProtein() && !m_DefaultStomachContents->HasProteinDigestionRate())
        m_DefaultStomachContents->GetProteinDigestionRate().Set(GetDefaultProteinDigestionRate());
    }
    if (config.FatAbsorptionFraction().present())
      io::Property::Marshall(config.FatAbsorptionFraction(), GetFatAbsorptionFraction());
    if (config.ProteinToUreaFraction().present())
      io::Property::Marshall(config.ProteinToUreaFraction(), GetProteinToUreaFraction());
    if (config.WaterDigestionRate().present())
      io::Property::Marshall(config.WaterDigestionRate(), GetWaterDigestionRate());
  }

  // Nervous
  if (in.NervousConfiguration().present()) {
    const CDM::NervousConfigurationData& config = in.NervousConfiguration().get();
    if (config.PupilDiameterBaseline().present())
      io::Property::Marshall(config.PupilDiameterBaseline(), GetPupilDiameterBaseline());
  }

  // Renal
  if (in.RenalConfiguration().present()) {
    const CDM::RenalConfigurationData& config = in.RenalConfiguration().get();

    if (config.EnableRenal().present())
      EnableRenal(config.EnableRenal().get());

    if (config.PlasmaSodiumConcentrationSetPoint().present())
      io::Property::Marshall(config.PlasmaSodiumConcentrationSetPoint(), GetPlasmaSodiumConcentrationSetPoint());

    if (config.LeftGlomerularFluidPermeabilityBaseline().present())
      io::Property::Marshall(config.LeftGlomerularFluidPermeabilityBaseline(), GetLeftGlomerularFluidPermeabilityBaseline());
    if (config.LeftGlomerularFilteringSurfaceAreaBaseline().present())
      io::Property::Marshall(config.LeftGlomerularFilteringSurfaceAreaBaseline(), GetLeftGlomerularFilteringSurfaceAreaBaseline());
    if (config.LeftTubularReabsorptionFluidPermeabilityBaseline().present())
      io::Property::Marshall(config.LeftTubularReabsorptionFluidPermeabilityBaseline(), GetLeftTubularReabsorptionFluidPermeabilityBaseline());
    if (config.LeftTubularReabsorptionFilteringSurfaceAreaBaseline().present())
      io::Property::Marshall(config.LeftTubularReabsorptionFilteringSurfaceAreaBaseline(), GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline());

    if (config.MaximumAfferentResistance().present())
      io::Property::Marshall(config.MaximumAfferentResistance(), GetMaximumAfferentResistance());
    if (config.MinimumAfferentResistance().present())
      io::Property::Marshall(config.MinimumAfferentResistance(), GetMinimumAfferentResistance());

    if (config.RightGlomerularFluidPermeabilityBaseline().present())
      io::Property::Marshall(config.RightGlomerularFluidPermeabilityBaseline(), GetRightGlomerularFluidPermeabilityBaseline());
    if (config.RightGlomerularFilteringSurfaceAreaBaseline().present())
      io::Property::Marshall(config.RightGlomerularFilteringSurfaceAreaBaseline(), GetRightGlomerularFilteringSurfaceAreaBaseline());
    if (config.RightTubularReabsorptionFluidPermeabilityBaseline().present())
      io::Property::Marshall(config.RightTubularReabsorptionFluidPermeabilityBaseline(), GetRightTubularReabsorptionFluidPermeabilityBaseline());
    if (config.RightTubularReabsorptionFilteringSurfaceAreaBaseline().present())
      io::Property::Marshall(config.RightTubularReabsorptionFilteringSurfaceAreaBaseline(), GetRightTubularReabsorptionFilteringSurfaceAreaBaseline());
    if (config.TargetSodiumDelivery().present())
      io::Property::Marshall(config.TargetSodiumDelivery(), GetTargetSodiumDelivery());
  }

  // Respiratory
  if (in.RespiratoryConfiguration().present()) {
    const CDM::RespiratoryConfigurationData& config = in.RespiratoryConfiguration().get();
    if (config.CentralControllerCO2PressureSetPoint().present())
      io::Property::Marshall(config.CentralControllerCO2PressureSetPoint(), GetCentralControllerCO2PressureSetPoint());
    if (config.CentralVentilatoryControllerGain().present())
      io::Property::Marshall(config.CentralVentilatoryControllerGain(), GetCentralVentilatoryControllerGain());
    if (config.PeripheralControllerCO2PressureSetPoint().present())
      io::Property::Marshall(config.PeripheralControllerCO2PressureSetPoint(), GetPeripheralControllerCO2PressureSetPoint());
    if (config.PeripheralVentilatoryControllerGain().present())
      io::Property::Marshall(config.PeripheralVentilatoryControllerGain(), GetPeripheralVentilatoryControllerGain());
    if (config.PleuralComplianceSensitivity().present())
      io::Property::Marshall(config.PleuralComplianceSensitivity(), GetPleuralComplianceSensitivity());
    if (config.PulmonaryVentilationRateMaximum().present())
      io::Property::Marshall(config.PulmonaryVentilationRateMaximum(), GetPulmonaryVentilationRateMaximum());
    if (config.VentilationTidalVolumeIntercept().present())
      io::Property::Marshall(config.VentilationTidalVolumeIntercept(), GetVentilationTidalVolumeIntercept());
    if (config.VentilatoryOcclusionPressure().present())
      io::Property::Marshall(config.VentilatoryOcclusionPressure(), GetVentilatoryOcclusionPressure());
  }

  // Tissue
  if (in.TissueConfiguration().present()) {
    const CDM::TissueConfigurationData& config = in.TissueConfiguration().get();

    if (config.EnableTissue().present())
      EnableTissue(config.EnableTissue().get());
  }

  return true;
}

CDM::BioGearsConfigurationData* BioGearsConfiguration::Unload() const
{
  CDM::BioGearsConfigurationData* data(new CDM::BioGearsConfigurationData());
  Unload(*data);
  return data;
}

void BioGearsConfiguration::Unload(CDM::BioGearsConfigurationData& data) const
{
  PhysiologyEngineConfiguration::Unload(data);

  // Barorecptor
  CDM::BaroreceptorConfigurationData* baro(new CDM::BaroreceptorConfigurationData());
  if (HasResponseSlope())
    io::Property::UnMarshall(*m_ResponseSlope, baro->ResponseSlope());
  if (HasHeartRateDistributedTimeDelay())
    io::Property::UnMarshall(*m_HeartRateDistributedTimeDelay, baro->HeartRateDistributedTimeDelay());
  ;
  if (HasHeartElastanceDistributedTimeDelay())
    io::Property::UnMarshall(*m_HeartElastanceDistributedTimeDelay, baro->HeartElastanceDistributedTimeDelay());
  ;
  if (HasSystemicResistanceDistributedTimeDelay())
    io::Property::UnMarshall(*m_SystemicResistanceDistributedTimeDelay, baro->SystemicResistanceDistributedTimeDelay());
  ;
  if (HasVenousComplianceDistributedTimeDelay())
    io::Property::UnMarshall(*m_VenousComplianceDistributedTimeDelay, baro->VenousComplianceDistributedTimeDelay());
  ;
  if (HasNormalizedHeartRateIntercept())
    io::Property::UnMarshall(*m_NormalizedHeartRateIntercept, baro->NormalizedHeartRateIntercept());
  if (HasNormalizedHeartRateSympatheticSlope())
    io::Property::UnMarshall(*m_NormalizedHeartRateSympatheticSlope, baro->NormalizedHeartRateSympatheticSlope());
  if (HasNormalizedHeartRateParasympatheticSlope())
    io::Property::UnMarshall(*m_NormalizedHeartRateParasympatheticSlope, baro->NormalizedHeartRateParasympatheticSlope());
  if (HasNormalizedHeartElastanceIntercept())
    io::Property::UnMarshall(*m_NormalizedHeartElastanceIntercept, baro->NormalizedHeartElastanceIntercept());
  if (HasNormalizedHeartElastanceSympatheticSlope())
    io::Property::UnMarshall(*m_NormalizedHeartElastanceSympatheticSlope, baro->NormalizedHeartElastanceSympatheticSlope());
  if (HasNormalizedResistanceIntercept())
    io::Property::UnMarshall(*m_NormalizedResistanceIntercept, baro->NormalizedResistanceIntercept());
  if (HasNormalizedResistanceSympatheticSlope())
    io::Property::UnMarshall(*m_NormalizedResistanceSympatheticSlope, baro->NormalizedComplianceParasympatheticSlope());
  if (HasNormalizedComplianceIntercept())
    io::Property::UnMarshall(*m_NormalizedComplianceIntercept, baro->NormalizedComplianceIntercept());
  if (HasNormalizedComplianceParasympatheticSlope())
    io::Property::UnMarshall(*m_NormalizedComplianceParasympatheticSlope, baro->NormalizedComplianceParasympatheticSlope());
  data.BaroreceptorConfiguration(std::unique_ptr<CDM::BaroreceptorConfigurationData>(baro));

  // Blood Chemistry
  CDM::BloodChemistryConfigurationData* bc(new CDM::BloodChemistryConfigurationData());
  if (HasMeanCorpuscularHemoglobin())
    io::Property::UnMarshall(*m_MeanCorpuscularHemoglobin, bc->MeanCorpuscularHemoglobin());
  if (HasMeanCorpuscularVolume())
    io::Property::UnMarshall(*m_MeanCorpuscularVolume, bc->MeanCorpuscularVolume());
  if (HasStandardDiffusionDistance())
    io::Property::UnMarshall(*m_StandardDiffusionDistance, bc->StandardDiffusionDistance());
  if (HasStandardOxygenDiffusionCoefficient())
    io::Property::UnMarshall(*m_StandardOxygenDiffusionCoefficient, bc->StandardOxygenDiffusionCoefficient());
  data.BloodChemistryConfiguration(std::unique_ptr<CDM::BloodChemistryConfigurationData>(bc));

  // Cardiovascular
  CDM::CardiovascularConfigurationData* cv(new CDM::CardiovascularConfigurationData());
  if (m_LeftHeartElastanceMaximum != nullptr)
    io::Property::UnMarshall(*m_LeftHeartElastanceMaximum, cv->LeftHeartElastanceMaximum());
  if (m_LeftHeartElastanceMinimum != nullptr)
    io::Property::UnMarshall(*m_LeftHeartElastanceMinimum, cv->LeftHeartElastanceMinimum());
  if (HasMinimumBloodVolumeFraction())
    io::Property::UnMarshall(*m_MinimumBloodVolumeFraction, cv->MinimumBloodVolumeFraction());
  if (m_RightHeartElastanceMaximum != nullptr)
    io::Property::UnMarshall(*m_RightHeartElastanceMaximum, cv->RightHeartElastanceMaximum());
  if (m_RightHeartElastanceMinimum != nullptr)
    io::Property::UnMarshall(*m_RightHeartElastanceMinimum, cv->RightHeartElastanceMinimum());
  if (HasStandardPulmonaryCapillaryCoverage())
    io::Property::UnMarshall(*m_StandardPulmonaryCapillaryCoverage, cv->StandardPulmonaryCapillaryCoverage());
  data.CardiovascularConfiguration(std::unique_ptr<CDM::CardiovascularConfigurationData>(cv));

  // Circuits
  CDM::CircuitConfigurationData* circuit(new CDM::CircuitConfigurationData());
  if (HasCardiovascularOpenResistance())
    io::Property::UnMarshall(*m_CardiovascularOpenResistance, circuit->CardiovascularOpenResistance());
  if (HasDefaultClosedElectricResistance())
    io::Property::UnMarshall(*m_DefaultClosedElectricResistance, circuit->DefaultClosedElectricResistance());
  if (HasDefaultClosedFlowResistance())
    io::Property::UnMarshall(*m_DefaultClosedFlowResistance, circuit->DefaultClosedFlowResistance());
  if (HasDefaultClosedHeatResistance())
    io::Property::UnMarshall(*m_DefaultClosedHeatResistance, circuit->DefaultClosedHeatResistance());
  if (HasDefaultOpenElectricResistance())
    io::Property::UnMarshall(*m_DefaultOpenElectricResistance, circuit->DefaultOpenElectricResistance());
  if (HasDefaultOpenFlowResistance())
    io::Property::UnMarshall(*m_DefaultOpenFlowResistance, circuit->DefaultOpenFlowResistance());
  if (HasDefaultOpenHeatResistance())
    io::Property::UnMarshall(*m_DefaultOpenHeatResistance, circuit->DefaultOpenHeatResistance());
  if (HasMachineClosedResistance())
    io::Property::UnMarshall(*m_MachineClosedResistance, circuit->MachineClosedResistance());
  if (HasMachineOpenResistance())
    io::Property::UnMarshall(*m_MachineOpenResistance, circuit->MachineOpenResistance());
  if (HasRespiratoryClosedResistance())
    io::Property::UnMarshall(*m_RespiratoryClosedResistance, circuit->RespiratoryClosedResistance());
  if (HasRespiratoryOpenResistance())
    io::Property::UnMarshall(*m_RespiratoryOpenResistance, circuit->RespiratoryOpenResistance());
  data.CircuitConfiguration(std::unique_ptr<CDM::CircuitConfigurationData>(circuit));

  // Constants
  CDM::ConstantsConfigurationData* consts(new CDM::ConstantsConfigurationData());
  if (HasOxygenMetabolicConstant())
    io::Property::UnMarshall(*m_OxygenMetabolicConstant, consts->OxygenMetabolicConstant());
  if (HasStefanBoltzmann())
    io::Property::UnMarshall(*m_StefanBoltzmann, consts->StefanBoltzmann());
  if (HasUniversalGasConstant())
    io::Property::UnMarshall(*m_UniversalGasConstant, consts->UniversalGasConstant());
  data.ConstantsConfiguration(std::unique_ptr<CDM::ConstantsConfigurationData>(consts));

  // Drugs
  CDM::DrugsConfigurationData* drugs(new CDM::DrugsConfigurationData());
  if (HasUsePDModel())
    drugs->PDModel(m_PDEnabled);
  data.DrugsConfiguration(std::unique_ptr<CDM::DrugsConfigurationData>(drugs));

  // Energy
  CDM::EnergyConfigurationData* energy(new CDM::EnergyConfigurationData());
  if (HasBodySpecificHeat())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->BodySpecificHeat());
  if (HasCoreTemperatureLow())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->CoreTemperatureLow());
  if (HasCoreTemperatureHigh())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->CoreTemperatureHigh());
  if (HasDeltaCoreTemperatureLow())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->DeltaCoreTemperatureLow());
  if (HasEnergyPerATP())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->EnergyPerATP());
  if (HasSweatHeatTransfer())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->SweatHeatTransfer());
  if (HasVaporSpecificHeat())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->VaporSpecificHeat());
  if (HasVaporizationEnergy())
    io::Property::UnMarshall(*m_UniversalGasConstant, energy->VaporizationEnergy());
  data.EnergyConfiguration(std::unique_ptr<CDM::EnergyConfigurationData>(energy));

  // Environment
  CDM::EnvironmentConfigurationData* env(new CDM::EnvironmentConfigurationData());
  if (HasAirDensity())
    io::Property::UnMarshall(*m_AirDensity, env->AirDensity());
  if (HasAirSpecificHeat())
    io::Property::UnMarshall(*m_AirSpecificHeat, env->AirSpecificHeat());
  if (HasMolarMassOfDryAir())
    io::Property::UnMarshall(*m_MolarMassOfDryAir, env->MolarMassOfDryAir());
  if (HasMolarMassOfWaterVapor())
    io::Property::UnMarshall(*m_MolarMassOfWaterVapor, env->MolarMassOfWaterVapor());
  if (HasInitialEnvironmentalConditions())
    env->InitialEnvironmentalConditions(std::unique_ptr<CDM::EnvironmentalConditionsData>(m_InitialEnvironmentalConditions->Unload()));
  if (HasWaterDensity())
    io::Property::UnMarshall(*m_WaterDensity, env->WaterDensity());
  data.EnvironmentConfiguration(std::unique_ptr<CDM::EnvironmentConfigurationData>(env));

  // Gastrointestinal
  CDM::GastrointestinalConfigurationData* gi(new CDM::GastrointestinalConfigurationData());
  if (HasCalciumAbsorptionFraction())
    io::Property::UnMarshall(*m_CalciumAbsorptionFraction, gi->CalciumAbsorptionFraction());
  if (HasCalciumDigestionRate())
    io::Property::UnMarshall(*m_CalciumDigestionRate, gi->CalciumDigestionRate());
  if (HasCarbohydrateAbsorptionFraction())
    io::Property::UnMarshall(*m_CarbohydrateAbsorptionFraction, gi->CarbohydrateAbsorptionFraction());
  if (HasDefaultCarbohydrateDigestionRate())
    io::Property::UnMarshall(*m_DefaultCarbohydrateDigestionRate, gi->DefaultCarbohydrateDigestionRate());
  if (HasDefaultFatDigestionRate())
    io::Property::UnMarshall(*m_DefaultFatDigestionRate, gi->DefaultFatDigestionRate());
  if (HasDefaultProteinDigestionRate())
    io::Property::UnMarshall(*m_DefaultProteinDigestionRate, gi->DefaultProteinDigestionRate());
  if (HasDefaultStomachContents())
    gi->DefaultStomachContents(std::unique_ptr<CDM::NutritionData>(m_DefaultStomachContents->Unload()));
  if (HasFatAbsorptionFraction())
    io::Property::UnMarshall(*m_FatAbsorptionFraction, gi->FatAbsorptionFraction());
  if (HasProteinToUreaFraction())
    io::Property::UnMarshall(*m_ProteinToUreaFraction, gi->ProteinToUreaFraction());
  if (HasWaterDigestionRate())
    io::Property::UnMarshall(*m_WaterDigestionRate, gi->WaterDigestionRate());
  data.GastrointestinalConfiguration(std::unique_ptr<CDM::GastrointestinalConfigurationData>(gi));

  // Nervous
  CDM::NervousConfigurationData* n(new CDM::NervousConfigurationData());
  if (HasPupilDiameterBaseline())
    io::Property::UnMarshall(*m_PupilDiameterBaseline, n->PupilDiameterBaseline());
  data.NervousConfiguration(std::unique_ptr<CDM::NervousConfigurationData>(n));

  // Renal
  CDM::RenalConfigurationData* renal(new CDM::RenalConfigurationData());
  if (HasEnableRenal())
    renal->EnableRenal(m_RenalEnabled);
  if (HasPlasmaSodiumConcentrationSetPoint())
    io::Property::UnMarshall(*m_PlasmaSodiumConcentrationSetPoint, renal->PlasmaSodiumConcentrationSetPoint());
  if (HasLeftGlomerularFilteringSurfaceAreaBaseline())
      io::Property::UnMarshall(*m_LeftGlomerularFilteringSurfaceAreaBaseline, renal->LeftGlomerularFilteringSurfaceAreaBaseline());
  if (HasLeftGlomerularFluidPermeabilityBaseline())
      io::Property::UnMarshall(*m_LeftGlomerularFluidPermeabilityBaseline, renal->LeftGlomerularFluidPermeabilityBaseline());
  if (HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline())
      io::Property::UnMarshall(*m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline, renal->LeftTubularReabsorptionFilteringSurfaceAreaBaseline());
  if (HasLeftTubularReabsorptionFluidPermeabilityBaseline())
      io::Property::UnMarshall(*m_LeftTubularReabsorptionFluidPermeabilityBaseline, renal->LeftTubularReabsorptionFluidPermeabilityBaseline());

  if (HasMaximumAfferentResistance())
    io::Property::UnMarshall(*m_MaximumAfferentResistance, renal->MaximumAfferentResistance());
  if (HasMinimumAfferentResistance())
      io::Property::UnMarshall(*m_MinimumAfferentResistance, renal->MinimumAfferentResistance());

  if (HasRightGlomerularFilteringSurfaceAreaBaseline())
    io::Property::UnMarshall(*m_RightGlomerularFilteringSurfaceAreaBaseline, renal->RightGlomerularFilteringSurfaceAreaBaseline());
  if (HasRightGlomerularFluidPermeabilityBaseline())
      io::Property::UnMarshall(*m_RightGlomerularFluidPermeabilityBaseline, renal->RightGlomerularFluidPermeabilityBaseline());
  if (HasRightTubularReabsorptionFilteringSurfaceAreaBaseline())
      io::Property::UnMarshall(*m_RightTubularReabsorptionFilteringSurfaceAreaBaseline, renal->RightTubularReabsorptionFilteringSurfaceAreaBaseline());
  if (HasRightTubularReabsorptionFluidPermeabilityBaseline())
      io::Property::UnMarshall(*m_RightTubularReabsorptionFluidPermeabilityBaseline, renal->RightTubularReabsorptionFluidPermeabilityBaseline());
  data.RenalConfiguration(std::unique_ptr<CDM::RenalConfigurationData>(renal));

  // Respiratory
  CDM::RespiratoryConfigurationData* resp(new CDM::RespiratoryConfigurationData());
  if (m_CentralControllerCO2PressureSetPoint != nullptr)
    io::Property::UnMarshall(*m_CentralControllerCO2PressureSetPoint, renal->RightTubularReabsorptionFluidPermeabilityBaseline());
  if (HasCentralVentilatoryControllerGain())
      io::Property::UnMarshall(*m_CentralVentilatoryControllerGain, resp->CentralVentilatoryControllerGain());
  if (m_PeripheralControllerCO2PressureSetPoint != nullptr)
      io::Property::UnMarshall(*m_PeripheralControllerCO2PressureSetPoint, resp->PeripheralControllerCO2PressureSetPoint());
  if (HasPeripheralVentilatoryControllerGain())
      io::Property::UnMarshall(*m_PeripheralVentilatoryControllerGain, resp->PeripheralVentilatoryControllerGain());
  if (HasPleuralComplianceSensitivity())
      io::Property::UnMarshall(*m_PleuralComplianceSensitivity, resp->PleuralComplianceSensitivity());
  if (m_PulmonaryVentilationRateMaximum != nullptr)
      io::Property::UnMarshall(*m_PulmonaryVentilationRateMaximum, resp->PulmonaryVentilationRateMaximum());
  if (HasVentilationTidalVolumeIntercept())
      io::Property::UnMarshall(*m_VentilationTidalVolumeIntercept, resp->VentilationTidalVolumeIntercept());
  if (HasVentilatoryOcclusionPressure())
      io::Property::UnMarshall(*m_VentilatoryOcclusionPressure, resp->VentilatoryOcclusionPressure());
  data.RespiratoryConfiguration(std::unique_ptr<CDM::RespiratoryConfigurationData>(resp));

  // Tissue
  CDM::TissueConfigurationData* tissue(new CDM::TissueConfigurationData());
  if (HasEnableTissue())
    tissue->EnableTissue(m_TissueEnabled);
  data.TissueConfiguration(std::unique_ptr<CDM::TissueConfigurationData>(tissue));
}

////////////////////
/** Baroreceptors */
////////////////////
bool BioGearsConfiguration::HasResponseSlope() const
{
  return m_ResponseSlope == nullptr ? false : m_ResponseSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetResponseSlope()
{
  if (m_ResponseSlope == nullptr)
    m_ResponseSlope = new SEScalar();
  return *m_ResponseSlope;
}
double BioGearsConfiguration::GetResponseSlope() const
{
  if (m_ResponseSlope == nullptr)
    return SEScalar::dNaN();
  return m_ResponseSlope->GetValue();
}

bool BioGearsConfiguration::HasHeartRateDistributedTimeDelay() const
{
  return m_HeartRateDistributedTimeDelay == nullptr ? false : m_HeartRateDistributedTimeDelay->IsValid();
}
SEScalarTime& BioGearsConfiguration::GetHeartRateDistributedTimeDelay()
{
  if (m_HeartRateDistributedTimeDelay == nullptr)
    m_HeartRateDistributedTimeDelay = new SEScalarTime();
  return *m_HeartRateDistributedTimeDelay;
}
double BioGearsConfiguration::GetHeartRateDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_HeartRateDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateDistributedTimeDelay->GetValue(unit);
}

bool BioGearsConfiguration::HasHeartElastanceDistributedTimeDelay() const
{
  return m_HeartElastanceDistributedTimeDelay == nullptr ? false : m_HeartElastanceDistributedTimeDelay->IsValid();
}
SEScalarTime& BioGearsConfiguration::GetHeartElastanceDistributedTimeDelay()
{
  if (m_HeartElastanceDistributedTimeDelay == nullptr)
    m_HeartElastanceDistributedTimeDelay = new SEScalarTime();
  return *m_HeartElastanceDistributedTimeDelay;
}
double BioGearsConfiguration::GetHeartElastanceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_HeartElastanceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_HeartElastanceDistributedTimeDelay->GetValue(unit);
}

bool BioGearsConfiguration::HasSystemicResistanceDistributedTimeDelay() const
{
  return m_SystemicResistanceDistributedTimeDelay == nullptr ? false : m_SystemicResistanceDistributedTimeDelay->IsValid();
}
SEScalarTime& BioGearsConfiguration::GetSystemicResistanceDistributedTimeDelay()
{
  if (m_SystemicResistanceDistributedTimeDelay == nullptr)
    m_SystemicResistanceDistributedTimeDelay = new SEScalarTime();
  return *m_SystemicResistanceDistributedTimeDelay;
}
double BioGearsConfiguration::GetSystemicResistanceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_SystemicResistanceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_SystemicResistanceDistributedTimeDelay->GetValue(unit);
}

bool BioGearsConfiguration::HasVenousComplianceDistributedTimeDelay() const
{
  return m_VenousComplianceDistributedTimeDelay == nullptr ? false : m_VenousComplianceDistributedTimeDelay->IsValid();
}
SEScalarTime& BioGearsConfiguration::GetVenousComplianceDistributedTimeDelay()
{
  if (m_VenousComplianceDistributedTimeDelay == nullptr)
    m_VenousComplianceDistributedTimeDelay = new SEScalarTime();
  return *m_VenousComplianceDistributedTimeDelay;
}
double BioGearsConfiguration::GetVenousComplianceDistributedTimeDelay(const TimeUnit& unit) const
{
  if (m_VenousComplianceDistributedTimeDelay == nullptr)
    return SEScalar::dNaN();
  return m_VenousComplianceDistributedTimeDelay->GetValue(unit);
}

bool BioGearsConfiguration::HasNormalizedHeartRateIntercept() const
{
  return m_NormalizedHeartRateIntercept == nullptr ? false : m_NormalizedHeartRateIntercept->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedHeartRateIntercept()
{
  if (m_NormalizedHeartRateIntercept == nullptr)
    m_NormalizedHeartRateIntercept = new SEScalar();
  return *m_NormalizedHeartRateIntercept;
}
double BioGearsConfiguration::GetNormalizedHeartRateIntercept() const
{
  if (m_NormalizedHeartRateIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateIntercept->GetValue();
}

bool BioGearsConfiguration::HasNormalizedHeartRateSympatheticSlope() const
{
  return m_NormalizedHeartRateSympatheticSlope == nullptr ? false : m_NormalizedHeartRateSympatheticSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedHeartRateSympatheticSlope()
{
  if (m_NormalizedHeartRateSympatheticSlope == nullptr)
    m_NormalizedHeartRateSympatheticSlope = new SEScalar();
  return *m_NormalizedHeartRateSympatheticSlope;
}
double BioGearsConfiguration::GetNormalizedHeartRateSympatheticSlope() const
{
  if (m_NormalizedHeartRateSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateSympatheticSlope->GetValue();
}

bool BioGearsConfiguration::HasNormalizedHeartRateParasympatheticSlope() const
{
  return m_NormalizedHeartRateParasympatheticSlope == nullptr ? false : m_NormalizedHeartRateParasympatheticSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedHeartRateParasympatheticSlope()
{
  if (m_NormalizedHeartRateParasympatheticSlope == nullptr)
    m_NormalizedHeartRateParasympatheticSlope = new SEScalar();
  return *m_NormalizedHeartRateParasympatheticSlope;
}
double BioGearsConfiguration::GetNormalizedHeartRateParasympatheticSlope() const
{
  if (m_NormalizedHeartRateParasympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartRateParasympatheticSlope->GetValue();
}

bool BioGearsConfiguration::HasNormalizedHeartElastanceIntercept() const
{
  return m_NormalizedHeartElastanceIntercept == nullptr ? false : m_NormalizedHeartElastanceIntercept->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedHeartElastanceIntercept()
{
  if (m_NormalizedHeartElastanceIntercept == nullptr)
    m_NormalizedHeartElastanceIntercept = new SEScalar();
  return *m_NormalizedHeartElastanceIntercept;
}
double BioGearsConfiguration::GetNormalizedHeartElastanceIntercept() const
{
  if (m_NormalizedHeartElastanceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartElastanceIntercept->GetValue();
}

bool BioGearsConfiguration::HasNormalizedHeartElastanceSympatheticSlope() const
{
  return m_NormalizedHeartElastanceSympatheticSlope == nullptr ? false : m_NormalizedHeartElastanceSympatheticSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedHeartElastanceSympatheticSlope()
{
  if (m_NormalizedHeartElastanceSympatheticSlope == nullptr)
    m_NormalizedHeartElastanceSympatheticSlope = new SEScalar();
  return *m_NormalizedHeartElastanceSympatheticSlope;
}
double BioGearsConfiguration::GetNormalizedHeartElastanceSympatheticSlope() const
{
  if (m_NormalizedHeartElastanceSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedHeartElastanceSympatheticSlope->GetValue();
}

bool BioGearsConfiguration::HasNormalizedResistanceIntercept() const
{
  return m_NormalizedResistanceIntercept == nullptr ? false : m_NormalizedResistanceIntercept->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedResistanceIntercept()
{
  if (m_NormalizedResistanceIntercept == nullptr)
    m_NormalizedResistanceIntercept = new SEScalar();
  return *m_NormalizedResistanceIntercept;
}
double BioGearsConfiguration::GetNormalizedResistanceIntercept() const
{
  if (m_NormalizedResistanceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedResistanceIntercept->GetValue();
}

bool BioGearsConfiguration::HasNormalizedResistanceSympatheticSlope() const
{
  return m_NormalizedResistanceSympatheticSlope == nullptr ? false : m_NormalizedResistanceSympatheticSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedResistanceSympatheticSlope()
{
  if (m_NormalizedResistanceSympatheticSlope == nullptr)
    m_NormalizedResistanceSympatheticSlope = new SEScalar();
  return *m_NormalizedResistanceSympatheticSlope;
}
double BioGearsConfiguration::GetNormalizedResistanceSympatheticSlope() const
{
  if (m_NormalizedResistanceSympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedResistanceSympatheticSlope->GetValue();
}

bool BioGearsConfiguration::HasNormalizedComplianceIntercept() const
{
  return m_NormalizedComplianceIntercept == nullptr ? false : m_NormalizedComplianceIntercept->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedComplianceIntercept()
{
  if (m_NormalizedComplianceIntercept == nullptr)
    m_NormalizedComplianceIntercept = new SEScalar();
  return *m_NormalizedComplianceIntercept;
}
double BioGearsConfiguration::GetNormalizedComplianceIntercept() const
{
  if (m_NormalizedComplianceIntercept == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedComplianceIntercept->GetValue();
}

bool BioGearsConfiguration::HasNormalizedComplianceParasympatheticSlope() const
{
  return m_NormalizedComplianceParasympatheticSlope == nullptr ? false : m_NormalizedComplianceParasympatheticSlope->IsValid();
}
SEScalar& BioGearsConfiguration::GetNormalizedComplianceParasympatheticSlope()
{
  if (m_NormalizedComplianceParasympatheticSlope == nullptr)
    m_NormalizedComplianceParasympatheticSlope = new SEScalar();
  return *m_NormalizedComplianceParasympatheticSlope;
}
double BioGearsConfiguration::GetNormalizedComplianceParasympatheticSlope() const
{
  if (m_NormalizedComplianceParasympatheticSlope == nullptr)
    return SEScalar::dNaN();
  return m_NormalizedComplianceParasympatheticSlope->GetValue();
}

//////////////////////
/** Blood Chemistry */
//////////////////////

bool BioGearsConfiguration::HasMeanCorpuscularHemoglobin() const
{
  return m_MeanCorpuscularHemoglobin == nullptr ? false : m_MeanCorpuscularHemoglobin->IsValid();
}
SEScalarMassPerAmount& BioGearsConfiguration::GetMeanCorpuscularHemoglobin()
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    m_MeanCorpuscularHemoglobin = new SEScalarMassPerAmount();
  return *m_MeanCorpuscularHemoglobin;
}
double BioGearsConfiguration::GetMeanCorpuscularHemoglobin(const MassPerAmountUnit& unit) const
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    return SEScalar::dNaN();
  return m_MeanCorpuscularHemoglobin->GetValue(unit);
}

bool BioGearsConfiguration::HasMeanCorpuscularVolume() const
{
  return m_MeanCorpuscularVolume == nullptr ? false : m_MeanCorpuscularVolume->IsValid();
}
SEScalarVolume& BioGearsConfiguration::GetMeanCorpuscularVolume()
{
  if (m_MeanCorpuscularVolume == nullptr)
    m_MeanCorpuscularVolume = new SEScalarVolume();
  return *m_MeanCorpuscularVolume;
}
double BioGearsConfiguration::GetMeanCorpuscularVolume(const VolumeUnit& unit) const
{
  if (m_MeanCorpuscularVolume == nullptr)
    return SEScalar::dNaN();
  return m_MeanCorpuscularVolume->GetValue(unit);
}

bool BioGearsConfiguration::HasStandardDiffusionDistance() const
{
  return m_StandardDiffusionDistance == nullptr ? false : m_StandardDiffusionDistance->IsValid();
}
SEScalarLength& BioGearsConfiguration::GetStandardDiffusionDistance()
{
  if (m_StandardDiffusionDistance == nullptr)
    m_StandardDiffusionDistance = new SEScalarLength();
  return *m_StandardDiffusionDistance;
}
double BioGearsConfiguration::GetStandardDiffusionDistance(const LengthUnit& unit) const
{
  if (m_StandardDiffusionDistance == nullptr)
    return SEScalar::dNaN();
  return m_StandardDiffusionDistance->GetValue(unit);
}

bool BioGearsConfiguration::HasStandardOxygenDiffusionCoefficient() const
{
  return m_StandardOxygenDiffusionCoefficient == nullptr ? false : m_StandardOxygenDiffusionCoefficient->IsValid();
}
SEScalarAreaPerTimePressure& BioGearsConfiguration::GetStandardOxygenDiffusionCoefficient()
{
  if (m_StandardOxygenDiffusionCoefficient == nullptr)
    m_StandardOxygenDiffusionCoefficient = new SEScalarAreaPerTimePressure();
  return *m_StandardOxygenDiffusionCoefficient;
}
double BioGearsConfiguration::GetStandardOxygenDiffusionCoefficient(const AreaPerTimePressureUnit& unit) const
{
  if (m_StandardOxygenDiffusionCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_StandardOxygenDiffusionCoefficient->GetValue(unit);
}

/////////////////////
/** Cardiovascular */
/////////////////////
bool BioGearsConfiguration::HasLeftHeartElastanceMaximum() const
{
  return m_LeftHeartElastanceMaximum == nullptr ? false : m_LeftHeartElastanceMaximum->IsValid();
}
SEScalarFlowElastance& BioGearsConfiguration::GetLeftHeartElastanceMaximum()
{
  if (m_LeftHeartElastanceMaximum == nullptr)
    m_LeftHeartElastanceMaximum = new SEScalarFlowElastance();
  return *m_LeftHeartElastanceMaximum;
}
double BioGearsConfiguration::GetLeftHeartElastanceMaximum(const FlowElastanceUnit& unit) const
{
  if (m_LeftHeartElastanceMaximum == nullptr)
    return SEScalar::dNaN();
  return m_LeftHeartElastanceMaximum->GetValue(unit);
}

bool BioGearsConfiguration::HasLeftHeartElastanceMinimum() const
{
  return m_LeftHeartElastanceMinimum == nullptr ? false : m_LeftHeartElastanceMinimum->IsValid();
}
SEScalarFlowElastance& BioGearsConfiguration::GetLeftHeartElastanceMinimum()
{
  if (m_LeftHeartElastanceMinimum == nullptr)
    m_LeftHeartElastanceMinimum = new SEScalarFlowElastance();
  return *m_LeftHeartElastanceMinimum;
}
double BioGearsConfiguration::GetLeftHeartElastanceMinimum(const FlowElastanceUnit& unit) const
{
  if (m_LeftHeartElastanceMinimum == nullptr)
    return SEScalar::dNaN();
  return m_LeftHeartElastanceMinimum->GetValue(unit);
}

bool BioGearsConfiguration::HasMinimumBloodVolumeFraction() const
{
  return m_MinimumBloodVolumeFraction == nullptr ? false : m_MinimumBloodVolumeFraction->IsValid();
}
SEScalarFraction& BioGearsConfiguration::GetMinimumBloodVolumeFraction()
{
  if (m_MinimumBloodVolumeFraction == nullptr)
    m_MinimumBloodVolumeFraction = new SEScalarFraction();
  return *m_MinimumBloodVolumeFraction;
}
double BioGearsConfiguration::GetMinimumBloodVolumeFraction() const
{
  if (m_MinimumBloodVolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_MinimumBloodVolumeFraction->GetValue();
}

bool BioGearsConfiguration::HasRightHeartElastanceMaximum() const
{
  return m_RightHeartElastanceMaximum == nullptr ? false : m_RightHeartElastanceMaximum->IsValid();
}
SEScalarFlowElastance& BioGearsConfiguration::GetRightHeartElastanceMaximum()
{
  if (m_RightHeartElastanceMaximum == nullptr)
    m_RightHeartElastanceMaximum = new SEScalarFlowElastance();
  return *m_RightHeartElastanceMaximum;
}
double BioGearsConfiguration::GetRightHeartElastanceMaximum(const FlowElastanceUnit& unit) const
{
  if (m_RightHeartElastanceMaximum == nullptr)
    return SEScalar::dNaN();
  return m_RightHeartElastanceMaximum->GetValue(unit);
}

bool BioGearsConfiguration::HasRightHeartElastanceMinimum() const
{
  return m_RightHeartElastanceMinimum == nullptr ? false : m_RightHeartElastanceMinimum->IsValid();
}
SEScalarFlowElastance& BioGearsConfiguration::GetRightHeartElastanceMinimum()
{
  if (m_RightHeartElastanceMinimum == nullptr)
    m_RightHeartElastanceMinimum = new SEScalarFlowElastance();
  return *m_RightHeartElastanceMinimum;
}
double BioGearsConfiguration::GetRightHeartElastanceMinimum(const FlowElastanceUnit& unit) const
{
  if (m_RightHeartElastanceMinimum == nullptr)
    return SEScalar::dNaN();
  return m_RightHeartElastanceMinimum->GetValue(unit);
}

bool BioGearsConfiguration::HasStandardPulmonaryCapillaryCoverage() const
{
  return m_StandardPulmonaryCapillaryCoverage == nullptr ? false : m_StandardPulmonaryCapillaryCoverage->IsValid();
}
SEScalar& BioGearsConfiguration::GetStandardPulmonaryCapillaryCoverage()
{
  if (m_StandardPulmonaryCapillaryCoverage == nullptr)
    m_StandardPulmonaryCapillaryCoverage = new SEScalar();
  return *m_StandardPulmonaryCapillaryCoverage;
}
double BioGearsConfiguration::GetStandardPulmonaryCapillaryCoverage() const
{
  if (m_StandardPulmonaryCapillaryCoverage == nullptr)
    return SEScalar::dNaN();
  return m_StandardPulmonaryCapillaryCoverage->GetValue();
}

//////////////
/** Circuit */
//////////////

bool BioGearsConfiguration::HasCardiovascularOpenResistance() const
{
  return m_CardiovascularOpenResistance == nullptr ? false : m_CardiovascularOpenResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetCardiovascularOpenResistance()
{
  if (m_CardiovascularOpenResistance == nullptr)
    m_CardiovascularOpenResistance = new SEScalarFlowResistance();
  return *m_CardiovascularOpenResistance;
}
double BioGearsConfiguration::GetCardiovascularOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_CardiovascularOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_CardiovascularOpenResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultClosedElectricResistance() const
{
  return m_DefaultClosedElectricResistance == nullptr ? false : m_DefaultClosedElectricResistance->IsValid();
}
SEScalarElectricResistance& BioGearsConfiguration::GetDefaultClosedElectricResistance()
{
  if (m_DefaultClosedElectricResistance == nullptr)
    m_DefaultClosedElectricResistance = new SEScalarElectricResistance();
  return *m_DefaultClosedElectricResistance;
}
double BioGearsConfiguration::GetDefaultClosedElectricResistance(const ElectricResistanceUnit& unit) const
{
  if (m_DefaultClosedElectricResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedElectricResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultClosedFlowResistance() const
{
  return m_DefaultClosedFlowResistance == nullptr ? false : m_DefaultClosedFlowResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetDefaultClosedFlowResistance()
{
  if (m_DefaultClosedFlowResistance == nullptr)
    m_DefaultClosedFlowResistance = new SEScalarFlowResistance();
  return *m_DefaultClosedFlowResistance;
}
double BioGearsConfiguration::GetDefaultClosedFlowResistance(const FlowResistanceUnit& unit) const
{
  if (m_DefaultClosedFlowResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedFlowResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultClosedHeatResistance() const
{
  return m_DefaultClosedHeatResistance == nullptr ? false : m_DefaultClosedHeatResistance->IsValid();
}
SEScalarHeatResistance& BioGearsConfiguration::GetDefaultClosedHeatResistance()
{
  if (m_DefaultClosedHeatResistance == nullptr)
    m_DefaultClosedHeatResistance = new SEScalarHeatResistance();
  return *m_DefaultClosedHeatResistance;
}
double BioGearsConfiguration::GetDefaultClosedHeatResistance(const HeatResistanceUnit& unit) const
{
  if (m_DefaultClosedHeatResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultClosedHeatResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultOpenElectricResistance() const
{
  return m_DefaultOpenElectricResistance == nullptr ? false : m_DefaultOpenElectricResistance->IsValid();
}
SEScalarElectricResistance& BioGearsConfiguration::GetDefaultOpenElectricResistance()
{
  if (m_DefaultOpenElectricResistance == nullptr)
    m_DefaultOpenElectricResistance = new SEScalarElectricResistance();
  return *m_DefaultOpenElectricResistance;
}
double BioGearsConfiguration::GetDefaultOpenElectricResistance(const ElectricResistanceUnit& unit) const
{
  if (m_DefaultOpenElectricResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenElectricResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultOpenFlowResistance() const
{
  return m_DefaultOpenFlowResistance == nullptr ? false : m_DefaultOpenFlowResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetDefaultOpenFlowResistance()
{
  if (m_DefaultOpenFlowResistance == nullptr)
    m_DefaultOpenFlowResistance = new SEScalarFlowResistance();
  return *m_DefaultOpenFlowResistance;
}
double BioGearsConfiguration::GetDefaultOpenFlowResistance(const FlowResistanceUnit& unit) const
{
  if (m_DefaultOpenFlowResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenFlowResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultOpenHeatResistance() const
{
  return m_DefaultOpenHeatResistance == nullptr ? false : m_DefaultOpenHeatResistance->IsValid();
}
SEScalarHeatResistance& BioGearsConfiguration::GetDefaultOpenHeatResistance()
{
  if (m_DefaultOpenHeatResistance == nullptr)
    m_DefaultOpenHeatResistance = new SEScalarHeatResistance();
  return *m_DefaultOpenHeatResistance;
}
double BioGearsConfiguration::GetDefaultOpenHeatResistance(const HeatResistanceUnit& unit) const
{
  if (m_DefaultOpenHeatResistance == nullptr)
    return SEScalar::dNaN();
  return m_DefaultOpenHeatResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasMachineClosedResistance() const
{
  return m_MachineClosedResistance == nullptr ? false : m_MachineClosedResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetMachineClosedResistance()
{
  if (m_MachineClosedResistance == nullptr)
    m_MachineClosedResistance = new SEScalarFlowResistance();
  return *m_MachineClosedResistance;
}
double BioGearsConfiguration::GetMachineClosedResistance(const FlowResistanceUnit& unit) const
{
  if (m_MachineClosedResistance == nullptr)
    return SEScalar::dNaN();
  return m_MachineClosedResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasMachineOpenResistance() const
{
  return m_MachineOpenResistance == nullptr ? false : m_MachineOpenResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetMachineOpenResistance()
{
  if (m_MachineOpenResistance == nullptr)
    m_MachineOpenResistance = new SEScalarFlowResistance();
  return *m_MachineOpenResistance;
}
double BioGearsConfiguration::GetMachineOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_MachineOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_MachineOpenResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasRespiratoryClosedResistance() const
{
  return m_RespiratoryClosedResistance == nullptr ? false : m_RespiratoryClosedResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetRespiratoryClosedResistance()
{
  if (m_RespiratoryClosedResistance == nullptr)
    m_RespiratoryClosedResistance = new SEScalarFlowResistance();
  return *m_RespiratoryClosedResistance;
}
double BioGearsConfiguration::GetRespiratoryClosedResistance(const FlowResistanceUnit& unit) const
{
  if (m_RespiratoryClosedResistance == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryClosedResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasRespiratoryOpenResistance() const
{
  return m_RespiratoryOpenResistance == nullptr ? false : m_RespiratoryOpenResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetRespiratoryOpenResistance()
{
  if (m_RespiratoryOpenResistance == nullptr)
    m_RespiratoryOpenResistance = new SEScalarFlowResistance();
  return *m_RespiratoryOpenResistance;
}
double BioGearsConfiguration::GetRespiratoryOpenResistance(const FlowResistanceUnit& unit) const
{
  if (m_RespiratoryOpenResistance == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryOpenResistance->GetValue(unit);
}

////////////////
/** Constants */
////////////////
bool BioGearsConfiguration::HasOxygenMetabolicConstant() const
{
  return m_OxygenMetabolicConstant == nullptr ? false : m_OxygenMetabolicConstant->IsValid();
}
SEScalar& BioGearsConfiguration::GetOxygenMetabolicConstant()
{
  if (m_OxygenMetabolicConstant == nullptr)
    m_OxygenMetabolicConstant = new SEScalar();
  return *m_OxygenMetabolicConstant;
}
double BioGearsConfiguration::GetOxygenMetabolicConstant() const
{
  if (m_OxygenMetabolicConstant == nullptr)
    return SEScalar::dNaN();
  return m_OxygenMetabolicConstant->GetValue();
}

bool BioGearsConfiguration::HasStefanBoltzmann() const
{
  return m_StefanBoltzmann == nullptr ? false : m_StefanBoltzmann->IsValid();
}
SEScalarPowerPerAreaTemperatureToTheFourth& BioGearsConfiguration::GetStefanBoltzmann()
{
  if (m_StefanBoltzmann == nullptr)
    m_StefanBoltzmann = new SEScalarPowerPerAreaTemperatureToTheFourth();
  return *m_StefanBoltzmann;
}
double BioGearsConfiguration::GetStefanBoltzmann(const PowerPerAreaTemperatureToTheFourthUnit& unit) const
{
  if (m_StefanBoltzmann == nullptr)
    return SEScalar::dNaN();
  return m_StefanBoltzmann->GetValue(unit);
}

bool BioGearsConfiguration::HasUniversalGasConstant() const
{
  return m_UniversalGasConstant == nullptr ? false : m_UniversalGasConstant->IsValid();
}
SEScalarHeatCapacitancePerAmount& BioGearsConfiguration::GetUniversalGasConstant()
{
  if (m_UniversalGasConstant == nullptr)
    m_UniversalGasConstant = new SEScalarHeatCapacitancePerAmount();
  return *m_UniversalGasConstant;
}
double BioGearsConfiguration::GetUniversalGasConstant(const HeatCapacitancePerAmountUnit& unit) const
{
  if (m_UniversalGasConstant == nullptr)
    return SEScalar::dNaN();
  return m_UniversalGasConstant->GetValue(unit);
}

/////////////
/** Energy */
/////////////
bool BioGearsConfiguration::HasBodySpecificHeat() const
{
  return m_BodySpecificHeat == nullptr ? false : m_BodySpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& BioGearsConfiguration::GetBodySpecificHeat()
{
  if (m_BodySpecificHeat == nullptr)
    m_BodySpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_BodySpecificHeat;
}
double BioGearsConfiguration::GetBodySpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_BodySpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_BodySpecificHeat->GetValue(unit);
}

bool BioGearsConfiguration::HasCarbondDioxideProductionFromOxygenConsumptionConstant() const
{
  return m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr ? false : m_CarbondDioxideProductionFromOxygenConsumptionConstant->IsValid();
}
SEScalar& BioGearsConfiguration::GetCarbondDioxideProductionFromOxygenConsumptionConstant()
{
  if (m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr)
    m_CarbondDioxideProductionFromOxygenConsumptionConstant = new SEScalar();
  return *m_CarbondDioxideProductionFromOxygenConsumptionConstant;
}
double BioGearsConfiguration::GetCarbondDioxideProductionFromOxygenConsumptionConstant() const
{
  if (m_CarbondDioxideProductionFromOxygenConsumptionConstant == nullptr)
    return SEScalar::dNaN();
  return m_CarbondDioxideProductionFromOxygenConsumptionConstant->GetValue();
}

bool BioGearsConfiguration::HasCoreTemperatureHigh() const
{
  return m_CoreTemperatureHigh == nullptr ? false : m_CoreTemperatureHigh->IsValid();
}
SEScalarTemperature& BioGearsConfiguration::GetCoreTemperatureHigh()
{
  if (m_CoreTemperatureHigh == nullptr)
    m_CoreTemperatureHigh = new SEScalarTemperature();
  return *m_CoreTemperatureHigh;
}
double BioGearsConfiguration::GetCoreTemperatureHigh(const TemperatureUnit& unit) const
{
  if (m_CoreTemperatureHigh == nullptr)
    return SEScalar::dNaN();
  return m_CoreTemperatureHigh->GetValue(unit);
}

bool BioGearsConfiguration::HasCoreTemperatureLow() const
{
  return m_CoreTemperatureLow == nullptr ? false : m_CoreTemperatureLow->IsValid();
}
SEScalarTemperature& BioGearsConfiguration::GetCoreTemperatureLow()
{
  if (m_CoreTemperatureLow == nullptr)
    m_CoreTemperatureLow = new SEScalarTemperature();
  return *m_CoreTemperatureLow;
}
double BioGearsConfiguration::GetCoreTemperatureLow(const TemperatureUnit& unit) const
{
  if (m_CoreTemperatureLow == nullptr)
    return SEScalar::dNaN();
  return m_CoreTemperatureLow->GetValue(unit);
}

bool BioGearsConfiguration::HasDeltaCoreTemperatureLow() const
{
  return m_DeltaCoreTemperatureLow == nullptr ? false : m_DeltaCoreTemperatureLow->IsValid();
}
SEScalarTemperature& BioGearsConfiguration::GetDeltaCoreTemperatureLow()
{
  if (m_DeltaCoreTemperatureLow == nullptr)
    m_DeltaCoreTemperatureLow = new SEScalarTemperature();
  return *m_DeltaCoreTemperatureLow;
}
double BioGearsConfiguration::GetDeltaCoreTemperatureLow(const TemperatureUnit& unit) const
{
  if (m_DeltaCoreTemperatureLow == nullptr)
    return SEScalar::dNaN();
  return m_DeltaCoreTemperatureLow->GetValue(unit);
}

bool BioGearsConfiguration::HasEnergyPerATP() const
{
  return m_EnergyPerATP == nullptr ? false : m_EnergyPerATP->IsValid();
}
SEScalarEnergyPerAmount& BioGearsConfiguration::GetEnergyPerATP()
{
  if (m_EnergyPerATP == nullptr)
    m_EnergyPerATP = new SEScalarEnergyPerAmount();
  return *m_EnergyPerATP;
}
double BioGearsConfiguration::GetEnergyPerATP(const EnergyPerAmountUnit& unit) const
{
  if (m_EnergyPerATP == nullptr)
    return SEScalar::dNaN();
  return m_EnergyPerATP->GetValue(unit);
}

bool BioGearsConfiguration::HasSweatHeatTransfer() const
{
  return m_SweatHeatTransfer == nullptr ? false : m_SweatHeatTransfer->IsValid();
}
SEScalarHeatConductance& BioGearsConfiguration::GetSweatHeatTransfer()
{
  if (m_SweatHeatTransfer == nullptr)
    m_SweatHeatTransfer = new SEScalarHeatConductance();
  return *m_SweatHeatTransfer;
}
double BioGearsConfiguration::GetSweatHeatTransfer(const HeatConductanceUnit& unit) const
{
  if (m_SweatHeatTransfer == nullptr)
    return SEScalar::dNaN();
  return m_SweatHeatTransfer->GetValue(unit);
}

bool BioGearsConfiguration::HasVaporizationEnergy() const
{
  return m_VaporizationEnergy == nullptr ? false : m_VaporizationEnergy->IsValid();
}
SEScalarEnergyPerMass& BioGearsConfiguration::GetVaporizationEnergy()
{
  if (m_VaporizationEnergy == nullptr)
    m_VaporizationEnergy = new SEScalarEnergyPerMass();
  return *m_VaporizationEnergy;
}
double BioGearsConfiguration::GetVaporizationEnergy(const EnergyPerMassUnit& unit) const
{
  if (m_VaporizationEnergy == nullptr)
    return SEScalar::dNaN();
  return m_VaporizationEnergy->GetValue(unit);
}

bool BioGearsConfiguration::HasVaporSpecificHeat() const
{
  return m_VaporSpecificHeat == nullptr ? false : m_VaporSpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& BioGearsConfiguration::GetVaporSpecificHeat()
{
  if (m_VaporSpecificHeat == nullptr)
    m_VaporSpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_VaporSpecificHeat;
}
double BioGearsConfiguration::GetVaporSpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_VaporSpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_VaporSpecificHeat->GetValue(unit);
}

//////////////////
/** Environment */
//////////////////
bool BioGearsConfiguration::HasAirDensity() const
{
  return m_AirDensity == nullptr ? false : m_AirDensity->IsValid();
}
SEScalarMassPerVolume& BioGearsConfiguration::GetAirDensity()
{
  if (m_AirDensity == nullptr)
    m_AirDensity = new SEScalarMassPerVolume();
  return *m_AirDensity;
}
double BioGearsConfiguration::GetAirDensity(const MassPerVolumeUnit& unit) const
{
  if (m_AirDensity == nullptr)
    return SEScalar::dNaN();
  return m_AirDensity->GetValue(unit);
}

bool BioGearsConfiguration::HasAirSpecificHeat() const
{
  return m_AirSpecificHeat == nullptr ? false : m_AirSpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& BioGearsConfiguration::GetAirSpecificHeat()
{
  if (m_AirSpecificHeat == nullptr)
    m_AirSpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_AirSpecificHeat;
}
double BioGearsConfiguration::GetAirSpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_AirSpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_AirSpecificHeat->GetValue(unit);
}

bool BioGearsConfiguration::HasMolarMassOfDryAir() const
{
  return m_MolarMassOfDryAir == nullptr ? false : m_MolarMassOfDryAir->IsValid();
}
SEScalarMassPerAmount& BioGearsConfiguration::GetMolarMassOfDryAir()
{
  if (m_MolarMassOfDryAir == nullptr)
    m_MolarMassOfDryAir = new SEScalarMassPerAmount();
  return *m_MolarMassOfDryAir;
}
double BioGearsConfiguration::GetMolarMassOfDryAir(const MassPerAmountUnit& unit) const
{
  if (m_MolarMassOfDryAir == nullptr)
    return SEScalar::dNaN();
  return m_MolarMassOfDryAir->GetValue(unit);
}

bool BioGearsConfiguration::HasMolarMassOfWaterVapor() const
{
  return m_MolarMassOfWaterVapor == nullptr ? false : m_MolarMassOfWaterVapor->IsValid();
}
SEScalarMassPerAmount& BioGearsConfiguration::GetMolarMassOfWaterVapor()
{
  if (m_MolarMassOfWaterVapor == nullptr)
    m_MolarMassOfWaterVapor = new SEScalarMassPerAmount();
  return *m_MolarMassOfWaterVapor;
}
double BioGearsConfiguration::GetMolarMassOfWaterVapor(const MassPerAmountUnit& unit) const
{
  if (m_MolarMassOfWaterVapor == nullptr)
    return SEScalar::dNaN();
  return m_MolarMassOfWaterVapor->GetValue(unit);
}

bool BioGearsConfiguration::HasInitialEnvironmentalConditions() const
{
  return m_InitialEnvironmentalConditions != nullptr;
}
SEEnvironmentalConditions& BioGearsConfiguration::GetInitialEnvironmentalConditions()
{
  if (m_InitialEnvironmentalConditions == nullptr)
    m_InitialEnvironmentalConditions = new SEEnvironmentalConditions(m_Substances);
  return *m_InitialEnvironmentalConditions;
}
const SEEnvironmentalConditions* BioGearsConfiguration::GetInitialEnvironmentalConditions() const
{
  return m_InitialEnvironmentalConditions;
}

bool BioGearsConfiguration::HasWaterDensity() const
{
  return m_WaterDensity == nullptr ? false : m_WaterDensity->IsValid();
}
SEScalarMassPerVolume& BioGearsConfiguration::GetWaterDensity()
{
  if (m_WaterDensity == nullptr)
    m_WaterDensity = new SEScalarMassPerVolume();
  return *m_WaterDensity;
}
double BioGearsConfiguration::GetWaterDensity(const MassPerVolumeUnit& unit) const
{
  if (m_WaterDensity == nullptr)
    return SEScalar::dNaN();
  return m_WaterDensity->GetValue(unit);
}

///////////////////////
/** Gastrointestinal */
///////////////////////

bool BioGearsConfiguration::HasCalciumDigestionRate() const
{
  return m_CalciumDigestionRate == nullptr ? false : m_CalciumDigestionRate->IsValid();
}
SEScalarMassPerTime& BioGearsConfiguration::GetCalciumDigestionRate()
{
  if (m_CalciumDigestionRate == nullptr)
    m_CalciumDigestionRate = new SEScalarMassPerTime();
  return *m_CalciumDigestionRate;
}
double BioGearsConfiguration::GetCalciumDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_CalciumDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_CalciumDigestionRate->GetValue(unit);
}

bool BioGearsConfiguration::HasCalciumAbsorptionFraction() const
{
  return m_CalciumAbsorptionFraction == nullptr ? false : m_CalciumAbsorptionFraction->IsValid();
}
SEScalarFraction& BioGearsConfiguration::GetCalciumAbsorptionFraction()
{
  if (m_CalciumAbsorptionFraction == nullptr)
    m_CalciumAbsorptionFraction = new SEScalarFraction();
  return *m_CalciumAbsorptionFraction;
}
double BioGearsConfiguration::GetCalciumAbsorptionFraction() const
{
  if (m_CalciumAbsorptionFraction == nullptr)
    return SEScalar::dNaN();
  return m_CalciumAbsorptionFraction->GetValue();
}

bool BioGearsConfiguration::HasCarbohydrateAbsorptionFraction() const
{
  return m_CarbohydrateAbsorptionFraction == nullptr ? false : m_CarbohydrateAbsorptionFraction->IsValid();
}
SEScalarFraction& BioGearsConfiguration::GetCarbohydrateAbsorptionFraction()
{
  if (m_CarbohydrateAbsorptionFraction == nullptr)
    m_CarbohydrateAbsorptionFraction = new SEScalarFraction();
  return *m_CarbohydrateAbsorptionFraction;
}
double BioGearsConfiguration::GetCarbohydrateAbsorptionFraction() const
{
  if (m_CarbohydrateAbsorptionFraction == nullptr)
    return SEScalar::dNaN();
  return m_CarbohydrateAbsorptionFraction->GetValue();
}

bool BioGearsConfiguration::HasDefaultCarbohydrateDigestionRate() const
{
  return m_DefaultCarbohydrateDigestionRate == nullptr ? false : m_DefaultCarbohydrateDigestionRate->IsValid();
}
SEScalarMassPerTime& BioGearsConfiguration::GetDefaultCarbohydrateDigestionRate()
{
  if (m_DefaultCarbohydrateDigestionRate == nullptr)
    m_DefaultCarbohydrateDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultCarbohydrateDigestionRate;
}
double BioGearsConfiguration::GetDefaultCarbohydrateDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultCarbohydrateDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultCarbohydrateDigestionRate->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultFatDigestionRate() const
{
  return m_DefaultFatDigestionRate == nullptr ? false : m_DefaultFatDigestionRate->IsValid();
}
SEScalarMassPerTime& BioGearsConfiguration::GetDefaultFatDigestionRate()
{
  if (m_DefaultFatDigestionRate == nullptr)
    m_DefaultFatDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultFatDigestionRate;
}
double BioGearsConfiguration::GetDefaultFatDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultFatDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultFatDigestionRate->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultProteinDigestionRate() const
{
  return m_DefaultProteinDigestionRate == nullptr ? false : m_DefaultProteinDigestionRate->IsValid();
}
SEScalarMassPerTime& BioGearsConfiguration::GetDefaultProteinDigestionRate()
{
  if (m_DefaultProteinDigestionRate == nullptr)
    m_DefaultProteinDigestionRate = new SEScalarMassPerTime();
  return *m_DefaultProteinDigestionRate;
}
double BioGearsConfiguration::GetDefaultProteinDigestionRate(const MassPerTimeUnit& unit) const
{
  if (m_DefaultProteinDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_DefaultProteinDigestionRate->GetValue(unit);
}

bool BioGearsConfiguration::HasDefaultStomachContents() const
{
  return m_DefaultStomachContents != nullptr;
}
SENutrition& BioGearsConfiguration::GetDefaultStomachContents()
{
  if (m_DefaultStomachContents == nullptr)
    m_DefaultStomachContents = new SENutrition(GetLogger());
  return *m_DefaultStomachContents;
}
const SENutrition* BioGearsConfiguration::GetDefaultStomachContents() const
{
  return m_DefaultStomachContents;
}

bool BioGearsConfiguration::HasFatAbsorptionFraction() const
{
  return m_FatAbsorptionFraction == nullptr ? false : m_FatAbsorptionFraction->IsValid();
}
SEScalarFraction& BioGearsConfiguration::GetFatAbsorptionFraction()
{
  if (m_FatAbsorptionFraction == nullptr)
    m_FatAbsorptionFraction = new SEScalarFraction();
  return *m_FatAbsorptionFraction;
}
double BioGearsConfiguration::GetFatAbsorptionFraction() const
{
  if (m_FatAbsorptionFraction == nullptr)
    return SEScalar::dNaN();
  return m_FatAbsorptionFraction->GetValue();
}

bool BioGearsConfiguration::HasProteinToUreaFraction() const
{
  return m_ProteinToUreaFraction == nullptr ? false : m_ProteinToUreaFraction->IsValid();
}
SEScalarFraction& BioGearsConfiguration::GetProteinToUreaFraction()
{
  if (m_ProteinToUreaFraction == nullptr)
    m_ProteinToUreaFraction = new SEScalarFraction();
  return *m_ProteinToUreaFraction;
}
double BioGearsConfiguration::GetProteinToUreaFraction() const
{
  if (m_ProteinToUreaFraction == nullptr)
    return SEScalar::dNaN();
  return m_ProteinToUreaFraction->GetValue();
}

bool BioGearsConfiguration::HasWaterDigestionRate() const
{
  return m_WaterDigestionRate == nullptr ? false : m_WaterDigestionRate->IsValid();
}
SEScalarVolumePerTime& BioGearsConfiguration::GetWaterDigestionRate()
{
  if (m_WaterDigestionRate == nullptr)
    m_WaterDigestionRate = new SEScalarVolumePerTime();
  return *m_WaterDigestionRate;
}
double BioGearsConfiguration::GetWaterDigestionRate(const VolumePerTimeUnit& unit) const
{
  if (m_WaterDigestionRate == nullptr)
    return SEScalar::dNaN();
  return m_WaterDigestionRate->GetValue(unit);
}

///////////////
/** Nervous */
/////////////

bool BioGearsConfiguration::HasPupilDiameterBaseline() const
{
  return m_PupilDiameterBaseline == nullptr ? false : m_PupilDiameterBaseline->IsValid();
}
SEScalarLength& BioGearsConfiguration::GetPupilDiameterBaseline()
{
  if (m_PupilDiameterBaseline == nullptr)
    m_PupilDiameterBaseline = new SEScalarLength();
  return *m_PupilDiameterBaseline;
}
double BioGearsConfiguration::GetPupilDiameterBaseline(const LengthUnit& unit) const
{
  if (m_PupilDiameterBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PupilDiameterBaseline->GetValue(unit);
}

////////////
/** Renal */
////////////

bool BioGearsConfiguration::HasPlasmaSodiumConcentrationSetPoint() const
{
  return m_PlasmaSodiumConcentrationSetPoint == nullptr ? false : m_PlasmaSodiumConcentrationSetPoint->IsValid();
}
SEScalarMassPerVolume& BioGearsConfiguration::GetPlasmaSodiumConcentrationSetPoint()
{
  if (m_PlasmaSodiumConcentrationSetPoint == nullptr)
    m_PlasmaSodiumConcentrationSetPoint = new SEScalarMassPerVolume();
  return *m_PlasmaSodiumConcentrationSetPoint;
}
double BioGearsConfiguration::GetPlasmaSodiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_PlasmaSodiumConcentrationSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PlasmaSodiumConcentrationSetPoint->GetValue(unit);
}

bool BioGearsConfiguration::HasPeritubularPotassiumConcentrationSetPoint() const
{
  return m_PeritubularPotassiumConcentrationSetPoint == nullptr ? false : m_PeritubularPotassiumConcentrationSetPoint->IsValid();
}
SEScalarMassPerVolume& BioGearsConfiguration::GetPeritubularPotassiumConcentrationSetPoint()
{
  if (m_PeritubularPotassiumConcentrationSetPoint == nullptr)
    m_PeritubularPotassiumConcentrationSetPoint = new SEScalarMassPerVolume();
  return *m_PeritubularPotassiumConcentrationSetPoint;
}
double BioGearsConfiguration::GetPeritubularPotassiumConcentrationSetPoint(const MassPerVolumeUnit& unit) const
{
  if (m_PeritubularPotassiumConcentrationSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PeritubularPotassiumConcentrationSetPoint->GetValue(unit);
}

bool BioGearsConfiguration::HasLeftGlomerularFluidPermeabilityBaseline() const
{
  return m_LeftGlomerularFluidPermeabilityBaseline == nullptr ? false : m_LeftGlomerularFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& BioGearsConfiguration::GetLeftGlomerularFluidPermeabilityBaseline()
{
  if (m_LeftGlomerularFluidPermeabilityBaseline == nullptr)
    m_LeftGlomerularFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_LeftGlomerularFluidPermeabilityBaseline;
}
double BioGearsConfiguration::GetLeftGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftGlomerularFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFluidPermeabilityBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasLeftGlomerularFilteringSurfaceAreaBaseline() const
{
  return m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr ? false : m_LeftGlomerularFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& BioGearsConfiguration::GetLeftGlomerularFilteringSurfaceAreaBaseline()
{
  if (m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr)
    m_LeftGlomerularFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_LeftGlomerularFilteringSurfaceAreaBaseline;
}
double BioGearsConfiguration::GetLeftGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_LeftGlomerularFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftGlomerularFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasLeftTubularReabsorptionFluidPermeabilityBaseline() const
{
  return m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr ? false : m_LeftTubularReabsorptionFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& BioGearsConfiguration::GetLeftTubularReabsorptionFluidPermeabilityBaseline()
{
  if (m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    m_LeftTubularReabsorptionFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_LeftTubularReabsorptionFluidPermeabilityBaseline;
}
double BioGearsConfiguration::GetLeftTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFluidPermeabilityBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasLeftTubularReabsorptionFilteringSurfaceAreaBaseline() const
{
  return m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr ? false : m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& BioGearsConfiguration::GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline()
{
  if (m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline;
}
double BioGearsConfiguration::GetLeftTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_LeftTubularReabsorptionFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasMaximumAfferentResistance() const
{
  return m_MaximumAfferentResistance == nullptr ? false : m_MaximumAfferentResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetMaximumAfferentResistance()
{
  if (m_MaximumAfferentResistance == nullptr)
    m_MaximumAfferentResistance = new SEScalarFlowResistance();
  return *m_MaximumAfferentResistance;
}
double BioGearsConfiguration::GetMaximumAfferentResistance(const FlowResistanceUnit& unit) const
{
  if (m_MaximumAfferentResistance == nullptr)
    return SEScalar::dNaN();
  return m_MaximumAfferentResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasMinimumAfferentResistance() const
{
  return m_MinimumAfferentResistance == nullptr ? false : m_MinimumAfferentResistance->IsValid();
}
SEScalarFlowResistance& BioGearsConfiguration::GetMinimumAfferentResistance()
{
  if (m_MinimumAfferentResistance == nullptr)
    m_MinimumAfferentResistance = new SEScalarFlowResistance();
  return *m_MinimumAfferentResistance;
}
double BioGearsConfiguration::GetMinimumAfferentResistance(const FlowResistanceUnit& unit) const
{
  if (m_MinimumAfferentResistance == nullptr)
    return SEScalar::dNaN();
  return m_MinimumAfferentResistance->GetValue(unit);
}

bool BioGearsConfiguration::HasRightGlomerularFluidPermeabilityBaseline() const
{
  return m_RightGlomerularFluidPermeabilityBaseline == nullptr ? false : m_RightGlomerularFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& BioGearsConfiguration::GetRightGlomerularFluidPermeabilityBaseline()
{
  if (m_RightGlomerularFluidPermeabilityBaseline == nullptr)
    m_RightGlomerularFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_RightGlomerularFluidPermeabilityBaseline;
}
double BioGearsConfiguration::GetRightGlomerularFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightGlomerularFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFluidPermeabilityBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasRightGlomerularFilteringSurfaceAreaBaseline() const
{
  return m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr ? false : m_RightGlomerularFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& BioGearsConfiguration::GetRightGlomerularFilteringSurfaceAreaBaseline()
{
  if (m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr)
    m_RightGlomerularFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_RightGlomerularFilteringSurfaceAreaBaseline;
}
double BioGearsConfiguration::GetRightGlomerularFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_RightGlomerularFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightGlomerularFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasRightTubularReabsorptionFluidPermeabilityBaseline() const
{
  return m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr ? false : m_RightTubularReabsorptionFluidPermeabilityBaseline->IsValid();
}
SEScalarVolumePerTimePressureArea& BioGearsConfiguration::GetRightTubularReabsorptionFluidPermeabilityBaseline()
{
  if (m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    m_RightTubularReabsorptionFluidPermeabilityBaseline = new SEScalarVolumePerTimePressureArea();
  return *m_RightTubularReabsorptionFluidPermeabilityBaseline;
}
double BioGearsConfiguration::GetRightTubularReabsorptionFluidPermeabilityBaseline(const VolumePerTimePressureAreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFluidPermeabilityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFluidPermeabilityBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasRightTubularReabsorptionFilteringSurfaceAreaBaseline() const
{
  return m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr ? false : m_RightTubularReabsorptionFilteringSurfaceAreaBaseline->IsValid();
}
SEScalarArea& BioGearsConfiguration::GetRightTubularReabsorptionFilteringSurfaceAreaBaseline()
{
  if (m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    m_RightTubularReabsorptionFilteringSurfaceAreaBaseline = new SEScalarArea();
  return *m_RightTubularReabsorptionFilteringSurfaceAreaBaseline;
}
double BioGearsConfiguration::GetRightTubularReabsorptionFilteringSurfaceAreaBaseline(const AreaUnit& unit) const
{
  if (m_RightTubularReabsorptionFilteringSurfaceAreaBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RightTubularReabsorptionFilteringSurfaceAreaBaseline->GetValue(unit);
}

bool BioGearsConfiguration::HasTargetSodiumDelivery()
{
  return m_TargetSodiumDelivery == nullptr ? false : m_TargetSodiumDelivery->IsValid();
}
SEScalarMassPerTime& BioGearsConfiguration::GetTargetSodiumDelivery()
{
  if (m_TargetSodiumDelivery == nullptr)
    m_TargetSodiumDelivery = new SEScalarMassPerTime();
  return *m_TargetSodiumDelivery;
}

//////////////////
/** Respiratory */
//////////////////
bool BioGearsConfiguration::HasCentralControllerCO2PressureSetPoint() const
{
  return m_CentralControllerCO2PressureSetPoint == nullptr ? false : m_CentralControllerCO2PressureSetPoint->IsValid();
}
SEScalarPressure& BioGearsConfiguration::GetCentralControllerCO2PressureSetPoint()
{
  if (m_CentralControllerCO2PressureSetPoint == nullptr)
    m_CentralControllerCO2PressureSetPoint = new SEScalarPressure();
  return *m_CentralControllerCO2PressureSetPoint;
}
double BioGearsConfiguration::GetCentralControllerCO2PressureSetPoint(const PressureUnit& unit) const
{
  if (m_CentralControllerCO2PressureSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_CentralControllerCO2PressureSetPoint->GetValue(unit);
}

bool BioGearsConfiguration::HasCentralVentilatoryControllerGain() const
{
  return m_CentralVentilatoryControllerGain == nullptr ? false : m_CentralVentilatoryControllerGain->IsValid();
}
SEScalar& BioGearsConfiguration::GetCentralVentilatoryControllerGain()
{
  if (m_CentralVentilatoryControllerGain == nullptr)
    m_CentralVentilatoryControllerGain = new SEScalar();
  return *m_CentralVentilatoryControllerGain;
}
double BioGearsConfiguration::GetCentralVentilatoryControllerGain() const
{
  if (m_CentralVentilatoryControllerGain == nullptr)
    return SEScalar::dNaN();
  return m_CentralVentilatoryControllerGain->GetValue();
}

bool BioGearsConfiguration::HasPeripheralControllerCO2PressureSetPoint() const
{
  return m_PeripheralControllerCO2PressureSetPoint == nullptr ? false : m_PeripheralControllerCO2PressureSetPoint->IsValid();
}
SEScalarPressure& BioGearsConfiguration::GetPeripheralControllerCO2PressureSetPoint()
{
  if (m_PeripheralControllerCO2PressureSetPoint == nullptr)
    m_PeripheralControllerCO2PressureSetPoint = new SEScalarPressure();
  return *m_PeripheralControllerCO2PressureSetPoint;
}
double BioGearsConfiguration::GetPeripheralControllerCO2PressureSetPoint(const PressureUnit& unit) const
{
  if (m_PeripheralControllerCO2PressureSetPoint == nullptr)
    return SEScalar::dNaN();
  return m_PeripheralControllerCO2PressureSetPoint->GetValue(unit);
}

bool BioGearsConfiguration::HasPeripheralVentilatoryControllerGain() const
{
  return m_PeripheralVentilatoryControllerGain == nullptr ? false : m_PeripheralVentilatoryControllerGain->IsValid();
}
SEScalar& BioGearsConfiguration::GetPeripheralVentilatoryControllerGain()
{
  if (m_PeripheralVentilatoryControllerGain == nullptr)
    m_PeripheralVentilatoryControllerGain = new SEScalar();
  return *m_PeripheralVentilatoryControllerGain;
}
double BioGearsConfiguration::GetPeripheralVentilatoryControllerGain() const
{
  if (m_PeripheralVentilatoryControllerGain == nullptr)
    return SEScalar::dNaN();
  return m_PeripheralVentilatoryControllerGain->GetValue();
}

bool BioGearsConfiguration::HasPleuralComplianceSensitivity() const
{
  return m_PleuralComplianceSensitivity == nullptr ? false : m_PleuralComplianceSensitivity->IsValid();
}
SEScalarInverseVolume& BioGearsConfiguration::GetPleuralComplianceSensitivity()
{
  if (m_PleuralComplianceSensitivity == nullptr)
    m_PleuralComplianceSensitivity = new SEScalarInverseVolume();
  return *m_PleuralComplianceSensitivity;
}
double BioGearsConfiguration::GetPleuralComplianceSensitivity(const InverseVolumeUnit& unit) const
{
  if (m_PleuralComplianceSensitivity == nullptr)
    return SEScalar::dNaN();
  return m_PleuralComplianceSensitivity->GetValue(unit);
}

bool BioGearsConfiguration::HasPulmonaryVentilationRateMaximum() const
{
  return m_PulmonaryVentilationRateMaximum == nullptr ? false : m_PulmonaryVentilationRateMaximum->IsValid();
}
SEScalarVolumePerTime& BioGearsConfiguration::GetPulmonaryVentilationRateMaximum()
{
  if (m_PulmonaryVentilationRateMaximum == nullptr)
    m_PulmonaryVentilationRateMaximum = new SEScalarVolumePerTime();
  return *m_PulmonaryVentilationRateMaximum;
}
double BioGearsConfiguration::GetPulmonaryVentilationRateMaximum(const VolumePerTimeUnit& unit) const
{
  if (m_PulmonaryVentilationRateMaximum == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVentilationRateMaximum->GetValue(unit);
}

bool BioGearsConfiguration::HasVentilatoryOcclusionPressure() const
{
  return m_VentilatoryOcclusionPressure == nullptr ? false : m_VentilatoryOcclusionPressure->IsValid();
}
SEScalarPressure& BioGearsConfiguration::GetVentilatoryOcclusionPressure()
{
  if (m_VentilatoryOcclusionPressure == nullptr)
    m_VentilatoryOcclusionPressure = new SEScalarPressure();
  return *m_VentilatoryOcclusionPressure;
}
double BioGearsConfiguration::GetVentilatoryOcclusionPressure(const PressureUnit& unit) const
{
  if (m_VentilatoryOcclusionPressure == nullptr)
    return SEScalar::dNaN();
  return m_VentilatoryOcclusionPressure->GetValue(unit);
}

bool BioGearsConfiguration::HasVentilationTidalVolumeIntercept() const
{
  return m_VentilationTidalVolumeIntercept == nullptr ? false : m_VentilationTidalVolumeIntercept->IsValid();
}
SEScalarVolume& BioGearsConfiguration::GetVentilationTidalVolumeIntercept()
{
  if (m_VentilationTidalVolumeIntercept == nullptr)
    m_VentilationTidalVolumeIntercept = new SEScalarVolume();
  return *m_VentilationTidalVolumeIntercept;
}
double BioGearsConfiguration::GetVentilationTidalVolumeIntercept(const VolumeUnit& unit) const
{
  if (m_VentilationTidalVolumeIntercept == nullptr)
    return SEScalar::dNaN();
  return m_VentilationTidalVolumeIntercept->GetValue(unit);
}
}
