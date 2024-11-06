#include "oop/const.h"

namespace cxx::oop {


    // ------------------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------------------

    ConstMethod::ConstMethod(const string& value) :
        _val(value),
        _ref(value + "-r"),
        _ptr(value + "-p") {
    }

    string ConstMethod::to_string() const { return "Constant(" + _val + ")"; }

    ConstMethod& ConstMethod::set(const string& value) {
        _val = value;
        _ref = value + "-r";
        _ptr = value + "-p";
        return *this;
    }

    string ConstMethod::value() { return _val; }

    const string ConstMethod::value() const { return _val; }

    string* ConstMethod::ptr() { return &_ptr; }

    const string* ConstMethod::ptr() const { return &_ptr; }

    string& ConstMethod::ref()& { return _ref; }

    const string& ConstMethod::ref() const& { return _ref; }

} // ! namespace cxx::oop
