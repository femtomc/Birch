/**
 * @file
 */
#pragma once

#include "bi/common/Dictionary.hpp"
#include "bi/common/OverloadedDictionary.hpp"
#include "bi/common/DispatcherDictionary.hpp"
#include "bi/common/Named.hpp"
#include "bi/primitive/definitely.hpp"
#include "bi/primitive/possibly.hpp"

#include <set>

namespace bi {
class VarParameter;
class FuncParameter;
class TypeParameter;
class ProgParameter;

class VarReference;
class FuncReference;
class TypeReference;
class ProgReference;

class Dispatcher;

/**
 * Scope.
 *
 * @ingroup compiler_common
 */
class Scope {
public:
  /**
   * Does the scope contain the parameter?
   *
   * @param param Parameter.
   *
   * For functions, matching is done by signature. For all others, matching
   * is done by name only.
   */
  bool contains(VarParameter* param);
  bool contains(FuncParameter* param);
  bool contains(TypeParameter* param);
  bool contains(ProgParameter* param);

  /**
   * Add parameter.
   *
   * @param param Parameter.
   */
  void add(VarParameter* param);
  void add(FuncParameter* param);
  void add(TypeParameter* param);
  void add(ProgParameter* param);

  /**
   * Resolve a reference to a parameter.
   *
   * @param ref Reference to resolve.
   *
   * @return Target of the reference.
   */
  void resolve(VarReference* ref);
  void resolve(FuncReference* ref);
  void resolve(TypeReference* ref);

  /*
   * Dispatchers.
   */
  bool contains(Dispatcher* dispatcher);
  void add(Dispatcher* dispatcher);
  Dispatcher* get(Dispatcher* dispatcher);

  /**
   * Inherit another scope into this scope. This is used to import
   * declarations from a base class into a derived class.
   *
   * @param scope Scope to inherit.
   */
  void inherit(Scope* scope);

  /**
   * Import another scope into this scope. This is used to import
   * declarations from one file into another file.
   *
   * @param scope Scope to inherit.
   */
  void import(Scope* scope);

  /**
   * Base scopes.
   */
  std::set<Scope*> bases;

  /*
   * Dictionaries.
   */
  Dictionary<VarParameter> vars;
  Dictionary<TypeParameter> types;
  OverloadedDictionary<FuncParameter,definitely> definites;
  OverloadedDictionary<FuncParameter,possibly> possibles;
  Dictionary<ProgParameter> progs;
  DispatcherDictionary dispatchers;

private:
  /**
   * Defer resolution to imported scopes.
   */
  template<class ParameterType, class ReferenceType>
  void resolveDefer(ReferenceType* ref);
};
}

template<class ParameterType, class ReferenceType>
void bi::Scope::resolveDefer(ReferenceType* ref) {
  auto iter = bases.begin();
  while (!ref->target && iter != bases.end()) {
    (*iter)->resolve(ref);
    ++iter;
  }
}
