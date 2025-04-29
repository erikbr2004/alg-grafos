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
	while (std::getline(arquivo, linha)) // L� cada linha do arquivo
    {
		std::istringstream iss(linha); // Cria um stream de string para ler a linha
        std::string origem, destino;

        // Ler os v�rtices de origem e destino da linha
        if (!(iss >> origem >> destino))
        {
            std::cerr << "Erro ao ler linha: " << linha << std::endl;
            continue;
        }

		// Verifica se n�o � uma linha nula
        if (origem == "-" || destino == "-")
			continue;

		toLowerString(origem, destino); // Converte os v�rtices para min�sculas

		// Adiciona a aresta ao grafo
        grafo.adicionarAresta(origem, destino);
    }

    arquivo.close();
}
