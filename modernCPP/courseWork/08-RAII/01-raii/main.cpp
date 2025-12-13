#include <mutex>
std::mutex m;

void f() {};
bool all_ok();

void bad() {
    m.lock();               // acquire the mutex
    f();                    // if f() throws an exception, the mutex is never released
    if (!all_ok()) return;  // early return, the mutex is never released
    m.unlock();             // if bad() reaches this statement, the mutex is released
}

void good() {
    std::lock_guard<std::mutex> lk(m);  // RAII class: mutex acqusition is initialized
    f();                                // if f() throws an exception, the mutex is released
    if(!all_ok()) return;               // if good() returns normally, the mutex is released
}

