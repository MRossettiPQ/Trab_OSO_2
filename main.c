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
#include "biblioteca.h"                                                         //Inclui algumas bibliotecas: unisted, openssl, sha256, inode.
//Declaração função
FILE*   criaSistemaArquivos     (char argc, char ** argv);
FILE*   direSistemaArquivos     (char argc, char ** argv);
FILE*   fileSistemaArquivos     (char argc, char ** argv);
char    criaPath                ();
void    verificaArquivo         (char argc, char ** argv);
void    debugArquivo            (char argc, char ** argv);


//Função principal
int main(char argc, char ** argv)
{
    FILE* arqDisco;
    char cmdCC[90], auxSprintf, *questiona = (char*)malloc(sizeof(char));
    printf("\nResposta: %s", questiona);

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
        printf("\n Adiciona Arquivo ao Sistema de Arquivos");
        arqDisco = criaSistemaArquivos(argc, argv);
        printf("\n Arquivo Adicionado ao Sistema de Arquivos Criado\n");
    }
    else if(0 == strcmp(argv[1], "addDir"))
    {
        // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Adiciona Diretorio ao Sistema de Arquivos");
        arqDisco = criaSistemaArquivos(argc, argv);
        printf("\n Diretorio Adicionado ao Sistema de Arquivos Criado\n");
    }    
    else if(0 == strcmp(argv[1], "sha256"))
    {
        // IMPRIME A HASH               - sha256 "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Imprime a HASH");
        verificaArquivo(argc, argv);                                        //Verifica se o .bin passado existe
        auxSprintf = sprintf(cmdCC, "%s/%s", criaPath(), argv[2]);          //Gera o path para o arquivo desejado
        printf("\n\nPath: %s\n\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else if(0 == strcmp(argv[1], "debug"))
    {
        // IMPRIME DADOS DO Bin         - debug "nome arquivo.bin"
        printf("\n Imprime os metadados do 'DISCO'");
        debugArquivo(argc, argv);
    }

    printf("\n=============FIM DO PROGRAMA=============\n\n");

	return 0;	
}
//Implementa função
char    criaPath            ()
{
    char pathSis[256];
    getcwd(pathSis, sizeof(pathSis));
    return pathSis;
}
void    debugArquivo        (char argc, char ** argv)                           //Função para impressão dos espaços de memoria, apenas para efeito comparativo
{
    printf("\n O Arquivo contem \n\n");
    printf("OFFSET\t\t01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\t\tTEXTO DECODIFICADO");


}
void    verificaArquivo     (char argc, char ** argv)                           //Função para detectar o arquivo .bin passado como argumento, e cria-lo caso não exista
{
    char cmdCC[35], auxSprintf;
    
    FILE *arquivo;  
    arquivo = fopen(argv[2], "r");
    
    if (arquivo != NULL)                                                        //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        printf("\n Arquivo no diretorio");
    }
    else
    {
        printf("\n Arquivo inexistente");
        auxSprintf = sprintf(cmdCC, "touch %s", argv[2]);                       //Gera o comando para criar o .bin
        system(cmdCC);                                                          //Convoca o comando para o sistema
        printf("\n Arquivo gerado\n\n");
    }
}
FILE*   direSistemaArquivos (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[2],"rb+");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        
    }
    return arquivo;
}
FILE*   fileSistemaArquivos (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[2],"rb+");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {

    }
    return arquivo;
}
FILE*   criaSistemaArquivos (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;                                                      
    
    arquivo = fopen(argv[2],"rb+");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        INODE novoINUDE;
        int pos = 0, posD;
        char *conteudo = (char*)malloc(5*(sizeof(char)));

        novoINUDE.IS_USED                   =   0x01;
        novoINUDE.IS_DIR                    =   0x00;
        novoINUDE.SIZE                      =   5;
        scanf                                                                                       
        fseek(arquivo, pos, 0);
        fputs(TAMBLOCO, arquivo);
        fputs(NUMBLOCO, arquivo);
        fputs(NUMINODE, arquivo);
        fputs(MAPABITS, arquivo);
        fputs(VETORINO, arquivo);
        fputs(DIRAIZ, arquivo);
        fputs(VETORAIZ, arquivo);

        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes" 
        // init fs.bin 5 10 2
        /*

        */


        //fwrite(&meta, sizeof(struct metadata), 1, arquivo);
    }
    else
    {
        printf("\n Arquivo não foi encontrado \n");
    }
    

    return arquivo;
}
