/**
 * @file GestaoFuncionarios.c
 * @author Hugo Silva
 * @date  13 Novembro 2020
 * @brief Implementação das funções da biblioteca GestaoFuncionarios.h (Parte privada)
 * 
 * Ficheiro c que contém a implementação das funções de gestão da lista de funcionários, adição, remoção e edição
 */
#include <stdio.h>
#include <stdlib.h>
#include "GestaoFuncionarios.h"
#include "Funcionario.h"
#include "Menus.h"

/**
 * Faz  realocação da memória, duplicando o tamanho atual
 * @param listafuncionarios apontador para lista de funcionários
 */
void expandirMemoria(ListaFuncionarios *listafuncionarios){
    Funcionario *func = (Funcionario*) realloc(listafuncionarios->listafuncionarios, sizeof(Funcionario) * (listafuncionarios->tamanho * 2));
    listafuncionarios->listafuncionarios= func;
    listafuncionarios->tamanho *= 2;
    
}
/**
 * Liberta a memória alocada para a lista de funcionários
 * @param listafuncionarios apontador para lista de funcionários
 */
void libertarMemoriaFuncionarios(ListaFuncionarios *listafuncionarios){
    free(listafuncionarios->listafuncionarios);
}

/**
 * Faz uma alocação de memória incial de acordo com TAMANHO_MAX
 * @param lista apontador para a lista de funcionários
 */
void funcaoAlocarMemoria(ListaFuncionarios *lista){
    lista->listafuncionarios = (Funcionario*) malloc (TAMANHO_MAX * sizeof(Funcionario));
    lista->listafuncionarios == NULL ? puts("Erro na alocação de memória"): printf("Memória  Lista Funciónarios Alocada com sucesso! \n"); 
    lista->tamanho= TAMANHO_MAX;
    lista->nrFuncionarios=0;    
}
/**
 * Imprime a lista de funcionários
 * @param listafuncionarios lista de funcionários
 *  Caso a lista esteja vazia informa o utilizador
 */
void listarTodosFuncionarios(ListaFuncionarios *listafuncionarios) {
    if (listafuncionarios->nrFuncionarios == 0) {
        puts("Lista Vazia!");
    } else {
        for (int i = 0; i < listafuncionarios->nrFuncionarios; i++) {
            puts("");
            printf("Funcionario nª %d\n", i);
            mostrarDadosFuncionario(listafuncionarios->listafuncionarios[i]);
        }
    }
}
/**
 * Adiciona um funcionário à lista  de funcionários, se possivel
 * @param listafuncionarios apontador para uma lista de funcionários
 * @return 1 se o funcionário foi adicionado com sucesso / 0  funcionário não inserido (Código do funcionário já existe na lista)
 * 
 */
int adicionarFuncionario(ListaFuncionarios *listafuncionarios) {
    Funcionario func;
    criarFuncionario(&func);
    //verifica se  código já existe 
    for (int i = 0; i < listafuncionarios->nrFuncionarios; i++) {
        if (listafuncionarios->listafuncionarios[i].codigo == func.codigo) {
            return 0;
        }
    }
    //lista cheia
    if (listafuncionarios->nrFuncionarios == listafuncionarios->tamanho) {
        expandirMemoria(listafuncionarios);
    }
    //Possivel a insercao, adiciona e incrimenta o nr de funcionários
    listafuncionarios->listafuncionarios[listafuncionarios->nrFuncionarios] = func;
    listafuncionarios->nrFuncionarios++;
    return 1;
}
/**
 * Devolve a posição em que ocorre um funcionário com um determinado código
 * @param listafuncionarios apontador para lista de funcionários
 * @param idFunc  identificador do funcionários a pesquisar
 * @return  Índice do funcionário se existir, -1 caso contrário 
 */
int obterIndiceFuncionario(ListaFuncionarios *listafuncionarios, int idFunc) {
    int i = 0;

    while (i < listafuncionarios->nrFuncionarios && listafuncionarios->listafuncionarios[i].codigo != idFunc){
         i++;
    }
    if (i == listafuncionarios->nrFuncionarios) { //Chegou ao fim da lista não encontrou
        return -1;
    }
   return i;  
}
/**
 * Atualiza um funcionário, se existir
 * @param listafuncionarios apontador para lista de funcionários
 * @param idFunc identificador do funcionário a editar
 */
void atualizaFuncionario(ListaFuncionarios *listafuncionarios, int idFunc) {
    Funcionario *fun;
    fun = obterFuncionario(listafuncionarios, idFunc);
    if (fun != NULL) {
        menuEditarFuncionario(fun);
    } else {
        puts(MSG_NAO_ENCONTRADO);
    }
}
/**
 * Mostra dados de um funcionário, se existir
 * @param listafuncionarios lista de funcionários
 * @param idFunc código do funcionário a mostrar
 */
void mostraFuncionario(ListaFuncionarios *listafuncionarios, int idFunc) {
    Funcionario *fun;
    fun = obterFuncionario(listafuncionarios, idFunc);
    if (fun != NULL) {
       mostrarDadosFuncionario(*fun);
    } else {
        puts(MSG_NAO_ENCONTRADO);
    }
}
/**
 * Devolve um apontador para um funcionário, se existir
 * @param listafuncionarios lista de funcionários
 * @param idFunc código do funcionário a obter
 * @return apontador para o funcionário, se existir, -1 caso o contrário
 */
Funcionario* obterFuncionario(ListaFuncionarios *listafuncionarios, int idFunc) {
    int pos = obterIndiceFuncionario(listafuncionarios, idFunc);

    if (pos == -1) {
        return NULL;
    } else {
        return &listafuncionarios->listafuncionarios[pos];
    }
}
/**
 * Função que remove funcionário, se existir 
 * @param listafuncionarios apontador lista de funcionarios
 * @param idFunc código do funcionário a remover
 * Nesta função o funcionário não é removido da lista, apenas o atributo estadoEmpregado passa a "Removido". Caso o código não exista, informa
 */
void apagarFuncionario(ListaFuncionarios *listafuncionarios, int idFunc) {
  int pos =  obterIndiceFuncionario(listafuncionarios,idFunc);
    //Funcionario *funcionario = obterFuncionario(listafuncionarios, idFunc);
    if (pos!= -1) {
        //ESTADO passa REMOVIDO, 
        for(int i = pos; pos < listafuncionarios->nrFuncionarios-1; i++){
          // listafuncionarios->nrFuncionarios[i]= listafuncionarios->nrFuncionarios[i+1];
        }
        //listafuncionarios->listafuncionarios[listafuncionarios->nrFuncionarios]=NULL;
        listafuncionarios->nrFuncionarios--;
        //funcionario->estadoEmpregado = 0;
        puts(MSG_REMOVIDO_SUCESS);
    } else {
        puts(MSG_NAO_ENCONTRADO);
    }
}
