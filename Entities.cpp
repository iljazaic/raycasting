#include "Geometry.cpp"
#include <vector>
#include <cmath>
#include <iostream>

using std::vector;
const double ONE_DEG_IN_RAD = (M_PI / 180);

enum TEXTURES
{
    SMOOTH,
    ROUGH,
    GLASS
};

class Ray
{
public:
    Line2d ray;
    Ray()
    {
        ray = *new Line2d();
    }
    Ray(Vector2d dir, Vector2d orig, double maxlen)
    {
        ray = *new Line2d(orig, dir, maxlen);
    }

    void rotate(double deltaRad)
    {
        ray.directionVector._rotate(deltaRad);
    }

    Vector2d findFirstIntersection(Map *map)
    {
        Vector2d currentIntersectionPoint = Vector2d(1.7976931348623157E+308, 1.7976931348623157E+308);
        for (const Wall &wall : map->wallConstruction)
        {
            Vector2d intersection = wall.lineOnMap.getIntersectionPoint(ray);
            if (intersection.mag < currentIntersectionPoint.mag)
            {
                currentIntersectionPoint = intersection;
            }
        }
    }
};
class Player; // forward declare

class PlayerViewport
{
public:
    double viewportAngle;
    double viewDistance;
    double viewportResolution;
    Player *parent;
    Vector2d viewportOrigin;
    Vector2d viewportDirection;

    // default game viewport
    PlayerViewport(Player *p) : parent(p), viewportAngle(45), viewDistance(100), viewportResolution(90), viewportOrigin(0, 0), viewportDirection(0, 0) {}
    int scanViewport(Map *map)
    {
        if (parent)
        {
            auto playerPos = parent->position;
            auto playerDir = parent->direction;

            // direction must start from +viewportAngle from the actial direction up to viewportResolution/2#
            playerDir._rotate((M_PI / 180) * viewportAngle);
            Ray r = *new Ray(playerPos, playerDir, viewDistance);
            int distances[(int)viewportResolution] = {};
            int i = 0;
            for (double d = viewportAngle; d >= -viewportResolution / 2; d -= 1.0)
            {
                r.rotate(ONE_DEG_IN_RAD);
                Vector2d intersection = r.findFirstIntersection(map);
                if (intersection.mag <= viewDistance) // is it really in our vision tho
                {
                    distances[i] = intersection.mag;
                }
                else
                {
                    distances[i] = -1; // make sure to draw black
                }
            }

            // draw the viewport
            // from top to bottom
            // each row checkes if it should draw
            for (int height = 0; height <= viewportAngle; height++)
            {

                for (int j = 0; j <= viewportResolution; j++)
                {
                    if (distances[j] != -1)
                    {
                        int heightAtPoint = (int)viewportAngle - distances[j];
                        if (height > round((viewportAngle - distances[j]) / 2) && height < round(viewportAngle - (viewportAngle - distances[j]) / 2))
                        {
                            std::cout << "a";
                        }
                        else
                        {
                            std::cout << " ";
                        }
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }

                std::cout << "\n";
            }
        }
    }
};

class Player
{
public:
    Vector2d position;
    Vector2d direction;
    PlayerViewport viewport;

    Player()
        : position(0.0, 0.0),
          direction(1.0, 1.0),
          viewport(this)
    {
        direction._normalize();
    }
    void rotateTick(double angle)
    {
        direction._rotate(angle);
    };
};

class Wall
{
public:
    enum TEXTURES texture;
    Line2d lineOnMap;

    Wall(Line2d line)
    {
        lineOnMap = line;
    }
    Wall(Line2d line, enum TEXTURES texture_)
    {
        texture = texture_;
        lineOnMap = lineOnMap;
    }
};

class RayCastingResult
{
public:
    double distance;
    double angle;

    RayCastingResult()
    {
        distance = 0;
        angle = 0;
    }
    RayCastingResult(double d, double a)
    {
        distance = d;
        angle = a;
    }
};

class Map
{
public:
    vector<Wall> wallConstruction;
    vector<Player> playerList;

    Map()
    {
        wallConstruction = std::vector<Wall>();
        playerList = std::vector<Player>();
    };
    Map(vector<Wall> &&wallConstruction_, vector<Player> &&playerList_) : wallConstruction(std::move(wallConstruction)) { playerList = *new vector<Player>; };

    void addPlayer(Player &&player_)
    {
        playerList.push_back(player_);
    }

    void addWall(Wall &&newWall)
    {
        wallConstruction.push_back(newWall);
    }
};

class ViewportEncoding
{
public:
    vector<double> distances;
    vector<TEXTURES> textures;
    int maxLength;

    // only empty constructor for reasons
    ViewportEncoding(int MAXLENGTH)
    {
        distances = *new vector<double>;
        textures = *new vector<TEXTURES>;
        maxLength = MAXLENGTH;
    };

    void push_element(double &&DISTANCE, TEXTURES &&TEXTURE)
    {
        distances.push_back(DISTANCE);
        textures.push_back(TEXTURE);
    };
};
