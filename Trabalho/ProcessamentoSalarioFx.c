/**
 * @file ProcessamentoSalarioFx.c
 * @author Hugo Silva
 * @date  25 Novembro 2020
 * @brief Ficheiro c que implementa as funções da bibloteca ProcessamentoSalarioFx
 * 
 * Neste ficheiro é implementada a funções que importa dados para processamento de salário. É também implementada a função que gera um relatório sobre os vencimentos processados
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProcessamentoSalarioFX.h"
#include "Utils.h"
#define TAMANHOCOLUNASIMPORTACAO 100

/**
 * Liberta a memória alocada da lista de dados para processamento
 * @param lista apontador para a lista de processamentos
 */
void libertarMemoriaDadosProcessamento(ListaProcessamentos *lista) {
    free(lista->listaProcessamentos);
    lista->numeroSalariosaProcessar = 0;
}

/**
 * Liberta a memória alocada da lista de vencimentos processados
 * @param lista apontador para a lista de vencimentos processados
 */
void libertarListaVencimentosProcessados(ListaVencimentosProcessadosMes *vencimentos) {
    free(vencimentos->lista);
}

/**
 * Função que importa o ficheiro com dados a processar e aloca  memória para a lista de vencimentos processados
 * @param listaDadosProcessamento lista de dados para processamento, que irá armazenar a informação lida do ficheiro
 * @param filename nome do ficheiro de importação dos dados
 * @param filerelatorio nome do relatório que irá ser gerado
 * @param listaVencimentos lista de vencimentos processados
 */
void carregarFicheiroProcessamento(ListaProcessamentos *listaDadosProcessamento, char*filename, char*filerelatorio, ListaVencimentosProcessadosMes *listaVencimentos) {
    importarFicheiroProcessamento(listaDadosProcessamento, filename); //Importa ficheiro já sabe que existe
    if (listaDadosProcessamento->numeroSalariosaProcessar != 0) {
        listaVencimentos->nrProcessamentos = listaDadosProcessamento->numeroSalariosaProcessar;
        listaVencimentos->salariosProcessados = 0;
        listaVencimentos->salariosNaoProcessados = 0;
        listaVencimentos->lista = (VencimentoProcessado*) malloc(sizeof (VencimentoProcessado) * listaVencimentos->nrProcessamentos);
        if( listaVencimentos->lista == NULL){
            puts("Memória lista vencimentos não alocada");
              listaVencimentos->nrProcessamentos = 0;
              listaVencimentos->lista = NULL;
        }
        strcpy(listaVencimentos->nomeRelatorio, filerelatorio);
    } else {
        listaVencimentos->nrProcessamentos = 0;
        listaVencimentos->lista = NULL;
    }

}

/**
 * Função que importa ficheiro com dados para processamento, caso exista
 * @param lista apontador para a lista de processamentos que irá armazenar os dados lidos do ficheiro, no caso de ser possível
 * @param filename nome do ficheiro que se pretende importar
 */
void importarFicheiroProcessamento(ListaProcessamentos *lista, char *filename) {
    int i = 0,  w = 0,x = 0;;
    char NomesColunas[TAMANHOCOLUNASIMPORTACAO];
    lista->numeroSalariosaProcessar = numeroLinhas(filename);
    FILE *file;
    file = fopen(filename, "r");
    if (lista->numeroSalariosaProcessar > 0) {
        lista->listaProcessamentos = (DadosProcessamentoSalario*) malloc(sizeof (DadosProcessamentoSalario) * lista->numeroSalariosaProcessar);
        if (lista->listaProcessamentos != NULL) {
           fgets(NomesColunas,TAMANHOCOLUNASIMPORTACAO, file); // Primeira linha do ficheiro desnecessária   
            while (i < lista->numeroSalariosaProcessar) {
                fscanf(file, "%d,%d,%d,%d,%d", &lista->listaProcessamentos[i].codigoFuncionario, &lista->listaProcessamentos[i].nrDiasSemana, &lista->listaProcessamentos[i].nrDiasFimdeSemana,
                        &lista->listaProcessamentos[i].nrMeiosDias, &lista->listaProcessamentos[i].nrFaltas);
                i++;
            }
           
        } else {
            puts("Erro ao alocar memória");
            lista->numeroSalariosaProcessar = 0;
        lista->listaProcessamentos = NULL;
        }
    } else {
        puts("Ficheiro de Importaçao Nulo!");
        lista->numeroSalariosaProcessar = 0;
        lista->listaProcessamentos = NULL;
    }
    fclose(file);
}

/**
 * Escreve a lista de vencimentos processados num mês em ficheiro, caso seja possível
 * @param lista lista de vencimentos processados
 */
void gerarRelatorio(ListaVencimentosProcessadosMes lista) {
    int i = 0;
    FILE *file;
    file = fopen(lista.nomeRelatorio, "w");
    if (file != NULL) {
        fprintf(file, "NrProcessamentos: %d \n", lista.nrProcessamentos);
        fprintf(file, "NrProcessamentos_Bem_sucedidos: %d \n", lista.salariosProcessados);
        fprintf(file, "Nrprocessamentos_Mal_Sucedidos: %d \n", lista.salariosNaoProcessados);
        while (i < lista.salariosProcessados) {
            fprintf(file, "CodFuncionario: %d,SalárioBruto: %.2f,SalárioLiquído: %.2f,RetençãoIrs: %.2f,Bónus: %.2f,SubsidioAlimentação: %.2f,EncargosTotaisEmpresa: %.2f,SegurancaSocial: %.2f,SegurancaSocialEmpresa: %.2f\n", lista.lista[i].codigoFuncionario,
                    lista.lista[i].salarioBruto, lista.lista[i].salarioLiquido, lista.lista[i].retencaoIrs, lista.lista[i].bonus, lista.lista[i].subsidioAlimentacao, lista.lista[i].encargosTotaisEmpresa,
                    lista.lista[i].impostoSegurancaSocialEmpresa, lista.lista[i].segurancaSocial);
            i++;
        }
    } else {
        puts("Erro");
    }
    fclose(file);
}

/**
 * Escreve todos os relatórios de vencimentos processados em ficheiro
 * @param relatorios lista de todos os relatórios processados
 */
void guardarRelatoriosProcessados(ListaTodosVencimentosProcessados relatorios) {
    if (relatorios.janeiro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.janeiro);
    }
    if (relatorios.fevereiro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.fevereiro);
    }
    if (relatorios.marco.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.marco);
    }
    if (relatorios.abril.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.abril);
    }
    if (relatorios.maio.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.maio);
    }
    if (relatorios.junho.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.junho);
    }
    if (relatorios.julho.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.julho);
    }
    if (relatorios.agosto.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.agosto);
    }
    if (relatorios.setembro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.setembro);
    }
    if (relatorios.outubro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.outubro);
    }
    if (relatorios.novembro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.novembro);
    }
    if (relatorios.dezembro.nrProcessamentos != 0) {
        gerarRelatorio(relatorios.dezembro);
    }
}
/**
 * Liberta memória alocada para os vencimentos processados, caso exista
 * @param relatorios
 */
void libertarMemoriaRelatoriosProcessados(ListaTodosVencimentosProcessados *relatorios) {
    if (relatorios->janeiro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->janeiro);
    }
    if (relatorios->fevereiro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->fevereiro);
    }
    if (relatorios->marco.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->marco);
    }
    if (relatorios->abril.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->abril);
    }
    if (relatorios->maio.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->maio);
    }
    if (relatorios->junho.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->junho);
    }
    if (relatorios->julho.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->julho);
    }
    if (relatorios->agosto.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->agosto);
    }
    if (relatorios->setembro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->setembro);
    }
    if (relatorios->outubro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->outubro);
    }
    if (relatorios->novembro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->novembro);
    }
    if (relatorios->dezembro.nrProcessamentos != 0) {
        libertarListaVencimentosProcessados(&relatorios->dezembro);
    }
}

/**
 * Importa um relatório de vencimentos processados, caso exista
 * @param lista apontador para a lista de vencimentos processados, que irá armazenar os valores lidos do ficheiro
 */
void obterRelatorio(ListaVencimentosProcessadosMes *lista) {
    int i = 0;
    FILE *file;
    file = fopen(lista->nomeRelatorio, "r");
    char nome[100];
    if (file != NULL) {
        fscanf(file, "%s %d ", nome, &lista->nrProcessamentos);
        fscanf(file, "%s %d", nome, &lista->salariosProcessados);
        if (lista->nrProcessamentos > 0) {
            lista->lista = (VencimentoProcessado*) malloc(sizeof (VencimentoProcessado) * lista->nrProcessamentos);
        }
        fscanf(file, "%s %d", nome, &lista->salariosNaoProcessados);
        while (i < lista->salariosProcessados) {
            fscanf(file, "%s %d,%s %f,%s %f,%s %f,%s %f,%s %f,%s %f,%s %f,%s %f", nome, &lista->lista[i].codigoFuncionario, nome,
                    &lista->lista[i].salarioBruto, nome, &lista->lista[i].salarioLiquido, nome, &lista->lista[i].retencaoIrs, nome, &lista->lista[i].bonus, nome, &lista->lista[i].subsidioAlimentacao, nome, &lista->lista[i].encargosTotaisEmpresa, nome,
                    &lista->lista[i].segurancaSocial, nome, &lista->lista[i].impostoSegurancaSocialEmpresa);
            i++;
        }
    } else {
        lista->salariosProcessados = 0;
        lista->lista = NULL;
        lista->nrProcessamentos = 0;

    }
    fclose(file);
}

void obterTodosRelatoriosProcessados(ListaTodosVencimentosProcessados *relatorios) {
    int aux = 0;
    relatorios->nrMesesProcessados = 0;
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            strcpy(relatorios->janeiro.nomeRelatorio, NOME_RELATORIO_JAN);
            obterRelatorio(&relatorios->janeiro);
            if (relatorios->janeiro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 1) {
            strcpy(relatorios->fevereiro.nomeRelatorio, NOME_RELATORIO_FEV);
            obterRelatorio(&relatorios->fevereiro);
            if (relatorios->fevereiro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 2) {
            strcpy(relatorios->marco.nomeRelatorio, NOME_RELATORIO_MAR);
            obterRelatorio(&relatorios->marco);
            if (relatorios->marco.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 3) {
            strcpy(relatorios->abril.nomeRelatorio, NOME_RELATORIO_ABR);
            obterRelatorio(&relatorios->abril);
            if (relatorios->abril.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 4) {
            strcpy(relatorios->maio.nomeRelatorio, NOME_RELATORIO_MAI);
            obterRelatorio(&relatorios->maio);
            if (relatorios->maio.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 5) {
            strcpy(relatorios->junho.nomeRelatorio, NOME_RELATORIO_JUN);
            obterRelatorio(&relatorios->junho);
            if (relatorios->junho.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 6) {
            strcpy(relatorios->julho.nomeRelatorio, NOME_RELATORIO_JUL);
            obterRelatorio(&relatorios->julho);
            if (relatorios->julho.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 7) {
            strcpy(relatorios->agosto.nomeRelatorio, NOME_RELATORIO_AGO);
            obterRelatorio(&relatorios->agosto);
            if (relatorios->agosto.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 8) {
            strcpy(relatorios->setembro.nomeRelatorio, NOME_RELATORIO_SET);
            obterRelatorio(&relatorios->setembro);
            if (relatorios->setembro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 9) {
            strcpy(relatorios->outubro.nomeRelatorio, NOME_RELATORIO_OUT);
            obterRelatorio(&relatorios->outubro);
            if (relatorios->outubro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 10) {
            strcpy(relatorios->novembro.nomeRelatorio, NOME_RELATORIO_NOV);
            obterRelatorio(&relatorios->novembro);
            if (relatorios->novembro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        } else if (i == 11) {
            strcpy(relatorios->dezembro.nomeRelatorio, NOME_RELATORIO_DEZ);
            obterRelatorio(&relatorios->dezembro);
            if (relatorios->dezembro.nrProcessamentos != 0) {
                relatorios->nrMesesProcessados++;
            }
        }

    }
}
