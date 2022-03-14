/**
 * @file TabelaIrs.c
 * @author Hugo Silva
 * @date  25 Novembro 2020
 * @brief Ficheiro c para implementação da biblioteca TabelaIrs.h
 * 
 * Ficheiro c onde são implementadas as funções de importação, edição e escrita das tabelas de IRS 
 */
#include <stdio.h>
#include <stdlib.h>
#include "TabelaIrs.h"
#include "Utils.h"
#define MSG_ERRO_READ_FILE "Impossivel abrir o ficheiro!"

/**
 * Liberta a memória alocada para a tabela de IRS
 * @param tabela apontador para a tabela de IRS
 */
void libertarMemoriaTabelaIRS(TabelaIrs *tabela){
    free(tabela->listaCriterios);
}
/**
 * Lê da consola a tabela que o utilizador pretende editar
 * @return 1 caso o utilizador escolha a tabela "NAOCASADO", 2 caso escolha "UNICO TITULAR" e 3 caso escolha "DOISTITULARES" 
 */
int obterTabela(){
  int opcao = 0;
    do {
        puts("Indique a  tabela que pretende editar!1.NAOCASADO, 2.UNICOTITULAR , 3.DOISTITULARES");
        scanf("%d", &opcao);
        if (opcao != 1 && opcao != 2 && opcao != 3) {
            puts("Opção Invalida !");
        }
    } while (opcao != 1 && opcao != 2 && opcao != 3);
    
    return opcao;
}

/**
 * Lê dados de um ficheiro (caso exista) e preenche as tabelas de IRS 
 * @param tabelaIrs apontador para a estrutura que irá armazenar as tabelas, caso a leitura seja realizada
 * @param filename nome do ficheiro que contém as tabelas 
 */
void lerFicheiroIrs(TabelaIrs *tabelaIrs, char *filename) {
    char NomesColunas [70];
    tabelaIrs->numeroLinhas = numeroLinhas(filename);
    FILE *file;
    int i = 0, w = 0,x = 0;
    file = fopen(filename, "r");
    if (file != NULL) {
          tabelaIrs->listaCriterios = (Irs*) malloc (sizeof(Irs) * tabelaIrs->numeroLinhas);
          if(tabelaIrs->listaCriterios != NULL){ //Boa prática verifica
          fgets(NomesColunas,70, file);    //Nomes das colunas    
        while (i < tabelaIrs->numeroLinhas) {
            fscanf(file, "%d,%f,%f,%f,%f,%f,%f,%f", &tabelaIrs->listaCriterios[i].ident, &tabelaIrs->listaCriterios[i].nivelSalario, &tabelaIrs->listaCriterios[i].semDependentes, &tabelaIrs->listaCriterios[i].umDependente, &tabelaIrs->listaCriterios[i].doisDependentes,
                    &tabelaIrs->listaCriterios[i].tresDependentes, &tabelaIrs->listaCriterios[i].quatroDependentes, &tabelaIrs->listaCriterios[i].cincoMaisDependentes);
            i++;
        }
         tabelaIrs->tamanho=tabelaIrs->numeroLinhas;
         // Separação nomes colunas
         while(NomesColunas[w] != ','){
          tabelaIrs->descricaoEstadoCivil[x++]= NomesColunas[w];
           w++;
         }
         tabelaIrs->descricaoEstadoCivil[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoNivelSalario[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoNivelSalario[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoSemDependentes[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoSemDependentes[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoUmDependente[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoUmDependente[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoDoisDependentes[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoDoisDependentes[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoTresDependentes[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoTresDependentes[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != ','){
          tabelaIrs->descricaoQuatroDependentes[x++]= NomesColunas[w];
          w++;
         }
         tabelaIrs->descricaoQuatroDependentes[x] = '\0';
         w++;
         x =0 ;
          while(NomesColunas[w] != '\0'){
              if(NomesColunas[w] != '\n'){
              tabelaIrs->descricaCincoDependentes[x++]= NomesColunas[w];   
              }
          w++;
         }
        tabelaIrs->descricaCincoDependentes[x] = '\0';
       }else{
            printf("Memória Dinámica alocação falhou IRS\n");    
            tabelaIrs->tamanho= 0;
            tabelaIrs->numeroLinhas=0;
       }
    } else {
          tabelaIrs->numeroLinhas=0;
          tabelaIrs->tamanho= 0;
        puts(MSG_ERRO_READ_FILE);
    }
    fclose(file);
}

/**
 * Lista os critérios correspondentes à tabela Não Casados
 * @param listaTabelas estrutura que contém os critérios da tabela de irs
 */
void imprimirTabelaNaoCasado(TabelaIrs listaTabelas) {
    int i = 0;
    puts("----------------Tabela Não Casado------------------------");
     printf("Linha|     %s        %s   %s   %s   %s   %s   %s\n", listaTabelas.descricaoNivelSalario, listaTabelas.descricaoSemDependentes, listaTabelas.descricaoUmDependente, listaTabelas.descricaoDoisDependentes, listaTabelas.descricaoTresDependentes, listaTabelas.descricaoQuatroDependentes, listaTabelas.descricaCincoDependentes);

    while (i < listaTabelas.numeroLinhas) {
        if (listaTabelas.listaCriterios[i].ident == 1) {
            printf("Linha-> %d | Até %.2f€   %.2f   %.2f    %.2f    %.2f   %.2f   %.2f\n", i, listaTabelas.listaCriterios[i].nivelSalario, listaTabelas.listaCriterios[i].semDependentes, listaTabelas.listaCriterios[i].umDependente, listaTabelas.listaCriterios[i].doisDependentes, listaTabelas.listaCriterios[i].tresDependentes, listaTabelas.listaCriterios[i].quatroDependentes,
                    listaTabelas.listaCriterios[i].cincoMaisDependentes);
        }
        i++;
    }
    puts("----------------------------------------------------------------------");
    puts("");
}
/**
 *  Lista os critérios correspondentes à tabela Caso Único Titular 
 * @param listaTabelas estrutura que contém os critérios da tabela de irs
 */
void imprimirTabelaUnicoTitular(TabelaIrs listaTabelas) {
    int i = 0;
    puts("----------------Tabela Unico Titular------------------------");
       printf("Linha|     %s        %s   %s   %s   %s   %s   %s\n", listaTabelas.descricaoNivelSalario, listaTabelas.descricaoSemDependentes, listaTabelas.descricaoUmDependente, listaTabelas.descricaoDoisDependentes, listaTabelas.descricaoTresDependentes, listaTabelas.descricaoQuatroDependentes, listaTabelas.descricaCincoDependentes);
    i = 0;
    while (i < listaTabelas.numeroLinhas) {
        if (listaTabelas.listaCriterios[i].ident == 2) {
            printf("Linha-> %d | Até %.2f€  %.2f  %.2f   %.2f   %.2f  %.2f  %.2f\n", i, listaTabelas.listaCriterios[i].nivelSalario, listaTabelas.listaCriterios[i].semDependentes, listaTabelas.listaCriterios[i].umDependente, listaTabelas.listaCriterios[i].doisDependentes, listaTabelas.listaCriterios[i].tresDependentes, listaTabelas.listaCriterios[i].quatroDependentes,
                    listaTabelas.listaCriterios[i].cincoMaisDependentes);
        }
        i++;
    }
    puts("----------------------------------------------------------------------");
    puts("");
}
/**
 * Lista os critérios correspondentes à tabela Caso Dois Titulares 
 * @param listaTabelas estrutura que contém os critérios da tabela de IRS
 */
void imprimirTabelaDoisTitular(TabelaIrs listaTabelas) {
    int i = 0;
    puts("----------------Tabela Dois Titulares------------------------");
     printf("Linha|     %s        %s   %s   %s   %s  %s  %s\n", listaTabelas.descricaoNivelSalario, listaTabelas.descricaoSemDependentes, listaTabelas.descricaoUmDependente, listaTabelas.descricaoDoisDependentes, listaTabelas.descricaoTresDependentes, listaTabelas.descricaoQuatroDependentes, listaTabelas.descricaCincoDependentes);
    i = 0;
    while (i < listaTabelas.numeroLinhas) {
        if (listaTabelas.listaCriterios[i].ident == 3) {
           printf("Linha-> %d | Até %.2f€  %.2f  %.2f   %.2f   %.2f  %.2f  %.2f\n", i, listaTabelas.listaCriterios[i].nivelSalario, listaTabelas.listaCriterios[i].semDependentes, listaTabelas.listaCriterios[i].umDependente, listaTabelas.listaCriterios[i].doisDependentes, listaTabelas.listaCriterios[i].tresDependentes, listaTabelas.listaCriterios[i].quatroDependentes,
                    listaTabelas.listaCriterios[i].cincoMaisDependentes);
        }
        i++;
    }
    puts("----------------------------------------------------------------------");
    puts("");
}
/**
 * Imprime as três tabelas de IRS
 * @param tabelas lista que contém as três tabelas de IRS  
 */
void imprimirTodasTabelasIrs(TabelaIrs tabelas) {
    imprimirTabelaNaoCasado(tabelas);
    imprimirTabelaUnicoTitular(tabelas);
    imprimirTabelaDoisTitular(tabelas);
}

/**
 * Faz  realocação da memória alocada para os critérios de IRS, duplicando o tamanho atual
 * @param tabela apontador para a tabela de IRS
 */
void expandeMemoriaTabelaIrs(TabelaIrs *tabela){
    Irs *temp = (Irs*) realloc (tabela->listaCriterios, sizeof(Irs) * (tabela->tamanho * 2));
    tabela->tamanho *= 2;
    tabela->listaCriterios = temp;
}
/**
 * Lê da consola dados para criação de uma nova linha para a tabela de IRS
 * @param irs apontador para um critério IRS, que corresponde a uma linha da tabela 
 */
void obterNovoCriterioIRS(Irs *irs){
    puts("Nivel Salarial");
    scanf("%f",&irs->nivelSalario);
    puts("Sem dependentes");
    irs->semDependentes =  obterPercentagem();
    puts("Um dependente");
    irs->umDependente =  obterPercentagem();
    puts("Dois dependentes");
    irs->doisDependentes =  obterPercentagem();
    puts("Três dependentes");
    irs->tresDependentes =  obterPercentagem();
    puts("Quatro dependentes");
    irs->quatroDependentes =  obterPercentagem();
    puts("Cinco ou mais dependentes");
    irs->cincoMaisDependentes =  obterPercentagem();
}
/**
 * Remove uma linha (selecionada pelo utilizador) de uma  tabela de IRS
 * @param tabelaIrs apontador para a estrutura que contém as tabelas de IRS
 */
void removerLinhaTabelaIrs(TabelaIrs *tabelaIrs){
    int linha, aux = 0;
    int tabela = obterTabela();
    switch (tabela) {
        case 1:
            imprimirTabelaNaoCasado(*tabelaIrs);
            break;
        case 2:
            imprimirTabelaUnicoTitular(*tabelaIrs);
            break;
        case 3:
            imprimirTabelaDoisTitular(*tabelaIrs);
            break;
    }
     do {
        puts("Escolha a LINHA que pretende Remover");
        scanf("%d", &linha);
        if (tabelaIrs->listaCriterios[linha].ident == tabela) {
            aux = 1;
        } else {
            puts("Linha NÃO pertence a esta tabela");
        }

    } while (aux == 0);
      tabelaIrs->numeroLinhas--;       
      for(int i = linha; i < tabelaIrs->numeroLinhas ; i++){
        tabelaIrs->listaCriterios[i]=tabelaIrs->listaCriterios[i + 1];
    }   
}

/**
 * Adiciona  nova linha a uma tabela de IRS
 * @param tabelaIrs apontador para a estrutura que contém as tabelas de IRS
 */
void adicionarNovosCriterios(TabelaIrs *tabelaIrs){
    int tabela,i;
    Irs irs;
    if(tabelaIrs ->numeroLinhas == tabelaIrs->tamanho){
        expandeMemoriaTabelaIrs(tabelaIrs);
    }
    tabela = obterTabela();
    irs.ident=tabela;
    obterNovoCriterioIRS(&irs); //Cria o critério
    for( i = 0; i < tabelaIrs ->numeroLinhas; i++){ //Tabela na qual será inserido
        if(irs.ident == tabelaIrs->listaCriterios[i].ident && irs.nivelSalario < tabelaIrs->listaCriterios[i].nivelSalario){
            break;
        }
    }
    if(i == tabelaIrs->numeroLinhas ){
         for( i = 0; i < tabelaIrs ->numeroLinhas; i++){
             if(tabelaIrs->listaCriterios[i].ident == irs.ident && tabelaIrs->listaCriterios[i].ident != tabelaIrs->listaCriterios[i+1].ident){
                 i++;
                 break;
             }
         }
    }
    tabelaIrs->numeroLinhas++;
    for(int j = tabelaIrs ->numeroLinhas; j > i; j-- ){
        tabelaIrs->listaCriterios[j]= tabelaIrs->listaCriterios[j-1];
    }
    tabelaIrs->listaCriterios[i]= irs;
}
/**
 *  Escreve as três tabelas de IRS num ficheiro, caso seja possível
 * @param tabelas tabelas de IRS
 * @param filename nome do ficheiro no qual os tabelas serão escritas
 */
void escreverTabelaFicheiroIRS(TabelaIrs tabelas, char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    int i = 0;
    if (file != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s\n", tabelas.descricaoEstadoCivil, tabelas.descricaoNivelSalario, tabelas.descricaoSemDependentes,
                tabelas.descricaoUmDependente, tabelas.descricaoDoisDependentes,
                tabelas.descricaoTresDependentes, tabelas.descricaoQuatroDependentes, tabelas.descricaCincoDependentes);

        while (i < tabelas.numeroLinhas) {
            fprintf(file, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", tabelas.listaCriterios[i].ident, tabelas.listaCriterios[i].nivelSalario, tabelas.listaCriterios[i].semDependentes, tabelas.listaCriterios[i].umDependente, tabelas.listaCriterios[i].doisDependentes,
                    tabelas.listaCriterios[i].tresDependentes, tabelas.listaCriterios[i].quatroDependentes, tabelas.listaCriterios[i].cincoMaisDependentes);
            i++;
        }

    } else {
        puts(MSG_ERRO_READ_FILE);
    }
  fclose(file);  
}
/**
 * Lê um float da consola  
 * @param min valor mínimo
 * @param max valor máximo
 * @return um valor compreendido entre o mínimo e o máximo que são passados como parâmetro 
 */
float obterValorFloat(float min, float max) {
    float salario;
    do {
        printf("Indique o nivel de SALARIO [%f - %f]",min,max);
        scanf("%d", &salario);
        if (salario < min || salario > max) {
            puts("Salario FORA do limite");
        }
    } while (salario < min || salario > max);
    
    return salario;
}
/**
 * Função que edita uma linha da tabela de IRS 
 * @param tabela apontador para as tabelas de IRS 
 */
void editarTabelaIRS(TabelaIrs *tabela) {
    int opcao = 0, linha, aux = 0;
    float maxSalario, minSalario;
    //Escolhe a tabela
    opcao = obterTabela();
    switch (opcao) {
        case 1:
            imprimirTabelaNaoCasado(*tabela);
            break;
        case 2:
            imprimirTabelaUnicoTitular(*tabela);
            break;
        case 3:
            imprimirTabelaDoisTitular(*tabela);
            break;
    }
    //Escolhe a linha a editar
    do {
        puts("Escolha a LINHA que pretende editar");
        scanf("%d", &linha);
        if (tabela->listaCriterios[linha].ident == opcao) {
            aux = 1;
        } else {
            puts("Linha NÃO pertence a esta tabela");
        }

    } while (aux == 0);
    ///obtem intervalo de valores para nivel salario
    if (linha == 0) {
        minSalario = 0;
        maxSalario = tabela->listaCriterios[linha + 1].nivelSalario;
    } else if (linha == tabela->numeroLinhas) {
        minSalario = tabela->listaCriterios[linha - 1].nivelSalario;
        maxSalario = tabela->listaCriterios[linha].nivelSalario * 2;
    } else if (tabela->listaCriterios[linha - 1].ident == opcao && tabela->listaCriterios[linha + 1].ident == opcao) {
        //Todas as linhas pertencem à mesma tabela
        minSalario = tabela->listaCriterios[linha - 1].nivelSalario;
        maxSalario = tabela->listaCriterios[linha + 1].nivelSalario;
    } else if (tabela->listaCriterios[linha - 1].ident != opcao && tabela->listaCriterios[linha + 1].ident == opcao) {
        minSalario = 0;
        maxSalario = tabela->listaCriterios[linha + 1].nivelSalario;
    } else if (tabela->listaCriterios[linha - 1].ident == opcao && tabela->listaCriterios[linha + 1].ident != opcao) {
        minSalario = tabela->listaCriterios[linha - 1].nivelSalario;
        maxSalario = tabela->listaCriterios[linha].nivelSalario * 2;
    }
    do {
        puts("Edição IRS");
        puts("----------------------------");
        puts("1. Percentagem SEM Dependentes");
        puts("2. Percentagem UM Dependentes");
        puts("3. Percentagem DOIS Dependentes");
        puts("4. Percentagem TRES Dependentes");
        puts("5. Percentagem QUATRO Dependentes");
        puts("6. Percentagem CINCO OU MAIS Dependentes");
        puts("7. NIVEL de Salario");
        puts("0. Concluir");
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                break;
            case 1:
                tabela->listaCriterios[linha].semDependentes = obterPercentagem();
                break;
            case 2:
                tabela->listaCriterios[linha].umDependente = obterPercentagem();
                break;
            case 3:
                tabela->listaCriterios[linha].doisDependentes = obterPercentagem();
                break;
            case 4:
                tabela->listaCriterios[linha].tresDependentes = obterPercentagem();
                break;
            case 5:
                tabela->listaCriterios[linha].quatroDependentes = obterPercentagem();
                break;
            case 6:
                tabela->listaCriterios[linha].cincoMaisDependentes = obterPercentagem();
                break;
            case 7:
                tabela->listaCriterios[linha].ident = obterValorFloat(minSalario, maxSalario);
                break;
            default:
                puts("Invalida");
                break;
        }
    } while (opcao != 0);
}