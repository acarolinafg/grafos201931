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
 *             Implementação do TAD Aresta                  *
 ***********************************************************/

#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

using namespace std;

class Aresta {
public:
    //Construtor
    Aresta(int label);
    //Destrutor
    ~Aresta();
    //Gets
    int getLabel();
    float getPeso();
    Aresta *getProximaAresta();
    //Sets
    void setPeso(float peso);
    void setProximaAresta(Aresta *proximaAresta);
private:
    int label;
    float peso;
    Aresta *proximaAresta;
};

#endif /* ARESTA_H */

