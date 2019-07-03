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
    

    arquivo = fopen(argv[2],"r+b");
    if (arquivo != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(char), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv2, sizeof(char), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(char), 1, arquivo); 
        //printf("\n T: %i \tN: %i \tI: %i\n", auxArgv1, auxArgv2, auxArgv3);
        posArq = posArq + retornaCeil(auxArgv2) + 2;
        int conAgv1 = auxArgv1, conAgv2 = auxArgv2,conAgv3 = auxArgv3;

        for(contY = 0; contY < conAgv3; contY++)
        {
            printf("\n Proximo INODE");
            contX = 0;
            fseek(arquivo, posArq++, SEEK_SET);
                fread(&carac, sizeof(int), 1, arquivo);
                sprintf(lido,"/%c", carac);
            do
            {
                fseek(arquivo, posArq++, SEEK_SET);
                    fread(&carac, sizeof(int), 1, arquivo);
                sprintf(lido,"%s%c", lido, carac);
                contX++;
            }while((contX < 10) && (carac != 0x00));
            if(0 == strcmp(adicionar, lido))
            {
                idPai = contY;
                printf("\n Pasta existe\t idPai: %i", idPai);
            }
            printf("\n %s == %s", adicionar, lido);
            posArq = posArq + 10 + (10 - contX);
            printf("\n Pos: %i", posArq);
        }

        printf("\n auxArgv1: %i \tauxArgv2: %i \tauxArgv3: %i", conAgv1, conAgv2, conAgv3);
        printf("\n idPai: %i \t- Ceil: %i \t- idPai*INODE: %i", idPai, (int)retornaCeil(conAgv2), idPai * (int)sizeof(INODE));
        posArq = 15 + (int)retornaCeil(conAgv2) + idPai * (sizeof(INODE));
        printf("\n Pos: %i", posArq);
        for(contY = 0; contY < 3; contY++)
        {
            fseek(arquivo, posArq++, SEEK_SET);
                fread(&carac, sizeof(int), 1, arquivo);
            if(carac == 0x00)
            {
                printf("\n Bloco direto [%i] zerado", contY);
            }
            printf("\n Bloco direto: %i", carac);
        }
        






            
    }
    int idMapa;
    idMapa = buscaBlock(argc, argv, idPai-1, 0);
    //printf("\nidMapa: %i", idMapa);
    idMapa = buscaBlock(argc, argv, idPai-1, 1);
    //printf("\nidMapa: %i", idMapa);
    idMapa = buscaBlock(argc, argv, idPai-1, 2);
    //printf("\nidMapa: %i", idMapa);

    return idInode;     
}
double   retornaCeil        (double numInodes)
{
    double divide = numInodes/8, result;
    result = ceil(divide);
    //printf("\nEntrada: %f\nDivide: %f\nCeil: %f", numInodes, divide, result);         //Debug da função

    return result;
}

int buscaBlock              (char argc, char **argv, int idPai, int idBloc)
{
    int idMapa, posArq = 0;
    char auxArgv1, auxArgv2, auxArgv3;
    FILE *arquivo;

    arquivo = fopen(argv[2],"r+b");
    if (arquivo != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(char), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv2, sizeof(char), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(char), 1, arquivo); 

        int dadoMapa, contX = 0, posMapa = 0, pai = idPai, ag = auxArgv3, bloco = bloco;


        posArq = posArq + bloco + pai * (int)sizeof(INODE);
        printf("\n pos: %i", posArq);

        fseek(arquivo, posArq++, SEEK_SET);
            fread(&idMapa, sizeof(char), 1, arquivo);

        posMapa = posArq;

        //printf("\n %i", ((int)auxArgv3 - idPai) * (int)sizeof(INODE));
        
        fseek(arquivo, posMapa++, posArq);
            fread(&dadoMapa, sizeof(char), 1, arquivo);

        printf("\n posArq: %i \t idMapaI: %i     \tidMapaC: %c", posArq, idMapa, idMapa);
        printf("\n posMapa: %i \t dadMapaI: %i    \tdadMapaC: %c", posMapa, dadoMapa, dadoMapa); 
    }
    fclose(arquivo);
    return idMapa;
}