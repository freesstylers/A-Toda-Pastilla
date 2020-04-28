#include "..\..\include\Components\ProjectileBehaviour.h"
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"

ProjectileBehaviour::ProjectileBehaviour(json& args):Component(args)
{
	speed = 0;
	dir = Vector3(0, 0, 0);
	bordeSup = 500;
	bordeInf = -500;
	bordeDer = 500;
	bordeIzq = -500;
}

void ProjectileBehaviour::init(json& args)
{

}

void ProjectileBehaviour::update()
{
	Transform* t = getEntity()->getComponent<Transform>("Transform");
	if (t->getPosition().X > bordeDer || t->getPosition().X < bordeIzq ||
		t->getPosition().Z > bordeSup || t->getPosition().Z < bordeInf) {
		getEntity()->setActive(false);
	}
	Vector3 pos = t->getPosition();
	float deltatime = MotorCasaPaco::getInstance()->DeltaTime() / 1000.0f;
	pos += dir.Normalized(dir) * speed * deltatime;
	t->setPosition(pos);
}

void ProjectileBehaviour::setDir(Vector3 dir)
{
	this->dir = dir;
}

void ProjectileBehaviour::setSpeed(float speed)
{
	this->speed = speed;
}
