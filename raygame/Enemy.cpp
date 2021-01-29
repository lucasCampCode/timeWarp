#include "Enemy.h"
#include "Player.h"
#include "Game.h"
Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{

}

bool Enemy::checkTargetInSight(float maxAngle, float maxDistance)
{
	if (m_target)
		return false;

	MathLibrary::Vector2 direction = m_target->getWorldPosition() - getWorldPosition();

	float distance = direction.getMagnitude();
	float angle = (float)_CMATH_::acos(MathLibrary::Vector2::dotProduct(getVelocity(), direction));
	//when target is in sight 
	if (angle < maxAngle && distance <= maxDistance)
		return true;

	return false;
}

void Enemy::onCollision(Actor* other)
{
	//check to see if enemy has collided with a player
	if (typeid(*other) == typeid(Player))
		attack((Entity*)other);//attacks Player
	other->setAcceleration(getVelocity() * 10);//pushes the entity away
}

void Enemy::update(float deltaTime)
{
	if (checkTargetInSight(0.75f, 3))
	{//if in sight sets  velocity to its target
		setVelocity((m_target->getWorldPosition() - getWorldPosition()));
	}
	else
	{
		setVelocity(MathLibrary::Vector2((rand() % 3) - 2, (rand() % 3) - 2));
	}
	Entity::update(deltaTime);
	//destroy enemy if health is below 0
	if (getHealth() <= 0)
	{
		Game::destroy(this);
	}
}
