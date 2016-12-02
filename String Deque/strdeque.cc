#include <iostream>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cassert>
#include "cstrdeque"
#include "cstrdequeconst"

using namespace std;
using map_t = unordered_map<unsigned long, deque<string>>;


namespace {
#ifdef NDEBUG
    const bool debug = false;
#else
    const bool debug = true;
#endif
}

void log_msg(const string& function, const string& message) {
    if (debug)
        cerr << function << ": " << message << endl;
}

void log_params(const string& function, const string& message) {
    if (debug)
        cerr << function << "(" << message << ")" << endl;
}

namespace {
    map_t &get_deques() {
        static map_t *deques = new map_t();
        return *deques;
    }

    map_t::iterator get_deque_iter(unsigned long id) {
        auto target = get_deques().find(id);
        return target;
    }

    bool deque_exists(const map_t::iterator& it) {
        return it != end(get_deques());
    }

    const string deque_repr(unsigned long id) {
        if (id == ::jnp1::emptystrdeque())
            return "the Empty Deque";
        else
            return "deque " + to_string(id);
    }
}

namespace jnp1 {

    unsigned long strdeque_new() {
        log_params(__FUNCTION__, "");

        static unsigned long deque_id = 0;
        assert(deque_id != ULONG_MAX);

        get_deques().insert(make_pair(deque_id, deque<string>()));

        log_msg(__FUNCTION__, to_string(deque_id) + " created");
        return deque_id++;
    }

    void strdeque_delete(unsigned long id) {
        log_params(__FUNCTION__, to_string(id));

        if (id == emptystrdeque()) {
            log_params(__FUNCTION__, "attempt to delete an empty deque");
            return;
        }

        auto it = get_deque_iter(id);
        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) + " does not exist");
            return;
        }

        get_deques().erase(it);

        log_msg(__FUNCTION__, deque_repr(id) + " deleted");
    }

    size_t strdeque_size(unsigned long id) {
        auto it = get_deque_iter(id);

        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) + " does not exist");
            return 0;
        } else {
            size_t size = it->second.size();
            log_msg(__FUNCTION__,
                    deque_repr(id) + " contains " + to_string(size) +
                    " elements");
            return size;
        }
    }

    void strdeque_insert_at(unsigned long id, size_t pos, const char *value) {
        log_params(__FUNCTION__,
                   to_string(id) + ", " + to_string(pos) + ", " +
                   (value == NULL ? "NULL" : "\"" + string(value) + "\""));

        if (value == NULL) {
            log_msg(__FUNCTION__, "attempt to insert NULL into deque");
            return;
        }

        if (id == emptystrdeque()) {
            log_msg(__FUNCTION__, "attempt to insert into an empty deque");
            return;
        }


        auto it = get_deque_iter(id);
        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) + " does not exist");
            return;
        }

        deque<string>::iterator it_deque;
        if (it->second.size() > pos)
            it_deque = begin(it->second) + pos;
        else
            it_deque = end(it->second);

        it->second.insert(it_deque, string(value));

        log_msg(__FUNCTION__,
                deque_repr(id) + ", element \"" + value +
                "\" inserted at " +
                to_string(max(pos, it->second.size())));
    }

    void strdeque_remove_at(unsigned long id, size_t pos) {
        log_params(__FUNCTION__, to_string(id) + ", " + to_string(pos));

        if (id == emptystrdeque()) {
            log_msg(__FUNCTION__, "attempt to remove from an empty deque");
            return;
        }

        auto it = get_deque_iter(id);
        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) + " does not exist");
            return;
        }

        if (it->second.size() > pos) {
            it->second.erase(begin(it->second) + pos);
            log_msg(__FUNCTION__, deque_repr(id) + ", element at " +
                                  to_string(pos) + " removed");
        } else {
            log_msg(__FUNCTION__,
                    deque_repr(id) + ", position " + to_string(pos) +
                    " bigger than size " +
                    to_string(it->second.size()));
        }
    }

    const char *strdeque_get_at(unsigned long id, size_t pos) {
        log_params(__FUNCTION__, to_string(id) + ", " + to_string(pos));

        auto it = get_deque_iter(id);
        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) +
                                  " does not contain an element at " +
                                  to_string(pos));
            return NULL;
        }

        if (it->second.size() > pos) {
            string res = it->second.at(pos);
            log_msg(__FUNCTION__, deque_repr(id) + ", element at " +
                                  to_string(pos) + " is \"" + res + "\"");
            return res.c_str();
        } else {
            log_msg(__FUNCTION__,
                    deque_repr(id) + ", position " + to_string(pos) +
                    " bigger than size " +
                    to_string(it->second.size()));
            return NULL;
        }
    }

    void strdeque_clear(unsigned long id) {
        log_params(__FUNCTION__, to_string(id));

        if (id == emptystrdeque()) {
            log_msg(__FUNCTION__, "attempt to clear the Empty Deque");
            return;
        }

        auto it = get_deque_iter(id);
        if (!deque_exists(it)) {
            log_msg(__FUNCTION__, deque_repr(id) + " does not exist");
            return;
        }

        it->second.clear();

        log_msg(__FUNCTION__, deque_repr(id) + " cleared");
        return;
    }

    int strdeque_comp(unsigned long id1, unsigned long id2) {
        log_params(__FUNCTION__, to_string(id1) + ", " + to_string(id2));

        auto it1 = get_deque_iter(id1);
        auto it2 = get_deque_iter(id2);

        if (!deque_exists(it1)) {
            log_msg(__FUNCTION__, deque_repr(id1) + " does not exist");
            it1 = get_deque_iter(emptystrdeque());
        }

        if (!deque_exists(it2)) {
            log_msg(__FUNCTION__, deque_repr(id2) + " does not exist");
            it2 = get_deque_iter(emptystrdeque());
        }

        const auto& deque1 = it1->second;
        const auto& deque2 = it2->second;

        int result;
        if (deque1 == deque2)
            result = 0;
        else if (deque1 > deque2)
            result = 1;
        else
            result = -1;

        log_msg(__FUNCTION__,
                "result of comparing " + deque_repr(id1) + " to " +
                deque_repr(id2) + " is " + to_string(result));
        return result;
    }

}
