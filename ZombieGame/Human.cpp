#include "Human.h"

#include <glm/gtx/rotate_vector.hpp>

#include <ctime>
#include <random>


Human::Human() :
    _frames(0)
{
    //Empty
}

Human::~Human()
{
    //Empty
}

void Human::init(float speed, glm::vec2 pos)
{

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _health = 100;

    _color.r = 200;
    _color.g = 0;
    _color.b = 200;
    _color.a = 255;

    _speed = speed;
    _position = pos;
    // Get random direction
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    // Make sure direction isn't zero
    if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

    _direction = glm::normalize(_direction);
}

void Human::update(const std::vector<std::string>& levelData,
                   std::vector<Human*>& humans,
                   std::vector<Zombie*>& zombies,
                   float deltaTime)
{

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

    _position += _direction * _speed * deltaTime;

    // Randomly change direction every 20 frames
    if (_frames == 30)
    {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    }
    else
    {
        _frames++;
    }

    if (collideWithLevel(levelData))
    {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    }
}
