#include "Components\ProjectileBehaviour.h"
#include"Components/VidaEnemigos.h"
#include"Components/VidaPlayer.h"
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "checkML.h"

ProjectileBehaviour::ProjectileBehaviour(json& args):Component(args)
{
	
}

void ProjectileBehaviour::init(json& args)
{

}

void ProjectileBehaviour::start()
{
	speed = 0;
	source = "Player";
	damage = 10;
	dir = Vector3(0, 0, 0);
	bordeSup = 500;
	bordeInf = -500;
	bordeDer = 500;
	bordeIzq = -500;
	timeBetwCol = 0.1;
	timeSinceLastCol = timeBetwCol;

	EventManager::getInstance()->RegisterListener(this, "PAUSE");
}

void ProjectileBehaviour::update()
{
	Transform* t = getEntity()->getComponent<Transform>("Transform");
	if (t->getPosition().X > bordeDer || t->getPosition().X < bordeIzq ||
		t->getPosition().Z > bordeSup || t->getPosition().Z < bordeInf) {
		e_->getComponent<Vida>("Vida")->sumaVida(-e_->getComponent<Vida>("Vida")->GetVida());
	}
	Vector3 pos = t->getPosition();

	float deltatime = MotorCasaPaco::getInstance()->DeltaTime();

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

void ProjectileBehaviour::setSource(std::string sourc)
{
	source = sourc;
}

std::string ProjectileBehaviour::getSource()
{
	return source;
}

void ProjectileBehaviour::setDamage(float dmg)
{
	damage = dmg;
}

void ProjectileBehaviour::OnCollision(Entity* other)
{
	if (timeSinceLastCol >= timeBetwCol) {
		if (source == "Player" && other->getTag() == "Enemy") {

			other->getComponent<VidaEnemigos>("VidaEnemigos")->sumaVida(-damage);
				e_->getComponent<Vida>("Vida")->sumaVida(-e_->getComponent<Vida>("Vida")->GetVida());
			timeSinceLastCol=0;

		}
		else if (source == "Enemy" && other->getTag() == "Player") {
			other->getComponent<VidaPlayer>("VidaPlayer")->sumaVida(-damage);
			e_->getComponent<Vida>("Vida")->sumaVida(-e_->getComponent<Vida>("Vida")->GetVida());
			timeSinceLastCol = 0;

		}
		else if (source == "Player" && other->getTag() == "Projectile" && other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource() == "Enemy") {
			other->getComponent<Vida>("Vida")->sumaVida(-e_->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->damage);
			if(e_->getTag() != "Bomba")
				e_->getComponent<Vida>("Vida")->sumaVida(-other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->damage);
			timeSinceLastCol = 0;
		}

		if (e_->getTag() == "Bomba" && other->getTag() == "Enemy")
		{
			EventManager::getInstance()->EmitEvent("BombaImpacto");
			std::list<Entity*> enemies = SceneManager::getInstance()->getCurrentScene()->getEntitiesByTag("Enemy");
			std::list<Entity*> bullets = SceneManager::getInstance()->getCurrentScene()->getEntitiesByTag("Projectile");
			for (auto it : enemies)
			{
				it->getComponent<VidaEnemigos>("VidaEnemigos")->sumaVida(-damage);
			}
			for (auto it : bullets)
			{
				if (it->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource() == "Enemy")
				{
					it->getComponent<Vida>("Vida")->sumaVida(-e_->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->damage);
				}
			}
		}
	}
	timeSinceLastCol += MotorCasaPaco::getInstance()->DeltaTime();
}

bool ProjectileBehaviour::ReceiveEvent(Event& event)
{
	if (event.type == "PAUSE")
		setEnabled(!isEnabled());

	return false;
}
