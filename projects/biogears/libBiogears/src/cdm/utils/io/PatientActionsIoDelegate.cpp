#include "PatientActionsIoDelegate.h"

#include "PropertyIoDelegate.h"
#include "ScenarioIoDelegate.h"

#include <biogears/cdm/patient/actions/SEAcuteStress.h>
#include <biogears/cdm/patient/actions/SEAirwayObstruction.h>
#include <biogears/cdm/patient/actions/SEApnea.h>
#include <biogears/cdm/patient/actions/SEAsthmaAttack.h>
#include <biogears/cdm/patient/actions/SEBrainInjury.h>
#include <biogears/cdm/patient/actions/SEBreathHold.h>
#include <biogears/cdm/patient/actions/SEBronchoconstriction.h>
#include <biogears/cdm/patient/actions/SEBurnWound.h>
#include <biogears/cdm/patient/actions/SECardiacArrest.h>
#include <biogears/cdm/patient/actions/SEChestCompression.h>
#include <biogears/cdm/patient/actions/SEChestCompressionForce.h>
#include <biogears/cdm/patient/actions/SEChestCompressionForceScale.h>
#include <biogears/cdm/patient/actions/SEChestOcclusiveDressing.h>
#include <biogears/cdm/patient/actions/SEConsciousRespiration.h>
#include <biogears/cdm/patient/actions/SEConsciousRespirationCommand.h>
#include <biogears/cdm/patient/actions/SEConsumeNutrients.h>
#include <biogears/cdm/patient/actions/SEExercise.h>
#include <biogears/cdm/patient/actions/SEForcedExhale.h>
#include <biogears/cdm/patient/actions/SEForcedInhale.h>
#include <biogears/cdm/patient/actions/SEHemorrhage.h>
#include <biogears/cdm/patient/actions/SEIntubation.h>
#include <biogears/cdm/patient/actions/SEMechanicalVentilation.h>
#include <biogears/cdm/patient/actions/SENeedleDecompression.h>
#include <biogears/cdm/patient/actions/SEOverride.h>
#include <biogears/cdm/patient/actions/SEPainStimulus.h>
#include <biogears/cdm/patient/actions/SEPatientAssessmentRequest.h>
#include <biogears/cdm/patient/actions/SEPericardialEffusion.h>
#include <biogears/cdm/patient/actions/SESepsis.h>
#include <biogears/cdm/patient/actions/SESubstanceBolus.h>
#include <biogears/cdm/patient/actions/SESubstanceCompoundInfusion.h>
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>
#include <biogears/cdm/patient/actions/SETensionPneumothorax.h>
#include <biogears/cdm/patient/actions/SEUrinate.h>
#include <biogears/cdm/patient/actions/SEUseInhaler.h>

#include <biogears/cdm/properties/SEScalarFraction.h>

#include <biogears/cdm/scenario/SEAdvanceTime.h>
#include <biogears/cdm/scenario/SESerializeState.h>

#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/substance/SESubstanceFraction.h>
#include <biogears/cdm/substance/SESubstanceManager.h>

#include <biogears/cdm/system/environment/actions/SEEnvironmentChange.h>
#include <biogears/cdm/system/environment/actions/SEThermalApplication.h>

#include <biogears/cdm/system/equipment/Anesthesia/actions/SEAnesthesiaMachineConfiguration.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEExpiratoryValveLeak.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEExpiratoryValveObstruction.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEInspiratoryValveLeak.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEInspiratoryValveObstruction.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEMaskLeak.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEOxygenTankPressureLoss.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEOxygenWallPortPressureLoss.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SESodaLimeFailure.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SETubeCuffLeak.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEVaporizerFailure.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEVentilatorPressureLoss.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEYPieceDisconnect.h>
#include <biogears/cdm/system/equipment/Inhaler/actions/SEInhalerConfiguration.h>

namespace biogears {
namespace io {
  //class SEActionList
  std::vector<std::unique_ptr<SEAction>> PatientActionsIoDelegate::action_factory(const CDM::ActionListData& in, SESubstanceManager& substances)
  {
    std::vector<std::unique_ptr<SEAction>> r_vec;
    for (const auto action_data : in.Action()) {
      r_vec.emplace_back(factory(action_data, substances));
    }
    return std::move(r_vec);
  }
  //----------------------------------------------------------------------------------
  //class SECondition
  std::unique_ptr<SEAction> PatientActionsIoDelegate::factory(const CDM::ActionData& data, SESubstanceManager& substances)
  {
    std::stringstream ss;
    SESubstance* substance;
    SESubstanceCompound* compound;

    auto action = (CDM::ActionData*)&data;
    auto advData = dynamic_cast<CDM::AdvanceTimeData*>(action);
    if (advData != nullptr) {
      auto result = std::make_unique<SEAdvanceTime>();
      ScenarioIoDelegate::Marshall(*advData, *result);
      return std::move(result);
    }

    auto stData = dynamic_cast<CDM::SerializeStateData*>(action);
    if (stData != nullptr) {
      auto result = std::make_unique<SESerializeState>();
      ScenarioIoDelegate::Marshall(*stData, *result);
      return result;
    }

    if (dynamic_cast<CDM::EnvironmentActionData*>(action) != nullptr) {
      if (dynamic_cast<CDM::EnvironmentChangeData*>(action) != nullptr) {
        auto result = std::make_unique<SEEnvironmentChange>(substances);
        result->Load(*(CDM::EnvironmentChangeData*)action);
        return result;
      }
      if (dynamic_cast<CDM::ThermalApplicationData*>(action) != nullptr) {
        auto result = std::make_unique<SEThermalApplication>();
        result->Load(*(CDM::ThermalApplicationData*)action);
        return result;
      }
      substances.GetLogger()->Error("Unsupported Environment Action Received", "SEScenario::Load");
    }

    if (dynamic_cast<CDM::PatientActionData*>(action) != nullptr) {
      auto pAssessmentData = dynamic_cast<CDM::PatientAssessmentRequestData*>(action);
      if (pAssessmentData != nullptr) {
        auto result = std::make_unique<SEPatientAssessmentRequest>();
        PatientActionsIoDelegate::Marshall(*pAssessmentData, *result);
        return result;
      }

      auto aStressData = dynamic_cast<CDM::AcuteStressData*>(action);
      if (aStressData != nullptr) {
        auto result = std::make_unique<SEAcuteStress>();
        PatientActionsIoDelegate::Marshall(*aStressData, *result);
        return result;
      }

      auto airObData = dynamic_cast<CDM::AirwayObstructionData*>(action);
      if (airObData != nullptr) {
        auto result = std::make_unique<SEAirwayObstruction>();
        PatientActionsIoDelegate::Marshall(*airObData, *result);
        return result;
      }

      auto apneaData = dynamic_cast<CDM::ApneaData*>(action);
      if (apneaData != nullptr) {
        auto result = std::make_unique<SEApnea>();
        PatientActionsIoDelegate::Marshall(*apneaData, *result);
        return result;
      }

      auto brainInjData = dynamic_cast<CDM::BrainInjuryData*>(action);
      if (brainInjData != nullptr) {
        auto result = std::make_unique<SEBrainInjury>();
        PatientActionsIoDelegate::Marshall(*brainInjData, *result);
        return result;
      }

      auto burnData = dynamic_cast<CDM::BurnWoundData*>(action);
      if (burnData != nullptr) {
        auto result = std::make_unique<SEBurnWound>();
        PatientActionsIoDelegate::Marshall(*burnData, *result);
        return result;
      }

      auto bconData = dynamic_cast<CDM::BronchoconstrictionData*>(action);
      if (bconData != nullptr) {
        auto result = std::make_unique<SEBronchoconstriction>();
        PatientActionsIoDelegate::Marshall(*bconData, *result);
        return result;
      }

      auto carrestData = dynamic_cast<CDM::CardiacArrestData*>(action);
      if (carrestData != nullptr) {
        auto result = std::make_unique<SECardiacArrest>();
        PatientActionsIoDelegate::Marshall(*carrestData, *result);
        return result;
      }

      auto asthmaData = dynamic_cast<CDM::AsthmaAttackData*>(action);
      if (asthmaData != nullptr) {
        auto result = std::make_unique<SEAsthmaAttack>();
        PatientActionsIoDelegate::Marshall(*asthmaData, *result);
        return result;
      }

      auto cprData = dynamic_cast<CDM::ChestCompressionData*>(action);
      if (cprData != nullptr) {
        auto cprForce = dynamic_cast<CDM::ChestCompressionForceData*>(cprData);
        if (cprForce != nullptr) {
          auto result = std::make_unique<SEChestCompressionForce>();
          PatientActionsIoDelegate::Marshall(*cprForce, *result);
          return result;
        }
        auto cprScale = dynamic_cast<CDM::ChestCompressionForceScaleData*>(cprData);
        if (cprScale != nullptr) {
          auto result = std::make_unique<SEChestCompressionForceScale>();
          PatientActionsIoDelegate::Marshall(*cprScale, *result);
          return result;
        }
      }

      auto codData = dynamic_cast<CDM::ChestOcclusiveDressingData*>(action);
      if (codData != nullptr) {
        auto result = std::make_unique<SEChestOcclusiveDressing>();
        PatientActionsIoDelegate::Marshall(*codData, *result);
        return result;
      }

      auto conRespData = dynamic_cast<CDM::ConsciousRespirationData*>(action);
      if (conRespData != nullptr) {
        auto result = std::make_unique<SEConsciousRespiration>();
        PatientActionsIoDelegate::Marshall(*conRespData, *result);
        return result;
      }

      auto consumeData = dynamic_cast<CDM::ConsumeNutrientsData*>(action);
      if (consumeData != nullptr) {
        auto result = std::make_unique<SEConsumeNutrients>();
        PatientActionsIoDelegate::Marshall(*consumeData, *result);
        return result;
      }

      auto exerciseData = dynamic_cast<CDM::ExerciseData*>(action);
      if (exerciseData != nullptr) {
        auto result = std::make_unique<SEExercise>();
        PatientActionsIoDelegate::Marshall(*exerciseData, *result);
        return result;
      }

      auto intub8Data = dynamic_cast<CDM::IntubationData*>(action);
      if (intub8Data != nullptr) {
        auto result = std::make_unique<SEIntubation>();
        PatientActionsIoDelegate::Marshall(*intub8Data, *result);
        return result;
      }

      auto mechVentData = dynamic_cast<CDM::MechanicalVentilationData*>(action);
      if (mechVentData != nullptr) {
        auto result = std::make_unique<SEMechanicalVentilation>();
        PatientActionsIoDelegate::Marshall(*mechVentData, *result);
        return result;
      }

      auto needlData = dynamic_cast<CDM::NeedleDecompressionData*>(action);
      if (needlData != nullptr) {
        auto result = std::make_unique<SENeedleDecompression>();
        PatientActionsIoDelegate::Marshall(*needlData, *result);
        return result;
      }

      auto overrideData = dynamic_cast<CDM::OverrideData*>(action);
      if (overrideData != nullptr) {
        auto result = std::make_unique<SEOverride>();
        PatientActionsIoDelegate::Marshall(*overrideData, *result);
        return result;
      }

      auto hemData = dynamic_cast<CDM::HemorrhageData*>(action);
      if (hemData != nullptr) {
        auto result = std::make_unique<SEHemorrhage>();
        PatientActionsIoDelegate::Marshall(*hemData, *result);
        return result;
      }

      auto painData = dynamic_cast<CDM::PainStimulusData*>(action);
      if (painData != nullptr) {
        auto result = std::make_unique<SEPainStimulus>();
        PatientActionsIoDelegate::Marshall(*painData, *result);
        return result;
      }

      auto pericData = dynamic_cast<CDM::PericardialEffusionData*>(action);
      if (pericData != nullptr) {
        auto result = std::make_unique<SEPericardialEffusion>();
        PatientActionsIoDelegate::Marshall(*pericData, *result);
        return result;
      }

      auto sepData = dynamic_cast<CDM::SepsisData*>(action);
      if (sepData != nullptr) {
        auto result = std::make_unique<SESepsis>();
        PatientActionsIoDelegate::Marshall(*sepData, *result);
        return result;
      }

      auto pneumoData = dynamic_cast<CDM::TensionPneumothoraxData*>(action);
      if (pneumoData != nullptr) {
        auto result = std::make_unique<SETensionPneumothorax>();
        PatientActionsIoDelegate::Marshall(*pneumoData, *result);
        return result;
      }

      auto bolusData = dynamic_cast<CDM::SubstanceBolusData*>(action);
      if (bolusData != nullptr) {
        substance = substances.GetSubstance(bolusData->Substance());
        if (substance == nullptr) {
          ss << "Unknown substance : " << bolusData->Substance();
          substances.GetLogger()->Fatal(ss, "SEScenario::Load");
        }
        auto result = std::make_unique<SESubstanceBolus>(*substance);
        PatientActionsIoDelegate::Marshall(*bolusData, *result);
        return result;
      }

      auto subInfuzData = dynamic_cast<CDM::SubstanceInfusionData*>(action);
      if (subInfuzData != nullptr) {
        substance = substances.GetSubstance(subInfuzData->Substance());
        if (substance == nullptr) {
          ss << "Unknown substance : " << subInfuzData->Substance();
          substances.GetLogger()->Fatal(ss, "SEScenario::Load");
        }
        auto result = std::make_unique<SESubstanceInfusion>(*substance);
        PatientActionsIoDelegate::Marshall(*subInfuzData, *result);
        return result;
      }

      auto subCInfuzData = dynamic_cast<CDM::SubstanceCompoundInfusionData*>(action);
      if (subCInfuzData != nullptr) {
        compound = substances.GetCompound(subCInfuzData->SubstanceCompound());
        if (compound == nullptr) {
          ss << "Unknown substance : " << subCInfuzData->SubstanceCompound();
          substances.GetLogger()->Fatal(ss, "SEScenario::Load");
        }
        auto result = std::make_unique<SESubstanceCompoundInfusion>(*compound);
        PatientActionsIoDelegate::Marshall(*subCInfuzData, *result);
        return result;
      }

      auto urinateData = dynamic_cast<CDM::UrinateData*>(action);
      if (urinateData != nullptr) {
        auto result = std::make_unique<SEUrinate>();
        PatientActionsIoDelegate::Marshall(*urinateData, *result);
        return result;
      }
      substances.GetLogger()->Error("Unsupported Patient Action Received", "SEScenario::Load");
    } else if (dynamic_cast<CDM::AnesthesiaMachineActionData*>(action) != nullptr) {
      auto anConfig = dynamic_cast<CDM::AnesthesiaMachineConfigurationData*>(action);
      if (anConfig != nullptr) {
        auto result = std::make_unique<SEAnesthesiaMachineConfiguration>(substances);
        result->Load(*anConfig);
        return result;
      }

      auto anO2WallLoss = dynamic_cast<CDM::OxygenWallPortPressureLossData*>(action);
      if (anO2WallLoss != nullptr) {
        auto result = std::make_unique<SEOxygenWallPortPressureLoss>();
        result->Load(*anO2WallLoss);
        return result;
      }

      auto anO2TankLoss = dynamic_cast<CDM::OxygenTankPressureLossData*>(action);
      if (anO2TankLoss != nullptr) {
        auto result = std::make_unique<SEOxygenTankPressureLoss>();
        result->Load(*anO2TankLoss);
        return result;
      }

      auto anExLeak = dynamic_cast<CDM::ExpiratoryValveLeakData*>(action);
      if (anExLeak != nullptr) {
        auto result = std::make_unique<SEExpiratoryValveLeak>();
        result->Load(*anExLeak);
        return result;
      }

      auto anExObs = dynamic_cast<CDM::ExpiratoryValveObstructionData*>(action);
      if (anExObs != nullptr) {
        auto result = std::make_unique<SEExpiratoryValveObstruction>();
        result->Load(*anExObs);
        return result;
      }

      auto anInLeak = dynamic_cast<CDM::InspiratoryValveLeakData*>(action);
      if (anInLeak != nullptr) {
        auto result = std::make_unique<SEInspiratoryValveLeak>();
        result->Load(*anInLeak);
        return result;
      }

      auto anInObs = dynamic_cast<CDM::InspiratoryValveObstructionData*>(action);
      if (anInObs != nullptr) {
        auto result = std::make_unique<SEInspiratoryValveObstruction>();
        result->Load(*anInObs);
        return result;
      }

      auto anMskLeak = dynamic_cast<CDM::MaskLeakData*>(action);
      if (anMskLeak != nullptr) {
        auto result = std::make_unique<SEMaskLeak>();
        result->Load(*anMskLeak);
        return result;
      }

      auto anSodaFail = dynamic_cast<CDM::SodaLimeFailureData*>(action);
      if (anSodaFail != nullptr) {
        auto result = std::make_unique<SESodaLimeFailure>();
        result->Load(*anSodaFail);
        return result;
      }

      auto anTubLeak = dynamic_cast<CDM::TubeCuffLeakData*>(action);
      if (anTubLeak != nullptr) {
        auto result = std::make_unique<SETubeCuffLeak>();
        result->Load(*anTubLeak);
        return result;
      }

      auto anVapFail = dynamic_cast<CDM::VaporizerFailureData*>(action);
      if (anVapFail != nullptr) {
        auto result = std::make_unique<SEVaporizerFailure>();
        result->Load(*anVapFail);
        return result;
      }

      auto anVentLoss = dynamic_cast<CDM::VentilatorPressureLossData*>(action);
      if (anVentLoss != nullptr) {
        auto result = std::make_unique<SEVentilatorPressureLoss>();
        result->Load(*anVentLoss);
        return result;
      }

      auto anYDisc = dynamic_cast<CDM::YPieceDisconnectData*>(action);
      if (anYDisc != nullptr) {
        auto result = std::make_unique<SEYPieceDisconnect>();
        result->Load(*anYDisc);
        return result;
      }
      substances.GetLogger()->Error("Unsupported Anesthesia Machine Action Received", "SEScenario::Load");
    } else if (dynamic_cast<CDM::InhalerActionData*>(action) != nullptr) {
      auto inhaleConfig = dynamic_cast<CDM::InhalerConfigurationData*>(action);
      if (inhaleConfig != nullptr) {
        auto result = std::make_unique<SEInhalerConfiguration>(substances);
        result->Load(*inhaleConfig);
        return result;
      }
    }

    if (substances.GetLogger() != nullptr) {
      substances.GetLogger()->Error("Unsupported Action Received", "SEAction::newFromBind");
    }
    return nullptr;
  }
  //----------------------------------------------------------------------------------
  //class SEPatientAction
  void PatientActionsIoDelegate::Marshall(const CDM::PatientActionData& in, SEPatientAction& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::ActionData&>(in), static_cast<SEAction&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEPatientAction& in, CDM::PatientActionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEAction&>(in), static_cast<CDM::ActionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEPatientAssessmentRequest
  void PatientActionsIoDelegate::Marshall(const CDM::PatientAssessmentRequestData& in, SEPatientAssessmentRequest& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Type = in.Type();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEPatientAssessmentRequest& in, CDM::PatientAssessmentRequestData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEAcuteStress
  void PatientActionsIoDelegate::Marshall(const CDM::AcuteStressData& in, SEAcuteStress& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEAcuteStress& in, CDM::AcuteStressData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEAirwayObstruction
  void PatientActionsIoDelegate::Marshall(const CDM::AirwayObstructionData& in, SEAirwayObstruction& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEAirwayObstruction& in, CDM::AirwayObstructionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEApnea
  void PatientActionsIoDelegate::Marshall(const CDM::ApneaData& in, SEApnea& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEApnea& in, CDM::ApneaData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEAsthmaAttack
  void PatientActionsIoDelegate::Marshall(const CDM::AsthmaAttackData& in, SEAsthmaAttack& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEAsthmaAttack& in, CDM::AsthmaAttackData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    CDM_PROPERTY_UNMARSHAL_HELPER(out, Severity)
  }
  //----------------------------------------------------------------------------------
  //class SEBrainInjury
  void PatientActionsIoDelegate::Marshall(const CDM::BrainInjuryData& in, SEBrainInjury& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
    out.m_Type = in.Type();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEBrainInjury& in, CDM::BrainInjuryData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEBronchoconstriction
  void PatientActionsIoDelegate::Marshall(const CDM::BronchoconstrictionData& in, SEBronchoconstriction& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEBronchoconstriction& in, CDM::BronchoconstrictionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEBurnWound
  void PatientActionsIoDelegate::Marshall(const CDM::BurnWoundData& in, SEBurnWound& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.TotalBodySurfaceArea(), out.GetTotalBodySurfaceArea());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEBurnWound& in, CDM::BurnWoundData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_TBSA != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TBSA, out.TotalBodySurfaceArea());
    }
  }
  //----------------------------------------------------------------------------------
  //class SECardiacArrest
  void PatientActionsIoDelegate::Marshall(const CDM::CardiacArrestData& in, SECardiacArrest& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_State = in.State();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SECardiacArrest& in, CDM::CardiacArrestData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    out.State(in.m_State);
  }
  //----------------------------------------------------------------------------------
  //class SEChestCompression
  void PatientActionsIoDelegate::Marshall(const CDM::ChestCompressionData& in, SEChestCompression& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEChestCompression& in, CDM::ChestCompressionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEChestCompressionForce
  void PatientActionsIoDelegate::Marshall(const CDM::ChestCompressionForceData& in, SEChestCompressionForce& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Force(), out.GetForce());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEChestCompressionForce& in, CDM::ChestCompressionForceData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Force != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Force, out.Force());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEChestCompressionForceScale
  void PatientActionsIoDelegate::Marshall(const CDM::ChestCompressionForceScaleData& in, SEChestCompressionForceScale& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.ForceScale(), out.GetForceScale());
    if (in.ForcePeriod().present()) {
      io::PropertyIoDelegate::Marshall(in.ForcePeriod(), out.GetForcePeriod());
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEChestCompressionForceScale& in, CDM::ChestCompressionForceScaleData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_ForceScale != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ForceScale, out.ForceScale());
    }
    if (in.m_ForcePeriod != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ForcePeriod, out.ForcePeriod());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEChestOcclusiveDressing
  void PatientActionsIoDelegate::Marshall(const CDM::ChestOcclusiveDressingData& in, SEChestOcclusiveDressing& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Side = in.Side();
    out.m_State = in.State();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEChestOcclusiveDressing& in, CDM::ChestOcclusiveDressingData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    out.State(in.m_State);
    if (in.HasSide()) {
      out.Side(in.m_Side);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEConsciousRespirationCommand
  void PatientActionsIoDelegate::Marshall(const CDM::ConsciousRespirationCommandData& in, SEConsciousRespirationCommand& out)
  {
    if (in.Comment().present()) {
      out.m_Comment = in.Comment().get();
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEConsciousRespirationCommand& in, CDM::ConsciousRespirationCommandData& out)
  {
    if (in.HasComment()) {
      out.Comment(in.m_Comment);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEForcedInhale
  void PatientActionsIoDelegate::Marshall(const CDM::ForcedInhaleData& in, SEForcedInhale& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::ConsciousRespirationCommandData&>(in), static_cast<SEConsciousRespirationCommand&>(out));
    io::PropertyIoDelegate::Marshall(in.InspiratoryCapacityFraction(), out.GetInspiratoryCapacityFraction());
    io::PropertyIoDelegate::Marshall(in.Period(), out.GetPeriod());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEForcedInhale& in, CDM::ForcedInhaleData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEConsciousRespirationCommand&>(in), static_cast<CDM::ConsciousRespirationCommandData&>(out));
    if (in.m_InspiratoryCapacityFraction != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InspiratoryCapacityFraction, out.InspiratoryCapacityFraction());
    }
    if (in.m_Period != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Period, out.Period());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEForcedExhale
  void PatientActionsIoDelegate::Marshall(const CDM::ForcedExhaleData& in, SEForcedExhale& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::ConsciousRespirationCommandData&>(in), static_cast<SEConsciousRespirationCommand&>(out));
    io::PropertyIoDelegate::Marshall(in.ExpiratoryReserveVolumeFraction(), out.GetExpiratoryReserveVolumeFraction());
    io::PropertyIoDelegate::Marshall(in.Period(), out.GetPeriod());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEForcedExhale& in, CDM::ForcedExhaleData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEConsciousRespirationCommand&>(in), static_cast<CDM::ConsciousRespirationCommandData&>(out));
    if (in.m_ExpiratoryReserveVolumeFraction != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ExpiratoryReserveVolumeFraction, out.ExpiratoryReserveVolumeFraction());
    }
    if (in.m_Period != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Period, out.Period());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEBreathHold
  void PatientActionsIoDelegate::Marshall(const CDM::BreathHoldData& in, SEBreathHold& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::ConsciousRespirationCommandData&>(in), static_cast<SEConsciousRespirationCommand&>(out));
    io::PropertyIoDelegate::Marshall(in.Period(), out.GetPeriod());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEBreathHold& in, CDM::BreathHoldData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEConsciousRespirationCommand&>(in), static_cast<CDM::ConsciousRespirationCommandData&>(out));
    if (in.m_Period != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Period, out.Period());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEUseInhaler
  void PatientActionsIoDelegate::Marshall(const CDM::UseInhalerData& in, SEUseInhaler& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::ConsciousRespirationCommandData&>(in), static_cast<SEConsciousRespirationCommand&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEUseInhaler& in, CDM::UseInhalerData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEConsciousRespirationCommand&>(in), static_cast<CDM::ConsciousRespirationCommandData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEConsciousRespiration
  void PatientActionsIoDelegate::Marshall(const CDM::ConsciousRespirationData& in, SEConsciousRespiration& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    // Set this before our super class tells us to Clear if the action wants us to keep our current data
    out.m_ClearCommands = !in.AppendToPrevious();
    out.m_ClearCommands = true;
    CDM::ConsciousRespirationCommandData* command;
    for (unsigned int i = 0; i < in.Command().size(); i++) {
      command = (CDM::ConsciousRespirationCommandData*)&in.Command()[i];

      CDM::BreathHoldData* bh = dynamic_cast<CDM::BreathHoldData*>(command);
      if (bh != nullptr) {
        PatientActionsIoDelegate::Marshall(*bh, out.AddBreathHold());
        continue;
      }

      CDM::ForcedInhaleData* fi = dynamic_cast<CDM::ForcedInhaleData*>(command);
      if (fi != nullptr) {
        PatientActionsIoDelegate::Marshall(*fi, out.AddForcedInhale());
        continue;
      }

      CDM::ForcedExhaleData* fe = dynamic_cast<CDM::ForcedExhaleData*>(command);
      if (fe != nullptr) {
        PatientActionsIoDelegate::Marshall(*fe, out.AddForcedExhale());
        continue;
      }

      CDM::UseInhalerData* si = dynamic_cast<CDM::UseInhalerData*>(command);
      if (si != nullptr) {
        PatientActionsIoDelegate::Marshall(*si, out.AddUseInhaler());
        continue;
      }
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEConsciousRespiration& in, CDM::ConsciousRespirationData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));

    out.AppendToPrevious(false);
    for (SEConsciousRespirationCommand* cmd : in.m_Commands) {
      auto cmdData = std::unique_ptr<CDM::ConsciousRespirationCommandData>();
      PatientActionsIoDelegate::UnMarshall(*cmd, *cmdData);
      out.Command().push_back( std::move(cmdData) );
    }
  }
  //----------------------------------------------------------------------------------
  //class SEConsumeNutrients
  void PatientActionsIoDelegate::Marshall(const CDM::ConsumeNutrientsData& in, SEConsumeNutrients& out)
  {
    PatientActionsIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    if (in.Nutrition().present()) {
      out.GetNutrition().Load(in.Nutrition().get());
    } else if (in.NutritionFile().present()) {
      out.SetNutritionFile(in.NutritionFile().get());
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEConsumeNutrients& in, CDM::ConsumeNutrientsData& out)
  {
    PatientActionsIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasNutrition()) {
      out.Nutrition(std::unique_ptr<CDM::NutritionData>(in.m_Nutrition->Unload()));
    }
    if (in.HasNutritionFile()) {
      out.NutritionFile(in.m_NutritionFile);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEExercise
  void PatientActionsIoDelegate::Marshall(const CDM::ExerciseData& in, SEExercise& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    if (in.Intensity().present()) {
      io::PropertyIoDelegate::Marshall(in.Intensity(), out.GetIntensity());
    } else if (in.DesiredWorkRate().present()) {
      io::PropertyIoDelegate::Marshall(in.DesiredWorkRate(), out.GetDesiredWorkRate());
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEExercise& in, CDM::ExerciseData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Intensity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Intensity, out.Intensity());
    }
    if (in.m_DesiredWorkRate != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_DesiredWorkRate, out.DesiredWorkRate());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEHemorrhage
  void PatientActionsIoDelegate::Marshall(const CDM::HemorrhageData& in, SEHemorrhage& out)
  {
    out.Clear();
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Compartment = in.Compartment();
    io::PropertyIoDelegate::Marshall(in.InitialRate(), out.GetInitialRate());
    //Place compartments in torso in a map so that we don't get too messy with nested conditionals.  Each vector is digits 2-4 of the MCIS code
    out.organMap["VenaCava"] = std::vector<unsigned int>{ 6, 6, 0 };
    out.organMap["LeftLung"] = std::vector<unsigned int>{ 7, 1, 0 };
    out.organMap["RightLung"] = std::vector<unsigned int>{ 7, 1, 0 };
    out.organMap["Myocardium"] = std::vector<unsigned int>{ 7, 2, 0 };
    out.organMap["Liver"] = std::vector<unsigned int>{ 8, 1, 0 };
    out.organMap["Spleen"] = std::vector<unsigned int>{ 8, 2, 0 };
    out.organMap["Splanchnic"] = std::vector<unsigned int>{ 8, 3, 0 };
    out.organMap["LeftKidney"] = std::vector<unsigned int>{ 8, 4, 0 };
    out.organMap["RightKidney"] = std::vector<unsigned int>{ 8, 4, 0 };
    out.organMap["SmallIntestine"] = std::vector<unsigned int>{ 8, 5, 0 };
    out.organMap["LargeIntestine"] = std::vector<unsigned int>{ 8, 6, 0 };
    out.SetMCIS();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEHemorrhage& in, CDM::HemorrhageData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasCompartment()) {
      out.Compartment(in.m_Compartment);
    }
    if (in.HasInitialRate()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InitialRate, out.InitialRate());
    }
  }
  //----------------------------------------------------------------------------------
  //class SESepsis
  void PatientActionsIoDelegate::Marshall(const CDM::SepsisData& in, SESepsis& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Compartment = in.Compartment();
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESepsis& in, CDM::SepsisData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasCompartment()) {
      out.Compartment(in.m_Compartment);
    }
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
  }
  //----------------------------------------------------------------------------------
  //class SEIntubation
  void PatientActionsIoDelegate::Marshall(const CDM::IntubationData& in, SEIntubation& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Type = in.Type();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEIntubation& in, CDM::IntubationData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEMechanicalVentilation
  void PatientActionsIoDelegate::Marshall(const CDM::MechanicalVentilationData& in, const SESubstanceManager& substances, SEMechanicalVentilation& out)
  {
    out.Clear();
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.SetState(in.State());
    if (in.Flow().present()) {
      io::PropertyIoDelegate::Marshall(in.Flow(), out.GetFlow());
    } else {
      out.GetFlow().Invalidate();
    }
    if (in.Pressure().present()) {
      io::PropertyIoDelegate::Marshall(in.Pressure(), out.GetPressure());
    } else {
      out.GetPressure().Invalidate();
    }

    out.m_GasFractions.clear();
    out.m_cGasFractions.clear();

    for (const CDM::SubstanceFractionData& sfData : in.GasFraction()) {
      auto sub = substances.GetSubstance(sfData.Name());
      if (sub == nullptr) {
        throw CommonDataModelException("Substance not found : " + sfData.Name());
      }
      if (sub->GetState() != CDM::enumSubstanceState::Gas) {
        throw CommonDataModelException("Substance not gas : " + sfData.Name());
      }
      auto subFrac = std::make_unique<SESubstanceFraction>(*sub);
      subFrac->Load(sfData);
      out.m_GasFractions.push_back(subFrac.get());
      out.m_cGasFractions.push_back(subFrac.release());
    }

    if (!out.IsValid()) {
      throw CommonDataModelException("Unable to Marshall SEMechanicalVentilation with the given MechanicalVentilationData");
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEMechanicalVentilation& in, CDM::MechanicalVentilationData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasState()) {
      out.State(in.m_State);
    }
    if (in.HasFlow()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Flow, out.Flow());
    }
    if (in.HasPressure()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Pressure, out.Pressure());
    }

    for (SESubstanceFraction* sf : in.m_GasFractions) {
      out.GasFraction().push_back(std::unique_ptr<CDM::SubstanceFractionData>(sf->Unload()));
    }
  }
  //----------------------------------------------------------------------------------
  //class SENeedleDecompression
  void PatientActionsIoDelegate::Marshall(const CDM::NeedleDecompressionData& in, SENeedleDecompression& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    out.m_Side = in.Side();
    out.m_State = in.State();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SENeedleDecompression& in, CDM::NeedleDecompressionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    out.State(in.m_State);
    if (in.HasSide()) {
      out.Side(in.m_Side);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEPainStimulus
  void PatientActionsIoDelegate::Marshall(const CDM::PainStimulusData& in, SEPainStimulus& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
    out.m_Location = in.Location();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEPainStimulus& in, CDM::PainStimulusData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
    if (in.HasLocation()) {
      out.Location(in.m_Location);
    }
  }
  //----------------------------------------------------------------------------------
  //class SEPericardialEffusion
  void PatientActionsIoDelegate::Marshall(const CDM::PericardialEffusionData& in, SEPericardialEffusion& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.EffusionRate(), out.GetEffusionRate());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEPericardialEffusion& in, CDM::PericardialEffusionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_EffusionRate != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_EffusionRate, out.EffusionRate());
    }
  }
  //----------------------------------------------------------------------------------
  //class SETensionPneumothorax
  void PatientActionsIoDelegate::Marshall(const CDM::TensionPneumothoraxData& in, SETensionPneumothorax& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
    out.m_Type = in.Type();
    out.m_Side = in.Side();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SETensionPneumothorax& in, CDM::TensionPneumothoraxData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
    if (in.HasSide()) {
      out.Side(in.m_Side);
    }
  }
  //----------------------------------------------------------------------------------
  //class SESubstanceAdministration
  void PatientActionsIoDelegate::Marshall(const CDM::SubstanceAdministrationData& in, SESubstanceAdministration& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESubstanceAdministration& in, CDM::SubstanceAdministrationData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SESubstanceBolus
  void PatientActionsIoDelegate::Marshall(const CDM::SubstanceBolusData& in, SESubstanceBolus& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::SubstanceAdministrationData&>(in), static_cast<SESubstanceAdministration&>(out));
    io::PropertyIoDelegate::Marshall(in.Dose(), out.GetDose());
    io::PropertyIoDelegate::Marshall(in.Concentration(), out.GetConcentration());
    out.m_AdminRoute = in.AdminRoute();
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESubstanceBolus& in, CDM::SubstanceBolusData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SESubstanceAdministration&>(in), static_cast<CDM::SubstanceAdministrationData&>(out));

    if (in.m_Dose != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Dose, out.Dose());
    }
    if (in.m_Concentration != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Concentration, out.Concentration());
    }
    if (in.HasAdminRoute()) {
      out.AdminRoute(in.m_AdminRoute);
    }
    out.Substance(in.m_Substance.GetName());
  }
  //----------------------------------------------------------------------------------
  //class SESubstanceBolusState
  void PatientActionsIoDelegate::Marshall(const CDM::SubstanceBolusStateData& in, SESubstanceBolusState& out)
  {
    io::PropertyIoDelegate::Marshall(in.ElapsedTime(), out.m_elapsedTime);
    io::PropertyIoDelegate::Marshall(in.AdministeredDose(), out.m_administeredDose);
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESubstanceBolusState& in, CDM::SubstanceBolusStateData& out)
  {
    out.Substance(in.m_substance.GetName());
    io::PropertyIoDelegate::UnMarshall(in.m_elapsedTime, out.ElapsedTime());
    io::PropertyIoDelegate::UnMarshall(in.m_administeredDose, out.AdministeredDose());
  }
  //----------------------------------------------------------------------------------
  //class SESubstanceCompoundInfusion
  void PatientActionsIoDelegate::Marshall(const CDM::SubstanceCompoundInfusionData& in, SESubstanceCompoundInfusion& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::SubstanceAdministrationData&>(in), static_cast<SESubstanceAdministration&>(out));

    io::PropertyIoDelegate::Marshall(in.Rate(), out.GetRate());
    io::PropertyIoDelegate::Marshall(in.BagVolume(), out.GetBagVolume());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESubstanceCompoundInfusion& in, CDM::SubstanceCompoundInfusionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SESubstanceAdministration&>(in), static_cast<CDM::SubstanceAdministrationData&>(out));
    if (in.m_Rate != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Rate, out.Rate());
    }
    if (in.m_BagVolume != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_BagVolume, out.BagVolume());
    }
    out.SubstanceCompound(in.m_Compound.GetName());
  }
  //----------------------------------------------------------------------------------
  //class SESubstanceInfusion
  void PatientActionsIoDelegate::Marshall(const CDM::SubstanceInfusionData& in, SESubstanceInfusion& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::SubstanceAdministrationData&>(in), static_cast<SESubstanceAdministration&>(out));
    io::PropertyIoDelegate::Marshall(in.Rate(), out.GetRate());
    io::PropertyIoDelegate::Marshall(in.Concentration(), out.GetConcentration());
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SESubstanceInfusion& in, CDM::SubstanceInfusionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SESubstanceAdministration&>(in), static_cast<CDM::SubstanceAdministrationData&>(out));
    if (in.m_Rate != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Rate, out.Rate());
    }
    if (in.m_Concentration != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Concentration, out.Concentration());
    }
    out.Substance(in.m_Substance.GetName());
  }
  //----------------------------------------------------------------------------------
  //class SEUrinate
  void PatientActionsIoDelegate::Marshall(const CDM::UrinateData& in, SEUrinate& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEUrinate& in, CDM::UrinateData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEOverride
  void PatientActionsIoDelegate::Marshall(const CDM::OverrideData& in, SEOverride& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::PatientActionData&>(in), static_cast<SEPatientAction&>(out));

    out.SetOverrideState(in.State());
    out.SetOverrideConformance(in.Conformant());
    if (in.ArterialBloodPHOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.ArterialBloodPHOverride(), out.GetArterialPHOverride());
    } else {
      out.GetArterialPHOverride().Invalidate();
    }
    if (in.VenousBloodPHOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.VenousBloodPHOverride(), out.GetVenousPHOverride());
    } else {
      out.GetVenousPHOverride().Invalidate();
    }
    if (in.CarbonDioxideSaturationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CarbonDioxideSaturationOverride(), out.GetCO2SaturationOverride());
    } else {
      out.GetCO2SaturationOverride().Invalidate();
    }
    if (in.CarbonMonoxideSaturationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CarbonMonoxideSaturationOverride(), out.GetCOSaturationOverride());
    } else {
      out.GetCOSaturationOverride().Invalidate();
    }
    if (in.OxygenSaturationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.OxygenSaturationOverride(), out.GetO2SaturationOverride());
    } else {
      out.GetO2SaturationOverride().Invalidate();
    }
    if (in.PhosphateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.PhosphateOverride(), out.GetPhosphateOverride());
    } else {
      out.GetPhosphateOverride().Invalidate();
    }
    if (in.WhiteBloodCellCountOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.WhiteBloodCellCountOverride(), out.GetWBCCountOverride());
    } else {
      out.GetWBCCountOverride().Invalidate();
    }
    if (in.TotalBilirubinOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalBilirubinOverride(), out.GetTotalBilirubinOverride());
    } else {
      out.GetTotalBilirubinOverride().Invalidate();
    }
    if (in.CalciumConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CalciumConcentrationOverride(), out.GetCalciumConcentrationOverride());
    } else {
      out.GetCalciumConcentrationOverride().Invalidate();
    }
    if (in.GlucoseConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.GlucoseConcentrationOverride(), out.GetGlucoseConcentrationOverride());
    } else {
      out.GetGlucoseConcentrationOverride().Invalidate();
    }
    if (in.LactateConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LactateConcentrationOverride(), out.GetLactateConcentrationOverride());
    } else {
      out.GetLactateConcentrationOverride().Invalidate();
    }
    if (in.PotassiumConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.PotassiumConcentrationOverride(), out.GetPotassiumConcentrationOverride());
    } else {
      out.GetPotassiumConcentrationOverride().Invalidate();
    }
    if (in.SodiumConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.SodiumConcentrationOverride(), out.GetSodiumConcentrationOverride());
    } else {
      out.GetSodiumConcentrationOverride().Invalidate();
    }
    if (in.BloodVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.BloodVolumeOverride(), out.GetBloodVolumeOverride());
    } else {
      out.GetBloodVolumeOverride().Invalidate();
    }
    if (in.CardiacOutputOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CardiacOutputOverride(), out.GetCardiacOutputOverride());
    } else {
      out.GetCardiacOutputOverride().Invalidate();
    }
    if (in.DiastolicArterialPressureOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.DiastolicArterialPressureOverride(), out.GetDiastolicArterialPressureOverride());
    } else {
      out.GetDiastolicArterialPressureOverride().Invalidate();
    }
    if (in.MeanArterialPressureOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.MeanArterialPressureOverride(), out.GetMAPOverride());
    } else {
      out.GetMAPOverride().Invalidate();
    }
    if (in.HeartRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.HeartRateOverride(), out.GetHeartRateOverride());
    } else {
      out.GetHeartRateOverride().Invalidate();
    }
    if (in.HeartStrokeVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.HeartStrokeVolumeOverride(), out.GetHeartStrokeVolumeOverride());
    } else {
      out.GetHeartStrokeVolumeOverride().Invalidate();
    }
    if (in.SystolicArterialPressureOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.SystolicArterialPressureOverride(), out.GetSystolicArterialPressureOverride());
    } else {
      out.GetSystolicArterialPressureOverride().Invalidate();
    }
    if (in.InsulinSynthesisRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.InsulinSynthesisRateOverride(), out.GetInsulinSynthesisRateOverride());
    } else {
      out.GetInsulinSynthesisRateOverride().Invalidate();
    }
    if (in.GlucagonSynthesisRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.GlucagonSynthesisRateOverride(), out.GetGlucagonSynthesisRateOverride());
    } else {
      out.GetGlucagonSynthesisRateOverride().Invalidate();
    }
    if (in.AchievedExerciseLevelOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.AchievedExerciseLevelOverride(), out.GetAchievedExerciseLevelOverride());
    } else {
      out.GetAchievedExerciseLevelOverride().Invalidate();
    }
    if (in.CoreTemperatureOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CoreTemperatureOverride(), out.GetCoreTemperatureOverride());
    } else {
      out.GetCoreTemperatureOverride().Invalidate();
    }
    if (in.CreatinineProductionRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.CreatinineProductionRateOverride(), out.GetCreatinineProductionRateOverride());
    } else {
      out.GetCreatinineProductionRateOverride().Invalidate();
    }
    if (in.ExerciseMeanArterialPressureDeltaOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.ExerciseMeanArterialPressureDeltaOverride(), out.GetExerciseMeanArterialPressureDeltaOverride());
    } else {
      out.GetExerciseMeanArterialPressureDeltaOverride().Invalidate();
    }
    if (in.FatigueLevelOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.FatigueLevelOverride(), out.GetFatigueLevelOverride());
    } else {
      out.GetFatigueLevelOverride().Invalidate();
    }
    if (in.LactateProductionRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LactateProductionRateOverride(), out.GetLactateProductionRateOverride());
    } else {
      out.GetLactateProductionRateOverride().Invalidate();
    }
    if (in.SkinTemperatureOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.SkinTemperatureOverride(), out.GetSkinTemperatureOverride());
    } else {
      out.GetSkinTemperatureOverride().Invalidate();
    }
    if (in.SweatRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.SweatRateOverride(), out.GetSweatRateOverride());
    } else {
      out.GetSweatRateOverride().Invalidate();
    }
    if (in.TotalMetabolicRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalMetabolicRateOverride(), out.GetTotalMetabolicOverride());
    } else {
      out.GetTotalMetabolicOverride().Invalidate();
    }
    if (in.TotalWorkRateLevelOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalWorkRateLevelOverride(), out.GetTotalWorkRateLevelOverride());
    } else {
      out.GetTotalWorkRateLevelOverride().Invalidate();
    }
    if (in.SodiumLostToSweatOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.SodiumLostToSweatOverride(), out.GetSodiumLostToSweatOverride());
    } else {
      out.GetSodiumLostToSweatOverride().Invalidate();
    }
    if (in.PotassiumLostToSweatOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.PotassiumLostToSweatOverride(), out.GetPotassiumLostToSweatOverride());
    } else {
      out.GetPotassiumLostToSweatOverride().Invalidate();
    }
    if (in.ChlorideLostToSweatOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.ChlorideLostToSweatOverride(), out.GetChlorideLostToSweatOverride());
    } else {
      out.GetChlorideLostToSweatOverride().Invalidate();
    }
    if (in.LeftAfferentArterioleResistanceOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LeftAfferentArterioleResistanceOverride(), out.GetLeftAfferentArterioleResistanceOverride());
    } else {
      out.GetLeftAfferentArterioleResistanceOverride().Invalidate();
    }
    if (in.LeftGlomerularFiltrationRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LeftGlomerularFiltrationRateOverride(), out.GetLeftGlomerularFiltrationRateOverride());
    } else {
      out.GetLeftGlomerularFiltrationRateOverride().Invalidate();
    }
    if (in.LeftReabsorptionRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LeftReabsorptionRateOverride(), out.GetLeftReaborptionRateOverride());
    } else {
      out.GetLeftReaborptionRateOverride().Invalidate();
    }
    if (in.RenalBloodFlowOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RenalBloodFlowOverride(), out.GetRenalBloodFlowOverride());
    } else {
      out.GetRenalBloodFlowOverride().Invalidate();
    }
    if (in.RenalPlasmaFlowOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RenalPlasmaFlowOverride(), out.GetRenalPlasmaFlowOverride());
    } else {
      out.GetRenalPlasmaFlowOverride().Invalidate();
    }
    if (in.RightAfferentArterioleResistanceOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RightAfferentArterioleResistanceOverride(), out.GetRightAfferentArterioleResistanceOverride());
    } else {
      out.GetRightAfferentArterioleResistanceOverride().Invalidate();
    }
    if (in.RightGlomerularFiltrationRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RightGlomerularFiltrationRateOverride(), out.GetRightGlomerularFiltrationRateOverride());
    } else {
      out.GetRightGlomerularFiltrationRateOverride().Invalidate();
    }
    if (in.RightReabsorptionRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RightReabsorptionRateOverride(), out.GetRightReaborptionRateOverride());
    } else {
      out.GetRightReaborptionRateOverride().Invalidate();
    }
    if (in.UrinationRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.UrinationRateOverride(), out.GetUrinationRateOverride());
    } else {
      out.GetUrinationRateOverride().Invalidate();
    }
    if (in.UrineProductionRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.UrineProductionRateOverride(), out.GetUrineProductionRateOverride());
    } else {
      out.GetUrineProductionRateOverride().Invalidate();
    }
    if (in.UrineOsmolalityOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.UrineOsmolalityOverride(), out.GetUrineOsmolalityOverride());
    } else {
      out.GetUrineOsmolalityOverride().Invalidate();
    }
    if (in.UrineVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.UrineVolumeOverride(), out.GetUrineVolumeOverride());
    } else {
      out.GetUrineVolumeOverride().Invalidate();
    }
    if (in.UrineUreaNitrogenConcentrationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.UrineUreaNitrogenConcentrationOverride(), out.GetUrineUreaNitrogenConcentrationOverride());
    } else {
      out.GetUrineUreaNitrogenConcentrationOverride().Invalidate();
    }
    if (in.ExpiratoryFlowOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.ExpiratoryFlowOverride(), out.GetExpiratoryFlowOverride());
    } else {
      out.GetExpiratoryFlowOverride().Invalidate();
    }
    if (in.InspiratoryFlowOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.InspiratoryFlowOverride(), out.GetInspiratoryFlowOverride());
    } else {
      out.GetInspiratoryFlowOverride().Invalidate();
    }
    if (in.PulmonaryComplianceOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.PulmonaryComplianceOverride(), out.GetPulmonaryComplianceOverride());
    } else {
      out.GetPulmonaryComplianceOverride().Invalidate();
    }
    if (in.PulmonaryResistanceOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.PulmonaryResistanceOverride(), out.GetPulmonaryResistanceOverride());
    } else {
      out.GetPulmonaryResistanceOverride().Invalidate();
    }
    if (in.RespirationRateOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.RespirationRateOverride(), out.GetRespirationRateOverride());
    } else {
      out.GetRespirationRateOverride().Invalidate();
    }
    if (in.TidalVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TidalVolumeOverride(), out.GetTidalVolumeOverride());
    } else {
      out.GetTidalVolumeOverride().Invalidate();
    }
    if (in.TargetPulmonaryVentilationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TargetPulmonaryVentilationOverride(), out.GetTargetPulmonaryVentilationOverride());
    } else {
      out.GetTargetPulmonaryVentilationOverride().Invalidate();
    }
    if (in.TotalAlveolarVentilationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalAlveolarVentilationOverride(), out.GetTotalAlveolarVentilationOverride());
    } else {
      out.GetTotalAlveolarVentilationOverride().Invalidate();
    }
    if (in.TotalLungVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalLungVolumeOverride(), out.GetTotalLungVolumeOverride());
    } else {
      out.GetTotalLungVolumeOverride().Invalidate();
    }
    if (in.TotalPulmonaryVentilationOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.TotalPulmonaryVentilationOverride(), out.GetTotalPulmonaryVentilationOverride());
    } else {
      out.GetTotalPulmonaryVentilationOverride().Invalidate();
    }
    if (in.ExtravascularFluidVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.ExtravascularFluidVolumeOverride(), out.GetExtravascularFluidVolumeOverride());
    } else {
      out.GetExtravascularFluidVolumeOverride().Invalidate();
    }
    if (in.IntracellularFluidVolumeOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.IntracellularFluidVolumeOverride(), out.GetIntracellularFluidVolumeOverride());
    } else {
      out.GetIntracellularFluidVolumeOverride().Invalidate();
    }
    if (in.LiverGlycogenOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.LiverGlycogenOverride(), out.GetLiverGlycogenOverride());
    } else {
      out.GetLiverGlycogenOverride().Invalidate();
    }
    if (in.MuscleGlycogenOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.MuscleGlycogenOverride(), out.GetMuscleGlycogenOverride());
    } else {
      out.GetMuscleGlycogenOverride().Invalidate();
    }
    if (in.StoredProteinOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.StoredProteinOverride(), out.GetStoredProteinOverride());
    } else {
      out.GetStoredProteinOverride().Invalidate();
    }
    if (in.StoredFatOverride().present()) {
      io::PropertyIoDelegate::Marshall(in.StoredFatOverride(), out.GetStoredFatOverride());
    } else {
      out.GetStoredFatOverride().Invalidate();
    }

    if (!out.IsValid()) {
      throw CommonDataModelException("Unable to marshall SEOverride from the provided OverrideData");
    }
  }
  //----------------------------------------------------------------------------------
  void PatientActionsIoDelegate::UnMarshall(const SEOverride& in, CDM::OverrideData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SEPatientAction&>(in), static_cast<CDM::PatientActionData&>(out));
    if (in.HasOverrideState()) {
      out.State((in.m_OverrideState) ? CDM::enumOnOff::On : CDM::enumOnOff::Off);
    }
    if (in.HasOverrideConformance()) {
      out.Conformant((in.m_OverrideConformance) ? CDM::enumOnOff::On : CDM::enumOnOff::Off);
    }
    if (in.HasArterialPHOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ArterialPHOR, out.ArterialBloodPHOverride());
    }
    if (in.HasVenousPHOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_VenousPHOR, out.VenousBloodPHOverride());
    }
    if (in.HasCO2SaturationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_CO2SaturationOR, out.CarbonDioxideSaturationOverride());
    }
    if (in.HasCOSaturationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_COSaturationOR, out.CarbonMonoxideSaturationOverride());
    }
    if (in.HasO2SaturationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_O2SaturationOR, out.OxygenSaturationOverride());
    }
    if (in.HasPhosphateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_PhosphateOR, out.PhosphateOverride());
    }
    if (in.HasWBCCountOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_WBCCountOR, out.WhiteBloodCellCountOverride());
    }
    if (in.HasTotalBilirubinOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalBilirubinOR, out.TotalBilirubinOverride());
    }
    if (in.HasCalciumConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_CalciumConcentrationOR, out.CalciumConcentrationOverride());
    }
    if (in.HasGlucoseConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_GlucoseConcentrationOR, out.GlucoseConcentrationOverride());
    }
    if (in.HasLactateConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LactateConcentrationOR, out.LactateConcentrationOverride());
    }
    if (in.HasPotassiumConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_PotassiumConcentrationOR, out.PotassiumConcentrationOverride());
    }
    if (in.HasSodiumConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_SodiumConcentrationOR, out.SodiumConcentrationOverride());
    }
    if (in.HasBloodVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_BloodVolumeOR, out.BloodVolumeOverride());
    }
    if (in.HasCardiacOutputOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_CardiacOutputOR, out.CardiacOutputOverride());
    }
    if (in.HasDiastolicArterialPressureOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_DiastolicArtPressureOR, out.DiastolicArterialPressureOverride());
    }
    if (in.HasMAPOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_MeanArtPressureOR, out.MeanArterialPressureOverride());
    }
    if (in.HasHeartRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_HeartRateOR, out.HeartRateOverride());
    }
    if (in.HasHeartStrokeVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_HeartStrokeVolumeOR, out.HeartStrokeVolumeOverride());
    }
    if (in.HasSystolicArterialPressureOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_SystolicArtPressureOR, out.SystolicArterialPressureOverride());
    }
    if (in.HasInsulinSynthesisRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InsulinSynthesisRateOR, out.InsulinSynthesisRateOverride());
    }
    if (in.HasGlucagonSynthesisRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_GlucagonSynthesisRateOR, out.GlucagonSynthesisRateOverride());
    }
    if (in.HasAchievedExerciseLevelOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_AcheivedExerciseLevelOR, out.AchievedExerciseLevelOverride());
    }
    if (in.HasCoreTemperatureOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_CoreTemperatureOR, out.CoreTemperatureOverride());
    }
    if (in.HasCreatinineProductionRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_CreatinineProductionRateOR, out.CreatinineProductionRateOverride());
    }
    if (in.HasExerciseMeanArterialPressureDeltaOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ExerciseMeanArterialPressureDeltaOR, out.ExerciseMeanArterialPressureDeltaOverride());
    }
    if (in.HasFatigueLevelOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_FatigueLevelOR, out.FatigueLevelOverride());
    }
    if (in.HasLactateProductionRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LactateProductionRateOR, out.LactateProductionRateOverride());
    }
    if (in.HasSkinTemperatureOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_SkinTemperatureOR, out.SkinTemperatureOverride());
    }
    if (in.HasSweatRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_SweatRateOR, out.SweatRateOverride());
    }
    if (in.HasTotalMetabolicOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalMetabolicOR, out.TotalMetabolicRateOverride());
    }
    if (in.HasTotalWorkRateLevelOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalWorkRateLevelOR, out.TotalWorkRateLevelOverride());
    }
    if (in.HasSodiumLostToSweatOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_SodiumLostToSweatOR, out.SodiumLostToSweatOverride());
    }
    if (in.HasPotassiumLostToSweatOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_PotassiumLostToSweatOR, out.PotassiumLostToSweatOverride());
    }
    if (in.HasChlorideLostToSweatOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ChlorideLostToSweatOR, out.ChlorideLostToSweatOverride());
    }
    if (in.HasLeftAfferentArterioleResistanceOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LAfferentArterioleResistOR, out.LeftAfferentArterioleResistanceOverride());
    }
    if (in.HasLeftGlomerularFiltrationRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m__LeftGlomerularFiltrationOR, out.LeftGlomerularFiltrationRateOverride());
      ;
    }
    if (in.HasLeftReaborptionRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LReabsorptionRateOR, out.LeftReabsorptionRateOverride());
    }
    if (in.HasRenalBloodFlowOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RenalBloodFlowOR, out.RenalBloodFlowOverride());
    }
    if (in.HasRenalPlasmaFlowOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RenalPlasmaOR, out.RenalPlasmaFlowOverride());
    }
    if (in.HasRightAfferentArterioleResistanceOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RAfferentArterioleResistOR, out.RightAfferentArterioleResistanceOverride());
    }
    if (in.HasRightGlomerularFiltrationRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m__RightGlomerularFiltrationOR, out.RightGlomerularFiltrationRateOverride());
    }
    if (in.HasRightReaborptionRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RReabsorptionRateOR, out.RightReabsorptionRateOverride());
    }
    if (in.HasUrineProductionRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_UrineProductionRateOR, out.UrineProductionRateOverride());
    }
    if (in.HasUrineOsmolalityOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_UrineOsmolalityOR, out.UrineOsmolalityOverride());
    }
    if (in.HasUrineVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_UrineVolumeOR, out.UrineVolumeOverride());
    }
    if (in.HasUrineUreaNitrogenConcentrationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_UrineUreaNitrogenConcentrationOverrideOR, out.UrineUreaNitrogenConcentrationOverride());
    }
    if (in.HasExpiratoryFlowOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ExpiratoryFlowOR, out.ExpiratoryFlowOverride());
    }
    if (in.HasInspiratoryFlowOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InspiratoryFlowOR, out.InspiratoryFlowOverride());
    }
    if (in.HasPulmonaryComplianceOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_PulmonaryComplianceOR, out.PulmonaryComplianceOverride());
    }
    if (in.HasPulmonaryResistanceOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_PulmonaryResistanceOR, out.PulmonaryResistanceOverride());
    }
    if (in.HasRespirationRateOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RespirationRateOR, out.RespirationRateOverride());
    }
    if (in.HasTidalVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TidalVolumeOR, out.TidalVolumeOverride());
    }
    if (in.HasTargetPulmonaryVentilationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TargetPulmonaryVentilationOR, out.TargetPulmonaryVentilationOverride());
    }
    if (in.HasTotalAlveolarVentilationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalAlveolarVentilationOR, out.TotalAlveolarVentilationOverride());
    }
    if (in.HasTotalLungVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalLungVolumeOR, out.TotalLungVolumeOverride());
    }
    if (in.HasTotalPulmonaryVentilationOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_TotalPulmonaryVentilationOR, out.TotalPulmonaryVentilationOverride());
    }
    if (in.HasExtravascularFluidVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ExtravascularFluidVolumeOR, out.ExtravascularFluidVolumeOverride());
    }
    if (in.HasIntracellularFluidVolumeOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_IntracellularFluidVolumeOR, out.IntracellularFluidVolumeOverride());
    }
    if (in.HasLiverGlycogenOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LiverGlycogenOR, out.LiverGlycogenOverride());
    }
    if (in.HasMuscleGlycogenOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_MuscleGlycogenOR, out.MuscleGlycogenOverride());
    }
    if (in.HasStoredProteinOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_StoredProteinOR, out.StoredProteinOverride());
    }
    if (in.HasStoredFatOverride()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_StoredFatOR, out.StoredFatOverride());
    }
  }
  //----------------------------------------------------------------------------------
}
}