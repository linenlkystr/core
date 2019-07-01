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

#include <biogears/schema/cdm/Anesthesia.hxx>

namespace biogears {
class SEAnesthesiaMachine;
class SEAnesthesiaMachineChamber;
class SEAnesthesiaMachineOxygenBottle;

#define CDM_ANESTHESIA_ACTIONS_UNMARSHAL_HELPER(xsd, func)                           \
  if (m_##func) {                                                                    \
    xsd.func(std::make_unique<std::remove_reference<decltype(xsd.func())>::type>()); \
    io::Property::UnMarshall(*m_##func, xsd.func());                       \
  }
namespace io {
  class BIOGEARS_PRIVATE_API Anesthesia {
  public:
    //template <typename SE, typename XSD>  option
    template <typename SE, typename XSD>
    static void Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out);
    template <typename SE, typename XSD>
    static void UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out);
    //class SEAnesthesiaMachine
    static void Marshall(const CDM::AnesthesiaMachineData& in, SEAnesthesiaMachine& out);
    static void UnMarshall(const SEAnesthesiaMachine& in, CDM::AnesthesiaMachineData & out);
    //class SEAnesthesiaMachineChamber
    static void Marshall(const CDM::AnesthesiaMachineChamberData& in, SEAnesthesiaMachineChamber& out);
    static void UnMarshall(const SEAnesthesiaMachineChamber& in, CDM::AnesthesiaMachineChamberData& out);
    //class SEAnesthesiaMachineOxygenBottle
    static void Marshall(const CDM::AnesthesiaMachineOxygenBottleData& in, SEAnesthesiaMachineOxygenBottle& out);
    static void UnMarshall(const SEAnesthesiaMachineOxygenBottle& in, CDM::AnesthesiaMachineOxygenBottleData& out);
  };
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void Anesthesia::Marshall(xsd::cxx::tree::optional<XSD> const& option_in, SE& out)
  {
    if (!option_in.present()) {
      out.Clear();
    } else {
      Marshall(option_in.get(), out);
    }
  }
  //----------------------------------------------------------------------------------
  template <typename SE, typename XSD>
  void Anesthesia::UnMarshall(const SE& in, xsd::cxx::tree::optional<XSD>& option_out)
  {
    auto item = std::make_unique<XSD>();
    UnMarshall(in, *item);
    option_out.set(*item);
  }
} // Namespace IO
} //Namespace Biogears