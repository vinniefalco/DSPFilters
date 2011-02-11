#include "DspFilters/Common.h"
#include "DspFilters/RBJBiquad.h"

namespace Dsp {

namespace detail {

RBJDesignTypeI::RBJDesignTypeI ()
{
  addBuiltinParamInfo (idFrequency);
  addBuiltinParamInfo (idQ);
}

RBJDesignTypeII::RBJDesignTypeII ()
{
  addBuiltinParamInfo (idFrequency);
  addBuiltinParamInfo (idBandwidth);
}

RBJDesignTypeIII::RBJDesignTypeIII ()
{
  addBuiltinParamInfo (idFrequency);
  addBuiltinParamInfo (idGain);
  addBuiltinParamInfo (idSlope);
}

}

//------------------------------------------------------------------------------

const std::string RBJLowPassDesign::getName () const
{
  return "RBJ Low Pass";
}

void RBJLowPassDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2]);
}

void RBJLowPassDesign::setup (double sampleRate,
                              double cutoffFrequency,
                              double q)
{
  double w0 = 2 * doublePi * cutoffFrequency / sampleRate;
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

void RBJHighPassDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2]);
}

void RBJHighPassDesign::setup (double sampleRate,
                               double cutoffFrequency,
                               double q)
{
  double w0 = 2 * doublePi * cutoffFrequency / sampleRate;
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

void RBJBandPass1Design::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2]);
}

void RBJBandPass1Design::setup (double sampleRate,
                                double centerFrequency, double bandWidth)
{
  double w0 = 2 * doublePi * centerFrequency / sampleRate;
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

void RBJBandPass2Design::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2]);
}

void RBJBandPass2Design::setup (double sampleRate,
                                double centerFrequency,
                                double bandWidth)
{
  double w0 = 2 * doublePi * centerFrequency / sampleRate;
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

void RBJBandStopDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2]);
}

void RBJBandStopDesign::setup (double sampleRate,
                               double centerFrequency,
                               double bandWidth)
{
  double w0 = 2 * doublePi * centerFrequency / sampleRate;
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

void RBJLowShelfDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2], params[3]);
}

void RBJLowShelfDesign::setup (double sampleRate,
                               double cutoffFrequency,
                               double gainDb,
                               double shelfSlope)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * cutoffFrequency / sampleRate;
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

void RBJHighShelfDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2], params[3]);
}

void RBJHighShelfDesign::setup (double sampleRate,
                                double cutoffFrequency,
                                double gainDb,
                                double shelfSlope)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * cutoffFrequency / sampleRate;
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

void RBJBandShelfDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[2], params[3]);
}

void RBJBandShelfDesign::setup (double sampleRate,
                                double centerFrequency,
                                double gainDb,
                                double bandWidth)
{
  double A  = pow (10, gainDb/40);
  double w0 = 2 * doublePi * centerFrequency / sampleRate;
  double cs = cos(w0);
  double sn = sin(w0);
  double AL = sn * sinh( doubleLn2/2 * bandWidth * w0/sn );
  assert (!isnan (AL));
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

void RBJAllPassDesign::setParameters (const Parameters& params)
{
  setup (params[0], params[1], params[3]);
}

void RBJAllPassDesign::setup (double sampleRate,
                              double phaseFrequency,
                              double q)
{
  double w0 = 2 * doublePi * phaseFrequency / sampleRate;
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

}
