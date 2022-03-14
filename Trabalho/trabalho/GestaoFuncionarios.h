/**
 * @file GestaoFuncionarios.h
 * @author Hugo Silva
 * @date 13 Novembro 2020
 * @brief Biblioteca  da lista de funcionários
 * 
 *  Biblioteca com funções de inserção,remoção e edição de funcionários 
 */
#ifndef LISTA_FUNCIONARIOS_H
#define LISTA_FUNCIONARIOS_H
#include "Funcionario.h" 
#define TAMANHO_MAX 5
/** @struct ListaFuncionarios
 * @brief Armazena uma lista de funcionários
 * @var ListaFuncionarios::nrFuncionarios
 *  'nrFuncionarios' número de funcionários da lista
 * @var ListaFuncionarios::tamanho
 *  'tamanho' tamanho da lista de funcionários
 * @var ListaFuncionarios::listafuncionarios
 *  'listafuncionarios' apontador para a estrutura Funcionario
 */
typedef struct {
    int nrFuncionarios;
    int tamanho;
    Funcionario *listafuncionarios; 
} ListaFuncionarios;

int adicionarFuncionario(ListaFuncionarios *listafuncionarios);
int obterIndiceFuncionario(ListaFuncionarios *listafuncionarios, int idFunc );
Funcionario* obterFuncionario(ListaFuncionarios *listafuncionarios, int idFunc );
void atualizaFuncionario(ListaFuncionarios *listafuncionarios,int idFunc);
void apagarFuncionario(ListaFuncionarios *listafuncionarios, int idFunc);
void listarTodosFuncionarios(ListaFuncionarios *listafuncionarios);
void expandirMemoria(ListaFuncionarios *listafuncionarios);
void libertarMemoriaFuncionarios(ListaFuncionarios *listafuncionarios);
void funcaoAlocarMemoria(ListaFuncionarios *lista);
void mostraFuncionario(ListaFuncionarios *listafuncionarios, int idFunc);
#endif /* LISTA_FUNCIONARIOS_H */

