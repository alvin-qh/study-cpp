#pragma once

#ifndef __CPLUSPLUS_OOP_CLASS_H
#define __CPLUSPLUS_OOP_CLASS_H

namespace cpp {
	/// @brief 定义 2D 向量类
	class Vector2D {
	protected:
		double _x;
		double _y;
		uint32_t* __destroy_count;

	public:
		/// @brief 默认构造器
		Vector2D();

		/// @brief 参数构造器
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		Vector2D(double x, double y);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		Vector2D(const Vector2D& o);

		/// @brief 析构函数
		///
		/// 析构函数一般声明为 `virtual`,
		/// 表示其为一个虚函数,
		/// 这样当前类的子类的析构函数调用时,
		/// 也会调用父类的析构函数
		virtual ~Vector2D();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		Vector2D& operator=(const Vector2D& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const Vector2D& o) const;

		/// @brief 设置析构数量记录变量指针
		///
		/// @param destroy_count 整数变量指针
		inline void __set_destroy_count_ref(uint32_t* destroy_count) {
			this->__destroy_count = destroy_count;
		}

		/// @brief 获取 `_x` 字段值
		///
		/// @return `x` 坐标值
		inline double x() const { return this->_x; };

		/// @brief 获取 `_y` 字段值
		///
		/// @return `y` 坐标值
		inline double y() const { return this->_y; };

		/// @brief 重新设置成员变量的值
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		inline void set(double x, double y) {
			_x = x;
			_y = y;
		}

		/// @brief 计算向量长度
		///
		/// @return 向量长度
		virtual double length() const;
	};

	/// @brief 定义 3D 向量类
	class Vector3D : public Vector2D {
	private:
		double _z;
	public:
		/// @brief 默认构造器
		Vector3D();

		/// @brief 参数构造器
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		Vector3D(double x, double y, double z);

		/// @brief 拷贝构造器
		///
		/// @param o 另一个同类型对象
		Vector3D(const Vector3D& o);

		/// @brief 析构函数
		virtual ~Vector3D();

		/// @brief 重载赋值运算符
		///
		/// @param o 另一个同类型对象
		/// @return 当前对象的引用
		Vector3D& operator=(const Vector3D& o);

		/// @brief 重载判等运算符
		///
		/// @param o 另一个同类型对象
		/// @return 两个对象是否相同
		bool operator==(const Vector3D& o) const;

		/// @brief 令 `Vector3D` 实例和 `Vector2D` 不相等
		///
		/// @return 不相等
		inline bool operator==(const Vector2D&) const { return false; }

		/// @brief 重新设置成员变量的值
		///
		/// @param x `x` 坐标值
		/// @param y `y` 坐标值
		/// @param z `z` 坐标值
		inline void set(double x, double y, double z) {
			Vector2D::set(x, y);
			_z = z;
		}

		/// @brief 获取 `_z` 字段值
		///
		/// @return `z` 坐标的值
		inline double z() const { return _z; };

		/// @brief 计算向量长度
		///
		/// @return 向量长度
		virtual double length() const override;
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_CLASS_H
