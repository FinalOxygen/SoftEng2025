#ifndef _RADIX_H
#define _RADIX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue> 

#include "SortTech.h"
#include "SortError.h"
#include "SortData.h"

template<class T, template<typename...> class Container>
class Radix : public SortTech<T, Container> {
  public:
    inline SortError sort(SortData<T> & data) override;

};
template<class T, template<typename...> class Container>
inline SortError Radix<T, Container>::sort(SortData<T> & data) {

  SortError error = SE_SUCCESS;

  if constexpr (std::is_integral<T>::value)
  {
    // Copy elements from SortData to a temporary vector for processing
    std::vector<T> temp(data.begin(error), data.end(error));

    constexpr size_t num_passes = sizeof(T);
    constexpr bool is_signed = std::is_signed<T>::value;

    for (size_t pass = 0; pass < num_passes; ++pass) {
      size_t shift = pass * 8;  // Each pass processes 8 bits
      std::vector<std::vector<T>> buckets(256);

      // Distribute elements into buckets based on the current byte
      for (const T& val : temp) {
        uint8_t digit = static_cast<uint8_t>((val >> shift) & 0xFF);
        // Adjust the most significant byte for signed types
        if (pass == num_passes - 1 && is_signed) {
          digit ^= 0x80;  // Flip the sign bit for proper ordering
        }
        buckets[digit].push_back(val);
      }

      // Rebuild the temporary vector from buckets
      temp.clear();
      for (auto& bucket : buckets) {
        temp.insert(temp.end(), bucket.begin(), bucket.end());
      }
    }

    // Copy sorted elements back to SortData using iterators
    auto data_iter = data.begin(error);
    auto temp_iter = temp.begin();
    for (; data_iter != data.end(error) && temp_iter != temp.end(); ++data_iter, ++temp_iter) {
      *data_iter = *temp_iter;
    }

  }


  return SE_SUCCESS;
}

#endif