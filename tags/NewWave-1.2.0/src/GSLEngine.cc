#include "NewWave/GSLEngine.hh"
#include "NewWave/Exceptions.hh"
#include "NewWave/Utils.hh"

#include <algorithm>

#include <iostream>

namespace NewWave {
  
  GSLEngine::GSLEngine(const gsl_wavelet_type *type, size_t degree,
                       const PixelDefinition &pixelDefn):
  _waveletType(type), _degree(degree),
  _wavelet(0), _workspace(0){
    
    init(pixelDefn);
    
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
      result.push_back(WaveletCoefficient(_yLevels.at(ii),
                                          _phiLevels.at(ii),
                                          ii,
                                          _yMinEdges.at(ii), _yMaxEdges.at(ii),
                                          _phiMinEdges.at(ii), _phiMaxEdges.at(ii),
                                          input.at(ii)));
    }
    
    return result;
  }
  
  PixelArray GSLEngine::inverseTransform(const WaveletCoefficients &coefficients)const{
    
    if(coefficients.size() != _nSegments2){
      throw PixelArrayMismatch();
    }
    
    vector<double> result(coefficients.size(), 0.);
    
    std::transform(coefficients.begin(), coefficients.end(), result.begin(),
                   [](const WaveletCoefficient &c){return c.value();});
    
    int status =
    gsl_wavelet2d_transform_inverse(_wavelet, &(result[0]),
                                    _nSegments, _nSegments, _nSegments, _workspace);
    
    if(status != GSL_SUCCESS)throw GSLException();

    
    return makeArray(result);
  }
  
  
  void GSLEngine::init(const PixelDefinition &pixelDefn){
    
    _nSegments = pixelDefn.nPixels();
    _nSegments2 = _nSegments*_nSegments;
    if(!isRadix2(_nSegments)) throw PixelDefinitionException("Length of pixel array is not radix 2");
    
    _wavelet = gsl_wavelet_alloc(_waveletType, _degree);
    _workspace = gsl_wavelet_workspace_alloc(_nSegments*_nSegments);
    
    initPhiLevels();
    initYLevels(pixelDefn);
    return;
  }
  
  void GSLEngine::initPhiLevels(){
    
    _phiLevels.clear();
    _phiMinEdges.clear();
    _phiMaxEdges.clear();
    
    for(size_t jj=0; jj != _nSegments; ++jj){
      _phiLevels.push_back(0);
      _phiMinEdges.push_back(0.);
      _phiMaxEdges.push_back(2.*M_PI);
      int nCoeffs = 1;
      int counter = 0;
      int level = 1;
      
      double phiMin = 0.;
      double phiIncr = 2.*M_PI;
      
      for(size_t ii=1; ii!= _nSegments; ++ii){
        _phiLevels.push_back(level);
        _phiMinEdges.push_back(phiMin);
        _phiMaxEdges.push_back(phiMin + phiIncr);
        phiMin += phiIncr;
        ++counter;
        if(counter == nCoeffs){
          counter  = 0;
          nCoeffs *= 2;
          ++level;
          phiMin = 0.;
          phiIncr *= 0.5;
        }
      }
    }
    return;
  }

  void GSLEngine::initYLevels(const PixelDefinition &pixelDefn){
    
    _yLevels.clear();
    _yMinEdges.clear();
    _yMaxEdges.clear();
    
    int level = 0;
    double yMin = pixelDefn.yMin();
    double yIncr = pixelDefn.yMax() - pixelDefn.yMin();
    _nLevels = 1;
    int nCoeffs = 1;
    int counter = 0;
    for(size_t ii=0; ii != _nSegments; ++ii){
      for(size_t jj=0; jj != _nSegments; ++jj){
        _yLevels.push_back(level);
        _yMinEdges.push_back(yMin);
        _yMaxEdges.push_back(yMin + yIncr);
      }
      
      yMin += yIncr;
      
      ++counter;
      if(counter == nCoeffs){
        counter = 0;
        yMin = pixelDefn.yMin();
        if(level != 0){
          ++level;
          nCoeffs *=2;
          ++_nLevels;
          yIncr *= 0.5;
        }else{
          level = 1;
          nCoeffs = 1;
          yIncr = pixelDefn.yMax() - pixelDefn.yMin();
        }
      }
    }
    return;
  }
  /*
  void GSLEngine::initPhiLevels(const PixelDefinition &pixelDefn){
    
    _phiLevels.clear();
    _phiMinEdges.clear();
    _phiMaxEdges.clear();
    
    int level = 0;
    double phiMin = 0.;
    double phiIncr = 2.*M_PI;
    _nLevels = 1;
    int nCoeffs = 1;
    int counter = 0;
    for(size_t ii=0; ii != _nSegments; ++ii){
      for(size_t jj=0; jj != _nSegments; ++jj){
        _phiLevels.push_back(level);
        _phiMinEdges.push_back(phiMin);
        _phiMaxEdges.push_back(phiMin + phiIncr);
      }
      
      phiMin += phiIncr;
      
      ++counter;
      if(counter == nCoeffs){
        counter = 0;
        phiMin = 0.;
        if(level != 0){
          ++level;
          nCoeffs *=2;
          ++_nLevels;
          phiIncr *= 0.5;
        }else{
          level = 1;
          nCoeffs = 1;
          phiIncr = 2.*M_PI;
        }
      }
    }
    return;
  }
  */
}

