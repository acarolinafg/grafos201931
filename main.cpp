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

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "No.h"
#include "Aresta.h"


using namespace std;

/**
 * Realiza a leitura do arquivo e transforma em um grafo
 * @param arquivo
 * @param dirigido
 * @param arestaPonderada
 * @param noPonderado
 * @return 
 */
Grafo *leitura(ifstream& arquivo, int dirigido, int arestaPonderada, int noPonderado) {
    //Variáveis auxiliares
    int ordem;
    int idNoOrigem;
    int idNoDestino;

    //Leitura da Ordem do grafo
    arquivo >> ordem;

    //Criação do Grafo
    Grafo *grafo = new Grafo(dirigido, arestaPonderada, noPonderado);

    //Leitura do arquivo
    if (!grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
        while (arquivo >> idNoOrigem >> idNoDestino) {
            grafo->inserirAresta(idNoOrigem, idNoDestino, 0);
        }
    } else if (grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
        float pesoAresta;

        while (arquivo >> idNoOrigem >> idNoDestino >> pesoAresta) {
            grafo->inserirAresta(idNoOrigem, idNoDestino, pesoAresta);
        }
    } else if (grafo->getNoPonderado() && !grafo->getArestaPonderada()) {
        float pesoNoOrigem, pesoNoDestino;

        while (arquivo >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino) {
            grafo->inserirAresta(idNoOrigem, idNoDestino, 0);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    } else if (grafo->getArestaPonderada() && grafo->getNoPonderado()) {
        float pesoNoOrigem, pesoNoDestino, pesoAresta;

        while (arquivo >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino >> pesoAresta) {
            grafo->inserirAresta(idNoOrigem, idNoDestino, pesoAresta);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    return grafo;
}

/**
 * Grava um grafo em um arquivo
 * @param arquivo
 * @param grafo
 */
void escrita(ofstream& arquivo, Grafo *grafo) {
    if (grafo != nullptr && grafo->getOrdem() > 0) {
        //Gravando a ordem do grafo
        arquivo << grafo->getOrdem();

        //Percorrendo o grafo
        No *p = grafo->getPrimeiroNo();
        Aresta * a;

        while (p != nullptr) {
            a = p->getPrimeiraAresta();

            while (a != nullptr) {
                if (!grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
                    arquivo << p->getId() << a->getLabel();
                } else if (grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
                    arquivo << p->getId() << a->getLabel() << a->getPeso();
                } else if (grafo->getNoPonderado() && !grafo->getArestaPonderada()) {
                    float pesoNoOrigem, pesoNoDestino;
                    pesoNoOrigem = p->getPeso();
                    pesoNoDestino = grafo->getNo(a->getLabel())->getPeso();

                    arquivo << p->getId() << pesoNoOrigem << a->getLabel() << pesoNoDestino;
                } else if (grafo->getArestaPonderada() && grafo->getNoPonderado()) {
                    float pesoNoOrigem, pesoNoDestino, pesoAresta;
                    pesoNoOrigem = p->getPeso();
                    pesoNoDestino = grafo->getNo(a->getLabel())->getPeso();
                    pesoAresta = a->getPeso();

                    arquivo << p->getId() << pesoNoOrigem << a->getLabel() << pesoNoDestino << pesoAresta;
                }

                a = a->getProximaAresta();
            }

            p = p->getProximoNo();
        }
    }
}

/**
 * Imprime o menu e retorna a opção escolhida pelo usuário
 * @return 
 */
int menu() {

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Imprimir caminhamento em largura" << endl;
    cout << "[2] Imprimir caminhamento em profundidade" << endl;
    cout << "[3] Fecho transitivo direto" << endl;
    cout << "[4] Fecho transitivo indireto" << endl;
    cout << "[5] Caminho Mínimo Dijkstra" << endl;
    cout << "[6] Caminho Mínimo Floyd" << endl;
    cout << "[7] Árvore Geradora Mínima de Prim" << endl;
    cout << "[8] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[9] Fecho triádico" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

/**
 * Execução do método escolhido
 * @param opcao
 * @param grafo
 * @param arquivo_saida
 */
void selecionar(int opcao, Grafo* grafo, ofstream& arquivo_saida) {

    switch (opcao) {

            //DFS
        case 1:
        {

            break;
        }

            //BFS
        case 2:
        {

            break;
        }

            //Fecho transitivo direto
        case 3:
        {

            break;
        }

            //Fecho transitivo indireto
        case 4:
        {



            break;
        }

            //Algoritmo de Dijkstra
        case 5:
        {

            break;
        }

            //Algoritmo de Floyd
        case 6:
        {

            break;
        }

            //Algoritmo de Prim
        case 7:
        {


            break;
        }

            //Algoritimo de Kruskal
        case 8:
        {

            break;
        }

            //Fecho triádico
        case 9:
        {

            break;
        }

    }

}

/**
 * Junção do menu com as opções de escolha
 * @param arquivo_saida
 * @param grafo
 * @return 
 */
int mainMenu(ofstream& arquivo_saida, Grafo* grafo) {

    int opcao = 1;

    while (opcao != 0) {
        system("clear");
        opcao = menu();

        if (arquivo_saida.is_open())
            selecionar(opcao, grafo, arquivo_saida);

        else
            cout << "Não foi possível abrir o arquivo de saída." << endl;

        arquivo_saida << endl;

    }

    return 0;
}

/************************************************************
 *                  PROGRAMA PRINCIPAL                      *
 ***********************************************************/
int main(int argc, char** argv) {

    return 0;
}