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
 *             Definindo os métodos do Nó                   *
 ***********************************************************/

#include "No.h"

/**
 * Contruturor do Nó
 * @param id
 */
No::No(int id) {
    this->id = id;
    this->peso = 0;
    this->grau = 0;
    this->grauSaida = 0;
    this->primeiraAresta = nullptr;
    this->ultimaAresta = nullptr;
    this->proximoNo = nullptr;
}

/**
 * Destrtutor do Nó
 */
No::~No() {
    Aresta *proxima = this->primeiraAresta;

    while (proxima != nullptr) {
        Aresta *aux = proxima->getProximaAresta();
        delete proxima;
        proxima = aux;
    }
}

/**
 * Retorna o identificador do nó
 * @return int id
 */
int No::getId() {
    return this->id;
}

/**
 * Retorna o peso do nó
 * @return float peso
 */
float No::getPeso() {
    return this->peso;
}

/**
 * Retorna o grau do nó (em caso de grafo direcionado representa o grau 
 * de entrada)
 * @return unsigned int grau
 */
unsigned int No::getGrau() {
    return this->grau;
}

/**
 * Retorna o grau dde saída de um nó
 * @return unsigned int grauSaida
 */
unsigned int No::getGrauSaida() {
    return this->grauSaida;
}

/**
 * Retorna a primeira aresta adjacente ao nó
 * @return Aresta *primeiraAresta
 */
Aresta *No::getPrimeiraAresta() {
    return this->primeiraAresta;
}

/**
 * Retorna a última aresta adjacente ao nó
 * @return Aresta *primeiraAresta
 */
Aresta *No::getUltimaAresta() {
    return this->ultimaAresta;
}

/**
 * Retorna o próximo nó
 * @return No *proximoNo
 */
No *No::getProximoNo() {
    return this->proximoNo;
}

/**
 * Armazena o peso do nó
 * @param peso
 */
void No::setPeso(float peso) {
    this->peso = peso;
}

/**
 * Armazena o próximo nó
 * @param proximoNo
 */
void No::setProximoNo(No* proximoNo) {
    this->proximoNo = proximoNo;
}

/**
 * Busca se uma aresta existe na lista de adjacência
 * @param label
 * @return bool true|false
 */
bool No::buscarAresta(int label) {
    //verifica se a lista de arestas adjacentes está vazia
    if (this->primeiraAresta != nullptr) {
        //percorrendo a lista a partir da primeira aresta
        for (Aresta *prox = this->primeiraAresta; prox != nullptr; prox = prox->getProximaAresta()) {
            if (prox->getLabel() == label)
                return true;
        }
    }
    return false;
}

/**
 * Retorna uma aresta da lista de adjacência
 * @param label
 * @return Aresta *aresta
 */
Aresta *No::getAresta(int label) {
    //verifica se a lista de arestas adjacentes está vazia
    if (this->primeiraAresta != nullptr) {
        //percorrendo a lista a partir da primeira aresta
        for (Aresta *prox = this->primeiraAresta; prox != nullptr; prox = prox->getProximaAresta()) {
            if (prox->getLabel() == label)
                return prox;
        }
    }
    return nullptr;
}

/**
 * Inserir uma nova aresta adjacente ao nó
 * @param label
 * @param peso
 */
void No::inserirAresta(int label, float peso) {
    //verifica se já existe aresta
    if (this->primeiraAresta != nullptr) {
        //cria uma nova aresta
        Aresta *aresta = new Aresta(label);
        aresta->setPeso(peso);

        //aloca a aresta criada na última posição da lista de arestas
        this->ultimaAresta->setProximaAresta(aresta);
        this->ultimaAresta = aresta;
    } else {
        //se é a primeira aresta
        this->primeiraAresta = new Aresta(label);
        this->primeiraAresta->setPeso(peso);
        this->ultimaAresta = this->primeiraAresta;
    }
}

/**
 * Remove a aresta adjacente ao nó
 * @param id
 * @param dirigido
 * @return 
 */
bool No::removerAresta(int label, bool dirigido) {
    //se a aresta existir vamos excluir 
    if(this->buscarAresta(label)){
        Aresta *aux = this->primeiraAresta;
        Aresta *anterior = nullptr;
        //percorrer a lista de arestas 
        while(aux->getLabel()!= label){
            anterior = aux;
            aux = aux->getProximaAresta();
        }
        
        //mantendo a lista
        if(anterior!= nullptr)
            anterior->setProximaAresta(aux->getProximaAresta());
        else
            this->primeiraAresta = aux->getProximaAresta();
        
        if(aux == this->ultimaAresta)
            this->ultimaAresta = anterior;
        
        if(aux->getProximaAresta() == this->ultimaAresta)
            this->ultimaAresta = aux->getProximaAresta();
        
        //delete aux;
        
        //verificando se o grafo é direcionado
        if(dirigido){
            this->decrementarGrauSaida();
        }else{
            this->decrementarGrau();
        }
        return true;
    }
    return false;
}

/**
 * Remove todas as arestas do nó
 */
void No::removerTodasAresta(){
    if(this->primeiraAresta!= nullptr){
        Aresta *prox = this->primeiraAresta;
        
        while(prox!= nullptr){
            Aresta *aux = prox->getProximaAresta();
            delete prox;
            prox = aux;
        }
        
        //atualizar o grau do nó
        this->grauSaida = this->grau = 0;
        
        //atualizar o ponteiro da lista de adjacentes
        this->primeiraAresta = this->ultimaAresta = nullptr;
    }
}

/**
 * Incrementa em uma unidade o grau do nó
 */
void No::incrementarGrau() {
    this->grau++;
}

/**
 * Incrementa em uma unidade o grau do nó
 */
void No::incrementarGrauSaida() {
    this->grauSaida++;
}

/**
 * Decrementa o grau do nó em uma unidade
 */
void No::decrementarGrau() {
    this->grau--;
}

/**
 * Decrementa o grau de saída em uma unidade
 */
void No::decrementarGrauSaida() {
    this->grauSaida--;
}