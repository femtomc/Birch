/**
 * Boolean vector value.
 */
class BooleanVectorValue(value:Boolean[_]) < Value {
  /**
   * The value.
   */
  value:Boolean[_] <- value;
  
  operator -> Boolean[_] {
    return value;
  }

  function accept(gen:Generator) {
    gen.visit(this);
  }

  function isValue() -> Boolean {
    return true;
  }
  
  function getBooleanVector() -> Boolean[_]? {
    return value;
  }
}
