#ifndef _RADIX_H
#define _RADIX_H

#include "SortTech.h"
#include "SortError.h"
#include "SortData.h"
#include <cmath>
#include <algorithm>

template<class T, template<typename...> class Container>
class Radix : public SortTech<T, Container> {
public:
    inline SortError sort(SortData<T, Container>& data) override;
};

template<class T, template<typename...> class Container>
inline SortError Radix<T, Container>::sort(SortData<T, Container>& data) {
    if (data.size() == 0)
        return SE_SUCCESS;
  
    T maxVal = *std::max_element(data.data().begin(), data.data().end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        // 1. Utwórz kubełki
        std::vector<std::vector<T>> buckets(10);

         for (size_t i = 0; i < data.size(); ++i) {
            int digit = (data[i] / exp) % 10;
            buckets[digit].push_back(data[i]);
        }

              size_t index = 0;
        for (int i = 0; i < 10; ++i) {
            for (T val : buckets[i]) {
                data.data()[index++] = val;
            }
        }
    }

    return SE_SUCCESS;
}

#endif
