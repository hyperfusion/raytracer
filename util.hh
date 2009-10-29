#ifndef __UTIL_HH__
#define __UTIL_HH__

#include <cmath>
using std::sqrt;

#include <ostream>
using std::ostream;
using std::endl;

/**
 * The following are ugly macros that take care of generating default
 * getters and setters for private fields.
 * ATTR is used for 
 */

#define ATTR(type, name)                        \
    void name(type name) { _##name = name; }    \
    type name() const { return _##name; }

#define REF_ATTR(type, name)                           \
    void name(const type &name) { _##name = name; }    \
    type &name() { return _##name; }                   \
    const type &name() const { return _##name; }



#endif // __UTIL_HH__
