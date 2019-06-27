/*
    Para compilar no terminal use:
    gcc main.c -o main -lssl -lcrypto 
    para executar ./main
    para init       - ./main init fs.bin
    para add        - ./main add fs.bin
    para addDir     - ./main addDir fs.bin
    para sha256     - ./main sha256 fs.bin
    para debug      - ./main debug fs.bin
    Caso queira pegar as hash de varios arquivos para efeito de comparação: https://md5file.com/calculator
    fs.bin              zerada  - hash: e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    fs-case4.bin        dados   - hash: 5e943f87291a49124b76aba868e278a11a5b99c56964e0039bd178e37217d619
    fs-case5.bin        dados   - hash: 42e371527570e3107ea3ebe9cec94bc47169c153fb53438d963c8008651dd39e
    fs-case6.bin        dados   - hash: a54859682dcd9d4c15d0927da68c502b62ff8cc9032e6acdb7de4398d2399e84
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
    char cmdCC[35], auxSprintf, *questiona = (char*)malloc(sizeof(char));
    printf("\nResposta: %s", questiona);

    do
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
            verificaArquivo(argc, argv);                                //Verifica se o .bin passado existe
            auxSprintf = sprintf(cmdCC, "/%s", argv[2]);                //Gera o path para o arquivo desejado
            printf("\n\nHash: ");
            printSha256(cmdCC);                                         //Imprime a HASH
        }
        else if(0 == strcmp(argv[1], "debug"))
        {
            // IMPRIME DADOS DO Bin         - debug "nome arquivo.bin"
            printf("\n Imprime os metadados do 'DISCO'");
        }
        printf("\nDeseja executar outro comando?\n");
			scanf("%s", questiona);
        //printf("\nDeseja executar outro comando? (1 - Para SIM          /2 - Para Não)\n");
		//	scanf("%i", &quesNum);
    } while((0 == strcmp(questiona, "s")) || (0 == strcmp(questiona, "S")) || (0 == strcmp(questiona, "SIM")) || (0 == strcmp(questiona, "sI")) || (0 == strcmp(questiona, "SI")) || (0 == strcmp(questiona, "Sim")));
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
        auxSprintf = sprintf(cmdCC, "touch %s", argv[2]);               //Gera o comando para criar o .bin
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
