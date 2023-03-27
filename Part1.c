#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_TAM 2048

//DEFININDO CARACTERES
enum Token{
  Mais = '+',
  Menos = '-',
  Indeterminado = '0'
};

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

      case ' ':
        tokens[i] = ' ';
        break;

      default:
        tokens[i] = Indeterminado;
        break;
    }
  }
  return tokens;
}

int main(void){
  char *entrada;
  
  //ENTRADA DO USUÁRIO
  printf("\nDIGITE A ENTRADA:\n");
  fgets(entrada, MAX_TAM, stdin);

  //RETORNO DOS TOKENS RECONHECIDOS
  printf("\nRetorno: %s\n",tokenizar(entrada));    
  
  return 0;
}
