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
#include <biogears/cdm/properties/SEDecimalFormat.h>

//Standard Includes
#include <iomanip>
#include <fstream>
//Project Includes

namespace biogears {
SEDecimalFormat::SEDecimalFormat(const SEDecimalFormat* dfault)
{
  Reset();
  if (dfault != nullptr)
    Set(*dfault);
}

SEDecimalFormat::~SEDecimalFormat()
{
  Reset();
}

void SEDecimalFormat::Reset()
{
  m_Precision = 6;
  m_Notation = DecimalNotation::Default;
}

void SEDecimalFormat::Set(const SEDecimalFormat& f)
{
  m_Precision = f.m_Precision;
  m_Notation = f.m_Notation;
}

void SEDecimalFormat::SetPrecision(std::streamsize p)
{
  m_Precision = p;
}
std::streamsize SEDecimalFormat::GetPrecision()
{
  return m_Precision;
}

void SEDecimalFormat::SetNotation(DecimalNotation n)
{
  m_Notation = n;
}
DecimalNotation SEDecimalFormat::GetNotation()
{
  return m_Notation;
}

void SEDecimalFormat::SetStream(std::ofstream& s)
{
  switch (m_Notation) {
  case DecimalNotation::Default:
    s 
    #ifndef ANDROID
      << std::defaultfloat 
    #endif
      << std::setprecision(m_Precision);
    break;
  case DecimalNotation::Fixed:
    s << std::fixed << std::setprecision(m_Precision);
    break;
  case DecimalNotation::Scientific:
    s << std::scientific << std::setprecision(m_Precision);
  }
}
}