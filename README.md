# alg-grafos — Algoritmos em Grafos

[![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![STL](https://img.shields.io/badge/Biblioteca-STL-004482?style=flat-square)](https://en.cppreference.com/w/cpp/container)
[![Estrutura](https://img.shields.io/badge/Estrutura-Grafos-2E7D32?style=flat-square)](https://en.wikipedia.org/wiki/Graph_(abstract_data_type))
[![IDE](https://img.shields.io/badge/Build-Visual%20Studio%202022-5C2D91?style=flat-square&logo=visualstudio&logoColor=white)](https://visualstudio.microsoft.com/)
[![Dataset](https://img.shields.io/badge/Dataset-SuperVia%20RJ-FFB300?style=flat-square)](#o-dataset-rede-ferroviária-do-rio-de-janeiro)
[![Status](https://img.shields.io/badge/Status-Memorial%20de%20disciplina-555555?style=flat-square)](#em-desenvolvimento)

Memorial da disciplina de **Algoritmos em Grafos**: uma biblioteca em C++ que implementa a
estrutura de grafo do zero, com múltiplas representações, algoritmos de travessia e
persistência em arquivo — aplicada a um grafo real, e não a um exemplo de livro-texto.

---

## Sobre o projeto

O núcleo é a classe `Grafo`, que representa o grafo como uma **lista de adjacência
associativa**:

```cpp
class Grafo {
private:
    std::map<std::string, std::set<std::string>> adjacencia;
    bool isDirecionado;
    // ...
};
```

A escolha de `map<string, set<string>>` em vez de uma matriz de inteiros indexada por
posição tem consequências práticas:

- **Vértices são nomeados**, não numerados. O grafo trabalha diretamente com
  `"Central_do_Brasil"` em vez de exigir uma tabela de tradução entre nomes e índices.
- **Arestas duplicadas são impossíveis** — o `set` garante unicidade sem verificação
  explícita.
- **Vizinhos saem ordenados**, o que torna a saída dos algoritmos determinística e fácil de
  conferir manualmente.
- **Memória proporcional às arestas existentes**, ao contrário da matriz de adjacência, que
  reserva espaço para todas as combinações possíveis de vértices.

Um único flag no construtor decide o comportamento: em grafos não direcionados,
`adicionarAresta` insere a ligação nos dois sentidos; em grafos direcionados, apenas no
sentido informado.

```cpp
void Grafo::adicionarAresta(const std::string& origem, const std::string& destino)
{
    adjacencia[origem].insert(destino);
    if (!isDirecionado)
        adjacencia[destino].insert(origem);
}
```

---

## O dataset: rede ferroviária do Rio de Janeiro

Em vez de um grafo sintético, o projeto usa a malha de trens metropolitanos da **SuperVia**:
**99 estações** conectadas por **99 trechos**, distribuídos pelos ramais Santa Cruz, Japeri,
Belford Roxo, Saracuruna, Guapimirim e Vila Inhomirim.

```text
Santa_Cruz -> Tancredo_Neves -> Paciencia -> ... -> Deodoro -> ... -> Central_do_Brasil
                                                       │
Belford_Roxo -> Coelho_da_Rocha -> ... -> Honorio_Gurgel <┘
                                                │
Paracambi -> Lages -> ... -> Anchieta -> R_Albuquerque
```

Isso torna os algoritmos concretos: uma busca em largura a partir de `Deodoro` responde
"quais estações estão a N conexões de distância", e as estações de baldeação aparecem
naturalmente como vértices de grau alto — `Deodoro`, `Sao_Cristovao`, `Triagem` e
`Saracuruna` são os pontos onde os ramais se cruzam.

---

## Representações implementadas

O mesmo grafo pode ser visualizado de quatro formas, cada uma útil em um contexto
diferente:

| Método | Saída | Quando é útil |
|--------|-------|---------------|
| `exibirGrafo()` | Lista de adjacência encadeada | Inspeção rápida da vizinhança de cada vértice |
| `mapaToMatrixAdj()` | Matriz de adjacência `V × V` | Verificar adjacência em tempo constante |
| `mapaToMatrixIncid()` | Matriz de incidência `V × A` | Análise por aresta; em grafos direcionados usa `1` para origem e `-1` para destino |
| `exibirGrafoMatematica()` | Notação formal `G = (V, A)` | Conferir o grafo contra a definição matemática, sem repetir arestas simétricas |

---

## Algoritmos

### Busca em largura (BFS)

Implementada com fila e conjunto de visitados, visitando o grafo por camadas de distância a
partir do vértice inicial.

```cpp
grafo.buscaEmLargura("deodoro");
```

```text
deodoro honorio_gurgel marechal_hermes r_albuquerque vila_militar barros_filho
rocha_miranda bento_ribeiro anchieta magalhaes_bastos costa_barros ...
```

A ordem revela a estrutura da malha: os quatro primeiros vizinhos de `deodoro` aparecem
antes de qualquer estação mais distante, e a partir daí a busca se espalha por camadas.

### Busca em profundidade (DFS)

Implementada de forma **iterativa com pilha explícita**, em vez de recursão. A escolha evita
estouro de pilha em grafos grandes e deixa o contraste com a BFS mais evidente: as duas
funções são quase idênticas, mudando apenas a extremidade de onde o próximo vértice é
retirado — `front()` na fila, `back()` na pilha.

```cpp
grafo.buscaEmProfundidade("deodoro");
```

```text
deodoro vila_militar magalhaes_bastos realengo padre_miguel ierme_da_silveira bangu
senador_camara santissimo a_vasconcelos campo_grande benjamin_monte inhoaiba ...
```

O contraste fica evidente: a DFS entra no ramal Santa Cruz e o percorre inteiro até o fim da
linha antes de voltar e explorar qualquer outro caminho.

---

## Estrutura do repositório

```text
.
├── main.cpp                  # Ponto de entrada: carrega o grafo e chama as operações
├── grafo.h / grafo.cpp       # Classe Grafo: representações e algoritmos
├── arquivos.h / arquivos.cpp # Leitura do arquivo de arestas e normalização
├── arestas.txt               # Dataset de entrada (rede SuperVia)
├── exportado.txt             # Grafo exportado, consumido pelas matrizes
└── MemorialGrafo.sln         # Solução do Visual Studio 2022
```

---

## Formato do arquivo de entrada

Cada linha de `arestas.txt` declara uma aresta como um par de vértices separados por espaço.
A linha `- -` funciona como separador visual entre ramais e é ignorada na leitura:

```text
Santa_Cruz Tancredo_Neves
Tancredo_Neves Paciencia
- -
Belford_Roxo Coelho_da_Rocha
```

Os nomes são convertidos para minúsculas na carga, de modo que `Deodoro` e `deodoro`
referenciam o mesmo vértice. Linhas malformadas são reportadas em `stderr` e descartadas,
sem interromper a leitura do restante do arquivo.

---

## Compilação e execução

### Visual Studio

Abra `MemorialGrafo.sln` e compile com `Ctrl + F5`. O projeto usa o toolset **v143**
(Visual Studio 2022).

### Linha de comando

```bash
g++ -std=c++17 main.cpp grafo.cpp arquivos.cpp -o grafos
```

```bash
./grafos
```

> O executável precisa ser iniciado no diretório onde está o `arestas.txt`, pois o arquivo é
> aberto por caminho relativo.

> **Compilando com MinGW no Git Bash:** o Git para Windows distribui sua própria
> `libstdc++-6.dll`, que pode ser carregada no lugar da versão do MinGW e derrubar o
> programa logo na primeira escrita em `std::cout`. Se isso acontecer, vincule as
> bibliotecas estaticamente:
>
> ```bash
> g++ -std=c++17 -static-libstdc++ -static-libgcc main.cpp grafo.cpp arquivos.cpp -o grafos
> ```

### Escolhendo o que executar

O `main.cpp` carrega o grafo e exibe a lista de adjacência. As demais operações estão
comentadas — descomente as que quiser testar:

```cpp
Grafo grafo;
carregarArestasDeArquivo(grafo, "arestas.txt");
grafo.exibirGrafo();

//grafo.exportarGrafoParaArquivo();
//grafo.mapaToMatrixAdj();
//grafo.mapaToMatrixIncid();
//grafo.exibirGrafoMatematica();
//grafo.buscaEmLargura("deodoro");
//grafo.buscaEmProfundidade("deodoro");
```

> **Importante:** `mapaToMatrixAdj()` e `mapaToMatrixIncid()` leem de `exportado.txt`, e não
> do grafo em memória. Execute `exportarGrafoParaArquivo()` antes delas sempre que o
> `arestas.txt` for alterado, ou as matrizes refletirão o estado anterior.

---

## Em desenvolvimento

`componentesFortementeConexos()` está parcialmente implementado. A construção do **grafo
transposto** já funciona e é retornada corretamente, mas a identificação dos componentes
ainda não: o algoritmo de Kosaraju exige que a primeira passagem em profundidade registre a
**ordem de finalização** dos vértices em uma pilha, e essa pilha ainda não é preenchida — de
modo que o segundo laço nunca executa.

Para concluir, os próximos passos são:

1. Extrair uma DFS auxiliar que empilhe cada vértice ao terminar de explorá-lo.
2. Percorrer a pilha em ordem inversa executando DFS sobre o grafo transposto.
3. Agrupar como um componente todos os vértices alcançados em cada uma dessas buscas.

---

## Conceitos exercitados

- Representação de grafos: lista de adjacência, matriz de adjacência e matriz de incidência
- Trade-offs entre representações em memória e complexidade de acesso
- Grafos direcionados e não direcionados sob uma mesma interface
- Travessias em largura e em profundidade, com estrutura iterativa
- Contêineres associativos da STL (`map`, `set`, `vector`, `list`)
- Leitura, validação e exportação de dados em arquivo
- Modelagem de um problema real como grafo

---

## Autor

- Erik Barbosa de Castro — [@erikbr2004](https://github.com/erikbr2004)
