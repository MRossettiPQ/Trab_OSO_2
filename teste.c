/*
    Para compilar no terminal use:
    gcc teste.c -o teste -lssl -lcrypto -lm
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
#include <unistd.h>
#include <stdio.h>
#include <string.h>                                                 //strlen
#include <stdlib.h>                                                 //strlen
#include <math.h>                                                   //Inclui algumas bibliotecas: unisted, openssl, sha256, inode.
#include "inode.h"

int     addDirRaiz              (char argc, char ** argv);
double  retornaCeil             (double numInodes);
int     buscaBlock              (char argc, char ** argv, int idPai, int idBloc);

//Função principal
int main                    (char argc, char ** argv)
{
    int tamEntrada = strlen(argv[3]), aux;
    char auxRaiz[tamEntrada], auxRaizRaiz[tamEntrada], auxArquivo[tamEntrada];
    //Pasta raiz
    sprintf (auxRaizRaiz, "%c", argv[3][0]);
    int contX = 1;
    while((contX < tamEntrada) && (argv[3][contX] != '/'))              //RAIZRAIZ
    {   
        sprintf (auxRaizRaiz, "%s%c", auxRaizRaiz, argv[3][contX]);
        contX = contX + 1;
    }
    sprintf (auxRaiz, "%c", argv[3][contX]);
    contX = contX + 1;
    while((contX < tamEntrada) && (argv[3][contX] != '/'))               //RAIZ
    {   
        sprintf (auxRaiz, "%s%c", auxRaiz, argv[3][contX]);
        contX = contX + 1;
    }
    sprintf (auxArquivo, "%c", argv[3][contX]);
    contX = contX + 1;
    while((contX < tamEntrada) && (argv[3][contX] != '\0'))              //Arquivo/Pasta a ser adicionada
    {   
        sprintf (auxArquivo, "%s%c", auxArquivo, argv[3][contX]);
        contX = contX + 1;
    }
    tamEntrada = strlen(auxRaizRaiz);
    aux = addDirRaiz(argc, argv);

    printf("\n");

	return 0;
}

int     addDirRaiz    (char argc, char ** argv)                           //Função que retorna Diretorio Raiz
{	
    int tamEntrada = strlen(argv[3]), tamanhoRaiz, idInode = 0, posArq = 0, contX = 1, contY, idPai = 0;
    char auxRaiz[tamEntrada], auxRaizRaiz[tamEntrada], auxArquivo[tamEntrada], adicionar[tamEntrada], lido[10];
    char carac, auxArgv1, auxArgv2, auxArgv3, auxHEX[10];
    FILE *arquivo;

    sprintf (auxRaizRaiz, "%c", argv[3][0]);
    while((contX < tamEntrada) && (argv[3][contX] != '/'))              //RAIZRAIZ
    {   
        sprintf (auxRaizRaiz, "%s%c", auxRaizRaiz, argv[3][contX]);
        contX = contX + 1;
    }
    sprintf (auxRaiz, "%c", argv[3][contX]);
    contX = contX + 1;
    while((contX < tamEntrada) && (argv[3][contX] != '/'))               //RAIZ
    {   
        sprintf (auxRaiz, "%s%c", auxRaiz, argv[3][contX]);
        contX = contX + 1;
    }

    printf("\n RaizRaiz: %s \t- Raiz: %s", auxRaizRaiz, auxRaiz);
    if(strlen(auxRaiz) == 0)                                                        //RAIZRAIZ deve ser adicionado
    {
        strcpy(adicionar, auxRaizRaiz);
    }
    else                                                                            //RAIZ deve ser adicionado
    {
        strcpy(adicionar, auxRaiz);
    }

    return idInode;     
}