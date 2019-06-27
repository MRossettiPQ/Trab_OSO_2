/*
    Para compilar no terminal use:
    gcc main.c -o main -lssl -lcrypto 
    para executar ./main
*/
//Importa arquivos pasta
#include "biblioteca.h"                                                  // 
//Declaração função
FILE*   criaSistemaArquivos     (char argc, char ** argv);
void    verificaArquivo         (char argc, char ** argv);


//Função principal
int main(char argc, char ** argv)
{
    FILE* arqDisco;
    char cmdCC[35], auxSprintf, *questiona = "SIM";
    
    printf("\nResposta: %s", questiona);

    while((0 == strcmp(questiona, "S")) || (0 == strcmp(questiona, "SIM")) || (0 == strcmp(questiona, "S")) || (0 == strcmp(questiona, "SI")) || (0 == strcmp(questiona, "Sim")))
    {
        printf("\n Decide a função");
        if(0 == strcmp(argv[1], "init"))
        {
            // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
            printf("\n Cria Sistema de Arquivos");
            arqDisco = criaSistemaArquivos(argc, argv);
            printf("\n Sistema de Arquivos Criado\n");
        }
        else if(0 == strcmp(argv[1], "add"))
        {
            // ADICIONA ARQUIVO             - add "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
            /* code */
        }
        else if(0 == strcmp(argv[1], "addDir"))
        {
            // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
            /* code */
        }    
        else if(0 == strcmp(argv[1], "sha256"))
        {
            // IMPRIME A HASH               - sha256 "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
            printf("\n Imprime a HASH");
            verificaArquivo(argc, argv);
            auxSprintf = sprintf(cmdCC, "/%s", argv[2]);                //Gera o path para o arquivo desejado
            printSha256(cmdCC);                                         //Imprime a HASH
        }
        else if(0 == strcmp(argv[1], "debug"))
        {
            // IMPRIME DADOS DO Bin         - debug "nome arquivo.bin"
            printf("\n Imprime os metadados do 'DISCO'");
        }
        printf("\nDeseja executar outro comando? (S - Para SIM          /N - Para Não)\n");
			scanf("%s", questiona);
    }
    printf("\n=============FIM DO PROGRAMA=============\n\n");

	return 0;	
}
//Implementa função
void    verificaArquivo     (char argc, char ** argv)                   //Função para detectar o arquivo .bin passado como argumento, e cria-lo caso não exista
{
    char cmdCC[35], auxSprintf;
    
    FILE *arquivo;  
    arquivo = fopen(argv[2], "r");
    
    if (arquivo != NULL)                                                //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        printf("\n Arquivo no diretorio");
    }
    else
    {
        printf("\n Arquivo inexistente");
        auxSprintf = sprintf(cmdCC, "touch %s", argv[2]);                        //Gera o comando para criar o .bin
        system(cmdCC);                                                  //Convoca o comando para o sistema
        printf("\n Arquivo gerado\n\n");
    }
}

FILE*   criaSistemaArquivos (char argc, char ** argv)                   //Cria o sistema de arquivos dentro do arquivo .bin
{
    verificaArquivo(argc, argv);                                        //Chama a verificação do arquivo .bin
    FILE *arquivo;                                                      

    arquivo = fopen(argv[2],"r");
    if (arquivo!=NULL)                                                  //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        //fwrite(&meta, sizeof(struct metadata), 1, arquivo);
    }
    else
    {
        printf("\n Arquivo não foi encontrado \n");
    }
    

    return arquivo;
}
