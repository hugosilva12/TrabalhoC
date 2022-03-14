/**
 * @file TabelaSegurancaSocial.h
 * @author Hugo Silva
 * @date 22 Novembro 2020
 * @brief Biblioteca criada para gestão da tabela  de Segurança Social
 * 
 *  Biblioteca com função de importação da tabela de Segurança Social, escrita da tabela em ficheiro, e operações de gestão (adição, edição e remoção de linhas)
*/
#ifndef SEGURANCASOCIAFX_H
#define SEGURANCASOCIAFX_H
#define FILE_SEGURANCA_SOCIAL "Tabelaseguranca_social.txt"
#define MAX_DESCRICAO_TABELA 150
#define MAX_TAMANHO 3
/** @struct TaxasSegurancaSocial
 * @brief Armazena uma linha da tabela de Segurança Social
 * @var TaxasSegurancaSocial::descTaxa
 *  'descTaxa' descrição da taxa
 * @var TaxasSegurancaSocial::Trabalhador
 *  'Trabalhador' percentagem da taxa que corresponde ao funcionário
 * @var TaxasSegurancaSocial::EntidadeEmpregadadora
 *  'EntidadeEmpregadadora' percentagem da taxa que à Entidade Empregadora
 * @var TaxasSegurancaSocial::Global
 *  'Global' percentagem global
 * @var TaxasSegurancaSocial::idTaxa
 *  'idTaxa' identificação númerica da taxa
 */
typedef struct  {
    char  descTaxa[MAX_DESCRICAO_TABELA];
    float EntidadeEmpregadadora;
    float Trabalhador;
    float Global;
    int idTaxa;
} TaxasSegurancaSocial;
/** @struct TabelaSegurancaSocial
 * @brief Armazena a tabela de Segurança Social
 * @var TabelaSegurancaSocial::numeroLinhas
 *  'numeroLinhas' número de linhas
 *  @var TabelaSegurancaSocial::tamanho
 *  'tamanho' tamanho da memória alocada para as linhas
 *  @var TabelaSegurancaSocial::idTaxa
 *  'idTaxa' descrição da coluna critério
 *  @var TabelaSegurancaSocial::descricaoTaxa
 *  'descricaoTaxa' descrição coluna da taxa
 * @var TabelaSegurancaSocial::descricaoTrabalhador
 *  'descricaoTrabalhador' descrição coluna do funcionário
 * @var TabelaSegurancaSocial::descricaoGlobal
 *  'descricaoGlobal' descrição coluna global
 * @var TabelaSegurancaSocial::descricaoEntidadeEmpregadora
 *  'descricaoEntidadeEmpregadora' descrição coluna Entidade Empregadora
 */
typedef struct  {
    char  idTaxa[MAX_DESCRICAO_TABELA];
    char  descricaoTaxa[MAX_DESCRICAO_TABELA];
    char  descricaoEntidadeEmpregadora[MAX_DESCRICAO_TABELA];
    char  descricaoTrabalhador[MAX_DESCRICAO_TABELA];
    char  descricaoGlobal[MAX_DESCRICAO_TABELA];
    int numeroLinhas;
    int tamanho;
    TaxasSegurancaSocial *taxas;
} TabelaSegurancaSocial;

void adicionarNovaTaxa(TabelaSegurancaSocial *lista);
void lerFicheiroSegurancaSocial(TabelaSegurancaSocial *lista,char*filename);
void escreverTabelaFicheiro(TabelaSegurancaSocial lista, char *filename) ;
void imprimirTabela(TabelaSegurancaSocial lista);
void editarTaxa(TabelaSegurancaSocial *lista); 
void libertarMemoriaTabelaSS(TabelaSegurancaSocial *tabela);
void removerLinha(TabelaSegurancaSocial *lista);
#endif /* SEGURANCA_SOCIAFX_H */

