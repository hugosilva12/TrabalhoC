
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
void lerStock(Stock *stock, char *nomeFicheiro ){
    
}
void ler(Necessidades *lista, char*filename) {
    int i = 0;
    int numeroLinhasf = numeroLinhas(filename);
    int op;
    int tipoMateriaPrima;
    int quantidade;
    FILE *file;
     char  descricaoEntidadeEmpregadora[100];
    lista->materiaPrima1 = 0;
    lista->materiaPrima2 = 0;
    lista->materiaPrima3 = 0;
    lista->materiaPrima4 = 0;
    lista->materiaPrima5 = 0;
    file = fopen(filename, "r");
    printf("%d",numeroLinhasf);
    if (numeroLinhasf > 0) {
        fscanf(file, "%s");
        while (i < numeroLinhasf) {
            fscanf(file, "%[h,]s,%d,%d", &descricaoEntidadeEmpregadora, &tipoMateriaPrima, &quantidade); 
            i++;
               printf("Necessidades de matéria 1: %s\n",descricaoEntidadeEmpregadora);
        printf("Necessidades de matéria 1: %d\n",tipoMateriaPrima);
         printf("Necessidades de matéria 1: %d\n",quantidade);
              
        }
     
        }else{
            printf("Falhou SS\n");
        }
        fclose(file);

    }

int main() {
      Necessidades  necessidades ;
             printf("Falhou SS\n");
    ler(&necessidades,"ordemProducao1.txt");
    return 0;
}

