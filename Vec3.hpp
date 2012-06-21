#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <cmath>

class Vec3
{
	public:
		float x, y, z;

		inline Vec3() : x(0), y(0), z(0) {}
		inline Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
		inline ~Vec3() {}

		inline Vec3& operator+=(const Vec3& V)
		{
			x += V.x;
			y += V.y;
			z += V.z;
			return *this;
		}
		inline Vec3 operator+(const Vec3& V2) { return Vec3(x + V2.x, y + V2.y, z + V2.z); }
		inline friend Vec3 operator+(const Vec3& V1, const Vec3& V2)
		{
			return Vec3(V1.x + V2.x, V1.y + V2.y, V1.z + V2.z);
		}

		inline Vec3& operator-=(const Vec3& V)
		{
			x -= V.x;
			y -= V.y;
			z -= V.z;
			return *this;
		}
		inline friend Vec3 operator-(const Vec3& V1, const Vec3& V2)
		{
			return Vec3(V1.x - V2.x, V1.y - V2.y, V1.z - V2.z);
		}
		inline Vec3 operator-(const Vec3& V)
		{
			return Vec3(x - V.x, y - V.y, z - V.z);
		}
		inline Vec3 operator-()
		{
			return Vec3(-x, -y, -z);
		}

		inline Vec3& operator*=(const float S)
		{
			x *= S;
			y *= S;
			z *= S;
			return *this;
		}
		inline friend Vec3 operator*(const Vec3& V, float S) { return Vec3(V.x*S, V.y*S, V.z*S); }
		inline friend Vec3 operator*(float S, const Vec3& V) { return Vec3(V.x*S, V.y*S, V.z*S); }

		inline Vec3& operator/=(const float S)
		{
			x /= S;
			y /= S;
			z /= S;
			return *this;
		}
		inline friend Vec3 operator/(const Vec3& V, float S) { return Vec3(V.x/S, V.y/S, V.z/S); }

		inline friend float operator*(const Vec3& V1, const Vec3& V2) { return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z; }
		inline friend Vec3 operator%(const Vec3& V1, const Vec3& V2) { return Vec3(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x); }

		inline friend bool operator==(const Vec3& V1, const Vec3& V2) { return V1.x == V2.x && V1.y == V2.y && V1.z == V2.z; }
		inline friend bool operator!=(const Vec3& V1, const Vec3& V2) { return !(V1.x == V2.x && V1.y == V2.y && V1.z == V2.z); }

		inline friend bool operator>(Vec3& V1, Vec3& V2) { return V1.getLength() > V2.getLength(); }
		inline friend bool operator<(Vec3& V1, Vec3& V2) { return V1.getLength() < V2.getLength(); }
		inline friend bool operator>=(Vec3& V1, Vec3& V2) { return V1.getLength() >= V2.getLength(); }
		inline friend bool operator<=(Vec3& V1, Vec3& V2) { return V1.getLength() <= V2.getLength(); }

		inline float getLength() { return sqrt(x*x + y*y + z*z); }
		inline float getSqLength() { return x*x + y*y + z*z; }
		inline Vec3 getNormalized() { return *this/(this->getLength()); }
};

#endif
