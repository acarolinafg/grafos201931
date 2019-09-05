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

#ifndef ARESTA_H
#define ARESTA_H

using namespace std;

class Aresta {
public:
    //Construtor
    Aresta(int idNo);
    //Destrutor
    ~Aresta();
    //Gets
    int getIdNo();
    float getPeso();
    Aresta *getProximaAresta();
    //Sets
    void setPeso(float peso);
    void setProximaAresta(Aresta *proximaAresta);
private:
    int idNo;
    float peso;
    Aresta *proximaAresta;
};

#endif /* ARESTA_H */

