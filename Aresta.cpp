/************************************************************
 * Universidade Federal de Juiz de Fora - UFJF              *
 * Instituto de Ciências Exatas                             *
 * Departamento de Ciência da Computação                    *
 * Disciplina: DCC059 – Teoria dos Grafos Período: 2019-3   *
 * Professor: Stênio Sã Rosário Furtado Soares              *
 * Aluna: Ana Carolina Fidelis Gonçalves                    *
 *                                                          *
 *                 TRABALHO PRÁTICO GRUPO 13                *
 ************************************************************/

/************************************************************
 *            Definindo os métodos da Aresta                *
 ***********************************************************/

#include "Aresta.h"

/**
 * Construtor da Aresta
 * @param label
 */
Aresta::Aresta(int label) {
    this->label = label;
    this->peso = 0;
    this->proximaAresta = nullptr;
}

/**
 * Destrutor da Aresta
 */
Aresta::~Aresta() {
    if (this->proximaAresta != nullptr) {
        delete this->proximaAresta;
        this->proximaAresta = nullptr;
    }
}

/**
 * Retorna o identificador da aresta (nó de destino)
 * @return int label
 */
int Aresta::getLabel() {
    return this->label;
}

/**
 * Retorna o peso da aresta
 * @return float peso
 */
float Aresta::getPeso() {
    return this->peso;
}

/**
 * Retorna a próxima aresta adjacente ao nó
 * @return Aresta *proximaAresta
 */
Aresta * Aresta::getProximaAresta() {
    return this->proximaAresta;
}

/**
 * Armazena o peso da aresta
 * @param peso
 */
void Aresta::setPeso(float peso) {
    this->peso = peso;
}

/**
 * Armazena a próxima aresta adjacente ao nó
 * @param proximaAresta
 */
void Aresta::setProximaAresta(Aresta* proximaAresta) {
    this->proximaAresta = proximaAresta;
}

