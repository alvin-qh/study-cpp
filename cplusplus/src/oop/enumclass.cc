#include "oop/enumclass.h"

namespace cxx::oop {
    using namespace std;

    // -------------------------------------------------------------------

#if __ge_cxx17
    optional<string> color_to_rgb(Color c) {
#else
    string color_to_rgb(Color c) {
#endif
        switch (c) {
        case Color::Red:
            return COLOR_RED;
        case Color::Green:
            return COLOR_GREEN;
        case Color::Blue:
            return COLOR_BLUE;
        default:
            return nullopt_or("");
        }
    }

    // -------------------------------------------------------------------

#if __ge_cxx17
    optional<string> gender_to_string(Gender g) {
#else
    string gender_to_string(Gender g) {
#endif
        switch (g) {
        case Gender::Male:
            return GENDER_MALE;
        case Gender::Female:
            return GENDER_FEMALE;
        default:
            return nullopt_or("");
        }
    }

#if __ge_cxx17
    optional<Gender> string_to_gender(const string & s) {
#else
    Gender string_to_gender(const string & s) {
#endif
        if (s == GENDER_MALE) {
            return Gender::Male;
        }
        if (s == GENDER_FEMALE) {
            return Gender::Female;
        }
        return nullopt_or(Gender::Unknown);
    }

    // -------------------------------------------------------------------

#if __ge_cxx17
    optional<__enum_value> ImitationEnum::from_string(const string & name) {
        if (name == A.name()) {
            return A;
        }
        if (name == B.name()) {
            return B;
        }
        if (name == C.name()) {
            return C;
        }
        return nullopt;
    }
#else
    // 当 C++ 版本低于 17, 类中定义的 `static` 类型变量需要代码文件中进行声明
    constexpr __enum_value ImitationEnum::A;
    constexpr __enum_value ImitationEnum::B;
    constexpr __enum_value ImitationEnum::C;
    constexpr __enum_value ImitationEnum::None;

    __enum_value ImitationEnum::from_string(const string & name) {
        if (name == A.name()) {
            return A;
        }
        if (name == B.name()) {
            return B;
        }
        if (name == C.name()) {
            return C;
        }
        return None;
    }
#endif

    } // namespace cxx::oop
