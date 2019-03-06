// C++17 pattern matching like syntax for std::variant and std::optional
// compiler explorer link: https://godbolt.org/z/k67PDI
#include <optional>
#include <variant>
#include <functional>
#include <string>
#include <iostream>


// helper type for match function (for match(x, with {}) syntax)
template<typename... Ts>
struct with : Ts ... { using Ts::operator()...; };
template<typename... Ts> with(Ts...) -> with<Ts...>;


// for std::variant there already is a 'pattern matcher' called std::visit
// we just swap the arguments
template<typename F, typename ...Args>
constexpr decltype(auto) match(std::variant<Args...>&& variant, F&& f) {
    return std::visit(std::forward<F>(f), std::move(variant));
}


template<typename F, typename ...Args>
constexpr decltype(auto) match(const std::variant<Args...>& variant, F&& f) {
    return std::visit(std::forward<F>(f), variant);
}


// for optional invoke depending on if it has a value
template<typename T, typename F>
constexpr decltype(auto) match(std::optional<T>&& opt, F&& f) {
    if (opt) {
        return std::forward<F>(f)(std::forward<T>(*opt));
    }
    else {
        // prefer explicit one with std::nullopt_t
        if constexpr (std::is_invocable_v<F, std::nullopt_t>) {
            return std::forward<F>(f)(std::nullopt);
        }
        else {
            return std::forward<F>(f)();
        }
    }
}


template<typename T, typename F>
constexpr decltype(auto) match(const std::optional<T>& opt, F&& f) {
    if (opt) {
        return std::forward<F>(f)(*opt);
    }
    else {
        if constexpr (std::is_invocable_v<F, std::nullopt_t>) {
            return std::forward<F>(f)(std::nullopt);
        }
        else {
            return std::forward<F>(f);
        }
    }
}


int main() {

    std::variant<int, double> v = 3.14;
    match(v, with{
            [](double d) { std::cout << d << '\n'; },
            [](int i) { std::cout << i << '\n'; }
    });

    using namespace std::string_literals;
    std::optional<int> opt{};
    const auto str = match(opt, with{
            // return types of all cases have to match
            [](int i) { return "opt holds a value: " + std::to_string(i); },
            [](std::nullopt_t) { return "opt has no value std::nullopt_t case"s; },
            [] { return "opt has no value empty case"s; }
    });
    std::cout << str << '\n';
}