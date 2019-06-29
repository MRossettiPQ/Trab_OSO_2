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
    disco.bin           dados   - hash: 0f3c42a06b8055af98b733bfa1186e4245157c09a404a7151ec13469c83c3f3b
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
void    verificaArquivo         (char argc, char ** argv);
void    debugArquivo            (char argc, char ** argv);
int     inodeLivre              (FILE* arquivo);


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
        char pathSis[256];
        // IMPRIME A HASH               - sha256 "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Imprime a HASH");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        verificaArquivo(argc, argv);                                        //Verifica se o .bin passado existe
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
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
void    debugArquivo        (char argc, char ** argv)                           //Função para impressão dos espaços de memoria, apenas para efeito comparativo
{
    printf("\nArquivo: %s", argv[2]);
    verificaArquivo(argc, argv);        
    printf("\n O Arquivo contem \n");
    printf("OFFSET\t\t01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\t\tTEXTO DECODIFICADO");
    char valor;
    int offset = 0000000, cont = 0;
    FILE *arquivo; 
    arquivo = fopen(argv[2], "r");
    
    printf("\n%i\t\t", offset);
    if (arquivo != NULL)                                                        //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        printf("\n%i\t\t", offset);
        while(fscanf(arquivo, "%s", valor) != EOF)
        {
            printf("%s  ");
            offset = offset + 00000001;
            if(cont == 15)
            {
                printf("\n'TEXTO DECODIFICADO'");
                printf("\n%i\t\t", offset);
            }
        }
    }
    fclose(arquivo);
}
int     inodeLivre              (FILE* arquivo)
{
	char aux = 0;
	int contX = 0, idInode = 0;
	fseek(arquivo, B_LIVRES, SEEK_SET);
	
	for (contX = 0; contX < N_INODE; contX++)
	{
		fread(&idInode, sizeof(int), 1, arquivo);
		aux++;
		
		if (idInode == 0x00)
		{
			fseek(arquivo, -sizeof(int), SEEK_CUR);
			fprintf(arquivo,"%c",aux);
			return aux;
		}
		
		if (contX < N_INODE-1)
        {
			fseek(arquivo, sizeof(INODE)-sizeof(int), SEEK_CUR);
	    }
    }
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
    fclose(arquivo);
}

FILE*   direSistemaArquivos (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[2],"rb+");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        
    }    
    else
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
    else
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
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        // init fs.bin 5 10 2
        INODE novoINODE;
        int pos = 0, posD;
        char TamanhoBloco[1], NumeroBloco[1], NumeroInode[1], *conteudo = (char*)malloc(5*(sizeof(char)));                                                                          
        fseek(arquivo, pos, 0);

        strcpy(TamanhoBloco, argv[3]);                                          //Tamanho dos blocos
        strcpy(NumeroBloco, argv[3]);                                           //Numero de blocos
        strcpy(NumeroInode, argv[3]);                                           //Numero de Inodes
        strcpy(novoINODE.SIZE, "1024");
        strcpy(novoINODE.SIZE, "1");
        strcpy(novoINODE.SIZE, "0");
        
        fwrite(&TamanhoBloco, sizeof(int), 1, arquivo);
        fwrite(&NumeroBloco, sizeof(int), 1, arquivo);
        fwrite(&NumeroInode, sizeof(int), 1, arquivo);
        fwrite(&novoINODE, sizeof(INODE), 1, arquivo);
        //fwrite(&meta, sizeof(struct metadata), 1, arquivo);
    }
    else
    {
        printf("\n Arquivo não foi encontrado \n");
    }

    return arquivo;
}
