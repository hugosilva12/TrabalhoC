/**
 * @file ProcessamentoSalario.h
 * @author Hugo Silva
 * @date 25 Novembro 2020
 * @brief Biblioteca criada para a funcionalidade de processamento de salário
 * 
 *  Biblioteca com a função de Log do projeto
 */
#ifndef PROCESSAMENTO_SALARIO_H
#define PROCESSAMENTO_SALARIO_H
#define TAMANHODESC 30
#include "TabelaSegurancaSocial.h"
#include "TabelaIrs.h"
#include "GestaoFuncionarios.h"
#define NOME_FICHEIROIMP_JAN "i_janeiro.txt"
#define NOME_FICHEIROIMP_FEV "i_fevereiro.txt"
#define NOME_FICHEIROIMP_MAR "i_março.txt"
#define NOME_FICHEIROIMP_ABR "i_abril.txt"
#define NOME_FICHEIROIMP_MAI "i_maio.txt"
#define NOME_FICHEIROIMP_JUN "i_junho.txt"
#define NOME_FICHEIROIMP_JUL "i_julho.txt"
#define NOME_FICHEIROIMP_AGO "i_agosto.txt"
#define NOME_FICHEIROIMP_SET "i_setembro.txt"
#define NOME_FICHEIROIMP_OUT "i_outubro.txt"
#define NOME_FICHEIROIMP_NOV "i_novembro.txt"
#define NOME_FICHEIROIMP_DEZ "i_dezembro.txt"
#define NOME_RELATORIO_JAN "relatorio_janeiro.txt"
#define NOME_RELATORIO_FEV "relatorio_fevereiro.txt"
#define NOME_RELATORIO_MAR "relatorio_março.txt"
#define NOME_RELATORIO_ABR "relatorio_abril.txt"
#define NOME_RELATORIO_MAI "relatorio_maio.txt"
#define NOME_RELATORIO_JUN "relatorio_junho.txt"
#define NOME_RELATORIO_JUL "relatorio_julho.txt"
#define NOME_RELATORIO_AGO "relatorio_agosto.txt"
#define NOME_RELATORIO_SET "relatorio_setembro.txt"
#define NOME_RELATORIO_OUT "relatorio_outubro.txt"
#define NOME_RELATORIO_NOV "relatorio_novembro.txt"
#define NOME_RELATORIO_DEZ "relatorio_dezembro.txt"
#define  TAMANHO_MIN_PROCESSAMENTOS 2
/** @struct DadosProcessamentoSalario
 * @brief Armazena dados de um funcionário para processamento de salário
 *  @var DadosProcessamentoSalario::codigoFuncionario
 *  'codigoFuncionario' código do funcionário
 *  @var DadosProcessamentoSalario::nrDiasSemana
 *  'nrDiasSemana' número de dias que trabalhou durante a semana
 *  @var DadosProcessamentoSalario::nrMeiosDias
 *  'nrMeiosDias' número de 1/2dias que trabalhou 
 *  @var DadosProcessamentoSalario::nrDiasFimdeSemana
 *  'nrDiasFimdeSemana' número de dias que trabalhou durante o fim de semana
 *  @var DadosProcessamentoSalario::nrFaltas
 *  'nrFaltas' número de dias que faltou
 */
typedef struct {
    int codigoFuncionario; //Unico
    int nrDiasSemana;
    int nrMeiosDias;
    int nrDiasFimdeSemana;
    int nrFaltas;
} DadosProcessamentoSalario;
/** @struct ListaProcessamentos
 * @brief Armazena uma lista de dados para processamento de salários
 * @var ListaProcessamentos::numeroSalariosaProcessar
 *  'numeroSalariosaProcessar' número de salários a processar
 * @var ListaProcessamentos::listaProcessamentos
 *  'listaProcessamentos' armazena a lista de processamentos
 */
typedef struct{
    int numeroSalariosaProcessar;
    DadosProcessamentoSalario *listaProcessamentos;
} ListaProcessamentos;

/** @struct VencimentoProcessado
 * @brief Armazena dados resultantes do processamento de um salário
 *  @var VencimentoProcessado::codigoFuncionario
 *  'codigoFuncionario' código do funcionário
 *  @var VencimentoProcessado::salarioLiquido
 *  'salarioLiquido' salário liquído
 *  @var VencimentoProcessado::salarioBruto
 *  'salarioBruto' salário bruto
 * @var VencimentoProcessado::descFaltas
 *  'subsidioAlimentacao' subsídio de alimentação
 * @var VencimentoProcessado::bonus
 *  'bonus' bónus resultante da idade,tempo na empresa e número de faltas
 * @var VencimentoProcessado::retencaoIrs
 *  'retencaoIrs' valor da retenção de IRS
 * @var VencimentoProcessado::encargosTotaisEmpresa
 *  'encargosTotaisEmpresa' valor dos encargos totais da empresa
 * @var VencimentoProcessado::impostoSegurancaSocialEmpresa
 *  'impostoSegurancaSocialEmpresa' valor da taxa de Segurança Social pago pela empresa
 * @var VencimentoProcessado::segurancaSocial
 *  'segurancaSocial' valor da taxa de Segurança Social
 * @var VencimentoProcessado::subsidioAlimentacao
 *  'subsidioAlimentacao' valor do subsídio de alimentação
 */
typedef struct {
    int codigoFuncionario;
    float salarioLiquido; 
    float salarioBruto;
    float subsidioAlimentacao;
    float bonus;
    float retencaoIrs;
    float segurancaSocial;
    float impostoSegurancaSocialEmpresa;
    float encargosTotaisEmpresa;
} VencimentoProcessado;

/** @struct ListaVencimentosProcessadosMes
 * @brief Armazena uma lista de salários processados num mês
 * @var ListaVencimentosProcessadosMes::nrProcessamentos
 *  'nrProcessamentos' número de processamentos realizados
 * @var ListaVencimentosProcessadosMes::salariosProcessados
 *  'salariosProcessados' número de salários processados
 * @var ListaVencimentosProcessadosMes::salariosNaoProcessados
 *  'salariosNaoProcessados' número de salários não processados
 * @var ListaVencimentosProcessadosMes::lista
 *  'lista' apontador para a estrutura VencimentoProcessado que armazena as informações dos salários processados
 */
typedef struct{
    char nomeRelatorio[TAMANHODESC];
    int nrProcessamentos;
    int salariosProcessados;
    int salariosNaoProcessados;
    VencimentoProcessado *lista;
}ListaVencimentosProcessadosMes;
/** @struct ListaTodosVencimentosProcessados
 * @brief Armazena um conjuntos de meses com salários processados
 *  @var ListaTodosVencimentosProcessados::nrMesesProcessados
 *  'nrMesesProcessados' número de meses processados
 * @var ListaTodosVencimentosProcessados::janeiro
 *  'janeiro' armazena relatório de janeiro
 *  @var ListaTodosVencimentosProcessados::fevereiro
 *  'fevereiro'armazena relatório de fevereiro
 *  @var ListaTodosVencimentosProcessados::marco
 *  'marco'armazena relatório de março
 *  @var ListaTodosVencimentosProcessados::abril
 *  'abril' armazena relatório de abril
 * @var ListaTodosVencimentosProcessados::maio
 *  'maio' armazena relatório de maio
 * @var ListaTodosVencimentosProcessados::junho
 *  'junho' armazena relatório de junho
 * @var ListaTodosVencimentosProcessados::julho
 *  'julho' armazena relatório de julho
 * @var ListaTodosVencimentosProcessados::agosto
 *  'agosto' armazena relatório de agosto
 * @var ListaTodosVencimentosProcessados::outubro
 *  'outubro' armazena relatório de outubro
 * @var ListaTodosVencimentosProcessados::novembro
 *  'novembro' armazena relatório de novembro
 * @var ListaTodosVencimentosProcessados::setembro
 *  'setembro' armazena relatório de setembro
 *  @var ListaTodosVencimentosProcessados::dezembro
 *  'dezembro' armazena relatório de dezembro
 */
typedef struct{
    ListaVencimentosProcessadosMes janeiro;
    ListaVencimentosProcessadosMes fevereiro;
    ListaVencimentosProcessadosMes marco;
    ListaVencimentosProcessadosMes abril;
    ListaVencimentosProcessadosMes maio;
    ListaVencimentosProcessadosMes junho;
    ListaVencimentosProcessadosMes julho;
    ListaVencimentosProcessadosMes agosto;
    ListaVencimentosProcessadosMes setembro;
    ListaVencimentosProcessadosMes outubro;
    ListaVencimentosProcessadosMes novembro;
    ListaVencimentosProcessadosMes dezembro;
    int nrMesesProcessados;
}ListaTodosVencimentosProcessados;
float subsidioAlimentacao(int descNrDiasSemana, int descNrDiasFimSemana, float subsidio);
float calculoSalarioBruto(int descNrDiasSemana,int descNrDiasFimSemana,int nrMeiosDias , float valorHora);
float calculoBonus(Data dataNascimento, Data dataEntrada, int numeroFaltas, float salarioBruto);
float calculoRetencaoIrs(TabelaIrs tabelaIrs, Funcionario func, float salarioBruto);
void ProcessamentoSalario(ListaProcessamentos listaDados, ListaFuncionarios listaFuncionarios, TabelaIrs tabelaIrs, TabelaSegurancaSocial tabelaSegurancaSocial,
        ListaVencimentosProcessadosMes *listaVencimentosProcessados);
void imprimirVencimentosProcessados(ListaVencimentosProcessadosMes listaVencimentosProcessados);


#endif /* PROCESSAMENTO_SALARIO_H */

