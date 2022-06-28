#pragma once
#include <vector>
#include <deque>
#include "Componente.h"

class Grafo;
class CaminoMasCorto;
class Vectola3D;


class GrafoConObstaculos: public Componente {
public:
	GrafoConObstaculos();
	bool init(const std::map<std::string, std::string>& mapa) override;
	std::deque<int> getCaminoMasCorto(int ori, int dest);
	//int getMatrizPos(Vectola3D pos);

private:
	std::vector<CaminoMasCorto>* arrayCaminos = nullptr;
	int ancho= 1;
	int alto= 1;
	int tamVertice=1;
	Grafo* g =nullptr;
	std::vector<int> matriz;

	void addAristas(int index);
	
};