/**
 * @file
 */
#pragma once

#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <initializer_list>
#include <tuple>
#include <memory>
#include <atomic>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cassert>
#include <getopt.h>
#include <dlfcn.h>

#ifdef _OPENMP
#include <omp.h>
#endif

/**
 * @def USE_MEMORY_POOL
 *
 * Set to 1 to use the built-in pooled allocator, or 0 to use standard
 * `malloc`/`realloc`/`free`.
 *
 * When performing memory leak checks with `valgrind`, set this to 0.
 * (Incidentally, may also need to disable OpenMP, at least on macOS.)
 */
#ifndef USE_MEMORY_POOL
#define USE_MEMORY_POOL 1
#endif

/**
 * @def USE_LAZY_DEEP_CLONE
 *
 * Set to 1 to use the lazy deep clone strategy, or 0 to use an eager deep
 * clone.
 */
#ifndef USE_LAZY_DEEP_CLONE
#define USE_LAZY_DEEP_CLONE 1
#endif

/**
 * @def INITIAL_MAP_SIZE
 *
 * Initial number of entries in each new map used for deep clone memoization.
 */
#ifndef INITIAL_MAP_SIZE
#define INITIAL_MAP_SIZE 64u
#endif

/**
 * @def INITIAL_SET_SIZE
 *
 * Initial number of entries in each new set used for ancestry memoization.
 */
#ifndef INITIAL_SET_SIZE
#define INITIAL_SET_SIZE 8u
#endif

/**
 * Constant to indicate a mutable value. Zero is convenient here, as it
 * enables multiplication to convolve multiple values.
 *
 * @ingroup libbirch
 */
static constexpr int64_t mutable_value = 0;
