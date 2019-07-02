#include "EnvironmentConditions.h"

#include "Scenario.h"

#include <biogears/cdm/scenario/SECondition.h>
#include <biogears/cdm/system/environment/conditions/SEInitialEnvironment.h>
#include <biogears/cdm/system/environment/conditions/SEEnvironmentCondition.h>

namespace biogears {
namespace io {
  //class SEEnvironmentCondition
  void EnvironmentConditions::Marshall(const CDM::EnvironmentConditionData& in, SEEnvironmentCondition& out)
  {
    io::Scenario::Marshall(static_cast<const CDM::ConditionData&>(in), static_cast<SECondition&>(out));
  }
  //----------------------------------------------------------------------------------
  void EnvironmentConditions::UnMarshall(const SEEnvironmentCondition& in, CDM::EnvironmentConditionData& out)
  {
    io::Scenario::UnMarshall(static_cast<const SECondition&>(in), static_cast<CDM::ConditionData&>(out));
  }
  //----------------------------------------------------------------------------------
  //class SEInitialEnvironment
  void EnvironmentConditions::Marshall(const CDM::InitialEnvironmentData& in, SEInitialEnvironment& out)
  {
    io::Scenario::Marshall(static_cast<const CDM::EnvironmentConditionData&>(in), static_cast<SEEnvironmentCondition&>(out));
    if (in.ConditionsFile().present())
      out.SetConditionsFile(in.ConditionsFile().get());
    if (in.Conditions().present())
      Marshall(in.Conditions(),out.GetConditions());
  }
  //----------------------------------------------------------------------------------
  void EnvironmentConditions::UnMarshall(const SEInitialEnvironment& in, CDM::InitialEnvironmentData& out)
  {
    io::Scenario::UnMarshall(static_cast<const SEEnvironmentCondition&>(in), static_cast<CDM::EnvironmentConditionData&>(out));
    if (in.HasConditions())
      UnMarshall(*in.m_Conditions, out.Conditions());
    else if (in.HasConditionsFile())
      out.ConditionsFile(in.m_ConditionsFile);
  }
  //----------------------------------------------------------------------------------
}
}