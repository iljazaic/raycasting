#include "Geometry.cpp"
#include <vector>

using std::vector;

enum TEXTURES
{
    SMOOTH,
    ROUGH,
    GLASS
};

class LightSource
{
public:
    double intensity;
    Vector2d position;
    Vector2d direction;
    double FOV; // IN RADIANS REMEMBER

    LightSource(double intensity_, Vector2d position_, Vector2d direction_)
    {
        intensity = intensity_;
        position = position_;
        direction = direction_;
        FOV = M_PI_2; // 45 deg
    }
};

class Player
{
public:
    Vector2d position;
    Vector2d direction;
    PlayerViewport viewport;

    Player()
    {
        position = *(new Vector2d(0.0, 0.0));
        direction = *(new Vector2d(1.0, 1.0));
        viewport = *new PlayerViewport();
        direction._normalize();
    };

    void moveTick(Vector2d direction_)
    {
        direction_._normalize();
        position._add(direction_);
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
    int brightness; // from 1 to 100?

    Wall(Line2d line)
    {
        lineOnMap = line;
        brightness = 0;
    }
    Wall(Line2d line, enum TEXTURES texture_)
    {
        texture = texture_;
        lineOnMap = lineOnMap;
        brightness = 0;
    }
};

class MapEntity
{
public:
    vector<Wall> wallConstruction;
    vector<Player> playerList;

    MapEntity(vector<Wall> &&wallConstruction_, vector<Player> &&playerList_) : wallConstruction(std::move(wallConstruction)) { playerList = *new vector<Player>; };

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
    
    //only empty constructor for reasons
    ViewportEncoding(int MAXLENGTH){
        distances=*new vector<double>;
        textures=*new vector<TEXTURES>;
        maxLength=MAXLENGTH;
    };


    void push_element(double &&DISTANCE, TEXTURES &&TEXTURE){
        distances.push_back(DISTANCE);
        textures.push_back(TEXTURE);
    };


};

class PlayerViewport
{
public:
    double viewportAngle;
    double viewDistance;
    double viewportResolution;
    Vector2d viewportOrigin;
    Vector2d viewportDirection;

    PlayerViewport()
    {
        viewportAngle = 45;
        viewportResolution = 90;
        viewDistance = 100;
        viewportOrigin = *new Vector2d(0, 0);
        viewportDirection = *new Vector2d(0, 0);
    }

    void scanViewport() {

    };
};