/*
 * Interface for delayed sampling $M$-path nodes.
 */
class Delay {
  /**
   * Parent, if one exists.
   */
  parent:Delay&;
  
  /**
   * Child, if one exists and it is on the $M$-path.
   */
  child:Delay?;
  
  /**
   * Has the random variate associated with this node been assigned a value?
   * If no random variate is associated with the node, always returns false.
   */
  function hasValue() -> Boolean {
    return false;
  }
  
  /**
   * Realize by simulation.
   */
  function realize();
  
  /**
   * Set the $M$-path child of this node.
   */
  function setChild(child:Delay) {
    child.parent <- this;
    this.child <- child;
  }
  
  /**
   * Remove the $M$-path child of this node.
   */
  function detach() {
    parent:Delay? <- this.parent;
    if (parent?) {
      this.parent <- nil;
      parent!.child <- nil;
    }
  }
  
  /**
   * Prune the $M$-path from below this node.
   */
  function prune() {
    if (child?) {
      child!.prune();
      child!.realize();
    }
  }
}
