#pragma once

#ifndef __CPLUSPLUS_TEMPLATE_TRAITS_H
#define __CPLUSPLUS_TEMPLATE_TRAITS_H

namespace cpp::temp {

	template <typename _Child>
	struct __traits_provider {
		using __self = __traits_provider<_Child>;
		using __child = _Child;
	private:
		size_t _count;
	public:
		__traits_provider() : __traits_provider(0) {}

		__traits_provider(const __self& o) : _count(o._count) {}

		__traits_provider(size_t count) : _count(count) {}

		__self& operator=(const __self& o) noexcept {
			_count = o._count;
			return *this;
		}

		std::strong_ordering operator<=>(const __self& o) const noexcept { return _count <=> o._count; }

		bool operator==(const __self& o) const noexcept { return _count == o._count; }

		__self& operator++() noexcept {
			++_count;
			return *static_cast<__self*>(this);
		}

		__self operator++(int) noexcept {
			__self tmp = *this;
			++_count;
			return tmp;
		}

		const char* name() const { return _Child::__name; }

		size_t count() const { return _count; }
	};

	class use_traits : public __traits_provider<use_traits> {
		using __base = __traits_provider<use_traits>;
		using __base::operator=;
	public:
		constexpr static const char* __name = "UseTraits";

		use_traits() : __base() {}

		use_traits(const use_traits& o) : __base(o) {}
	};

}

#endif  // __CPLUSPLUS_TEMPLATE_TRAITS_H
