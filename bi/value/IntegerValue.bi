/**
 * Integer value.
 */
class IntegerValue(value:Integer) < Value {
  /**
   * The value.
   */
  value:Integer <- value;

  operator -> Integer {
    return value;
  }
  
  function accept(gen:Generator) {
    gen.visit(this);
  }

  function isValue() -> Boolean {
    return true;
  }

  function getInteger() -> Integer? {
    return value;
  }

  function getReal() -> Real? {
    return value;
  }
}
