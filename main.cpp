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
        arquivo << grafo->getOrdem() << endl;

        //Percorrendo o grafo
        No *p = grafo->getPrimeiroNo();
        Aresta * a;
        int idNoOrigem, idNoDestino;

        while (p != nullptr) {
            idNoOrigem = p->getId();
            a = p->getPrimeiraAresta();

            while (a != nullptr) {
                idNoDestino = a->getLabel();

                if (!grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
                    arquivo << idNoOrigem << " " << idNoDestino;
                } else if (grafo->getArestaPonderada() && !grafo->getNoPonderado()) {
                    arquivo << idNoOrigem << " " << idNoDestino << " " << a->getPeso();
                } else if (grafo->getNoPonderado() && !grafo->getArestaPonderada()) {
                    float pesoNoOrigem, pesoNoDestino;
                    pesoNoOrigem = p->getPeso();
                    pesoNoDestino = grafo->getNo(idNoDestino)->getPeso();

                    arquivo << idNoOrigem << " " << pesoNoOrigem << " " << idNoDestino << " " << pesoNoDestino;
                } else if (grafo->getArestaPonderada() && grafo->getNoPonderado()) {
                    float pesoNoOrigem, pesoNoDestino, pesoAresta;
                    pesoNoOrigem = p->getPeso();
                    pesoNoDestino = grafo->getNo(idNoDestino)->getPeso();
                    pesoAresta = a->getPeso();

                    arquivo << idNoOrigem << " " << pesoNoOrigem << " " << idNoDestino << " " << pesoNoDestino << " " << pesoAresta;
                }

                arquivo << endl;

                a = a->getProximaAresta();
            }

            p = p->getProximoNo();

            //remover nó para evitar duplicação de arestas no arquivo em caso de grafo dirigido
            if (!grafo->getDirigido())
                grafo->removerNo(idNoOrigem);

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
    int vertice;
    switch (opcao) {

            //BFS
        case 1:
        {
            cout << "Informe um vértice:" << endl;
            cin >> vertice;

            grafo->buscaBFS(vertice);

            break;
        }

            //DFS
        case 2:
        {
            cout << "Informe um vértice:" << endl;
            cin >> vertice;

            grafo->buscaDFS(vertice);
            break;
        }

            //Fecho transitivo direto
        case 3:
        {
            cout << "Informe um vértice:" << endl;
            cin >> vertice;
            
            grafo->fechoTransitivoDireto(vertice);
            break;
        }

            //Fecho transitivo indireto
        case 4:
        {
            cout << "Informe um vértice:" << endl;
            cin >> vertice;
            
            grafo->fechoTransitivoIndireto(vertice);
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
        //system("clear");
        opcao = menu();

        if (arquivo_saida.is_open())
            selecionar(opcao, grafo, arquivo_saida);

        else
            cout << "Não foi possível abrir o arquivo de saída." << endl;
    }

    //gravar o grafo
    if (opcao == 0) {
        escrita(arquivo_saida, grafo);
    }

    return 0;
}

/************************************************************
 *                  PROGRAMA PRINCIPAL                      *
 ***********************************************************/
int main(int argc, char** argv) {
    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {
        cout << "ERROR: Esperando: ./<nome_programa> <arquivo_entrada> <arquivo_saida> <dirigido> <ponderado_aresta> <ponderado_no> " << endl;
        return 1;
    }

    string nome_programa(argv[0]);
    string arq_entrada_nome(argv[1]);

    if (arq_entrada_nome.find(".") <= arq_entrada_nome.size()) {
        string instance = arq_entrada_nome.substr(0, arq_entrada_nome.find("."));
        cout << "Executando o  " << nome_programa << " com a instância " << instance << " ... " << endl;
    }

    ifstream arq_entrada;
    ofstream arq_saida;

    arq_entrada.open(argv[1], ios::in);
    arq_saida.open(argv[2], ios::out | ios::trunc);

    Grafo *grafo;

    if (arq_entrada.is_open()) {
        grafo = leitura(arq_entrada, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    } else
        cout << "Não foi possível abrir o arquivo " << arq_entrada_nome << endl;
    
    mainMenu(arq_saida, grafo);

    //Fechando arquivo de entrada
    arq_entrada.close();

    //Fechando arquivo de saída
    arq_saida.close();

    return 0;
}