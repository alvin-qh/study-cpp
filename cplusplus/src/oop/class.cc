#include <cmath>

#include "oop/class.h"

namespace cxx::oop {

    // 在默认构造器中调用参数构造器
    AClass::AClass() : AClass(0) { }

    AClass::AClass(int value) : _value(value) {
        // 另一种形式的成员变量赋值
        // _value = value;
    }

    // 在拷贝构造器中调用参数构造器
    AClass::AClass(const AClass& o) : AClass(o._value) { }

    AClass::~AClass() { }

    AClass& AClass::operator=(const AClass& o) {
        _value = o._value;
        return *this;
    }

    bool AClass::operator==(const AClass& o) const { return _value == o._value; }

#if !__ge_cxx20
    bool AClass::operator!=(const AClass& o) const { return !(*this == o); }
#endif

    void AClass::set_value(int value) { _value = value; }

    double AClass::value() const { return _value; }

} // namespace cxx::oop
