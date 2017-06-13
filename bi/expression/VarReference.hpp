/**
 * @file
 */
#pragma once

#include "bi/expression/Expression.hpp"
#include "bi/expression/Parameter.hpp"
#include "bi/common/Named.hpp"
#include "bi/common/Reference.hpp"

namespace bi {
/**
 * Reference to a variable.
 *
 * @ingroup compiler_expression
 */
class VarReference: public Expression, public Named, public Reference<
    Parameter> {
public:
  /**
   * Constructor.
   *
   * @param name Name.
   * @param loc Location.
   * @param target Target.
   */
  VarReference(shared_ptr<Name> name, shared_ptr<Location> loc = nullptr,
      const Parameter* target = nullptr);

  /**
   * Destructor.
   */
  virtual ~VarReference();

  virtual Expression* accept(Cloner* visitor) const;
  virtual Expression* accept(Modifier* visitor);
  virtual void accept(Visitor* visitor) const;

  using Expression::definitely;
  using Expression::possibly;

  virtual bool dispatchDefinitely(const Expression& o) const;
  virtual bool definitely(const VarReference& o) const;
  virtual bool definitely(const Parameter& o) const;

  virtual bool dispatchPossibly(const Expression& o) const;
  virtual bool possibly(const VarReference& o) const;
  virtual bool possibly(const Parameter& o) const;
};
}
