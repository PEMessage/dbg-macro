#ifndef DBG_MACRO_DBG_EX_H
#define DBG_MACRO_DBG_EX_H
#include "result.hpp"
#include <string>

namespace dbg {
// These forward declaration must be declare before dbg.h included
template <typename T, typename E>
inline bool pretty_print(std::ostream& stream, const cpp::result<T,E>& value);

template <typename E>
inline bool pretty_print(std::ostream& stream, const cpp::failure<E>& value);
}

#include "dbg.h"

namespace dbg {
// Add type_name specializations for result and failure
template <typename T, typename E>
std::string get_type_name(type_tag<cpp::result<T,E>>) {
    return "result<" + type_name<T>() + ", " + type_name<E>() + ">";
}

template <typename E>
std::string get_type_name(type_tag<cpp::failure<E>>) {
    return "failure<" + type_name<E>() + ">";
}

template <typename T, typename E>
inline bool pretty_print(std::ostream& stream, const cpp::result<T,E>& value) {
    if (value.has_value()) {
        if constexpr (!std::is_void_v<T>) {
            stream << "result{value: ";
            pretty_print(stream, *value);
        } else {
            (void)(value);
            stream << "result{void";
        }
    } else {
        stream << "result{error: ";
        pretty_print(stream, value.error());
    }
    stream << "}";
    return true;
}

template <typename E>
inline bool pretty_print(std::ostream& stream, const cpp::failure<E>& value) {
    stream << "failure{";
    pretty_print(stream, value.error());
    stream << "}";
    return true;
}


} // namespace dbg
#endif // #ifndef DBG_MACRO_DBG_H

