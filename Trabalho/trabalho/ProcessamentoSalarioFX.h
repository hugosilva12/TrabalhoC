/**
 * @file ProcessamentoSalarioFX.h
 * @author Hugo Silva
 * @date 27 Novembro 2020
 * @brief Biblioteca com funções de importação/escrita em ficheiro 
 * 
 *  Biblioteca com a função de importação de ficheiros para processamento e funcção de escrita de relatório dos vencimentos processados
 */
#ifndef PROCESSAMENTO_SALARIOFX_H
#define PROCESSAMENTO_SALARIOFX_H
#include "ProcessamentoSalario.h"

void carregarFicheiroProcessamento(ListaProcessamentos *lista, char*filename,char*filerelatorio,ListaVencimentosProcessadosMes *listaVencimentos);
void gerarRelatorio(ListaVencimentosProcessadosMes lista);
void obterRelatorio(ListaVencimentosProcessadosMes *lista);
void importarFicheiroProcessamento(ListaProcessamentos *lista, char*filename);
void libertarListaVencimentosProcessados(ListaVencimentosProcessadosMes *lista);
void libertarMemoriaDadosProcessamento(ListaProcessamentos *lista);
void libertarMemoriaRelatorios(ListaTodosVencimentosProcessados *relatorios);
void obterTodosRelatoriosProcessados(ListaTodosVencimentosProcessados *relatorios);
void guardarRelatoriosProcessados(ListaTodosVencimentosProcessados relatorios);
void inicializacaoRelatorios(ListaTodosVencimentosProcessados *relatorios, int memoria);
void libertarMemoriaRelatoriosProcessados(ListaTodosVencimentosProcessados *relatorios);
#endif 

