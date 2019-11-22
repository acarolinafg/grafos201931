/************************************************************
 * Universidade Federal de Juiz de Fora - UFJF              *
 * Instituto de Ciências Exatas                             *
 * Departamento de Ciência da Computação                    *
 * Disciplina: DCC059 – Teoria dos Grafos Período: 2019-3   *
 * Professor: Stênio Sã Rosário Furtado Soares              *
 * Aluno(s): Ana Carolina Fidelis Gonçalves                 *
 *           Paulo Sergio de Oliveira Silva                 *
 *                                                          *
 *                 TRABALHO PRÁTICO GRUPO 13                *
 ************************************************************/

/************************************************************
 *              Implementação do TAD Grafo                  *
 ***********************************************************/

#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <valarray>
#include <queue>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

using namespace std;

class Grafo {
public:
    //Construtor
    Grafo(bool dirigido, bool arestaPonderada, bool noPonderado);
    //Destrutor
    ~Grafo();
    //Gets
    int getOrdem();
    int getNArestas();
    bool getDirigido();
    bool getArestaPonderada();
    bool getNoPonderado();
    No *getPrimeiroNo();
    No *getUltimoNo();
    //Outros métodos
    bool buscarNo(int id);
    No *getNo(int id);
    void inserirNo(int id);
    void inserirAresta(int id, int label, float peso);
    void removerNo(int id);
    void imprimir();
    Grafo *clone();
    void buscaBFS(int id);
    void buscaDFS(int id);
    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);
    void caminhoMinimoDjikstra(int origem,int destino);
    void caminhoMinimoFloyd(int origem, int destino);
    Grafo *arvoreGeradoraMinimaKruskall();
    Grafo *arvoreGeradoraMinimaPrim();
    void fechoTriadico();
    bool nulo();
    bool isConexo();
    bool isCompleto();
    bool isNoArticulacao(int id);
private:
    //Atributos
    int ordem;
    int nArestas;
    bool dirigido;
    bool arestaPoderada;
    bool noPonderado;
    No* primeiroNo;
    No* ultimoNo;
    void dfs(int id, int *visitados, int cont);
    void ordenaArestaPeso(Aresta *vetor, int n);
        
};

#endif /* GRAFO_H */

