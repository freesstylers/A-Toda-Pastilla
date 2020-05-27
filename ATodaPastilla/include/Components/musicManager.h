#pragma once

#include "Entity/Component.h"
#include "Audio/AudioManager.h"
#include "Audio/AudioComponent.h"
#include <string>
#include "Scene/SceneManager.h"

class MusicManager : public AudioComponent
{
public:
	MusicManager(json& args);
	~MusicManager();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

private:
	int numObj = -1;
	Vector3 pos;
	Vector3 vel;
	std::string audioRoute;
	int song1 = 0;
	bool intro = false;

	EnemySpawner* es = nullptr;
};



