/**
 * @file
 */
#pragma once

#include "src/statement/Statement.hpp"
#include "src/common/ReturnTyped.hpp"
#include "src/common/Scoped.hpp"
#include "src/common/Braced.hpp"

namespace birch {
/**
 * Type conversion operator.
 *
 * @ingroup statement
 */
class ConversionOperator: public Statement,
    public ReturnTyped,
    public Scoped,
    public Braced {
public:
  /**
   * Constructor.
   *
   * @param returnType Return type.
   * @param braces Body.
   * @param loc Location.
   */
  ConversionOperator(Type* returnType, Statement* braces,
      Location* loc = nullptr);

  /**
   * Destructor.
   */
  virtual ~ConversionOperator();

  virtual bool isDeclaration() const;

  virtual Statement* accept(Cloner* visitor) const;
  virtual Statement* accept(Modifier* visitor);
  virtual void accept(Visitor* visitor) const;
};
}
