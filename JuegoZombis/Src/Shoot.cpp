#include "Shoot.h"
#include "InputManager.h"
#include "Entidad.h"
#include "EntidadManager.h"
#include "Transform.h"
#include <time.h>
#include "FMODAudioManager.h"

Shoot::Shoot() : shootTime(), cont(), lastBullet()
{
}

Shoot::~Shoot()
{
}

bool Shoot::init(const std::map<std::string, std::string>& mapa)
{
    if (mapa.find("shootTime") == mapa.end()) return false;
    std::string::size_type sz = 0, sa = 0;
    std::string shootTimeString = mapa.at("shootTime");
    shootTime = stoi(shootTimeString);
    _inicializado = true;
   
    return true;
}

void Shoot::update()
{
    clock_t auxc = clock();

    // Primero compueba que haya pasado el tiempo necesario para disparar una bala
    if (auxc > lastBullet + shootTime) {

        // Luego si está pulsado el boton izquierdo del ratón se dispara
        if (ih().getMouseButtonState(ih().LEFT)) {
            // Actualiza el tiempo
            lastBullet = auxc;

            // Se instancia la bala
            Vectola3D pos = _entity->getComponent<Transform>()->getPosition();
            pos.setY(0);

            Entidad* bala = Entidad::instantiate("Bala.prefab", pos);
            Singleton<FMODAudioManager>::instance()->playMusic(2, false);
        }
    }
}