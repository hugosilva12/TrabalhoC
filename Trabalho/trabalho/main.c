
/**
 * @file main.c
 * @author Hugo Silva
 * @date  5 Novembro 2020
 * @brief Ficheiro que contém a função principal do programa
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"
#include "Funcionario.h"
#include "GestaoFuncionarios.h"
#include "TabelaIrs.h"
#include "TabelaSegurancaSocial.h"
#include "ProcessamentoSalarioFX.h"

/**
 * Função principal do Programa
 * @return 0 em caso de sucesso, um número diferente de 0 em caso de erro
 */
int main() {
    ListaFuncionarios listaFuncionarios = {.nrFuncionarios = 0 ,.tamanho = 0 };
    TabelaSegurancaSocial tabelaSegurancaSocial = {.numeroLinhas = 0, .tamanho = 0};
    TabelaIrs tabelaIrs = {.numeroLinhas = 0, .tamanho = 0};
    ListaTodosVencimentosProcessados relatoriosVencimentosProcessados = {.janeiro.nrProcessamentos = 0,.fevereiro.nrProcessamentos = 0,.marco.nrProcessamentos = 0,.abril.nrProcessamentos = 0,.maio.nrProcessamentos = 0,.junho.nrProcessamentos = 0,.julho.nrProcessamentos = 0,.agosto.nrProcessamentos = 0,.setembro.nrProcessamentos = 0,.outubro.nrProcessamentos = 0,.novembro.nrProcessamentos = 0,.dezembro.nrProcessamentos = 0,.nrMesesProcessados =0};
    menuPrincipal(&listaFuncionarios,&tabelaSegurancaSocial,&tabelaIrs,&relatoriosVencimentosProcessados);
    if(listaFuncionarios.tamanho != 0){libertarMemoriaFuncionarios(&listaFuncionarios);}
    if(tabelaSegurancaSocial.tamanho != 0){ libertarMemoriaTabelaSS(&tabelaSegurancaSocial);}
    if(tabelaIrs.tamanho != 0){ libertarMemoriaTabelaIRS(&tabelaIrs);}
    libertarMemoriaRelatoriosProcessados(&relatoriosVencimentosProcessados);  
    printf("Terminou o programa!");
    return 0;
}

