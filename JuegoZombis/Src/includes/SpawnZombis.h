#pragma once
#include "Componente.h"

typedef long clock_t;

const int POS_ZOMBIS_X = 1150;
const int POS_ZOMBIS_Y = 750;
const int MARGIN = 100;

class SpawnZombis : public Componente {
public:
    SpawnZombis() {};
    ~SpawnZombis() {};
    bool init(const std::map<std::string, std::string>& mapa);
    void update();
    void increaseRatio() { if (time_to_spawn > 200) time_to_spawn -= 10; };
private:
    clock_t time_to_spawn = 1500;
    clock_t lastZombie = 0;
};
