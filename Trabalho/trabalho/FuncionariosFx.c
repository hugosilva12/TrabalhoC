/**
 * @file FuncionariosFx.c
 * @author Hugo Silva
 * @date  23 Novembro 2020
 * @brief Implementação das funções da biblioteca FuncionariosFx.h
 * 
 * Ficheiro c que contém a implementação das funções de leitura e escrita em ficheiro
 */
#include <stdio.h>
#include <stdlib.h>
#include "FuncionariosFx.h"
#include "Funcionario.h"
#include "GestaoFuncionarios.h"
#define MSG_ERRO_FILE "Ficheiro não encontrado"

/**
 * Lê de um ficheiro (caso exista) o número de alunos atualmente na lista
 * @param nomeficheiro nome do ficheiro no qual está o número
 * @return retorna o número lido, caso não tenha sido possível ler retorna 0
 */
int obtemContadorfx(char *nomeficheiro) {
    int contador = 0;
    FILE *fp = fopen(nomeficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    } else {
        puts(MSG_ERRO_FILE);
    }
    return contador;
}
/**
 * Lê dados de um ficheiro (caso exista) e preenche a lista de funcionários e o seu número
 * @param listafuncionarios apontador para a lista de funcionários que será preenchida, se o ficheiro existir
 * @param nomeficheiro nome do ficheiro que contém a lista de funcionários
 */
void carregarFuncionariosFx(ListaFuncionarios *listafuncionarios, char *nomeficheiro) {
    int sucesso = 0;
    FILE *fp = fopen(nomeficheiro, "rb");
    if (fp != NULL) {
        fread(&listafuncionarios->nrFuncionarios, sizeof (int), 1, fp);
        if (listafuncionarios->nrFuncionarios > 0) {
            listafuncionarios->listafuncionarios = (Funcionario*) malloc(listafuncionarios->nrFuncionarios * sizeof (Funcionario));
            if (listafuncionarios->listafuncionarios != NULL) {
                fread(listafuncionarios->listafuncionarios, sizeof (Funcionario), listafuncionarios->nrFuncionarios, fp);
                listafuncionarios->tamanho = listafuncionarios->nrFuncionarios;
                sucesso = 1;
            } else {
                printf("Erro alocação memória para lista funcionários");
            }

        }
        fclose(fp);
    }
    if (!sucesso) {
        fp = fopen(nomeficheiro, "wb");
        listafuncionarios->listafuncionarios = (Funcionario *) malloc(TAMANHO_MAX * sizeof (Funcionario));
        if (listafuncionarios->listafuncionarios != NULL) {
            listafuncionarios->tamanho = TAMANHO_MAX;
            listafuncionarios->nrFuncionarios = 0;
            fclose(fp);
        } else {
            printf("Erro alocação memória para lista funcionários");
             listafuncionarios->tamanho = 0;
            listafuncionarios->nrFuncionarios = 0;
        }
    }
}

/**
 * Escreve o conteúdo da lista de funcionários em ficheiro 
 * @param listafuncionarios apontador para a lista de funcionários que será escrita em ficheiro
 * @param nomeficheiro nome do ficheiro no qual a lista será escrita
 */
void guardarFuncionariosFx(ListaFuncionarios *listafuncionarios, char *nomeficheiro) {
    FILE *fp = fopen(nomeficheiro, "w");
    if (fp != NULL) {
        fwrite(&listafuncionarios->nrFuncionarios, sizeof (int), 1, fp);
        fwrite(listafuncionarios->listafuncionarios, sizeof (Funcionario), listafuncionarios->nrFuncionarios, fp);
        fclose(fp);
    } else {
        puts(MSG_ERRO_FILE);
    }
}

