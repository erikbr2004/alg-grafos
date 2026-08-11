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
    std::map<std::string, std::set<std::string>> adjacencia;
    bool isDirecionado;
    
public:
    Grafo(bool isDirecionado = false) : isDirecionado(isDirecionado) {}
    
    void adicionarAresta(const std::string& origem, const std::string& destino);
    
    const void exibirGrafo();

    const void existeVertices();
    
    const bool existeVertice(const std::string& vertice);
    
    const std::set<std::string> obterVizinhos(const std::string& vertice);

    const void exportarGrafoParaArquivo();

    const void mapaToMatrixAdj();

    const void mapaToMatrixIncid();

	const void exibirGrafoMatematica();

	const void buscaEmLargura(const std::string& verticeInicial);
    
	const void buscaEmProfundidade(const std::string& verticeInicial);

	const std::map<std::string, std::set<std::string>> componentesFortementeConexos();
};
