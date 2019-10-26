/**
 * @file
 */
#include "bi/exception/FinalBodyException.hpp"

#include "bi/io/bih_ostream.hpp"

bi::FinalBodyException::FinalBodyException(const MemberFunction* o) {
  std::stringstream base;
  bih_ostream buf(base);
  if (o->loc) {
    buf << o->loc;
  }
  buf << "error: a member function marked final must have a body\n";
  if (o->loc) {
    buf << o->loc;
  }
  buf << "note: in\n";
  buf << o;
  msg = base.str();
}
