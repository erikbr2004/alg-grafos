// Grafo.h - Definição de um grafo simples usando lista de adjacência
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>

class Grafo {
private:
    // Representação do grafo usando lista de adjacência
    std::map<std::string, std::set<std::string>> adjacencia;
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
    const std::set<std::string> obterVizinhos(const std::string& vertice);

	// Exporta o grafo para um arquivo
    const void exportarGrafoParaArquivo();

	// Converte o grafo para uma matriz de adjacência
    const void mapaToMatrixAdj();

	// Converte o grafo para uma matriz de incidência
    const void mapaToMatrixIncid();

    // Mostra o grafo de forma matematica
	const void exibirGrafoMatematica();

    // Busca em largura
	const void buscaEmLargura(const std::string& verticeInicial);
    
    // Busca em profundidade
	const void buscaEmProfundidade(const std::string& verticeInicial);

	// Componentes fortemente conexos
	const std::map<std::string, std::set<std::string>> componentesFortementeConexos();
};
