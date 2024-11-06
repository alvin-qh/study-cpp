#include "oop/enumclass.h"

namespace cxx::oop {
    using namespace std;

    // -------------------------------------------------------------------

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

    optional<__enum_value> ImitationEnum::from_string(const string& name) {
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
