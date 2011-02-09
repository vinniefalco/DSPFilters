#ifndef DSPDEMO_CHART_H
#define DSPDEMO_CHART_H

/*
 * Provides some common functionality for displayed charts.
 *
 */
class Chart : public Component
{
public:
  Chart ();
  ~Chart ();

  void paint (Graphics& g);

  virtual const String getName() const;
  virtual void paintContents (Graphics& g) = 0;

  static void drawText (Graphics &g,
                        const Point<int> ptOrigin,
                        const String text,
                        Justification just = Justification::bottomLeft);

private:
  void paintName (Graphics& g);

protected:
  Colour m_cBack;
  Colour m_cFrame;
  Colour m_cAxis;
  Colour m_cAxisMinor;
  Colour m_cText;
};

#endif

