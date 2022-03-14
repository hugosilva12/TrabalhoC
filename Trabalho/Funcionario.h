/**
 * @file Funcionario.h
 * @author Hugo Silva
 * @date 11 Novembro 2020
 * @brief Biblioteca  com a estrutura para armazenar informações do funcionário (parte pública)
 * 
 * Bibloteca com a estrutura do funcionário, enumerações  e funções  para leitura de dados da consola
 */
#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#define TAMANHO_STRING 100
#define TAMANHO_TELEMOVEL 12
#define MSG_NAO_ENCONTRADO "Código não corresponde a nenhum funcionário!"
#define MSG_REMOVIDO_SUCESS "Funcionario Removido com SUCESSO!"
#define ANO_MIN 1955
#define ANO_MAX 2003
#define ANO_MAX_ENTRADA 2021
/** @struct Data
 * @brief Armazena uma data 
 * @var Data::dia
 *  'dia' dia
 * @var Data::mes
 *  'mes' mês
 * @var Data::ano
 *  'ano' ano 
 */
typedef struct {
    int dia, mes, ano;
} Data;
/*! Enumeração que representa o estado civil do funcionário */
typedef enum {
    NAOCASADO = 1, /*!< Não Casado */
    CASADOUNICOTITULAR,/*!< Casado Único titular*/
   CASADODOISTITULARES /*!< Casado dois titulares */
} EstadoCivil;
/*! Enumeração que representa o cargo do funcionário na empresa */
typedef enum {
    ADMINISTRADOR = 1,/*!< Administrador */
     EMPREGADO, /*!< Empregado */
   CHEFE   /*!< Chefe */
} Cargo;
/*! Enumeração que representa o estado do funcionário  */
typedef enum {
     REMOVIDO = 0, /*!< Funcionário foi removido */
      ATIVO  /*!< Funcionário ativo */
} EstadoFuncionario;
/** @struct Funcionario
 * @brief  Armazena todas as informações relativas a um funcionário
 * @var Funcionario::codigo 
 *  'codigo' código de funcionário
 * @var Funcionario::dataEntradaEmpresa
 *  'dataEntradaEmpresa' data de entrada na empresa
 * @var Funcionario::nome
 *  'nome' nome do funcionário
 *  @var Funcionario::dataSaidaEmpresa
 *  'dataSaidaEmpresa' data saída da empresa
 * @var Funcionario::dataNascimento
 *  'dataNascimento' data de nascimento
 * @var Funcionario::nrDependentes
 *  'nrDependentes' dependentes do funcionário
 * @var Funcionario::subsidioAlimentacao
 *  'subsidioAlimentacao' valor subsídio alimentação
 * @var Funcionario::valorHora
 *  'valorHora' valor que ganha por hora
 * @var Funcionario::criterioSS
 *  'criterioSS' identificação da taxa de segurança social a utilizar
 */
typedef struct {
    int codigo; //Unico
    char nome[TAMANHO_STRING];
    char numeroTelemovel[TAMANHO_TELEMOVEL];
    Data dataNascimento;
    Data dataEntradaEmpresa;
    Data dataSaidaEmpresa;
    EstadoCivil estadoCivil;
    EstadoFuncionario estadoEmpregado;
    Cargo  cargoEmpresa;
    int nrDependentes;
    float subsidioAlimentacao;
    float valorHora;
    int criterioSS;
} Funcionario;

void criarFuncionario(Funcionario *funcionario);
void lerData(Data *data, int AnoMax); 
int funcionarioAtivo();
int estadoCivil();
void numeroTelemovel(Funcionario *funcionario);
int  cargoFuncionario();
void mostrarDadosFuncionario(Funcionario func);
char *estadoCivilToString(EstadoCivil comb);
#endif 

