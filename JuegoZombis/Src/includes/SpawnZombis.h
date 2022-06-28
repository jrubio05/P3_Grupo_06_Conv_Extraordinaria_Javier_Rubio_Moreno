#pragma once
#include "Componente.h"

typedef long clock_t;

const int POS_ZOMBIS_X = 1150;
const int POS_ZOMBIS_Y = 750;
const int MARGIN = 100;
const clock_t TIME_TO_SPAWN = 400;

class SpawnZombis : public Componente
{
public:
    SpawnZombis() {};
    ~SpawnZombis() {};
    bool init(const std::map<std::string, std::string>& mapa);
    void update();
private:
    clock_t lastZombie = 0;
};

