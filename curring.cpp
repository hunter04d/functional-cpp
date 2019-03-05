// C++17 curring
// compiler explorer link https://godbolt.org/z/y8pkIg
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <functional>


template<typename F>
constexpr auto curry(F&& f) {
    // I din't find any simple way to avoid by-value capture that works for all cases
    // thankfully compilers are able to inline all of this madness quite easily
    return [f](auto&& ... args) constexpr {
        if constexpr (!std::is_invocable_v<F, decltype(args)...>) {
            return curry([&f, &args...](auto&& ... xs)
            constexpr -> std::invoke_result_t<F, decltype(args)..., decltype(xs)...> {
                return f(std::forward<decltype(args)>(args)..., std::forward<decltype(xs)>(xs)...);
            });
        }
        else {
            return f(std::forward<decltype(args)>(args)...);
        }
    };
}


constexpr int add3(const int a, const int b, const int c) {
    return a + b + c;
}

int main() {
    // note: most IDEs get confused about this type of code
    constexpr auto fn = curry(add3);
    constexpr auto res1 = fn(10, 20)(30);
    constexpr auto res2 = fn(10)(20, 30);
    constexpr auto res3 = fn(10, 20)(30);
    constexpr auto res4 = fn(10)(20)(30);
    constexpr auto res5 = fn(10, 20, 30);
    std::cout << res1 << '\n';
    std::cout << res2 << '\n';
    std::cout << res3 << '\n';
    std::cout << res4 << '\n';
    std::cout << res5 << '\n';

    return 0;
}
