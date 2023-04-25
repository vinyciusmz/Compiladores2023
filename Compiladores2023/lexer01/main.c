#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
  Soma,
  Subtracao,
  Multiplicacao,
  Divisao,
  Vazio
} Token;

typedef struct
{
  Token tipo;
  char valor;
} TokenInfo;

TokenInfo *criarNovoToken(Token tipo, char valor)
{
  TokenInfo *token = (TokenInfo *)malloc(sizeof(TokenInfo));
  token->tipo = tipo;
  token->valor = valor;
  return token;
}

TokenInfo *ProxToken(char **charAtual)
{
  char c = **charAtual;
  Token tipo = Vazio;
  switch (c)
  {
  case '+':
    tipo = Soma;
    (*charAtual)++;
    break;
  case '-':
    tipo = Subtracao;
    (*charAtual)++;
    break;
  case '*':
    tipo = Multiplicacao;
    (*charAtual)++;
    break;
  case '/':
    tipo = Divisao;
    (*charAtual)++;
    break;
  case ' ':
    (*charAtual)++;
    return NULL;
  default:
    (*charAtual)++;
    break;
  }
  TokenInfo *token = criarNovoToken(tipo, c);
  return token;
}

void tokenizer(char *s, TokenInfo **tokens, int *tamanho)
{
  *tokens = (TokenInfo *)malloc(sizeof(TokenInfo) * strlen(s));
  *tamanho = 0;

  char *charAtual = s;
  while (*charAtual)
  {
    TokenInfo *token = ProxToken(&charAtual);
    if (token != NULL)
    {
      (*tokens)[*tamanho] = *token;
      (*tamanho)++;
      free(token);
    }
  }
}
int main(int argc, char *argv[])
{
  FILE *file;
  long size;
  char *textoArquivo;

  file = fopen(argv[1], "rb");
  if (!file)
  {
    perror("Falha ao abrir o arquivo");
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  textoArquivo = (char *)malloc(size + 1);
  if (!textoArquivo)
  {
    perror("Falha ao alocar memória");
    fclose(file);
    exit(1);
  }

  fread(textoArquivo, 1, size, file);
  textoArquivo[size] = '\0';

  fclose(file);

  printf("%s\n", textoArquivo);

  TokenInfo *tokens;
  int tamanho;
  tokenizer(textoArquivo, &tokens, &tamanho);
  for (int i = 0; i < tamanho; i++)
  {
    switch (tokens[i].tipo)
    {
    case Soma:
      printf("Soma\n");
      break;
    case Subtracao:
      printf("Subtracao\n");
      break;
    case Multiplicacao:
      printf("Multiplicacao\n");
      break;
    case Divisao:
      printf("Divisao\n");
      break;
    case Vazio:
      printf("Não identificado: %c\n", tokens[i].valor);
      break;
    }
  }
  free(tokens);
  free(textoArquivo);
  return 0;
}