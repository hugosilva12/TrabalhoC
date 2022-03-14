/**
 * @file Utils.h
 * @author Hugo Silva
 * @date 3 Janeiro 2021
 * @brief Biblioteca para operações diversas
 */

#ifndef UTILS_H
#define UTILS_H
#include "Funcionario.h"
void cleanInputBuffer();
float obterPercentagem();
int numeroLinhas(char*filename); 
int verificaExistenciaFicheiro(char*filename);
int calcularIdade(Data data);
int visualizarRelatorioemMemoria();
#endif /* UTILS_H */

