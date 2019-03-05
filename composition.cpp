// C++17 functional composition
// compiler explorer link https://godbolt.org/z/KyyG5p
#include <type_traits>
#include <functional>
#include <iostream>


template<typename F1, typename F2>
constexpr auto compose_helper(F1&& f1, F2&& f2) {
    // capture by value and hoping that the compiler will optimize this away
    return [f1, f2](auto&& ...args)
    constexpr {
        return f2((f1)(std::forward<decltype(args)>(args)...));
    };
}


// operator sadly does not work
template<typename F1, typename F2>
constexpr auto operator>>(F1&& f1, F2&& f2) {
    return compose(std::forward<F1>(f1), std::forward<F2>(f2));
}


template<typename F1, typename... Fns>
constexpr auto compose(F1&& f1, Fns&& ... fns) {
    if constexpr (sizeof...(fns) == 1) {
        return compose_helper(std::forward<F1>(f1), std::forward<Fns>(fns)...);
    }
    else {
        return compose_helper(std::forward<F1>(f1), compose(std::forward<Fns>(fns)...));
    }
}


constexpr int add3(int a, int b, int c) noexcept {
    return a + b + c;
}


template<typename T>
constexpr auto id(T&& t) noexcept {
    return std::forward<T>(t);
}


int main() {
    // type of a genetic function has to be specified, however generic lambda is allowed
    constexpr auto fn = compose(add3, [](auto i) { return i * 2; }, id<int>);
    constexpr auto res = fn(10, 20, 30);
    std::cout << res;
}
