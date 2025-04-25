#include "grafo.h"
#include "arquivos.h"

int main()
{

	Grafo grafo;
	carregarArestasDeArquivo(grafo, "arestas.txt");
	grafo.exibirGrafo();

	std::cout << std::endl;
	
	std::list<std::string> vizinhos = grafo.obterVizinhos("cosmos");
	if (vizinhos.empty())
		std::cout << "O vértice não possui vizinhos." << std::endl;
	else
	{
		std::cout << "Vizinhos: ";
		for (const auto& vizinho : vizinhos)
			std::cout << vizinho << " ";
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}