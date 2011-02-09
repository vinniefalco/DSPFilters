#include "DspFilters/Common.h"
#include "DspFilters/RBJBiquad.h"

namespace Dsp {

namespace detail {

const ParameterInfo RBJDesignTypeI::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "Q";
    info.szName = "Q";
    info.szUnits= "";
    info.minValue = 0.01;
    info.maxValue = 16;
    info.defaultValue = 1;
    break;
  }

  return info;
}

const ParameterInfo RBJDesignTypeII::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "bw";
    info.szName = "Bandwidth";
    info.szUnits= "Octaves";
    info.minValue = 0.01;
    info.maxValue = 8;
    info.defaultValue = 1;
    break;
  }

  return info;
}

const ParameterInfo RBJDesignTypeIII::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "gain";
    info.szName = "Gain";
    info.szUnits= "dB";
    info.minValue = -12;
    info.maxValue = 12;
    info.defaultValue = 0;
    break;

  case 2:
    info.szLabel = "slope";
    info.szName = "Slope";
    info.szUnits= "";
    info.minValue = 0.01;
    info.maxValue = 4;
    info.defaultValue = 1;
    break;
  }

  return info;
}

}

//------------------------------------------------------------------------------

const std::string RBJLowPassDesign::getName () const
{
  return "RBJ Low Pass";
}

void RBJLowPassDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJLowPassDesign::setup (double normalizedCornerFrequency, double q)
{
  double w0 = 2 * doublePi * normalizedCornerFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / (2 * q);
  double b0 = (1 - cs) / 2;
  double b1 =  1 - cs;
  double b2 = (1 - cs) / 2;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJHighPassDesign::getName () const
{
  return "RBJ High Pass";
}

void RBJHighPassDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJHighPassDesign::setup (double normalizedCornerFrequency, double q)
{
  double w0 = 2 * doublePi * normalizedCornerFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / ( 2 * q );
  double b0 =  (1 + cs) / 2;
  double b1 = -(1 + cs);
  double b2 =  (1 + cs) / 2;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJBandPass1Design::getName () const
{
  return "RBJ Band Pass I";
}

void RBJBandPass1Design::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJBandPass1Design::setup (double normalizedCenterFrequency, double bandWidth)
{
  double w0 = 2 * doublePi * normalizedCenterFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / ( 2 * bandWidth );
  double b0 = bandWidth * AL;// sn / 2;
  double b1 =  0;
  double b2 = -bandWidth * AL;//-sn / 2;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJBandPass2Design::getName () const
{
  return "RBJ Band Pass II";
}

void RBJBandPass2Design::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJBandPass2Design::setup (double normalizedCenterFrequency, double bandWidth)
{
  double w0 = 2 * doublePi * normalizedCenterFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / ( 2 * bandWidth );
  double b0 =  AL;
  double b1 =  0;
  double b2 = -AL;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJBandStopDesign::getName () const
{
  return "RBJ Band Stop";
}

void RBJBandStopDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJBandStopDesign::setup (double normalizedCenterFrequency, double bandWidth)
{
  double w0 = 2 * doublePi * normalizedCenterFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / ( 2 * bandWidth );
  double b0 =  1;
  double b1 = -2 * cs;
  double b2 =  1;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJLowShelfDesign::getName () const
{
  return "RBJ Low Shelf";
}

void RBJLowShelfDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1], parameters[2]);
}

void RBJLowShelfDesign::setup (double normalizedCornerFrequency,
                               double gainDb,
                               double shelfSlope)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * normalizedCornerFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / 2 * ::std::sqrt ((A + 1/A) * (1/shelfSlope - 1) + 2);
  double sq = 2 * sqrt(A) * AL;
  double b0 =    A*( (A+1) - (A-1)*cs + sq );
  double b1 =  2*A*( (A-1) - (A+1)*cs );
  double b2 =    A*( (A+1) - (A-1)*cs - sq );
  double a0 =        (A+1) + (A-1)*cs + sq;
  double a1 =   -2*( (A-1) + (A+1)*cs );
  double a2 =        (A+1) + (A-1)*cs - sq;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJHighShelfDesign::getName () const
{
  return "RBJ High Shelf";
}

void RBJHighShelfDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1], parameters[2]);
}

void RBJHighShelfDesign::setup (double normalizedCornerFrequency,
                                double gainDb,
                                double shelfSlope)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * normalizedCornerFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / 2 * ::std::sqrt ((A + 1/A) * (1/shelfSlope - 1) + 2);
  double sq = 2 * sqrt(A) * AL;
  double b0 =    A*( (A+1) - (A-1)*cs + sq );
  double b1 = -2*A*( (A-1) - (A+1)*cs );
  double b2 =    A*( (A+1) - (A-1)*cs - sq );
  double a0 =        (A+1) + (A-1)*cs + sq;
  double a1 =    2*( (A-1) + (A+1)*cs );
  double a2 =        (A+1) + (A-1)*cs - sq;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJBandShelfDesign::getName () const
{
  return "RBJ Band Shelf";
}

void RBJBandShelfDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1], parameters[2]);
}

void RBJBandShelfDesign::setup (double normalizedCenterFrequency,
                                double gainDb,
                                double bandWidth)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * normalizedCenterFrequency;
  double cs = cos(w0);
  double sn = sin(w0);
  double AL = sn * sinh( doubleLn2/2 * bandWidth * w0/sn );
  double b0 =  1 + AL * A;
  double b1 = -2 * cs;
  double b2 =  1 - AL * A;
  double a0 =  1 + AL / A;
  double a1 = -2 * cs;
  double a2 =  1 - AL / A;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}

//------------------------------------------------------------------------------

const std::string RBJAllPassDesign::getName () const
{
  return "RBJ All Pass";
}

void RBJAllPassDesign::setParameters (const Parameters& parameters)
{
  setup (parameters[0], parameters[1]);
}

void RBJAllPassDesign::setup (double normalizedFrequency, double q)
{
  double w0 = 2 * doublePi * normalizedFrequency;
  double cs = cos (w0);
  double sn = sin (w0);
  double AL = sn / ( 2 * q );
  double b0 =  1 - AL;
  double b1 = -2 * cs;
  double b2 =  1 + AL;
  double a0 =  1 + AL;
  double a1 = -2 * cs;
  double a2 =  1 - AL;
  setCoefficients (a0, a1, a2, b0, b1, b2);
}







#if 0  

const Filter::ParameterInfo RBJBandPass1::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "bw";
    info.szName = "Bandwidth";
    info.szUnits= "Octaves";
    info.minValue = 0.01;
    info.maxValue = 8;
    info.defaultValue = 1;
    break;
  }

  return info;
}

void RBJBandPass1::setParameters (const Parameters& parameters)
{
  m_parameters = parameters;
  setupBandPass1 (m_parameters[0], m_parameters[1]);
}

//------------------------------------------------------------------------------

const std::string RBJBandStop::getName () const
{
  return "RBJ Band Stop";
}

int RBJBandStop::getNumParameters () const
{
  return 2;
}

const Filter::ParameterInfo RBJBandStop::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "bw";
    info.szName = "Bandwidth";
    info.szUnits= "Octaves";
    info.minValue = 0.01;
    info.maxValue = 8;
    info.defaultValue = 1;
    break;
  }

  return info;
}

void RBJBandStop::setParameters (const Parameters& parameters)
{
  m_parameters = parameters;
  setupBandStop (m_parameters[0], m_parameters[1]);
}

//------------------------------------------------------------------------------

const std::string RBJLowShelf::getName () const
{
  return "RBJ Low Shelf";
}

int RBJLowShelf::getNumParameters () const
{
  return 3;
}

const Filter::ParameterInfo RBJLowShelf::getParameterInfo (int index) const
{
  ParameterInfo info;
  switch (index)
  {
  case 0:
    info.szLabel = "Freq";
    info.szName = "Frequency";
    info.szUnits= "Hz";
    info.minValue = 10./44100;
    info.maxValue = 22040./44100;
    info.defaultValue = 0.25;
    break;
  
  case 1:
    info.szLabel = "gain";
    info.szName = "Gain";
    info.szUnits= "dB";
    info.minValue = -12;
    info.maxValue = 12;
    info.defaultValue = 0;
    break;

  case 2:
    info.szLabel = "slope";
    info.szName = "Slope";
    info.szUnits= "";
    info.minValue = 0.01;
    info.maxValue = 4;
    info.defaultValue = 1;
    break;
  }

  return info;
}

void RBJLowShelf::setParameters (const Parameters& parameters)
{
  m_parameters = parameters;
  setupLowShelf (m_parameters[0], m_parameters[1], m_parameters[2]);
}
#endif

}
