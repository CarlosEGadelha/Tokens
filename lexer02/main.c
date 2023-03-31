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
  QuebraLinha = '\n',
  Multiplicacao = '*',
  Divisao = '/',
  Potencia = '^',
  Indeterminado,
};

int checaPotencia(int i, char *s){
  int prox = i+1;
  
  if(s[prox] == '*'){
    return 1;
  }
  else{
    return 0;
  }
}

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
  int j=0;

  //DEFININDO O TAMANHO DO ARRAY TOKENS DE ACORDO COM O TAMANHO DA ENTRADA
  tokens = (char *) malloc(n * sizeof(char));

  //VERIFICANDO O ARRAY DE CARACTERES
  for(int i =0; s[i] != '\0'; i++){
    switch(s[i]){
      case Mais:
        tokens[j] = Mais;
      break;

      case Menos:
        tokens[j] = Menos;
      break;

      case Espaco:
        tokens[j] = Espaco;
      break;

      case QuebraLinha:
        tokens[j] = QuebraLinha;
      break;
        
      case Multiplicacao:
        if(checaPotencia(i, s))
        {
          int prox = i +1;
          tokens[j] = Potencia;
          i++;
        }
        else
        {
          tokens[j] = Multiplicacao;
        }
      break;

      case Divisao:
        tokens[j] = Divisao;
      break;

      default:
        tokens[j] = s[i];
      break;
    }
    j++;
  }
  return tokens;
}

void LerTokens(char *s){
  for(int i =0; s[i] != '\0'; i++){
    switch(s[i]){
      case Mais:
        printf("Mais %c\n", s[i]);
      break;

      case Menos:
        printf("Menos %c\n", s[i]);
      break;

      case Multiplicacao:
        printf("Multiplicação %c\n", s[i]);
      break;

      case Potencia:
        printf("Potencia **\n");
      break;

      case Divisao:
        printf("Divisão %c\n", s[i]);
      break;

      case Espaco:
      break;
        
      case QuebraLinha:
      break;
      
      default:
        printf("Indeterminado %c\n", s[i]);
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
