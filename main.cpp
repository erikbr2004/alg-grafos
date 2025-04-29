#include "grafo.h"
#include "arquivos.h"

int main()
{

	Grafo grafo;
	carregarArestasDeArquivo(grafo, "arestas.txt");
	grafo.exibirGrafo();  // Exibe o grafo atraves de uma lista de adjacencia

	std::cout << std::endl;

	//grafo.exportarGrafoParaArquivo();

	// Diferentes tipos de exibicao do grafo
	//grafo.mapaToMatrixAdj();
	//grafo.mapaToMatrixIncid();
	//grafo.exibirGrafoMatematica();

	//grafo.buscaEmLargura("deodoro");
	//grafo.buscaEmProfundidade("deodoro");

	return EXIT_SUCCESS;
}