#ifndef NEWWAVE_MOMENTUM_HELPERS_HH
#define NEWWAVE_MOMENTUM_HELPERS_HH

#include <type_traits>

namespace NewWave{
  
  using std::enable_if;
  using std::is_member_function_pointer;
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::pT)>::value, double>::type
  pT(const T &p){
    return p.pT();
  }

  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::pt)>::value &&
  !is_member_function_pointer<decltype(&T::pT)>::value , double>::type
  pT(const T &p){
    return p.pt();
  }

  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::PT)>::value &&
  !is_member_function_pointer<decltype(&T::pt)>::value &&
  !is_member_function_pointer<decltype(&T::pT)>::value , double>::type
  pT(const T &p){
    return p.PT();
  }

  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::perp)>::value &&
  !is_member_function_pointer<decltype(&T::PT)>::value &&
  !is_member_function_pointer<decltype(&T::pt)>::value &&
  !is_member_function_pointer<decltype(&T::pT)>::value , double>::type
  pT(const T &p){
    return p.perp();
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::rapidity)>::value, double>::type
  rapidity(const T &p){
    return p.rapidity();
  }

  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::Rapidity)>::value &&
                      !is_member_function_pointer<decltype(&T::rapidity)>::value, double>::type
  rapidity(const T &p){
    return p.Rapidity();
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::phi)>::value, double>::type
  phi(const T &p){
    return p.phi();
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::Phi)>::value &&
  !is_member_function_pointer<decltype(&T::phi)>::value, double>::type
  phi(const T &p){
    return p.Phi();
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  !is_member_function_pointer<decltype(&T::perp)>::value &&
  !is_member_function_pointer<decltype(&T::PT)>::value &&
  !is_member_function_pointer<decltype(&T::pt)>::value &&
  !is_member_function_pointer<decltype(&T::pT)>::value , double>::type
  pT(const T &p){
    return pT(p.momentum());
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  !is_member_function_pointer<decltype(&T::Rapidity)>::value &&
  !is_member_function_pointer<decltype(&T::rapidity)>::value, double>::type
  rapidity(const T &p){
    return rapidity(p.momentum());
  }
  
  template<typename T>
  typename enable_if<is_member_function_pointer<decltype(&T::momentum)>::value &&
  !is_member_function_pointer<decltype(&T::Phi)>::value &&
  !is_member_function_pointer<decltype(&T::phi)>::value, double>::type
  phi(const T &p){
    return phi(p.momentum());
  }
  
}

#endif
