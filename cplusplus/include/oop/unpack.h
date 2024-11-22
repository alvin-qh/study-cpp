#pragma once

#ifndef __CPLUSPLUS_OPP__UNPACK_H
#define __CPLUSPLUS_OPP__UNPACK_H

#if __ge_cxx17

namespace cxx::oop {

	/// @brief 定义结构体, 演示 unpack 操作
	struct Unpack {
		double x, y, z;
		int data[3];
	};

} // namespace cxx::oop

#endif // __ge_cxx17
#endif // __CPLUSPLUS_OPP__UNPACK_H
