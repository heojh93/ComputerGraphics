#include "mathclass.h"
#include "intersectionTest.h"
#include "interval.h"
Plane::Plane ()
:normal(0,0,0),
d(0.0)
{

}

Plane::Plane (const vector3& vNormal, double offset)
{
	normal = vNormal;
	d = -offset;
}

Plane::Plane (const vector3& vNormal, const vector3& vPoint)
{
	setPlane(vNormal, vPoint);
}

Plane::Plane (const vector3& vPoint0, const vector3& vPoint1,
	const vector3& vPoint2)
{
	setPlane(vPoint0, vPoint1, vPoint2);
}

double Plane::distance(const vector3& vPoint) const
{
	return normal%vPoint + d;
}

void Plane::setPlane(const vector3& vPoint0, const vector3& vPoint1,
	const vector3& vPoint2)
{
	vector3 kEdge1 = vPoint1 - vPoint0;
	vector3 kEdge2 = vPoint2 - vPoint0;
	normal.cross(kEdge1, kEdge2);
	normal.normalize();
	d = -normal%vPoint0;
}

void Plane::setPlane(const vector3& vNormal, const vector3& vPoint)
{
	normal = vNormal;
	normal .normalize();
	d = -vNormal%vPoint;
}

bool Sphere::isInside(std::vector<Plane>& vol) const
{
	if(vol.size())
	{
		bool bInside=true;
		for(int j=0; j<vol.size(); j++)
		{
			//                  dist= -1
			// --------------   dist=0
			//         |        dist=1
			//  inside |        dist=2
			if(vol[j].distance(center)<radius)
			{
				bInside=false; break;
			}
		}

		if(bInside)	return true;
	}
	return false;
}

std::pair<bool, double> Ray::intersects(const vector3& a,
    const vector3& b, const vector3& c, bool bCCW) const
{
	vector3 normal;
	normal.cross(b-a, c-a);
	normal.normalize();

	if(!bCCW) normal*=-1;

	return Ray::intersects(a,b,c,normal, true, false);
}


std::pair<bool, double> Ray::intersects(const vector3& a,
    const vector3& b, const vector3& c, const vector3& normal,
    bool positiveSide, bool negativeSide) const
{
	const Ray& ray=*this;
    //
    // Calculate intersection with plane.
    //
    double t;
    {
        double denom = normal%ray.direction();

        // Check intersect side
        if (denom > + std::numeric_limits<double>::epsilon())
        {
            if (!negativeSide)
                return std::pair<bool, double>(false, 0);
        }
        else if (denom < - std::numeric_limits<double>::epsilon())
        {
            if (!positiveSide)
                return std::pair<bool, double>(false, 0);
        }
        else
        {
            // Parallel or triangle area is close to zero when
            // the plane normal not normalised.
            return std::pair<bool, double>(false, 0);
        }

        t = normal%(a - ray.origin()) / denom;

        if (t < 0)
        {
            // Intersection is behind origin
            return std::pair<bool, double>(false, 0);
        }
    }

    //
    // Calculate the largest area projection plane in X, Y or Z.
    //
    int i0, i1;
    {
        double n0 = ABS(normal[0]);
        double n1 = ABS(normal[1]);
        double n2 = ABS(normal[2]);

        i0 = 1; i1 = 2;
        if (n1 > n2)
        {
            if (n1 > n0) i0 = 0;
        }
        else
        {
            if (n2 > n0) i1 = 0;
        }
    }

    //
    // Check the intersection point is inside the triangle.
    //
    {
        double u1 = b[i0] - a[i0];
        double v1 = b[i1] - a[i1];
        double u2 = c[i0] - a[i0];
        double v2 = c[i1] - a[i1];
        double u0 = t * ray.direction()[i0] + ray.origin()[i0] - a[i0];
        double v0 = t * ray.direction()[i1] + ray.origin()[i1] - a[i1];

        double alpha = u0 * v2 - u2 * v0;
        double beta  = u1 * v0 - u0 * v1;
        double area  = u1 * v2 - u2 * v1;

        // epsilon to avoid float precision error
        const double EPSILON = 1e-3f;

        double tolerance = - EPSILON * area;

        if (area > 0)
        {
            if (alpha < tolerance || beta < tolerance || alpha+beta > area-tolerance)
                return std::pair<bool, double>(false, 0);
        }
        else
        {
            if (alpha > tolerance || beta > tolerance || alpha+beta < area-tolerance)
                return std::pair<bool, double>(false, 0);
        }
    }

    return std::pair<bool, double>(true, t);
}


std::pair<bool, double> Ray::intersects(const Plane& plane) const
{
	Ray const& ray=*this;

	double denom = plane.normal%ray.direction();

	if (ABS(denom) < std::numeric_limits<double>::epsilon())
    {
        // Parallel
        return std::pair<bool, double>(false, 0);
    }
    else
    {
		double nom = plane.normal%ray.origin() + plane.d;
        double t = -(nom/denom);
        return std::pair<bool, double>(t >= 0, t);
    }
}

std::pair<bool, double> Ray::intersects(const std::vector<Plane>& planes) const
{
	const Ray& ray=*this;

    std::vector<Plane>::const_iterator planeit, planeitend;
    planeitend = planes.end();
    std::pair<bool, double> ret;
    ret.first = false;
    ret.second = -100000;
	interval overlap(-100000, 100000);

    for (planeit = planes.begin(); planeit != planeitend; ++planeit)
    {
        const Plane& plane = *planeit;
        {
            // Test single plane
            std::pair<bool, double> planeRes =
                ray.intersects(plane);
            //if (planeRes.first)
            {
				// is origin outside?
				if (plane.distance(ray.origin())>0)
					overlap&=interval(planeRes.second,100000);
				else
					overlap&=interval(-100000, planeRes.second);

            }
        }
    }

	//printf(">> %f %f:", overlap.start_pt(), overlap.end_pt());
	if (overlap.len()>0)
    {
        ret.first = true;
        ret.second = overlap.start_pt();
    }
	else
	{
		ret.first=false;
	}

    return ret;
}

std::pair<bool, double> Ray::intersects(const Sphere& sphere) const
{
	const Ray& ray=*this;
	const vector3& raydir = ray.direction();
    // Adjust ray origin relative to sphere center
    const vector3& rayorig = ray.origin() - sphere.center;
    double radius = sphere.radius;


    // Mmm, quadratics
    // Build coeffs which can be used with std quadratic solver
    // ie t = (-b +/- sqrt(b*b + 4ac)) / 2a
    double a = raydir%raydir;
    double b = 2 * rayorig%raydir;
    double c = rayorig%rayorig - radius*radius;

    // Calc determinant
    double d = (b*b) - (4 * a * c);
    if (d < 0)
    {
        // No intersection
        return std::pair<bool, double>(false, 0);
    }
    else
    {
        // BTW, if d=0 there is one intersection, if d > 0 there are 2
        // But we only want the closest one, so that's ok, just use the
        // '-' version of the solver
        double t = ( -b - sqrt(d) ) / (2 * a);
        if (t < 0)
            t = ( -b + sqrt(d) ) / (2 * a);
        return std::pair<bool, double>(true, t);
    }
}

