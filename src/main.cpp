#include <type_traits>
#include <vector>
#include <experimental/type_traits>

template <typename T, template <typename> typename C>
using is_satisfied = std::enable_if<C<T>::value, T>;

template <typename T>
using begin_type = decltype(std::declval<T>().begin());

template <typename T>
using end_type = decltype(std::declval<T>().end());

template <typename T>
using is_iterable = std::conjunction<
    std::experimental::is_detected<begin_type, T>,
    std::experimental::is_detected<end_type, T>
>;

template <typename A>
class MyClass {
    using iterable = typename is_satisfied<A, is_iterable>::type;
    iterable _mem;
};

int main() {
    MyClass<std::vector<int>> ok;
    // MyClass<int> ng;

    return 0;
}
