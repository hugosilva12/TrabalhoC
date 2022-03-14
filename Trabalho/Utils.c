/**
 * @file Utils.c
 * @author Hugo Silva
 * @date  3 Janeiro 2021
 * @brief Ficheiro c para implementação das operações diversas
 *
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
/**
 * Função que limpa o Buffer do teclado
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Função que lê da consola um valor float
 * @return  retorna um valor float inserido pelo utilizador 
 */
float obterPercentagem() {
    float perc;
    do {
        puts("Insira nova percentagem ");
        scanf("%f", &perc);
    } while (perc > 100);

    return perc;
}
/**
 * Verifica se um ficheiro existe
 * @param filename nome de um ficheiro
 * @return retorna 1 caso o ficheiro exista, 0 caso o contrário
 */
int verificaExistenciaFicheiro(char*filename) {
    int opcao = 1;
    FILE* verifica;
    verifica = fopen(filename, "r");

    if (verifica == NULL) {
        opcao = 0;
    }
    fclose(verifica);
    return opcao;
}
/**
 * Efetua uma operação que calcula a diferença de anos entre a data atual e uma data passada como parâmetro 
 * @param data  data que irá ser comparada com a data atual
 * @return um valor inteiro que corresponde à diferença de anos
 */
int calcularIdade(Data data) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int idade;

    if (tm->tm_mon + 1 < data.mes) {
        idade = tm->tm_year + 1900 - (data.ano + 1);
    } else if (tm->tm_mon + 1 > data.mes) {
        idade = tm->tm_year + 1900 - data.ano;
    } else {
        if (data.dia < tm->tm_mday) {
            idade = tm->tm_year + 1900 - data.ano;
        } else if (data.dia > tm->tm_mday) {
            idade = tm->tm_year + 1900 - (data.ano + 1);
        } else {
            idade = tm->tm_year + 1900 - data.ano;
        }
    }
    return idade;
}
/**
 * Obtêm o número de linhas de um ficheio, caso ele exista
 * @param filename nome do ficheiro
 * @return o número de linhas que o ficheiro possui
 */
int numeroLinhas(char*filename) {
    char c;
    FILE *file;
    file = fopen(filename, "r");
    int lines = 0;
    if (file != NULL) {
         for (c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n')  
            lines = lines + 1; 
    }
    fclose(file);
    return lines - 1;
}
/**
 * Função que lê da consola a decisão do utilizador, caso exista um relatório de vencimentos em memória
 * @return 0 caso o utilizador pretenda subsituir o relatório, 1 caso o utilizador pretenda visualizar o relatório que já se encontra em memória
 */
int visualizarRelatorioemMemoria() {
    char  aux ;
        do {
            puts("Existe um relatório em memória! \n 1-Visualizar 0-Substituir  ?");
            scanf(" %c", &aux);
            if (aux != '1' && aux != '0') {
                puts("Escolha Invalida");
            }
        } while (aux != '1'&& aux != '0');
        
   if(aux == '1'){
       return 1;
   }    
    return 0;
}
