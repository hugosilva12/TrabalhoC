/**
 * @file FuncionariosFx.h
 * @author Hugo Silva
 * @date 23 Novembro 2020
 * @brief Biblioteca  para guardar e importar lista de funcionários. (parte pública)
 * 
 *  Biblioteca com assinatura das funções de escrita e leitura em ficheiro binário da lista de funcionários 
 */
#ifndef GESTAO_FUNCIONARIOSFX_H
#define GESTAO_FUNCIONARIOSFX_H
#include "GestaoFuncionarios.h"
#define FILE_FUNCIONARIOS "funcionarios.bin"
int obtemContadorfx(char *nomeficheiro);
void carregarFuncionariosFx(ListaFuncionarios *listafuncionarios,char *nomeficheiro);
void guardarFuncionariosFx(ListaFuncionarios *listafuncionarios,char *nomeficheiro);

#endif /* GESTAO_FUNCIONARIOSFX_H */

