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
 *               Implementação do TAD No                    *
 ***********************************************************/

#ifndef NO_H
#define NO_H
#include <iostream>
#include "Aresta.h"

using namespace std;

class No {
public:
    //Contrutor
    No(int id);
    //Destrutor
    ~No();
    //Gets
    int getId();
    float getPeso();
    unsigned int getGrau();
    unsigned int getGrauSaida();
    Aresta *getPrimeiraAresta();
    Aresta *getUltimaAresta();
    No *getProximoNo();
    //Sets
    void setPeso(float peso);
    void setProximoNo(No *proximoNo);
    //Outros métodos
    bool buscarAresta(int label);
    Aresta *getAresta(int label);
    void inserirAresta(int label, float peso);
    bool removerAresta(int label, bool dirigido);
    void removerTodasAresta();
    void incrementarGrau();
    void incrementarGrauSaida();
    void decrementarGrau();
    void decrementarGrauSaida();
private:
    int id;
    float peso;
    unsigned int grau;
    unsigned int grauSaida;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
    No* proximoNo;
};

#endif /* NO_H */

