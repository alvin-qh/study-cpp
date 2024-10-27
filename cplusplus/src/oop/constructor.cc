#include "oop/constructor.h"

namespace cxx::oop {

    Constructor::Constructor() noexcept : Constructor(0) {}

    Constructor::Constructor(double value) noexcept : _val(value) {}

    Constructor::Constructor(std::string&& val) : _val(std::stod(val)) {}

    Constructor::Constructor(const std::string& val) :_val(std::stod(val)) {}

    Constructor::~Constructor() noexcept {}

    double Constructor::value() const noexcept { return _val; }

} // ! namespace cxx::oop
