#include "oop/const.h"

namespace cxx::oop {

    Constant::Constant(const string& value) :
        _val(value),
        _ref(value + "-r"),
        _ptr(value + "-p") {
    }

    string Constant::to_string() const { return "Constant(" + _val + ")"; }

    Constant& Constant::set(const string& value) {
        _val = value;
        _ref = value + "-r";
        _ptr = value + "-p";
        return *this;
    }

    string Constant::value() { return _val; }

    const string Constant::value() const { return _val; }

    string* Constant::ptr() { return &_ptr; }

    const string* Constant::ptr() const { return &_ptr; }

    string& Constant::ref()& { return _ref; }

    const string& Constant::ref() const& { return _ref; }

} // ! namespace cxx::oop
