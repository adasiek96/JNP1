#include <string>
#include "cstrdequeconst"
#include "cstrdeque"

using namespace std;

extern void log_msg(const string& function, const string& message);
extern void log_params(const string& function, const string& message);

namespace {
#ifdef NDEBUG
    const bool debug = false;
#else
    const bool debug  = true;
#endif
}


namespace jnp1 {
    unsigned long emptystrdeque() {
        log_params(__FUNCTION__, "");

        static unsigned long empty_id;
        static bool empty_initialized = false;
        if (empty_initialized) {
            return empty_id;
        }
        empty_initialized = true;
        empty_id = ::jnp1::strdeque_new();
        log_msg(__FUNCTION__, "the Empty Deque created");
        return empty_id;
    }

}
