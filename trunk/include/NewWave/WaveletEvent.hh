#ifndef NEWWAVE_WAVELET_EVENT_HH
#define NEWWAVE_WAVELET_EVENT_HH

#include "NewWave/RasterisedEvent.hh"
#include "NewWave/WaveletEngine.hh"
#include "NewWave/Utils.hh"

#include <cmath>

namespace NewWave{
  
  /// A representation of the event in the wavelet domain
  template<typename T>
  class WaveletEvent{
    
  public:
    
    WaveletEvent(const T &particles,
                 const PixelDefinition &pixelDefn,
                 const WaveletEngine &engine):
    _originalEvent(particles, pixelDefn),
    _rasterisedEvent(_originalEvent),
    _engine(engine),
    _doInvert(false){}
    
    /// Constructor from a RasterisedEvent and a WaveletEngine
    WaveletEvent(const RasterisedEvent<T> &event, const WaveletEngine &engine):
    _originalEvent(event),
    _rasterisedEvent(event),
    _engine(engine),
    _doInvert(false){}

    
    /// Return the wavelet coefficients
    /**
     *  Returns the set of wavelet coefficients, including the effect of 
     *  any event processing in the wavelet domain, e.g. noise removal, 
     *  thresholding, level selection.
     *
     *  \return The wavelet coefficients
     */
    const WaveletCoefficients &coefficients()const{return _coefficients();}
    
    /// Return the rasterised event in rapidity-\f$\phi\f$ space
    /**
     *  Return a copy of the RasterisedEvent that includes the effect of
     *  any processing in the wavelet domain (e.g. noise thresholding).
     *  This is obtained by inverse transforming the set of coefficients.
     *
     *  \return The RasterisedEvent
     */
    const RasterisedEvent<T> &rasterisedEvent()const{
      
      if(!_doInvert) return _rasterisedEvent;
      
      const PixelArray &pixels = _engine.inverseTransform(coefficients());
      _rasterisedEvent = RasterisedEvent<T>(pixels, _rasterisedEvent.pixelDefinition());
      _doInvert = false;
      return _rasterisedEvent;
    }
    
    /// Return the original RasterisedEvent, unmodified
    /**
     *  Gives access to the event prior to any wavelet processing
     *
     *  \return The original event, unmodified by wavelet processing
     */
    const RasterisedEvent<T> &originalEvent()const{
      return _originalEvent;
    }
    
    const T &particles()const{
      
      _ratio = rasterisedEvent().pixels() / _originalEvent.pixels() ;
      
      _modifiedParticles.clear();
      
      for(auto p: _originalEvent.inputParticles()){
        size_t ybin   = _originalEvent.pixelDefinition().yPixelIndex(p.momentum().rapidity());
        size_t phiBin = _originalEvent.pixelDefinition().phiPixelIndex(p.momentum().phi());
        double ratio = _ratio[ybin][phiBin];
        if(ratio > 0.){
          _modifiedParticles.push_back(p);
          _modifiedParticles.back().setMomentum(p.momentum()*ratio);
        }
      }
      
      return _modifiedParticles;
    }
    
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
    void denoise(double noiseThreshold){
      for(WaveletCoefficient &coeff: _coefficients()){
        if(fabs(coeff.value()) < noiseThreshold){
          coeff.setValue(0.);
          _doInvert = true;
        }
      }
    }

    
  private:
    
    WaveletCoefficients &_coefficients()const{
      if(_coeffs.size() != 0) return _coeffs;
      _coeffs = _engine.transform(_rasterisedEvent.pixels());
      return _coeffs;
    }

    
    RasterisedEvent<T> _originalEvent;
    mutable RasterisedEvent<T> _rasterisedEvent;
    const WaveletEngine &_engine;
    
    mutable WaveletCoefficients _coeffs;
    
    mutable bool _doInvert;
    
    mutable PixelArray _ratio;
    
    mutable T _modifiedParticles;
    
  };
}

#endif
