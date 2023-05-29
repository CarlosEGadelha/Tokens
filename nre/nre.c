#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_TAMANHO 255
#define HEADER 42   
#define STA 16
#define LDA 32
#define ADD 48
#define OR 64
#define AND 80
#define NOT 96
#define JMP 128
#define JN 144
#define JZ 160
#define HLT 240

int verificaNegativo(uint8_t num){
  return num >> 7;
}
 
void lerBinario(char *nomeArquivo){
  static uint8_t c[MAX_TAMANHO];
  FILE *f;
  f = fopen(nomeArquivo, "r");
  fseek(f, 0, SEEK_SET);
  fread(c, 512, 1, f);
  
  for(int i = 0; c[i] != HLT; i++){
    printf(" %u ", c[i]);
  }

  printf("\n");
}

void gerarBinario(char *buffer, int tamanhoBuffer, char *nomeArquivo){
  FILE *f = fopen(nomeArquivo, "wb");
  fwrite(buffer, 1, tamanhoBuffer, f);
  fclose(f);
}

void verificaBytes(char *nomeArquivo){
  uint8_t c[MAX_TAMANHO], Ac, PC;
  int i = 3;
  FILE *f;
  f = fopen(nomeArquivo, "r");
  fseek(f, 0, SEEK_SET);
  fread(c, 512, 1, f);
  
  if(c[0] != HEADER){
    printf("\nRejeitado! O primeiro byte deve ser 42.");
    exit(0);
  }
  
  Ac = c[1];
  PC = c[2];
 
  while(c[i] != HLT){
    switch(c[i]){
      case STA:
        i++;
        c[c[i]] = Ac;
        break;
      
      case LDA:
        i++;
        Ac = c[c[i]];
        break;
    
      case ADD:
        i++;
        Ac += c[c[i]];
        break;

      case OR:
        i++;
        Ac |= c[c[i]];
        break;

      case AND:
        i++;
        Ac &= c[c[i]];
        break;

      case NOT:
        Ac = ~Ac;
        break;

      case JMP:
        i++;
        i = c[i];
        i--;
        break;

      case JN:
        i++;
        if(verificaNegativo( c[c[i]]) )
          i = c[i];
          i--;
        break;
      
      case JZ:
        if(Ac == 0){
          i++;
          i = c[i];
          i--;
        }
        break;
    }
    i++;
  }

  PC = i;

  printf("\nACUMULADOR: %u\n", Ac);
  printf("\nProgram counter: %u\n", PC);

}

int main(int argc, char **argv) {
  lerBinario(argv[1]);
  verificaBytes(argv[1]);

	return 0;
}
