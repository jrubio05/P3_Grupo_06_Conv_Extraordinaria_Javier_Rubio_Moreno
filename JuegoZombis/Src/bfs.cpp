#include "includes\bfs.h"
#include "grafo.h"
#include <queue>

CaminoMasCorto::CaminoMasCorto(Grafo* g, int ori) :
    visit(g->V(), false),
    ant(g->V()),
    dist(g->V()),
    grafo(g),
    origen(ori)
{
    std::queue<int> q;

    dist[origen] = 0;
    visit[origen] = true;

    q.push(origen);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : grafo->ady(v)) {
            if (!visit[w]) {
                ant[w] = v;
                dist[w] = dist[v] + 1;
                visit[w] = true;
                q.push(w);
            }
        }
    }
}

bool CaminoMasCorto::hayCamino(int v) const
{
    return visit[v];
}

int CaminoMasCorto::distancia(int v) const
{
    return dist[v];
}

Camino CaminoMasCorto::camino(int v) const
{
    if (!hayCamino(v))
        throw std::domain_error("No existe camino");

    Camino cam;
    for (int x = v; x != origen; x = ant[x])
        cam.push_front(x);
    cam.push_front(origen);
    return cam;
}
