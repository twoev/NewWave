#ifndef NEWWAVE_MOMENTUM_HELPERS_HH
#define NEWWAVE_MOMENTUM_HELPERS_HH

#include <type_traits>

namespace NewWave{
  
  using std::enable_if;
  using std::is_member_function_pointer;
  
  template <typename T>
  struct has_momentum {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::momentum)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };

  template <typename T>
  struct has_setMomentum {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::setMomentum)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template <typename T>
  struct has_pT {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::pT)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };

  template <typename T>
  struct has_pt {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::pt)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template <typename T>
  struct has_PT {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::PT)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template <typename T>
  struct has_perp {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::perp)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template <typename T>
  struct has_rapidity {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::rapidity)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };

  template <typename T>
  struct has_Rapidity {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::Rapidity)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template <typename T>
  struct has_phi {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::phi)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };

  template <typename T>
  struct has_Phi {
    
    template <typename U>
    static constexpr bool
    _value(typename enable_if<is_member_function_pointer<decltype(&U::Phi)>::value, U*>::type){
      return true;
    }
    
    template <typename U>
    static constexpr bool
    _value(...){
      return false;
    }
    
    static constexpr bool value = _value<T>(0);
  };
  
  template<typename T>
  typename enable_if<has_pT<T>::value, double>::type
  pT(const T &p){
    return p.pT();
  }

  template<typename T>
  typename enable_if<has_pt<T>::value &&
  !has_pT<T>::value, double>::type
  pT(const T &p){
    return p.pt();
  }

  template<typename T>
  typename enable_if<has_PT<T>::value &&
  !has_pt<T>::value &&
  !has_pT<T>::value , double>::type
  pT(const T &p){
    return p.PT();
  }

  template<typename T>
  typename enable_if<has_perp<T>::value &&
  !has_PT<T>::value &&
  !has_pt<T>::value &&
  !has_pT<T>::value , double>::type
  pT(const T &p){
    return p.perp();
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  !has_perp<T>::value &&
  !has_PT<T>::value &&
  !has_pt<T>::value &&
  !has_pT<T>::value , double>::type
  pT(const T &p){
    return pT(p.momentum());
  }
  
  template<typename T>
  typename enable_if<has_rapidity<T>::value, double>::type
  rapidity(const T &p){
    return p.rapidity();
  }

  template<typename T>
  typename enable_if<has_Rapidity<T>::value &&
  !has_rapidity<T>::value, double>::type
  rapidity(const T &p){
    return p.Rapidity();
  }
  
  template<typename T>
  typename enable_if<has_momentum<T>::value &&
  !has_Rapidity<T>::value &&
  !has_rapidity<T>::value, double>::type
  rapidity(const T &p){
    return rapidity(p.momentum());
  }
  
  template<typename T>
  typename enable_if<has_phi<T>::value, double>::type
  phi(const T &p){
    return p.phi();
  }
  
  template<typename T>
  typename enable_if<has_Phi<T>::value &&
  !has_phi<T>::value, double>::type
  phi(const T &p){
    return p.Phi();
  }
  
  template<typename T>
  typename enable_if<has_momentum<T>::value &&
  !has_Phi<T>::value &&
  !has_phi<T>::value, double>::type
  phi(const T &p){
    return phi(p.momentum());
  }
  
  
  template<typename T>
  typename enable_if<has_momentum<T>::value &&
  has_setMomentum<T>::value>::type
  scaleMomentum(double scale, T &p){
    p.setMomentum(p.momentum() * scale);
    return;
  }
  
  template<typename T>
  typename enable_if<!has_momentum<T>::value>::type
  scaleMomentum(double scale, T &p){
    p *= scale;
    return;
  }
  
  template<typename T>
  class Momentum {
    
  public:
    
    using element_type = typename T::value_type;
    
    inline static double rapidity(const element_type &p){
      return NewWave::rapidity(p);
    }
    
    inline static double pT(const element_type &p){
      return NewWave::pT(p);
    }
    
    inline static double phi(const element_type &p){
      return NewWave::phi(p);
    }
    
    inline static void scale(double s, element_type &p){
      NewWave::scaleMomentum(s, p);
      return;
    }
    
  };
  
}

#endif



