#include "Common.h"
#include "GainChart.h"

//------------------------------------------------------------------------------

GainChart::GainChart ()
  : m_filter (0)
  , m_maxDb (0)
{
}

const String GainChart::getName () const
{
  return "Gain (dB)";
}

int GainChart::yToScreen (float y)
{
  AffineTransform t = calcTransform();
  Point<float> p (0, y);
  return int(p.transformedBy (t).getY());
}

void GainChart::paintContents (Graphics& g)
{
  AffineTransform t = calcTransform();

  g.setColour (Colours::blue);
  g.strokePath (m_path, 1, t);

  g.setColour (Colours::black);
  drawDbLine (g, 0, false);

  g.setColour (m_cAxisMinor);
  drawDbLine (g, -3, false);

  int skip = 6;
  if (getHeight() < 240)
    skip = 12;

  g.setColour (m_cAxis);

  for (int i = -skip; true; i -= skip)
    if (!drawDbLine (g, i))
      break;

  for (int i = skip; true; i += skip)
    if (!drawDbLine (g, i))
      break;
}

void GainChart::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  update ();
}

void GainChart::onFilterParameters ()
{
  update ();
}

/*
 * compute the path.
 * the x coordinates will range from 0..1
 * the y coordinates will be in gain dB
 *
 */
void GainChart::update ()
{
  m_path.clear();

  if (m_filter)
  {
    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    for (int xi = 0; xi < r.getWidth(); ++xi )
    {
      float x = xi / float(r.getWidth()-1);
      Dsp::complex_t c = m_filter->response (x/2);
      float y = std::abs(c);
      if (y < 1e-5)
          y = 1e-5;
      y = 20 * log10 (y);

      if (xi == 0)
        m_path.startNewSubPath (x, y);
      else
        m_path.lineTo (x, y);
    }

    m_path.startNewSubPath (0, 0);
  }

  m_maxDb = floor(m_path.getBounds().getBottom()+0.5);

  repaint();
}

bool GainChart::drawDbLine (Graphics& g, int db, bool drawLabel)
{
  bool onScreen = true;

  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds;
  const int y = yToScreen (db);

  if (y >= r.getY() && y < r.getBottom())
  {
    g.fillRect (r.getX(), y, r.getWidth(), 1);

    if (drawLabel)
    {
      if (db >= 0)
        drawText (g, Point<int> (r.getX()+6, y-2), String(db));
      else
        drawText (g, Point<int> (r.getX()+6, y+2), String(db), Justification::topLeft);
    }
  }
  else
  {
    onScreen = false;
  }

  return onScreen;
}

AffineTransform GainChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  float maxDb = jmax (m_maxDb, float(kMaxDb));

  AffineTransform t;

  // scale x from 0..1 to 0..getWidth(), and flip vertical
  t = AffineTransform::scale (r.getWidth(), -1);

  // move y down so maxDb is at the top
  t = t.translated (0, maxDb);

  // scale y from gain to 0..1 bounds in r
  t = t.scaled (1, 1./(maxDb - kMinDb));

  // scale y from 0..1 to getHeight()
  t = t.scaled (1, r.getHeight());

  // translate
  t = t.translated (r.getX(), r.getY());

  return t;
}
