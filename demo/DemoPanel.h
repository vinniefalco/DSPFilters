#ifndef DSPDEMO_DEMOPANEL_H
#define DSPDEMO_DEMOPANEL_H

#include "Common.h"
#include "ResizableLayout.h"

class DemoPanel :
	public Component,
  public MenuBarModel,
	public ButtonListener,
	public ComboBoxListener,
	public SliderListener,
  public ResizableLayout
{
public:
  DemoPanel();
  ~DemoPanel();

  const StringArray getMenuBarNames();
  const PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

  static const int kMaxOrder = 50;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoPanel);

  // Proto
  enum
  {
	  idButter=1,
	  idChebyI=2,
	  idChebyII=3,
	  idElliptic=4,
	  idBessel=5,
	  idLegendere=6
  };

  // Kind
  enum
  {
	  idLowPass=1,
	  idHighPass=2,
	  idBandPass=3,
	  idBandStop=4,
	  idLowShelf=5,
	  idHighShelf=6,
	  idPeakEq=7
  };

  // Knobs
  enum
  {
	  idOrd=0,
	  idFreq=1,
	  idWid=2,
	  idRip=3,
	  idAtt=4,
	  idGain=5,
	  idSlope=6,

	  knobCount
  };

  // Graphs
  enum
  {
	  idBrick=0,
	  idPhase=1,
	  idPoles=2,
	  idResponse=3,
	  idDelay=4,
	  idStep=5,

	  chartCount
  };

  struct Filters
  {
	  Dsp::ButterLowPass<kMaxOrder,1> butterLp;
	  Dsp::ButterHighPass<kMaxOrder,1> butterHp;
	  Dsp::ButterBandPass<kMaxOrder,1> butterBp;
	  Dsp::ButterBandStop<kMaxOrder,1> butterBs;
	  Dsp::ButterLowShelf<kMaxOrder,1> butterLs;
	  Dsp::ButterHighShelf<kMaxOrder,1> butterHs;
	  Dsp::ButterEq<kMaxOrder,1> butterEq;

	  Dsp::ChebyILowPass<kMaxOrder,1> chebyILp;
	  Dsp::ChebyIHighPass<kMaxOrder,1> chebyIHp;
	  Dsp::ChebyIBandPass<kMaxOrder,1> chebyIBp;
	  Dsp::ChebyIBandStop<kMaxOrder,1> chebyIBs;
	  Dsp::ChebyILowShelf<kMaxOrder,1> chebyILs;
	  Dsp::ChebyIHighShelf<kMaxOrder,1> chebyIHs;
	  Dsp::ChebyIEq<kMaxOrder,1> chebyIEq;

	  Dsp::ChebyIILowPass<kMaxOrder,1> chebyIILp;
	  Dsp::ChebyIIHighPass<kMaxOrder,1> chebyIIHp;
	  Dsp::ChebyIIBandPass<kMaxOrder,1> chebyIIBp;
	  Dsp::ChebyIIBandStop<kMaxOrder,1> chebyIIBs;
	  Dsp::ChebyIILowShelf<kMaxOrder,1> chebyIILs;
	  Dsp::ChebyIIHighShelf<kMaxOrder,1> chebyIIHs;
	  Dsp::ChebyIIEq<kMaxOrder,1> chebyIIEq;

	  Dsp::EllipticLowPass<kMaxOrder,1> ellipticLp;
	  Dsp::EllipticHighPass<kMaxOrder,1> ellipticHp;
	  Dsp::EllipticBandPass<kMaxOrder,1> ellipticBp;
	  Dsp::EllipticBandStop<kMaxOrder,1> ellipticBs;

	  Dsp::BesselLowPass<kMaxOrder,1> besselLp;
	  Dsp::BesselHighPass<kMaxOrder,1> besselHp;
	  Dsp::BesselBandPass<kMaxOrder,1> besselBp;
	  Dsp::BesselBandStop<kMaxOrder,1> besselBs;

	  Dsp::LegendereLowPass<kMaxOrder,1> legendereLp;
  };

private:
  void SpecDefaults( Spec *spec );
  void SpecToCtrls( void );
  Dsp::PoleFilterOld *SpecToFilter( const Spec &spec, Filters *filters );

private:
  void paint( Graphics &g );
  void buttonClicked( Button *ctrl );
  void comboBoxChanged( ComboBox *ctrl );
  void sliderValueChanged( Slider *ctrl );

private:
  ComboBox *	m_menuProto;
  ComboBox *	m_menuKind;
  Slider *		m_knob[knobCount];
  FilterChartOld *		m_chart[chartCount];

  Spec				m_spec;
  Filters				m_filters;
  Dsp::PoleFilterOld *	m_filter;
};

#endif

