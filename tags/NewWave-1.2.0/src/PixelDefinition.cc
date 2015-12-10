#include "NewWave/PixelDefinition.hh"
#include "NewWave/Exceptions.hh"
#include "NewWave/Utils.hh"

#include <iostream>
#include <string>

namespace NewWave{
  
  PixelDefinition::PixelDefinition(size_t nBins, double yMax, bool allowPadding):
  _nBinsPhi(nBins), _nBinsY(nBins), _nBins(nBins),
  _phiMin(0.), _yMin(-yMax),
  _phiMax(TWOPI), _yMax(yMax),
  _nLevels(0), _gotLevels(false){
    
    if(isOdd(_nBins)) throw PixelDefinitionException("Number of bins is odd");
    
    if(!isRadix2(_nBins)){
      if(!allowPadding){
        throw PixelDefinitionException("nBins is not radix 2 and padding is not allowed.  Enable padding **with care** using the allowPadding argument");
      }else{
        std::cout<<"Warning: Padding the rapidity direction.  This may lead to pixels of smaller phi dimension than you expect.  Choose a value of nBins that is radix 2 if you want to avoid this."<<std::endl;
      }
    }
    
    _nBins = nearestRadix2(_nBins);
    
    _padPhi = 0;
    _rangePhi = TWOPI;
    _phi0 = 0.;
    _phiToBin = (double)_nBins / _rangePhi;
    
    _padY = (_nBins - nBins) / 2;
    _rangeY = 2. * yMax *((double)_nBins) / ((double)nBins);
    _yToBin = (double)_nBins / _rangeY;
    _y0 = -0.5 * _rangeY;
    
  }
  
  PixelDefinition::PixelDefinition(size_t nBinsPhi, double phiMin, double phiMax,
                                   size_t nBinsY, double yMin, double yMax,
                                   bool allowPhiPadding):
  _nBinsPhi(nBinsPhi), _nBinsY(nBinsY), _phiMin(phiMin), _yMin(yMin),
  _phiMax(phiMax), _yMax(yMax),
  _nLevels(0), _gotLevels(false){
    
    _phiMin = mod2Pi(_phiMin);
    _phiMax = mod2Pi(_phiMax);
    
    if(_phiMin > _phiMax) throw PixelDefinitionException("phi min is greater than phi max");
    if(_yMin > _yMax) throw PixelDefinitionException("rapidity min is greater than rapidity max");
      
    if(isOdd(_nBinsPhi)) throw PixelDefinitionException("nBinsPhi is odd.");
    if(isOdd(_nBinsY)) throw PixelDefinitionException("nBinsY is odd");
    
    _nBins = (_nBinsPhi > _nBinsY)? _nBinsPhi: _nBinsY;
    
    _nBins = nearestRadix2(_nBins);
    
    if(_nBins != _nBinsPhi){
      if(!allowPhiPadding){
        throw PixelDefinitionException("Phi pixel padding is not allowed.  Enable with allowPhiPadding=true and see documentation.");
      }else{
        std::cout<<"Warning: Padding phi direction for pixel definition.  This may well not be sensible"<<std::endl;
      }
      
    }
    
    _padPhi = (_nBins - _nBinsPhi) / 2;
    _padY   = (_nBins - nBinsY) / 2;
  
    _rangePhi = (phiMax - phiMin)*((double)_nBins)/ ((double)_nBinsPhi);
    _rangeY = (yMax - yMin)*((double)_nBins) / ((double)_nBinsY);
    
    _phiToBin = (double)_nBins / _rangePhi;
    _yToBin = (double)_nBins / _rangeY;
    
    _y0 = yMin - _rangeY * ((double)_padY) / ((double)_nBins);
    _phi0 = phiMin - _rangePhi * ((double)_padPhi) / ((double)_nBins);
    
  }
  
  PixelArray PixelDefinition::makeEmptyPixelArray()const{
    return vector<vector<double> >(_nBins, vector<double>(_nBins, 0.));
  }
  
  size_t PixelDefinition::phiPixelIndex(double phi)const{
    
    double phiRel = mod2Pi(phi) - _phi0;
    if(phiRel < 0.) throw PixelDefinitionException("bad phi value: " + std::to_string(phi));
    double dPhiBin = phiRel * _phiToBin;
    
    return (int)dPhiBin;
  }
  
  size_t PixelDefinition::yPixelIndex(double y)const{
    
    double yRel = y - _y0;
    if(yRel < 0.) throw PixelDefinitionException("rapidity is out of range: " + std::to_string(y));
    
    double dYBin = yRel * _yToBin;
    return (int) dYBin;
  }
  
  size_t PixelDefinition::nPixels()const{
    return _nBins;
  }
  
  double PixelDefinition::yMin()const{
    return _yMin;
  }
  
  double PixelDefinition::yMax()const{
    return _yMax;
  }
  
  bool PixelDefinition::covers(double rapidity, double phi)const{
    if(rapidity > yMax() || rapidity < yMin()) return false;
    
    phi = mod2Pi(phi);
    
    if(phi > _phiMax || phi < _phiMin) return false;
    
    return true;
  }
  
  size_t PixelDefinition::nLevels()const{
    
    if(_gotLevels) return _nLevels;
    
    _nLevels = 1;
    size_t nCoeffs = 1;
    size_t counter = 0;
    
    for(size_t ii=0; ii != _nBins; ++ii){
      ++counter;
      
      if(counter == nCoeffs){
        counter = 0;
        nCoeffs *=2;
        ++_nLevels;
      }
    }
    _gotLevels = true;
    return _nLevels;
  }
  
}

