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
 *              Implementação do TAD Grafo                  *
 ***********************************************************/

#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

class Grafo {
public:
    //Construtor
    Grafo(int ordem, bool dirigido, bool arestaPonderada, bool noPonderado);
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
private:
    //Atributos
    int ordem;
    int nArestas;
    bool dirigido;
    bool arestaPoderada;
    bool noPonderado;
    No* primeiroNo;
    No* ultimoNo;

};

#endif /* GRAFO_H */

