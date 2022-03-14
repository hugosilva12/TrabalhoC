/**
 * @file TabelaIrs.h
 * @author Hugo Silva
 * @date 25 Novembro 2020
 * @brief Biblioteca criada para gestão da tabela de IRS
 * 
 *  Biblioteca com função de importação da tabela de IRS, escrita da tabela em ficheiro, e operações de gestão (adição, edição e remoção de linhas)
*/
#ifndef TABELA_IRS_H
#define TABELA_IRS_H
#define FILEIRS "Tabelairs.txt"
#include "Funcionario.h"
#define SIZE_TIPO_FUNCIONARIO 200
/** @struct Irs
 * @brief Armazena uma linha da tabela de IRS
 *  @var Irs::ident
 *  'ident' identifica a tabela a que a linha pertence
 *  @var Irs::semDependentes
 *  'semDependentes' taxa sem dependentes
 *  @var Irs::umDependente
 *  'umDependente' taxa um dependente
 *  @var Irs::doisDependentes
 *  'doisDependentes' taxa dois dependentes
 * @var Irs::tresDependentes
 *  'tresDependentes' taxa três dependentes
 * @var Irs::quatroDependentes
 *  'quatroDependentes' taxa quatro dependentes
 * @var Irs::cincoMaisDependentes
 *  'cincoMaisDependentes' taxa cinco ou mais dependentes
 */
typedef struct {
    EstadoCivil ident;
    float nivelSalario;
    float semDependentes;
    float umDependente;
    float doisDependentes;
    float tresDependentes;
    float quatroDependentes;
    float cincoMaisDependentes;
} Irs;
/** @struct TabelaIrs
 * @brief Armazena as três tabelas de IRS
 * @var TabelaIrs::numeroLinhas
 *  'numeroLinhas' número de linhas das três tabelas
 * @var TabelaIrs::tamanho
 *  'tamanho' tamanho da memória alocada para as linhas da tabela
 * @var TabelaIrs::descricaoNivelSalario
 *  'descricaoNivelSalario' descrição coluna nível salarial
 * @var TabelaIrs::descricaoSemDependentes
 *  'descricaoSemDependentes' descrição coluna sem dependentes
 * @var TabelaIrs::descricaoUmDependente
 *  'descricaoUmDependente' descrição coluna um dependente
 * @var TabelaIrs::descricaoDoisDependentes
 *  'descricaoDoisDependentes' descrição coluna dois dependentes
 * @var TabelaIrs::descricaoTresDependentes
 *  'descricaoTresDependentes' descrição coluna três dependentes
 * @var TabelaIrs::descricaoQuatroDependentes
 *  'descricaoQuatroDependentes' descrição coluna quatro dependentes
 * @var TabelaIrs::descricaCincoDependentes
 *  'descricaCincoDependentes' descrição coluna cinco mais dependentes
 * @var TabelaIrs::listaCriterios
 *  'listaCriterios' apontador que para alocar a memória necessária para as linhas 
 * @var TabelaIrs::descricaoEstadoCivil
 *  'descricaoEstadoCivil' descrição coluna do estado civil
 */
typedef struct {
    int numeroLinhas;
    int tamanho;
    char descricaoNivelSalario[SIZE_TIPO_FUNCIONARIO];
    char descricaoSemDependentes[SIZE_TIPO_FUNCIONARIO];
    char descricaoUmDependente[SIZE_TIPO_FUNCIONARIO];
    char descricaoDoisDependentes[SIZE_TIPO_FUNCIONARIO];
    char descricaoTresDependentes[SIZE_TIPO_FUNCIONARIO];
    char descricaoQuatroDependentes[SIZE_TIPO_FUNCIONARIO];
    char descricaCincoDependentes[SIZE_TIPO_FUNCIONARIO];
    char descricaoEstadoCivil[SIZE_TIPO_FUNCIONARIO];
    Irs *listaCriterios;
} TabelaIrs;
void lerFicheiroIrs(TabelaIrs *tabela, char *filename);
void imprimirTodasTabelasIrs(TabelaIrs tabela);
void editarTabelaIRS(TabelaIrs *listaTabelas);
void escreverTabelaFicheiroIRS(TabelaIrs listaTabelas, char *filename); 
void imprimirTabelaNaoCasado(TabelaIrs listaTabelas);
void imprimirTabelaUnicoTitular(TabelaIrs listaTabelas);
void imprimirTabelaDoisTitular(TabelaIrs listaTabelas);
void adicionarNovosCriterios(TabelaIrs *listaTabelas);
void obterNovoCriterioIRS(Irs *irs);
void expandeMemoriaTabelaIrs(TabelaIrs *tabela);
void removerLinhaTabelaIrs(TabelaIrs *listaTabelas);
void libertarMemoriaTabelaIRS(TabelaIrs *tabela);
int obterTabela();
#endif /* TABELA_IRS_H */

