/**
 * @file
 */
#pragma once

#include "bi/expression/Expression.hpp"
#include "bi/common/Annotated.hpp"
#include "bi/primitive/poset.hpp"
#include "bi/primitive/is_convertible.hpp"

namespace bi {
/**
 * Overloaded object. Groups all overloads into one object.
 *
 * @ingroup common
 */
template<class ObjectType>
class Overloaded {
public:
  /**
   * Constructor.
   */
  Overloaded();

  /**
   * Constructor.
   *
   * @param o First overload.
   */
  Overloaded(ObjectType* o);

  /**
   * Does this contain the given overload?
   *
   * @param o The overload.
   */
  bool contains(ObjectType* o);

  /**
   * Get the given overload.
   *
   * @param o The overload.
   */
  ObjectType* get(ObjectType* o);

  /**
   * Add an overload.
   *
   * @param o The overload.
   */
  void add(ObjectType* o);

  /**
   * Number of overloads.
   */
  int size() const;

  /**
   * Iterators.
   */
  auto begin() const {
    return overloads.begin();
  }
  auto end() const {
    return overloads.end();
  }

  /**
   * Get first overload.
   */
  ObjectType* front() const;

  /**
   * Set a particular annotation on all overloads.
   */
  void set(const Annotation a);

  /**
   * Overloads.
   */
  poset<ObjectType*,is_convertible> overloads;
};
}
