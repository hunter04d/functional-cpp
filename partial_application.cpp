// C++17 partial application
// compiler explorer link: https://godbolt.org/z/CdN8Uh
#include <iostream>
#include <utility>

template<typename F, typename... Args>
constexpr auto partial(F&& f, Args&& ... args) {
    // note: in c++20: return [&f, ...args = std::forward<Args>(args)] will remove the copies
    // for now this is the best I could come up with
    return [&f, args...](auto&& ... rest) constexpr {
        return std::forward<F>(f)(args..., std::forward<decltype(rest)>(rest)...);
    };
}

constexpr int add3(const int a, const int b, const int c) {
    return a + b + c;
}

int main() {
    constexpr auto add10_and_2_more = partial(add3, 10);
    constexpr auto res = add10_and_2_more(20, 30);
    std::cout << res;
}
