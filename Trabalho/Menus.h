/**
 * @file Menus.h
 * @author Hugo Silva
 * @date 11 Novembro 2020
 * @brief Biblioteca criada para os menus do programa
 * 
 *  Biblioteca com as assinaturas das funções dos  menus do programa
 */
#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include "GestaoFuncionarios.h"
#include "TabelaIrs.h"
#include "TabelaSegurancaSocial.h"
#include "ProcessamentoSalario.h"
#include "Listagens.h"
void menuPrincipal(ListaFuncionarios *listaFuncionarios, TabelaSegurancaSocial *tabelaSegurancaSocial, TabelaIrs *tabelaIrs,ListaTodosVencimentosProcessados *relatoriosGerados);
void menuEditarFuncionario(Funcionario *func);
void menuPrincipalFuncionarios(ListaFuncionarios *listaFuncionarios);
void menuListagens(ListaFuncionarios listaFuncionarios, PercentagemIdades *relatorioIdades, PercentagemTempoEmpresa *relatorioTempoEmpresa, DespesasAnuais *despesas, RelatorioFaltas *gestaoFaltas,
        RelatorioValorHora *relatorioVhora, PercentagemEstadoCivil *relatorioEstadoCivil);
void imprimirMeses();
void menuTabelasIrs(TabelaIrs * tabela);
void menuProcessamentoSalario(ListaFuncionarios listaFuncionarios,TabelaIrs tabelaIrs, TabelaSegurancaSocial tabelaSegurancaSocial, ListaTodosVencimentosProcessados *relatoriosGuardados);
void menuTabelaSegurancaSocial(TabelaSegurancaSocial *tabelaSegurancaSocial);
#endif /* MENUPRINCIPAL_H */

