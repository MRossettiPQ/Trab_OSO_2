/*
    Para compilar no terminal use:
    gcc main.c -o main -lssl -lcrypto -lm
    para executar ./main
    para init       - ./main init fs.bin
    para add        - ./main add fs.bin
    para addDir     - ./main addDir fs.bin
    para sha256     - ./main sha256 fs.bin
    para debug      - ./main debug fs.bin
    Tabela ASCII: https://bluesock.org/~willg/dev/ascii.html
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
double  retornaCeil             (double numInodes);

typedef struct 
{
    unsigned char       tamBloco;
    unsigned char       numBloco;
    unsigned char       numInode;
    char                *mapaBits;
    INODE               *vetorInode;
    char                indDir;
    char                *vetorBloco;
} INFOINODE;

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
        /*
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
        */
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
    FILE *arquivo;  
    arquivo = fopen(argv[2], "w+b");
    
    if (arquivo != NULL)                                                        //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        printf("\n Arquivo no diretorio");
    }
    else
    {
        printf("\n Arquivo inexistente");                                                    //Convoca o comando para o sistema
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
    
    arquivo = fopen(argv[2],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        // init fs.bin 5 10 2
        INFOINODE novoINFO;
        int pos = 0, posD, trocaBase, trocaBaseTB, trocaBaseNB, trocaBaseNI, contInode, contMapaBit, contBloco;
        float ceilMax = 0, auxCeil;
        char auxHex;

        //Transforma a char do argv em Hexadecimal
        trocaBase = (int)strtol(argv[3], NULL, 10);                             //Troca base do Tamanho do Bloco
        novoINFO.tamBloco = trocaBase;

        trocaBase = (int)strtol(argv[4], NULL, 10);                             //Troca base do Numero de Blocos
        novoINFO.numBloco = trocaBase;

        trocaBase = (int)strtol(argv[5], NULL, 10);                             //Troca base do Numero de Inodes
        novoINFO.numInode = trocaBase;

        //Transforma a char do argv em inteiro
        trocaBaseTB = (int)strtol(argv[3], NULL, 10);                           //Troca base do Tamanho do Bloco
        trocaBaseNB = (int)strtol(argv[4], NULL, 10);                           //Troca base do Numero de Blocos
        trocaBaseNI = (int)strtol(argv[5], NULL, 10);                           //Troca base do Numero de Inodes

        ceilMax = retornaCeil((double)strtol(argv[4], NULL, 10));
        //printf("\n Tamanho do Bloco: %i\n Numero de Bloco: %i\n Numero de Inodes: %i\n Numero Ceil: %f", trocaBaseTB, trocaBaseNB, trocaBaseNI, ceilMax);
        
        printf("\n Primeiro Malloc: mapaBits");
        novoINFO.mapaBits   = (char*)malloc(ceilMax);                           //Aloca o Mapa de Bits com N/8 posições
        printf("\n Segundo Malloc: vetorBloco");
        novoINFO.vetorBloco = (char*)malloc(trocaBaseTB * trocaBaseNB);         //Aloca o Vetor de Blocos com T * N Posições
        printf("\n Terceiro Malloc: vetorInode");
        //novoINFO.vetorInode = (INODE)malloc(trocaBaseNI * sizeoff(int));        //Aloca o Vetor de Inode com I posições
        //strcpy(novoINFO.dadoInode.NAME, "NaoUsado");
        fseek(arquivo, pos, SEEK_SET);                                          //Entra no arquivo na primeira posição
        for(contMapaBit = 0; contMapaBit <= ceilMax; contMapaBit++)
        {  
            novoINFO.mapaBits[contMapaBit]    =   0x00;                         //Recebe o mapa de bits
        }
        for(contInode = 0; contInode <= trocaBaseNI; contInode++)
        {   
            printf("\n Dentro do for para o Inode[%i]", contInode+1);
            /*
            typedef struct 
            {
                unsigned char       tamBloco;
                unsigned char       numBloco;
                unsigned char       numInode;
                char                *mapaBits;
                INODE               *vetorInode;
                char                indDir;
                char                *vetorBloco;
            } INFOINODE;
            typedef struct 
            {
                unsigned char IS_USED;                                              // 0x01 se utilizado, 0x00 se livre
                unsigned char IS_DIR;                                               // 0x01 se diretorio, 0x00 se arquivo
                char NAME[10];                                                      // Nome do arquivo/dir
                char SIZE;                                                          // Tamanho do arquivo/dir em bytes
                unsigned char DIRECT_BLOCKS[3];                                     // 
                unsigned char INDIRECT_BLOCKS[3];                                   // 
                unsigned char DOUBLE_INDIRECT_BLOCKS[3];                            // 
            } INODE;
            
            //novoINFO.vetorInode[contInode].IS_USED  =   0x00;
            //novoINFO.vetorInode[contInode].IS_DIR   =   0x00;
            //novoINFO.vetorInode[contInode].SIZE = (int)strlen(novoINFO.dadoInode.NAME);
            //novoINFO.vetorInode[contInode].NAME  =      "TESTE DO NOME";
            */
        }
        for(contBloco = 0; contBloco <= (trocaBaseNI * trocaBaseTB); contBloco++)
        {
            novoINFO.vetorBloco[contBloco]  =   0x00;                               //Recebe o mapa de bits
        }
        novoINFO.indDir                 =   0x01;                                   //Posiciona o indice do diretorio raiz
        fwrite(&novoINFO, sizeof(INFOINODE), 1, arquivo);                           //Adiciona Inode no Arquivo .Bin
    }
    else
    {
        printf("\n Arquivo não foi encontrado \n");
    }
    return arquivo;
}

double   retornaCeil             (double numInodes)
{
    double divide = numInodes/8, result;
    result = ceil(divide);
    //printf("\nEntrada: %f\nDivide: %f\nCeil: %f", numInodes, divide, result);         //Debug da função

    return result;
}