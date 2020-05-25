#include "Audio/AudioComponent.h"
#include "MotorCasaPaco.h"
#include "Components/EnemySpawner.h"
#include "Components/GameManager.h"
#include "Entity/Transform.h"

#include "Components/musicManager.h"


MusicManager::MusicManager(json& args) : AudioComponent(args)
{
}

MusicManager::~MusicManager()
{
	AudioManager::getInstance()->stopChannel(1);
}

bool MusicManager::ReceiveEvent(Event& event)
{
	return false;
}

void MusicManager::update()
{
	if (intro) {
		if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
			playMusic("assets/sound/CancionPastillaPart2.mp3", 1);
			intro = false;
		}
	}
	else {
		if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
			if (es->getCurrWave() == 0) {
				playMusic("assets/sound/CancionPastillaPart3.mp3", 1);
			}
			else if (es->getCurrWave() == 1) {
				playMusic("assets/sound/CancionPastillaPart4.mp3", 1);
			}
			else if (es->getCurrWave() == 2) {
				playMusic("assets/sound/CancionPastillaPart5.mp3", 1);
			}
			else if (es->getCurrWave() >= 3) {
				playMusic("assets/sound/CancionPastillaPart6.mp3", 1);
			}
		}
	}

	AudioComponent::update();
}


void MusicManager::init(json& j)
{
	if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
		playMusic("assets/sound/CancionPastillaPart1.mp3", 1);
	}
	intro = true;
	es = SceneManager::getInstance()->getCurrentScene()->getEntity("EnemySpawner")->getComponent<EnemySpawner>("EnemySpawner");
	std::cout << "res pas do" << std::endl;
	AudioComponent::init(j);
}
