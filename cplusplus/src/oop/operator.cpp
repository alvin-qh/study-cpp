#include "oop/operator.hpp"

namespace cpp::oop {
	using namespace std;

	Operator::Operator() : Operator(0, 0, 0) {}

	Operator::Operator(double x, double y, double z) :_x(x), _y(y), _z(z) {}

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

} // ! namespace cpp::oop
