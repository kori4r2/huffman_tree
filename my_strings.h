/*
	Italo Tobler Silva - nUSP 8551910
*/
#ifndef my_strings
#define my_strings

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*------------------------------------------------------------------------------------------------------------
   copy_sized_string_input()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
void copy_sized_string_input(FILE *input, void *location, int size);

/*------------------------------------------------------------------------------------------------------------
   get_string_list()
        Le o numero de strings para leitura e le as strings da stream de dados passada da maneira desejada
        - Parametros
          FILE* : stream de dados
	  int*: endereco da variavel que guarda o numero de linhas lidas
	  int : modo de leitura; 0 - tamanho da string limitado; 1 - le ate encontrar \n ou EOF
        - Retorno
          char** : vetor de strings lido; NULL caso erro de leitura
*/
char **get_string_list(FILE *stream, int *tam, int mode);

/*------------------------------------------------------------------------------------------------------------
   read_sized_string()
        Funcao que aloca uma quantidade fixa de memoria e le caracteres da stdin ate encontrar \n ou EOF mas
	armazena um numero limitado de caracteres
        - Parametros
          FILE* : stream de dados a ser lida
	  int : tamanho maximo da string
        - Retorno
          char* : string lida
*/
char *read_sized_string(FILE *stream, int size);

/*------------------------------------------------------------------------------------------------------------
   my_get_line_valid()
        Funcao que le uma string da stream de dados passada, eliminando caracteres invalidos no inicio
        - Parametros
          FILE* : stream de dados a ser lida
	  int* : endereco da variavel que armazena a condicao de parada
        - Retorno
          char : string lida da stream de dados; NULL caso erro de leitura
*/
char *my_get_line_valid(FILE *stream, int *ending);

/*------------------------------------------------------------------------------------------------------------
   ny_gets()
        Funcao que le uma string de tamanho maximo desejado da stream passada, tendo espaços, quebra de linha
	e fim de arquivo como condicoes de parada
        - Parametros
          FILE* : stream de dados a ser lida
	  int : tamanho da string a ser lida
        - Retorno
          char* : string lida da stream de dados; NULL caso erro de leitura
*/
char *my_gets(FILE *stream, int str_size);

/*------------------------------------------------------------------------------------------------------------
   free_string_list()
        Funcao que libera a memoria alocada por um vetor contendo um numero determinado de strings
        - Parametros
          char** : vetor de strings com memoria alocada
	  int : tamanho do vetor de strings
        - Retorno
          void
*/
void free_string_list(char **string_list, int size);

/*------------------------------------------------------------------------------------------------------------
   my_get_line()
        Funcao que le uma string da stream de dados desejada ate que seja encontrada quebra de linha ou fim de
	arquivo
        - Parametros
          FILE* : stream de dados a ser lida
        - Retorno
          char* : string lida da stream de dados; NULL caso erro de leitura
*/
char *my_get_line(FILE *stream);

/*------------------------------------------------------------------------------------------------------------
   print_string_list()
        Funcao que imprime as strings armazenadas em um vetor de strings, imprimindo uma a cada linha
        - Parametros
          char** : vetor de strings a ser impresso
	  int : tamanho do vetor de strings a ser impresso
        - Retorno
          void
*/
void print_string_list(char **string_list, int size);

/*------------------------------------------------------------------------------------------------------------
   search_char()
        Funcao que busca uma string à procura de um caractere desejado
        - Parametros
	  char : caractere a ser buscado
          char** : vetor de strings onde a busca será realizada
        - Retorno
          int : 1 - caractere encontrado; 0 - caractere não encontrado ou string inválida
*/
int search_char(char, char*);

#endif
