#include "DspFilters/Common.h"
#include "DspFilters/Butterworth.h"

namespace Dsp {

namespace Butterworth {

namespace detail {

void AnalogLowPass::design (int numPoles,
                            LayoutBase& proto)
{
  proto.reset ();

  const double n2 = 2 * numPoles;
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    complex_t c = std::polar (1., doublePi_2 + (2 * i + 1) * doublePi / n2);
    proto.addPoleZero (c, infinity());
    proto.addPoleZero (std::conj (c), infinity());
  }

  if (numPoles & 1)
    proto.addPoleZero (-1, infinity());

  proto.setNormal (0, 1);
}

void AnalogLowShelf::design (int numPoles,
                             double gainDb,
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
                         double cutoffFrequency)
{
  AnalogLowPass::design (order, m_analogProto);

  LowPassTransform::transform (cutoffFrequency / sampleRate,
                               m_digitalProto,
                               m_analogProto);

  Cascade::setup (m_digitalProto);
}

void HighPassBase::setup (int order,
                          double sampleRate,
                          double cutoffFrequency)
{
  AnalogLowPass::design (order, m_analogProto);

  HighPassTransform::transform (cutoffFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandPassBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  AnalogLowPass::design (order, m_analogProto);

  BandPassTransform::transform (centerFrequency / sampleRate,
                                widthFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandStopBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  AnalogLowPass::design (order, m_analogProto);

  BandStopTransform::transform (centerFrequency / sampleRate,
                                widthFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void LowShelfBase::setup (int order,
                         double sampleRate,
                         double cutoffFrequency,
                         double gainDb)
{
  AnalogLowShelf::design (order, gainDb, m_analogProto);

  LowPassTransform::transform (cutoffFrequency / sampleRate,
                               m_digitalProto,
                               m_analogProto);

  Cascade::setup (m_digitalProto);
}

void HighShelfBase::setup (int order,
                           double sampleRate,
                           double cutoffFrequency,
                           double gainDb)
{
  AnalogLowShelf::design (order, gainDb, m_analogProto);

  HighPassTransform::transform (cutoffFrequency / sampleRate,
                                m_digitalProto,
                                m_analogProto);

  Cascade::setup (m_digitalProto);
}

void BandShelfBase::setup (int order,
                           double sampleRate,
                           double centerFrequency,
                           double widthFrequency,
                           double gainDb)
{
  AnalogLowShelf::design (order, gainDb, m_analogProto);

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
