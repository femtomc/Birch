/**
 * @file
 */
#include "bi/common/Path.hpp"

#include "bi/visitor/all.hpp"

#include "boost/filesystem.hpp"

#include <sstream>

bi::Path::Path(Name* head, Path* tail, Location* loc) :
    Located(loc), head(head), tail(tail) {
  //
}

bi::Path::~Path() {
  //
}

void bi::Path::accept(Visitor* visitor) const {
  visitor->visit(this);
}

bool bi::Path::operator==(const Path& o) const {
  return *head == *o.head
      && ((!tail && !o.tail) || (tail && o.tail && *tail == *o.tail));
}

bool bi::Path::operator!=(Path& o) {
  return !(*this == o);
}

std::string bi::Path::file() const {
  boost::filesystem::path file("bi");
  const Path* path = this;
  while (path) {
    file /= path->head->str();
    path = path->tail;
  }
  file.replace_extension("bi");

  return file.string();
}

std::string bi::Path::str() const {
  std::stringstream buf;
  const Path* path = this;
  while (path) {
    buf << path->head->str();
    path = path->tail;
    if (path) {
      buf << '.';
    }
  }
  return buf.str();
}
