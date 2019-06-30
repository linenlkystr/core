#include "PatientIoDelegate.h"

namespace biogears {
namespace io {
  //class SEActivePatientEvent
  void PatientIoDelegate::Marshall(const CDM::ActivePatientEventData& in, SEActivePatientEvent& out)
  {
  }
  //----------------------------------------------------------------------------------
  void PatientIoDelegate::UnMarshall(const SEActivePatientEvent& in, CDM::ActivePatientEventData& out)
  {
  }
  //----------------------------------------------------------------------------------
  //class SEPatient
  void PatientIoDelegate::Marshall(const CDM::PatientData& in, SEPatient& out)
  {
  }
  //----------------------------------------------------------------------------------
  void PatientIoDelegate::UnMarshall(const SEPatient& in, CDM::PatientData& out)
  {
  }
  //----------------------------------------------------------------------------------
}
}