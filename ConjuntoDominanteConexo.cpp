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

/***********************************************************
 *          Problema - Conjunto Dominate Conexo            *
 ***********************************************************/

#include "ConjuntoDominanteConexo.h"

ConjuntoDominanteConexo::ConjuntoDominanteConexo(Grafo *instancia) {
    if(!instancia->isConexo()){
        cout << "Grafo Desconexo - Não é possível gerar um Conjunto Dominante Conexo." << endl;
        exit(0);
    }
    this->instancia = instancia;
}

ConjuntoDominanteConexo::~ConjuntoDominanteConexo() {
    this->instancia->~Grafo();
}

