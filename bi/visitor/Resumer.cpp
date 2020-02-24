/**
 * @file
 */
#include "bi/visitor/Resumer.hpp"

bi::Resumer::Resumer(const Yield* yield) :
    yield(yield),
    foundYield(yield == nullptr) {
  //
}

bi::Resumer::~Resumer() {
  //
}

bi::Statement* bi::Resumer::clone(const Fiber* o) {
  auto r = new Function(o->annotation, o->name, o->typeParams->accept(this),
      o->params->accept(this), o->returnType->accept(this),
      o->braces->accept(this), o->loc);
  r->number = yield ? yield->number : 0;
  r->set(RESUME);
  if (!yield) {
    r->set(START);
  }
  return r;
}

bi::Statement* bi::Resumer::clone(const MemberFiber* o) {
  auto r = new MemberFunction(o->annotation, o->name,
      o->typeParams->accept(this), o->params->accept(this),
      o->returnType->accept(this), o->braces->accept(this), o->loc);
  r->number = yield ? yield->number : 0;
  r->set(RESUME);
  if (!yield) {
    r->set(START);
  }
  return r;
}

bi::Statement* bi::Resumer::clone(const LocalVariable* o) {
  LocalVariable* r = nullptr;
  if (foundYield) {
    r = new LocalVariable(o->annotation, o->name, o->type->accept(this),
        o->brackets->accept(this), o->args->accept(this),
        o->value->accept(this), o->loc);
  } else {
    r = new LocalVariable(o->name, o->type->accept(this), o->loc);
    r->set(RESUME);
  }
  r->number = o->number;
  return r;
}

bi::Statement* bi::Resumer::clone(const Yield* o) {
  if (o == yield && !foundYield) {  // may encounter second time if in loop
    foundYield = true;
    return new EmptyStatement(o->loc);
  } else if (foundYield) {
    auto r = new Yield(o->single->accept(this), o->loc);
    r->number = o->number;
    return r;
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const Return* o) {
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const ExpressionStatement* o) {
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const Assert* o) {
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const Raw* o) {
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const StatementList* o) {
  auto head = o->head->accept(this);
  auto tail = o->tail->accept(this);
  if (!head->isEmpty() && !tail->isEmpty()) {
    return new StatementList(head, tail, o->loc);
  } else if (!head->isEmpty()) {
    return head;
  } else if (!tail->isEmpty()) {
    return tail;
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const Braces* o) {
  auto single = o->single->accept(this);
  if (foundYield) {
    return new Braces(single, o->loc);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const If* o) {
  auto cond = o->cond->accept(this);
  auto foundBefore = foundYield;
  auto trueBraces = o->braces->accept(this);
  auto foundTrue = foundYield;
  auto falseBraces = o->falseBraces->accept(this);
  auto foundFalse = foundYield;

  if (foundBefore) {
    return new If(cond, trueBraces, falseBraces, o->loc);
  } else if (foundTrue) {
    return trueBraces;
  } else if (foundFalse) {
    return falseBraces;
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const For* o) {
  ///@todo unroll as for While and DoWhile
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const Parallel* o) {
  /* it is not possible to yield within a parallel loop, so this may be
   * treated as one atomic statement */
  if (foundYield) {
    return Cloner::clone(o);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const While* o) {
  auto cond = o->cond->accept(this);
  auto foundBefore = foundYield;
  auto braces = o->braces->accept(this);
  auto foundAfter = foundYield;

  if (foundBefore) {
    /* keep everything */
    return new While(cond, braces, o->loc);
  } else if (foundAfter) {
    /* `braces` has unrolled and reduced the first iteration of the loop
     * only, will need to clone in the entire loop after it */
    auto loop = new While(cond, o->braces->accept(this), o->loc);
    return new StatementList(braces, loop, o->loc);
  } else {
    return new EmptyStatement(o->loc);
  }
}

bi::Statement* bi::Resumer::clone(const DoWhile* o) {
  auto foundBefore = foundYield;
  auto braces = o->braces->accept(this);
  auto cond = o->cond->accept(this);
  auto foundAfter = foundYield;

  if (foundBefore) {
    /* keep everything */
    return new DoWhile(braces, cond, o->loc);
  } else if (foundAfter) {
    /* `braces` has unrolled and reduced the first iteration of the loop
     * only, will need to clone in the entire loop in after it, now as a
     * while rather than do-while loop, to ensure that the condition is
     * checked before the second iteration */
    auto loop = new While(cond, o->braces->accept(this), o->loc);
    return new StatementList(braces, loop, o->loc);
  } else {
    return new EmptyStatement(o->loc);
  }
}
