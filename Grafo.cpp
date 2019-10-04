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
 * @param dirigido
 * @param arestaPonderada
 * @param noPonderado
 */
Grafo::Grafo(bool dirigido, bool arestaPonderada, bool noPonderado) {
    this->dirigido = dirigido;
    this->arestaPoderada = arestaPonderada;
    this->noPonderado = noPonderado;
    this->ultimoNo = this->primeiroNo = nullptr;
    this->nArestas = 0;
    this->ordem = 0;
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
    //atualizar a ordem do grafo
    this->ordem++;
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
    //atualizar o número de arestas
    this->nArestas++;
}

/**
 * Remover nó do grafo
 * @param id
 */
void Grafo::removerNo(int id) {
    //excluir somente se o nó existir
    if (this->buscarNo(id)) {
        //remoção das arestas
        if (this->dirigido) {
            //percorrer toda a lista de nós buscando onde o nó id é nó de origem e exluir a aresta
            for (No *p = this->primeiroNo; p != nullptr; p = p->getProximoNo()) {
                //remove e atualiza o número de aresta do grafo
                if (p->removerAresta(id, this->dirigido))
                    this->nArestas--;
            }
        } else {
            //removendo a aresta id do nó adjacente ao nó id
            No *no = this->getNo(id);

            //percorrer as arestas do nó
            for (Aresta *p = no->getPrimeiraAresta(); p != nullptr; p = p->getProximaAresta()) {
                //nó destino
                No *adj = this->getNo(p->getLabel());
                adj->removerAresta(id, this->dirigido);
                this->nArestas--;
            }
        }

        //remoção do nó e manutenção da lista de nos
        No *aux = this->primeiroNo;
        No *anterior = nullptr;
        while (aux->getId() != id) {
            anterior = aux;
            aux = aux->getProximoNo();
        }

        //mantendo a lista
        if (anterior != nullptr)
            anterior->setProximoNo(aux->getProximoNo());
        else
            this->primeiroNo = aux->getProximoNo();

        if (aux == this->ultimoNo)
            this->ultimoNo = anterior;

        if (aux->getProximoNo() == this->ultimoNo)
            this->ultimoNo = aux->getProximoNo();

        aux->removerTodasAresta();
        //delete aux;

        //atualizar a ordem do grafo
        this->ordem--;
    }
}

/**
 * Imprime todos os nós com suas arestas na tela
 */
void Grafo::imprimir() {
    if (this->primeiroNo != nullptr) {
        No *p = this->primeiroNo;

        //percorrendo a lista de nó
        while (p != nullptr) {
            cout << p->getId() << ": ";

            //imprimir as arestas
            Aresta *a = p->getPrimeiraAresta();
            while (a != nullptr) {
                cout << a->getLabel() << "->";
                a = a->getProximaAresta();
            }
            cout << "" << endl;
            p = p->getProximoNo();
        }
    } else {
        cout << "Grafo nulo";
    }
}

/**
 * Realiza uma cópia da estrutura do grafo
 * @return 
 */
Grafo *Grafo::clone() {
    if (this->primeiroNo != nullptr) {
        Grafo * g = new Grafo(this->dirigido, this->arestaPoderada, this->noPonderado);

        No *p = this->primeiroNo;
        while (p != nullptr) {
            Aresta *a = p->getPrimeiraAresta();

            while (a != nullptr) {
                if (!g->getArestaPonderada() && !g->getNoPonderado()) {

                    g->inserirAresta(p->getId(), a->getLabel(), 0);

                } else if (g->getArestaPonderada() && !g->getNoPonderado()) {

                    g->inserirAresta(p->getId(), a->getLabel(), a->getLabel());

                } else if (g->getNoPonderado() && !g->getArestaPonderada()) {

                    g->inserirAresta(p->getId(), a->getLabel(), 0);
                    g->getNo(p->getId())->setPeso(p->getPeso());

                    No *destino = this->getNo(a->getLabel());
                    g->getNo(destino->getId())->setPeso(destino->getPeso());

                } else if (g->getArestaPonderada() && g->getNoPonderado()) {

                    g->inserirAresta(p->getId(), a->getLabel(), a->getLabel());
                    g->getNo(p->getId())->setPeso(p->getPeso());

                    No *destino = this->getNo(a->getLabel());
                    g->getNo(destino->getId())->setPeso(destino->getPeso());
                }
                a = a->getProximaAresta();
            }
            p = p->getProximoNo();
        }
    } else {
        cout << "Grafo nulo";
    }
}

/**
 * Caminhamento em largura
 * @param id
 */
void Grafo::buscaBFS(int id) {
    if (this->primeiroNo == nullptr) {
        cout << "Grafo nulo" << endl;
    } else if (!this->buscarNo(id)) {
        cout << "Vértice não encontrado." << endl;
    } else {
        queue<No*> fila; // enfileirando p
        int visitados[this->getOrdem()], cont = 1;

        for (int i = 0; i < this->getOrdem(); i++)
            visitados[i] = 0;

        //iniciar a visita do primeiro nó
        fila.push(this->getNo(id));
        //marcar o nó p como visitado
        visitados[id - 1] = cont;

        //percorrendo a lista de nó
        while (!fila.empty()) {
            //visitar os vizinhos que ainda não foram visitados
            No *p = fila.front();
            Aresta *a = p->getPrimeiraAresta();
            while (a != nullptr) {
                No *v = this->getNo(a->getLabel());

                if (visitados[v->getId() - 1] == 0) {
                    fila.push(v);
                    cont++;
                    visitados[v->getId() - 1] = cont;
                }
                a = a->getProximaAresta();
            }
            //desenfileira
            fila.pop();
        }

        //imprimir os vértices visitados
        cout << "Nós visitados a partir do vértice " << id << ": " << endl;
        for (int i = 0; i<this->getOrdem(); i++) {
            if (visitados[i] != 0) {
                id = i + 1;
                cout << this->getNo(id)->getId() << "(" << visitados[i] << "º)" << endl;

            }
        }
    }
}

/**
 * Imprime a busca em profundidade a partir do nó buscado
 * @param id
 * @return 
 */
void Grafo::buscaDFS(int id) {
    if (this->primeiroNo == nullptr) {
        cout << "Grafo nulo" << endl;
    } else if (!this->buscarNo(id)) {
        cout << "Vértice não encontrado." << endl;
    } else {
        int visitados[this->getOrdem()], cont = 1;

        for (int i = 0; i<this->getOrdem(); i++)
            visitados[i] = 0;

        //iniciar a busca
        this->dfs(id - 1, visitados, cont);

        //imprimir os vértices visitados
        cout << "Nós visitados a partir do vértice " << id << ": " << endl;
        for (int i = 0; i<this->getOrdem(); i++) {
            if (visitados[i] != 0) {
                id = i + 1;
                cout << this->getNo(id)->getId() << "(" << visitados[i] << "º)" << endl;

            }
        }
    }
}

/**
 * Realiza a busca em profundidade dos nós
 * @param i
 * @param visitados
 * @param cont
 * @return 
 */
void Grafo::dfs(int i, int *visitados, int cont) {
    No *p = this->getNo(i + 1);
    Aresta *a = p->getPrimeiraAresta();

    //Marcar o nó como visitado
    visitados[i] = cont;

    //visitar seus vizinhos
    while (a != nullptr) {
        //atualizar o i
        i = a->getLabel() - 1;

        if (visitados[i] == 0)
            dfs(i, visitados, cont + 1);

        a = a->getProximaAresta();
    }
}

/**
 * Imprime o id de todo nó alcançavel pelo no de id passado
 * @param id
 */
void Grafo::fechoTransitivoDireto(int id) {
    if (this->primeiroNo == nullptr) {
        cout << "Grafo nulo" << endl;
    } else if (!this->getDirigido()) {
        cout << "Grafo não orientado." << endl;
    } else if (!this->buscarNo(id)) {
        cout << "Vértice não encontrado." << endl;
    } else {
        cout << "Fecho transitivo direto do nó " << id << ":" << endl;
        No* p = this->getNo(id);
        Aresta* a = p->getPrimeiraAresta();
        while (a != (p->getUltimaAresta()->getProximaAresta())) {
            cout << "No: " << a->getLabel() << endl;
            a = a->getProximaAresta();
        }
    }
}

/**
 * Imprime todo nó que pode alcançar o nó de id por um caminho direcionado
 * @param id
 */
void Grafo::fechoTransitivoIndireto(int id) {
    if (this->primeiroNo == nullptr) {
        cout << "Grafo nulo" << endl;
    } else if (!this->getDirigido()) {
        cout << "Grafo não orientado." << endl;
    } else if (!this->buscarNo(id)) {
        cout << "Vértice não encontrado." << endl;
    } else {
        cout << "Fecho transitivo indireto do nó " << id << ":" << endl;

        No* busca = this->primeiroNo;
        Aresta* a = busca->getPrimeiraAresta();
        while (busca != nullptr) {
            while (a != (busca->getUltimaAresta()->getProximaAresta())) {
                if (a->getLabel() == id)
                    cout << "No: " << busca->getId() << endl;
                a = a->getProximaAresta();
            }
            busca = busca->getProximoNo();
            a = busca->getPrimeiraAresta();
        }
    }

}

/**
 * Imprime o caminho mínimo entre dois vértices e cancula seu custo pelo 
 * algoritmo de Djikstra
 * 
 * @param origem
 * @param destino
 */
void Grafo::caminhoMinimoDjikstra(int origem, int destino) {

}

/**
 * Imprime o caminho mínimo entre dois vértices e cancula seu custo pelo 
 * algoritmo de Floyd
 * 
 * @param origem
 * @param destino
 */
void Grafo::caminhoMinimoFloyd(int origem, int destino) {

}

/**
 * Dado um grafo não orientado a função retorna o conjunto de n-1 arestas que
 * conectam todos os nós do grafo e cujo o peso somatório dos pesoso das arestas
 * é mínimo usando o algoritimo de Prim
 * @return 
 */
Grafo* Grafo::arvoreGeradoraMinimaPrim() {

}

/**
 * Ordena as arestas pelo peso
 * @param vetor
 * @param n
 */
void Grafo::ordenaArestaPeso(Aresta* vetor, int n){
    
}

/**
 * Dado um grafo não orientado a função retorna o conjunto de n-1 arestas que
 * conectam todos os nós do grafo e cujo o peso somatório dos pesoso das arestas
 * é mínimo usando o algoritimo Kruskall
 * @return 
 */
Grafo* Grafo::arvoreGeradoraMinimaKruskall() {

}

void Grafo::fechoTriadico() {

}

