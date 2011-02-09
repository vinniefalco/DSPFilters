#ifndef DSPDEMO_GRAPHCOMPONENT_H
#define DSPDEMO_GRAPHCOMPONENT_H

// General graph. Comes with a basic frame and some colors. Allows
// for a label and provides utility functions to draw some features.
class GraphComponent : public Component
{
public:
  GraphComponent ();
  ~GraphComponent ();

  void paint (Graphics& g);

  void paintBackground (Graphics& g);

protected:
  Colour m_cBack;
  Colour m_cFrame;
  Colour m_cAxis;
  Colour m_cAxisMinor;
  Colour m_cText;
};

#endif

