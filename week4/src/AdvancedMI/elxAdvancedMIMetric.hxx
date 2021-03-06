/*=========================================================================
 *
 *  Copyright UMC Utrecht and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __elxAdvancedMIMetric_HXX__
#define __elxAdvancedMIMetric_HXX__

#include "elxAdvancedMIMetric.h"
#include "itkTimeProbe.h"


namespace elastix
{

/**
 * ******************* Initialize ***********************
 */

template< class TElastix >
void
AdvancedMIMetric< TElastix >
::Initialize( void ) throw ( itk::ExceptionObject )
{
  itk::TimeProbe timer;
  timer.Start();
  this->Superclass1::Initialize();
  timer.Stop();
  elxout << "Initialization of AdvancedMI metric took: "
         << static_cast< long >( timer.GetMean() * 1000 ) << " ms." << std::endl;

} // end Initialize()

template< class TElastix >
void
AdvancedMIMetric< TElastix >
::BeforeEachResolution( void )
{
  /** Get the current resolution level. */
  unsigned int level
    = ( this->m_Registration->GetAsITKBaseType() )->GetCurrentLevel();

  /** Set limiters. */
  // typedef itk::HardLimiterFunction< RealType, FixedImageDimension >         FixedLimiterType;
  // typedef itk::ExponentialLimiterFunction< RealType, MovingImageDimension > MovingLimiterType;
  // this->SetFixedImageLimiter( FixedLimiterType::New() );
  // this->SetMovingImageLimiter( MovingLimiterType::New() );

  /** Get and set the number of histogram bins. */
  unsigned int numberOfHistogramBins = 32;
  this->GetConfiguration()->ReadParameter( numberOfHistogramBins,
    "NumberOfHistogramBins", this->GetComponentLabel(), level, 0 );
  this->SetNumberOfHistogramBins( numberOfHistogramBins );

  bool useJVHWEstimator = true;
  this->GetConfiguration()->ReadParameter( useJVHWEstimator,
    "UseJVHWEstimator", this->GetComponentLabel(), level, 0 );
  this->SetUseJVHWEstimator( useJVHWEstimator );
}



} // end namespace elastix

#endif // end #ifndef __elxAdvancedMIMetric_HXX__
