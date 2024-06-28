
/*
*Geral: Esse algoritmo faz o match do parâmetro com o conteúdo de algum arquivo buscado
*
*Uso: ./logfind [string buscada]
*Listagem de arquivos permitidos ./logfind
*
*Output: todos arquivos que contenham [string] em seu conteúdo
*
!   Exemplo:
?
!   ./logfind thiago oi demais
?   Se o arquivo rapaz.txt e outro.txt conter thiago, oi E demais
!   rapaz.txt outro.txt
*/

#include <stdio.h>
#include "dbg.h"
#include <string.h>

#define MAX_BUFFER 1000
#define MAX_SIZE 100

int main(int argc, char *argv[])
{
    char *files[4];
    files[0] = "outro.txt";
    files[1] = "teste.txt";

    if (argc == 1)
    {
        int i = 0;
        printf("Arquivos permitidos:\n");
        while (files[i] != NULL)
        {
            puts(files[i]);
            i++;
        }

        return 0;
    }

    char word[MAX_SIZE];             // Palavra buscada
    char buffer[MAX_BUFFER];         // buffer que mantém o conteúdo do arquivo

    // Procura um arquivo por vez e verifica se word é uma substring de buffer
    int fileLoop = 0;
    FILE *fp;
    for (fileLoop = 0; fileLoop < 2; fileLoop++)
    {
        //*Abre o arquivo e verifica se abriu com êxito
        fp = fopen(files[fileLoop], "r");
        check(fp != NULL, "File error");

        int i = 0;
        int flag = 0;
        for(i = 1; i < argc - 1; i++){ //Percorre cada palavra de entrada na execução
            memcpy(word, argv[i], MAX_SIZE); // Copia o conteúdo passado como parâmetro na execução para word

            while (fgets(buffer, sizeof(buffer), fp)){ // Lê cada palavra do arquivo e salva em buffer.
                if (strlen(buffer) > 1)
                {
                    if (strlen(word) > strlen(buffer))
                    {
                        //? Se o buffer for menor que word, não é necessário verificar
                        continue;
                    }
                    
                    if (strstr(buffer, word))
                    { //* Verifica a Substring
                        flag++;
                        
                        break;
                    }
                }
            }
        }

        if(flag == argc - 1){
            puts(files[fileLoop]);
        }
    
        fclose(fp);
    }

    return 0;
error:
    if (fp)
        fclose(fp);
    return 1;
}
