/**
 * @file
 *
 * Cast functions for multiple dispatch.
 */
#pragma once

#include "bi/primitive/shared_ptr.hpp"

#include <type_traits>

namespace bi {
enum TypeFlag {
  /**
   * Built-in type (e.g. double, int).
   */
  IS_BUILTIN,

  /**
   * Class type (most other things).
   */
  IS_CLASS,

  /**
   * Shared pointer to class type, used for polymorphic types.
   */
  IS_POINTER
};

template<class T>
struct type_flag {
  static const TypeFlag value =
      std::is_class<T>::value ? IS_CLASS : IS_BUILTIN;
};

template<class T>
struct type_flag<shared_ptr<T>> {
  static const TypeFlag value = IS_POINTER;
};

/**
 * Cast.
 */
template<class To, class From, TypeFlag to_flag, TypeFlag from_flag>
struct cast_impl {
  static To eval(From&& o) {
    throw std::bad_cast();
  }
};

template<class To, class From>
struct cast_impl<To,From,IS_BUILTIN,IS_BUILTIN> {
  static To eval(From&& o) {
    return static_cast<To>(o);
  }
};

template<class To, class From>
struct cast_impl<To,From,IS_BUILTIN,IS_CLASS> {
  static To eval(From&& o) {
    return static_cast<To>(o);
  }
};

template<class To, class From>
struct cast_impl<To,From,IS_CLASS,IS_CLASS> {
  static To eval(From&& o) {
    return dynamic_cast<To>(o);
  }
};

template<class To, class From>
struct cast_impl<To,From,IS_POINTER,IS_CLASS> {
  static To eval(From&& o) {
    return static_cast<To>(o);
  }
};

template<class To, class From>
struct cast_impl<To,From,IS_POINTER,IS_POINTER> {
  static To eval(From&& o) {
    auto result = To(o);
    if (result) {
      return result;
    } else {
      throw std::bad_cast();
    }
  }
};

/**
 * Cast.
 */
template<class To, class From>
inline To cast(From&& o) {
  static constexpr TypeFlag to_flag =
      type_flag<typename std::decay<To>::type>::value;
  static constexpr TypeFlag from_flag = type_flag<
      typename std::decay<From>::type>::value;

  return cast_impl<To,From,to_flag,from_flag>::eval(o);
}
}
