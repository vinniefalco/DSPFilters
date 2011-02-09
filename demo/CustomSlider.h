#ifndef DSPDEMO_CUSTOMSLIDER_H
#define DSPDEMO_CUSTOMSLIDER_H

#include "Common.h"

class CustomSlider : public Slider
{
public:
  CustomSlider (String name = String::empty)
    : Slider (name)
  {
  }

  void mouseDrag (const MouseEvent& e)
  {
    e.source.enableUnboundedMouseMovement (true, false);
    Slider::mouseDrag (e);
  }
};

#endif
