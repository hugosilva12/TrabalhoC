/**
 * @file TabelaSegurancaSocial.c
 * @author Hugo Silva
 * @date  23 Novembro 2020
 * @brief Ficheiro c que implementa as funções da bibloteca TabelaSegurancaSocial.h
 * 
 *  Ficheiro c onde são implementadas as funções de importação, edição e escrita da tabela em ficheiro 
 */
#include <stdio.h>
#include <stdlib.h>
#include "TabelaSegurancaSocial.h"
#define MSG_ERRO_READ_FILE "Impossivel abrir o ficheiro!"
#include "Utils.h"

/**
 * Liberta a memória alocada para a tabela
 * @param tabela apontador para a tabela da Segurança Social
 */
void libertarMemoriaTabelaSS(TabelaSegurancaSocial *tabela) {
    free(tabela->taxas);
}
/**
 * Lê dados de um ficheiro,caso exista, e preenche a tabela de Segurança Social
 * @param lista apontador para a estrutura que irá armazenar a tabela de Seguraça Social, caso a leitura de ficheiro seja realizada
 * @param filename nome do ficheiro que contêm a tabela de Segurança Social
 */
void lerFicheiroSegurancaSocial(TabelaSegurancaSocial *lista, char*filename) {
    int i = 0, w = 0, sucesso = 0;
    lista->numeroLinhas = numeroLinhas(filename);
    TaxasSegurancaSocial crite;
    FILE *file;
    file = fopen(filename, "r");
    if (lista->numeroLinhas > 0) {
        lista->taxas = (TaxasSegurancaSocial*) malloc(sizeof (TaxasSegurancaSocial) * lista->numeroLinhas);
        if(lista->taxas != NULL){
        fscanf(file, "%s %s %s %s %s",lista->idTaxa ,lista->descricaoTaxa, lista->descricaoEntidadeEmpregadora, lista->descricaoTrabalhador, lista->descricaoGlobal);
        while (i < lista->numeroLinhas) {
            fscanf(file, "%d,%s %f,%f,%f", &crite.idTaxa, &crite.descTaxa, &crite.EntidadeEmpregadadora, &crite.Trabalhador, &crite.Global);
            lista->taxas[i] = crite;
            i++;
        }
        sucesso = 1;
        lista->tamanho = lista->numeroLinhas;
        }else{
            printf("Memória Dinámica alocação falhou SS\n");
        }
        fclose(file);
        //Remove _ da discrição 
        for (int j = 0; j < lista->numeroLinhas; j++) {
            w = 0;
            while (lista->taxas[j].descTaxa[w] != '\0') {
                if (lista->taxas[j].descTaxa[w] == '_') {
                    lista->taxas[j].descTaxa[w] = ' ';
                }
                w++;
            }
        }
    }
    if (!sucesso) {
        lista->taxas = NULL;
        lista->tamanho = 0;
        lista->numeroLinhas = 0;
        fclose(file);
    }
}
/**
 *  Remove uma taxa da tabela 
 * @param tabelaIrs apontador para a tabela da Segurança Social
 */
void removerLinha(TabelaSegurancaSocial *lista) {
    int linhaRemover;
    do {
        printf("Insira a linha da tabela que pretende remover [2-%d]\n ", lista->numeroLinhas);
        scanf("%d", &linhaRemover);
        if (linhaRemover < 0 || linhaRemover > lista->numeroLinhas) {
            puts("Não existe essa linha na tabela!");
        }
    } while (linhaRemover < 0 || linhaRemover > lista->numeroLinhas);

    if (linhaRemover == 0) {
        puts("Linha Impossível de remover!"); //Garantia de que existe sempre uma linha para processamento de salário
    } else {
        for (int i = linhaRemover; i < lista->numeroLinhas; i++) {
            lista->taxas[i] = lista->taxas[i + 1];
        }
        lista->numeroLinhas--;
        puts("Linha removida com sucesso!");
    }

}
/**
 * Expande a memória alocada para a tabela, duplicando o seu tamanho atual
 * @param lista apontador para a tabela de Segurança Social
 */
void expandirMemoriaTabelaSS(TabelaSegurancaSocial *lista) {
    TaxasSegurancaSocial *tmp = (TaxasSegurancaSocial*) realloc(lista->taxas, sizeof (TaxasSegurancaSocial)* (lista->tamanho * 2));
    lista->tamanho *= 2;
    lista->taxas = tmp;
}

/**
 *  Imprime a tabela de Segurança Social
 * @param lista estrutura que contém a tabela
 */
void imprimirTabela(TabelaSegurancaSocial lista) {
    int i;
    puts("----------------------Tabela Segurança Social------------------------");
    for (i = 0; i < lista.numeroLinhas; i++) {
        printf("NrCritério:%d||DESCRIÇÃO: %s||E.EMPREGADORA %.2f||FUNCIONARIO %.2f||GLOBAL %.2f \n",lista.taxas[i].idTaxa ,lista.taxas[i].descTaxa, lista.taxas[i].EntidadeEmpregadadora,
                lista.taxas[i].Trabalhador, lista.taxas[i].Global);
    }
    puts("----------------------------------------------------------------------");
}

/**
 * Adiciona uma nova taxa à tabela de Segurança Social
 * @param lista apontador para a tabela  onde irá ser adicionada a nova taxa 
 */
void adicionarNovaTaxa(TabelaSegurancaSocial *lista) {
    TaxasSegurancaSocial criterio;
    int w = 0;
    if (lista->numeroLinhas == lista->tamanho) {
        expandirMemoriaTabelaSS(lista);
    }
    cleanInputBuffer();
    puts("Escreva a descrição do criterio");
    fgets(criterio.descTaxa, MAX_DESCRICAO_TABELA, stdin);
    puts("Escreva a percentagem da Entidade Empregadora");
    scanf("%f", &criterio.EntidadeEmpregadadora);
    puts("Insira nova percentagem do Funcionario");
    scanf("%f", &criterio.Trabalhador);
    criterio.idTaxa=  lista->numeroLinhas + 1;
    criterio.Global = criterio.EntidadeEmpregadadora + criterio.Trabalhador;
    //Retirar os espaços da descriçao
    while (criterio.descTaxa[w] != '\0'   ) {
        if(criterio.descTaxa[w] == '\n'){
            criterio.descTaxa[w] = '\0';
        }
        w++;
    }
    lista->taxas[lista->numeroLinhas] = criterio;
    lista->numeroLinhas++;
}
/**
 * Escreve a tabela num ficheiro, caso seja possível
 * @param tabela tabela que será escrita
 * @param filename nome do ficheiro na qual a tabela será escrita
 */
void escreverTabelaFicheiro(TabelaSegurancaSocial tabela, char *filename) {
    //Adiciona _ em vez de espacao discrição 
    int w = 0;
    for (int j = 0; j < tabela.numeroLinhas; j++) {
        w = 0;
        while (tabela.taxas[j].descTaxa[w] != '\0') {
            if (tabela.taxas[j].descTaxa[w] == ' ') {
                tabela.taxas[j].descTaxa[w] = '_';
            }
            w++;
        }
    }
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "%s %s %s %s %s \n",tabela.idTaxa,tabela.descricaoTaxa, tabela.descricaoEntidadeEmpregadora, tabela.descricaoTrabalhador, tabela.descricaoGlobal);
        for (int i = 0; i < tabela.numeroLinhas; i++) {
            fprintf(file, "%d,%s %.2f,%.2f,%.2f \n", tabela.taxas[i].idTaxa, tabela.taxas[i].descTaxa, tabela.taxas[i].EntidadeEmpregadadora, tabela.taxas[i].Trabalhador, tabela.taxas[i].Global);
        }
    } else {
        puts(MSG_ERRO_READ_FILE);
    }
    fclose(file);
}
/**
 * Edita uma taxa da Segurança Social
 * @param tabela apontador para tabela 
 */
void editarTaxa(TabelaSegurancaSocial *tabela) {
    int auxx, opcao;
    do {
        printf("Insira a linha da tabela que pretende editar [0-%d]\n ", tabela->numeroLinhas);
        scanf("%d", &auxx);
        if (auxx < 0 || auxx > tabela->numeroLinhas) {
            puts("Não existe essa linha na tabela!");
        }
    } while (auxx < 0 || auxx > tabela->numeroLinhas);

    puts("Escolha o que pretende editar");

    do {
        puts("Editar Tabela Segurança Social");
        puts("----------------------------");
        puts("1. Percentagem Entidade Empregadora");
        puts("2. Percentagem Trabalhador");
        puts("0. Concluir");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                tabela->taxas[auxx].EntidadeEmpregadadora = obterPercentagem();
                tabela->taxas[auxx].Global = tabela->taxas[auxx].EntidadeEmpregadadora + tabela->taxas[auxx].Trabalhador;
                if(tabela->taxas[auxx].Global > 100){
                    tabela->taxas[auxx].Global = 100;
                }
                break;
            case 2:
                tabela->taxas[auxx].Trabalhador = obterPercentagem();
                tabela->taxas[auxx].Global = tabela->taxas[auxx].EntidadeEmpregadadora + tabela->taxas[auxx].Trabalhador;
                 if(tabela->taxas[auxx].Global > 100){
                    tabela->taxas[auxx].Global = 100;
                }
                break;
        }
    } while (opcao != 0);
}