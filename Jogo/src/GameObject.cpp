#include "GameObject.hpp"

GameObject::GameObject(Vector2 position)
{
    this -> position = position;
}

GameObject::~GameObject()
{
}

Vector2 GameObject::getPosition()
{
    return this -> position;
}
