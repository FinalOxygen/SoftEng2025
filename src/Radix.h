#ifndef _RADIX_H
#define _RADIX_H

#include <algorithm>
#include "SortTech.h"
#include "SortError.h"
#include "SortData.h"

template<class T, template<typename...> class Container>
class Radix : public SortTech<T, Container> {
public:
    inline SortError sort(SortData<T, Container>& data) override;
};

template<class T, template<typename...> class Container>
inline SortError Radix<T, Container>::sort(SortData<T, Container>& data) {
    if (data.size() == 0)
        return SE_SUCCESS;

    auto& container = data.getData();

    T max = *std::max_element(container.begin(), container.end());
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::stable_sort(container.begin(), container.end(),
            [exp](T a, T b) {
                return (a / exp) % 10 < (b / exp) % 10;
            }
        );
    }

    return SE_SUCCESS;
}

#endif
