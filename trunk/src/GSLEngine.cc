#include "NewWave/GSLEngine.hh"
#include "NewWave/Exceptions.hh"
#include "NewWave/Utils.hh"

namespace NewWave {
  
  GSLEngine::GSLEngine(const gsl_wavelet_type *type, size_t degree,
                       const PixelDefinition &pixelDefn):
  _waveletType(type), _degree(degree),
  _wavelet(0), _workspace(0){
    
    init(pixelDefn.nPixels());
    
  }
  
  GSLEngine::~GSLEngine(){
    if(_wavelet != 0){
      delete _wavelet;
      _wavelet = 0;
    }
    
    if(_workspace != 0){
      delete _workspace;
      _workspace = 0;
    }
    
  }
  
  WaveletCoefficients GSLEngine::transform(const PixelArray &pixels)const{
    
    if(pixels.size() != _nSegments){
      throw PixelArrayMismatch();
    }
    
    vector<double> input = makeRowFromArray(pixels);
    
    int status =
    gsl_wavelet2d_transform_forward(_wavelet, &(input[0]),
                                    _nSegments, _nSegments, _nSegments,
                                    _workspace);
    
    if(status != GSL_SUCCESS)throw GSLException();
    
    WaveletCoefficients result;
    
    for(size_t ii=0; ii != input.size(); ++ii){
      result.push_back(WaveletCoefficient(_yLevels[ii],
                                          _phiLevels[ii],
                                          input[ii]));
    }
    
    return result;
  }
  
  PixelArray GSLEngine::inverseTransform(const WaveletCoefficients &coefficients)const{
    
    if(coefficients.size() != _nSegments2){
      throw PixelArrayMismatch();
    }
    
    vector<double> input(0., _nSegments2);
    
    for(size_t ii=0; ii != coefficients.size(); ++ii){
      
    }
    
    
    return PixelArray();
  }
  
  
  void GSLEngine::init(size_t nSegments){
    _nSegments = nSegments;
    _nSegments2 = nSegments*nSegments;
    if(!isRadix2(_nSegments)) throw PixelDefinitionException("Length of pixel array is not radix 2");
    
    _wavelet = gsl_wavelet_alloc(_waveletType, _degree);
    _workspace = gsl_wavelet_workspace_alloc(_nSegments*_nSegments);
    
    initPhiLevels();
    initYLevels();
    return;
  }
  
  void GSLEngine::initYLevels(){
    
    for(size_t jj=0; jj != _nSegments; ++jj){
      _yLevels.push_back(0);
      int nCoeffs = 1;
      int counter = 0;
      int level = 1;
      for(size_t ii=1; ii!= _nSegments; ++ii){
        _yLevels.push_back(level);
        ++counter;
        if(counter == nCoeffs){
          counter  = 0;
          nCoeffs *= 2;
          ++level;
        }
      }
    }
    return;
  }
  
  void GSLEngine::initPhiLevels(){
    
    int level = 0;
    _nLevels = 1;
    int nCoeffs = 1;
    int counter = 0;
    for(size_t ii=0; ii != _nSegments; ++ii){
      for(size_t jj=0; jj != _nSegments; ++jj){
        _phiLevels.push_back(level);
      }
      
      ++counter;
      if(counter == nCoeffs){
        counter = 0;
        if(level != 0){
          ++level;
          nCoeffs *=2;
          ++_nLevels;
        }else{
          level = 1;
          nCoeffs = 1;
        }
      }
    }
    return;
  }
  
}

