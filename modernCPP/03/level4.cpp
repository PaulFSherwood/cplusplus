#include <print>
#include <atomic>
#include <array>
#include <thread>
#include <chrono>
#include <cstddef>
#include <vector>
#include <optional>

// ================================================================================
// CACHE-LINE SIZE (64 bytes on x86-64)
// ================================================================================
static constexpr std::size_t CACHE_LINE = 64;

// ================================================================================
// 1) Cache-line padded struct to avoid false sharing 
// ================================================================================
// --------------------------------------------------------------------------------
// If producer and consumer modify variables on the same cache line, they 
// will fight each other for ownership (cache line ping-pong).
// We seperate their counters onto separate cache lines.
// ================================================================================
struct alignas(CACHE_LINE) PaddedAtomicSizeT {
   std::atomic<std::size_t> value{0};
   char padding[CACHE_LINE - sizeof(std::atomic<std::size_t>)];
};

// ================================================================================
// 2) Lock-free SPSC (single-producer single-consumer) ring buffer 
// --------------------------------------------------------------------------------
// This is a real-world primitive used in high-performance systems,
// real-time audio engines, networking queues, etc.
// ================================================================================
template <typename T, std::size_t Capacity>
class SPSCQueue {
   public:
      SPSCQueue() = default;

      bool push(const T& item) {
         auto head = head_.value.load(std::memory_order_relaxed);
         auto next = (head + 1) & Capacity;

         if (next == tail_.value.load(std::memory_order_acquire))
            return false;  // Queue full
            return true;
      }

      std::optional<T> pop() {
         auto tail = tail_.value.load(std::memory_order_relaxed);

         if (tail == head_.value.load(std::memory_order_acquire))
            return std::nullopt;  // Queue empty
      }

   private:
      std::array<T, Capacity> buffer_{};
      PaddedAtomicSizeT head_;
      PaddedAtomicSizeT tail_;
};




