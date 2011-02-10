#ifndef DSPFILTERS_BIQUAD_H
#define DSPFILTERS_BIQUAD_H

#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

/*
 * Holds coefficients for a second order Infinite Impulse Response
 * digital filter. This is the building block for all IIR filters.
 *
 */

class Biquad
{
public:
  // Expresses the biquad as a pair of pole/zeros, with gain
  // values so that the coefficients can be reconstructed precisely.
  struct PoleZeroForm
  {
    PoleZeroForm ();

    explicit PoleZeroForm (const Biquad& s);

    complex_t pole[2];
    complex_t zero[2];
    double gain;
  };

public:
  Biquad ();

  explicit Biquad (const PoleZeroForm& pzf);

  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const;

  double getA0 () const { return m_a0; }
  double getA1 () const { return m_a1; }
  double getA2 () const { return m_a2; }
  double getB0 () const { return m_b0; }
  double getB1 () const { return m_b1; }
  double getB2 () const { return m_b2; }

public:
  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0)
      *dest++ = state.process (*dest, *this);
  }

  // Process a block of samples, interpolating from the old section's coefficients
  // to this section's coefficients, over numSamples. This implements smooth
  // parameter changes.
  template <class StateType, typename Sample>
  void process (int numSamples,
                Sample* dest,
                StateType& state,
                Biquad sectionPrev) const 
  {
    double t = 1. / numSamples;
    double da1 = (m_a1 - sectionPrev.m_a1) * t;
    double da2 = (m_a2 - sectionPrev.m_a2) * t;
    double db0 = (m_b0 - sectionPrev.m_b0) * t;
    double db1 = (m_b1 - sectionPrev.m_b1) * t;
    double db2 = (m_b2 - sectionPrev.m_b2) * t;

    while (--numSamples >= 0)
    {
      sectionPrev.m_a1 += da1;
      sectionPrev.m_a2 += da2;
      sectionPrev.m_b0 += db0;
      sectionPrev.m_b1 += db1;
      sectionPrev.m_b2 += db2;

      *dest++ = state.process (*dest, sectionPrev);
    }
  }

  // Process a block of samples, interpolating from the old section's pole/zeros
  // to this section's pole/zeros, over numSamples. The interpolation is done
  // in the z-plane using polar coordinates.
  template <class StateType, typename Sample>
  void process (int numSamples,
                Sample* dest,
                StateType& state,
                PoleZeroForm zPrev) const 
  {
    PoleZeros z (*this);
    double t = 1. / numSamples;
    complex_t dp0 = (z.pole[0] - zPrev.pole[0]) * t;
    complex_t dp1 = (z.pole[1] - zPrev.pole[1]) * t;
    complex_t dz0 = (z.zero[0] - zPrev.zero[0]) * t;
    complex_t dz1 = (z.zero[1] - zPrev.zero[1]) * t;
    double dg = (z.gain - zPrev.gain) * t;

    while (--numSamples >= 0)
    {
      zPrev.pole[0] += dp0;
      zPrev.pole[1] += dp1;
      zPrev.zero[0] += dz0;
      zPrev.zero[1] += dz1;
      zPrev.gain += dg;

      *dest++ = state.process (*dest, Biquad (zPrev));
    }
  }

public:
  // Set the coefficients. The overall gain is collected,
  // stored and factored out to reduce computation.
  void setCoefficients (double a0, double a1, double a2,
                        double b0, double b1, double b2);

  // Set the poles and zeros from two-element arrays.
  void setPoleZeros (complex_t const* poles, complex_t const* zeros);

  // Set the stage to reflect a single pole/zero.
  void setPoleZero (complex_t pole, complex_t zero);

  // Independently set the 'a' coefficients from a pair of poles
  void setPoles (complex_t pole1, complex_t pole2);

  // Independently set the 'b' coefficients from a pair of zeros
  void setZeros (complex_t zero1, complex_t zero2);

  // Scale the overall output by multiplying the coefficients
  // of the numerator polynomial 'b' by a constant
  void scale (double factor);

  // Set up the identity filter (i.e. pass input to output unaffected)
  void setupIdentity ();

private:
  //

  double m_a1;
  double m_a2;
  double m_b1;
  double m_b2;

  double m_a0;
  double m_b0;
};

//------------------------------------------------------------------------------

// Base for all designs that use a biquad
class BiquadDesign : public Biquad
{
public:
  const PoleZeros getPoleZeros ();
};

}

#endif
