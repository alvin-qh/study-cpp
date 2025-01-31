#include "oop/const.h"

namespace cxx::oop {
    using namespace std;

    // ------------------------------------------------------------------------------------------------------------

    // 对头文件中 `ConstField` 类的静态只读字段进行初始化;
    const string ConstField::CS_STR_2 = "BB";

    // ------------------------------------------------------------------------------------------------------------

    ConstMethod::ConstMethod(const string& value) :
        _val(value),
        _ref(value + "-r"),
        _ptr(value + "-p") { }

    string ConstMethod::to_string() const {
        return "Constant(" + _val + ")";
    }

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

} // namespace cxx::oop
