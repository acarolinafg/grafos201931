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

#include <cstdlib>
#include <iostream>
#include "Grafo.h"

using namespace std;

/**
 * Realiza a leitura do arquivo e transforma em um grafo
 * @param arquivo
 * @param dirigido
 * @param arestaPonderada
 * @param noPonderado
 * @return 
 */
Grafo *leitura(ifstream& arquivo, int dirigido, int arestaPonderada, int noPonderado){
    //Variáveis auxiliares
    int ordem;
    int idNoOrigem;
    int idNoDestino;
    
    //Leitura da Ordem do grafo
    arquivo >> ordem;
    
    //Criação do Grafo
    Grafo *grafo = new Grafo(dirigido, arestaPonderada, noPonderado);
    
    //Leitura do arquivo
    if(!grafo->getArestaPonderada() && !grafo->getNoPonderado()){
        while(arquivo >> idNoOrigem >> idNoDestino){
            grafo->inserirAresta(idNoOrigem, idNoDestino, 0);
        }
    }else if(grafo->getArestaPonderada() && !grafo->getNoPonderado()){
        float pesoAresta;
        
        while(arquivo >> idNoOrigem >> idNoDestino >> pesoAresta){
            grafo->inserirAresta(idNoOrigem, idNoDestino, pesoAresta);
        }
    }else if(!grafo->getNoPonderado() && !grafo->getArestaPonderada()){
        float pesoNoOrigem, pesoNoDestino;
        
        while(arquivo >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino){
            grafo->inserirAresta(idNoOrigem, idNoDestino, 0);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }else if(grafo->getArestaPonderada() && grafo->getNoPonderado()){
        float pesoNoOrigem, pesoNoDestino, pesoAresta;
        
        while(arquivo >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino >> pesoAresta){
            grafo->inserirAresta(idNoOrigem, idNoDestino, pesoAresta);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }
    
    return grafo;
}

/************************************************************
 *                  PROGRAMA PRINCIPAL                      *
 ***********************************************************/
int main(int argc, char** argv) {

    return 0;
}