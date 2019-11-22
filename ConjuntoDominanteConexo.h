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

#ifndef CONJUNTODOMINANTECONEXO_H
#define CONJUNTODOMINANTECONEXO_H
#include "Grafo.h"

class ConjuntoDominanteConexo {
public:
    ConjuntoDominanteConexo(Grafo *instancia);
    virtual ~ConjuntoDominanteConexo();
private:
    Grafo *instancia;
};

#endif /* CONJUNTODOMINANTECONEXO_H */

