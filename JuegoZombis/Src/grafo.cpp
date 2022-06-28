#include "grafo.h"

Grafo::Grafo(int V) : _V(V), _A(0), _ady(_V) {}

Grafo::Grafo(std::istream& flujo, int primer) : _A(0) {
    flujo >> _V;
    if (!flujo) return;
    _ady.resize(_V);
    int E, v, w;
    flujo >> E;
    while (E--) {
        flujo >> v >> w;
        ponArista(v - primer, w - primer);
    }
}

int Grafo::V() const {
    return _V;
}

void Grafo::ponArista(int v, int w)
{
    if (v < 0 || v >= _V || w < 0 || w >= _V)
        throw std::domain_error("Vertice inexistente");
    ++_A;
    _ady[v].push_back(w);
    _ady[w].push_back(v);
}

Adys const& Grafo::ady(int v) const
{
    if (v < 0 || v >= _V)
        throw std::domain_error("Vertice inexistente");
    return _ady[v];
}

void Grafo::print(std::ostream& o) const
{
    o << _V << " vértices, " << _A << " aristas\n";
    for (int v = 0; v < _V; ++v) {
        o << v << ": ";
        for (int w : _ady[v]) {
            o << w << " ";
        }
        o << "\n";
    }
}