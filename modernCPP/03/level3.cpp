#include <print>
#include <coroutine>
#include <ranges>
#include <array>
#include <cstddef>

// ============================================================
// GCC-Compatible Coroutine Generator that Satisfies input_range
// ============================================================

template <typename T>
class Generator {
public:
    // ---------------- promise_type ----------------
    struct promise_type {
        T current_value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend()   noexcept { return {}; }

        std::suspend_always yield_value(T value) noexcept {
            current_value = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        Generator get_return_object() {
            return Generator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
    };

    // ---------------- iterator ----------------
    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;
        using iterator_concept  = std::input_iterator_tag;

        iterator() = default;

        explicit iterator(std::coroutine_handle<promise_type> h)
            : h_(h) {}

        iterator& operator++() {
            h_.resume();
            return *this;
        }

        void operator++(int) { operator++(); }

        const T& operator*() const {
            return h_.promise().current_value;
        }

        bool operator==(std::default_sentinel_t) const {
            return !h_ || h_.done();
        }

    private:
        std::coroutine_handle<promise_type> h_{};
    };

    // ---------------- Generator ----------------
    Generator() = default;
    explicit Generator(std::coroutine_handle<promise_type> h) : h_(h) {}

    Generator(Generator&& other) noexcept : h_(other.h_) {
        other.h_ = {};
    }

    ~Generator() {
        if (h_) h_.destroy();
    }

    iterator begin() {
        if (h_) h_.resume();
        return iterator{h_};
    }

    std::default_sentinel_t end() { return {}; }

private:
    std::coroutine_handle<promise_type> h_{};
};

// ============================================================
// Example: yield squares 1^2 to n^2
// ============================================================
Generator<int> squares(int n) {
    for (int i = 1; i <= n; ++i)
        co_yield i * i;
}

// ============================================================
// Main — Works on GCC 15.2.0
// ============================================================
int main() {
    std::print("=== Advanced C++23 Example (GCC-compatible) ===\n");

    Generator<int> gen = squares(10);

    // Pipeline: even squares, then multiply by 10
    auto pipeline =
        gen
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 10; });

    std::print("Even squares * 10:\n");
    for (int v : pipeline)
        std::print("  {}\n", v);

    // ========================================================
    // constexpr example without loops — GCC limitation
    // ========================================================
    constexpr std::array<int, 5> arr{1, 2, 3, 4, 5};

    // Must unroll — GCC forbids loops in constexpr lambdas
    constexpr int sum =
        arr[0] +
        arr[1] +
        arr[2] +
        arr[3] +
        arr[4];

    std::print("\nconstexpr sum = {}\n", sum);

    return 0;
}

