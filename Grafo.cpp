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
#include "Grafo.h"

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
            if (prox->getId() == id) {
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
No *Grafo::getNo(int id) {
    if (this->primeiroNo != nullptr) {
        for (No*prox = this->primeiroNo; prox != nullptr; prox = prox->getProximoNo()) {
            if (prox->getId() == id) {
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
void Grafo::inserirNo(int id) {
    //verifica se já existe nó
    if (this->primeiroNo != nullptr) {
        //inserir o  nó no final da lista
        No *no = new No(id);
        this->ultimoNo->setProximoNo(no);
        this->ultimoNo = no;
    } else {
        this->primeiroNo = new No(id);
        this->ultimoNo = this->primeiroNo;
    }
}

/**
 * Inserir aresta 
 * @param id
 * @param label
 * @param peso
 */
void Grafo::inserirAresta(int id, int label, float peso) {
    //inserir nó se ainda não foi inserido no grafo
    if (!this->buscarNo(id))
        this->inserirNo(id);

    //inserir nó adjacente se ele ainda não está no grafo
    if (!this->buscarNo(label))
        this->inserirNo(label);

    No *no = this->getNo(id);
    no->inserirAresta(label, peso);

    //grafo direcionado
    if (this->dirigido) {
        no->incrementarGrauSaida();
    } else {//grafo simples
        //inserir a aresta no adjacente
        No *adj = this->getNo(label);
        adj->inserirAresta(id, peso);

        adj->incrementarGrau();
        no->incrementarGrau();
    }
}

/**
 * Remover nó do grafo
 * @param id
 */
void Grafo::removerNo(int id){
    //excluir somente se o nó existir
    if(this->buscarNo(id)){
        //remoção das arestas
        if(this->dirigido){
            //percorrer toda a lista de nós buscando onde o nó id é nó de origem e exluir a aresta
            for(No *p = this->primeiroNo; p!= nullptr; p = p->getProximoNo()){
                p->removerAresta(id, this->dirigido);
            }
        }else{
           //removendo a aresta id do nó adjacente ao nó id
           No *no = this->getNo(id);
           
           //percorrer as arestas do nó
           for(Aresta *p = no->getPrimeiraAresta(); p!= nullptr; p = p->getProximaAresta()){
               //nó destino
               No *adj = this->getNo(p->getLabel());
               adj->removerAresta(id,this->dirigido);
           }
        }
        
        //remoção do nó e manutenção da lista de nos
        No *aux = this->primeiroNo;
        No *anterior = nullptr;
        while(aux->getId()!= id){
            anterior = aux;
            aux = aux->getProximoNo();
        }
        
        //mantendo a lista
        if(anterior!= nullptr)
            anterior->setProximoNo(aux->getProximoNo());
        else
            this->primeiroNo = aux->getProximoNo();
        
        if(aux == this->ultimoNo)
            this->ultimoNo = anterior;
        
        if(aux->getProximoNo() == this->ultimoNo)
            this->ultimoNo = aux->getProximoNo();
        
        delete aux;
        
        //atualizar a ordem do grafo
        this->ordem--;
    }
}