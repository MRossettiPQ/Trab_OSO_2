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

//Função principal
int main                    (char argc, char ** argv)
{
    FILE* arqDisco;
    char cmdCC[90], auxSprintf, *questiona = (char*)malloc(sizeof(char)), pathSis[256];;
    int aux;
    //printf("\nResposta: %s", questiona);

    //printf("\n Decide a função");
    if(0 == strcmp(argv[1], "init"))
    {
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        //printf("\n Cria Sistema de Arquivos");
        aux = criaSistemaArquivos(argc, argv);
        //printf("\n Sistema de Arquivos Criado\n");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else if(0 == strcmp(argv[1], "add"))
    {
        // ADICIONA ARQUIVO             - add "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Adiciona Arquivo ao Sistema de Arquivos");
        aux = fileSistemaArquivos(argc, argv);
        printf("\n Arquivo Adicionado ao Sistema de Arquivos Criado\n");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else if(0 == strcmp(argv[1], "addDir"))
    {
        // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        //printf("\n Adiciona Diretorio ao Sistema de Arquivos");
        aux = direSistemaArquivos(argc, argv);
        //printf("\n Diretorio Adicionado ao Sistema de Arquivos Criado\n");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }    
    else if(0 == strcmp(argv[1], "sha256"))
    {
        // IMPRIME A HASH               - sha256 "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Imprime a HASH");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        verificaArquivo(argc, argv);                                        //Verifica se o .bin passado existe
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\n\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    printf("\n=============FIM DO PROGRAMA=============\n\n");

	return 0;	
}
int     achaInodoLivre      (char argc, char ** argv)
{
    char auxArgv1, auxArgv2, auxArgv3;
	int idInode = 0, posArq = 1, contX = 0, contY = 0;
    FILE *arquivo;
    arquivo = fopen(argv[2],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        posArq = posArq + 1;
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        //printf("\n auxArgv1: %i - auxArgv2: %i", auxArgv1, auxArgv2);

        posArq = 3 + retornaCeil(auxArgv1); // + auxArgv2 * sizeof(INODE);

        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv3, sizeof(int), 1, arquivo); 
    
        //printf("\n posArq2: %i \t- auxArgv3: %i", posArq, auxArgv3);
        idInode = 0; 
        contY = 0;
        for(contX = 0; contX < auxArgv2; contX++)
        {   
            //printf("\n posArq3: %i \t- auxArgv3: %i\n contX: %d \t- contY: %d ", posArq, auxArgv3, idInode, contY);
            if (auxArgv3 == 0x00)
            {
                printf("\n SAINDO: %d", idInode + 1);
                fclose(arquivo);
                return idInode + 1;                                            //Indice do diretorio raiz
            }
            posArq = 5 + retornaCeil(auxArgv1) + (int)sizeof(INODE) * (contY + 1);
            
            fseek(arquivo, posArq, SEEK_SET);
            fread(&auxArgv3, sizeof(int), 1, arquivo);
            idInode = idInode + 1; 
            contY = contY + 1;
        }
    }
    fclose(arquivo);
    printf("\n Sem espaço no INODO");
    return 0;  
}
int     posDiretorioRaiz    (char argc, char ** argv)
{	
    char auxArgv1, auxArgv2, auxHEX[10];
	int idInode = 0, posArq = 1;
    FILE *arquivo;
    arquivo = fopen(argv[2],"r+b");
    if (arquivo != NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        posArq = posArq + 1;
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        posArq = posArq + retornaCeil(auxArgv1) + auxArgv2 * sizeof(INODE);
        //printf("\nposArq: %i - Ceil: %i", posArq, (int)retornaCeil(auxArgv1));
        fseek(arquivo, posArq, SEEK_SET);
        fread(&idInode, sizeof(int), 1, arquivo);
        //sprintf (auxHEX, "%c", idInode);

        //printf("\nauxArgv1: %i - auxArgv2: %i - posArq: %i - idInode: %i - auxHEX: %s", auxArgv1, auxArgv2, posArq, idInode, auxHEX);
        
        //return (int)strtol(auxHEX, NULL, 10); 
        return idInode;                 
    }
}
void    verificaArquivo     (char argc, char ** argv)                           //Função para detectar o arquivo .bin passado como argumento, e cria-lo caso não exista
{    
    char cmdCC[40];
    FILE *arquivo;  
    arquivo = fopen(argv[2], "r");
    if (arquivo != NULL)                                                        //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        //printf("\n Arquivo no diretorio");
    }
    else
    {
        //printf("\n Arquivo inexistente");                                                    //Convoca o comando para o sistema
        int n = sprintf(cmdCC, "touch %s", argv[2]);
        system(cmdCC);
        //printf("\n Arquivo gerado\n\n");
    }
}
int   direSistemaArquivos   (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
    // ADICIONA DIRETORIO           - addDir fs.bin /etc
    int posArq = 1, idInode, idDirRaiz, sizeNome, contX, aux;
    char auxHEX[10], auxArgv1, auxArgv2, auxENT[10];
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[2],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        posArq = posArq + 1;
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        //printf("\n auxArgv1: %i \t auxArgv2: %i", auxArgv1, auxArgv2);

        idDirRaiz = posDiretorioRaiz(argc, argv);
        printf("\n id Diretorio raiz: %i", idDirRaiz);
        if(idDirRaiz == 0)
        {
            printf("\n Sem diretorio raiz");
            idInode = achaInodoLivre(argc, argv);
            //printf("\n\tidInode: %i", idInode);
            if(idInode != 0)
            {
                posArq = 2 + retornaCeil(auxArgv1) + (idInode-1) * sizeof(INODE) + 1;
                //printf("\n\tposArq: %i", posArq);
                fseek(arquivo, posArq, SEEK_SET);
                    sprintf (auxENT, "%c", 0x01);               //IS_USED
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
                    sprintf (auxENT, "%c", 0x01);               //IS_DIR
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
                    sprintf (auxENT, "%c", 0x2f);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                    sprintf (auxENT, "%c", 0x00);               //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                
                sizeNome = strlen(auxENT);                      //TAMANHO NOME
                sprintf (auxENT, "%c", sizeNome);               //char TAMANHO NOME
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //TAMANHO NOME

                    sprintf (auxENT, "%c", 0x02);               
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKINDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKDUPLAMENTENDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);

                

            }
            posArq = 2 + retornaCeil(auxArgv1) +  auxArgv2 * sizeof(INODE);
            fseek(arquivo, posArq, SEEK_SET);
            sprintf (auxENT, "%c", idInode);    
            fwrite(&auxENT, sizeof(char), 1, arquivo);
        }        
        else
        {
            idInode = achaInodoLivre(argc, argv);
            printf("\n ADICIONA DIRETORIO\n\tidInode: %i", idInode);
            if(idInode != 0)
            {
                posArq = 2 + retornaCeil(auxArgv1) + sizeof(INODE) * (idInode - 1);
                fseek(arquivo, posArq, SEEK_SET);
                    sprintf (auxENT, "%c", 0x01);               //IS_USED
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
                    sprintf (auxENT, "%c", 0x01);               //IS_DIR
                fwrite(&auxENT, sizeof(char), 1, arquivo); 

                sizeNome = strlen(argv[3]);                      //TAMANHO NOME                
                for(contX = 1; contX < sizeNome; contX++)
                {
                    sprintf (auxENT, "%c", argv[3][contX]);      //NOME DIRETORIO
                    fwrite(&auxENT, sizeof(char), 1, arquivo);  
                }
                for(contX = 0; contX < (11 - sizeNome); contX++)
                {
                    sprintf (auxENT, "%c", 0x00);                //NOME DIRETORIO
                    fwrite(&auxENT, sizeof(char), 1, arquivo);  
                }

                sprintf (auxENT, "%x", sizeNome);               //char TAMANHO NOME
                printf("\n %s", auxHEX);
                aux = (int)strtol(auxENT, NULL, 10);

                fwrite(&aux, sizeof(char), 1, arquivo);      //TAMANHO NOME

                    sprintf (auxENT, "%c", 0x02);               
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKINDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);      //BLOCKDUPLAMENTENDIRETO
                fwrite(&auxENT, sizeof(char), 1, arquivo);
                fwrite(&auxENT, sizeof(char), 1, arquivo);
            }
        }
    }
    fclose(arquivo);

    return 0;
}
int   fileSistemaArquivos   (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    // ADICIONA ARQUIVO             - add "nome arquivo.bin" "Nome Arquivo para o Sistema" "Texto do arquivo"
    // ADICIONA ARQUIVO             - add fs.bin /teste.txt abcd
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[2],"rb+");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        //strcpy(newNode.name,argv[4]);
    }
    else
    {

    }
    fclose(arquivo);

    return 0;
}
int   criaSistemaArquivos   (char argc, char ** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    int aux;
    verificaArquivo(argc, argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;                        
    arquivo = fopen(argv[2],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        // init fs.bin 5 10 2
        INFOINODE novoINFO;
        int pos = 0, posD, trocaBaseTB, trocaBaseNB, trocaBaseNI, trocaBase, contInode, contMapaBit, contBloco;
        float ceilMax = 0, auxCeil;
        char auxHex, auxSize;

        fseek(arquivo, pos, SEEK_SET);                                          //Entra no arquivo na primeira posição
        //Transforma a char do argv em Hexadecimal
        trocaBaseTB = (int)strtol(argv[3], NULL, 10);                           //Troca base do Tamanho do Bloco
        novoINFO.tamBloco = trocaBaseTB;

        trocaBaseNB = (int)strtol(argv[4], NULL, 10);                           //Troca base do Numero de Blocos
        novoINFO.numBloco = trocaBaseNB;

        trocaBaseNI = (int)strtol(argv[5], NULL, 10);                           //Troca base do Numero de Inodes
        novoINFO.numInode = trocaBaseNI;
        fwrite(&novoINFO.tamBloco, sizeof(char), 1, arquivo);   
        fwrite(&novoINFO.numBloco, sizeof(char), 1, arquivo);   
        fwrite(&novoINFO.numInode, sizeof(char), 1, arquivo);  

        ceilMax = retornaCeil((double)strtol(argv[4], NULL, 10));
        //printf("\n Tamanho do Bloco: %i\n Numero de Bloco: %i\n Numero de Inodes: %i\n Numero Ceil: %f", trocaBaseTB, trocaBaseNB, trocaBaseNI, ceilMax);
        
        novoINFO.mapaBits   = (char*)malloc(ceilMax * sizeof(char));                    //Aloca o Mapa de Bits com N/8 posições
        for(contMapaBit = 0; contMapaBit < ceilMax; contMapaBit++)
        {  
            novoINFO.mapaBits[contMapaBit]    =   (char)strtol("0", NULL, 10);          //Recebe o mapa de bits
            //printf("\nMapa de Bits[%i]: %X, %i", contMapaBit, novoINFO.mapaBits[contMapaBit], novoINFO.mapaBits[contMapaBit]);
            fwrite(&novoINFO.mapaBits[contMapaBit], sizeof(char), 1, arquivo);   
        }
        novoINFO.vetorInode = (INODE*)malloc(trocaBaseNI * sizeof(INODE));              //Aloca o Vetor de Inode com I posições
        for(contInode = 0; contInode < trocaBaseNI; contInode++)
        {   
            //printf("\n Dentro do for para o Inode[%i]", contInode+1);
            novoINFO.vetorInode[contInode].IS_USED  =   0x00;
            fwrite(&novoINFO.vetorInode[contInode].IS_USED, sizeof(char), 1, arquivo);  

            novoINFO.vetorInode[contInode].IS_DIR   =   0x00;
            fwrite(&novoINFO.vetorInode[contInode].IS_DIR, sizeof(char), 1, arquivo);   
            
            
            //strcpy(novoINFO.vetorInode[contInode].NAME, "TESTE NOME");
            
            novoINFO.vetorInode[contInode].NAME[0] = 0x00;
            novoINFO.vetorInode[contInode].NAME[1] = 0x00;
            novoINFO.vetorInode[contInode].NAME[2] = 0x00;
            novoINFO.vetorInode[contInode].NAME[3] = 0x00;
            novoINFO.vetorInode[contInode].NAME[4] = 0x00;
            novoINFO.vetorInode[contInode].NAME[5] = 0x00;
            novoINFO.vetorInode[contInode].NAME[6] = 0x00;
            novoINFO.vetorInode[contInode].NAME[7] = 0x00;
            novoINFO.vetorInode[contInode].NAME[8] = 0x00;
            novoINFO.vetorInode[contInode].NAME[9] = 0x00;
            /* */
            fwrite(&novoINFO.vetorInode[contInode].NAME, 10, 1, arquivo);   
           
            novoINFO.vetorInode[contInode].SIZE = 0x00;
            fwrite(&novoINFO.vetorInode[contInode].SIZE, sizeof(char), 1, arquivo);    

            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[1] = 0x00;
            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[2] = 0x00;
            novoINFO.vetorInode[contInode].DIRECT_BLOCKS[3] = 0x00;
            fwrite(&novoINFO.vetorInode[contInode].DIRECT_BLOCKS[1], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].DIRECT_BLOCKS[2], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].DIRECT_BLOCKS[3], sizeof(char), 1, arquivo); 

            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[1] = 0x00;
            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[2] = 0x00;
            novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[3] = 0x00;
            fwrite(&novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[1], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[2], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[3], sizeof(char), 1, arquivo); 


            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[1] = 0x00;
            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[2] = 0x00;
            novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[3] = 0x00;
            fwrite(&novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[1], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[2], sizeof(char), 1, arquivo); 
            fwrite(&novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[3], sizeof(char), 1, arquivo); 
            
            //printf("\nNome: %s - Tamanho: %c", novoINFO.vetorInode[contInode].NAME, novoINFO.vetorInode[contInode].SIZE);
        }
        novoINFO.indDir                 =   0x00;                                       //Posiciona o indice do diretorio raiz
        fwrite(&novoINFO.indDir, sizeof(char), 1, arquivo);  
        trocaBase = trocaBaseTB * trocaBaseNB;  
        novoINFO.vetorBloco = (char*)malloc(trocaBase * sizeof(char));                  //Aloca o Vetor de Blocos com T * N Posições
        for(contBloco = 0; contBloco < (trocaBaseNI * trocaBaseTB); contBloco++)
        {
            novoINFO.vetorBloco[contBloco]  =  0x00;//(int)strtol("3", NULL, 10);       //Recebe o vetor de bloco
            fwrite(&novoINFO.vetorBloco[contBloco], sizeof(char), 1, arquivo);
        }
    }
    else
    {
        printf("\n Arquivo não foi encontrado \n");
    }
    fclose(arquivo);
    aux = direSistemaArquivos(argc, argv);

    return 0;
}
double   retornaCeil        (double numInodes)
{
    double divide = numInodes/8, result;
    result = ceil(divide);
    //printf("\nEntrada: %f\nDivide: %f\nCeil: %f", numInodes, divide, result);         //Debug da função

    return result;
}