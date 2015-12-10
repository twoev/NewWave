#ifndef NEWWAVE_WAVELET_BASE_EVENT_HH
#define NEWWAVE_WAVELET_BASE_EVENT_HH

#include "NewWave/WaveletCoefficient.fh"
#include "NewWave/FrequencyBand.fh"
#include "NewWave/PixelDefinition.hh"

namespace NewWave{
  
  class WaveletBaseEvent{
    
  public:
    
    virtual const WaveletCoefficients &coefficients() const = 0;
    
    virtual const FrequencyBands &frequencyBands()const = 0;

    virtual const FrequencyBand &frequencyBand(const WaveletCoefficient &coeff)const = 0;
    
    virtual const PixelDefinition &pixelDefn()const = 0;
    
    void setEvent(WaveletCoefficient &coeff)const;
    
  };
  
}

#endif
