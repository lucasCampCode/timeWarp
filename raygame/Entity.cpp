
#include "Entity.h"
#include "Game.h"
#include "raylib.h"

Entity::Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_health = health;
	m_damage = damage;
	setTag("Entity");
}
Entity::~Entity()
{
	Actor::~Actor();
}
/// <summary>
/// this instance of the entity attacks the other instance
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
bool Entity::attack(Entity* other)
{
	other->takeDamage(m_damage);
	return true;
}
/// <summary>
/// this instance takes damages
/// </summary>
/// <param name="totalDamage"></param>
/// <returns></returns>
bool Entity::takeDamage(float totalDamage)
{
	m_health -= totalDamage;
	return true;
}

void Entity::onCollision(Actor* other)
{
}

void Entity::update(float deltaTime)
{
	//returns acceleration to 0 if acceleration changes
	if (getAcceleration().x > 0)
		setAcceleration(MathLibrary::Vector2(getAcceleration().x - 1, getAcceleration().y));
	if (getAcceleration().y > 0)
		setAcceleration(MathLibrary::Vector2(getAcceleration().x, getAcceleration().y - 1));
	if (getAcceleration().x < 0)
		setAcceleration(MathLibrary::Vector2(getAcceleration().x + 1, getAcceleration().y));
	if (getAcceleration().y < 0)
		setAcceleration(MathLibrary::Vector2(getAcceleration().x, getAcceleration().y + 1));
	Actor::update(deltaTime);
}

void Entity::draw()
{
	Actor::draw();
}