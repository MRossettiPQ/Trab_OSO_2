#include "biblioteca.h"

int main(char argc, char ** argv)
{
    verificaArquivo(argc, argv);
    FILE *arquivo; 
    INFOINODE novoINFO;
    int pos = 0, posD, trocaBaseTB, trocaBaseNB, trocaBaseNI, trocaBase, contInode, contMapaBit, contBloco;
    float ceilMax = 0, auxCeil;
    char auxHex, auxSize;
    arquivo = fopen(argv[2],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, pos, SEEK_SET);                                          //Entra no arquivo na primeira posição
        //Transforma a char do argv em Hexadecimal
        trocaBaseTB = (int)strtol(argv[3], NULL, 10);                           //Troca base do Tamanho do Bloco
        novoINFO.tamBloco = trocaBaseTB;

        trocaBaseNB = (int)strtol(argv[4], NULL, 10);                           //Troca base do Numero de Blocos
        novoINFO.numBloco = trocaBaseNB;

        trocaBaseNI = (int)strtol(argv[5], NULL, 10);                           //Troca base do Numero de Inodes
        novoINFO.numInode = trocaBaseNI;

        ceilMax = retornaCeil((double)strtol(argv[4], NULL, 10));
        printf("\n Tamanho do Bloco: %i\n Numero de Bloco: %i\n Numero de Inodes: %i\n Numero Ceil: %f", trocaBaseTB, trocaBaseNB, trocaBaseNI, ceilMax);
        
        //printf("\n Primeiro Malloc: mapaBits");
        novoINFO.mapaBits   = malloc(ceilMax * sizeof(char));                   //Aloca o Mapa de Bits com N/8 posições
        //printf("\n Segundo Malloc: vetorBloco");
        trocaBase = trocaBaseTB * trocaBaseNB;
        novoINFO.vetorBloco = (char*)malloc(trocaBase * sizeof(char));          //Aloca o Vetor de Blocos com T * N Posições
        //printf("\n Terceiro Malloc: vetorInode");
        novoINFO.vetorInode = (INODE*)malloc(trocaBaseNI * sizeof(INODE));      //Aloca o Vetor de Inode com I posições
        
        for(contMapaBit = 0; contMapaBit < ceilMax; contMapaBit++)
        {  
            novoINFO.mapaBits[contMapaBit]    =   (char)strtol("10", NULL, 10); //Recebe o mapa de bits
            printf("\nMapa de Bits: %X, %i", novoINFO.mapaBits[contMapaBit], novoINFO.mapaBits[contMapaBit]);
        }
        for(contInode = 0; contInode < trocaBaseNI; contInode++)
        {   
            printf("\n Dentro do for para o Inode[%i]", contInode+1);
            novoINFO.vetorInode[contInode].IS_USED  =   0x01;
            novoINFO.vetorInode[contInode].IS_DIR   =   0x01;

            strcpy(novoINFO.vetorInode[contInode].NAME, "TESTE NOME");
           
            novoINFO.vetorInode[contInode].SIZE = 0x78;

            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[1] = 0x74;
            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[2] = 0x74;
            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[3] = 0x74;

            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[1] = 0x70;
            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[2] = 0x70;
            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[3] = 0x70;

            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[1] = 0x67;
            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[2] = 0x67;
            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[3] = 0x67;
            printf("\nNome: %s, Tamanho Aux: %d, Tamanho: %d", novoINFO.vetorInode[contInode].NAME, auxSize, novoINFO.vetorInode[contInode].SIZE);
        }
        novoINFO.indDir                 =   0x2b;                                   //Posiciona o indice do diretorio raiz
        for(contBloco = 0; contBloco < (trocaBaseNI * trocaBaseTB); contBloco++)
        {
            novoINFO.vetorBloco[contBloco]  =  0x26;//(int)strtol("3", NULL, 10);                               //Recebe o vetor de bloco
        }
        fwrite(&novoINFO, sizeof(INFOINODE), 1, arquivo);    
        printf("\n");
    }
	return 0;	
}
double   retornaCeil             (double numInodes)
{
    double divide = numInodes/8, result;
    result = ceil(divide);
    //printf("\nEntrada: %f\nDivide: %f\nCeil: %f", numInodes, divide, result);         //Debug da função

    return result;
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