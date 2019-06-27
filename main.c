/*
    Para compilar no terminal use:
    gcc main.c -o main -lssl -lcrypto 
    para executar ./main
*/
//Importa arquivos pasta
#include "biblioteca.h"                                                  // 
//Declaração função
FILE* criaSistemaArquivos(char argc, char ** argv);
void verificaArquivo(char argc, char ** argv);


//Função principal
int main(char argc, char ** argv)
{
    FILE* arqDisco;
    char *cmdCC;
    

    if(0 == strcmp(argv[1], "init"))
    {
        // CRIA SISTEMA DE ARQUIVO  - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        arqDisco = criaSistemaArquivos(argc, argv);
    }
    else if(0 == strcmp(argv[1], "add"))
    {
        /* code */
    }
    else if(0 == strcmp(argv[1], "addDir"))
    {
        /* code */
    }    
    else if(0 == strcmp(argv[1], "sha256"))
    {
        /* code */
    }
    else if(0 == strcmp(argv[1], "debug"))
    {
        /* code */
    }

    printf("\n=============FIM DO PROGRAMA=============\n\n");

	return 0;	
}
//Implementa função
void verificaArquivo(char argc, char ** argv)
{
    char *cmdCC, n;
    
    FILE *fp;
    fp = fopen(argv[2], "r");
    //VERIFICA ARQUIVO .bin NO DIRETORIO
    if (fp!=NULL)
    { 
        printf("\n Arquivo no diretorio");
    }
    else
    {
        printf("\n Arquivo inexistente");
        n = sprintf(cmdCC, "touch %s", argv[2]);
        system(cmdCC);
        printf("\n Arquivo gerado");
    }
}

FILE* criaSistemaArquivos(char argc, char ** argv)
{
    verificaArquivo(argc, argv);
    FILE *arquivo;

    arquivo = fopen(argv[2],"r");
    if (arquivo!=NULL)
    {
        //fwrite(&meta, sizeof(struct metadata), 1, arquivo);
    }
    else
    {
        printf("\nArquivo não foi encontrado \n");
    }
    

    return arquivo;
}
