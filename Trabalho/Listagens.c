/**
 * @file Listagens.c
 * @author Hugo Silva
 * @date  3 Janeiro 2020
 * @brief Implementação das funções da biblioteca Listagens.h
 * 
 * Implementação das funções que realizam as 6 listagens propostas pelo grupo
 */
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "ProcessamentoSalario.h"
#include "Listagens.h"
#include "ProcessamentoSalarioFX.h"
#include <string.h>

/**
 *  Liberta a memória do relatório de faltas, caso tenha sido alocada
 * @param gestaofaltas apontador para uma estrutura que guarda o relatório sobre faltas
 */
void libertarMemoriaGestaoFaltas(RelatorioFaltas *gestaofaltas) {
    for (int i = 0; i < 12; i++) {
        if(gestaofaltas->lista[i].Semfaltas != NULL){
          free(gestaofaltas->lista[i].Semfaltas);   
        }
        if(gestaofaltas->lista[i].Umafaltas != NULL){
          free(gestaofaltas->lista[i].Umafaltas);   
        }
        if(gestaofaltas->lista[i].DuasouTresFaltas != NULL){
          free(gestaofaltas->lista[i].DuasouTresFaltas);   
        }
        if(gestaofaltas->lista[i].MaisTresFaltas != NULL){
          free(gestaofaltas->lista[i].MaisTresFaltas);   
        }
    }
}

/**
 * Função que realoca memória 
 * @param gestao apontador no qual será feita a realocação de memória
 * @param tamanho  tamanho da lista que será duplicada
 */
void expandirMemoriaFaltas(int *gestao, int *tamanho) {
    int *tmp = (int*) realloc(gestao, sizeof (int)*(*tamanho * 2));
    *gestao = *tmp;
    *tamanho *= 2;
}

/**
 * Obtêm a percentagens de funcionários por intervalos de idade
 * @param lista lista dos funcionários
 * @param relatorio apontador para a estrutura que guarda os resultados obtidos
 */
void percentagemIdadesFuncionarios(ListaFuncionarios lista, PercentagemIdades *relatorio) {
    int maissessenta = 0, entre51e60 = 0, entre41e50 = 0, entre31e40 = 0, entre26e30 = 0, menos26 = 0;
    int idade;
    for (int i = 0; i < lista.nrFuncionarios; i++) {
        idade = calcularIdade(lista.listafuncionarios[i].dataNascimento);
        printf("%d\n\n", idade);
        if (idade > 60) { //Trabalhador com + de 60 anos
            maissessenta++;
        } else if (idade <= 60 && idade > 50) {//Trabalhador entre 51 e 60 anos
            entre51e60++;
        } else if (idade <= 50 && idade > 41) { //Trabalhador entre 41 e 50 anos
            entre41e50++;
        } else if (idade <= 40 && idade > 30) { //Trabalhador entre 31 e 40 anos
            entre31e40++;
        } else if (idade <= 30 && idade > 25) { // Trabalhador entre 26 e 30 anos
            entre26e30++;
        } else if (idade < 26) {
            menos26++;
        }
    }
    relatorio->funcionariosAnalisados = lista.nrFuncionarios;
    relatorio->percentagemMais60 = (float) maissessenta / lista.nrFuncionarios;
    relatorio->percentagemMais60 *= 100;
    relatorio->percentagemEntre51e60 = (float) entre51e60 / lista.nrFuncionarios;
    relatorio->percentagemEntre51e60 *= 100;
    relatorio->percentagemEntre41e50 = (float) entre41e50 / lista.nrFuncionarios;
    relatorio->percentagemEntre41e50 *= 100;
    relatorio->percentagemEntre31e40 = (float) entre31e40 / lista.nrFuncionarios;
    relatorio->percentagemEntre31e40 *= 100;
    relatorio->percentagemEntre26e30 = (float) entre26e30 / lista.nrFuncionarios;
    relatorio->percentagemEntre26e30 *= 100;
    relatorio->percentagemMenos26 = (float) menos26 / lista.nrFuncionarios;
    relatorio->percentagemMenos26 *= 100;
    relatorio->funcionariosComBonus = entre26e30 + entre31e40 + entre41e50 + entre51e60 + maissessenta;
    relatorio->funcionariosSemBonus = menos26;
}

/**
 * Obtêm a percentagem de funcionários por intervalos de anos na empresa
 * @param lista lista dos funcionários
 * @param relatorio apontador para a estrutura que guarda os resultados obtidos
 */
void percentagemTempoEmpresa(ListaFuncionarios lista, PercentagemTempoEmpresa *relatorio) {
    int mais20 = 0, menos5 = 0, entre5e10 = 0, entre11e20 = 0;
    int AnosEmpresa;
    for (int i = 0; i < lista.nrFuncionarios; i++) {
        AnosEmpresa = calcularIdade(lista.listafuncionarios[i].dataEntradaEmpresa);
        if (AnosEmpresa > 4 && AnosEmpresa <= 10) { //Entre 5 e 10 anos
            entre5e10++;
        } else if (AnosEmpresa > 10 && AnosEmpresa <= 20) {// Entre 11 e 20 anos
            entre11e20++;
        } else if (AnosEmpresa > 20) { //Mais 20 anos;
            mais20++;
        } else if (AnosEmpresa < 5) {
            menos5++;
        }
    }
    relatorio->funcionariosAnalisados = lista.nrFuncionarios;
    relatorio->funcionariosComBonus = mais20 + entre5e10 + entre11e20;
    relatorio->funcionariosSemBonus = menos5;
    relatorio->percentagemMenos5 = (float) menos5 / lista.nrFuncionarios;
    relatorio->percentagemMenos5 *= 100;
    relatorio->percentagemMais20 = (float) mais20 / lista.nrFuncionarios;
    relatorio->percentagemMais20 *= 100;
    relatorio->percentagemEntre5e10 = (float) entre5e10 / lista.nrFuncionarios;
    relatorio->percentagemEntre5e10 *= 100;
    relatorio->percentagemEntre11e20 = (float) entre11e20 / lista.nrFuncionarios;
    relatorio->percentagemEntre11e20 *= 100;

}

/**
 * Calcula as despesas totais que a empresa teve num mês
 * @param lista vencimentos que foram processados nesse mês
 * @param valorTotal  apontador para o valor no qual a despesa total será guardada
 * @param salariosProcessados apontador que armazena o número de salários processados num mês
 */
void despesaTotalEmpresaPorMes(ListaVencimentosProcessadosMes lista, float *valorTotal, int *salariosProcessados) {
    int i = 0;
    *salariosProcessados = lista.salariosProcessados;
    for (i = 0; i < lista.nrProcessamentos; i++) {
        *valorTotal = *valorTotal + lista.lista[i].encargosTotaisEmpresa;
    }
}

/**
 * Calcula as despesas totais que a empresa teve anualmente mediante os relatórios processados
 * @param despesas apontador para a estrutura que irá armazenar as depesas de todos os meses
 */
void DespesasTotais(DespesasAnuais *despesas) {
    ListaVencimentosProcessadosMes lista;
    despesas->despesaTotal = 0;
    for (int i = 0; i < 12; i++) {
        lista.lista = NULL;
        if (i == 0) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_JAN);
        } else if (i == 1) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_FEV);
        } else if (i == 2) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_MAR);
        } else if (i == 3) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_ABR);
        } else if (i == 4) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_MAI);
        } else if (i == 5) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_JUN);
        } else if (i == 6) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_JUL);
        } else if (i == 7) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_AGO);
        } else if (i == 8) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_SET);
        } else if (i == 9) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_OUT);
        } else if (i == 10) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_NOV);
        } else if (i == 11) {
            strcpy(lista.nomeRelatorio, NOME_RELATORIO_DEZ);
        }
        obterRelatorio(&lista);
        if (lista.salariosProcessados == 0) {
            despesas->meses[i].despesaTotal = 0;
            despesas->meses[i].salariosProcessados = 0;
        } else {
            despesaTotalEmpresaPorMes(lista, &despesas->meses[i].despesaTotal, &despesas->meses[i].salariosProcessados);
            despesas->despesaTotal += despesas->meses[i].despesaTotal;
        }
        if (lista.lista != NULL) {
            libertarListaVencimentosProcessados(&lista);
        }
    }
    despesas->estadoRelatorio = 1;
}

/**
 * Obtêm uma listagem dos funcionários pelo seu número de faltas num mês
 * @param gestaofaltas apontador para estrutura que irá armazenar a listagem
 */
void listagemFuncionariosPorFaltas(RelatorioFaltas *gestaofaltas) {
    ListaProcessamentos lista;
    lista.listaProcessamentos = NULL;
    char FicheiroImport[20];
    gestaofaltas->estadoRelatorio = 1;
    for (int i = 0; i < 12; i++) {
        switch (i) {
            case 0:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JAN);
                break;
            case 1:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_FEV);
                break;
            case 2:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_MAR);
                break;
            case 3:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_ABR);
                break;
            case 4:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_MAI);
                break;
            case 5:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JUN);
                break;
            case 6:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JUL);
                break;
            case 7:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_AGO);
                break;
            case 8:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_SET);
                break;
            case 9:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_OUT);
                break;
            case 10:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_NOV);
                break;
            case 11:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_DEZ);
                break;
        }
        gestaofaltas->lista[i].nrUmafaltas = 0;
        gestaofaltas->lista[i].nrMaisTresFaltas = 0;
        gestaofaltas->lista[i].nrSemfaltas = 0;
        gestaofaltas->lista[i].nrDuasouTresFaltas = 0;

        //Verifica se ficheiro existe
        if (verificaExistenciaFicheiro(FicheiroImport) == 1) {
            importarFicheiroProcessamento(&lista, FicheiroImport);
            gestaofaltas->lista[i].tamanhoSemfaltas = TAMANHOCODIGOS;
            gestaofaltas->lista[i].tamanhoUmafaltas = TAMANHOCODIGOS;
            gestaofaltas->lista[i].tamanhoDuasouTresFaltas = TAMANHOCODIGOS;
            gestaofaltas->lista[i].tamanhoMaisTresFaltas = TAMANHOCODIGOS;
            gestaofaltas->lista[i].Umafaltas = (int*) malloc(sizeof (int) * TAMANHOCODIGOS);
            gestaofaltas->lista[i].Semfaltas = (int*) malloc(sizeof (int) * TAMANHOCODIGOS);
            gestaofaltas->lista[i].DuasouTresFaltas = (int*) malloc(sizeof (int) * TAMANHOCODIGOS);
            gestaofaltas->lista[i].MaisTresFaltas = (int*) malloc(sizeof (int) * TAMANHOCODIGOS);
            gestaofaltas->lista[i].nrFuncionariosAnalisados = lista.numeroSalariosaProcessar;
            for (int j = 0; j < lista.numeroSalariosaProcessar; j++) {
                if (lista.listaProcessamentos[j].nrFaltas == 0) {
                    if (gestaofaltas->lista[i].nrSemfaltas == gestaofaltas->lista[i].tamanhoSemfaltas) {
                        expandirMemoriaFaltas(gestaofaltas->lista[i].Semfaltas, &gestaofaltas->lista[i].tamanhoSemfaltas);
                    }
                    gestaofaltas->lista[i].Semfaltas[gestaofaltas->lista[i].nrSemfaltas] = lista.listaProcessamentos[j].codigoFuncionario;
                    gestaofaltas->lista[i].nrSemfaltas++;
                } else if (lista.listaProcessamentos[j].nrFaltas == 1) {
                    if (gestaofaltas->lista[i].nrUmafaltas == gestaofaltas->lista[i].tamanhoUmafaltas) {
                        expandirMemoriaFaltas(gestaofaltas->lista[i].Umafaltas, &gestaofaltas->lista[i].tamanhoUmafaltas);
                    }
                    gestaofaltas->lista[i].Umafaltas[gestaofaltas->lista[i].nrUmafaltas] = lista.listaProcessamentos[j].codigoFuncionario;
                    gestaofaltas->lista[i].nrUmafaltas++;
                } else if (lista.listaProcessamentos[j].nrFaltas == 2 || lista.listaProcessamentos[j].nrFaltas == 3) {
                    if (gestaofaltas->lista[i].nrDuasouTresFaltas == gestaofaltas->lista[i].tamanhoDuasouTresFaltas) {
                        expandirMemoriaFaltas(gestaofaltas->lista[i].DuasouTresFaltas, &gestaofaltas->lista[i].tamanhoDuasouTresFaltas);
                    }
                    gestaofaltas->lista[i].DuasouTresFaltas[gestaofaltas->lista[i].nrDuasouTresFaltas] = lista.listaProcessamentos[j].codigoFuncionario;
                    gestaofaltas->lista[i].nrDuasouTresFaltas++;
                } else if (lista.listaProcessamentos[j].nrFaltas > 3) {
                    if (gestaofaltas->lista[i].nrMaisTresFaltas == gestaofaltas->lista[i].tamanhoMaisTresFaltas) {
                        expandirMemoriaFaltas(gestaofaltas->lista[i].MaisTresFaltas, &gestaofaltas->lista[i].tamanhoMaisTresFaltas);
                    }
                    gestaofaltas->lista[i].MaisTresFaltas[gestaofaltas->lista[i].nrMaisTresFaltas] = lista.listaProcessamentos[j].codigoFuncionario;
                    gestaofaltas->lista[i].nrMaisTresFaltas++;
                }
            }
            libertarMemoriaDadosProcessamento(&lista); //Liberta a memória alocada 
        } else {
            gestaofaltas->lista[i].Umafaltas = NULL;
            gestaofaltas->lista[i].Semfaltas = NULL;
            gestaofaltas->lista[i].MaisTresFaltas = NULL;
            gestaofaltas->lista[i].DuasouTresFaltas = NULL;
            gestaofaltas->lista[i].nrFuncionariosAnalisados = 0;
            gestaofaltas->lista[i].tamanhoSemfaltas = 0;
            gestaofaltas->lista[i].tamanhoUmafaltas = 0;
            gestaofaltas->lista[i].tamanhoDuasouTresFaltas = 0;
            gestaofaltas->lista[i].tamanhoMaisTresFaltas = 0;
        }
    }
}

/**
 *  Obtêm o valor mínimo, máximo e médio pago por hora
 * @param lista lista dos funcionários
 * @param relatorio apontador para a estrutura que armazena os resultados obtido
 */
void relatorioValorHora(ListaFuncionarios lista, RelatorioValorHora *relatorio) {
    relatorio->estadoRelatorio = 1;
    relatorio->valorMedio = 0;
    relatorio->valorMinimoHora = lista.listafuncionarios[0].valorHora;
    relatorio->valorMaximoHora = lista.listafuncionarios[0].valorHora;

    for (int i = 0; i < lista.nrFuncionarios; i++) {
        if (relatorio->valorMinimoHora > lista.listafuncionarios[i].valorHora) {
            relatorio->valorMinimoHora = lista.listafuncionarios[i].valorHora;
        }
        if (relatorio->valorMaximoHora < lista.listafuncionarios[i].valorHora) {
            relatorio->valorMaximoHora = lista.listafuncionarios[i].valorHora;
        }
        relatorio->valorMedio += lista.listafuncionarios[i].valorHora;
    }
    relatorio->valorMedio = relatorio->valorMedio / lista.nrFuncionarios;

}

/**
 * Obtêm a percentagem de funcionários por estado civil
 * @param lista lista dos funcionários
 * @param relatorio apontador para a estrutura que guarda os resultados obtidos
 */
void relatorioPercentagemEstadoCivil(ListaFuncionarios lista, PercentagemEstadoCivil *relatorio) {
    int aux1 = 0, aux2 = 0, aux3 = 0;
    relatorio->estadoRelatorio = 1;
    for (int i = 0; i < lista.nrFuncionarios; i++) {
        if (lista.listafuncionarios[i].estadoCivil == 1) {
            aux1++;
        } else if (lista.listafuncionarios[i].estadoCivil == 2) {
            aux2++;
        } else if (lista.listafuncionarios[i].estadoCivil == 3) {
            aux3++;
        }
    }
    relatorio->percNaoCasado = (float) aux1 / lista.nrFuncionarios;
    relatorio->percNaoCasado *= 100;
    relatorio->percCasadoUnicoTitular = (float) aux2 / lista.nrFuncionarios;
    relatorio->percCasadoUnicoTitular *= 100;
    relatorio->percCasadoDoisTitulares = (float) aux3 / lista.nrFuncionarios;
    relatorio->percCasadoDoisTitulares *= 100;
}

/**
 * Escreve o relatório de faltas em ficheiro, se possível
 * @param gestaofaltas apontador para os dados do relatório de faltas
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatorioFaltas(RelatorioFaltas *gestaofaltas, char*filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < 12; i++) {
            if (i == 0) {
                fprintf(file, "-------Janeiro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 1) {
                fprintf(file, "-------Fevereiro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 2) {
                fprintf(file, "-------Março-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 3) {
                fprintf(file, "-------Abril-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 4) {
                fprintf(file, "-------Maio-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 5) {
                fprintf(file, "-------Junho-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 6) {
                fprintf(file, "-------Julho-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 7) {
                fprintf(file, "-------Agosto-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 8) {
                fprintf(file, "-------Setembro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 9) {
                fprintf(file, "-------Outubro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 10) {
                fprintf(file, "-------Novembro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            } else if (i == 11) {
                fprintf(file, "-------Dezembro-------------NRF: %d ", gestaofaltas->lista[i].nrFuncionariosAnalisados);
            }
            if (gestaofaltas->lista[i].nrFuncionariosAnalisados == 0) {
                fprintf(file, "Mês Não analisado!\n");
            } else {
                fprintf(file, "\nZEROFaltas: %d\n", gestaofaltas->lista[i].nrSemfaltas);
                for (int j = 0; j < gestaofaltas->lista[i].nrSemfaltas; j++) {
                    fprintf(file, "%d\n", gestaofaltas->lista[i].Semfaltas[j]);
                }
                fprintf(file, "UMFalta: %d\n", gestaofaltas->lista[i].nrUmafaltas);
                for (int j = 0; j < gestaofaltas->lista[i].nrUmafaltas; j++) {
                    fprintf(file, "%d\n", gestaofaltas->lista[i].Umafaltas[j]);
                };
                fprintf(file, "DUAS/TRÊSFaltas: %d\n", gestaofaltas->lista[i].nrDuasouTresFaltas);
                for (int j = 0; j < gestaofaltas->lista[i].nrDuasouTresFaltas; j++) {
                    fprintf(file, "%d\n", gestaofaltas->lista[i].DuasouTresFaltas[j]);
                }
                fprintf(file, "MAISTRÊSFaltas: %d\n", gestaofaltas->lista[i].nrMaisTresFaltas);
                for (int j = 0; j < gestaofaltas->lista[i].nrMaisTresFaltas; j++) {
                    fprintf(file, "%d\n", gestaofaltas->lista[i].MaisTresFaltas[j]);
                }
            }
        }
    }
    fclose(file);
}
/**
 * Importa o relatório de faltas do ficheiro, se possível
 * @param gestaofaltas apontador para os dados do relatório de faltas
 * @param filename nome do ficheiro no qual o relatório será lido
 */
void obterRelatorioFaltas(RelatorioFaltas *gestaofaltas, char*filename) {
    char palavrasEliminar[100];
    int i = 0, w = 0;
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        while (i < 12) {
            fscanf(file, "%s %d", palavrasEliminar, &gestaofaltas->lista[i].nrFuncionariosAnalisados);
            if (gestaofaltas->lista[i].nrFuncionariosAnalisados != 0) {
                fscanf(file, "%s %d", palavrasEliminar, &gestaofaltas->lista[i].nrSemfaltas);
                gestaofaltas->lista[i].Semfaltas = (int*) malloc(sizeof (int) *gestaofaltas->lista[i].nrSemfaltas);
                while (w < gestaofaltas->lista[i].nrSemfaltas) {
                    fscanf(file, "%d", &gestaofaltas->lista[i].Semfaltas[w]);
                    w++;
                }
                w = 0;
                fscanf(file, "%s %d", palavrasEliminar, &gestaofaltas->lista[i].nrUmafaltas);
                gestaofaltas->lista[i].Umafaltas = (int*) malloc(sizeof (int) *gestaofaltas->lista[i].nrUmafaltas);
                while (w < gestaofaltas->lista[i].nrUmafaltas) {
                    fscanf(file, "%d", &gestaofaltas->lista[i].Umafaltas[w]);
                    w++;
                }
                w = 0;
                fscanf(file, "%s %d", palavrasEliminar, &gestaofaltas->lista[i].nrDuasouTresFaltas);
                gestaofaltas->lista[i].DuasouTresFaltas = (int*) malloc(sizeof (int) *gestaofaltas->lista[i].nrDuasouTresFaltas);
                while (w < gestaofaltas->lista[i].nrDuasouTresFaltas) {
                    fscanf(file, "%d", &gestaofaltas->lista[i].DuasouTresFaltas[w]);
                    w++;
                }
                w = 0;
                fscanf(file, "%s %d", palavrasEliminar, &gestaofaltas->lista[i].nrMaisTresFaltas);
                gestaofaltas->lista[i].MaisTresFaltas = (int*) malloc(sizeof (int) *gestaofaltas->lista[i].nrMaisTresFaltas);
                while (w < gestaofaltas->lista[i].nrMaisTresFaltas) {
                    fscanf(file, "%d", &gestaofaltas->lista[i].MaisTresFaltas[w]);
                    w++;
                }

            } else {
                gestaofaltas->lista[i].nrSemfaltas = 0;
                gestaofaltas->lista[i].nrUmafaltas = 0;
                gestaofaltas->lista[i].nrDuasouTresFaltas = 0;
                gestaofaltas->lista[i].nrMaisTresFaltas = 0;
            }
            w = 0;
            i++;
        }
        gestaofaltas->estadoRelatorio = 1;
    }
    fclose(file);
}

/**
 * Escreve o relatório da percentagem de funcionários pelo intervalo de idades em ficheiro, se possível
 * @param percentagens apontador para o relatório
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatoriopercentagemIdadesFuncionarios(PercentagemIdades *percentagens, char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Número_de_Funcionarios_analisados: %d \n", percentagens->funcionariosAnalisados);
        fprintf(file, "Número_de_Funcionarios_com_Direito_a_Bónus_por_idade: %d \n", percentagens->funcionariosComBonus);
        fprintf(file, "Número_de_Funcionarios_sem_Bónus_por_idade: %d \n", percentagens->funcionariosSemBonus);
        fprintf(file, "Mais_de_60anos: %.2f\n", percentagens->percentagemMais60);
        fprintf(file, "Entre_51_e_60anos: %.2f\n", percentagens->percentagemEntre51e60);
        fprintf(file, "Entre_41_e_50anos: %.2f\n", percentagens->percentagemEntre41e50);
        fprintf(file, "Entre_26_e_30anos: %.2f\n", percentagens->percentagemEntre31e40);
        fprintf(file, "Entre_31_e_40anos: %.2f\n", percentagens->percentagemEntre26e30);
        fprintf(file, "Menos_de_26_anos: %.2f\n", percentagens->percentagemMenos26);
    } else {
        puts("Impossivel Gerar relatório da percentagem de Idades!");
    }

    fclose(file);
}
/**
 * Importa de ficheiro relatório da percentagens de funcionários por idade, caso exista
 * @param percentagens apontador para o relatório que irá armazenar as informações do ficheiro
 * @param filename nome do ficheiro do qual o relatório será lido
 */
void obterRelatoriopercentagemIdadesFuncionarios(PercentagemIdades *percentagens, char *filename) {
    char nome[100];
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%s %d", nome, &percentagens->funcionariosAnalisados);
        fscanf(file, "%s %d", nome, &percentagens->funcionariosComBonus);
        fscanf(file, "%s %d", nome, &percentagens->funcionariosSemBonus);
        fscanf(file, "%s %f", nome, &percentagens->percentagemMais60);
        fscanf(file, "%s %f", nome, &percentagens->percentagemEntre51e60);
        fscanf(file, "%s %f", nome, &percentagens->percentagemEntre41e50);
        fscanf(file, "%s %f", nome, &percentagens->percentagemEntre31e40);
        fscanf(file, "%s %f", nome, &percentagens->percentagemEntre26e30);
        fscanf(file, "%s %f", nome, &percentagens->percentagemMenos26);
    } else {
        percentagens->funcionariosAnalisados = 0;
        puts("Impossivel Ler relatório da percentagem de Idades!");
    }

    fclose(file);

}

/** 
 * Escreve o relatório da percentagem de funcionários por anos na empresa em ficheiro, se possível
 * @param relatorio apontador para o relatório
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatorioPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio, char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    char percentagem [2] = "%";
    if (file != NULL) {
        fprintf(file, "Número_de_Funcionarios_analisados: %d \n", relatorio->funcionariosAnalisados);
        fprintf(file, "Número_de_Funcionarios_com_Direito_a_Bónus_por_Tempo_Empresa: %d \n", relatorio->funcionariosComBonus);
        fprintf(file, "Número_de_Funcionarios_sem_Bónus_por_tempo: %d \n", relatorio->funcionariosSemBonus);
        fprintf(file, "Mais_de_20_anos: %.2f %s\n", relatorio->percentagemMais20, percentagem);
        fprintf(file, "Entre_11_e_20_anos: %.2f %s\n", relatorio->percentagemEntre11e20, percentagem);
        fprintf(file, "Entre_5_e_10_anos: %.2f %s\n", relatorio->percentagemEntre5e10, percentagem);
        fprintf(file, "Menos_de_5_anos: %.2f %s\n", relatorio->percentagemMenos5, percentagem);
    } else {
        puts("Impossivel Gerar relatório da percentagem de Idades!");
    }

    fclose(file);
}
/**
 * Importa de um ficheiro o relatório sobre a percentagem de funcionários por anos na empresa, caso exista
 * @param relatorio apontador para o relatório 
 * @param filename nome do ficheiro do qual o relatório será lido
 */
void obterRelatorioPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio, char *filename) {
    char nome[100];
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%s %d", nome, &relatorio->funcionariosAnalisados);
        fscanf(file, "%s %d", nome, &relatorio->funcionariosComBonus);
        fscanf(file, "%s %d", nome, &relatorio->funcionariosSemBonus);
        fscanf(file, "%s %f", nome, &relatorio->percentagemMais20);
        fscanf(file, "%s %f", nome, &relatorio->percentagemEntre11e20);
        fscanf(file, "%s %f", nome, &relatorio->percentagemEntre5e10);
        fscanf(file, "%s %f", nome, &relatorio->percentagemMenos5);
    } else {
        puts("Impossivel Gerar relatório da percentagem de Idades!");
        relatorio->funcionariosAnalisados = 0;
    }

    fclose(file);
}

/**
 * Escreve o relatório sobre o valor hora em ficheiro, se possível
 * @param relatorio apontador para o relatório
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatorioValorHora(RelatorioValorHora *relatorio, char*filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "ValorMaisAlto: %.2f\n", relatorio->valorMaximoHora);
        fprintf(file, "ValorMaisBaixo: %.2f\n", relatorio->valorMinimoHora);
        fprintf(file, "Medio: %.2f\n", relatorio->valorMedio);
        fprintf(file, "DiferençaEntre[max-min]: %.2f\n", relatorio->valorMaximoHora - relatorio->valorMinimoHora);
    } else {
        puts("Erro!");
    }
    fclose(file);
}

/**
 *  Lê relatório sobre valores hora, caso exista
 * @param relatorio apontador para o relatório
 * @param filename nome do ficheiro do qual o relatório será lido
 */
void obterRelatorioValorHora(RelatorioValorHora *relatorio, char*filename) {
    char nome[30];
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%s %f\n", nome, &relatorio->valorMaximoHora);
        fscanf(file, "%s %f\n", nome, &relatorio->valorMinimoHora);
        fscanf(file, "%s %f\n", nome, &relatorio->valorMedio);
        fscanf(file, "%s %f\n", nome, &relatorio->diferenca);
        relatorio->estadoRelatorio = 1;
    } else {
        puts("Erro!");
        relatorio->estadoRelatorio = 0;
    }
    fclose(file);

}

/**
 * Escreve o relatório da percentagem por estado civil em ficheiro, se possível
 * @param relatorio apontador para o relatório
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio, char*filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        fputs("Percentagem_por_Estado_Civil\n", file);
        fprintf(file, "NãoCasados %.2f\n", relatorio->percNaoCasado);
        fprintf(file, "CasadoÚnicoTitular %.2f\n", relatorio->percCasadoUnicoTitular);
        fprintf(file, "CasadoDoisTitulares %.2f\n", relatorio->percCasadoDoisTitulares);
        relatorio->estadoRelatorio = 1;

    } else {
        puts("Erro!");      
    }
    fclose(file);
}

/**
 * Importa o relatório de percentagem por estado civil , caso exista
 * @param relatorio apontador para o relatório
 * @param filename nome do ficheiro do qual o relatório será lido
 */
void obterRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio, char*filename) {
    char nome[100];
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%s", nome);
        fscanf(file, "%s %f", nome, &relatorio->percNaoCasado);
        fscanf(file, "%s %f", nome, &relatorio->percCasadoUnicoTitular);
        fscanf(file, "%s %f", nome, &relatorio->percCasadoDoisTitulares);
        relatorio->estadoRelatorio = 1;
    } else {
        puts("Erro!");
         relatorio->estadoRelatorio = 0;
    }
    fclose(file);
}

/**
 * Escreve o relatório das depesas anuais em ficheiro, se possível
 * @param despesas apontador para a o relatório
 * @param filename nome do ficheiro no qual o relatório será escrito
 */
void gerarRelatorioDespesasTotais(DespesasAnuais *despesas, char*filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < 12; i++) {
            if (i == 0) {
                fputs("-------Janeiro-----------------\n", file);
            } else if (i == 1) {
                fputs("-------Fevereiro-----------------\n", file);
            } else if (i == 2) {
                fputs("-------Março-----------------\n", file);
            } else if (i == 3) {
                fputs("-------Abril-----------------\n", file);
            } else if (i == 4) {
                fputs("-------Maio-----------------\n", file);
            } else if (i == 5) {
                fputs("-------Junho-----------------\n", file);
            } else if (i == 6) {
                fputs("-------Julho-----------------\n", file);
            } else if (i == 7) {
                fputs("-------Agosto---------------------\n", file);
            } else if (i == 8) {
                fputs("-------Setembro--------------------\n", file);
            } else if (i == 9) {
                fputs("-------Outubro--------------------\n", file);
            } else if (i == 10) {
                fputs("-------Novembro-------------------\n", file);
            } else if (i == 11) {
                fputs("-------Dezembro-------------------\n", file);
            }
            fprintf(file, "NrSaláriosProcessados: %d\n", despesas->meses[i].salariosProcessados);
            fprintf(file, "DespesaTotal: %.2f\n", despesas->meses[i].despesaTotal);
        }

        fprintf(file, "-------Total-------------------\nTOTAL: %.2f€", despesas->despesaTotal);
    } else {
        puts("Erro ao Gerar Relatório de Despesas Totais");
    }
    fclose(file);
}
/**
 * Importa o relatório das despesas totais, caso exista
 * @param relatorio apontador para a estrutura do relatório que irá armazenar os dados lidos do ficheiro
 * @param filename nome do ficheiro do qual será importado o relatório
 */
void obterRelatorioDespesasTotais(DespesasAnuais *relatorio, char*filename) {
    char nome[100]; //Variavél lixo
    int i = 0;
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        while (i < 12) {
            fscanf(file, "%s", nome);
            fscanf(file, "%s %d", nome, &relatorio->meses[i].salariosProcessados);
            fscanf(file, "%s %f", nome, &relatorio->meses[i].despesaTotal);
            i++;
        }
        fscanf(file, "%s", nome);
        fscanf(file, "%s %f", nome, &relatorio->despesaTotal);
        relatorio->estadoRelatorio = 1;
    } else {
        puts("Erro!");
    }
    fclose(file);
}

/**
 * Imprime na consola o relatório da percentagem de funcionários pelo intervalo de idades
 * @param relatorio apontador para o relatório
 */
void imprimirPercentagemIdadesFuncionarios(PercentagemIdades *relatorio) {
    char percentagem [2] = "%";
    puts("---Percentagem Idades Funcionários--");
    printf("Número de Funcionarios analisados: %d \n", relatorio->funcionariosAnalisados);
    printf("Número de Funcionarios com Direito a Bónus por idade: %d \n", relatorio->funcionariosComBonus);
    printf("Número de Funcionarios sem Bónus por idade: %d \n", relatorio->funcionariosSemBonus);
    printf("Mais de 60 anos: %.2f%s\n", relatorio->percentagemMais60, percentagem);
    printf("Entre 51 e 60 anos: %f%s\n", relatorio->percentagemEntre51e60, percentagem);
    printf("Entre 41 e 50 anos: %f%s\n", relatorio->percentagemEntre41e50, percentagem);
    printf("Entre 26 e 30 anos: %f%s\n", relatorio->percentagemEntre31e40, percentagem);
    printf("Entre 31 e 40 anos: %f%s\n", relatorio->percentagemEntre26e30, percentagem);
    printf("Menos de 26 anos: %f%s\n", relatorio->percentagemMenos26, percentagem);
}

/**
 * Imprime na consola o relatório sobre o valor hora
 * @param relatorio apontador para o relatório
 */
void imprimirRelatorioValorHora(RelatorioValorHora *relatorio) {
    printf("Valor mais alto: %.2f€\n", relatorio->valorMaximoHora);
    printf("Valor mais baixo: %.2f€\n", relatorio->valorMinimoHora);
    printf("Medio: %.2f€\n", relatorio->valorMedio);
    printf("Diferença entre max-min: %.2f€\n", relatorio->valorMaximoHora - relatorio->valorMinimoHora);
}

/**
 * Imprime na consola o relatório da percentagem de funcionários por estado civil
 * @param relatorio apontador para o relatório 
 */
void imprimirRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio) {
    puts("Relatório sobre estado civil");
    printf("Percentagem de Não Casados %.2f \n", relatorio->percNaoCasado);
    printf("Percentagem de Casado Unico Titular %.2f \n", relatorio->percCasadoUnicoTitular);
    printf("Percentagem de Casado Dois Titulares %.2f\n", relatorio->percCasadoDoisTitulares);
}

/**
 * Imprime na consola a listagem de funcionários por faltas
 * @param gestaofaltas apontador para a listagem
 */
void imprimirGestaofaltas(RelatorioFaltas *gestaofaltas) {
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            puts("\n-------Janeiro-------------------");
        } else if (i == 1) {
            puts("\n-------Fevereiro-------------------");
        } else if (i == 2) {
            puts("\n-------Março-------------------");
        } else if (i == 3) {
            puts("\n-------Abril-------------------");
        } else if (i == 4) {
            puts("\n-------Maio-------------------");
        } else if (i == 5) {
            puts("\n-------Junho-------------------");
        } else if (i == 6) {
            puts("\n-------Julho-------------------");
        } else if (i == 7) {
            puts("\n-------Agosto-------------------");
        } else if (i == 8) {
            puts("\n-------Setembro-------------------");
        } else if (i == 9) {
            puts("\n-------Outobro-------------------");
        } else if (i == 10) {
            puts("\n-------Novembro-------------------");
        } else if (i == 11) {
            puts("\n-------Dezembro-------------------");
        }
        if (gestaofaltas->lista[i].nrFuncionariosAnalisados == 0) {
            printf("Mês Não analisado!\n");
        } else {
            printf("\nCódigos Funcionarios Sem faltas: \n");
            if (gestaofaltas->lista[i].nrSemfaltas == 0) {
                puts("Sem códigos");
            } else {
                for (int j = 0; j < gestaofaltas->lista[i].nrSemfaltas; j++) {
                    printf("%d ", gestaofaltas->lista[i].Semfaltas[j]);
                }
            }
            printf("\nFuncionarios 1 faltas: \n");
            for (int j = 0; j < gestaofaltas->lista[i].nrUmafaltas; j++) {
                printf("%d ", gestaofaltas->lista[i].Umafaltas[j]);
            };
            printf("\nFuncionarios 2/3 faltas: \n");
            for (int j = 0; j < gestaofaltas->lista[i].nrDuasouTresFaltas; j++) {
                printf("%d ", gestaofaltas->lista[i].DuasouTresFaltas[j]);
            }
            printf("\nFuncionarios Com mais 3 faltas: \n");
            for (int j = 0; j < gestaofaltas->lista[i].nrMaisTresFaltas; j++) {
                printf("%d ", gestaofaltas->lista[i].MaisTresFaltas[j]);
            }
        }

    }
}

/**
 * Imprime na consola o relatório sobre as despesas totais
 * @param despesas apontador para o relatório que contêm as despesas totais
 */
void imprimirDespesasTotais(DespesasAnuais *despesas) {
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            puts("-------Janeiro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 1) {
            puts("-------Febreiro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 2) {
            puts("-------Março-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 3) {
            puts("-------Abril-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 4) {
            puts("-------Maio-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 5) {
            puts("-------Junho-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 6) {
            puts("-------Julho-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 7) {
            puts("-------Agosto-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 8) {
            puts("-------Setembro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 9) {
            puts("-------Outubro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 10) {
            puts("-------Novembro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        } else if (i == 11) {
            puts("-------Dezembro-----------------");
            printf("Número de Salários processados:%d\n", despesas->meses[i].salariosProcessados);
            printf("Despesa Total: %.2f€\n", despesas->meses[i].despesaTotal);
        }
    }
    printf("Despesa TOTAL:%.2f€ \n", despesas->despesaTotal);
}

/**
 * Imprime na consola o relatório da percentagem de funcionários pelo seu tempo na empresa
 * @param relatorio apontador para o relatório
 */
void imprimirPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio) {
    char percentagem [2] = "%";
    puts("---Percentagem Funcionarios por anos na Empresa--");
    printf("Número de Funcionarios analisados: %d \n", relatorio->funcionariosAnalisados);
    printf("Número de Funcionarios com Direito a Bónus por idade: %d \n", relatorio->funcionariosComBonus);
    printf("Número de Funcionarios sem Bónus por idade: %d \n", relatorio->funcionariosSemBonus);
    printf("Mais de 20 anos: %.2f%s\n", relatorio->percentagemMais20, percentagem);
    printf("Entre 11 e 20 anos: %.2f%s\n", relatorio->percentagemEntre11e20, percentagem);
    printf("Entre 5 e 10 anos: %.2f%s\n", relatorio->percentagemEntre5e10, percentagem);
    printf("Menos de 5 anos: %.2f%s\n", relatorio->percentagemMenos5, percentagem);
}