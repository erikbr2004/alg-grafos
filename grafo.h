// Grafo.h - Definição de um grafo simples usando lista de adjacência
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

class Grafo {
private:
    // Representação do grafo usando lista de adjacência
    std::unordered_map<std::string, std::list<std::string>> adjacencia;
    bool isDirecionado;
    
public:
    // Construtor
    Grafo(bool isDirecionado = false) : isDirecionado(isDirecionado) {}
    
    // Adiciona uma aresta ao grafo
    void adicionarAresta(const std::string& origem, const std::string& destino);
    
    // Exibe o grafo
    const void exibirGrafo();

	// Exibe os vértices do grafo
    const void existeVertices();
    
    // Verifica se um vértice existe no grafo
    const bool existeVertice(const std::string& vertice);
    
    // Retorna os vizinhos de um vértice
    const std::list<std::string> obterVizinhos(const std::string& vertice);
};
