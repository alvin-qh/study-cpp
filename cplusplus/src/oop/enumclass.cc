#include "oop/enumclass.h"

namespace cxx::oop {
    using namespace std;

    optional<string> color_to_rgb(Color c) {
        switch (c) {
        case Color::Red:
            return COLOR_RED;
        case Color::Green:
            return COLOR_GREEN;
        case Color::Blue:
            return COLOR_BLUE;
        default:
            return nullopt;
        }
    }

    // -------------------------------------------------------------------

    optional<string> gender_to_string(Gender g) {
        switch (g) {
        case Gender::Male:
            return GENDER_MALE;
        case Gender::Female:
            return GENDER_FEMALE;
        default:
            return nullopt;
        }
    }

    optional<Gender> string_to_gender(const string& s) {
        if (s == GENDER_MALE) {
            return Gender::Male;
        }
        if (s == GENDER_FEMALE) {
            return Gender::Female;
        }
        return nullopt;
    }

    // -------------------------------------------------------------------

    const ImitationEnum::__enum_value ImitationEnum::A("A", 1);

    const ImitationEnum::__enum_value ImitationEnum::B("B", 2);

    const ImitationEnum::__enum_value ImitationEnum::C("C", 3);

    ImitationEnum::__enum_value::__enum_value(const string& name, int value) :
        _name(name), _value(value) {
    }

    const string& ImitationEnum::__enum_value::name() const {
        return _name;
    }

    int ImitationEnum::__enum_value::value() const {
        return _value;
    }

    ImitationEnum::__enum_value::operator int() const {
        return _value;
    }

    ImitationEnum::__enum_value::operator string() const {
        return _name;
    }

    ImitationEnum::__enum_value::operator const string& () const {
        return _name;
    }

    ImitationEnum::__enum_value::operator const char* () const {
        return _name.c_str();
    }

    optional<ImitationEnum::__enum_value>
        ImitationEnum::from_string(const string& name) {
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

} // ! namespace cxx::oop
