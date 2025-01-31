#include <utility>

#include "oop/operator.h"

namespace cxx::oop {
    using namespace std;

    Operator::Operator() : Operator(0, 0, 0) { }

    Operator::Operator(double x, double y, double z) :
        _x(x), _y(y), _z(z) { }

    Operator& Operator::operator=(Operator&& right) noexcept {
        if (this != &right) {
            _x = exchange(right._x, 0);
            _y = exchange(right._y, 0);
            _z = exchange(right._z, 0);
        }
        return *this;
    }

    Operator Operator::operator+(const Operator& right) const {
        return Operator(
            _x + right._x,
            _y + right._y,
            _z + right._z
        );
    }

    Operator Operator::operator*(double scalar) const {
        return Operator(
            _x * scalar,
            _y * scalar,
            _z * scalar
        );
    }

    double Operator::operator*(const Operator& right) const {
        return _x * right._x + _y * right._y + _z * right._z;
    }

    double Operator::operator[](int index) const {
        switch (index) {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            throw std::out_of_range("Index out of range");
        }
    }

    double Operator::x() const { return _x; }
    double Operator::y() const { return _y; }
    double Operator::z() const { return _z; }

    Operator& Operator::operator++() noexcept {
        ++_x;
        ++_y;
        ++_z;
        return *this;
    }

    Operator Operator::operator++(int) noexcept {
        Operator tmp = *this;
        ++(*this);
        return tmp;
    }

    Operator& Operator::operator--() noexcept {
        --_x;
        --_y;
        --_z;
        return *this;
    }

    Operator Operator::operator--(int) noexcept {
        Operator tmp = *this;
        --(*this);
        return tmp;
    }

    Operator Operator::operator+(const tuple<double, double, double>& r) const noexcept {
        return Operator(
            _x + get<0>(r),
            _y + get<1>(r),
            _z + get<2>(r)
        );
    }

    Operator Operator::operator-(const tuple<double, double, double>& r) const noexcept {
        return Operator(
            _x - get<0>(r),
            _y - get<1>(r),
            _z - get<2>(r)
        );
    }

    bool Operator::operator==(const Operator& right) const noexcept {
        if (this == &right) {
            return true;
        }
        return
            _x == right._x &&
            _y == right._y &&
            _z == right._z;
    }

#if __ge_cxx20
    partial_ordering Operator::operator<=>(const Operator& right) const noexcept {
        partial_ordering ord = _x <=> right._x;

        if (ord != partial_ordering::equivalent) {
            ord = _y <=> right._y;
            if (ord == partial_ordering::equivalent) {
                ord = _z <=> right._z;
            }
        }
        return ord;
    }
#else
    bool Operator::operator<(const Operator& right) const noexcept {
        return
            _x < right._x ||
            (_x == right._x && _y < right._y) ||
            (_x == right._x && _y == right._y && _z < right._z);
    }

    bool Operator::operator<=(const Operator& right) const noexcept {
        return !(*this > right);
    }

    bool Operator::operator>(const Operator& right) const noexcept {
        return
            _x > right._x ||
            (_x == right._x && _y > right._y) ||
            (_x == right._x && _y == right._y && _z > right._z);
    }

    bool Operator::operator>=(const Operator& right) const noexcept {
        return !(*this < right);
    }

    bool Operator::operator!=(const Operator& right) const noexcept {
        return !(*this == right);
    }
#endif // __ge_cxx20

    Operator operator-(const Operator& left, const Operator& right) {
        return Operator(
            left._x - right._x,
            left._y - right._y,
            left._z - right._z
        );
    }

    Operator operator+(const std::tuple<double, double, double>& left, const Operator& right) {
        return Operator(
            get<0>(left) + right._x,
            get<1>(left) + right._y,
            get<2>(left) + right._z
        );
    }

    Operator operator-(const std::tuple<double, double, double>& left, const Operator& right) {
        return Operator(
            get<0>(left) - right._x,
            get<1>(left) - right._y,
            get<2>(left) - right._z
        );
    }

    OperatorChild::OperatorChild() : Operator() { }

    OperatorChild::OperatorChild(double x, double y, double z) : Operator(x, y, z) { }

} // namespace cxx::oop
