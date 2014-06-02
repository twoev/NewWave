#ifndef NEWWAVE_WAVELET_EVENT_HH
#define NEWWAVE_WAVELET_EVENT_HH

#include "NewWave/RasterisedEvent.hh"
#include "NewWave/WaveletEngine.hh"

namespace NewWave{
  
  /// A representation of the event in the wavelet domain
  
  class WaveletEvent{
    
  public:
    
    /// Constructor from a RasterisedEvent and a WaveletEngine
    WaveletEvent(const RasterisedEvent &event, const WaveletEngine &engine);
    
    /// Return the wavelet coefficients
    /**
     *  Returns the set of wavelet coefficients, including the effect of 
     *  any event processing in the wavelet domain, e.g. noise removal, 
     *  thresholding, level selection.
     *
     *  \return The wavelet coefficients
     */
    const WaveletCoefficients &coefficients()const;
    
    /// Return the rasterised event in rapidity-\f$\phi\f$ space
    /**
     *  Return a copy of the RasterisedEvent that includes the effect of
     *  any processing in the wavelet domain (e.g. noise thresholding).
     *  This is obtained by inverse transforming the set of coefficients.
     *
     *  \return The RasterisedEvent
     */
    const RasterisedEvent &rasterisedEvent()const;
    
    /// Return the original RasterisedEvent, unmodified
    /**
     *  Gives access to the event prior to any wavelet processing
     *
     *  \return The original event, unmodified by wavelet processing
     */
    const RasterisedEvent &originalEvent()const;
    
    /// De-noise the event using a simple flat threshold
    /**
     *  Event de-noising removes all coefficients whose magnitude is 
     *  below the given threshold.  Note that since different analysis
     *  systems use different units (GeV, MeV...) this threshold must be
     *  set consistently with that.  In other words, if you want a 
     *  threshold of 1GeV and your units are MeV, the argument is 1000.
     *
     *  \param noiseThreshold The threshold for coefficients
     */
    void denoise(double noiseThreshold);
    
  private:
    
    WaveletCoefficients &_coefficients()const;
    
    RasterisedEvent _originalEvent;
    mutable RasterisedEvent _rasterisedEvent;
    const WaveletEngine &_engine;
    
    mutable WaveletCoefficients _coeffs;
    
    mutable bool _doInvert;
    
  };
}

#endif
