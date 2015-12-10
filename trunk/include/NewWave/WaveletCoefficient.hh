#ifndef NEWWAVE_WAVELET_COEFFICIENT_HH
#define NEWWAVE_WAVELET_COEFFICIENT_HH

#include "NewWave/FrequencyBand.fh"
#include "NewWave/WaveletCoefficient.fh"
#include "NewWave/WaveletBaseEvent.hh"

namespace NewWave {
  
  using std::size_t;
  
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
     *  \param key A key that, within the present event, is unique for this coefficient
     *  \param yMin The lower edge of the rapidity region to which this coefficient contributes, normalised so that the entire rapidity range is {0,1}
     *  \param phiMin The lower edge of the phi region to which this coefficient contributes, normalised so that the entire phi range is {0,1}
     *  \param value The value of the coefficient
     */
    WaveletCoefficient(size_t yLevel, size_t phiLevel,
                       size_t key,
                       double yMin, double yMax,
                       double phiMin, double phiMax,
                       double value);
    
    /// The value of the coefficient
    /**
     *  \return The value of the coefficient
     */
    double value()const;
    
    /// Return a unique key for the coefficient
    /**
     *  In a given event, there is a fixed set of coefficients 
     *  specifying the event.  Each one has a key that is unique within 
     *  that set.  Coefficients from different events may have the same
     *  key, of course.
     *
     *  \return The unique key for this WaveletCoefficient
     */
    size_t key()const;
    
    /// The rapidity level of the coefficient
    /**
     *  The rapidity level gives the scale of the wavelet basis function in
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
    
    
    /// The minimum of the \f$\phi\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and 
     *  \f$y\f$ levels.
     */
    double phiMin()const;

    /// The maximum of the \f$\phi\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and
     *  \f$y\f$ levels.
     */
    double phiMax()const;
    
    /// The centre of the \f$\phi\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and
     *  \f$y\f$ levels.
     */
    double phiCentre()const;
    
    /// The minimum of the \f$y\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and
     *  \f$y\f$ levels.
     */
    double yMin()const;

    /// The maximum of the \f$y\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and
     *  \f$y\f$ levels.
     */
    double yMax()const;
    
    /// The centre of the \f$y\f$ range covered by the coefficient
    /**
     *  The contribution of each coefficient is localised to a region in
     *  \f$\phi-y\f$, the size of which depends on the \f$\phi\f$ and
     *  \f$y\f$ levels.
     */
    double yCentre()const;
    
    /// Set the value of the coefficient
    /**
     * \param val the new value of the coefficient
     */
    void setValue(double val);
    
    /// Give a hash that is unique to the FrequencyBand this coefficient belongs in
    /**
     *  The hash is determined by the y-level, the \f$\phi\f$-level, and 
     *  the total number of levels used.  The hash is simply 
     *
     *  \f$(level_{\phi}) + (N_{levels} + 1)\times(level_{y})\f$
     *
     *  \param nLevels the total number of levels specified in the transform
     */
    int frequencyHash(int nLevels)const;
    
    /// Give a hash that is unique to the FrequencyBand this coefficient belongs in
    /**
     *  The hash is determined by the y-level, the \f$\phi\f$-level, and
     *  the total number of levels used.  The hash is simply
     *
     *  \f$(level_{\phi}) + (N_{levels} + 1)\times(level_{y})\f$
     *
     *  \param nLevels the total number of levels specified in the transform
     */
    int frequencyHash()const;
    
    const FrequencyBand &frequencyBand()const;
    
  private:
    
    double _value;
    size_t _yLevel;
    size_t _phiLevel;
    size_t _key;
    
    double _yMin;
    double _phiMin;
    
    double _yMax;
    double _phiMax;
    
    mutable double _yCentre;
    mutable double _phiCentre;
    
    mutable bool _haveYCentre;
    mutable bool _havePhiCentre;
    
    friend class WaveletBaseEvent;
    
    const WaveletBaseEvent *_event;
    
  };
  
}

#endif
