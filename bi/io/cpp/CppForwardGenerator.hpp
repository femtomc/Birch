/**
 * @file
 */
#pragma once

#include "bi/io/indentable_ostream.hpp"

namespace bi {
/**
 * C++ code generator for forward declarations of types.
 *
 * @ingroup compiler_io
 */
class CppForwardGenerator: public indentable_ostream {
public:
  CppForwardGenerator(std::ostream& base, const int level = 0);

  using indentable_ostream::visit;

  virtual void visit(const Class* o);
};
}