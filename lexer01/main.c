#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_TAM 2048
#define MAX_TAMANHO 256

//DEFININDO CARACTERES
enum Token{
  Mais = '+',
  Menos = '-',
  Espaco = ' ',
  Multiplicacao = '*',
  Divisao = '/',
  Indeterminado = '0',
};

char *lerArquivo(char *nomeArquivo) {
  FILE *file;
  char texto[MAX_TAMANHO];
  char *palavra;

  file = fopen(nomeArquivo, "r");

  // #LENDO POR LINHA#
  palavra = fgets(texto, MAX_TAMANHO, file);

  free(file);
  return palavra;
}

//FUNÇÃO QUE VERIFICA OS TOKENS
char *tokenizar(char *s){ 
  char *tokens;
  size_t n = sizeof(s)/sizeof(s[0]);
  
  //DEFININDO O TAMANHO DO ARRAY TOKENS DE ACORDO COM O TAMANHO DA ENTRADA
  tokens = (char *) malloc(n * sizeof(char));

  //VERIFICANDO O ARRAY DE CARACTERES
  for(int i =0; s[i] != '\0'; i++){
    switch(s[i]){
      case Mais:
        tokens[i] = Mais;
        break;

      case Menos:
        tokens[i] = Menos;
        break;

      case Espaco:
        tokens[i] = Espaco;
        break;

      case Multiplicacao:
        tokens[i] = Multiplicacao;
        break;

      case Divisao:
        tokens[i] = Divisao;
        break;

      default:
        tokens[i] = Indeterminado;
        break;
    }
  }
  return tokens;
}

void LerTokens(char *s){
  for(int i =0; s[i] != '\0'; i++){
    switch(s[i]){
      case Mais:
        printf("Mais\n");
        break;

      case Menos:
        printf("Menos\n");
        break;

      case Multiplicacao:
        printf("Multiplicação\n");
        break;

      case Divisao:
        printf("Divisão\n");
        break;

      case Espaco:
        break;
        
      default:
        printf("Indeterminado\n");
        break;
    }
  }
}

int main(int argc, char **argv){
  //ENTRADA DO USUÁRIO
  //printf("\nDIGITE A ENTRADA:\n");
  //fgets(entrada, MAX_TAM, stdin);

  //RETORNO DOS TOKENS RECONHECIDOS
  LerTokens(tokenizar(lerArquivo(argv[1])));
  
  return 0;
}
