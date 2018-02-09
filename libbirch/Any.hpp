/**
 * @file
 */
#pragma once

#include "libbirch/SharedPointer.hpp"
#include "libbirch/Wrapper.hpp"

namespace bi {
/**
 * Base class for all class types.
 *
 * @ingroup libbirch
 */
class Any: public std::enable_shared_from_this<Any> {
public:
  /**
   * Constructor.
   */
  Any();

  /**
   * Copy constructor.
   */
  Any(const Any& o);

  /**
   * Destructor.
   */
  virtual ~Any();

  /**
   * Clone the object.
   */
  virtual std::shared_ptr<Any> clone() const;

  /**
   * Get the object world.
   */
  const std::shared_ptr<World>& getWorld();

  /**
   * Pointer to this with wrapper for world.
   */
  template<class T>
  auto self() {
    return Wrapper<T>(static_cast<T*>(this));
  }

  /**
   * Create a shared pointer from this object.
   */
  template<class T>
  auto shared_from_this() {
    auto ptr = enable_shared_from_this<Any>::shared_from_this();
    return SharedPointer<T>(std::static_pointer_cast<T>(ptr));
  }

protected:
  /**
   * The world to which this object belongs.
   */
  std::shared_ptr<World> world;
};
}
