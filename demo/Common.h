#ifndef DSPDEMO_COMMON_H
#define DSPDEMO_COMMON_H

#include <functional> 

#include "juce_amalgamated.h"

#include "DspFilters/Dsp.h"

#ifdef _MSC_VER
#  pragma warning (disable: 4100)
#endif

class FilterChart;
const int kSampleRate=44100;
const int kMaxOrder=50;

struct Spec : Dsp::Spec
{
	int proto;
	int kind;
};

inline Rectangle<int> tlbr (int top, int left, int bottom, int right)
{
  return Rectangle<int> (left, top, right-left, bottom-top);
}

#endif
