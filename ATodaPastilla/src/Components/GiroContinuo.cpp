#include "Components/GiroContinuo.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"

GiroContinuo::GiroContinuo(json& args) : Component(args)
{
	
}

GiroContinuo::~GiroContinuo()
{

}

void GiroContinuo::update()
{
	e_->getComponent<Transform>("Transform")->rotate(Vector3(0.0f, rotation_, 0.0f));
}

void GiroContinuo::init(json& j)
{
	if (!j["rotation"].is_null()) rotation_ = j["rotation"];
}
