#ifndef NEWWAVE_GSL_ENGINE_HH
#define NEWWAVE_GSL_ENGINE_HH

#include <vector>

#include "NewWave/WaveletEngine.hh"
#include "NewWave/PixelDefinition.hh"

namespace NewWave{
  
  using std::vector;
  
  class GSLEngine : public WaveletEngine{

  public:
    
    struct wavelet;
    struct wavelet_type;
    struct wavelet_workspace;
    
    GSLEngine(wavelet_type *type, size_t degree,
              const PixelDefinition &pixelDefn);
    
    ~GSLEngine();
    
    WaveletCoefficients transform(const PixelArray &pixels)const;
    
    PixelArray inverseTransform(const WaveletCoefficients &coefficients)const;

    
  private:
    
    void init(size_t nSegments);

    void initYLevels();

    void initPhiLevels();

    /// The wavelet type (Daubechies, Harr...)
    wavelet_type *_waveletType;
    
    /// The wavelet degree (i.e. 4 for Daubechies 4)
    size_t _degree;
    
    /// gsl wavelet object
    wavelet *_wavelet;
    /// workspace for the wavelet transform
    wavelet_workspace *_workspace;
    
    size_t _nSegments;
    size_t _nSegments2;
    size_t _nLevels;
    
    vector<size_t> _yLevels;
    vector<size_t> _phiLevels;
    
  };

}


#endif
