#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void gerarBinario(char *buffer, int tamanhoBuffer, char *nomeArquivo){
  FILE *f = fopen(nomeArquivo, "wb");
  fwrite(buffer, 1, tamanhoBuffer, f);
  fclose(f);
}

int main(int argc, char **argv) {
	//char buffer[13] = {42,2,1,32,10,48,11,16,12,240,11,2,0};
  char buffer[13] = {42, 0, 0, 32, 10, 64, 11, 16, 12, 240, 1, 2, 0};
  //char buffer[13] = {42, 0, 0, 32, 10, 80, 11, 16, 12, 240, 3, 2, 0};
  //char buffer[14] = {42,0,0,32,12,96,48,13,96,16,1,240,10,4};

  gerarBinario(buffer, 14, "binario.nar");
  
  return 0;
}
