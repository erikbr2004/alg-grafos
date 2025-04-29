#include "grafo.h"

void Grafo::adicionarAresta(const std::string& origem, const std::string& destino)
{
	adjacencia[origem].insert(destino);
    if (!isDirecionado)
        adjacencia[destino].insert(origem);
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

const std::set<std::string> Grafo::obterVizinhos(const std::string& vertice)
{
    if (existeVertice(vertice))
        return adjacencia.at(vertice);
    return {};
}

const void Grafo::exportarGrafoParaArquivo()
{
	std::string nomeArquivo = { "exportado.txt" };
	std::ofstream arquivo(nomeArquivo);
	if (!arquivo.is_open())
	{
		std::cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << std::endl;
		return;
	}

	// Escreve os vértices e arestas no arquivo
	for (const auto& par : adjacencia)
	{
		const std::string& vertice = par.first;
		const std::set<std::string>& vizinhos = par.second;
		for (const auto& vizinho : vizinhos)
			arquivo << vertice << " " << vizinho << std::endl;
	}
	arquivo.close();
}

const void Grafo::mapaToMatrixAdj()
{
    std::string nomeArquivo = { "exportado.txt" };
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }
    
    // Mapeia vértices para índices
    std::map<std::string, int> mapaVertices;
    std::vector<std::string> listaVertices;
    std::vector<std::vector<int>> matrizAdj;
    
    std::string origem, destino;
    while (arquivo >> origem >> destino)
    {
        if (mapaVertices.find(origem) == mapaVertices.end())
        {
            mapaVertices[origem] = (int)listaVertices.size();
            listaVertices.push_back(origem);
        }
        if (mapaVertices.find(destino) == mapaVertices.end())
        {
            mapaVertices[destino] = (int)listaVertices.size();
            listaVertices.push_back(destino);
        }
    }
    
    // Inicializa a matriz de adjacência
    int tamanho = (int)listaVertices.size();
    matrizAdj.resize(tamanho, std::vector<int>(tamanho, 0));
    
    // Reposiciona o cursor do arquivo para o início
    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);
    
    // Preenche a matriz de adjacência
    while (arquivo >> origem >> destino)
    {
        int i = mapaVertices[origem];
        int j = mapaVertices[destino];
        matrizAdj[i][j] = 1;
        if (!isDirecionado)
            matrizAdj[j][i] = 1;
    }
    
    arquivo.close();
    
    // Exibe a matriz de adjacência
    std::cout << "Matriz de Adjacencia:" << std::endl;
    for (const auto& linha : matrizAdj)
    {
        for (int valor : linha)
            std::cout << valor << " ";
        std::cout << std::endl;
    }
}

const void Grafo::mapaToMatrixIncid()
{
    std::string nomeArquivo = { "exportado.txt" };
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    // Mapeia vértices para índices
    std::map<std::string, int> mapaVertices;
    std::vector<std::string> listaVertices;
    std::vector<std::pair<std::string, std::string>> listaArestas;
    std::vector<std::vector<int>> matrizIncid;

    std::string origem, destino;
    while (arquivo >> origem >> destino)
    {
        if (mapaVertices.find(origem) == mapaVertices.end())
        {
            mapaVertices[origem] = (int)listaVertices.size();
            listaVertices.push_back(origem);
        }
        if (mapaVertices.find(destino) == mapaVertices.end())
        {
            mapaVertices[destino] = (int)listaVertices.size();
            listaVertices.push_back(destino);
        }
        listaArestas.emplace_back(origem, destino);
    }

    // Inicializa a matriz de incidência
    int numVertices = (int)listaVertices.size();
    int numArestas = (int)listaArestas.size();
    matrizIncid.resize(numVertices, std::vector<int>(numArestas, 0));

    // Preenche a matriz de incidência
    for (int k = 0; k < numArestas; ++k)
    {
        const auto& aresta = listaArestas[k];
        int i = mapaVertices[aresta.first];
        int j = mapaVertices[aresta.second];

        if (isDirecionado)
        {
            matrizIncid[i][k] = 1;  // Origem
            matrizIncid[j][k] = -1; // Destino
        }
        else
        {
            matrizIncid[i][k] = 1;
            matrizIncid[j][k] = 1;
        }
    }

    arquivo.close();

    // Exibe a matriz de incidência
    std::cout << "Matriz de Incidencia:" << std::endl;
    unsigned int cont = 0;
    for (const auto& linha : matrizIncid)
    {
        for (int valor : linha)
            std::cout << valor << " "; cont++;
        std::cout << std::endl;
    }
}

const void Grafo::exibirGrafoMatematica()
{
    std::cout << "Grafo: G = (V, A)" << std::endl;
    std::cout << "V = { ";
    for (const auto& par : adjacencia)
        std::cout << par.first << " ";
    std::cout << "}" << std::endl;
 
    std::cout << "A = { ";
    std::set<std::pair<std::string, std::string>> arestasExibidas;
    for (const auto& par : adjacencia)
    {
        const std::string& vertice = par.first;
        const std::set<std::string>& vizinhos = par.second;
        for (const auto& vizinho : vizinhos)
        {
            std::pair<std::string, std::string> aresta = {vertice, vizinho};
            std::pair<std::string, std::string> arestaInvertida = {vizinho, vertice};
            if (arestasExibidas.find(aresta) == arestasExibidas.end() &&
                arestasExibidas.find(arestaInvertida) == arestasExibidas.end())
            {
                std::cout << "(" << vertice << ", " << vizinho << ") ";
                arestasExibidas.insert(aresta);
 			   std::cout << std::endl;
            }
        }
    }
    std::cout << "}" << std::endl;
}

const void Grafo::buscaEmLargura(const std::string& verticeInicial)
{
	std::set<std::string> visitados;
	std::list<std::string> fila;
	visitados.insert(verticeInicial);
	fila.push_back(verticeInicial);
	while (!fila.empty())
	{
		std::string vertice = fila.front();
		fila.pop_front();
		std::cout << vertice << " ";
		for (const auto& vizinho : obterVizinhos(vertice))
		{
			if (visitados.find(vizinho) == visitados.end())
			{
				visitados.insert(vizinho);
				fila.push_back(vizinho);
			}
		}
	}
	std::cout << std::endl;
}

const void Grafo::buscaEmProfundidade(const std::string& verticeInicial)
{
	std::set<std::string> visitados;
	std::list<std::string> pilha;
	visitados.insert(verticeInicial);
	pilha.push_back(verticeInicial);
	while (!pilha.empty())
	{
		std::string vertice = pilha.back();
		pilha.pop_back();
		std::cout << vertice << " ";
		for (const auto& vizinho : obterVizinhos(vertice))
		{
			if (visitados.find(vizinho) == visitados.end())
			{
				visitados.insert(vizinho);
				pilha.push_back(vizinho);
			}
		}
	}
	std::cout << std::endl;    
}

const std::map<std::string, std::set<std::string>> Grafo::componentesFortementeConexos()
{
	// Implementação do algoritmo de Kosaraju para encontrar componentes fortemente conexos
	std::map<std::string, std::set<std::string>> grafoTransposto;
	for (const auto& par : adjacencia)
	{
		const std::string& vertice = par.first;
		for (const auto& vizinho : par.second)
			grafoTransposto[vizinho].insert(vertice);
	}
	std::set<std::string> visitados;
	std::list<std::string> pilha;
	for (const auto& par : adjacencia)
	{
		const std::string& vertice = par.first;
		if (visitados.find(vertice) == visitados.end())
			buscaEmProfundidade(vertice);
	}
	visitados.clear();
	while (!pilha.empty())
	{
		std::string vertice = pilha.back();
		pilha.pop_back();
		if (visitados.find(vertice) == visitados.end())
			buscaEmLargura(vertice);
	}

	return grafoTransposto;
}
