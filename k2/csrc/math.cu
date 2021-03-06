/**
 * @brief
 * ragged
 *
 * @copyright
 * Copyright (c)  2020  Xiaomi Corporation (authors: Daniel Povey)
 *
 * @copyright
 * See LICENSE for clarification regarding multiple authors
 */

#include "k2/csrc/math.h"

namespace k2 {
/*
  Returns index of highest bit set, in range -1..31.
  HighestBitSet(0) = -1,
  HighestBitSet(1) = 0,
  HighestBitSet(2,3) = 1
  ...
 */
int32_t HighestBitSet(int32_t i) {
  K2_CHECK_GE(i, 0);
  for (int64_t j = 0; j < 32; j++) {
    if (i < (1 << j)) {
      return i - 1;
    }
  }
  return 32;
}

// returns random int32_t from [min..max]
int32_t RandInt(int32_t min, int32_t max) {
  K2_CHECK_GE(max, min);
  return (min + (rand() % (max + 1 - min)));  // NOLINT
}

// Returns random ints from a distribution that gives more weight to lower
// values.  I'm not implying this is a geometric distribution.  Anyway
// we aren't relying on any exact properties.
int32_t RandIntGeometric(int32_t min, int32_t max) {
  max >>= (RandInt(0, HighestBitSet(max / min)));
  if (max < min) max = min;
  return RandInt(min, max);
}

}  // namespace k2
