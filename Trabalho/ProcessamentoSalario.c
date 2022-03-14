/**
 * @file ProcessamentoSalario.c
 * @author Hugo Silva
 * @date  25 Novembro 2020
 * @brief Ficheiro c que implementa as funções da biblioteca ProcessamentoSalario.h
 * 
 * Ficheiro c que implementa as funções da bibloteca ProcessamentoSalario, responsável pelos cálculos de salário de um conjunto de funcionários 
 */
#include <stdio.h>
#include <stdlib.h>
#include "ProcessamentoSalario.h"
#include "TabelaIrs.h"
#include "TabelaSegurancaSocial.h"
#include "Utils.h"
#include "GestaoFuncionarios.h"
#define NUMERO_HORAS_DIA 8
#define NUMERO_HORAS_MEIO_DIA 4
#define VALOR_PER 0.01

/**
 * Calcula o valor do subsídio de alimentação de um funcionário
 * @param numeroDiasTrabalhadosSemana número de dias  trabalhou na semana
 * @param numeroDiasTrabalhadosFimdesemana número de dias que trabalhou no fim de semana
 * @param subsidio valor do subsídio do funcionário por dia
 * @return retorna o valor resultante do produto do número de dias trabalhados com o valor do subsídio que o funcionário recebe por dia
 */
float subsidioAlimentacao(int numeroDiasTrabalhadosSemana, int numeroDiasTrabalhadosFimdesemana, float subsidio) {
    return (numeroDiasTrabalhadosSemana + numeroDiasTrabalhadosFimdesemana) * subsidio;
}

/**
 * Calcula o salário bruto fruto do número de dias  trabalhados
 * @param numeroDiasTrabalhadosSemana número de dias que o funcionário trabalhou na semana
 * @param numeroDiasTrabalhadosFimdesemana número de dias que trabalhou no fim de semana
 * @param numeroMeioDiasTrabalhados número de meios dias  trabalhou
 * @param valorHora valor que o funcionário ganha por hora
 * @return retorna o valor correspondente ao salário bruto do funcionário
 */
float calculoSalarioBruto(int numeroDiasTrabalhadosSemana, int numeroDiasTrabalhadosFimdesemana, int numeroMeioDiasTrabalhados, float valorHora) {
    const float valorPorDia = NUMERO_HORAS_DIA * valorHora, valorMeioDia = NUMERO_HORAS_MEIO_DIA * valorHora;
    float salarioSemana = valorPorDia * numeroDiasTrabalhadosSemana;
    float salarioFimdeSemana = (valorPorDia * numeroDiasTrabalhadosFimdesemana) + ((valorPorDia * numeroDiasTrabalhadosFimdesemana) * 0.5); //val + 50%
    float salarioMeioDia = numeroMeioDiasTrabalhados* valorMeioDia;
    return salarioSemana + salarioFimdeSemana + salarioMeioDia;
}

/**
 * Calcula o bónus a receber pelo funcionário face à sua idade, tempo na empresa e número de faltas
 * @param dataNascimento data de nascimento utilizada para obter a sua idade
 * @param dataEntrada  data de entrada na empresa para obter anos de experiência
 * @param numeroFaltas número de faltas 
 * @param salarioBruto valor utilizado para cáculo do bónus
 * @return um valor positivo caso a percentagem de bónus seja positiva, retorna um valor negativo caso o funcionário contenha um numéro excessivo de faltas
 */
float calculoBonus(Data dataNascimento, Data dataEntrada, int numeroFaltas, float salarioBruto) {
    float bonus; // percentagem bonus
    int idade = calcularIdade(dataNascimento);
    int anosnaEmpresa = calcularIdade(dataEntrada);
    //Idade
    if (idade > 60) { //Trabalhador com + de 60 anos
        bonus = 15;
    } else if (idade <= 60 && idade > 50) {//Trabalhador entre 51 e 60 anos
        bonus = 12;
    } else if (idade <= 50 && idade > 41) { //Trabalhador entre 41 e 50 anos
        bonus = 10.5;
    } else if (idade <= 40 && idade > 30) { //Trabalhador entre 31 e 40 anos
        bonus = 7.5;
    } else if (idade <= 30 && idade > 25) { // Trabalhador entre 26 e 30 anos
        bonus = 5.5;
    } else {
        bonus = 0;
    }
    //Data entrada na empresa
    if (anosnaEmpresa > 4 && anosnaEmpresa <= 10) { //Entre 5 e 10 anos
        bonus = bonus + 2.5;
    } else if (anosnaEmpresa > 10 && anosnaEmpresa <= 20) {// Entre 11 e 20 anos
        bonus = bonus + 5.5;
    } else if (anosnaEmpresa > 20) { //Mais 20 anos;
        bonus = bonus + 7.5;
    }
    //Assuidade
    if (numeroFaltas == 0) { //Nunca falta + bonus de 0.5%
        bonus = bonus + 0.5;
    } else if (numeroFaltas == 1) {// uma falta - 2%
        bonus = bonus - 1.5;
    } else if (numeroFaltas == 2 || numeroFaltas == 3) { // duas ou 3 faltaS - 2%
        bonus = bonus - 3.5;
    } else if (numeroFaltas > 3) { // 3 ou mais faltas
        bonus = bonus - (numeroFaltas * 1.5);
    }
    return salarioBruto * (bonus * VALOR_PER);
}

/**
 * Efetua o cálculo de retenção de IRS mediante o estado civil, número de dependentes e nível salarial
 * @param tabelaIrs tabelas de IRS 
 * @param func informação relativa a um funcionário
 * @param salarioBruto salário bruto no qual será aplicada a taxa de retenção 
 * @return  valor da retenção de IRS resultante do produto do salário bruto com a taxa
 */
float calculoRetencaoIrs(TabelaIrs tabelaIrs, Funcionario func, float salarioBruto) {
    int aux = 0, i = 0;
    Irs tabelaPesquisa[tabelaIrs.numeroLinhas];
    //Faz a copia da tabela apenas necessaria
    for (i = 0; i < tabelaIrs.numeroLinhas; i++) {
        if (func.estadoCivil == tabelaIrs.listaCriterios[i].ident) {
            tabelaPesquisa[aux] = tabelaIrs.listaCriterios[i];
            aux++;
        }
    }
    //Procura nivel salarial
    i = 0;
    while (salarioBruto > tabelaPesquisa[i].nivelSalario && i < aux) {
        i++;
    }
    //Caso o nivel seja o ultimo nivel
    if (i == aux) {
        i--;
    }
    if (func.nrDependentes == 0) {
        return salarioBruto * (tabelaPesquisa[i].semDependentes * VALOR_PER);
    } else if (func.nrDependentes == 1) {
        return salarioBruto * (tabelaPesquisa[i].umDependente * 0.01);
    } else if (func.nrDependentes == 2) {
        return salarioBruto * (tabelaPesquisa[i].doisDependentes * VALOR_PER);
    } else if (func.nrDependentes == 3) {
        return salarioBruto * (tabelaPesquisa[i].tresDependentes * VALOR_PER);
    } else if (func.nrDependentes == 4) {
        return salarioBruto * (tabelaPesquisa[i].quatroDependentes * VALOR_PER);
    } else {
        return salarioBruto * (tabelaPesquisa[i].cincoMaisDependentes * VALOR_PER);
    }
}

/**
 * Calcula o valor a pagar pelo funcionário e pela entidade empregadora à Segurança Social
 * @param tabelaSegurancaSocial tabela com as taxas que podem ser aplicadas
 * @param func dados do funcionário na qual está a identificação da taxa que será aplicada
 * @param salarioBruto valor do salário na qual será aplicada a taxa
 * @param impostoSegurancaSocialEmpresa apontador irá armazenar o valor correspondente à entidade empregadora 
 * @return valor resultante do produto do salário bruto com a taxa aplicada
 */
float calculoSegurancaSocial(TabelaSegurancaSocial tabelaSegurancaSocial, Funcionario func, float salarioBruto, float *impostoSegurancaSocialEmpresa) {
    int i = 0, opcao = 0;
    float entidadeEmpregadora, funcionario, global;
    while (i < tabelaSegurancaSocial.numeroLinhas && opcao == 0) {
        if (func.criterioSS == tabelaSegurancaSocial.taxas[i].idTaxa) {
            opcao = 1;
            entidadeEmpregadora = tabelaSegurancaSocial.taxas[i].EntidadeEmpregadadora *VALOR_PER;
            funcionario = tabelaSegurancaSocial.taxas[i].Trabalhador * VALOR_PER;
            global = funcionario + entidadeEmpregadora;
        }
        i++;
    }
    if (opcao == 0) { //Caso o número de criterio do funcionário não existir na tabela, usa o geral
        entidadeEmpregadora = tabelaSegurancaSocial.taxas[0].EntidadeEmpregadadora *VALOR_PER;
        funcionario = tabelaSegurancaSocial.taxas[0].Trabalhador * VALOR_PER;
        global = funcionario + entidadeEmpregadora;
    }
    *impostoSegurancaSocialEmpresa = salarioBruto * entidadeEmpregadora; //Guarda o Valor que a empresa tem de pagar
    return salarioBruto * global;
}

/**
 * Executa o processamento de um salário. Nesta função é calculado o salário bruto, líquido, subsídio de alimentação, retenção de IRS,
 *  taxa para a Segurança Social e despesas totais da empresa  
 * @param func  apontador para os dados de um funcionário
 * @param dados dados para efetuar cálculos (Número de dias trabalhados, faltas, etc)
 * @param tabelaIrs tabela de IRS
 * @param tabelaSS  tabela da Segurança Social
 * @param vencimento apontador que irá guardar os dados resultantes do processamento de salário
 */
void calculoSalario(Funcionario *func, DadosProcessamentoSalario dados, TabelaIrs tabelaIrs, TabelaSegurancaSocial tabelaSS, VencimentoProcessado *vencimento) {
    float vsubsidioAlimentacao, bonus, salarioBruto, irs, segurancaSocial, impostoSegurancaSocialEmpresa, salarioLiquido, encargosTotaisEmpresa;
    vsubsidioAlimentacao = subsidioAlimentacao(dados.nrDiasSemana, dados.nrDiasFimdeSemana, func->subsidioAlimentacao);
    salarioBruto = calculoSalarioBruto(dados.nrDiasSemana, dados.nrDiasFimdeSemana, dados.nrMeiosDias, func->valorHora);
    bonus = calculoBonus(func->dataNascimento, func->dataEntradaEmpresa, dados.nrFaltas, salarioBruto);
    salarioBruto = salarioBruto + bonus;
    irs = calculoRetencaoIrs(tabelaIrs, *func, salarioBruto);
    segurancaSocial = calculoSegurancaSocial(tabelaSS, *func, salarioBruto, &impostoSegurancaSocialEmpresa);
    salarioLiquido = salarioBruto - (irs + segurancaSocial);
    encargosTotaisEmpresa = salarioBruto + vsubsidioAlimentacao + impostoSegurancaSocialEmpresa;
    vencimento->codigoFuncionario = func->codigo;
    vencimento->subsidioAlimentacao = vsubsidioAlimentacao;
    vencimento->bonus = bonus;
    vencimento->segurancaSocial = segurancaSocial;
    vencimento->salarioBruto = salarioBruto;
    vencimento->impostoSegurancaSocialEmpresa = impostoSegurancaSocialEmpresa;
    vencimento->salarioLiquido = salarioLiquido;
    vencimento->encargosTotaisEmpresa = encargosTotaisEmpresa;
    vencimento->retencaoIrs = irs;
}
/**
 * Executa o processamento de salários, caso o código do funcionário exista
 * @param listaDados lista de dados para processamento 
 * @param listaFuncionarios lista de funcionários 
 * @param tabelaIrs tabela de IRS
 * @param tabelaSegurancaSocial tabela da Segurança Social
 * @param listaVencimentosProcessados apontador que irá armazenar os valores dos salários processados
 */
void ProcessamentoSalario(ListaProcessamentos listaDados, ListaFuncionarios listaFuncionarios, TabelaIrs tabelaIrs, TabelaSegurancaSocial tabelaSegurancaSocial,
        ListaVencimentosProcessadosMes *listaVencimentosProcessados) {
    int i;
    printf("%d \n \n", listaDados.numeroSalariosaProcessar);
    for (i = 0; i < listaDados.numeroSalariosaProcessar; i++) {
        Funcionario *func = obterFuncionario(&listaFuncionarios, listaDados.listaProcessamentos[i].codigoFuncionario);
        if (func != NULL) {
            calculoSalario(func, listaDados.listaProcessamentos[i], tabelaIrs, tabelaSegurancaSocial, &listaVencimentosProcessados->lista[listaVencimentosProcessados->salariosProcessados]);
            listaVencimentosProcessados->salariosProcessados++;

        } else {
            listaVencimentosProcessados->salariosNaoProcessados++;
        }
    }
}
/**
 * Imprime na consola o relatório com os vencimentos processados
 * @param listaVencimentosProcessados lista com os vencimentos processados
 */
void imprimirVencimentosProcessados(ListaVencimentosProcessadosMes listaVencimentosProcessados) {
    int i = 0;
    puts("Relatório Vencimentos!");
    printf("NrProcessamentos: %d \n", listaVencimentosProcessados.nrProcessamentos);
    printf("NrProcessamentos_Bem_sucedidos: %d \n", listaVencimentosProcessados.salariosProcessados);
    printf("Nrprocessamentos_Mal_Sucedidos: %d \n", listaVencimentosProcessados.salariosNaoProcessados);
    while (i < listaVencimentosProcessados.salariosProcessados) {
        puts("");
        printf("CFuncionario: %d \nSalárioBruto: %.2f€ \nSalárioLiquído: %.2f€ \nRetençãoIrs: %.2f€ \nBónus: %.2f€ \nSubsidioAlimentação: %.2f€ \nEncargosTotaisEmpresa: %.2f€\nSegurancaSocial: %.2f€ \nSegurancaSocialEmpresa: %.2f€\n", listaVencimentosProcessados.lista[i].codigoFuncionario,
                listaVencimentosProcessados.lista[i].salarioBruto, listaVencimentosProcessados.lista[i].salarioLiquido, listaVencimentosProcessados.lista[i].retencaoIrs, listaVencimentosProcessados.lista[i].bonus, listaVencimentosProcessados.lista[i].subsidioAlimentacao, listaVencimentosProcessados.lista[i].encargosTotaisEmpresa,
                listaVencimentosProcessados.lista[i].segurancaSocial, listaVencimentosProcessados.lista[i].impostoSegurancaSocialEmpresa);
        i++;
    }
}