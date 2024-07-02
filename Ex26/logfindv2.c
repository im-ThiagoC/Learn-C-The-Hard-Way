#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <windows.h>


#define MAX_FILES 1000
#define MAX_FILENAME_LENGTH 256
#define MAX_SIZE 256
#define MAX_BUFFER 256
#define DISALLOWED_DIRS 4

const char *disallowedDirs[] = {
    "",
    ".git",
    ".vs",
    ".vscode"
};

int isDisallowedDir(const char *dirName) {
    for (int i = 1; i < DISALLOWED_DIRS; i++) {
        if (strcmp(dirName, disallowedDirs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void saveFileName(char files[][MAX_FILENAME_LENGTH], int *fileCount, const char *fileName) {
    if (*fileCount < MAX_FILES) {
        strcpy(files[*fileCount], fileName); 
        (*fileCount)++; //fileCount tem ponteiro para main
    } else {
        printf("Número máximo de arquivos atingido.\n");
    }
}

void findAndSaveFiles(const char *dirPath, char files[][MAX_FILENAME_LENGTH], int *fileCount) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    char subDir[MAX_PATH];

    // Formata o caminho para buscar todos os arquivos e diretórios
    snprintf(searchPath, MAX_PATH, "%s\\*", dirPath);

    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erro ao abrir o diretório %s\n", dirPath);
        return;
    }

    do {
        // Ignora os diretórios "." e ".."
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            // Verifica se é um diretório não permitido
            if (isDisallowedDir(findFileData.cFileName)) {
                continue;
            }

            snprintf(subDir, MAX_PATH, "%s\\%s", dirPath, findFileData.cFileName);
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Se for um diretório, faz a busca recursiva
                findAndSaveFiles(subDir, files, fileCount);
            } else {
                // Se for um arquivo, verifica a extensão
                if (strstr(findFileData.cFileName, ".") && !(strstr(findFileData.cFileName, ".exe"))) {
                    saveFileName(files, fileCount, subDir);
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main(int argc, char *argv[]) {
    char dirPath[MAX_PATH] = "..";
    char files[MAX_FILES][MAX_FILENAME_LENGTH];
    int fileCount = 0;

    // Encontra e salva os arquivos
    findAndSaveFiles(dirPath, files, &fileCount);

    // Lista os nomes dos arquivos armazenados
    if(argc == 1){
        printf("Arquivos encontrados na busca:\n");
        for (int i = 0; i < fileCount; i++) {
            printf("%s\n", files[i]);
        }
    }

    char word[MAX_SIZE];             // Palavra buscada
    char buffer[MAX_BUFFER];         // buffer que mantém o conteúdo do arquivo

    // Procura um arquivo por vez e verifica se word é uma substring de buffer
    int fileLoop = 0;
    FILE *fp;
    for (fileLoop = 0; fileLoop < fileCount; fileLoop++)
    {
        //*Abre o arquivo e verifica se abriu com êxito
        fp = fopen(files[fileLoop], "r");
        check(fp != NULL, "File error");
        //log_info("Entrando em %s", files[fileLoop]);

        //Reset
        int i = 1;
        int flag = 0;

        for(i = 1; i < argc; i++){ //Percorre cada palavra de entrada na execução
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
                        //Rebobina para inicio do arquivo
                        rewind(fp);
                        //? fseek() works too
                        //fseek(fp, 0, 0);
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
