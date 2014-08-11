#ifndef NEWWAVE_WAVELET_COEFFICIENT_HH
#define NEWWAVE_WAVELET_COEFFICIENT_HH

#include <vector>

namespace NewWave {
  
  using std::size_t;
  using std::vector;
  
  ///  Contains a single wavelet coefficient value, together with its levels
  /**
   *  The wavelet coefficient has a value, together with the scale information 
   *  for the wavelet basis function it corresponds to.  The scale information 
   *  is in the form of an integer level, such that the scale is proportional to
   *  \f$ 1 / 2^{l}\f$, where \f$l\f$ is the level.  There are two such levels for
   *  rapidity and \f$\phi\f$
   */
  class WaveletCoefficient{
    
  public:
    
    /// Constructor
    /**
     *  Construct a WaveletCoefficient from its rapidity level, phi level and value
     *
     *  \param yLevel The rapidity level
     *  \param phiLevel The \f$\phi\f$ level
     *  \param value The value of the coefficient
     */
    WaveletCoefficient(size_t yLevel, size_t phiLevel, double value);
    
    /// The value of the coefficient
    /**
     *  \return The value of the coefficient
     */
    double value()const;
    
    /// The rapidity level of the coefficient
    /**
     *  The rapidity level gives the scale of the wavelet basis funciton in
     *  the rapidity axis.  The scale is proportional to \f$1 / 2^{l}\f$
     *
     *  \return The rapidity level
     */
    size_t yLevel()const;
    
    /// The \f$\phi\f$ level of the coefficient
    /**
     *  The \f$\phi\f$ level gives the scale of the wavelet basis funciton in
     *  the \f$\phi\f$ axis.  The scale is proportional to \f$1 / 2^{l}\f$
     *
     *  \return The \f$\phi\f$ level
     */
    size_t phiLevel()const;
    
    /// Set the value of the coefficient
    /**
     * \param val the new value of the coefficient
     */
    void setValue(double val);
    
  private:
    
    double _value;
    size_t _yLevel;
    size_t _phiLevel;
    
  };
  
  typedef vector<WaveletCoefficient> WaveletCoefficients;
  
}

#endif
