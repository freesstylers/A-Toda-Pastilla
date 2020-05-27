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
	if (song1 == 0) {
		if (intro) {
			if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
				MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart2.mp3", 1, false);
				intro = false;
			}
		}
		else {
			if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
				if (es->getCurrWave() == 0) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart2.mp3", 1, false);
				}
				else if (es->getCurrWave() == 1) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart3.mp3", 1, false);
				}
				else if (es->getCurrWave() == 2) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart4.mp3", 1, false);
				}
				else if (es->getCurrWave() == 3) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart5.mp3", 1, false);
				}
				else if (es->getCurrWave() >= 4) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart6.mp3", 1, false);
				}
			}
		}
	}
	else {
		if (intro) {
			if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
				MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti2.mp3", 1, false);
				intro = false;
			}
		}
		else {
			if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
				if (es->getCurrWave() == 0) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti2.mp3", 1, false);
				}
				else if (es->getCurrWave() == 1) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti3.mp3", 1, false);
				}
				else if (es->getCurrWave() == 2) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti4.mp3", 1, false);
				}
				else if (es->getCurrWave() == 3) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti5.mp3", 1, false);
				}
				else if (es->getCurrWave() >= 4) {
					MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti6.mp3", 1, false);
				}
			}
		}
	}

	AudioComponent::update();
}


void MusicManager::init(json& j)
{
	song1 = (rand() % 2);
	if (song1 == 0) {
		if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
			MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/CancionPastillaPart1.mp3", 1, false);
		}
	}
	else {
		if (!MotorCasaPaco::getInstance()->getAudioManager()->isPlayingChannel(1)) {
			MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/Pasti1.mp3", 1, false);
		}
	}
	intro = true;
	es = SceneManager::getInstance()->getCurrentScene()->getEntity("EnemySpawner")->getComponent<EnemySpawner>("EnemySpawner");
	std::cout << "res pas do" << std::endl;
	AudioComponent::init(j);
}



