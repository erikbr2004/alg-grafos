// Grafo.h - Defini��o de um grafo simples usando lista de adjac�ncia
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

class Grafo {
private:
    // Representa��o do grafo usando lista de adjac�ncia
    std::unordered_map<std::string, std::list<std::string>> adjacencia;
    bool isDirecionado;
    
public:
    // Construtor
    Grafo(bool isDirecionado = false) : isDirecionado(isDirecionado) {}
    
    // Adiciona uma aresta ao grafo
    void adicionarAresta(const std::string& origem, const std::string& destino);
    
    // Exibe o grafo
    const void exibirGrafo();

	// Exibe os v�rtices do grafo
    const void existeVertices();
    
    // Verifica se um v�rtice existe no grafo
    const bool existeVertice(const std::string& vertice);
    
    // Retorna os vizinhos de um v�rtice
    const std::list<std::string> obterVizinhos(const std::string& vertice);
};
