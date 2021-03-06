#include "SpawnZombis.h"

#include "InputManager.h"
#include "Entidad.h"
#include "EntidadManager.h"
#include "Transform.h"
#include <time.h>
#include "FMODAudioManager.h"

bool SpawnZombis::init(const std::map<std::string, std::string>& mapa) {
	return true;
}

void SpawnZombis::update() {
	clock_t auxc = clock();
	if (auxc > lastZombie + time_to_spawn) {
		lastZombie = auxc;

		Entidad* zombie = Entidad::instantiate("Zombie.prefab");
		FMODAudioManager::instance()->playMusic(5, false);

		// Los zombis se generan en las 4 esquinas de manera aleatoria
		int x = POS_ZOMBIS_X;
		int z = POS_ZOMBIS_Y;

		int mx = rand() % MARGIN - MARGIN / 2;
		int mz = rand() % MARGIN - MARGIN / 2;

		if (rand() % 2 == 1) {
			x = -x;
			x += mx;
		}

		if (rand() % 2 == 1) {
			z = -z;
			z += mz;
		}

		zombie->getComponent<Transform>()->setPosition(
			zombie->getComponent<Transform>()->getPositionX() + x,
			zombie->getComponent<Transform>()->getPositionY() + z
		);
		zombie->getComponent<Transform>()->setZHeight(1);

		increaseRatio();
	}
}
