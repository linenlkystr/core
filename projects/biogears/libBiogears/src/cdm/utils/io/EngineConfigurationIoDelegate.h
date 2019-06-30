/**************************************************************************************
Copyright 2019 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
#include <memory>

#include "biogears/cdm/CommonDataModel.h"
#include <biogears/exports.h>

#include <biogears/schema/cdm/EngineConfiguration.hxx>

namespace biogears {
class SEPhysiologyEngineConfiguration;
class SEPhysiologyEngineStabilization;
class SEPhysiologyEngineConditionStabilization;
class SEPhysiologyEngineTimedStabilization;
class SEPhysiologyEngineTimedConditionStabilization;
class SEPhysiologyEngineDynamicStabilization;
class SEPhysiologyEngineDynamicConditionStabilization;
class SEPhysiologyEngineDynamicStabilizationCriteria;
class SEPhysiologyEngineDynamicStabilizationCriteriaProperty;

#define CDM_ENGINE_CONFIGURATION_UNMARSHAL_HELPER(xsd, func)                           \
  if (m_##func) {                                                                    \
    xsd.func(std::make_unique<std::remove_reference<decltype(xsd.func())>::type>()); \
    io::PropertyIoDelegate::UnMarshall(*m_##func, xsd.func());                       \
  }
namespace io {
  class BIOGEARS_PRIVATE_API EngineConfigurationIoDelegate {
  public:
    //template <typename SE, typename XSD>  option
    template <typename SE, typename XSD>
    static void Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out);
    template <typename SE, typename XSD>
    static void UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out);
    //class SEPhysiologyEngineConfiguration
    static void Marshall(const CDM::PhysiologyEngineConfigurationData& in, SEPhysiologyEngineConfiguration& out);
    static void UnMarshall(const SEPhysiologyEngineConfiguration& in, CDM::PhysiologyEngineConfigurationData& out);
    //class SEPhysiologyEngineStabilization
    static void Marshall(const CDM::PhysiologyEngineStabilizationData& in, SEPhysiologyEngineStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineStabilization& in, CDM::PhysiologyEngineStabilizationData& out);
    //class SEPhysiologyEngineConditionStabilization
    static void Marshall(const CDM::PhysiologyEngineConditionStabilizationData& in, SEPhysiologyEngineConditionStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineConditionStabilization& in, CDM::PhysiologyEngineConditionStabilizationData& out);
    //class SEPhysiologyEngineTimedStabilization
    static void Marshall(const CDM::PhysiologyEngineTimedStabilizationData& in, SEPhysiologyEngineTimedStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineTimedStabilization& in, CDM::PhysiologyEngineTimedStabilizationData& out);
    //class SEPhysiologyEngineTimedConditionStabilization
    static void Marshall(const CDM::PhysiologyEngineTimedConditionStabilizationData& in, SEPhysiologyEngineTimedConditionStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineTimedConditionStabilization& in, CDM::PhysiologyEngineTimedConditionStabilizationData& out);
    //class SEPhysiologyEngineDynamicStabilization
    static void Marshall(const CDM::PhysiologyEngineDynamicStabilizationData& in, SEPhysiologyEngineDynamicStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineDynamicStabilization& in, CDM::PhysiologyEngineDynamicStabilizationData& out);
    //class SEPhysiologyEngineDynamicConditionStabilization
    static void Marshall(const CDM::PhysiologyEngineDynamicConditionStabilizationData& in, SEPhysiologyEngineDynamicConditionStabilization& out);
    static void UnMarshall(const SEPhysiologyEngineDynamicConditionStabilization& in, CDM::PhysiologyEngineDynamicConditionStabilizationData& out);
    //class SEPhysiologyEngineDynamicStabilizationCriteria
    static void Marshall(const CDM::PhysiologyEngineDynamicStabilizationCriteriaData& in, SEPhysiologyEngineDynamicStabilizationCriteria& out);
    static void UnMarshall(const SEPhysiologyEngineDynamicStabilizationCriteria& in, CDM::PhysiologyEngineDynamicStabilizationCriteriaData& out);
    //class SEPhysiologyEngineDynamicStabilizationCriteriaProperty
    static void Marshall(const CDM::PhysiologyEngineDynamicStabilizationCriteriaPropertyData& in, SEPhysiologyEngineDynamicStabilizationCriteriaProperty& out);
    static void UnMarshall(const SEPhysiologyEngineDynamicStabilizationCriteriaProperty& in, CDM::PhysiologyEngineDynamicStabilizationCriteriaPropertyData& out);
  };
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void EngineConfigurationIoDelegate::Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out)
  {
    if (!option_in.present()) {
      out.Invalidate();
    } else {
      Marshall(option_in.get(), out);
    }
  }
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void EngineConfigurationIoDelegate::UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out)
  {
    auto item = std::make_unique<XSD>();
    UnMarshall(in, *item);
    option_out.set(*item);
  }
} // Namespace IO
} //Namespace Biogears
