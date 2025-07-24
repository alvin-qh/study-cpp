#include "oop/constructor.h"

namespace cxx::oop {

    Constructor::Constructor() noexcept : Constructor(0) { }

    Constructor::Constructor(double value) noexcept : _val(value) { }

    Constructor::Constructor(int int_part, uint32_t dec_part) noexcept {
        double dec = 0;
        while (dec_part > 0) {
            uint32_t n = dec_part % 10;
            dec_part /= 10;
            dec = (dec * 0.1) + (n * 0.1);
        }
        _val = int_part + dec;
    }

    Constructor::Constructor(const nothing_t&, std::initializer_list<double> list) noexcept {
        double dec = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            dec += *it;
        }
        _val = dec;
    }

    Constructor::Constructor(std::string&& val) {
        // 本代码仅为演示参数 `val` 被移动,
        // 正常情况下字符串转数值无需使用移动语意
        std::string s(std::move(val));
        _val = std::stod(s);
    }

    Constructor::Constructor(const std::string& val) :_val(std::stod(val)) { }

    Constructor::Constructor(const Constructor& o) noexcept : _val(o._val) { }

    Constructor::Constructor(Constructor&& o) noexcept
        : _val(std::exchange(o._val, 0)) { }

    Constructor::~Constructor() noexcept { }

    double Constructor::value() const noexcept { return _val; }


    Constructor make_constructor(double value) noexcept {
        // 直接返回 `double` 值, 自动调用 `Constructor(double)` 构造器
        return value;
    }

    Constructor make_constructor(int int_part, uint32_t dec_part) noexcept {
        // 直接返回 "value list", 自动调用 `Constructor(int, uint_32)` 构造器
        return { int_part, dec_part };
    }

    Constructor make_constructor(std::string&& s) {
        // 必须显式调用构造器构造返回值对象
        return Constructor(std::move(s));
    }

    Constructor make_constructor(const std::string& s) {
        // 必须显式调用构造器构造返回值对象
        return Constructor(s);
    }

} // namespace cxx::oop
