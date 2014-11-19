#ifndef NEWWAVE_MOMENTUM_HH
#define NEWWAVE_MOMENTUM_HH

#include "NewWave/MomentumHelpers.hh"
#include <memory>

namespace NewWave{
  
  using std::shared_ptr;
  
  template<typename T>
  class IMomentum{
    
  public:
    /**
     *  Return the rapidity or, depending on implementation, 
     *  rapidity-like quantity (e.g. pseudo-rapidity) of the 
     *  particle-like object p
     */
    virtual double rapidity(const T &p) const = 0;
    /**
     *  Return the pT or, depending on implementation, pT-like quantity 
     *  (e.g. eT) of the particle-like object p
     */
    virtual double pT(const T &p) const = 0;
    /**
     *  Return the phi of the particle-like object p
     */
    virtual double phi(const T &p) const = 0;
    /**
     *  Scale the momentum or, depending on implementation, 
     *  momentum-like quantity of the particle-like object p
     *
     *  \param s value to multiply the momentum by
     */
    virtual void scale(double s,T &p) const = 0;
    
  };
  
  template<typename T>
  class Momentum : public IMomentum<T>{
    
  public:
    
    double rapidity(const T &p)const{
      return NewWave::rapidity(p);
    }
    
    double pT(const T &p)const{
      return NewWave::pT(p);
    }
    
    double phi(const T &p)const{
      return NewWave::phi(p);
    }
    
    void scale(double s, T &p) const{
      NewWave::scaleMomentum(s, p);
      return;
    }
    
  };
  
  /// Alias to shared pointer to a Momentum
  template<typename T> using MomentumPtr = shared_ptr<IMomentum<T> >;
  
}

#endif
