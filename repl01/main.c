#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

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

void expressao(char *entrada);
char *termo(char* expressao);
int numero(char* termo);

//FUNÇÃO PARA LER O ARQUIVO TXT
char *lerArquivo(char *nomeArquivo) {
  FILE *file;
  char *palavra = (char*) malloc(MAX_TAM * sizeof(char));
  char ch;

  file = fopen(nomeArquivo, "r");
  // #LENDO CARACTER POR CARACTER#
  while((ch=fgetc(file)) != EOF){
    char aux[2];
    aux[0] = ch;
    aux[1] = '\0';
    strcat(palavra, aux);
  }

  //printf("\n%s\n",palavra);
  free(file);
  return palavra;
}

//VERIFICA SE O TOLKEN É UM NÚMERO
int lerNumero(int i, char *s){
  int j = i;

  if(isdigit(s[j]) == 0 && s[j] != '.'){
    return 0;
  }
  
  return 1;
}

//VERIFICA SE O NÚMERO É VALIDO
int checaNum(char *num){
  unsigned pontos=0;

  for(int i=0; num[i]!='\0'; i++){
    if(num[i]=='.')
      pontos++;
  }

  if(pontos<2)
    return 1;
  else
    return 0;
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

      case Espaco:
        tokens[j] = Espaco;
      break;

      case QuebraLinha:
        tokens[j] = QuebraLinha;
      break;

      default:
        tokens[j] = s[i];
      break;
    }
    j++;
  }
  return tokens;
}

//FUNÇÃO PRINTAR OS VALORES DO VETOR tokens
int LerTokens(char *s){
  for(int i =0; s[i] != '\0'; i++){
    char num[MAX_TAM] = "";
    switch(s[i]){
      case Mais:
        printf("Mais %c\n", s[i]);
      break;

      case Espaco:
      break;
        
      case QuebraLinha:
      break;
      
      default:        
        //LOGICA PARA VERIFICAR SE O TOKEN É UM NÚMERO OU INDETERMINADO
        if(lerNumero(i,s)){  
          while(lerNumero(i,s)){  
            char aux[2];
            sprintf(aux, "%c", s[i]);
            strcat(num, aux);
            i++;
          }
          i--;
          if(!checaNum(num)){
            printf("Indeterminado %s\n", num);
            return 1;
          }
        }
        else{
          printf("Indeterminado %c\n", s[i]);
          return 1;
        }       
      break;
    }
  }
  return 0;
}

void expressao(char *entrada){
  char *retorno=termo(entrada);

  if(retorno !="Invalido" || entrada=='\0'){
    printf("\n%s\n", retorno);
    free(retorno);
  }
  else
    printf("\nINVÁLIDO\n");

}

char *termo(char *expressao){
  int tam_num = 1, tam_num2 = 1, numero_index = 1;
  float resultado;
  char *num = (char*) malloc(sizeof(char) * tam_num);
  char *num2 = (char*) malloc(sizeof(char) * tam_num2);
  char *retorno;

  for(int i=0; expressao[i]!='\0'; i++){
    if(expressao[i]=='+'){
      numero_index++;
      i++;
    }
    if(numero_index==1){
      tam_num++;
      num = (char*) realloc(num, sizeof(char) * tam_num);
      char aux[2];
      sprintf(aux, "%c", expressao[i]);
      strcat(num, aux);
    }
    else if(numero_index==2){ 
      tam_num2++;
      num2 = (char*) realloc(num2, sizeof(char) * tam_num2);
      char aux2[2];
      sprintf(aux2, "%c", expressao[i]);
      strcat(num2, aux2);
    }
    else
      return "Invalido";
  }

  if(!numero(num) && num2=='\0')
    return num;
  else if(!numero(num) && !numero(num2) ){
    resultado = atof(num) + atof(num2);
    retorno = (char*) malloc(sizeof(char) * sizeof(resultado));
    sprintf(retorno, "%f", resultado);
    return retorno;
  }
  else
    return "Invalido";
}

int numero(char *termo){
  return LerTokens(termo);
}

int main(int argc, char **argv){ 
  //VERIFICAR TOKENS
  expressao(tokenizar(lerArquivo(argv[1])));

  return 0;
}
