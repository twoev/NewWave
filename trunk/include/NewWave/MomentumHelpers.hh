#ifndef NEWWAVE_MOMENTUM_HELPERS_HH
#define NEWWAVE_MOMENTUM_HELPERS_HH

#include <type_traits>

namespace NewWave{
  
  using std::enable_if;
  using std::is_member_function_pointer;
  
  template <typename T, typename NameGetter>
  struct has_member_impl
  {
    typedef char matched_return_type;
    typedef long unmatched_return_type;
    
    template <typename C>
    static matched_return_type f(typename NameGetter::template get<C>*);
    
    template <typename C>
    static unmatched_return_type f(...);
    
  public:
    static const bool value = (sizeof(f<T>(0)) == sizeof(matched_return_type));
  };
  
  template <typename T, typename NameGetter>
  struct has_member :
  std::integral_constant<bool, NewWave::has_member_impl<T, NameGetter>::value>
  { };
  
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
  
  // checker funcs
  struct check_pT{
    template<typename T, double (T::*)() const = &T::pT >
    struct get
    { };
  };

  struct check_pt{
    template<typename T, double (T::*)() const = &T::pt >
    struct get
    { };
  };
  
  struct check_PT{
    template<typename T, double (T::*)() const = &T::PT >
    struct get
    { };
  };
  
  struct check_perp{
    template<typename T, double (T::*)() const = &T::perp >
    struct get
    { };
  };
  
  struct check_rapidity{
    template<typename T, double (T::*)() const = &T::rapidity >
    struct get
    { };
  };

  struct check_Rapidity{
    template<typename T, double (T::*)() const = &T::Rapidity >
    struct get
    { };
  };

  struct check_phi{
    template<typename T, double (T::*)() const = &T::phi >
    struct get
    { };
  };
  
  struct check_Phi{
    template<typename T, double (T::*)() const = &T::Phi >
    struct get
    { };
  };
  // end of checker funcs


  template <typename T>
  struct has_pT :
  has_member<T, check_pT>
  { };

  template <typename T>
  struct has_pt :
  has_member<T, check_pt>
  { };
  
  template <typename T>
  struct has_PT :
  has_member<T, check_PT>
  { };
  
  template <typename T>
  struct has_perp :
  has_member<T, check_perp>
  { };
  
  template <typename T>
  struct has_rapidity :
  has_member<T, check_rapidity>
  { };
  
  template <typename T>
  struct has_Rapidity :
  has_member<T, check_Rapidity>
  { };

  template <typename T>
  struct has_phi :
  has_member<T, check_phi>
  { };
  
  template <typename T>
  struct has_Phi :
  has_member<T, check_Phi>
  { };
  
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
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
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
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  !has_Phi<T>::value &&
  !has_phi<T>::value, double>::type
  phi(const T &p){
    return phi(p.momentum());
  }
  
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  is_member_function_pointer<decltype(&T::setMomentum)>::value>::type
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
  
  
}

#endif



