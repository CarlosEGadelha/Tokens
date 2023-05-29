#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_TAMANHO 512
#define MAX_MEMORIA 30000
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

void gerarBinario(char *buffer, int tamanhoBuffer){
  FILE *f = fopen("binario.bin", "wb");
  fwrite(buffer, 1, tamanhoBuffer, f);
  fclose(f);
}

void verificaBytes(char *nomeArquivo){
  uint8_t c[MAX_TAMANHO], Ac, PC;
  int i = 3;
  FILE *f;
  f = fopen(nomeArquivo, "rb");
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
        //printf(" STA ");
        i++;
        c[c[i]] = Ac;
        //printf(" END: %u ", c[i]);
        //printf(" %u ", c[c[i]]);
        break;
      
      case LDA:
        //printf(" LDA ");
        i++;
        Ac = c[c[i]];
        //printf(" END: %u ", c[i]);
        //printf(" AC: %u ", Ac);
        break;
    
      case ADD:
        //printf(" ADD ");
        i++;
        Ac += c[c[i]];
        //printf(" END: %u ", c[i]);
        //printf(" AC: %u ", Ac);
        break;

      case OR:
        //printf(" OR ");
        i++;
        Ac |= c[c[i]];
        break;

      case AND:
        //printf(" AND ");
        i++;
        Ac &= c[c[i]];
        break;

      case NOT:
        Ac = ~Ac;
        //printf(" NOT ");
        break;

      case JMP:
        i++;
        i = c[i];
        i--;
        //printf(" JMP ");
        break;

      case JN:
        //printf(" JN ");
        i++;
        if(verificaNegativo(c[c[i]]))
          i = c[i];
          i--;
        break;
      
      case JZ:
        //printf(" JN ");
        if(Ac == 0){
          i++;
          i = c[i];
          i--;
        }
        break;
    }
    i++;
  }

  printf("\nACUMULADOR: %u\n", Ac);
  printf("\nProgram counter: %u\n", PC);

}

int main() {
	char buffer[13] = {42,2,1,32,10,48,11,16,12,240,1,2,0};
	//char buffer[26] = {42, 1, 0, 16, 0, 32, 0, 48, 0, 64, 0, 80, 0, 96, 128, 14, 3, 144, 17, 0, 32, 1, 160, 22, 0, 240};
  gerarBinario(buffer, 13);

  lerBinario("binario.bin");

  verificaBytes("binario.bin");

	return 0;
}
