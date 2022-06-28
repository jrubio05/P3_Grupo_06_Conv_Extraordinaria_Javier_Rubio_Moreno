#pragma once
#include <vector>


class GeneracionAleatorio {
public:
	GeneracionAleatorio(int nObstaculos, int base1, int base2, int alto, int ancho);
	std::vector<int> generaObstaculo();

private:

	float halton1d(int base, int index);
	std::pair<float,float> halton2d(int base1, int base2, int index);
	
	std::vector<int> matriz;
	int nObstaculos;
	int base1;
	int base2; 
	int alto;
	int ancho;




};