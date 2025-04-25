#include "grafo.h"

void Grafo::adicionarAresta(const std::string& origem, const std::string& destino)
{
    adjacencia[origem].push_back(destino);
    if (!isDirecionado)
        adjacencia[destino].push_back(origem);
}

const void Grafo::exibirGrafo()
{
    for (const auto& par : adjacencia)
    {
        std::cout << par.first << " -> ";
        for (const auto& vizinho : par.second)
            std::cout << vizinho << " -> ";
        std::cout << "NULL" << std::endl;
    }
}

const void Grafo::existeVertices()
{
	std::cout << "Vértices do grafo:" << std::endl;
	for (const auto& par : adjacencia)
		std::cout << par.first << std::endl;
}

const bool Grafo::existeVertice(const std::string& vertice)
{
    return adjacencia.find(vertice) != adjacencia.end();
}

const std::list<std::string> Grafo::obterVizinhos(const std::string& vertice)
{
    if (existeVertice(vertice))
        return adjacencia.at(vertice);
    return {};
}