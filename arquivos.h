#pragma once
#include <fstream>
#include <sstream>

#include "grafo.h"

void toLowerString(std::string& origem, std::string& destino);
void carregarArestasDeArquivo(Grafo& grafo, const std::string& nomeArquivo);