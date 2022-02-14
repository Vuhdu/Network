#pragma once
#include "Vector3.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"
#include <vector>

namespace CommonUtilities
{

	// If the ray is parallel to the plane, aOutIntersectionPoint remains unchanged. If
	// the ray is in the plane, true is returned, if not, false is returned. If the ray
	// isn't parallel to the plane, the intersection point is stored in
	// aOutIntersectionPoint and true returned.
	template<class T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T rayDirDotNormalSquare = aRay.myDirection.Dot(aPlane.GetNormal()) * aRay.myDirection.Dot(aPlane.GetNormal());
		
		if (rayDirDotNormalSquare < 0.0001)
		{
			Vector3<T> rayPointToPlanePoint = aRay.myOrigin - aPlane.GetPoint();
			T scalar = rayPointToPlanePoint.Dot(aPlane.GetNormal()) * rayPointToPlanePoint.Dot(aPlane.GetNormal());
			
			if(scalar < 0.0001)
			{
				return true;
			}

			return false;
		}

		T d = aPlane.GetPoint().Dot(aPlane.GetNormal());

		T t = (d - aRay.myOrigin.Dot(aPlane.GetNormal())) / (aRay.myDirection.Dot(aPlane.GetNormal()));

		if (t >= 0)
		{
			aOutIntersectionPoint = aRay.myOrigin + aRay.myDirection * t;

			return true;
		}

		return false;
	
	}
		
	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// A ray in one of the AABB's sides is counted as intersecting it.
	template<class T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{
		if (aAABB.IsInside(aRay.myOrigin))
		{
			return true;
		}
	
		Vector3<T> min = aAABB.myMin;
		Vector3<T> max = aAABB.myMax;

		Vector3<T> c1 = min;
		Vector3<T> c2 = { min.x, min.y, max.z };
		Vector3<T> c3 = { min.x, max.y, max.z };
		Vector3<T> c4 = { min.x, max.y, min.z };
		Vector3<T> c5 = { max.x, min.y, min.z };
		Vector3<T> c6 = { max.x, max.y, min.z };
		Vector3<T> c7 = { max.x, min.y, max.z };
		Vector3<T> c8 = max;

		Vector3<T> intersectionPoint;

		std::vector<Plane<T>> planeVector;

		planeVector.emplace_back(c1, c3, c4);
		planeVector.emplace_back(c3, c4, c8);
		planeVector.emplace_back(c1, c4, c6);
		planeVector.emplace_back(c2, c3, c8);
		planeVector.emplace_back(c1, c2, c5);
		planeVector.emplace_back(c5, c6, c8);

		bool result = false;

		for (int i = 0; i < planeVector.size(); i++)
		{
			if (IntersectionPlaneRay(planeVector[i], aRay, intersectionPoint))
			{
				if (aAABB.IsInside(intersectionPoint))
				{
					return true;
				}
			}
		}
		return false;
	}
		
	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// A ray intersecting the surface of the sphere is considered as intersecting it.
	template<class T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> e = aSphere.myCenter - aRay.myOrigin;
		
		T eDotmyDirection = e.Dot(aRay.myDirection);
		
		if (eDotmyDirection <= 0.0f)
		{
			return false;
		}
			
		Vector3<T> a = aRay.myDirection * eDotmyDirection;

		return (e.LengthSqr() - a.LengthSqr()) <= (aSphere.myRadius * aSphere.myRadius);
	}
}

