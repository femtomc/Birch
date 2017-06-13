/**
 * @file
 */
#include "bi/expression/Expression.hpp"

#include "bi/common/Iterator.hpp"
#include "bi/type/EmptyType.hpp"
#include "bi/expression/Range.hpp"

bi::Expression::Expression(Type* type, shared_ptr<Location> loc) :
    Located(loc), Typed(type) {
  //
}

bi::Expression::Expression(shared_ptr<Location> loc) :
    Located(loc) {
  //
}

bi::Expression::~Expression() {
  //
}

bool bi::Expression::isEmpty() const {
  return false;
}

bool bi::Expression::hasAssignable() const {
  for (auto iter = begin(); iter != end(); ++iter) {
    if ((*iter)->type->assignable) {
      return true;
    }
  }
  return false;
}

bi::Expression* bi::Expression::strip() {
  return this;
}

int bi::Expression::tupleSize() const {
  int result = 0;
  for (auto iter = begin(); iter != end(); ++iter) {
    ++result;
  }
  return result;
}

int bi::Expression::tupleDims() const {
  int result = 0;
  for (auto iter = begin(); iter != end(); ++iter) {
    if (dynamic_cast<const Range*>(*iter)) {
      ++result;
    }
  }
  return result;
}

bi::Iterator<bi::Expression> bi::Expression::begin() const {
  if (isEmpty()) {
    return end();
  } else {
    return bi::Iterator<Expression>(this);
  }
}

bi::Iterator<bi::Expression> bi::Expression::end() const {
  return bi::Iterator<Expression>(nullptr);
}

bool bi::Expression::definitely(const Expression& o) const {
  return o.dispatchDefinitely(*this);
}

bool bi::Expression::definitely(const BinaryReference& o) const {
  return false;
}

bool bi::Expression::definitely(const BracesExpression& o) const {
  return false;
}

bool bi::Expression::definitely(const BracketsExpression& o) const {
  return false;
}

bool bi::Expression::definitely(const EmptyExpression& o) const {
  return false;
}

bool bi::Expression::definitely(const FuncReference& o) const {
  return false;
}

bool bi::Expression::definitely(const GlobalVariable& o) const {
  return false;
}

bool bi::Expression::definitely(const Index& o) const {
  return false;
}

bool bi::Expression::definitely(const LambdaFunction& o) const {
  return false;
}

bool bi::Expression::definitely(const List<Expression>& o) const {
  return false;
}

bool bi::Expression::definitely(const Literal<bool>& o) const {
  return false;
}

bool bi::Expression::definitely(const Literal<int64_t>& o) {
  return false;
}

bool bi::Expression::definitely(const Literal<double>& o) const {
  return false;
}

bool bi::Expression::definitely(const Literal<const char*>& o) {
  return false;
}

bool bi::Expression::definitely(const LocalVariable& o) const {
  return false;
}

bool bi::Expression::definitely(const Member& o) const {
  return false;
}

bool bi::Expression::definitely(const MemberVariable& o) const {
  return false;
}

bool bi::Expression::definitely(const Parameter& o) const {
  return false;
}

bool bi::Expression::definitely(const ParenthesesExpression& o) const {
  return false;
}

bool bi::Expression::definitely(const Range& o) const {
  return false;
}

bool bi::Expression::definitely(const Span& o) const {
  return false;
}

bool bi::Expression::definitely(const Super& o) const {
  return false;
}

bool bi::Expression::definitely(const This& o) const {
  return false;
}

bool bi::Expression::definitely(const UnaryReference& o) const {
  return false;
}

bool bi::Expression::definitely(const VarReference& o) const {
  return false;
}

bool bi::Expression::possibly(const Expression& o) const {
  return o.dispatchPossibly(*this);
}

bool bi::Expression::possibly(const BinaryReference& o) const {
  return false;
}

bool bi::Expression::possibly(const BracesExpression& o) const {
  return false;
}

bool bi::Expression::possibly(const BracketsExpression& o) const {
  return false;
}

bool bi::Expression::possibly(const EmptyExpression& o) const {
  return false;
}

bool bi::Expression::possibly(const FuncReference& o) const {
  return false;
}

bool bi::Expression::possibly(const GlobalVariable& o) const {
  return false;
}

bool bi::Expression::possibly(const Index& o) const {
  return false;
}

bool bi::Expression::possibly(const LambdaFunction& o) const {
  return false;
}

bool bi::Expression::possibly(const List<Expression>& o) const {
  return false;
}

bool bi::Expression::possibly(const Literal<bool>& o) const {
  return false;
}

bool bi::Expression::possibly(const Literal<int64_t>& o) {
  return false;
}

bool bi::Expression::possibly(const Literal<double>& o) const {
  return false;
}

bool bi::Expression::possibly(const Literal<const char*>& o) {
  return false;
}

bool bi::Expression::possibly(const LocalVariable& o) const {
  return false;
}

bool bi::Expression::possibly(const MemberVariable& o) const {
  return false;
}

bool bi::Expression::possibly(const Parameter& o) const {
  return false;
}

bool bi::Expression::possibly(const ParenthesesExpression& o) const {
  return false;
}

bool bi::Expression::possibly(const Range& o) const {
  return false;
}

bool bi::Expression::possibly(const Span& o) const {
  return false;
}

bool bi::Expression::possibly(const Super& o) const {
  return false;
}

bool bi::Expression::possibly(const This& o) const {
  return false;
}

bool bi::Expression::possibly(const Member& o) const {
  return false;
}

bool bi::Expression::possibly(const UnaryReference& o) const {
  return false;
}

bool bi::Expression::possibly(const VarReference& o) const {
  return false;
}

bool bi::Expression::operator==(Expression& o) {
  return definitely(o) && o.definitely(*this);
}

bool bi::Expression::operator!=(Expression& o) {
  return !(*this == o);
}
