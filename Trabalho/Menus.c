/**
 * @file Menus.c
 * @author Hugo Silva
 * @date  25 Novembro 2020
 * @brief Ficheiro c que implementa funções da biblioteca Menus.h
 * 
 * Ficheiro c que contém as implementações das funções para os menus
 */
#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"
#include "Utils.h"
#include "Listagens.h"
#define TITLE_IRS "Gestão Tabela IRS"
#define TITLE_SS "Gestão Tabela Segurança Social"
#define READ_FICHEIRO_MSG "Ler Ficheiro"
#define WRITE_FICHEIRO_MSG "Gravar Ficheiro"
#define TITLE_SALARIO "Processamento de salário"
#define MSG_TABELA_VAZIA "Tabela tem de ser importada!"
#define MSG_DADOS_EST "Listagens"
#define MSG_NAO_EXISTE_FICHEIRO_IMP "Não existe um ficheiro relativo a esse mês!"
#define MSG_CANCELA_PROCESSAMENTO "Cancelou processamento!"
#define IMPOSSIVEL_GUARDAR_FUNCIONARIOS "Impossível Guardar Lista Vazia!"
#define IMPOSSIVEL_GUARDAR_TIRS "Impossível Guardar Tabela de Irs Vazia!"
#define IMPOSSIVEL_GUARDAR_TSS "Impossível Guardar Tabelas Seguranca Social Vazia!"
#define IMPOSSIVEL_GUARDAR_RELATORIOIDADE  "Impossível Gerar Relatorio sobre idade!"
#define IMPOSSIVEL_GUARDAR_RELATORIOEMPRESA "Impossível Gerar Relatorio sobre tempo na empresa!"
#define IMPOSSIVEL_GUARDAR_RELATORIODESPESAS "Impossível Gerar Relatorio sobre despesasTotais !"
#define IMPOSSIVEL_GUARDAR_RELATORIOVALORHORA "Impossível Gerar Relatorio sobre Valor por  hora !"
#define IMPOSSIVEL_GUARDAR_RELATORIODESTADOCIVIL "Impossível Gerar Relatorio sobre Estado Civil!"
#define IMPOSSIVEL_GUARDAR_RELATORIOFALTAS "Impossível Gerar Relatorio sobre Faltas"
#define MSG_CANCELOU_OP "Cancelou Execução!"
#define MSG_LISTAFUNCVAZIA "Lista de funcionários vazia!"
#define MSG_LOG_SUCESSO "Acesso ao ficheiro para leitura!"
#define MSG_ADD_ERRO "Código já existente!"
#define MSG_ADD_SUCESSO "Inserido com sucesso!"
#define TITLE_1 "Gestão de Funcionários"
#define ADD_FUNCIONARIO "Criar Funcionário"
#define EDITAR_FUNCIONARIO "Editar Funcionário"
#define REMOVER_FUNCIONARIO "Remover Funcionário "
#include "Funcionario.h"
#include "GestaoFuncionarios.h"
#include "FuncionariosFx.h"
#include "TabelaSegurancaSocial.h"
#include "TabelaIrs.h"
#include "ProcessamentoSalario.h"
#include "ProcessamentoSalarioFX.h"
#include "Utils.h"
#include "Logs.h"
#include <string.h>

/**
 * Menu de alterações de dados de um funcionário  
 * @param func apontador para o funcionário que será editado
 */
void menuEditarFuncionario(Funcionario *func) {
    int opcao;
    do {
        opcao = -1;
        puts("----------------------");
        puts("Edição do Funcionário \n");
        puts("----------------------");
        printf("0. CONCLUIR edição  \n");
        printf("1. Número de Dependentes \n");
        printf("2. Subsídio Alimentacão \n");
        printf("3. Valor por hora!\n");
        printf("4. Número telemovel \n");
        printf("5. Cargo na Empresa \n");
        printf("6. Estado Civil \n");
        printf("7. Data Entrada na Empresa\n");
        printf("8. Data Nascimento \n");
        printf("9. Nome do Funcionário \n");
        printf("10. Data Saída da Empresa \n");
        printf("11. NR Critério SS \n");
        puts("Insira a sua opção [0-11]:");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                break;
            case 1:
                puts("Número de Filhos");
                scanf("%d", &func->nrDependentes);
                break;
            case 2:
                puts("Subsidio Alimentaçao");
                scanf("%f", &func->subsidioAlimentacao);
                break;
            case 3:
                puts("Valor que recebe por hora!");
                scanf("%f", &func->valorHora);
                break;
            case 4:
                puts("Número de Telemóvel");
                numeroTelemovel(func);
                break;
            case 5:
                func->estadoCivil = estadoCivil();
                break;
            case 6:
                func->cargoEmpresa = cargoFuncionario();
                break;
            case 7:
                lerData(&func->dataEntradaEmpresa, ANO_MAX_ENTRADA);
                break;
            case 8:
                lerData(&func->dataNascimento, ANO_MAX);
                break;
            case 9:
                puts("Escreva o nome do Funcionario");
                fgets(func->nome, TAMANHO_STRING, stdin);
                break;
            case 10:
                lerData(&func->dataSaidaEmpresa, ANO_MAX_ENTRADA);
                break;
            case 11:
                puts("Critério Segurança Social a aplicar");
                scanf("%d", &func->criterioSS);
                break;
            default:
                puts("Opção inválida!");
                break;
        }
    } while (opcao != 0);
}

/**
 * Menu principal da gestão de funcionários, contêm  várias operações que é possível realizar (Edição, Remoção, Listagem e Criação de funcionários) 
 * @param listaFuncionarios apontador para a lista de funcionários
 */
void menuPrincipalFuncionarios(ListaFuncionarios *listaFuncionarios) {
    char opcaoo;
    int aux;
    do {
        puts("----------------------");
        puts("Gestão de Funcionários");
        puts("----------------------");
        printf("1. %s\n", ADD_FUNCIONARIO);
        printf("2. %s\n", EDITAR_FUNCIONARIO);
        printf("3. %s\n", REMOVER_FUNCIONARIO);
        printf("4. Listar todos funcionários \n");
        printf("5. Mostrar dados de um  funcionário\n");
        puts("0. Voltar ao menu principal");
        printf("----NrFuncionarios: %d/ %d \n", listaFuncionarios->nrFuncionarios, listaFuncionarios->tamanho);
        puts("Insira a sua opção [1-5]:");
        scanf(" %c", &opcaoo);
        switch (opcaoo) {
            case '0':
                break;
            case '1':
                if (listaFuncionarios->tamanho == 0) {
                    funcaoAlocarMemoria(listaFuncionarios);
                } //Não existe memória, aloca-se
                adicionarFuncionario(listaFuncionarios) == 1 ? puts(MSG_ADD_SUCESSO) : puts(MSG_ADD_ERRO);
                break;
            case '2':
                if (listaFuncionarios->nrFuncionarios == 0) {
                    puts(MSG_LISTAFUNCVAZIA);
                } else {
                    puts("Insira o id do Funcionário a editar:");
                    scanf("%d", &aux);
                    atualizaFuncionario(listaFuncionarios, aux);
                }
                break;
            case '3':
                if (listaFuncionarios->nrFuncionarios == 0) {
                    puts(MSG_LISTAFUNCVAZIA);
                } else {
                    puts("Insira o id do Funcionário a remover:");
                    scanf("%d", &aux);
                    apagarFuncionario(listaFuncionarios, aux);
                }
                break;
            case '4':
                listarTodosFuncionarios(listaFuncionarios);
                break;
            case '5':
                  if (listaFuncionarios->nrFuncionarios == 0) {
                    puts(MSG_LISTAFUNCVAZIA);
                } else {
                puts("Código do funcionário");
                scanf("%d", &aux);
                mostraFuncionario(listaFuncionarios, aux);
                }
                break;
            default:
                puts("Opção inválida!");
                break;
        }

    } while (opcaoo != '0');

}

/**
 * Menu de gestão da tabela de Segurança Social
 * @param tabelaSegurancaSocial apontador para a tabela 
 */
void menuTabelaSegurancaSocial(TabelaSegurancaSocial *tabelaSegurancaSocial) {
    char opcao;
    do {
        puts("--------------------");
        puts("----Tabela Segurança Social--");
        puts("1. Visualizar tabela");
        puts("2. Editar linha da tabela");
        puts("3. Adicionar novo campo");
        puts("4. Importar Tabela");
        puts("5. Eliminar Linha");
        puts("0. Voltar ao menu Principal");
        printf("Memoria da Tabela %d/%d \n", tabelaSegurancaSocial->numeroLinhas, tabelaSegurancaSocial->tamanho);
        puts("Insira a sua opção [1-5]:");
        scanf(" %c", &opcao);
        switch (opcao) {
            case '0':
                break;
            case '1':
                tabelaSegurancaSocial->numeroLinhas != 0 ? imprimirTabela(*tabelaSegurancaSocial) : puts(MSG_TABELA_VAZIA);
                break;
            case '2':
                tabelaSegurancaSocial->numeroLinhas != 0 ? editarTaxa(tabelaSegurancaSocial) : puts(MSG_TABELA_VAZIA);
                break;
            case '3':
                tabelaSegurancaSocial->numeroLinhas != 0 ? adicionarNovaTaxa(tabelaSegurancaSocial) : puts(MSG_TABELA_VAZIA);
                break;
            case '4':
                libertarMemoriaTabelaSS(tabelaSegurancaSocial);
                lerFicheiroSegurancaSocial(tabelaSegurancaSocial, FILE_SEGURANCA_SOCIAL);
                break;
            case '5':
                tabelaSegurancaSocial->numeroLinhas != 0 ? removerLinha(tabelaSegurancaSocial) : puts(MSG_TABELA_VAZIA);
                break;
            default:
                puts("Inválido");
                break;
        }

    } while (opcao != '0');
}

/**
 * Função que imprime os meses do ano
 */
void imprimirMeses() {
    puts("1. Janeiro");
    puts("2. Fevereiro");
    puts("3. Março");
    puts("4. Abril");
    puts("5. Maio");
    puts("6. Junho");
    puts("7. Julho");
    puts("8. Agosto");
    puts("9. Setembro");
    puts("10.Outrubro");
    puts("11.Novembro");
    puts("12.Dezembro");
    puts("0. SAIR");
}

/**
 * Menu para as listagens propostas pelo grupo
 * @param listaFuncionarios lista de funcionários
 * @param relatorioIdades apontador para o relatório das percentagens por intervalo de idade
 * @param relatorioTempoEmpresa apontador para o relatório das percentagens por anos na empresa
 * @param relatorioDespesasAnuais apontador para o relatório das despesas anuais
 * @param gestaoFaltas apontador para a listagem de funcionários por faltas 
 * @param relatorioVhora apontador para a listagem dos valores hora 
 * @param relatorioEstadoCivil apontador para o relatório das percentagens por estado civil
 */
void menuListagens(ListaFuncionarios listaFuncionarios, PercentagemIdades *relatorioIdades, PercentagemTempoEmpresa *relatorioTempoEmpresa, DespesasAnuais *relatorioDespesasAnuais, RelatorioFaltas *gestaoFaltas,
        RelatorioValorHora *relatorioVhora, PercentagemEstadoCivil *relatorioEstadoCivil) {
    int aux;
    char opcao;
    do {
        aux = 0;
        puts("--------------------");
        puts("----Dados Estatisticos--");
        puts("1. Percentagem de Idades Funcionarios");
        puts("2. Despesas Totais da empresa por mês");
        puts("3. Percentagem por Tempo na Empresa");
        puts("4. Detalhes faltas");
        puts("5. Valor Médio por Hora//Valor Máximo//Valor Minímo");
        puts("6. Percentagem por estado Civil");
        puts("0. Sair");
        puts("Insira a sua opção [1-6]:");
        scanf(" %c", &opcao);
        switch (opcao) {
            case '0':
                break;
            case '1':
                if (relatorioIdades->funcionariosAnalisados != 0)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                    if (listaFuncionarios.nrFuncionarios != 0) { //Caso lista vazia
                     percentagemIdadesFuncionarios(listaFuncionarios, relatorioIdades), imprimirPercentagemIdadesFuncionarios(relatorioIdades);
                        } else { //Caso não exista relatorio
                            puts(MSG_LISTAFUNCVAZIA);
                        }
                } else {
                    imprimirPercentagemIdadesFuncionarios(relatorioIdades);
                }
                break;
            case '2':
                if (relatorioDespesasAnuais->estadoRelatorio == 1)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                        DespesasTotais(relatorioDespesasAnuais);
                        imprimirDespesasTotais(relatorioDespesasAnuais);
                } else {
                    imprimirDespesasTotais(relatorioDespesasAnuais);
                }
                break;
            case '3':
                if (relatorioTempoEmpresa->funcionariosAnalisados != 0)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                    if (listaFuncionarios.nrFuncionarios != 0) {
                            percentagemTempoEmpresa(listaFuncionarios, relatorioTempoEmpresa);
                            imprimirPercentagemTempoEmpresa(relatorioTempoEmpresa);
                    } else {
                        puts(MSG_LISTAFUNCVAZIA);
                    }
                } else {
                    imprimirPercentagemTempoEmpresa(relatorioTempoEmpresa);
                }

                break;
            case '4':
                if (gestaoFaltas->estadoRelatorio == 1)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                    libertarMemoriaGestaoFaltas(gestaoFaltas);
                    listagemFuncionariosPorFaltas(gestaoFaltas);
                    imprimirGestaofaltas(gestaoFaltas);
                } else {
                    imprimirGestaofaltas(gestaoFaltas);
                }
                break;
            case '5':
                if (relatorioVhora->estadoRelatorio == 1)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                    if (listaFuncionarios.nrFuncionarios != 0) {
                        relatorioValorHora(listaFuncionarios, relatorioVhora);
                        imprimirRelatorioValorHora(relatorioVhora);
                    } else {
                        puts(MSG_LISTAFUNCVAZIA);
                    }
                } else {
                    imprimirRelatorioValorHora(relatorioVhora);
                }
                break;
            case '6':
                if (relatorioEstadoCivil->estadoRelatorio == 1)aux = visualizarRelatorioemMemoria();
                if (aux == 0) {
                    if (listaFuncionarios.nrFuncionarios != 0) {
                        relatorioPercentagemEstadoCivil(listaFuncionarios, relatorioEstadoCivil);
                        imprimirRelatorioPercentagemEstadoCivil(relatorioEstadoCivil);
                    } else {
                        puts(MSG_LISTAFUNCVAZIA);
                    }
                } else {
                    imprimirRelatorioPercentagemEstadoCivil(relatorioEstadoCivil);
                }
                break;
            default:
                puts("Inválido");
                break;
        }
    } while (opcao != '0');
}

/**
 * Menu de gestão das tabelas de IRS
 * @param tabela apontador para a tabelas de IRS
 */
void menuTabelasIrs(TabelaIrs * tabela) {
    int opcao;
    do {
        opcao = -1;
        puts("--------------------");
        puts("----Tabela IRS--");
        puts("--------------------");
        puts("1. Visualizar tabelas");
        puts("2. Editar tabela");
        puts("3. Adicionar campo tabela");
        puts("4. Importar tabela");
        puts("5. Remover linha da tabela");
        puts("0. Voltar ao menu Principal");
        puts("Insira a sua opção [1-5]:");
        printf("Memoria Tabela %d/%d\n", tabela->numeroLinhas, tabela->tamanho);
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                break;
            case 1:
                tabela->numeroLinhas != 0 ? imprimirTodasTabelasIrs(*tabela) : puts(MSG_TABELA_VAZIA);
                break;
            case 2:
                tabela->numeroLinhas != 0 ? editarTabelaIRS(tabela) : puts(MSG_TABELA_VAZIA);
                break;
            case 3:
                tabela->numeroLinhas != 0 ? adicionarNovosCriterios(tabela) : puts(MSG_TABELA_VAZIA);
                break;
            case 4:
                libertarMemoriaTabelaIRS(tabela);
                lerFicheiroIrs(tabela, FILEIRS);
                break;
            case 5:
                tabela->numeroLinhas != 0 ? removerLinhaTabelaIrs(tabela) : puts(MSG_TABELA_VAZIA);
                break;
            default:
                puts("Invalida");
                break;
        }

    } while (opcao != 0);
}

/**
 * Menu responsável pelas operações relacionadas com processamento de salário
 * @param listaProcessamentos apontador para a lista que armazena os dados para processamento
 * @param listaFuncionarios lista de funcionários
 * @param tabelaIrs tabelas de IRS
 * @param tabelaSegurancaSocial tabela da Segurança Social
 * @param relatoriosGuardados apontador para a lista de relatórios processados
 */
void menuProcessamentoSalario(ListaFuncionarios listaFuncionarios, TabelaIrs tabelaIrs, TabelaSegurancaSocial tabelaSegurancaSocial, ListaTodosVencimentosProcessados *relatoriosGuardados) {
    ListaProcessamentos listaProcessamentos = {.numeroSalariosaProcessar = 0};
    char FicheiroImport[20];
    char FicheiroRelatorio[25];
    int opcao;
    int aux = 0, substituirRelatorio;
    do {
        opcao = -1;
        substituirRelatorio = 0;
        aux = 0;
        puts("--------------------");
        puts("----Processamento de Salario--");
        puts("--------------------");
        imprimirMeses();
        printf("Meses PROCESSADOS %d/12\n", relatoriosGuardados->nrMesesProcessados);
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                FicheiroImport[0] = '\0';
                break;
            case 1:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JAN);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_JAN);
                break;
            case 2:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_FEV);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_FEV);
                break;
            case 3:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_MAR);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_MAR);
                break;
            case 4:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_ABR);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_ABR);
                break;
            case 5:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_MAI);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_MAI);
                break;
            case 6:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JUN);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_JUN);
                break;
            case 7:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_JUL);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_JUL);
                break;
            case 8:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_AGO);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_AGO);
                break;
            case 9:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_SET);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_SET);
                break;
            case 10:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_OUT);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_OUT);
                break;
            case 11:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_NOV);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_NOV);
                break;
            case 12:
                strcpy(FicheiroImport, NOME_FICHEIROIMP_DEZ);
                strcpy(FicheiroRelatorio, NOME_RELATORIO_DEZ);
                break;
            case 13:
                //imprimirVencimentosProcessados(*listaVencimentosProcessados);
                break;
            default:
                puts("Invalida");
                FicheiroImport[0] = '\0';
                break;
        }
        if (FicheiroImport[0] != '\0') { //Verifica Relatório em memória
            if (opcao == 1) {
                if (relatoriosGuardados->janeiro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->janeiro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->janeiro), imprimirVencimentosProcessados(relatoriosGuardados->janeiro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->janeiro);
                    }
                } else {
                    relatoriosGuardados->nrMesesProcessados++;
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->janeiro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->janeiro), imprimirVencimentosProcessados(relatoriosGuardados->janeiro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 2) {
                if (relatoriosGuardados->fevereiro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->fevereiro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->fevereiro), imprimirVencimentosProcessados(relatoriosGuardados->fevereiro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->fevereiro);
                    }
                } else {
                   
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->fevereiro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->fevereiro), imprimirVencimentosProcessados(relatoriosGuardados->fevereiro), relatoriosGuardados->nrMesesProcessados++ : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 3) {
                if (relatoriosGuardados->marco.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->marco),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->marco), imprimirVencimentosProcessados(relatoriosGuardados->marco) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->marco);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->marco),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->marco), imprimirVencimentosProcessados(relatoriosGuardados->marco), relatoriosGuardados->nrMesesProcessados++ : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 4) {
                if (relatoriosGuardados->abril.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->abril),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->abril), imprimirVencimentosProcessados(relatoriosGuardados->abril) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->abril);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? relatoriosGuardados->nrMesesProcessados++,carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->abril),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->abril), imprimirVencimentosProcessados(relatoriosGuardados->abril) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 5) {
                if (relatoriosGuardados->maio.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->maio),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->maio), imprimirVencimentosProcessados(relatoriosGuardados->maio) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->maio);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->maio),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->maio), imprimirVencimentosProcessados(relatoriosGuardados->maio),    relatoriosGuardados->nrMesesProcessados++: puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 6) {
                if (relatoriosGuardados->junho.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->junho),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->junho), imprimirVencimentosProcessados(relatoriosGuardados->junho) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->junho);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->junho),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->junho), imprimirVencimentosProcessados(relatoriosGuardados->junho), relatoriosGuardados->nrMesesProcessados++ : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 7) {
                if (relatoriosGuardados->julho.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->julho),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->julho), imprimirVencimentosProcessados(relatoriosGuardados->julho) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->julho);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->julho),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->julho), imprimirVencimentosProcessados(relatoriosGuardados->julho),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 8) {
                if (relatoriosGuardados->agosto.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->agosto),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->agosto), imprimirVencimentosProcessados(relatoriosGuardados->agosto) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->agosto);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->agosto),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->agosto), imprimirVencimentosProcessados(relatoriosGuardados->agosto),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 9) {
                if (relatoriosGuardados->setembro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->setembro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->setembro), imprimirVencimentosProcessados(relatoriosGuardados->setembro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->setembro);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->setembro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->setembro), imprimirVencimentosProcessados(relatoriosGuardados->setembro),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 10) {
                if (relatoriosGuardados->outubro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->outubro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->outubro), imprimirVencimentosProcessados(relatoriosGuardados->outubro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->outubro);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->outubro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->outubro), imprimirVencimentosProcessados(relatoriosGuardados->outubro),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 11) {
                if (relatoriosGuardados->novembro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->novembro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->novembro), imprimirVencimentosProcessados(relatoriosGuardados->novembro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->novembro);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->novembro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->novembro), imprimirVencimentosProcessados(relatoriosGuardados->novembro),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            } else if (opcao == 12) {
                if (relatoriosGuardados->dezembro.nrProcessamentos != 0) {
                    aux = visualizarRelatorioemMemoria();
                    if (aux == 0) {
                        verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->dezembro),
                                ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->dezembro), imprimirVencimentosProcessados(relatoriosGuardados->dezembro) : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                    } else {
                        imprimirVencimentosProcessados(relatoriosGuardados->dezembro);
                    }
                } else {
                    verificaExistenciaFicheiro(FicheiroImport) == 1 ? carregarFicheiroProcessamento(&listaProcessamentos, FicheiroImport, FicheiroRelatorio, &relatoriosGuardados->dezembro),
                            ProcessamentoSalario(listaProcessamentos, listaFuncionarios, tabelaIrs, tabelaSegurancaSocial, &relatoriosGuardados->dezembro), imprimirVencimentosProcessados(relatoriosGuardados->dezembro),relatoriosGuardados->nrMesesProcessados++  : puts(MSG_NAO_EXISTE_FICHEIRO_IMP);
                }
            }

            listaProcessamentos.numeroSalariosaProcessar == 0 ? : libertarMemoriaDadosProcessamento(&listaProcessamentos); //Liberta memória de lista já não usada, caso tenha sido criada
        }
       
    } while (opcao != 0);
}
/**
 * Menu principal do programa
 * @param listaFuncionarios apontador para a lista de funcionários
 * @param tabelaSegurancaSocial apontador para a tabela de Segurança Social
 * @param tabelaIrs apontador para as tabelas de IRS
 * @param listaProcessamentos apontador para a lista de dados para processamento de salário
 * @param listaVencimentosProcessados apontador para a lista de vencimentos processados
 * @param relatoriosGuardados apontador para a lista de relatórios guardados em ficheiro
 */
void menuPrincipal(ListaFuncionarios *listaFuncionarios, TabelaSegurancaSocial *tabelaSegurancaSocial, TabelaIrs *tabelaIrs,
        ListaTodosVencimentosProcessados *relatoriosVencimentosProcessados) {
    int opcao;
    PercentagemIdades relatorioIdade = {.funcionariosAnalisados = 0};
    PercentagemTempoEmpresa relatorioTempoEmpresa = {.funcionariosAnalisados = 0};
    DespesasAnuais despesas = {.estadoRelatorio = 0};
    RelatorioFaltas relatorioFaltas = {.estadoRelatorio = 0};
    RelatorioValorHora relatorioValorhora = {.estadoRelatorio = 0};
    PercentagemEstadoCivil relatorioEstadoCivil = {.estadoRelatorio = 0};
    do {
        opcao = -1;
        puts("--------------------");
        puts("----Menu-Principal--");
        puts("--------------------");
        printf("1. %s\n", TITLE_1);
        printf("2. %s\n", TITLE_IRS);
        printf("3. %s\n", TITLE_SS);
        printf("4. %s\n", READ_FICHEIRO_MSG);
        printf("5. %s\n", WRITE_FICHEIRO_MSG);
        printf("6. %s\n", TITLE_SALARIO);
        printf("7. %s\n", MSG_DADOS_EST);
        puts("0. Sair");
        puts("Insira a sua opção [1-7]:");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                libertarMemoriaGestaoFaltas(&relatorioFaltas);
                break;
            case 1:
                menuPrincipalFuncionarios(listaFuncionarios);
                break;
            case  2:
                menuTabelasIrs(tabelaIrs);
                break;
            case  3:
                menuTabelaSegurancaSocial(tabelaSegurancaSocial);
                break;
            case  4:
                //Liberta a memória alocada, caso alocada e lê os ficheiros
                if(listaFuncionarios->tamanho != 0){libertarMemoriaFuncionarios(listaFuncionarios);}
                if(tabelaIrs->tamanho != 0){  libertarMemoriaTabelaIRS(tabelaIrs);}
                if(tabelaSegurancaSocial->tamanho != 0){libertarMemoriaTabelaSS(tabelaSegurancaSocial);}
                if(relatorioFaltas.estadoRelatorio == 1){libertarMemoriaGestaoFaltas(&relatorioFaltas);}
                libertarMemoriaRelatoriosProcessados(relatoriosVencimentosProcessados);
                obterRelatorioDespesasTotais(&despesas,FILENAME_DESPESASTOTAIS);
                obterRelatoriopercentagemIdadesFuncionarios(&relatorioIdade,FILENAME_PERCENTAGEMIDADES);
                obterRelatorioPercentagemTempoEmpresa(&relatorioTempoEmpresa,FILENAME_PERCENTAGEMANOSEMPRESA);
                obterRelatorioFaltas(&relatorioFaltas,FILENAME_RELATORIOFALTAS);
                logMsg("Leitura Relatórios Processados", LOG_FILE);
                obterTodosRelatoriosProcessados(relatoriosVencimentosProcessados);
                logMsg("Leitura Ficheiro Segurança Social", LOG_FILE);
                lerFicheiroSegurancaSocial(tabelaSegurancaSocial, FILE_SEGURANCA_SOCIAL);
                logMsg("Leitura Ficheiro Funcionários", LOG_FILE);
                carregarFuncionariosFx(listaFuncionarios, FILE_FUNCIONARIOS);
                logMsg("Leitura Ficheiro IRS", LOG_FILE);
                lerFicheiroIrs(tabelaIrs, FILEIRS);
                if (verificaExistenciaFicheiro(FILENAME_RELATORIOVALORH) == 1) {
                    obterRelatorioValorHora(&relatorioValorhora, FILENAME_RELATORIOVALORH);
                }
                if (verificaExistenciaFicheiro(FILENAME_RELATORIOESTADOCIVIL) == 1) {
                    obterRelatorioPercentagemEstadoCivil(&relatorioEstadoCivil, FILENAME_RELATORIOESTADOCIVIL);
                }
                break;
            case  5:
                listaFuncionarios->nrFuncionarios == 0 ? puts(IMPOSSIVEL_GUARDAR_FUNCIONARIOS) : guardarFuncionariosFx(listaFuncionarios, FILE_FUNCIONARIOS), logMsg("Escrita Ficheiro Funcionários", LOG_FILE);
                tabelaIrs->numeroLinhas == 0 ? puts(IMPOSSIVEL_GUARDAR_TIRS) : escreverTabelaFicheiroIRS(*tabelaIrs, FILEIRS), logMsg("Escrita Ficheiro Irs", LOG_FILE);
                tabelaSegurancaSocial->numeroLinhas == 0 ? puts(IMPOSSIVEL_GUARDAR_TSS) : escreverTabelaFicheiro(*tabelaSegurancaSocial, FILE_SEGURANCA_SOCIAL), logMsg("Escrita Ficheiro Segurança Social", LOG_FILE);
                relatorioIdade.funcionariosAnalisados == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIOIDADE) : gerarRelatoriopercentagemIdadesFuncionarios(&relatorioIdade, FILENAME_PERCENTAGEMIDADES), logMsg("Escrita Relatorio Percentagem Idade", LOG_FILE);
                relatorioTempoEmpresa.funcionariosAnalisados == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIOEMPRESA) : gerarRelatorioPercentagemTempoEmpresa(&relatorioTempoEmpresa, FILENAME_PERCENTAGEMANOSEMPRESA), logMsg("Escrita Relatorio Tempo Empresa", LOG_FILE);
                despesas.estadoRelatorio == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIODESPESAS) : gerarRelatorioDespesasTotais(&despesas, FILENAME_DESPESASTOTAIS), logMsg("Escrita Relatorio Despesas Totais", LOG_FILE);
                relatorioFaltas.estadoRelatorio == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIOFALTAS) : gerarRelatorioFaltas(&relatorioFaltas, FILENAME_RELATORIOFALTAS), logMsg("Escrita Relatorio Faltas", LOG_FILE);
                relatorioValorhora.estadoRelatorio == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIOVALORHORA) : gerarRelatorioValorHora(&relatorioValorhora, FILENAME_RELATORIOVALORH), logMsg("Escrita Relatorio Valor Hora", LOG_FILE);
                relatorioEstadoCivil.estadoRelatorio == 0 ? puts(IMPOSSIVEL_GUARDAR_RELATORIODESTADOCIVIL) : gerarRelatorioPercentagemEstadoCivil(&relatorioEstadoCivil, FILENAME_RELATORIOESTADOCIVIL), logMsg("Escrita Relatorio Estado Civil", LOG_FILE);
                guardarRelatoriosProcessados(*relatoriosVencimentosProcessados);
                break;
            case 6:
                if (listaFuncionarios->nrFuncionarios == 0 || tabelaIrs->numeroLinhas == 0 || tabelaSegurancaSocial->numeroLinhas == 0) {
                    puts("Para executar processamento salário é necessário Tabelas Irs e SS bem como lista funcionarios");
                } else {
                    menuProcessamentoSalario(*listaFuncionarios, *tabelaIrs, *tabelaSegurancaSocial, relatoriosVencimentosProcessados);
                }
                break;
            case 7:
                menuListagens(*listaFuncionarios, &relatorioIdade, &relatorioTempoEmpresa, &despesas, &relatorioFaltas, &relatorioValorhora, &relatorioEstadoCivil);
                break;
            default:
                puts("Opção inválida!");
                break;
        }
    } while (opcao != 0);
}
