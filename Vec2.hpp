#ifndef _VEC2_H_
#define _VEC2_H_

#include <cmath>

/// @brief Classe simple décrivant un vecteur de R²
class Vec2
{
	public:
		float x; ///< Composante x
		float y; ///< Composante y

		inline Vec2() : x(0.f), y(0.f) {}
		inline Vec2(float newX, float newY) : x(newX), y(newY) {}
		inline ~Vec2() {}

		// inline Vec2(const sf::Vector2f& V) : x(V.x), y(V.y) {}

		inline float getLength() { return sqrt(x*x + y*y); }
		inline float getSquaredLength() { return x*x + y*y; }
		inline Vec2 getNormalized() { return *this/getLength(); }
		inline void normalize() { *this /= getLength(); }
		inline Vec2 getOrthogonal() { return Vec2(-y, x); }

		inline float getAngle()
		{
			Vec2 V = getNormalized();
			return acos(V.x)*((V.y > 0.f) ? 1 : -1);
		}

		inline float getAngle(Vec2 V)
		{
			Vec2 N = getNormalized();
			V.normalize();
			return acos(N*V)*((N.getOrthogonal()*V > 0.f) ? 1 : -1);
		}

		inline Vec2& operator+=(const Vec2& V)
		{
			x += V.x;
			y += V.y;
			return *this;
		}

		inline Vec2& operator-=(const Vec2& V)
		{
			x -= V.x;
			y -= V.y;
			return *this;
		}

		inline Vec2& operator*=(const float& f)
		{
			x *= f;
			y *= f;
			return *this;
		}

		inline Vec2& operator/=(const float& f)
		{
			x /= f;
			y /= f;
			return *this;
		}

		inline friend Vec2 operator-(const Vec2& V) { return Vec2(-V.x, -V.y); }
		inline friend Vec2 operator+(const Vec2& V1, const Vec2& V2) { return Vec2(V1.x + V2.x, V1.y + V2.y); }
		inline friend Vec2 operator-(const Vec2& V1, const Vec2& V2) { return Vec2(V1.x - V2.x, V1.y - V2.y); }
		inline friend Vec2 operator*(const Vec2& V, const float& f) { return Vec2(V.x*f, V.y*f); }
		inline friend Vec2 operator*(const float& f, const Vec2& V) { return Vec2(V.x*f, V.y*f); }
		inline friend Vec2 operator/(const Vec2& V, const float& f) { return Vec2(V.x/f, V.y/f); }
		/// @brief Produit scalaire
		inline friend float operator*(const Vec2& V1, const Vec2& V2) { return (V1.x*V2.x + V1.y*V2.y); }

		inline friend bool operator==(const Vec2& V1, const Vec2& V2) { return (V1.x == V2.x && V1.y == V2.y); }
		inline friend bool operator!=(const Vec2& V1, const Vec2& V2) { return (V1.x != V2.x || V1.y != V2.y); }
		/// @brief Teste les normes
		inline friend bool operator>(Vec2& V1, Vec2& V2) { return (V1.getSquaredLength() > V2.getSquaredLength()); }
		/// @brief Teste les normes
		inline friend bool operator<(Vec2& V1, Vec2& V2) { return (V1.getSquaredLength() < V2.getSquaredLength()); }
		/// @brief Teste les normes
		inline friend bool operator>=(Vec2& V1, Vec2& V2) { return (V1.getSquaredLength() >= V2.getSquaredLength()); }
		inline friend bool operator<=(Vec2& V1, Vec2& V2) { return (V1.getSquaredLength() <= V2.getSquaredLength()); }
};

#endif
