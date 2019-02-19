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
#define _USE_MATH_DEFINES

#include <biogears/cdm/circuit/fluid/SEFluidCircuit.h>
#include <biogears/cdm/compartment/SECompartmentManager.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartmentGraph.h>
#include <biogears/cdm/compartment/substances/SEGasSubstanceQuantity.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/properties/SEScalarFlowCompliance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarInverseVolume.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstanceFraction.h>
#include <biogears/cdm/utils/DataTrack.h>
#include <biogears/engine/test/BioGearsEngineTest.h>
#include <math.h>

namespace biogears {
void BioGearsEngineTest::RespiratoryCircuitAndTransportTest(RespiratoryConfiguration config, const std::string& sTestDirectory)
{
  TimingProfile tmr;
  tmr.Start("Test");
  //Output files
  DataTrack outTrkCircuit;
  DataTrack outTrkGraph;
  DataTrack aerosolGraphTrk;
  std::ofstream fileCircuit;
  std::ofstream fileGraph;
  std::ofstream fAerosolGraph;

  BioGears bg(sTestDirectory + "/RespiratoryCircuitAndTransportTest.log");
  bg.GetPatient().Load("./patients/StandardMale.xml");
  bg.SetupPatient();
  bg.m_Config->EnableRenal(CDM::enumOnOff::Off);
  bg.m_Config->EnableTissue(CDM::enumOnOff::Off);
  bg.CreateCircuitsAndCompartments();
  bg.GetSubstances().InitializeGasCompartments();
  SEEnvironmentalConditions& env = bg.GetEnvironment().GetConditions();

  SEFluidCircuit* rCircuit = nullptr;
  SEGasCompartmentGraph* rGraph = nullptr;
  SELiquidCompartmentGraph* aGraph = nullptr;
  std::string sCircuitFileName;
  std::string sTransportFileName;
  std::string sAerosolTxptFileName;
  if (config == RespiratorySolo) {
    rCircuit = &bg.GetCircuits().GetRespiratoryCircuit();
    rGraph = &bg.GetCompartments().GetRespiratoryGraph();
    aGraph = nullptr;
    sCircuitFileName = "/RespiratoryCircuitOutput.csv";
    sTransportFileName = "/RespiratoryTransportOutput.csv";
    sAerosolTxptFileName = "";
  } else if (config == RespiratoryWithInhaler) {
    rCircuit = &bg.GetCircuits().GetRespiratoryAndInhalerCircuit();
    rGraph = &bg.GetCompartments().GetRespiratoryAndInhalerGraph();
    aGraph = &bg.GetCompartments().GetAerosolAndInhalerGraph();
    sCircuitFileName = "/RespiratoryAndInhalerCircuitOutput.csv";
    sTransportFileName = "/RespiratoryAndInhalerTransportOutput.csv";
    sAerosolTxptFileName = "/AerosolInhalerTransportOutput.csv";

    // Get an aerosolized substance
    SESubstance* albuterol = bg.GetSubstances().GetSubstance("Albuterol");
    if (albuterol == nullptr) {
      bg.Error("Could not find the aerosol substance : Albuterol");
    } else {
      bg.GetSubstances().AddActiveSubstance(*albuterol);
      SELiquidCompartment* mouthpiece = bg.GetCompartments().GetLiquidCompartment(BGE::InhalerCompartment::Mouthpiece);
      mouthpiece->GetSubstanceQuantity(*albuterol)->GetMass().SetValue(90, MassUnit::ug);
      mouthpiece->Balance(BalanceLiquidBy::Mass);
    }
  } else if (config == RespiratoryWithMechanicalVentilator) {
    rCircuit = &bg.GetCircuits().GetRespiratoryAndMechanicalVentilatorCircuit();
    rGraph = &bg.GetCompartments().GetRespiratoryAndMechanicalVentilatorGraph();
    aGraph = nullptr;
    sCircuitFileName = "/RespiratoryAndMechanicalVentilatorCircuitOutput.csv";
    sTransportFileName = "/RespiratoryAndMechanicalVentilatorTransportOutput.csv";
    sAerosolTxptFileName = "";
  } else {
    return;
  }

  SEFluidCircuitPath* driverPath = rCircuit->GetPath(BGE::RespiratoryPath::EnvironmentToRespiratoryMuscle);
  SEGasTransporter gtxpt(VolumePerTimeUnit::L_Per_s, VolumeUnit::L, VolumeUnit::L, NoUnit::unitless, bg.GetLogger());
  SELiquidTransporter ltxpt(VolumePerTimeUnit::mL_Per_s, VolumeUnit::mL, MassUnit::ug, MassPerVolumeUnit::ug_Per_mL, bg.GetLogger());
  SEFluidCircuitCalculator calc(FlowComplianceUnit::L_Per_cmH2O, VolumePerTimeUnit::L_Per_s, FlowInertanceUnit::cmH2O_s2_Per_L, PressureUnit::cmH2O, VolumeUnit::L, FlowResistanceUnit::cmH2O_s_Per_L, bg.GetLogger());

  //Set the reference not pressure to the standard environment
  //This is needed because we're not setting the Environment during initialization in this unit test
  rCircuit->GetNode(BGE::EnvironmentNode::Ambient)->GetNextPressure().Set(env.GetAtmosphericPressure());
  rCircuit->GetNode(BGE::EnvironmentNode::Ambient)->GetPressure().Set(env.GetAtmosphericPressure());
  //Precharge the stomach to prevent negative volume
  rCircuit->GetNode(BGE::RespiratoryNode::Stomach)->GetNextPressure().Set(env.GetAtmosphericPressure());
  rCircuit->GetNode(BGE::RespiratoryNode::Stomach)->GetPressure().Set(env.GetAtmosphericPressure());

  //Circuit Analysis Test --------------------------------------------------
  //Execution parameters
  double time = 0;
  double deltaT_s = 1.0 / 90.0;
  double runTime_min = 10.0;
  //Drive waveform parameters
  double period = 5.0;
  double alpha = (2 * M_PI) / (period);
  double driverPressure_cmH2O = 0.0;
  double amplitude_cmH2O = 6.0;
  double yOffset = -12.0;

  for (unsigned int i = 0; i < runTime_min * 60.0 / deltaT_s; i++) {
    //PreProcess - Push driver pressure and  variable compliance data into the Circuit
    driverPressure_cmH2O = yOffset + amplitude_cmH2O * sin(alpha * time); //compute new pressure
    driverPath->GetNextPressureSource().SetValue(driverPressure_cmH2O, PressureUnit::cmH2O);

    //Process - Execute the circuit
    calc.Process(*rCircuit, deltaT_s);
    //Execute the substance transport function
    gtxpt.Transport(*rGraph, deltaT_s);
    // Do it again for aerosols
    if (aGraph != nullptr)
      ltxpt.Transport(*aGraph, deltaT_s);
    //convert 'Next' values to current
    calc.PostProcess(*rCircuit);

    outTrkCircuit.Track(time, *rCircuit);
    outTrkGraph.Track(time, *rGraph);
    if (aGraph != nullptr)
      aerosolGraphTrk.Track(time, *aGraph);
    time += deltaT_s;

    if (i == 0) {
      outTrkCircuit.CreateFile(std::string(sTestDirectory + sCircuitFileName).c_str(), fileCircuit);
      outTrkGraph.CreateFile(std::string(sTestDirectory + sTransportFileName).c_str(), fileGraph);
      if (aGraph != nullptr)
        aerosolGraphTrk.CreateFile(std::string(sTestDirectory + sAerosolTxptFileName).c_str(), fAerosolGraph);
    }
    outTrkCircuit.StreamTrackToFile(fileCircuit);
    outTrkGraph.StreamTrackToFile(fileGraph);
    if (aGraph != nullptr)
      aerosolGraphTrk.StreamTrackToFile(fAerosolGraph);
  }
  fileCircuit.close();
  fileGraph.close();
  fAerosolGraph.close();
  std::stringstream ss;
  ss << "It took " << tmr.GetElapsedTime_s("Test") << "s to run";
  bg.GetLogger()->Info(ss.str(), "RespiratoryCircuitAndTransportTest");
}

void BioGearsEngineTest::RespiratoryCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratorySolo, sTestDirectory);
}

void BioGearsEngineTest::RespiratoryWithInhalerCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratoryWithInhaler, sTestDirectory);
}

void BioGearsEngineTest::RespiratoryWithMechanicalVentilatorCircuitAndTransportTest(const std::string& sTestDirectory)
{
  RespiratoryCircuitAndTransportTest(RespiratoryWithMechanicalVentilator, sTestDirectory);
}

void BioGearsEngineTest::RespiratoryDriverTest(const std::string& sTestDirectory)
{
  TimingProfile tmr;
  tmr.Start("Test");
  BioGears bg(sTestDirectory + "/RespiratoryDriverTest.log");
  bg.GetPatient().Load("./patients/StandardMale.xml");
  bg.SetupPatient();
  bg.m_Config->EnableRenal(CDM::enumOnOff::Off);
  bg.m_Config->EnableTissue(CDM::enumOnOff::Off);
  bg.CreateCircuitsAndCompartments();
  SEEnvironmentalConditions env(bg.GetSubstances());
  env.Load("./environments/Standard.xml");
  SEGasCompartment* cEnv = bg.GetCompartments().GetGasCompartment(BGE::EnvironmentCompartment::Ambient);
  for (SESubstanceFraction* subFrac : env.GetAmbientGases()) {
    bg.GetSubstances().AddActiveSubstance(subFrac->GetSubstance());
    cEnv->GetSubstanceQuantity(subFrac->GetSubstance())->GetVolumeFraction().Set(subFrac->GetFractionAmount());
  }
  bg.GetSubstances().InitializeGasCompartments();

  DataTrack trk1;
  SEFluidCircuit& RespCircuit = bg.GetCircuits().GetRespiratoryCircuit();
  SEFluidCircuitCalculator calc(FlowComplianceUnit::L_Per_cmH2O, VolumePerTimeUnit::L_Per_s, FlowInertanceUnit::cmH2O_s2_Per_L, PressureUnit::cmH2O, VolumeUnit::L, FlowResistanceUnit::cmH2O_s_Per_L, bg.GetLogger());

  double deltaT_s = 1.0 / 90.0;

  SEFluidCircuitPath* driverPressurePath = RespCircuit.GetPath(BGE::RespiratoryPath::EnvironmentToRespiratoryMuscle);
  SEFluidCircuitPath* rightPleuralToRespiratoryMuscle = RespCircuit.GetPath(BGE::RespiratoryPath::RightPleuralToRespiratoryMuscle);
  SEFluidCircuitPath* leftPleuralToRespiratoryMuscle = RespCircuit.GetPath(BGE::RespiratoryPath::LeftPleuralToRespiratoryMuscle);

  SEFluidCircuitNode* rightPleuralNode = RespCircuit.GetNode(BGE::RespiratoryNode::RightPleural);
  SEFluidCircuitNode* leftPleuralNode = RespCircuit.GetNode(BGE::RespiratoryNode::LeftPleural);
  SEFluidCircuitNode* rightDeadSpaceNode = RespCircuit.GetNode(BGE::RespiratoryNode::RightAnatomicDeadSpace);
  SEFluidCircuitNode* leftDeadSpaceNode = RespCircuit.GetNode(BGE::RespiratoryNode::LeftAnatomicDeadSpace);
  SEFluidCircuitNode* rightAlveoliNode = RespCircuit.GetNode(BGE::RespiratoryNode::RightAlveoli);
  SEFluidCircuitNode* leftAlveoliNode = RespCircuit.GetNode(BGE::RespiratoryNode::LeftAlveoli);

  RespCircuit.GetNode(BGE::EnvironmentNode::Ambient)->GetNextPressure().SetValue(760, PressureUnit::mmHg);

  driverPressurePath->GetNextPressureSource().SetValue(0.0, PressureUnit::cmH2O);
  double PressureIncrement_cmH2O = 0.1;
  double DriverPressure_cmH2O = 0.0;
  bool bSettled = false;
  bool bIRVReached = false;
  bool bRVReached = false;
  int iTime = 0;

  while (!bIRVReached) {
    double TotalVolume_L = 0.0;
    double PreviousTotalVolume_L = 0.0;
    while (!bSettled) {
      //Set the driver pressure
      //Note: the driver pressure should be negative
      driverPressurePath->GetNextPressureSource().SetValue(DriverPressure_cmH2O, PressureUnit::cmH2O);

      //Variable compliance feedback
      //TODO: Figure out how to use that actual Respiratory function.  For now we'll just copy and paste it in.
      double dRightPleuralCompliance = rightPleuralToRespiratoryMuscle->GetNextCompliance().GetValue(FlowComplianceUnit::L_Per_cmH2O);
      double dLeftPleuralCompliance = leftPleuralToRespiratoryMuscle->GetNextCompliance().GetValue(FlowComplianceUnit::L_Per_cmH2O);
      double dRightPleuralVolumeBaseline = rightPleuralNode->GetVolumeBaseline().GetValue(VolumeUnit::L);
      double dLeftPleuralVolumeBaseline = leftPleuralNode->GetVolumeBaseline().GetValue(VolumeUnit::L);
      double dRightPleuralVolume = rightPleuralNode->GetNextVolume().GetValue(VolumeUnit::L);
      double dLeftPleuralVolume = leftPleuralNode->GetNextVolume().GetValue(VolumeUnit::L);

      dRightPleuralCompliance = (dRightPleuralVolume - dRightPleuralVolumeBaseline) * 5.0 * dRightPleuralCompliance + dRightPleuralCompliance;
      dLeftPleuralCompliance = (dLeftPleuralVolume - dLeftPleuralVolumeBaseline) * 5.0 * dLeftPleuralCompliance + dLeftPleuralCompliance;

      dRightPleuralCompliance = LIMIT(dRightPleuralCompliance, 1e-6, 0.05);
      dLeftPleuralCompliance = LIMIT(dLeftPleuralCompliance, 1e-6, 0.05);

      rightPleuralToRespiratoryMuscle->GetNextCompliance().SetValue(dRightPleuralCompliance, FlowComplianceUnit::L_Per_cmH2O);
      leftPleuralToRespiratoryMuscle->GetNextCompliance().SetValue(dLeftPleuralCompliance, FlowComplianceUnit::L_Per_cmH2O);

      //Process the circuit
      calc.Process(RespCircuit, deltaT_s);
      //Advance time
      calc.PostProcess(RespCircuit);

      //Calculate the total lung volume
      TotalVolume_L = leftDeadSpaceNode->GetNextVolume(VolumeUnit::L) + leftAlveoliNode->GetNextVolume(VolumeUnit::L) + rightDeadSpaceNode->GetNextVolume(VolumeUnit::L) + rightAlveoliNode->GetNextVolume(VolumeUnit::L);

      //Check to see if the circuit has stabilized
      if (std::abs(TotalVolume_L - PreviousTotalVolume_L) < 0.0001) {
        //Output values
        trk1.Track("LungVolume_L", iTime, TotalVolume_L);
        trk1.Track("DriverPressure_cmH2O", iTime, driverPressurePath->GetPressureSource(PressureUnit::cmH2O));
        iTime++;
        bSettled = true;
      }
      PreviousTotalVolume_L = TotalVolume_L;
    }
    bSettled = false;

    //Check to see if we've gone all the way to the max volume
    if (TotalVolume_L >= bg.GetPatient().GetTotalLungCapacity(VolumeUnit::L)) {
      bIRVReached = true;
    } else {
      DriverPressure_cmH2O = DriverPressure_cmH2O - PressureIncrement_cmH2O;
    }
  }
  trk1.WriteTrackToFile(std::string(sTestDirectory + "/RespiratoryDriverOutput.csv").c_str());
  std::stringstream ss;
  ss << "It took " << tmr.GetElapsedTime_s("Test") << "s to run";
  bg.GetLogger()->Info(ss.str(), "RespiratoryDriverTest");
}

void BioGearsEngineTest::LiteRespiratoryCircuitTest(const std::string& sTestDirectory)
{
  //Elements needed for test
  m_Logger->ResetLogFile(sTestDirectory + "/RespiratoryLite.log");
  std::string resultsFile = sTestDirectory + "/RespiratoryLite.csv";
  std::string resultsGraph = sTestDirectory + "/RespiratoryLiteGraph.csv";
  BioGears bg(m_Logger);
  SECircuitManager circuits(m_Logger);
  SEGasTransporter gtxpt(VolumePerTimeUnit::L_Per_s, VolumeUnit::L, VolumeUnit::L, NoUnit::unitless, bg.GetLogger());
  SEFluidCircuitCalculator calc(FlowComplianceUnit::mL_Per_mmHg, VolumePerTimeUnit::mL_Per_s, FlowInertanceUnit::mmHg_s2_Per_mL, PressureUnit::mmHg, VolumeUnit::mL, FlowResistanceUnit::mmHg_s_Per_mL, m_Logger);
  DataTrack circuitTrk;
  DataTrack graphTrk;
  SEFluidCircuit* respLite = &circuits.CreateFluidCircuit("RespLite");

  //Set up circuit constants
  //Compliances
  double larynxCompliance_L_Per_cmH2O = 0.00127;
  double tracheaCompliance_L_Per_cmH2O = 0.00238;
  double throatCompliance_L_Per_cmH2O = 1.0 / (1.0 / larynxCompliance_L_Per_cmH2O + 1.0 / tracheaCompliance_L_Per_cmH2O);
  double broncheaCompliance_L_Per_cmH2O = 0.0131;
  double alveoliCompliance_L_Per_cmH2O = 0.2;
  double chestWallCompliance_L_Per_cmH2O = 0.2445;
  //Resistances
  double mouthToLarynxResistance_cmH2O_s_Per_L = 1.021;
  double larynxToTracheaResistance_cmH2O_s_Per_L = 0.3369;
  double mouthToThroatResistance_cmH2O_s_Per_L = mouthToLarynxResistance_cmH2O_s_Per_L + larynxToTracheaResistance_cmH2O_s_Per_L;
  double tracheaToBroncheaResistance_cmH2O_s_Per_L = 0.3063;
  double broncheaToAlveoliResistance_cmH2O_s_Per_L = 0.0817;
  //Target volumes are end-expiratory (i.e. bottom of breathing cycle, pressures = ambient pressure)
  double functionalResidualCapacity_L = 2.4;   //This includes what's left in alveoli and dead space
  double targetDeadSpace_mL = 135.0;           //This includes bronchea, larynx, thrachea
  double larynxVolume_mL = 34.4;
  double tracheaVolume_mL = 6.63;
  double broncheaVolume_mL = targetDeadSpace_mL - (larynxVolume_mL + tracheaVolume_mL);
  double alveoliVolume_L = functionalResidualCapacity_L - (larynxVolume_mL + tracheaVolume_mL + broncheaVolume_mL) / 1000.0;
  //Pressures
  double ambientPressure_cmH2O = Convert(760.0, PressureUnit::mmHg, PressureUnit::cmH2O);
  double pleuralPressure_cmH20 = ambientPressure_cmH2O - 5.0;
  //Circuit Nodes
  SEFluidCircuitNode& mouth = respLite->CreateNode("Mouth");
  mouth.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  mouth.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  mouth.GetVolumeBaseline().SetValue(20.6, VolumeUnit::mL);   //From BioGears.cpp -- no compliance, so volume constant, but need this to define gas volume fractions and transport
  SEFluidCircuitNode& throat = respLite->CreateNode("Throat");
  throat.GetVolumeBaseline().SetValue(tracheaVolume_mL + larynxVolume_mL, VolumeUnit::mL);
  throat.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  throat.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  SEFluidCircuitNode& bronchea = respLite->CreateNode("Bronchea");
  bronchea.GetVolumeBaseline().SetValue(broncheaVolume_mL, VolumeUnit::mL);
  bronchea.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  bronchea.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  SEFluidCircuitNode& alveoli = respLite->CreateNode("Alveoli");
  alveoli.GetVolumeBaseline().SetValue(alveoliVolume_L, VolumeUnit::L);
  alveoli.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  alveoli.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  SEFluidCircuitNode& pleural = respLite->CreateNode("Pleural");
  pleural.GetPressure().SetValue(pleuralPressure_cmH20, PressureUnit::cmH2O);
  pleural.GetNextPressure().SetValue(pleuralPressure_cmH20, PressureUnit::cmH2O);
  pleural.GetVolumeBaseline().SetValue(0.017, VolumeUnit::L); //From BioGears.cpp
  SEFluidCircuitNode& chestWall = respLite->CreateNode("ChestWall");
  chestWall.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  chestWall.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  SEFluidCircuitNode& ground = respLite->CreateNode("Ground");
  ground.GetPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  ground.GetNextPressure().SetValue(ambientPressure_cmH2O, PressureUnit::cmH2O);
  ground.GetVolumeBaseline().SetValue(std::numeric_limits<double>::infinity(), VolumeUnit::L);
  respLite->AddReferenceNode(ground);

  //Pathways
  SEFluidCircuitPath& amToMouth = respLite->CreatePath(ground, mouth, "GroundToMouth");
  amToMouth.GetPressureSourceBaseline().SetValue(0.0, PressureUnit::cmH2O);
  SEFluidCircuitPath& mouthToThroat = respLite->CreatePath(mouth, throat, "MouthToTrachea");
  mouthToThroat.GetResistanceBaseline().SetValue(mouthToThroatResistance_cmH2O_s_Per_L, FlowResistanceUnit::cmH2O_s_Per_L);
  SEFluidCircuitPath& throatToBronchea = respLite->CreatePath(throat, bronchea, "ThroatToBronchea");
  throatToBronchea.GetResistanceBaseline().SetValue(tracheaToBroncheaResistance_cmH2O_s_Per_L, FlowResistanceUnit::cmH2O_s_Per_L);
  SEFluidCircuitPath& throatCompliance = respLite->CreatePath(throat, pleural, "ThroatToPleural");
  throatCompliance.GetComplianceBaseline().SetValue(throatCompliance_L_Per_cmH2O, FlowComplianceUnit::L_Per_cmH2O);
  SEFluidCircuitPath& broncheaToAlveoli = respLite->CreatePath(bronchea, alveoli, "BroncheaToAlveoli");
  broncheaToAlveoli.GetResistanceBaseline().SetValue(broncheaToAlveoliResistance_cmH2O_s_Per_L, FlowResistanceUnit::cmH2O_s_Per_L);
  SEFluidCircuitPath& broncheaCompliance = respLite->CreatePath(bronchea, pleural, "BroncheaCompliance");
  broncheaCompliance.GetComplianceBaseline().SetValue(broncheaCompliance_L_Per_cmH2O, FlowComplianceUnit::L_Per_cmH2O);
  SEFluidCircuitPath& alveoliCompliance = respLite->CreatePath(alveoli, pleural, "AlveoliCompliance");
  alveoliCompliance.GetComplianceBaseline().SetValue(alveoliCompliance_L_Per_cmH2O, FlowComplianceUnit::L_Per_cmH2O);
  SEFluidCircuitPath& pleuralCompliance = respLite->CreatePath(pleural, chestWall, "PleuralToChestWall");
  pleuralCompliance.GetComplianceBaseline().SetValue(chestWallCompliance_L_Per_cmH2O, FlowComplianceUnit::L_Per_cmH2O);
  SEFluidCircuitPath& driver = respLite->CreatePath(ground, chestWall, "Driver");
  driver.GetPressureSourceBaseline().SetValue(0.0, PressureUnit::cmH2O);

  respLite->SetNextAndCurrentFromBaselines();
  respLite->StateChange();

  //Set up compartments
  SEGasCompartmentGraph* liteGraph = &bg.GetCompartments().CreateGasGraph("LiteGraph");
  liteGraph->Clear();
  liteGraph->StateChange();

  SEGasCompartment& cAmbient = bg.GetCompartments().CreateGasCompartment("cAmbient");
  cAmbient.MapNode(ground);
  SEGasCompartment& cMouth = bg.GetCompartments().CreateGasCompartment("cMouth");
  cMouth.MapNode(mouth);
  SEGasCompartment& cThroat = bg.GetCompartments().CreateGasCompartment("cThroat");
  cThroat.MapNode(throat);
  SEGasCompartment& cBronchea = bg.GetCompartments().CreateGasCompartment("cBronchea");
  cBronchea.MapNode(bronchea);
  SEGasCompartment& cAlveoli = bg.GetCompartments().CreateGasCompartment("cAlveoli");
  cAlveoli.MapNode(alveoli);
  SEGasCompartment& cPleuralSpace = bg.GetCompartments().CreateGasCompartment("cPleuralSpace");
  cPleuralSpace.MapNode(pleural);
  cPleuralSpace.MapNode(chestWall);
  SEGasCompartment& cDeadSpace = bg.GetCompartments().CreateGasCompartment("cDeadSpace");
  cDeadSpace.AddChild(cThroat);
  cDeadSpace.AddChild(cBronchea);

  SEGasCompartmentLink& lAmbientToMouth = bg.GetCompartments().CreateGasLink(cAmbient,cMouth,"lAmbientToMouth");
  lAmbientToMouth.MapPath(amToMouth);
  SEGasCompartmentLink& lMouthToThroat = bg.GetCompartments().CreateGasLink(cMouth, cThroat, "lMouthToThroat");
  lMouthToThroat.MapPath(mouthToThroat);
  SEGasCompartmentLink& lThroatToBronchea = bg.GetCompartments().CreateGasLink(cThroat, cBronchea, "lThroatToBronchea");
  lThroatToBronchea.MapPath(throatToBronchea);
  SEGasCompartmentLink& lThroatToPleural = bg.GetCompartments().CreateGasLink(cThroat, cPleuralSpace, "lThroatToPleural");
  lThroatToPleural.MapPath(throatCompliance);
  SEGasCompartmentLink& lBroncheaToAlveoli = bg.GetCompartments().CreateGasLink(cBronchea, cAlveoli, "lBroncheaToAlveoli");
  lBroncheaToAlveoli.MapPath(broncheaToAlveoli);
  SEGasCompartmentLink& lBroncheaToPleural = bg.GetCompartments().CreateGasLink(cBronchea, cPleuralSpace, "lBroncheaToPleural");
  lBroncheaToPleural.MapPath(broncheaCompliance);
  SEGasCompartmentLink& lAlveoliToPleural = bg.GetCompartments().CreateGasLink(cAlveoli, cPleuralSpace, "lAlveoliToPleural");
  lAlveoliToPleural.MapPath(alveoliCompliance);

  liteGraph->AddCompartment(cAmbient);
  liteGraph->AddCompartment(cMouth);
  liteGraph->AddCompartment(cThroat);
  liteGraph->AddCompartment(cBronchea);
  liteGraph->AddCompartment(cAlveoli);
  liteGraph->AddCompartment(cPleuralSpace);
  liteGraph->AddLink(lAmbientToMouth);
  liteGraph->AddLink(lMouthToThroat);
  liteGraph->AddLink(lThroatToBronchea);
  liteGraph->AddLink(lThroatToPleural);
  liteGraph->AddLink(lBroncheaToAlveoli);
  liteGraph->AddLink(lBroncheaToPleural);
  liteGraph->AddLink(lAlveoliToPleural);
  liteGraph->StateChange();

  //Set up substances
  SESubstance& O2 = bg.GetSubstances().GetO2();
  bg.GetSubstances().AddActiveSubstance(O2);
  SESubstance& CO2 = bg.GetSubstances().GetCO2();
  bg.GetSubstances().AddActiveSubstance(CO2);
  SESubstance& N2 = bg.GetSubstances().GetN2();
  bg.GetSubstances().AddActiveSubstance(N2);
  double o2Fraction = 0.21;
  double n2Fraction = 0.7896;
  double co2Fraction = 0.0004;

  //Intialize partial pressures
  for (auto c : liteGraph->GetCompartments()) {
    
    c->GetSubstanceQuantity(O2)->GetVolumeFraction().SetValue(o2Fraction);
    c->GetSubstanceQuantity(CO2)->GetVolumeFraction().SetValue(co2Fraction);
    c->GetSubstanceQuantity(N2)->GetVolumeFraction().SetValue(n2Fraction);
    c->Balance(BalanceGasBy::VolumeFraction);
  }
  std::cout << "Graph Set" << std::endl;
  //Chemoreceptor parameters
  double tau_p_P = 83.0;
  double gain_p_P = 1310.0;
  double tau_p_RR = 147.78;
  double gain_p_RR = 0.8735;
  double f_base = 3.7;
  double tau_c_P = 105.0;
  double gain_c_P = 850.0;
  double tau_c_RR = 400.0;
  double gain_c_RR = 0.9;
  double pCO2_base = 40.0;
  

  double nextDriverPressure_cmH2O = 0.0;
  double totalVolume_mL = 0.0;
  double deadSpaceVolume_mL = 0.0;
  double timeStep_s = 0.02;
  double simTime_min = 0.25;
  double currentTime_s = 0.0;
  double driveFrequency_Per_min = 12.0;
  double ieRatio = 0.6;
  double cycleTime_s = 60.0 / driveFrequency_Per_min;
  double timeInCycle_s = 0.0;
  double expTime_s = cycleTime_s / (1.0 + ieRatio);
  double inTime_s = expTime_s * ieRatio;
  double tau_s = expTime_s / 5.0;

  for (int i = 0; i < simTime_min * 60.0 / timeStep_s; i++) {
    //nextDriverPressure_cmH2O = maxAmplitude_cmH2O * std::cos(2.0 * pi * driveFrequency_Per_min / 60.0 * currentTime_s) + driveOffset_cmH2O;
    if (timeInCycle_s < inTime_s) {
      nextDriverPressure_cmH2O = 5.0 / (inTime_s * expTime_s) * std::pow(timeInCycle_s, 2.0) + -5.0 * cycleTime_s / (inTime_s * expTime_s) * timeInCycle_s;
    } else {
      nextDriverPressure_cmH2O = -5.0 / (1.0 - std::exp(-expTime_s / tau_s)) * (std::exp(-(timeInCycle_s - inTime_s) / tau_s) - std::exp(-expTime_s / tau_s));
    }
    driver.GetNextPressureSource().SetValue(nextDriverPressure_cmH2O, PressureUnit::cmH2O);
    calc.Process(*respLite, timeStep_s);
    gtxpt.Transport(*liteGraph, timeStep_s);
    totalVolume_mL = (throat.GetVolume(VolumeUnit::mL) + bronchea.GetVolume(VolumeUnit::mL) + alveoli.GetVolume(VolumeUnit::mL)); // + pleural.GetVolume(VolumeUnit::mL);
    deadSpaceVolume_mL = totalVolume_mL - alveoli.GetVolume(VolumeUnit::mL);
    calc.PostProcess(*respLite);
    circuitTrk.Track(currentTime_s, *respLite);
    circuitTrk.Track("DriveInput", currentTime_s, nextDriverPressure_cmH2O);
    circuitTrk.Track("TotalLungVolume_mL", currentTime_s, totalVolume_mL);
    circuitTrk.Track("DeadSpace (mL)", currentTime_s, deadSpaceVolume_mL);
    graphTrk.Track(currentTime_s, *liteGraph);
    currentTime_s += timeStep_s;
    timeInCycle_s += timeStep_s;
    if (timeInCycle_s >= cycleTime_s) {
      timeInCycle_s = 0.0;
    }
  }

  circuitTrk.WriteTrackToFile(resultsFile.c_str());
  graphTrk.WriteTrackToFile(resultsGraph.c_str());
  std::cout << "Success" << std::endl;
}
}