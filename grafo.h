// Grafo.h - Defini��o de um grafo simples usando lista de adjac�ncia
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
    // Representa��o do grafo usando lista de adjac�ncia
    std::map<std::string, std::set<std::string>> adjacencia;
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
    const std::set<std::string> obterVizinhos(const std::string& vertice);

	// Exporta o grafo para um arquivo
    const void exportarGrafoParaArquivo();

	// Converte o grafo para uma matriz de adjac�ncia
    const void mapaToMatrixAdj();

	// Converte o grafo para uma matriz de incid�ncia
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
