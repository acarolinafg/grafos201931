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
 *             Definindo os métodos do Grafo                *
 ***********************************************************/
#include <valarray>

#include "Grafo.h"
#include "No.h"

/**
 * Constrtutor de um objeto Grafo
 * @param ordem
 * @param dirigido
 * @param arestaPonderada
 * @param noPonderado
 */
Grafo::Grafo(int ordem, bool dirigido, bool arestaPonderada, bool noPonderado) {
    this->ordem = ordem;
    this->dirigido = dirigido;
    this->arestaPoderada = arestaPonderada;
    this->noPonderado = noPonderado;
    this->ultimoNo = this->primeiroNo = nullptr;
    this->nArestas = 0;
}

/**
 * Destrutor do Grafo
 */
Grafo::~Grafo() {
    No *prox = this->primeiroNo;

    while (prox != nullptr) {
        prox->removerTodasAresta();
        No *aux = prox->getProximoNo();
        delete prox;
        prox = aux;
    }
}

/**
 * Retorna o número de nós do grafo
 * @return int ordem
 */
int Grafo::getOrdem() {
    return this->ordem;
}

/**
 * Retorna o número de arestas do grafo
 * @return int nArestas
 */
int Grafo::getNArestas() {
    return this->nArestas;
}

/**
 * Retorna se o grafo é ou não direcionado
 * @return bool dirigido
 */
bool Grafo::getDirigido() {
    return this->dirigido;
}

/**
 * Retorna se o grafo é ou não é ponderado nas arestas
 * @return bool arestaPonderada
 */
bool Grafo::getArestaPonderada() {
    return this->arestaPoderada;
}

/**
 * Retorna se o grafo é ou não ponderado nos vértices
 * @return 
 */
bool Grafo::getNoPonderado() {
    return this->noPonderado;
}

/**
 * Retorna o ponteiro para primeira posição na lista de nós dos grafo
 * @return 
 */
No *Grafo::getPrimeiroNo() {
    return this->primeiroNo;
}

/**
 * Retorna o ponteiro para o último nó inserido no grafo
 * @return 
 */
No *Grafo::getUltimoNo() {
    return this->ultimoNo;
}

/**
 * Busca um nó do grafo
 * @param id
 * @return 
 */
bool Grafo::buscarNo(int id) {
    if (this->primeiroNo != nullptr) {
        for (No*prox = this->primeiroNo; prox != nullptr; prox = prox->getProximoNo()) {
            if(prox->getId() == id){
                return true;
            }
        }
    }
    return false;
}

/**
 * Retorna um nó buscado 
 * @param id
 * @return 
 */
No *Grafo::getNo(int id){
    if (this->primeiroNo != nullptr) {
        for (No*prox = this->primeiroNo; prox != nullptr; prox = prox->getProximoNo()) {
            if(prox->getId() == id){
                return prox;
            }
        }
    }
    return nullptr;
}

/**
 * Inserir um nó do grafo
 * @param id
 */
void Grafo::inserirNo(int id){
    //verifica se já existe nó
    if(this->primeiroNo!= nullptr){
        //inserir o  nó no final da lista
        No *no = new No(id);
        this->ultimoNo->setProximoNo(no);
        this->ultimoNo = no;
        
    }else{
        this->primeiroNo = new No(id);
        this->ultimoNo = this->primeiroNo;
    }
}
