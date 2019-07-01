#include "Scenario.h"

#include "PatientActions.h"
#include "PatientConditions.h"
#include "Property.h"

#include <biogears/cdm/scenario/SEAction.h>
#include <biogears/cdm/scenario/SEAdvanceTime.h>
#include <biogears/cdm/scenario/SECondition.h>

#include <biogears/cdm/engine/PhysiologyEngineConfiguration.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/scenario/SEAnesthesiaMachineActionCollection.h>
#include <biogears/cdm/scenario/SEEnvironmentActionCollection.h>
#include <biogears/cdm/scenario/SEInhalerActionCollection.h>
#include <biogears/cdm/scenario/SEScenario.h>
#include <biogears/cdm/scenario/SEScenarioAutoSerialization.h>
#include <biogears/cdm/scenario/SEScenarioInitialParameters.h>
#include <biogears/cdm/scenario/SESerializeState.h>
#include <biogears/cdm/scenario/requests/SECompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SECompartmentSubstanceDataRequest.h>
#include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>
#include <biogears/cdm/scenario/requests/SEEnvironmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEEquipmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEGasCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SELiquidCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEPatientDataRequest.h>
#include <biogears/cdm/scenario/requests/SEPhysiologyDataRequest.h>
#include <biogears/cdm/scenario/requests/SESubstanceDataRequest.h>
#include <biogears/cdm/scenario/requests/SEThermalCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SETissueCompartmentDataRequest.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceManager.h>

namespace biogears {
namespace io {
  void Scenario::Marshall(const CDM::ConditionData& in, SECondition& out)
  {
    out.Clear();
    if (in.Comment().present()) {
      out.m_Comment = in.Comment().get();
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SECondition& in, CDM::ConditionData& out)
  {
    if (in.HasComment()) {
      out.Comment(in.m_Comment);
    }
  }
  //-----------------------------------------------------------------------------
  //class SEAction
  void Scenario::Marshall(const CDM::ActionData& in, SEAction& out)
  {
    out.Clear();
    if (in.Comment().present()) {
      out.m_Comment = in.Comment().get();
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEAction& in, CDM::ActionData& out)
  {
    if (in.HasComment()) {
      out.Comment(in.m_Comment);
    }
  }
  //-----------------------------------------------------------------------------
  //class SEDataRequest
  void Scenario::Marshall(const CDM::DataRequestData& in, SEDataRequest& out)
  {
    io::Property::Marshall(static_cast<CDM::DecimalFormatData const&>(in), static_cast<SEDecimalFormat&>(out));
    out.m_Name = in.Name();
    if (in.Unit().present()) {
      out.m_RequestedUnit = in.Unit().get();
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEDataRequest& in, CDM::DataRequestData& out)
  {
    io::Property::UnMarshall(static_cast<SEDecimalFormat const&>(in), static_cast<CDM::DecimalFormatData&>(out));
    out.Name(in.m_Name);
    if (in.HasUnit()) {
      out.Unit(in.m_Unit->GetString());
    } else if (in.HasRequestedUnit()) {

      out.Unit(in.m_RequestedUnit);
    }
  }
  //-----------------------------------------------------------------------------
  //class SEPatientDataRequest
  void Scenario::Marshall(const CDM::PatientDataRequestData& in, SEPatientDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEPatientDataRequest& in, CDM::PatientDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SEPhysiologyDataRequest
  void Scenario::Marshall(const CDM::PhysiologyDataRequestData& in, SEPhysiologyDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEPhysiologyDataRequest& in, CDM::PhysiologyDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SEEnvironmentDataRequest
  void Scenario::Marshall(const CDM::EnvironmentDataRequestData& in, SEEnvironmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEEnvironmentDataRequest& in, CDM::EnvironmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SEEquipmentDataRequest
  void Scenario::Marshall(const CDM::EquipmentDataRequestData& in, SEEquipmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
    out.SetType(in.Type());
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEEquipmentDataRequest& in, CDM::EquipmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
  }
  //-----------------------------------------------------------------------------
  //class SECompartmentDataRequest
  void Scenario::Marshall(const CDM::CompartmentDataRequestData& in, SECompartmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
    out.SetCompartment(in.Compartment());
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SECompartmentDataRequest& in, CDM::CompartmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
    out.Compartment(in.m_Compartment);
  }
  //-----------------------------------------------------------------------------
  //class SECompartmentSubstanceDataRequest
  void Scenario::Marshall(const CDM::CompartmentSubstanceDataRequestData& in, SESubstanceManager const& substances, SECompartmentSubstanceDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
    if (in.Substance().present()) {
      out.SetSubstance(substances.GetSubstance(in.Substance().get()));
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SECompartmentSubstanceDataRequest& in, CDM::CompartmentSubstanceDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
    if (in.HasSubstance()) {
      out.Substance(in.m_Substance->GetName());
    }
  }
  //-----------------------------------------------------------------------------
  //class SEGasCompartmentDataRequest
  void Scenario::Marshall(const CDM::GasCompartmentDataRequestData& in, SESubstanceManager const& substances, SEGasCompartmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::CompartmentSubstanceDataRequestData const&>(in), substances, static_cast<SECompartmentSubstanceDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEGasCompartmentDataRequest& in, CDM::GasCompartmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SECompartmentSubstanceDataRequest const&>(in), static_cast<CDM::CompartmentSubstanceDataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SELiquidCompartmentDataRequest0
  void Scenario::Marshall(const CDM::LiquidCompartmentDataRequestData& in, SESubstanceManager const& substances, SELiquidCompartmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::CompartmentSubstanceDataRequestData const&>(in), substances, static_cast<SECompartmentSubstanceDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SELiquidCompartmentDataRequest& in, CDM::LiquidCompartmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SECompartmentSubstanceDataRequest const&>(in), static_cast<CDM::CompartmentSubstanceDataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SEThermalCompartmentDataRequest
  void Scenario::Marshall(const CDM::ThermalCompartmentDataRequestData& in, SEThermalCompartmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::CompartmentDataRequestData const&>(in), static_cast<SECompartmentDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEThermalCompartmentDataRequest& in, CDM::ThermalCompartmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SECompartmentDataRequest const&>(in), static_cast<CDM::CompartmentDataRequestData&>(out));
  }
  //-----------------------------------------------------------------------------
  //class SETissueCompartmentDataRequest
  void Scenario::Marshall(const CDM::TissueCompartmentDataRequestData& in, SETissueCompartmentDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::CompartmentDataRequestData const&>(in), static_cast<SECompartmentDataRequest&>(out));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SETissueCompartmentDataRequest& in, CDM::TissueCompartmentDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SECompartmentDataRequest const&>(in), static_cast<CDM::CompartmentDataRequestData&>(out));
  }
  //class SESubstanceDataRequest
  void Scenario::Marshall(const CDM::SubstanceDataRequestData& in, SESubstanceManager const& substances, SESubstanceDataRequest& out)
  {
    io::Scenario::Marshall(static_cast<CDM::DataRequestData const&>(in), static_cast<SEDataRequest&>(out));
    if (in.Compartment().present()) {
      out.SetCompartment(in.Compartment().get());
    }
    out.SetSubstance(substances.GetSubstance(in.Substance()));
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SESubstanceDataRequest& in, CDM::SubstanceDataRequestData& out)
  {
    io::Scenario::UnMarshall(static_cast<SEDataRequest const&>(in), static_cast<CDM::DataRequestData&>(out));
    if (in.HasCompartment()) {
      out.Compartment(in.m_Compartment);
    }
    if (in.HasSubstance()) {
      out.Substance(in.m_Substance->GetName());
    }
  }
  //-----------------------------------------------------------------------------
  //class SEScenario
  void Scenario::Marshall(const CDM::ScenarioData& in, SEScenario& out)
  {
    out.Clear();
    if (in.Name().present()) {
      out.m_Name = in.Name().get();
    }
    if (in.Description().present()) {
      out.m_Description = in.Description().get();
    }
    if (in.EngineStateFile().present()) {
      out.SetEngineStateFile(in.EngineStateFile().get());
    } else if (in.InitialParameters().present()) {
      Marshall(in.InitialParameters(), out.GetInitialParameters());
    } else {
      throw CommonDataModelException("No State or Initial Parameters provided");
    }
    if (in.AutoSerialization().present()) {
      Marshall(in.AutoSerialization(), out.GetAutoSerialization());
    }
    if (in.DataRequests().present()) {
      out.m_DataRequestMgr.Load(in.DataRequests().get(), out.m_SubMgr);
    }
    for (auto& action : in.Action()) {
      auto new_action = PatientActions::factory(action, out.m_SubMgr);
      if (new_action != nullptr) {
        out.m_Actions.push_back(new_action.release());
      }
    }
    if (!out.IsValid()) {
      throw CommonDataModelException("Unable Marshall SEScenario from ScenarioData");
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEScenario& in, CDM::ScenarioData& out)
  {
    out.Name(in.m_Name);
    out.Description(in.m_Description);
    if (in.HasEngineStateFile()) {
      out.EngineStateFile(in.m_EngineStateFile);
    } else if (in.HasInitialParameters()) {
      out.InitialParameters(std::make_unique<CDM::ScenarioInitialParametersData>());
      UnMarshall(*in.m_InitialParameters, out.InitialParameters());
    }
    if (in.HasAutoSerialization()) {
      out.AutoSerialization(std::make_unique<CDM::ScenarioAutoSerializationData>());
      UnMarshall(*in.m_AutoSerialization, out.AutoSerialization());
    }
    out.DataRequests(std::unique_ptr<CDM::DataRequestsData>(in.m_DataRequestMgr.Unload()));
    for (auto* action : in.m_Actions) {
      CDM::ActionData data;
      Scenario::UnMarshall(*action, data);
      out.Action().push_back(data);
    }
  }
  //-----------------------------------------------------------------------------
  //class SEScenarioInitialParameters
  void Scenario::Marshall(const CDM::ScenarioInitialParametersData& in, SEScenarioInitialParameters& out)
  {
    out.Clear();

    if (in.Configuration().present()) {
      out.GetConfiguration().Load(in.Configuration().get());
    }
    if (in.PatientFile().present()) {
      out.m_PatientFile = in.PatientFile().get();
    } else if (in.Patient().present()) {
      out.GetPatient().Load(in.Patient().get());
    } else {
      throw CommonDataModelException("No patient provided");
    }

    for (unsigned int i = 0; i < in.Condition().size(); i++) {
      auto condition = PatientConditions::factory(in.Condition()[i], out.m_SubMgr);
      if (condition != nullptr) {
        out.m_Conditions.push_back(condition.release());
      }
    }

    if (!out.IsValid()) {
      throw CommonDataModelException("Unable Marshall SEScenarioInitialParamaters from ScenarioInitialParamatersData");
    }
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEScenarioInitialParameters& in, CDM::ScenarioInitialParametersData& out)
  {
    if (in.HasPatientFile()) {
      out.PatientFile(in.m_PatientFile);
    } else if (in.HasPatient()) {
      out.Patient(std::unique_ptr<CDM::PatientData>(in.m_Patient->Unload()));
    }
    for (SECondition* condition : in.m_Conditions) {
      CDM::ConditionData data;
      Scenario::UnMarshall(*condition, data);
      out.Condition().push_back(data);
    }
    if (in.HasConfiguration()) {
      out.Configuration(std::unique_ptr<CDM::PhysiologyEngineConfigurationData>(in.m_Configuration->Unload()));
    }
  }
  //-----------------------------------------------------------------------------
  //class SEScenarioAutoSerialization
  void Scenario::Marshall(const CDM::ScenarioAutoSerializationData& in, SEScenarioAutoSerialization& out)
  {
    out.Clear();
    io::Property::Marshall(in.Period(), out.GetPeriod());
    out.SetPeriodTimeStamps(in.PeriodTimeStamps());
    out.SetAfterActions(in.AfterActions());
    out.SetReloadState(in.ReloadState());
    out.SetDirectory(in.Directory());
    out.SetFileName(in.FileName());
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEScenarioAutoSerialization& in, CDM::ScenarioAutoSerializationData& out)
  {
    if (in.HasPeriod()) {
      io::Property::UnMarshall(*in.m_Period, out.Period());
    }
    if (in.HasPeriodTimeStamps()) {
      out.PeriodTimeStamps(in.m_PeriodTimeStamps);
    }
    if (in.HasAfterActions()) {
      out.AfterActions(in.m_AfterActions);
    }
    if (in.HasReloadState()) {
      out.ReloadState(in.m_ReloadState);
    }
    if (in.HasDirectory()) {
      out.Directory(in.m_Directory);
    }
    if (in.HasFileName()) {
      out.FileName(in.m_FileName);
    }
  }
  //-----------------------------------------------------------------------------
  //class SEAdvanceTime
  void Scenario::Marshall(const CDM::AdvanceTimeData& in, SEAdvanceTime& out)
  {
    Marshall(static_cast<const CDM::ActionData&>(in), static_cast<SEAction&>(out));
    io::Property::Marshall(in.Time(), out.GetTime());
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SEAdvanceTime& in, CDM::AdvanceTimeData& out)
  {
    UnMarshall(static_cast<const SEAction&>(in), static_cast<CDM::ActionData&>(out));
    if (in.HasTime()) {
      io::Property::UnMarshall(*in.m_Time, out.Time());
    }
  }
  //-----------------------------------------------------------------------------
  //class SESerializeState
  void Scenario::Marshall(const CDM::SerializeStateData& in, SESerializeState& out)
  {
    Marshall(static_cast<const CDM::ActionData&>(in), static_cast<SEAction&>(out));
    out.SetType(in.Type());
    out.SetFilename(in.Filename());
  }
  //-----------------------------------------------------------------------------
  void Scenario::UnMarshall(const SESerializeState& in, CDM::SerializeStateData& out)
  {
    UnMarshall(static_cast<const SEAction&>(in), static_cast<CDM::ActionData&>(out));
    if (in.HasFilename()) {
      out.Filename(in.m_Filename);
    }
    if (in.HasType()) {
      out.Type(in.m_Type);
    }
  }
  //-----------------------------------------------------------------------------
}
}
