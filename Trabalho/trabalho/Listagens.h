/**
 * @file Listagens.h
 * @author Hugo Silva
 * @date  3 Janeiro 2021
 * @brief Biblioteca com as estruturas de dados e funções utilizadas para listagens propostas pelo grupo
 *
 */
#ifndef DADOSESTATISTICOS_H
#define DADOSESTATISTICOS_H
#define FILENAME_PERCENTAGEMIDADES "ListagempercentagemIdade.txt"
#define FILENAME_PERCENTAGEMANOSEMPRESA "ListagempercentagemAnosEmpresa.txt"
#define FILENAME_DESPESASTOTAIS "ListagemDespesasTotais.txt"
#define FILENAME_RELATORIOFALTAS "ListagemGestaoFaltas.txt"
#define FILENAME_RELATORIOVALORH "ListagemrelatoriValorHora.txt"
#define FILENAME_RELATORIOESTADOCIVIL "ListagemEstadocivil.txt"
#define TAMANHOCODIGOS 3
/*! Enumeração que representa se um relatório exitem em memória*/
typedef enum {
   RelatorioNaoGerado = 0,/*!< Relatório não existe em memória */
RelatorioFoiGerado = 1 /*!< Relatório existe em memória*/
} RelatorioGerado;
/** @struct PercentagemIdades
 * @brief Armazena  a percentagem de funcionários por intervalos de idade
 * @var PercentagemIdades::funcionariosAnalisados
 *  'funcionariosAnalisados' número de funcionários da lista
 * @var PercentagemIdades::percentagemMenos26
 *  'percentagemMenos26' percentagem de funcionários com menos de 26 anos
 * @var PercentagemIdades::percentagemEntre31e40
 *  'percentagemEntre31e40' percentagem de funcionários com idade entre 31 e 40 anos
 * @var PercentagemIdades::percentagemEntre41e50
 *  'percentagemEntre41e50' percentagem de funcionários com idade entre 41 e 50 anos
 * @var PercentagemIdades::percentagemEntre26e30
 *  'percentagemEntre26e30' percentagem de funcionários com idade entre 26 e 30 anos
 * @var PercentagemIdades::percentagemEntre51e60
 *  'percentagemEntre51e60' percentagem de funcionários com idade entre 51 e 60 anos
 * @var PercentagemIdades::percentagemMais60
 *  'percentagemMais60' percentagem de funcionários com mais de 60 anos
 * @var PercentagemIdades::funcionariosSemBonus
 *  'funcionariosSemBonus'número de funcionários sem bónus pela idade
 * @var PercentagemIdades::funcionariosComBonus
 *  'funcionariosComBonus' número de funcionários com bónus pela idade
 */
typedef struct {
    int funcionariosAnalisados;
    float percentagemMenos26;
    float percentagemEntre26e30;
    float percentagemEntre31e40;    
    float percentagemEntre41e50;
    float percentagemEntre51e60;
    float percentagemMais60;
    int funcionariosComBonus;
    int funcionariosSemBonus;
} PercentagemIdades;
/** @struct PercentagemTempoEmpresa
 * @brief Armazena  a percentagem de funcionários por anos na empresa
 * @var PercentagemTempoEmpresa::funcionariosAnalisados
 *  'funcionariosAnalisados' número de funcionários da lista
 *  @var PercentagemTempoEmpresa::funcionariosSemBonus
 *  'funcionariosSemBonus'número de funcionários sem bónus por anos na empresa
 * @var PercentagemTempoEmpresa::percentagemMenos5
 *  'percentagemMenos5' percentagem de funcionários com menos de 5 anos
 *  @var PercentagemTempoEmpresa::percentagemEntre5e10
 *  'percentagemEntre5e10' percentagem de funcionário entre 5 e 10 anos
 * @var PercentagemTempoEmpresa::percentagemEntre11e20
 *  'percentagemEntre11e20' percentagem de funcionário entre 11 e 20 anos
 * @var PercentagemTempoEmpresa::percentagemMais20
 *  'percentagemMais20' percentagem de funcionários com mais de 20 anos na empresa
 */
typedef struct {
    int funcionariosAnalisados;
    float percentagemMenos5;
    float percentagemEntre5e10;
    float percentagemEntre11e20;    
    float percentagemMais20;
    int funcionariosComBonus;
    int funcionariosSemBonus;
} PercentagemTempoEmpresa;
/** @struct DespesaMes
 * @brief Armazena a despesa total de um mês
 * @var DespesaMes::salariosProcessados
 *  'salariosProcessados'número de salários processados
 * @var DespesaMes::despesaTotal
 *  'despesaTotal' despesa total de um mês
 */
typedef struct {
    int salariosProcessados;
    float despesaTotal;
} DespesaMes;
/** @struct DespesasAnuais
 * @brief Armazena a despesa de todos os meses processados
 */
typedef struct {
    DespesaMes meses[12]; //Caso estático, serão sempre analisados os 12 meses
    float despesaTotal;
    RelatorioGerado estadoRelatorio;
} DespesasAnuais;
/** @struct gestaoFaltasMes
 * @brief Armazena os funcionários pelo seu número de faltas num mês
 * @var gestaoFaltasMes::tamanhoSemfaltas
 *  'tamanhoSemfaltas' tamanho da lista sem faltas
 * @var gestaoFaltasMes::nrFuncionariosAnalisados
 *  'nrFuncionariosAnalisados' número de funcionários analisados
 * @var gestaoFaltasMes::tamanhoUmafaltas
 *  'tamanhoUmafaltas' tamanho da lista de funcionários com uma falta
 * @var gestaoFaltasMes::tamanhoDuasouTresFaltas
 *  'tamanhoDuasouTresFaltas' tamanho da lista de funcionários com  2 ou 3 faltas
 * @var gestaoFaltasMes::tamanhoMaisTresFaltas
 *  'tamanhoMaisTresFaltas' tamanho da lista de funcionários com mais de 3 faltas
 * @var gestaoFaltasMes::nrSemfaltas
 *  'nrSemfaltas' número de funcionários sem faltas
 * @var gestaoFaltasMes::nrUmafaltas
 *  'nrUmafaltas' número de funcionários com uma falta
 * @var gestaoFaltasMes::nrDuasouTresFaltas
 *  'nrDuasouTresFaltas' número de funcionários com 2 ou 3 faltas
 * @var gestaoFaltasMes::nrMaisTresFaltas
 *  'nrMaisTresFaltas' número de funcionários com mais de 3 faltas
 * @var gestaoFaltasMes::Semfaltas
 *  'Semfaltas' apontador para a lista de funcionários sem faltas
 * @var gestaoFaltasMes::Umafaltas
 *  'Umafaltas' apontador para a lista de funcionários com 1 falta
 * @var gestaoFaltasMes::DuasouTresFaltas
 *  'DuasouTresFaltas' apontador para a lista de funcionários com 2/3 faltas
 * @var gestaoFaltasMes::MaisTresFaltas
 *  'MaisTresFaltas' apontador para a lista de funcionários com mais de 3 faltas
 */
typedef struct {
    int tamanhoSemfaltas;
    int tamanhoUmafaltas;
    int tamanhoDuasouTresFaltas;
    int tamanhoMaisTresFaltas;
    int nrSemfaltas;
    int nrUmafaltas;
    int nrMaisTresFaltas;
    int nrDuasouTresFaltas;
    int *Semfaltas;
    int *Umafaltas;
    int *DuasouTresFaltas;
    int *MaisTresFaltas;
    int nrFuncionariosAnalisados;
} gestaoFaltasMes;
/** @struct RelatorioFaltas
 * @brief Armazena a listagem de funcionários por faltas (Todos os meses)
 * @var RelatorioFaltas::lista
 *  'lista' array que corresponde aos 12 meses do ano
 * @var RelatorioFaltas::estadoRelatorio
 *  'estadoRelatorio' estado do relatório
 */
typedef struct {
   gestaoFaltasMes lista[12]; //Caso estático, serão sempre analisados os 12 meses
   RelatorioGerado estadoRelatorio;
} RelatorioFaltas;
/** @struct RelatorioValorHora
 * @brief Armazena o valor minímo, máximo e médio pago por hora
 *  @var RelatorioValorHora::valorMaximoHora
 *  'valorMaximoHora' valor mais alto que um funcionário recebe
 *  @var RelatorioValorHora::valorMinimoHora
 *  'valorMinimoHora' valor mais baixo que um funcionário recebe
 *  @var RelatorioValorHora::diferenca
 *  'diferenca' diferença entre o máximo e o minímo
 *  @var RelatorioValorHora::valorMedio
 *  'valorMedio' valor médio de todos os funcionários
 * @var RelatorioValorHora::estadoRelatorio
 *  'estadoRelatorio' estado do relatório
 */
typedef struct {
   float valorMaximoHora; 
   float valorMinimoHora; 
   float valorMedio;
   float diferenca;
   RelatorioGerado estadoRelatorio;
} RelatorioValorHora;
/** @struct PercentagemEstadoCivil
 * @brief Armazena a percentagem de funcionários por estado civil
 *  @var PercentagemEstadoCivil::percNaoCasado
 *  'percNaoCasado' percentagem de funcionários não casados
 *  @var PercentagemEstadoCivil::percCasadoUnicoTitular
 *  'percCasadoUnicoTitular' percentagem de funcionários casados com único titular
 *  @var PercentagemEstadoCivil::percCasadoDoisTitulares
 *  'percCasadoDoisTitulares' percentagem de funcionários casados com dois titulares
 *  @var PercentagemEstadoCivil::estadoRelatorio
 *  'estadoRelatorio' estado do relatório
 */ 
typedef struct {
   float percNaoCasado; 
   float percCasadoUnicoTitular; 
   float percCasadoDoisTitulares;
   RelatorioGerado estadoRelatorio;
} PercentagemEstadoCivil;
void expandirMemoriaFaltas(int *gestao, int *tamanho);
void despesaTotalEmpresaPorMes(ListaVencimentosProcessadosMes lista, float *valor_total, int *salariosProcessados);
void percentagemIdadesFuncionarios(ListaFuncionarios lista, PercentagemIdades *percentagens);
void percentagemTempoEmpresa(ListaFuncionarios lista, PercentagemTempoEmpresa *percentagem);
void listagemFuncionariosPorFaltas(RelatorioFaltas *gestaofaltas);
void DespesasTotais(DespesasAnuais *despesas);
void relatorioValorHora(ListaFuncionarios lista, RelatorioValorHora *relatorio);
void relatorioPercentagemEstadoCivil(ListaFuncionarios lista, PercentagemEstadoCivil *relatorio);
void imprimirPercentagemIdadesFuncionarios(PercentagemIdades *percentagens);
void imprimirGestaofaltas(RelatorioFaltas *gestaofaltas);
void imprimirPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio) ;
void imprimirDespesasTotais(DespesasAnuais *despesas);
void imprimirRelatorioValorHora(RelatorioValorHora *relatorio);
void imprimirRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio);
void gerarRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio, char*filename);
void gerarRelatorioDespesasTotais(DespesasAnuais *despesas, char*filename);
void gerarRelatorioValorHora(RelatorioValorHora *gestaofaltas, char*filename);
void gerarRelatorioPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio, char *filename); 
void gerarRelatorioFaltas(RelatorioFaltas *gestaofaltas, char*filename);
void gerarRelatoriopercentagemIdadesFuncionarios(PercentagemIdades *percentagens, char *filename);
void obterRelatorioValorHora(RelatorioValorHora *relatorio, char*filename);
void obterRelatorioPercentagemEstadoCivil(PercentagemEstadoCivil *relatorio, char*filename);
void obterRelatorioDespesasTotais(DespesasAnuais *relatorio, char*filename);
void obterRelatoriopercentagemIdadesFuncionarios(PercentagemIdades *percentagens, char *filename);
void obterRelatorioPercentagemTempoEmpresa(PercentagemTempoEmpresa *relatorio, char *filename); 
void obterRelatorioFaltas(RelatorioFaltas *gestaofaltas, char*filename);
void libertarMemoriaGestaoFaltas(RelatorioFaltas *gestaofaltas);
#endif /* DADOSESTATISTICOS_H */

