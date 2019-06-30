#include "PatientConditionsIoDelegate.h"

#include "PropertyIoDelegate.h"
#include "ScenarioIoDelegate.h"

#include "biogears/cdm/system/environment/conditions/SEInitialEnvironment.h"
#include <biogears/cdm/patient/conditions/SEChronicAnemia.h>
#include <biogears/cdm/patient/conditions/SEChronicHeartFailure.h>
#include <biogears/cdm/patient/conditions/SEChronicObstructivePulmonaryDisease.h>
#include <biogears/cdm/patient/conditions/SEChronicPericardialEffusion.h>
#include <biogears/cdm/patient/conditions/SEChronicRenalStenosis.h>
#include <biogears/cdm/patient/conditions/SEChronicVentricularSystolicDysfunction.h>
#include <biogears/cdm/patient/conditions/SEDehydration.h>
#include <biogears/cdm/patient/conditions/SEDiabetesType1.h>
#include <biogears/cdm/patient/conditions/SEDiabetesType2.h>
#include <biogears/cdm/patient/conditions/SEImpairedAlveolarExchange.h>
#include <biogears/cdm/patient/conditions/SELobarPneumonia.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/cdm/patient/conditions/SEStarvation.h>
#include <biogears/cdm/scenario/SECondition.h>

#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarArea.h>

#include "biogears/cdm/substance/SESubstanceManager.h"

namespace biogears {
namespace io {
  //class SEConditionList
  std::vector<std::unique_ptr<SECondition>> PatientConditionsIoDelegate::condition_factory(const CDM::ConditionListData& in, SESubstanceManager& substances)
  {
    std::vector<std::unique_ptr<SECondition>> r_vec;
    for (const auto condition_data : in.Condition()) {
      r_vec.emplace_back(factory(condition_data, substances));
    }
    return std::move(r_vec);
  }
  //----------------------------------------------------------------------------------
  std::unique_ptr<SECondition> PatientConditionsIoDelegate::factory(const CDM::ConditionData& data, SESubstanceManager& substances)
  {
    // Could speed up case by testing Patient Conditions vs another type
    // But we only have 1 type at this time, and a few conditions to support
    const auto ccAnemiaData = dynamic_cast<const CDM::ChronicAnemiaData*>(&data);
    if (ccAnemiaData != nullptr) {
      auto cc = std::make_unique<SEChronicAnemia>();
      PatientConditionsIoDelegate::Marshall(*ccAnemiaData,*cc);
      return cc;
    }
    const auto ccopdData = dynamic_cast<const CDM::ChronicObstructivePulmonaryDiseaseData*>(&data);
    if (ccopdData != nullptr) {
      auto cc = std::make_unique<SEChronicObstructivePulmonaryDisease>();
      PatientConditionsIoDelegate::Marshall(*ccopdData,*cc);
      return cc;
    }
    const auto ccVentSysDysfuncData = dynamic_cast<const CDM::ChronicVentricularSystolicDysfunctionData*>(&data);
    if (ccVentSysDysfuncData != nullptr) {
      auto cc = std::make_unique<SEChronicVentricularSystolicDysfunction>();
      PatientConditionsIoDelegate::Marshall(*ccVentSysDysfuncData,*cc);
      return cc;
    }
    const auto ccPericardialEffusionData = dynamic_cast<const CDM::ChronicPericardialEffusionData*>(&data);
    if (ccPericardialEffusionData != nullptr) {
      auto cc = std::make_unique<SEChronicPericardialEffusion>();
      PatientConditionsIoDelegate::Marshall(*ccPericardialEffusionData,*cc);
      return cc;
    }
    const auto ccRenalStenosisData = dynamic_cast<const CDM::ChronicRenalStenosisData*>(&data);
    if (ccRenalStenosisData != nullptr) {
      auto cc = std::make_unique<SEChronicRenalStenosis>();
      PatientConditionsIoDelegate::Marshall(*ccRenalStenosisData,*cc);
      return cc;
    }
    const auto ccDehydrationData = dynamic_cast<const CDM::DehydrationData*>(&data);
    if (ccDehydrationData != nullptr) {
      auto cc = std::make_unique<SEDehydration>();
      PatientConditionsIoDelegate::Marshall(*ccDehydrationData,*cc);
      return cc;
    }
    const auto ccDiabetesType1Data = dynamic_cast<const CDM::DiabetesType1Data*>(&data);
    if (ccDiabetesType1Data != nullptr) {
      auto cc = std::make_unique<SEDiabetesType1>();
      PatientConditionsIoDelegate::Marshall(*ccDiabetesType1Data,*cc);
      return cc;
    }
    const auto ccDiabetesType2Data = dynamic_cast<const CDM::DiabetesType2Data*>(&data);
    if (ccDiabetesType2Data != nullptr) {
      auto cc = std::make_unique<SEDiabetesType2>();
      PatientConditionsIoDelegate::Marshall(*ccDiabetesType2Data,*cc);
      return cc;
    }
    const auto ccStarvationData = dynamic_cast<const CDM::StarvationData*>(&data);
    if (ccStarvationData != nullptr) {
      auto cc = std::make_unique<SEStarvation>();
      PatientConditionsIoDelegate::Marshall(*ccStarvationData,*cc);
      return cc;
    }
    const auto ccImpairedAlveolarExchangeData = dynamic_cast<const CDM::ImpairedAlveolarExchangeData*>(&data);
    if (ccImpairedAlveolarExchangeData != nullptr) {
      auto cc = std::make_unique<SEImpairedAlveolarExchange>();
      PatientConditionsIoDelegate::Marshall(*ccImpairedAlveolarExchangeData,*cc);
      return cc;
    }
    const auto ccLobarPneumoniaData = dynamic_cast<const CDM::LobarPneumoniaData*>(&data);
    if (ccLobarPneumoniaData != nullptr) {
      auto cc = std::make_unique<SELobarPneumonia>();
      PatientConditionsIoDelegate::Marshall(*ccLobarPneumoniaData,*cc);
      return cc;
    }
    const auto ccInitialEnvironmentData = dynamic_cast<const CDM::InitialEnvironmentData*>(&data);
    if (ccInitialEnvironmentData != nullptr) {
      auto cc = std::make_unique<SEInitialEnvironment>(substances);
      cc->Load(*ccInitialEnvironmentData);
      return cc;
    }

    if (substances.GetLogger() != nullptr) {
      substances.GetLogger()->Error("Unsupported Condition Received", "PatientConditionsIoDelegate::factory");
      throw CommonDataModelException("Unsupported Condition Received in PatientConditionsIoDelegate::factory");
    }
    return nullptr;
  }
  //----------------------------------------------------------------------------------
  //SEPatientCondition
  void PatientConditionsIoDelegate::Marshall(const CDM::PatientConditionData& in, SEPatientCondition& out)
  {
    ScenarioIoDelegate::Marshall(static_cast<const CDM::ConditionData&>(in), static_cast<SECondition&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEPatientCondition& in, CDM::PatientConditionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
  }
  //SEChronicAnemia
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicAnemiaData& in, SEChronicAnemia& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.ReductionFactor(), out.GetReductionFactor());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicAnemia& in, CDM::ChronicAnemiaData& out)
  {
    PatientConditionsIoDelegate::UnMarshall(static_cast<const SEPatientCondition&>(in), static_cast<CDM::PatientConditionData&>(out));
    if (in.m_ReductionFactor != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ReductionFactor, out.ReductionFactor());
    }
  }
  //----------------------------------------------------------------------------------
  //SEChronicHeartFailure
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicHeartFailureData& in, SEChronicHeartFailure& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicHeartFailure& in, CDM::ChronicHeartFailureData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //SEChronicVentricularSystolicDysfunction
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicVentricularSystolicDysfunctionData& in, SEChronicVentricularSystolicDysfunction& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicVentricularSystolicDysfunction& in, CDM::ChronicVentricularSystolicDysfunctionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //SEChronicObstructivePulmonaryDisease
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicObstructivePulmonaryDiseaseData& in, SEChronicObstructivePulmonaryDisease& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.BronchitisSeverity(), out.GetBronchitisSeverity());
    io::PropertyIoDelegate::Marshall(in.EmphysemaSeverity(), out.GetEmphysemaSeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicObstructivePulmonaryDisease& in, CDM::ChronicObstructivePulmonaryDiseaseData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));

    if (in.m_BronchitisSeverity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_BronchitisSeverity, out.BronchitisSeverity());
    }
    if (in.m_EmphysemaSeverity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_EmphysemaSeverity, out.BronchitisSeverity());
    }
  }
  //----------------------------------------------------------------------------------
  //SEChronicPericardialEffusion
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicPericardialEffusionData& in, SEChronicPericardialEffusion& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.AccumulatedVolume(), out.GetAccumulatedVolume());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicPericardialEffusion& in, CDM::ChronicPericardialEffusionData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_AccumulatedVolume != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_AccumulatedVolume, out.AccumulatedVolume());
    }
  }
  //----------------------------------------------------------------------------------
  //SEChronicRenalStenosis
  void PatientConditionsIoDelegate::Marshall(const CDM::ChronicRenalStenosisData& in, SEChronicRenalStenosis& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.LeftKidneySeverity(), out.GetLeftKidneySeverity());
    io::PropertyIoDelegate::Marshall(in.RightKidneySeverity(), out.GetRightKidneySeverity());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEChronicRenalStenosis& in, CDM::ChronicRenalStenosisData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.HasLeftKidneySeverity()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LeftKidneySeverity, out.LeftKidneySeverity());
    }
    if (in.HasRightKidneySeverity()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RightKidneySeverity, out.RightKidneySeverity());
    }
  }
  //----------------------------------------------------------------------------------
  //SEDehydration
  void PatientConditionsIoDelegate::Marshall(const CDM::DehydrationData& in, SEDehydration& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.DehydrationFraction(), out.GetDehydrationFraction());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEDehydration& in, CDM::DehydrationData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_DehydrationFraction != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_DehydrationFraction, out.DehydrationFraction());
      ;
    }
  }
  //----------------------------------------------------------------------------------
  //SEDiabetesType1
  void PatientConditionsIoDelegate::Marshall(const CDM::DiabetesType1Data& in, SEDiabetesType1& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.InsulinProductionSeverity(), out.GetInsulinProductionSeverity());
  
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEDiabetesType1& in, CDM::DiabetesType1Data& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_InsulinProductionSeverity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InsulinProductionSeverity, out.InsulinProductionSeverity());
    }
  }
  //----------------------------------------------------------------------------------
  //SEDiabetesType2
  void PatientConditionsIoDelegate::Marshall(const CDM::DiabetesType2Data& in, SEDiabetesType2& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.InsulinProductionSeverity(), out.GetInsulinProductionSeverity());
    io::PropertyIoDelegate::Marshall(in.InsulinResistanceSeverity(), out.GetInsulinResistanceSeverity());
  
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEDiabetesType2& in, CDM::DiabetesType2Data& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_InsulinProductionSeverity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InsulinProductionSeverity, out.InsulinProductionSeverity());
    }
    if (in.m_InsulinResistanceSeverity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_InsulinResistanceSeverity, out.InsulinResistanceSeverity());
    }
  }
  //----------------------------------------------------------------------------------
  //SEImpairedAlveolarExchange
  void PatientConditionsIoDelegate::Marshall(const CDM::ImpairedAlveolarExchangeData& in, SEImpairedAlveolarExchange& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.ImpairedSurfaceArea(), out.GetImpairedSurfaceArea());
    io::PropertyIoDelegate::Marshall(in.ImpairedFraction(), out.GetImpairedFraction());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEImpairedAlveolarExchange& in, CDM::ImpairedAlveolarExchangeData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.HasImpairedSurfaceArea()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ImpairedSurfaceArea, out.ImpairedSurfaceArea());
    }
    if (in.HasImpairedFraction()) {
      io::PropertyIoDelegate::UnMarshall(*in.m_ImpairedFraction, out.ImpairedFraction());
    }
  }
  //----------------------------------------------------------------------------------
  //SELobarPneumonia
  void PatientConditionsIoDelegate::Marshall(const CDM::LobarPneumoniaData& in, SELobarPneumonia& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.Severity(), out.GetSeverity());
    io::PropertyIoDelegate::Marshall(in.LeftLungAffected(), out.GetLeftLungAffected());
    io::PropertyIoDelegate::Marshall(in.RightLungAffected(), out.GetRightLungAffected());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SELobarPneumonia& in, CDM::LobarPneumoniaData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_Severity != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_Severity, out.Severity());
    }
    if (in.m_LeftLungAffected != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_LeftLungAffected, out.LeftLungAffected());
    }
    if (in.m_RightLungAffected != nullptr) {
      io::PropertyIoDelegate::UnMarshall(*in.m_RightLungAffected, out.RightLungAffected());
    }
  }
  //----------------------------------------------------------------------------------
  //SEStarvation
  void PatientConditionsIoDelegate::Marshall(const CDM::StarvationData& in, SEStarvation& out)
  {
    PatientConditionsIoDelegate::Marshall(static_cast<const CDM::PatientConditionData&>(in), static_cast<SEPatientCondition&>(out));
    io::PropertyIoDelegate::Marshall(in.TimeSinceMeal(), out.GetTimeSinceMeal());
  }
  //----------------------------------------------------------------------------------
  void PatientConditionsIoDelegate::UnMarshall(const SEStarvation& in, CDM::StarvationData& out)
  {
    ScenarioIoDelegate::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
    if (in.m_TimeSinceMeal != nullptr)
      io::PropertyIoDelegate::UnMarshall(*in.m_TimeSinceMeal, out.TimeSinceMeal());
  }
  //----------------------------------------------------------------------------------
}
}
