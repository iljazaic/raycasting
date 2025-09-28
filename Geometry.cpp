#include <cmath>
#include <algorithm>

class Vector2d
{
public:
    double x;
    double y;
    double mag;
    double theta;

    Vector2d()
    {
        x = 0.0;
        y = 0.0;
        theta = 0.0;
        mag = 0.0;
    }

    Vector2d(double x_, double y_)
    {
        x = x_;
        y = y_;
        mag = sqrt(x * x + y * y);
        theta = atan2(y, x);
    }

    // create a unit vector with just an angle
    Vector2d(double theta_)
    {
        theta = theta_;
        mag = 1;
        x = sin(theta);
        y = cos(theta);
    }

    void _normalize()
    {
        x = cos(theta);
        y = sin(theta);
        mag = 1.0;
    }

    void _scale(double scalar)
    {
        mag *= scalar;
        x = asin(theta) * mag;
        y = acos(theta) * mag;
    }

    void _add(Vector2d vector2)
    {
        x += vector2.x;
        y += vector2.y;
        mag = sqrt(x * x + y * y);
        theta = atan2(y, x);
    }

    void _rotate(double angle)
    {
        theta += angle;
        if (theta > 2 * M_PI)
        {
            theta -= 2 * M_PI; // just to keep it more or less within the range of 0->2pi
        } // i like the control :D
        if (theta < 0.0)
        {
            theta = 2 * M_PI + theta;
        }

        x = asin(theta) * mag;
        y = acos(theta) * mag;
    }

    double _scalarProduct(Vector2d vector2)
    {
        return x * vector2.x + y * vector2.y;
    }
    double _angleWith(Vector2d vector2)
    {
        return acos(_scalarProduct(vector2) / (mag * vector2.mag));
    }

    double distaceWith(Vector2d vector2)
    {
        return sqrt((x - vector2.x) * (x - vector2.x) + (y - vector2.y) * (y - vector2.y));
    }
};

class Line2d
{
public:
    Vector2d pointVector;
    Vector2d directionVector;
    double scalar;

    Line2d()
    {
        pointVector = *new Vector2d();
        directionVector = *new Vector2d();
        scalar = 0;
    }

    Line2d(Vector2d p1, Vector2d p2, double length)
    {
        pointVector = p1;
        directionVector = p2;
        scalar = length;
    }

    Vector2d *getIntersectionPoint(Line2d line2) // returns a pointer to a point lol but kinda like vector2d
    {
        // parametric form of vectors taken
        if (((line2.directionVector.y * directionVector.x) - (line2.directionVector.x * directionVector.y)) == 0)
        {
            return NULL;
        }
        // derived algebraically on the spot because forgot the substitution formula for 2d cross products 👉👈
        double t = ((line2.pointVector.x - pointVector.x) * line2.directionVector.y -
                    (line2.pointVector.y - pointVector.y) * line2.directionVector.x) /
                   ((directionVector.x * line2.directionVector.y) -
                    (directionVector.y * line2.directionVector.x));

        return new Vector2d(pointVector.x + directionVector.x * t, pointVector.y + directionVector.y * t);
    }

    Vector2d pointOfIntersection(Line2d line2) {

    };
};

class Vector3d
{
public:
    double x;
    double y;
    double z;
    double mag;
    double theta;
    double phi;

    Vector3d()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        mag = 0.0;
        theta = 0.0;
        phi = 0.0;
    }

    Vector3d(double x_, double y_, double z_)
    {
        x = x_;
        y = y_;
        z = z_;
        mag = sqrt(x * x + y * y + z * z);
        theta = mag != 0.0 ? std::clamp(acos(z / mag), -1.0, 1.0) : 0.0;
        phi = atan2(y, x);
    }
};

class rectangle
{
public:
    double height;
    double width;
    Vector2d normalVector;
    Vector2d locaion; // defines the bottom left corner of the rectangle

    rectangle(double height_, double width_, Vector2d normalVector_, Vector2d location_)
    {
        height = height_;
        width = width_;
        normalVector_._normalize();
        normalVector = normalVector_;
        locaion = locaion;
    }
};


class ViewportPolygon{
    public:
    std::vector<Vector2D> points;

    ViewportPolygon(std::vector<Vector2d>&& points_) : points(std::move(points_)) {}


    
};


class PlayerViewport{
    public:
        


}