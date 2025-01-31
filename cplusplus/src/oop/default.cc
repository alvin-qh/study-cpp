#include "oop/default.h"

namespace cxx::oop {
    using namespace std;

    Default::Default() : Default("") { }

    Default::Default(const string& name) : _name(name) { }

    bool Default::operator==(const Default& o) const { return _name == o._name; }

    const string& Default::name() const { return _name; }

} // namespace cxx::oop
