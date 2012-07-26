#pragma once

#include <vector>

#include <Math.hpp>
#include <Vec2.hpp>

class Bezier2D
{
	private:
		std::vector<Vec2> ControlPoints;
		std::vector<Vec2> Points;

	public:
		Bezier2D(std::vector<Vec2>& Data, unsigned int nbPoints = 100) :
			ControlPoints(Data)
		{
			compute(nbPoints);
		}
		~Bezier2D() {}

		void compute(unsigned int nbPoints = 100)
		{
			Points.clear();
			Points.reserve(nbPoints);
			for(unsigned int i(0); i < nbPoints; i++)
			{
				Vec2 P(0, 0);
				for(unsigned int j(0); j < ControlPoints.size(); j++)
					P += ControlPoints[j]*berstein(ControlPoints.size() - 1, j,
						static_cast<float>(i)/static_cast<float>(nbPoints));
				Points.push_back(P);
			}
		}

		unsigned int getControlPointCount() { return ControlPoints.size(); }
		unsigned int getPointCount() { return Points.size(); }

		Vec2 get(unsigned int nPoint) { return Points[std::min(nPoint, Points.size() - 1)]; }
		Vec2 operator[](unsigned int nPoint) { return Points[std::min(nPoint, Points.size() - 1)]; }
		Vec2 operator()(unsigned int nPoint) { return ControlPoints[std::min(nPoint, ControlPoints.size() - 1)]; }

		Bezier2D& operator+=(Vec2 V) { ControlPoints.push_back(V); }

		void reset() { ControlPoints.clear(); }

		Vec2 getDelta(unsigned int nPoint) {
			if(nPoint >= Points.size() || nPoint == 0)
				return Vec2(0, 0);
			return Points[nPoint] - Points[nPoint - 1];
		}

		Vec2 get(float t)
		{
			if(t < 0.f) t = 0.f;
			while(t > 1.f) t /= 100.f;
			return Points[static_cast<unsigned int>(t*Points.size())];
		}
};
