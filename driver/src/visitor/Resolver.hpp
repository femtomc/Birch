/**
 * @file
 */
#pragma once

#include "src/visitor/ScopedModifier.hpp"

namespace birch {
/**
 * Populate local scopes, and resolve identifiers.
 *
 * @ingroup visitor
 */
class Resolver: public ScopedModifier {
public:
  /**
   * Constructor.
   *
   * @param currentPackage If the visitor will not begin by visiting the
   * package, provide it for scoping purposes.
   * @param currentClass If the visitor will begin by visiting the members of
   * a class, but not the class itself, provide it for scoping purposes.
   */
  Resolver(Package* currentPackage = nullptr, Class* currentClass = nullptr);

  /**
   * Destructor.
   */
  virtual ~Resolver();

  using ScopedModifier::modify;

  virtual Expression* modify(Parameter* o);
  virtual Statement* modify(LocalVariable* o);
  virtual Expression* modify(NamedExpression* o);
  virtual Type* modify(NamedType* o);
  virtual Statement* modify(Class* o);
};
}
