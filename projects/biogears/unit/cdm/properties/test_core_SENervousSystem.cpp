//-------------------------------------------------------------------------------------------
//- Copyright 2017 Applied Research Associates, Inc.
//- Licensed under the Apache License, Version 2.0 (the "License"); you may not use
//- this file except in compliance with the License. You may obtain a copy of the License
//- at:
//- http://www.apache.org/licenses/LICENSE-2.0
//- Unless required by applicable law or agreed to in writing, software distributed under
//- the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//- CONDITIONS OF ANY KIND, either express or implied. See the License for the
//-  specific language governing permissions and limitations under the License.
//-------------------------------------------------------------------------------------------
//!
//! @author David Lee
//! @date   2017 Aug 3rd
//!
//! Unit Test for Biogears-common Config
//!
#include <limits>
#include <thread>

#include <gtest/gtest.h>

#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/system/physiology/SENervousSystem.h>
#include <biogears/cdm/properties/SEScalarTypes.h>

#ifdef DISABLE_BIOGEARS_SENervousSystem_TEST
#define TEST_FIXTURE_NAME DISABLED_Core_SENervousSystem_Fixture
#else
#define TEST_FIXTURE_NAME Core_SENervousSystem_Fixture
#endif

using namespace biogears;
// The fixture for testing class Foo.
class TEST_FIXTURE_NAME : public ::testing::Test {
protected:
  // You can do set-up work for each test here.
  TEST_FIXTURE_NAME() = default;

  // You can do clean-up work that doesn't throw exceptions here.
  virtual ~TEST_FIXTURE_NAME() = default;

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  // Code here will be called immediately after the constructor (right
  // before each test).
  virtual void SetUp() override;

  // Code here will be called immediately after each test (right
  // before the destructor).
  virtual void TearDown() override;

  biogears::Logger* logger;
  biogears::SENervousSystem* es;
};

void TEST_FIXTURE_NAME::SetUp()
{
  logger = new biogears::Logger;
  es = new biogears::SENervousSystem(logger);
}

void TEST_FIXTURE_NAME::TearDown()
{
  delete es;
  delete logger;
}
TEST_F(TEST_FIXTURE_NAME, BaroreceptorHeartRateScale)
{
  EXPECT_FALSE( es->HasBaroreceptorHeartRateScale());
  es->GetBaroreceptorHeartRateScale().SetValue(1.0);
  EXPECT_TRUE( es->HasBaroreceptorHeartRateScale());
  EXPECT_EQ(1.0, es->GetBaroreceptorHeartRateScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasBaroreceptorHeartRateScale());
  auto dvalue = ces.GetBaroreceptorHeartRateScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, BaroreceptorHeartElastanceScale)
{
  EXPECT_FALSE( es->HasBaroreceptorHeartElastanceScale());
  es->GetBaroreceptorHeartElastanceScale().SetValue(1.0);
  EXPECT_TRUE( es->HasBaroreceptorHeartElastanceScale());
  EXPECT_EQ(1.0, es->GetBaroreceptorHeartElastanceScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasBaroreceptorHeartElastanceScale());
  auto dvalue = ces.GetBaroreceptorHeartElastanceScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, BaroreceptorResistanceScale)
{
  EXPECT_FALSE( es->HasBaroreceptorResistanceScale());
  es->GetBaroreceptorResistanceScale().SetValue(1.0);
  EXPECT_TRUE( es->HasBaroreceptorResistanceScale());
  EXPECT_EQ(1.0, es->GetBaroreceptorResistanceScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasBaroreceptorResistanceScale());
  auto dvalue = ces.GetBaroreceptorResistanceScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, BaroreceptorComplianceScale)
{
  EXPECT_FALSE( es->HasBaroreceptorComplianceScale());
  es->GetBaroreceptorComplianceScale().SetValue(1.0);
  EXPECT_TRUE( es->HasBaroreceptorComplianceScale());
  EXPECT_EQ(1.0, es->GetBaroreceptorComplianceScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasBaroreceptorComplianceScale());
  auto dvalue = ces.GetBaroreceptorComplianceScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, ChemoreceptorHeartRateScale)
{
  EXPECT_FALSE( es->HasChemoreceptorHeartRateScale());
  es->GetChemoreceptorHeartRateScale().SetValue(1.0);
  EXPECT_TRUE( es->HasChemoreceptorHeartRateScale());
  EXPECT_EQ(1.0, es->GetChemoreceptorHeartRateScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasChemoreceptorHeartRateScale());
  auto dvalue = ces.GetChemoreceptorHeartRateScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, ChemoreceptorHeartElastanceScale)
{
  EXPECT_FALSE( es->HasChemoreceptorHeartElastanceScale());
  es->GetChemoreceptorHeartElastanceScale().SetValue(1.0);
  EXPECT_TRUE( es->HasChemoreceptorHeartElastanceScale());
  EXPECT_EQ(1.0, es->GetChemoreceptorHeartElastanceScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasChemoreceptorHeartElastanceScale());
  auto dvalue = ces.GetChemoreceptorHeartElastanceScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, PainVisualAnalogueScale)
{
  EXPECT_FALSE( es->HasPainVisualAnalogueScale());
  es->GetPainVisualAnalogueScale().SetValue(1.0);
  EXPECT_TRUE( es->HasPainVisualAnalogueScale());
  EXPECT_EQ(1.0, es->GetPainVisualAnalogueScale().GetValue());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasPainVisualAnalogueScale());
  auto dvalue = ces.GetPainVisualAnalogueScale();
  EXPECT_NE(dvalue, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, LeftEyePupillaryResponse)
{
  EXPECT_FALSE( es->HasLeftEyePupillaryResponse());
  es->GetLeftEyePupillaryResponse();
  EXPECT_TRUE( es->HasLeftEyePupillaryResponse());
  es->RemoveLeftEyePupillaryResponse();
  EXPECT_FALSE( es->HasLeftEyePupillaryResponse());

  const biogears::SENervousSystem ces(logger);
  EXPECT_FALSE( ces.HasLeftEyePupillaryResponse());
  auto dvalue = ces.GetLeftEyePupillaryResponse(); // so this returns a NULL instead of a nan
  EXPECT_EQ(NULL, dvalue);
}
TEST_F(TEST_FIXTURE_NAME, RightEyePupillaryResponse)
{
  EXPECT_FALSE( es->HasRightEyePupillaryResponse());
  es->GetRightEyePupillaryResponse();
  EXPECT_TRUE( es->HasRightEyePupillaryResponse());
  es->RemoveRightEyePupillaryResponse();
  EXPECT_FALSE( es->HasRightEyePupillaryResponse());

  const biogears::SENervousSystem cds(logger);
  EXPECT_FALSE( cds.HasRightEyePupillaryResponse());
  auto dvalue = cds.GetRightEyePupillaryResponse(); // so this returns a NULL instead of a nan
  EXPECT_EQ(NULL, dvalue);
}
//LeftEyePupillaryResponse
//RightEyePupillaryResponse
