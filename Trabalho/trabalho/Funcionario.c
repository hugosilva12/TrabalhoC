/**
 * @file Funcionario.c
 * @author Hugo Silva
 * @date  11 Novembro 2020
 * @brief  Ficheiro c que contém a parte privada da biblioteca Funcionario.h
 *  
 * Ficheiro c que contém as funções para criar um funcionário e mostrar os seus dados.Possui também funções de input para obter dados da consola 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionario.h"
#define MSG_DATANASCIMENTO "-------Data Nascimento------"
#define MSG_DATA_ENTRADA_EMPRESA "-------Data Entrada na Empresa------"
#define MSG_DATA_SAIDA_EMPRESA "-------Data Saida da Empresa------"
#define MSG_NOME "Nome do Funcionário"
#include "Utils.h"

/**
 * Função que recebe um valor de uma enumeração e retorna-o em String
 * @param comb  parâmetro que representa um valor da enumeração do Estado Civil 1-NAOCASADO 2-CASADOUNICOTITULAR 3-CASADODOISTITULARES
 * @return  retorna em string o valor que recebeu como parametro
 */
char *estadoCivilToString(EstadoCivil comb) {
    switch (comb) {
        case NAOCASADO:
            return "NAOCASADO";
            break;
        case CASADOUNICOTITULAR:
            return "CASADO";
            break;
        case CASADODOISTITULARES:
            return "CASADODOISTITULARES";
            break;
            return NULL;
    }
}

/**
 * Recebe um valor de uma enumeração  e retorna-o em String
 * @param comb parâmetro que representa um valor da enumeração do Cargo 1-ADMINISTRADOR 2-EMPREGADO 3-CHEFE
 * @return retorna em string o valor que recebeu como parâmetro
 */
char *cargoFuncionarioToString(Cargo comb) {
    switch (comb) {
        case ADMINISTRADOR:
            return "ADMINISTRADOR";
            break;
        case EMPREGADO:
            return "EMPREGADO";
            break;
        case CHEFE:
            return "CHEFE";
            break;
            return NULL;
    }
}

/**
 * Recebe um valor de uma enumeração e retorna-o em String
 * @param comb parâmetro que representa um valor da enumeração do estado do funcionário, 0-Removido, 1-Ativo
 * @return retorna em string o valor que recebeu como parâmetro
 */
char *empregadoAtivoToString(EstadoFuncionario comb) {
    switch (comb) {
        case REMOVIDO:
            return "REMOVIDO";
            break;
        case ATIVO:
            return "ATIVO";
            break;

            return NULL;
    }
}

/**  Imprime na consola as informações de um funcionário 
 * @param func  parâmetro que contém todos os dados referentes a um funcionário.
 */
void mostrarDadosFuncionario(Funcionario func) {
    printf("Código do Funcionário: %d \n", func.codigo);
    printf("Nome do Funcionário:%s", func.nome);
    printf("Data nascimento do Funcionário: %d/%d/%d \n", func.dataNascimento.dia, func.dataNascimento.mes, func.dataNascimento.ano);
    printf("Número de Dependentes: %d\n", func.nrDependentes);
    printf("Número de Telemóvel: %s\n", func.numeroTelemovel);
    printf("Estado Civil: %s\n", estadoCivilToString(func.estadoCivil));
    puts("-----Dados Vida Profissional--------");
    printf("Cargo do Funcionário: %s\n", cargoFuncionarioToString(func.cargoEmpresa));
    printf("Data Entrada Empresa: %d/%d/%d \n", func.dataEntradaEmpresa.dia, func.dataEntradaEmpresa.mes, func.dataEntradaEmpresa.ano);
    if (func.dataSaidaEmpresa.dia != 0) { // Caso tenha data de saída
        printf("Data de saída da empresa: %d/%d/%d \n", func.dataSaidaEmpresa.dia, func.dataSaidaEmpresa.mes, func.dataSaidaEmpresa.ano);
    }
    printf("Valor Subsidio Alimentação: %.2f€\n", func.subsidioAlimentacao);
    printf("Valor por Hora: %.2f€\n", func.valorHora);
    printf("Data de saída da empresa: %d/%d/%d \n", func.dataSaidaEmpresa.dia, func.dataSaidaEmpresa.mes, func.dataSaidaEmpresa.ano);
    if (func.estadoEmpregado == 0) {
        puts("Funcionario REMOVIDO");
    } else {
        printf("Funcionário ATIVO! \n");
    }
    printf("TAXA DE SEGURANÇA SOCIAL a aplicar %d \n", func.criterioSS);

}

/**
 *  Lê da consola uma data
 * @param data  apontador para uma estrutura data que contém três valores inteiros, um é referido ao dia, outro ao mês e outro ao ano.
 * Esta função verifica os dados inseridos pelo utilizador de modo a que os correspondam à realidade.Por exemplo é impossível ao
 * utilizador registar uma data de entrada com o ano 2030, sendo que o ano atual é 2021.
 */
void lerData(Data *data, int AnoMax) {
    int dia, mes, ano, maxDia;
    do {
        puts("Mês: [1-12]");
        scanf("%d", &mes);
        if (mes < 1 || mes > 13) {
            puts("Mês Invalido!,insira de novo!");
        }
    } while (mes < 1 || mes > 13);
    data->mes = mes;
    maxDia = 32; //Dias por mes
    if (data->mes == 2) {
        maxDia = 29;
    } else if (data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 11) {
        maxDia = 31;
    }
    do {
        printf("Dia: [1-%d]", maxDia - 1);
        scanf("%d", &dia);
        if (dia < 1 || dia >= maxDia) {
            puts("Dia Invalido!,insira de novo!");
        }

    } while (dia < 1 || dia >= maxDia);
    data->dia = dia;
    do {
        puts("Ano: ");
        scanf("%d", &ano);
        if (ano < ANO_MIN || ano >= AnoMax) {
            puts("Ano não Aceite! \n!");
        }
    } while (ano < ANO_MIN || ano >= AnoMax);
    data->ano = ano;
}

/**
 * Lê da consola se o estado do funcionário na empresa é ativo ou removido
 * @return retorna 1 caso o funcionário esteja ainda na empresa, 0 caso o mesmo não se verifique
 */
int funcionarioAtivo() {
    char escolha;
    int ativo = 0;
    do {
        puts("Funcionario ativo na empresa? [S-N]");
        scanf(" %c", &escolha);
        if (escolha != 'N' && escolha != 'S') {
            puts("Caracter errado!");
        }
    } while (escolha != 'N' && escolha != 'S');
    if (escolha == 'S') {
        ativo = 1;
    }
    return ativo;
}

/**
 * Função que lê da consola estado civil do funcionário
 * @return retorna 1 caso seja NAO CASADO, retorna 2  caso seja CASADO UNICO TITULAR e retorna 3 caso seja CASADO DOIS TITULARES. 
 * Esta função garante que o estado civil inserido pelo utilizador é válido
 */
int estadoCivil() {
    char opcao = 'N';
    int retorna;

    do {
        puts("Indique o estado civil do funcionario 1.NAOCASADO, 2.CASADO UNICO TITULAR , 3.CASADO DOIS TITULARES");
        scanf(" %c", &opcao);
        if (opcao != '1' && opcao != '2' && opcao != '3') {
            puts("Opção Invalida !");
        }

    } while (opcao != '1' && opcao != '2' && opcao != '3');
    switch (opcao) {
        case '1':
            retorna = 1;
            break;
        case '2':
            retorna = 2;
            break;
        case '3':
            retorna = 3;
            break;
    }
    return retorna;
}

/**
 * Função que lê da consola o cargo do funcionário
 * @return retorna 1 caso seja Chefe, 2 caso seja Administrador e 3 caso seja Empregado
 * 
 */
int cargoFuncionario() {
    char opcao = 'N';
    int retorna;
    do {
        puts("Indique o cargo  do funcionario 1.Chefe 2.Administrador  3.Empregado");
        scanf(" %c", &opcao);
        if (opcao != '1' && opcao != '2' && opcao != '3') {
            puts("Opção Invalida !");
        }
    } while (opcao != '1' && opcao != '2' && opcao != '3');
    switch (opcao) {
        case '1':
            retorna = 1;
            break;
        case '2':
            retorna = 2;
            break;
        case '3':
            retorna = 3;
            break;
    }
    return retorna;
}

/**
 * Função que lê da consola um número de telemóvel válido
 * @param funcionario apontador para uma estrutura funcionário que irá armazenar o número lido da consola
 */
void numeroTelemovel(Funcionario *funcionario) {
    int opcao = 0;
    do {
        puts("Número de Telemóvel");
        fgets(funcionario->numeroTelemovel, TAMANHO_TELEMOVEL, stdin);
        if (strlen(funcionario->numeroTelemovel) == 10 && funcionario->numeroTelemovel[0] == '9') {
            if (funcionario->numeroTelemovel[1] == '0' || funcionario->numeroTelemovel[1] == '1' || funcionario->numeroTelemovel[1] == '2'
                    || funcionario->numeroTelemovel[1] == '6' || funcionario->numeroTelemovel[1] == '3') {
                opcao = 1;
            }
            if (opcao == 0) {
                puts("Número Invalido, por favor repita");
            }
        }
    } while (opcao != 1);
}

/**
 * Lê um funcionário da consola
 * @param funcionário apontador para a estrutura Funcionario que permite armazenar todos os dados de um funcionário
 */
void criarFuncionario(Funcionario *funcionario) {
    puts("Código do Funcionário");
    scanf("%d", &funcionario->codigo);
    puts(MSG_NOME);
    cleanInputBuffer();
    fgets(funcionario->nome, TAMANHO_STRING, stdin);
    puts(MSG_DATANASCIMENTO);
    lerData(&funcionario->dataNascimento, ANO_MAX);
    cleanInputBuffer();
    numeroTelemovel(funcionario);
    puts("Número de Dependentes");
    scanf("%d", &funcionario->nrDependentes);
    puts(MSG_DATA_ENTRADA_EMPRESA);
    lerData(&funcionario->dataEntradaEmpresa, ANO_MAX_ENTRADA);
    puts(MSG_DATA_SAIDA_EMPRESA); //Funcionario esta ativo logo não tem data de saida 
    if (funcionarioAtivo() == 1) {
        funcionario->dataSaidaEmpresa.ano = 0;
        funcionario->dataSaidaEmpresa.mes = 0;
        funcionario->dataSaidaEmpresa.dia = 0;
        funcionario->estadoEmpregado = 1;
    } else {
        lerData(&funcionario->dataSaidaEmpresa, ANO_MAX_ENTRADA);
        funcionario->estadoEmpregado = 0;
    };
    funcionario->estadoCivil = estadoCivil();
    funcionario->cargoEmpresa = cargoFuncionario();
    puts("Valor que recebe por hora!");
    scanf("%f", &funcionario->valorHora);
    puts("Subsidio Alimentaçao");
    scanf("%f", &funcionario->subsidioAlimentacao);
    puts("Critério Segurança Social a aplicar -> [ex: 1 // 2 // 3 // 4]");
    scanf("%d", &funcionario->criterioSS);
}

