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

#include <ostream>

namespace biogears {
enum class SEGender {
  Invalid = -1,
  Male = 0,
  Female
};

enum class SEPatientEvent {
  Invalid = -1,
  Antidiuresis = 0,
  Asystole,
  Bradycardia,
  Bradypnea,
  BrainOxygenDeficit,
  CardiacArrest,
  CardiogenicShock,
  CriticalBrainOxygenDeficit,
  Dehydration,
  Diuresis,
  Fasciculation,
  Fatigue,
  FunctionalIncontinence,
  Hypercapnia,
  Hyperglycemia,
  MildHyperkalemia,
  SevereHyperkalemia,
  MildHypernatremia,
  SevereHypernatremia,
  Hyperthermia,
  Hypoglycemia,
  HypoglycemicShock,
  HypoglycemicComa,
  Hypothermia,
  MildHypokalemia,
  SevereHypokalemia,
  MildHyponatremia,
  SevereHyponatremia,
  Hypoxia,
  HypovolemicShock,
  IntracranialHypertension,
  IntracranialHypotension,
  IrreversibleState,
  Ketoacidosis,
  LacticAcidosis,
  LiverGlycogenDepleted,
  MaximumPulmonaryVentilationRate,
  MetabolicAcidosis,
  MetabolicAlkalosis,
  MildAcuteRespiratoryDistress,
  ModerateAcuteRespiratoryDistress,
  MuscleCatabolism,
  MuscleGlycogenDepleted,
  MyocardiumOxygenDeficit,
  Natriuresis,
  NutritionDepleted,
  PulselessRhythm,
  RenalHypoperfusion,
  RespiratoryAcidosis,
  RespiratoryAlkalosis,
  StartOfCardiacCycle,
  StartOfExhale,
  StartOfInhale,
  SevereAcuteRespiratoryDistress,
  SevereSepsis,
  Tachycardia,
  Tachypnea
};

std::ostream& operator<<(std::ostream& os, const SEPatientEvent& event)
{
  switch (event) {
  case SEPatientEvent::Antidiuresis:
    os << "Antidiuresis";
    break;
  case SEPatientEvent::Asystole:
    os << "Asystole";
    break;
  case SEPatientEvent::Bradycardia:
    os << "Bradycardia";
    break;
  case SEPatientEvent::Bradypnea:
    os << "Bradypnea";
    break;
  case SEPatientEvent::BrainOxygenDeficit:
    os << "BrainOxygenDeficit";
    break;
  case SEPatientEvent::CardiacArrest:
    os << "CardiacArrest";
    break;
  case SEPatientEvent::CardiogenicShock:
    os << "CardiogenicShock";
    break;
  case SEPatientEvent::CriticalBrainOxygenDeficit:
    os << "CriticalBrainOxygenDeficit";
    break;
  case SEPatientEvent::Dehydration:
    os << "Dehydration";
    break;
  case SEPatientEvent::Diuresis:
    os << "Diuresis";
    break;
  case SEPatientEvent::Fasciculation:
    os << "Fasciculation";
    break;
  case SEPatientEvent::Fatigue:
    os << "Fatigue";
    break;
  case SEPatientEvent::FunctionalIncontinence:
    os << "FunctionalIncontinence";
    break;
  case SEPatientEvent::Hypercapnia:
    os << "Hypercapnia";
    break;
  case SEPatientEvent::Hyperglycemia:
    os << "Hyperglycemia";
    break;
  case SEPatientEvent::MildHyperkalemia:
    os << "MildHyperkalemia";
    break;
  case SEPatientEvent::SevereHyperkalemia:
    os << "SevereHyperkalemia";
    break;
  case SEPatientEvent::MildHypernatremia:
    os << "MildHypernatremia";
    break;
  case SEPatientEvent::SevereHypernatremia:
    os << "SevereHypernatremia";
    break;
  case SEPatientEvent::Hyperthermia:
    os << "Hyperthermia";
    break;
  case SEPatientEvent::Hypoglycemia:
    os << "Hypoglycemia";
    break;
  case SEPatientEvent::HypoglycemicShock:
    os << "HypoglycemicShock";
    break;
  case SEPatientEvent::HypoglycemicComa:
    os << "HypoglycemicComa";
    break;
  case SEPatientEvent::Hypothermia:
    os << "Hypothermia";
    break;
  case SEPatientEvent::MildHypokalemia:
    os << "MildHypokalemia";
    break;
  case SEPatientEvent::SevereHypokalemia:
    os << "SevereHypokalemia";
    break;
  case SEPatientEvent::MildHyponatremia:
    os << "MildHyponatremia";
    break;
  case SEPatientEvent::SevereHyponatremia:
    os << "SevereHyponatremia";
    break;
  case SEPatientEvent::Hypoxia:
    os << "Hypoxia";
    break;
  case SEPatientEvent::HypovolemicShock:
    os << "HypovolemicShock";
    break;
  case SEPatientEvent::IntracranialHypertension:
    os << "IntracranialHypertension";
    break;
  case SEPatientEvent::IntracranialHypotension:
    os << "IntracranialHypotension";
    break;
  case SEPatientEvent::IrreversibleState:
    os << "IrreversibleState";
    break;
  case SEPatientEvent::Ketoacidosis:
    os << "Ketoacidosis";
    break;
  case SEPatientEvent::LacticAcidosis:
    os << "LacticAcidosis";
    break;
  case SEPatientEvent::LiverGlycogenDepleted:
    os << "LiverGlycogenDepleted";
    break;
  case SEPatientEvent::MaximumPulmonaryVentilationRate:
    os << "MaximumPulmonaryVentilationRate";
    break;
  case SEPatientEvent::MetabolicAcidosis:
    os << "MetabolicAcidosis";
    break;
  case SEPatientEvent::MetabolicAlkalosis:
    os << "MetabolicAlkalosis";
    break;
  case SEPatientEvent::MildAcuteRespiratoryDistress:
    os << "MildAcuteRespiratoryDistress";
    break;
  case SEPatientEvent::ModerateAcuteRespiratoryDistress:
    os << "ModerateAcuteRespiratoryDistress";
    break;
  case SEPatientEvent::MuscleCatabolism:
    os << "MuscleCatabolism";
    break;
  case SEPatientEvent::MuscleGlycogenDepleted:
    os << "MuscleGlycogenDepleted";
    break;
  case SEPatientEvent::MyocardiumOxygenDeficit:
    os << "MyocardiumOxygenDeficit";
    break;
  case SEPatientEvent::Natriuresis:
    os << "Natriuresis";
    break;
  case SEPatientEvent::NutritionDepleted:
    os << "NutritionDepleted";
    break;
  case SEPatientEvent::PulselessRhythm:
    os << "PulselessRhythm";
    break;
  case SEPatientEvent::RenalHypoperfusion:
    os << "RenalHypoperfusion";
    break;
  case SEPatientEvent::RespiratoryAcidosis:
    os << "RespiratoryAcidosis";
    break;
  case SEPatientEvent::RespiratoryAlkalosis:
    os << "RespiratoryAlkalosis";
    break;
  case SEPatientEvent::StartOfCardiacCycle:
    os << "StartOfCardiacCycle";
    break;
  case SEPatientEvent::StartOfExhale:
    os << "StartOfExhale";
    break;
  case SEPatientEvent::StartOfInhale:
    os << "StartOfInhale";
    break;
  case SEPatientEvent::SevereAcuteRespiratoryDistress:
    os << "SevereAcuteRespiratoryDistress";
    break;
  case SEPatientEvent::SevereSepsis:
    os << "SevereSepsis";
    break;
  case SEPatientEvent::Tachycardia:
    os << "Tachycardia";
    break;
  case SEPatientEvent::Tachypnea:
    os << "Tachypnea";
    break;

  default:
    os << "Invalid";
  }
  return os;
}
}
