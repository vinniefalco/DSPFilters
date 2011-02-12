#include "DspFilters/Common.h"
#include "DspFilters/ChebyshevI.h"

namespace Dsp {

namespace ChebyshevI {

namespace detail {

void AnalogLowPass::design (int numPoles,
                            double rippleDb,
                            LayoutBase& proto)
{
  proto.reset ();

  const double eps = std::sqrt (1. / std::exp (-rippleDb * 0.1 * doubleLn10) - 1);
  const double v0 = asinh (1 / eps) / numPoles;
  const double sinh_v0 = -sinh (v0);
  const double cosh_v0 = cosh (v0);

  const double n2 = 2 * numPoles;
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    const int k = 2 * i + 1 - numPoles;
    double a = sinh_v0 * cos (k * doublePi / n2);
    double b = cosh_v0 * sin (k * doublePi / n2);

    proto.addPoleZero (complex_t (a, b), infinity());
    proto.addPoleZero (complex_t (a, -b), infinity());
  }

  if (numPoles & 1)
  {
    proto.addPoleZero (complex_t (sinh_v0, 0), infinity());
    proto.setNormal (0, 1);
  }
  else
  {
    proto.setNormal (0, pow (10, -rippleDb/20.));
  }

}

void AnalogLowShelf::design (int numPoles,
                             double gainDb,
                             double rippleDb,
                             LayoutBase& proto)
{
  proto.reset ();

  const double n2 = numPoles * 2;
  const double g = pow (pow (10., gainDb/20), 1. / n2);
  const double gp = -1. / g;
  const double gz = -g;

  const int pairs = numPoles / 2;
  for (int i = 1; i <= pairs; ++i)
  {
    const double theta = doublePi * (0.5 - (2 * i - 1) / n2);
    proto.addPoleZeroConjugatePairs (std::polar (gp, theta), std::polar (gz, theta));
  }
  
  if (numPoles & 1)
    proto.addPoleZero (gp, gz);

  proto.setNormal (doublePi, 1);
}

//------------------------------------------------------------------------------

void LowPassBase::setup (int order,
                         double sampleRate,
                         double cutoffFrequency,
                         double rippleDb)
{
  AnalogLowPass::design (order, rippleDb, m_analogProto);

  LowPassTransform::transform (cutoffFrequency / sampleRate,
                               m_digitalProto,
                               m_analogProto);

  Cascade::setup (m_digitalProto);
}

void HighPassBase::setup (int order,
                          double sampleRate,
                          double cutoffFrequency,
                          double rippleDb)
{
  AnalogLowPass::design (order, rippleDb, m_analogProto);

  HighPassTransform::transform (cutoffFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandPassBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency,
                          double rippleDb)
{
  AnalogLowPass::design (order, rippleDb, m_analogProto);

  BandPassTransform::transform (centerFrequency / sampleRate,
                                widthFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandStopBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency,
                          double rippleDb)
{
  AnalogLowPass::design (order, rippleDb, m_analogProto);

  BandStopTransform::transform (centerFrequency / sampleRate,
                                widthFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void LowShelfBase::setup (int order,
                          double sampleRate,
                          double cutoffFrequency,
                          double gainDb,
                          double rippleDb)
{
  AnalogLowShelf::design (order, gainDb, rippleDb, m_analogProto);

  LowPassTransform::transform (cutoffFrequency / sampleRate,
                               m_digitalProto,
                               m_analogProto);

  Cascade::setup (m_digitalProto);
}

void HighShelfBase::setup (int order,
                           double sampleRate,
                           double cutoffFrequency,
                           double gainDb,
                           double rippleDb)
{
  AnalogLowShelf::design (order, gainDb, rippleDb, m_analogProto);

  HighPassTransform::transform (cutoffFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandShelfBase::setup (int order,
                           double sampleRate,
                           double centerFrequency,
                           double widthFrequency,
                           double gainDb,
                           double rippleDb)
{
  AnalogLowShelf::design (order, gainDb, rippleDb, m_analogProto);

  BandPassTransform::transform (centerFrequency / sampleRate,
                                widthFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  m_digitalProto.setNormal (((centerFrequency/sampleRate) < 0.25) ? doublePi : 0, 1);

  Cascade::setup (m_digitalProto);
}

}

}

}
