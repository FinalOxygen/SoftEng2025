#ifndef _RADIX_H
#define _RADIX_H

#include "SortTech.h"
#include "SortError.h"
#include "SortData.h"
#include <type_traits>
#include <algorithm>

template<class T, template<typename...> class Container>
class Radix : public SortTech<T, Container> {
public:
    inline SortError sort(SortData<T, Container> & data) override;
};

template<class T, template<typename...> class Container>
inline SortError Radix<T, Container>::sort(SortData<T, Container> & data) {
    // Tylko dla typów całkowitych
    if (!std::is_integral<T>::value) {
        return SE_INVALID_TYPE;
    }

    if (data.data.empty()) return SE_SUCCESS;

    T maxVal = *std::max_element(data.data.begin(), data.data.end());

    for (T exp = 1; maxVal / exp > 0; exp *= 10) {
        const int base = 10;
        Container<T> output(data.data.size());
        int count[base] = {0};

        for (const T& val : data.data) {
            count[(val / exp) % base]++;
        }

        for (int i = 1; i < base; i++) {
            count[i] += count[i - 1];
        }

        for (int i = static_cast<int>(data.data.size()) - 1; i >= 0; i--) {
            T val = data.data[i];
            int index = (val / exp) % base;
            output[--count[index]] = val;
        }

        data.data = output;
    }

    return SE_SUCCESS;
}


#endif
