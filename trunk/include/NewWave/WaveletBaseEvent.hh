#ifndef NEWWAVE_WAVELET_BASE_EVENT_HH
#define NEWWAVE_WAVELET_BASE_EVENT_HH

#include "NewWave/WaveletCoefficient.fh"
#include "NewWave/FrequencyBand.fh"
#include "NewWave/PixelDefinition.hh"

#include <functional>

namespace NewWave{
  
  /**
   *  Just an abstract interface to WaveletEvent that we can use
   *  without knowing the template type of WaveletEvent<>
   */
  
  class WaveletBaseEvent{
    
  public:
    
    virtual const WaveletCoefficients &coefficients() const = 0;
    
    virtual const FrequencyBands &frequencyBands() const = 0;

    virtual const FrequencyBand &frequencyBand(const WaveletCoefficient &coeff) const = 0;
    
    virtual const PixelDefinition &pixelDefn() const = 0;
    
    virtual const PixelArray &pixels() const = 0;
    
    virtual const PixelArray &originalPixels() const = 0;
    
    virtual void setPileUpThreshold(double threshold) = 0;
    
    virtual void setScaleParticles(bool doScale) = 0;
    
    virtual void scale(const std::function<double (const WaveletCoefficient&)> &scaler) = 0;
    
    void setEvent(WaveletCoefficient &coeff) const;
    
    
    
  };
  
}

#endif
