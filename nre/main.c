#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define MAX_TAMANHO 512
#define MAX_MEMORIA 30000

/*int P = 0;
int memoria[MAX_MEMORIA];
char mem_repeticao[MAX_MEMORIA];
int repeticao =0;

void verificaCaracter(char letra){

	if(repeticao == 0)
	{
		if(letra == '>')
			P++;
		if(letra == '<')
			P--;
		if(letra == '+')
			memoria[P] += 1;
		if(letra == '-')
			memoria[P] -= 1;
		if(letra == '.')
			putchar(memoria[P]);	
		if(letra == ',')
			memoria[P] = getchar();
		if(letra == '[')
			repeticao ++;
		if(letra == ']'){
			printf("\nRejeitado! Loop finalizado antes de ser inicializado!");
		 	exit(0);
		}
	}

	else 
	{
		if(letra == ']'){
		
			repeticao = 0;
			
			while(memoria[P] != 0){
				for(int i =0; i < MAX_MEMORIA ; i++)
					verificaCaracter(mem_repeticao[i]);
			}	
		}
			
		else{
			mem_repeticao[repeticao] = letra;
			repeticao ++;
		}
	}
}

int verificaSintaxe(char *palavra){
	char letra;
  unsigned i = 0;
	char alfabeto[] = {'>', '<', '+', '-', '.', ',', '[', ']', '\n','\t'}; 
	unsigned aceita = 0;

	while (i < strlen(palavra)) {
		letra = palavra[i];

		for(int j = 0; alfabeto[j]!=NULL; j++){
			if(letra == alfabeto[j]){
				aceita++;
				verificaCaracter(letra);
			}
		}

		if(aceita == 0)
			return 1;

		aceita =0;
		i++;
	}
	
	return 0; 
}

void lerArquivo(char *nomeArquivo) {
  FILE *f;
  f = fopen(nomeArquivo, "r");
  fseek(f, 0, SEEK_SET);
  fread(c,512,1, f);

  // #LENDO POR LINHA#
  for(int i = 0; c[i] != NULL; i++){
    //if(verificaSintaxe(c[i]) != 0){
      //printf("\nRejeitado! Caracter %s não pertence aos comandos da linguagem\n", palavra);
			//exit(0);
    //}
    printf(" %x ", c[i]);
  }
	
	printf("\nAceito\n");	
  fclose(f);
}*/

void lerBinario(char *nomeArquivo){
  static uint8_t c[MAX_TAMANHO];
  FILE *f;
  f = fopen(nomeArquivo, "r");
  fseek(f, 0, SEEK_SET);
  fread(c, 512, 1, f);
  
  for(int i = 0; c[i] != 0b11110000; i++){
    printf(" %u ", c[i]);
  }
}

void gerarBinario(char *buffer, int tamanhoBuffer){
  FILE *f = fopen("binario.bin", "wb");
  fwrite(buffer, 1, 10, f);
  fclose(f);
}

int main() {
	char buffer[10] = {42,0,0,32,10,48,11,16,12,240};
	
  gerarBinario(buffer, 10);

  lerBinario("binario.bin");

	return 0;
}
