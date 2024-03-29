#pragma once
#include "maths/Matrix.h"
#include <cmath>
#include "MathsFunc.h"


namespace maths
{

	template <typename T>
	struct mat4 : public mat<T, 4>
	{
		//Calling parent constructor
		mat4(const T scalar = T())
			:mat<T, 4>{ scalar }
		{};
		mat4(const mat<T, 4> rhs)
			: mat<T, 4>(rhs) {}

		//Matrix Rotation
		static inline mat4<T> RotateXMat(const T rad);
		static inline mat4<T> RotateYMat(const T rad);
		static inline mat4<T> RotateZMat(const T rad);
		static inline mat4<T> RotateMat(const T rad, const vec3<T>& axis);
		static inline mat4<T> RotateMat(const T rad, const T x, const T y, T const z);
		inline vec3f MultiplyByVec3f(const vec3f& rhs);
		inline void Rotate(const T rad, const vec3<T>& axis);
		inline void Rotate(const T rad, const T x, const T y, T const z);
		inline void Translate(const T x, const T y, const T z);
		inline void Translate(const vec3<T> vec);
		inline void RotateX(const T rad);
		inline void RotateY(const T rad);
		inline void RotateZ(const T rad);

	};


	template <typename T>
	static inline vec4<T> times(mat4<T> thi, const vec4<T> rhs)
	{
		vec4<T> ans;
		ans.x = thi.elements[0] * rhs.x + thi.elements[4] * rhs.y + thi.elements[8] * rhs.z + thi.elements[12] * rhs.w;
		ans.y = thi.elements[1] * rhs.x + thi.elements[5] * rhs.y + thi.elements[9] * rhs.z + thi.elements[13] * rhs.w;
		ans.z = thi.elements[2] * rhs.x + thi.elements[6] * rhs.y + thi.elements[10] * rhs.z + thi.elements[14] * rhs.w;
		ans.w = thi.elements[3] * rhs.x + thi.elements[7] * rhs.y + thi.elements[11] * rhs.z + thi.elements[15] * rhs.w;
		return ans;
	}
	template <typename T>
	inline mat4<T> mat4<T>::RotateXMat(const T rad)
	{

		const T sinTheta = sin(rad);
		const T cosTheta = cos(rad);

		mat4<T> ans;
		ans.elements[0] = (T)1;
		ans.elements[1] = (T)0;
		ans.elements[2] = (T)0;
		ans.elements[3] = (T)0;
		ans.elements[4] = (T)0;
		ans.elements[5] = (T)cosTheta;
		ans.elements[6] = (T)sinTheta;
		ans.elements[7] = (T)0;
		ans.elements[8] = (T)0;
		ans.elements[9] = (T)-sinTheta;
		ans.elements[10] = (T)cosTheta;
		ans.elements[11] = (T)0;
		ans.elements[12] = (T)0;
		ans.elements[13] = (T)0;
		ans.elements[14] = (T)0;
		ans.elements[15] = (T)1;

		return ans;
	};

	template <typename T>
	inline mat4<T> mat4<T>::RotateYMat(const T rad)
	{

		const T sinTheta = sin(rad);
		const T cosTheta = cos(rad);

		mat4<T> ans;
		ans.elements[0] = (T)cosTheta;
		ans.elements[1] = (T)0;
		ans.elements[2] = (T)sinTheta;
		ans.elements[3] = (T)0;
		ans.elements[4] = (T)0;
		ans.elements[5] = (T)1;
		ans.elements[6] = (T)0;
		ans.elements[7] = (T)0;
		ans.elements[8] = (T)-sinTheta;
		ans.elements[9] = (T)0;
		ans.elements[10] = (T)cosTheta;
		ans.elements[11] = (T)0;
		ans.elements[12] = (T)0;
		ans.elements[13] = (T)0;
		ans.elements[14] = (T)0;
		ans.elements[15] = (T)1;

		return ans;
	};

	template <typename T>
	inline mat4<T> mat4<T>::RotateZMat(const T rad)
	{

		const T sinTheta = sin(rad);
		const T cosTheta = cos(rad);

		mat4<T> ans;
		ans.elements[0] = (T)cosTheta;
		ans.elements[1] = (T)sinTheta;
		ans.elements[2] = (T)0;
		ans.elements[3] = (T)0;
		ans.elements[4] = (T)-sinTheta;
		ans.elements[5] = (T)cosTheta;
		ans.elements[6] = (T)0;
		ans.elements[8] = (T)0;
		ans.elements[7] = (T)0;
		ans.elements[8] = (T)0;
		ans.elements[9] = (T)0;
		ans.elements[10] = (T)0;
		ans.elements[11] = (T)0;
		ans.elements[12] = (T)0;
		ans.elements[14] = (T)0;
		ans.elements[15] = (T)1;

		return ans;
	};

	template <typename T>
	inline mat4<T> mat4<T>::RotateMat(const T rad, const vec3<T>& axis)
	{
		mat4 ans(1.0f);

		float r = GetRadians(rad);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		ans.elements[0 + 0 * 4] = x * x * omc + c;
		ans.elements[0 + 1 * 4] = y * x * omc + z * s;
		ans.elements[0 + 2 * 4] = x * z * omc - y * s;
		ans.elements[1 + 0 * 4] = x * y * omc - z * s;
		ans.elements[1 + 1 * 4] = y * y * omc + c;
		ans.elements[1 + 2 * 4] = y * z * omc + x * s;
		ans.elements[2 + 0 * 4] = x * z * omc + y * s;
		ans.elements[2 + 1 * 4] = y * z * omc - x * s;
		ans.elements[2 + 2 * 4] = z * z * omc + c;

		return ans;
	}

	template <typename T>
	inline mat4<T> mat4<T>::RotateMat(const T rad, const T x, const T y, T const z)
	{
		mat4 ans(1.0f);

		float r = GetRadians(rad);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		ans.elements[0 + 0 * 4] = x * x * omc + c;
		ans.elements[0 + 1 * 4] = y * x * omc + z * s;
		ans.elements[0 + 2 * 4] = x * z * omc - y * s;
		ans.elements[1 + 0 * 4] = x * y * omc - z * s;
		ans.elements[1 + 1 * 4] = y * y * omc + c;
		ans.elements[1 + 2 * 4] = y * z * omc + x * s;
		ans.elements[2 + 0 * 4] = x * z * omc + y * s;
		ans.elements[2 + 1 * 4] = y * z * omc - x * s;
		ans.elements[2 + 2 * 4] = z * z * omc + c;

		return ans;
	}

	template<typename T>
	inline vec3f mat4<T>::MultiplyByVec3f(const vec3f& rhs)
	{
		return { (this->elements[0] * rhs.x + this->elements[4] * rhs.y + this->elements[8] * rhs.z + this->elements[12]),
				(this->elements[1] * rhs.x + this->elements[5] * rhs.y + this->elements[9] * rhs.z + this->elements[13]),
				(this->elements[2] * rhs.x + this->elements[6] * rhs.y + this->elements[10] * rhs.z + this->elements[14]) };
	}

	template <typename T>
	static inline mat4<T> Ortho(T left, T right, T top, T bottom, T zNear = -1, T zFar = 1)
	{
		mat4<T> ans((T)1);
		// Creates orthographic projection matrix

		ans.elements[0] = (T)2 / (right - left);
		ans.elements[5] = (T)2 / (top - bottom);
		ans.elements[10] = -(T)2 / (zFar - zNear);
		ans.elements[12] = -(right + left) / (right - left);
		ans.elements[13] = -(top + bottom) / (top - bottom);
		ans.elements[14] = -(zFar + zNear) / (zFar - zNear);

		return ans;
	}

	template <typename T>
	static inline mat4<T> lookAt(vec3<T> pos, vec3<T> target, vec3<T> up)
	{
		// function to convert world space into view space coordinates
		// positive z is pointing towards you
		// positive x is pointing to the right
		// positive y is pointing upwards
		// The axis are being calculated relative to the camera (view space)

		vec3<T> zDir = pos - target;
		vec3<T> positiveZDir = normalize(zDir);
		vec3<T> positiveXDir = normalize(cross(zDir, up));
		vec3<T> positiveYDir = cross(positiveXDir, positiveZDir);
		
		mat4<T> translation((T)1);
		translation.elements[12] = -pos.x;
		translation.elements[13] = -pos.y;
		translation.elements[14] = -pos.z;

		mat4<T> rotation((T)1);
		rotation.elements[0] = positiveXDir.x;
		rotation.elements[4] = positiveXDir.y;
		rotation.elements[8] = positiveXDir.z;

		rotation.elements[1] = positiveYDir.x;
		rotation.elements[5] = positiveYDir.y;
		rotation.elements[9] = positiveYDir.z;

		rotation.elements[2] = positiveZDir.x;
		rotation.elements[6] = positiveZDir.y;
		rotation.elements[10] = positiveZDir.z;

		return rotation * translation;
	}


	template <typename T>
	static inline mat4<T> Perspective(T fov, T aspectRatio, T zNear, T zFar)
	{
		mat4<T> ans(0);
		
		float cotHalfFOV = (T)1 / tan(GetRadians((T)0.5 * fov));
		
		ans.elements[0] = cotHalfFOV / aspectRatio;
		ans.elements[5] = cotHalfFOV;
		ans.elements[10] = (zNear + zFar) / (zNear - zFar);
		ans.elements[11] = -(T)1;
		ans.elements[14] = ((T)2 * zNear * zFar) / (zNear - zFar);
		
		return ans;
	}

	template <typename T>
	inline mat4<T> TranslateMat(const T x, const T y, const T z)
	{
		mat4<T> ans((T)1);
		ans.elements[12] = x;
		ans.elements[13] = y;
		ans.elements[14] = z;

		return ans;
	}

	template <typename T>
	inline mat4<T> TranslateMat(const vec3<T> vec3)
	{
		mat4<T> ans((T)1);
		ans.elements[12] = vec3.x;
		ans.elements[13] = vec3.y;
		ans.elements[14] = vec3.z;

		return ans;
	}

	template<typename T>
	inline void mat4<T>::Rotate(const T rad, const vec3<T>& axis)
	{
		*this =  *this * RotateMat(GetRadians(rad), axis);
	}

	template<typename T>
	inline void mat4<T>::Rotate(const T rad, const T x, const T y, T const z)
	{
		*this = RotateMat(GetRadians(rad), x, y, z) * *this;
	}

	template <typename T>
	inline void mat4<T>::Translate(const T x, const T y, const T z)
	{

		*this = TranslateMat(x, y, z) * *this;
	}

	template <typename T>
	inline void mat4<T>::Translate(const vec3<T> vec)
	{
		*this = TranslateMat(vec) * *this;
	}

	template<typename T>
	inline void mat4<T>::RotateX(const T rad)
	{
		*this = *this * RotateXMat(rad);
	}

	template<typename T>
	inline void mat4<T>::RotateY(const T rad)
	{
		*this = *this * RotateYMat(rad);
	}

	template<typename T>
	inline void mat4<T>::RotateZ(const T rad)
	{
		*this = *this * RotateZMat(rad);
	}

	typedef mat4<int> mat4i;
	typedef mat4<float> mat4f;

}