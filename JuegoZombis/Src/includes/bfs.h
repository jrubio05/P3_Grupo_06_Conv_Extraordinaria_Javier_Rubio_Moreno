#pragma once
#include <deque>
#include <vector>

class Grafo;

using Camino = std::deque<int>;

class CaminoMasCorto {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    Grafo* grafo = nullptr;
    int origen;


public:
    CaminoMasCorto(Grafo* g, int v);

    // ¿hay camino del origen a v?
    bool hayCamino(int v) const;

    // número de aristas entre s y v
    int distancia(int v) const;

    // devuelve el camino más corto desde el origen a v (si existe)
    Camino camino(int v) const;


};