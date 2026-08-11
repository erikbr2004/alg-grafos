#include "arquivos.h"

void toLowerString(std::string& origem, std::string& destino)
{
    for (auto& c : origem)
        c = tolower(c);
    for (auto& c : destino)
        c = tolower(c);
}

void carregarArestasDeArquivo(Grafo& grafo, const std::string& nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;
	while (std::getline(arquivo, linha))
    {
		std::istringstream iss(linha);
        std::string origem, destino;

        if (!(iss >> origem >> destino))
        {
            std::cerr << "Erro ao ler linha: " << linha << std::endl;
            continue;
        }

        if (origem == "-" || destino == "-")
			continue;

		toLowerString(origem, destino);

        grafo.adicionarAresta(origem, destino);
    }

    arquivo.close();
}
