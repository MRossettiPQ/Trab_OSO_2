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
int main                    ()
{
    int maxLen = 50 + 2, totalCount = 0, contX = 0, contY = 0, contZ = 0, aux;
    char *tempStr = (char*)malloc(maxLen * sizeof(char));
    char cmdCC[200], auxSprintf, *questiona = (char*)malloc(sizeof(char)), pathSis[256];
    size_t  len;
    char **argv = (char**) malloc(5 * sizeof(char*));
    if(1)
    {
        do 
        {
            fgets(tempStr, maxLen, stdin);  // get chars from input buffer
            len = strlen(tempStr);
            if (tempStr[len-1] == '\n') {   // newline indicates end of string
                tempStr[len-1] = '\0';      // delete it
                len = strlen(tempStr);      // and recalc length
            }
            totalCount += (int)len;
<<<<<<< HEAD
        }while ((int)len > maxLen-1);
=======
        }while ((int)len > maxLen);
        //printf("\n Comando: %s", tempStr);
>>>>>>> parent of 0c17be2... 010720192300
        int tamEntrada = strlen(tempStr);
        for (contX = 0; contX < 5; contX++)
        {
            argv[contX] = (char*) malloc(sizeof(char));
        }
        contY = 0;
        int contAux = 0;
        sprintf (argv[contY], "%c", tempStr[2]);
        contX = 2;
        while((contY < 5) && (tempStr[contX] != '\0'))
        {  
            while((contX < tamEntrada) && (tempStr[contX] != ' ') && (tempStr[contX + 1] != '"'))
            {  
                sprintf (argv[contY], "%s%c", argv[contY], tempStr[contX + 1]);
                contX = contX + 1;
            }
<<<<<<< HEAD
            int tamFrase = strlen(argv[contY]);
            //printf("\n Frase: %s\n", argv[contY]);
=======
            //printf("\nTamanho da frase: %i", tamFrase);
            //printf("\n Frase: %s", argv[contY]);
>>>>>>> parent of 0c17be2... 010720192300
            contY = contY + 1;
            contX = contX + 1;
            sprintf (argv[contY], "%c", tempStr[contX]);
        }
    }
<<<<<<< HEAD
    //au
    //aux =  verDupDire              (argv, 0);
=======
    aux =  verDupDire              (argv, 0);
>>>>>>> parent of 0c17be2... 010720192300
    //printf("\n Decide a função");
    if(0 == strcmp(argv[0], "init"))
    {
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        //printf("\n Cria Sistema de Arquivos");
        aux = criaSistemaArquivos(argv);
        //printf("\n Sistema de Arquivos Criado\n");
        
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
<<<<<<< HEAD
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[1]);             //Gera o PATH para o arquivo desejado
        //printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
=======
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
>>>>>>> parent of 0c17be2... 010720192300
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else if(0 == strcmp(argv[0], "add"))
    {
        // ADICIONA ARQUIVO             - add "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Adiciona Arquivo ao Sistema de Arquivos");
        aux = fileSistemaArquivos(argv);
        printf("\n Arquivo Adicionado ao Sistema de Arquivos Criado\n");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
<<<<<<< HEAD
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[1]);             //Gera o PATH para o arquivo desejado
        //printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
=======
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
>>>>>>> parent of 0c17be2... 010720192300
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else if(0 == strcmp(argv[0], "addDir"))
    {
        // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Adiciona Diretorio ao Sistema de Arquivos");
        aux = direSistemaArquivos(argv); 
        printf("\n Diretorio Adicionado ao Sistema de Arquivos Criado\n");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
<<<<<<< HEAD
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[1]);             //Gera o PATH para o arquivo desejado
        //printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
=======
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\nHash: ", cmdCC);                              //Imprime o PATH do diretorio do programa
>>>>>>> parent of 0c17be2... 010720192300
        printSha256(cmdCC);                                                 //Imprime a HASH
    }    
    else if(0 == strcmp(argv[0], "sha256"))
    {
        // IMPRIME A HASH               - sha256 "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        printf("\n Imprime a HASH");
        getcwd(pathSis, sizeof(pathSis));                                   //Busca o PATH do diretorio do programa
        verificaArquivo(argv);                                              //Verifica se o .bin passado existe
        auxSprintf = sprintf(cmdCC, "%s/%s", pathSis, argv[2]);             //Gera o PATH para o arquivo desejado
        printf("\n\nPath: %s\n\nHash: ", cmdCC);                            //Imprime o PATH do diretorio do programa
        printSha256(cmdCC);                                                 //Imprime a HASH
    }
    else
    {
        printf("\nComando não reconhecido");
    }
    
    printf("\n=============FIM DO PROGRAMA=============\n\n");

	return 0;	
}


int   fileSistemaArquivos       (char** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    // ADICIONA ARQUIVO             - add "nome arquivo.bin" "Nome Arquivo para o Sistema" "Texto do arquivo"
    // ADICIONA ARQUIVO             - add fs.bin /teste.txt abcd
    int posArq = 1, idInode, idDirRaiz, sizeNome, sizeBloco, contX, aux;
    char auxHEX[10], auxArgv1, auxArgv2, auxENT[10];
    verificaArquivo(argv);                                                //Chama a verificação do arquivo .bin
    FILE *arquivo;
    arquivo = fopen(argv[1],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        posArq = posArq + 1;
        fseek(arquivo, posArq, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        //printf("\n auxArgv1: %i \t auxArgv2: %i", auxArgv1, auxArgv2);

        idInode = achaInodoLivre(argv);
        //printf("\n\tidInode: %i", idInode);
        if(idInode != 0)
        {
            posArq = 2 + retornaCeil(auxArgv1) + (idInode-1) * sizeof(INODE) + 1;
            //printf("\n\tposArq: %i", posArq);
            fseek(arquivo, posArq, SEEK_SET);
                sprintf (auxENT, "%c", 0x01);                   //IS_USED
            fwrite(&auxENT, sizeof(char), 1, arquivo); 
                sprintf (auxENT, "%c", 0x00);                   //IS_DIR
            fwrite(&auxENT, sizeof(char), 1, arquivo); 

            sizeNome = strlen(argv[3]);                         //TAMANHO NOME                
            for(contX = 1; contX < sizeNome; contX++)
            {
<<<<<<< HEAD
                idInode = achaInodoLivre(argv);
                printf("\n ADICIONA DIRETORIO\n\tidInode: %i", idInode);
                if(idInode != 0)
                {    
                    int idMB, troca;
                        char auxTroca, posicaoVetorBloco;
                        fseek(direArquivo, 0, SEEK_SET);
                        posArq = 3;

                    fseek(direArquivo, posArq++, SEEK_SET);
                        fread(&auxTroca, sizeof(char), 1, direArquivo);
                        sprintf(auxHEX, "%c", auxTroca);
                        posArq = 3;
                        posicaoVetorBloco = auxTroca;
                        auxTroca = auxTroca + 1;
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxTroca, sizeof(char), 1, direArquivo);

                    fseek(direArquivo, 0, SEEK_SET);
                        posArq = 3 + retornaCeil(auxArgv1) + ((int)sizeof(INODE) * (idInode - 1));
                        printf("\n posArq: %i", posArq);                     
                        int idMapa = buscaVetor(argv);
                        sprintf (auxENT, "%c", idMapa);  

                    fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x01);                   //IS_USED
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x01);                   //IS_DIR
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 

                    
                    sizeNome = strlen(adicionar);                             //TAMANHO NOME 
                    int contNome = 1;

                    for(contX = 1; contX < sizeNome; contX++)
                    {
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", adicionar[contX]);         //NOME DIRETORIO
                        fwrite(&auxENT, sizeof(char), 1, direArquivo);  
                    }
                    for(contX = 0; contX < (11 - sizeNome); contX++)
                    {
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x00);                   //NOME DIRETORIO
                        fwrite(&auxENT, sizeof(char), 1, direArquivo);  
                    }

                    sprintf (auxENT, "%x", sizeNome);                   //char TAMANHO NOME
                        printf("\n %s", auxHEX);
                        aux = (char)strtol(auxENT, NULL, 16);
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&aux, sizeof(int), 1, direArquivo);          //TAMANHO NOME
                    

                    //fseek(direArquivo, posArq++, SEEK_SET);       
                    //fwrite(&auxENT, sizeof(char), 1, direArquivo);
                    //sprintf (auxENT, "%i", 0x03);
                    for(contX = 0; contX < 3; contX++)                  //Bloco direto      
                    {
                        sprintf (auxENT, "%c", 0x00);
                        fseek(direArquivo, posArq++, SEEK_SET);       
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }               
                    sprintf (auxENT, "%c", 0x00);                       //Não implementado
                    for(contX = 0; contX < 3; contX++)
                    {   
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }
                    for(contX = 0; contX < 3; contX++)
                    {   
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }
                    //Atualiza Vetor de Blocos
                    posArq = 0;
                    int sizeTexto = strlen(argv[3]);                             //TAMANHO NOME 
=======
                sprintf (auxENT, "%c", argv[3][contX]);         //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);  
            }
            for(contX = 0; contX < (11 - sizeNome); contX++)
            {
                sprintf (auxENT, "%c", 0x00);                //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);  
            }
            sprintf (auxENT, "%c", sizeNome);                   //char TAMANHO NOME
            fwrite(&auxENT, sizeof(char), 1, arquivo);          //TAMANHO NOME
>>>>>>> parent of 0c17be2... 010720192300


            sizeBloco = strlen(argv[4]);                        //Tamanho conteudo arquivo 
            /*              
            for(contX = 1; contX < sizeNome; contX++)           //Conteudo arquivo   
            {
                sprintf (auxENT, "%c", argv[4][contX]);         
                fwrite(&auxENT, sizeof(char), 1, arquivo);  
            }
            for(contX = 0; contX < (4 - sizeBloco); contX++)
            {
                sprintf (auxENT, "%c", 0x00);                   //NOME DIRETORIO
                fwrite(&auxENT, sizeof(char), 1, arquivo);  
            }
            */
            
            sprintf (auxENT, "%c", 0x26); 
            for(contX = 0; contX < 3; contX++)
            {   
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
            }
            sprintf (auxENT, "%c", 0x00); 
            for(contX = 0; contX < 3; contX++)
            {   
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
            }
            for(contX = 0; contX < 3; contX++)
            {   
                fwrite(&auxENT, sizeof(char), 1, arquivo); 
            }  
        }
        posArq = 2 + retornaCeil(auxArgv1) +  auxArgv2 * sizeof(INODE);
        fseek(arquivo, posArq, SEEK_SET);
        sprintf (auxENT, "%c", idInode);    
        fwrite(&auxENT, sizeof(char), 1, arquivo);
    }
    fclose(arquivo);

    return 0;
}
int   direSistemaArquivos       (char** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
    // ADICIONA DIRETORIO           - addDir fs.bin /etc
    int posArq = 0, idInode, idDirRaiz, sizeNome, contX, aux, auxAr, idPai = 0;
    char auxHEX[10], auxArgv1, auxArgv2, auxENT[10];
    verificaArquivo(argv);                                                          //Chama a verificação do arquivo .bin
    
    FILE *direArquivo;
    direArquivo = fopen(argv[1],"r+b");
    if (direArquivo != NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    
        fseek(direArquivo, posArq++, SEEK_SET);
        fseek(direArquivo, posArq++, SEEK_SET);         
            fread(&auxArgv1, sizeof(int), 1, direArquivo);                          //Numero de Blocos
        fseek(direArquivo, posArq++, SEEK_SET); 
            fread(&auxArgv2, sizeof(int), 1, direArquivo);                          //Numero de Inodes
        //printf("\n auxArgv1: %i \t auxArgv2: %i", auxArgv1, auxArgv2);
        auxAr = (int)auxArgv2;
       
        if(0 == verDupDire(argv, 0))
        {
            idDirRaiz = posDiretorioRaiz(argv);                                         //
            printf("\n id Diretorio raiz: %i", idDirRaiz);
            if(idDirRaiz == 0x00)
            {
                idInode = achaInodoLivre(argv);
                printf("\n ADICIONA DIRETORIO\n\tidInode: %i", idInode);
                if(idInode != 0)
                {    
                    int idMB, troca;
                        char auxTroca, posicaoVetorBloco;
                        fseek(direArquivo, 0, SEEK_SET);
                        posArq = 3;

                    fseek(direArquivo, posArq++, SEEK_SET);
                        fread(&auxTroca, sizeof(char), 1, direArquivo);
                        sprintf(auxHEX, "%c", auxTroca);
                        posArq = 3;
                        posicaoVetorBloco = auxTroca;
                        auxTroca = auxTroca + 1;
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxTroca, sizeof(char), 1, direArquivo);

                    fseek(direArquivo, 0, SEEK_SET);
                        posArq = 3 + retornaCeil(auxArgv1) + ((int)sizeof(INODE) * (idInode - 1));
                        printf("\n posArq: %i", posArq);                     
                        int idMapa = buscaVetor(argv);
                        sprintf (auxENT, "%c", idMapa);  

                    fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x01);                   //IS_USED
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x01);                   //IS_DIR
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 

                    
                    sizeNome = strlen(argv[2]);                             //TAMANHO NOME 
                    int contNome = 1;

                    for(contX = 1; contX < sizeNome; contX++)
                    {
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", argv[2][contX]);         //NOME DIRETORIO
                        fwrite(&auxENT, sizeof(char), 1, direArquivo);  
                    }
                    for(contX = 0; contX < (11 - sizeNome); contX++)
                    {
                        fseek(direArquivo, posArq++, SEEK_SET);
                        sprintf (auxENT, "%c", 0x00);                   //NOME DIRETORIO
                        fwrite(&auxENT, sizeof(char), 1, direArquivo);  
                    }

                    sprintf (auxENT, "%x", sizeNome);                   //char TAMANHO NOME
                        printf("\n %s", auxHEX);
                        aux = (char)strtol(auxENT, NULL, 16);
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&aux, sizeof(int), 1, direArquivo);          //TAMANHO NOME
                    

                    //fseek(direArquivo, posArq++, SEEK_SET);       
                    //fwrite(&auxENT, sizeof(char), 1, direArquivo);
                    //sprintf (auxENT, "%i", 0x03);
                    for(contX = 0; contX < 3; contX++)                  //Bloco direto      
                    {
                        sprintf (auxENT, "%c", 0x00);
                        fseek(direArquivo, posArq++, SEEK_SET);       
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }               
                    sprintf (auxENT, "%c", 0x00);                       //Não implementado
                    for(contX = 0; contX < 3; contX++)
                    {   
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }
                    for(contX = 0; contX < 3; contX++)
                    {   
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxENT, sizeof(char), 1, direArquivo); 
                    }
                    //Atualiza Vetor de Blocos
                    posArq = 0;
                        idMapa = buscaIdMapa(argv, idDirRaiz);
                        fseek(direArquivo, 0, SEEK_SET);
                        posArq = 4 + retornaCeil((int)auxArgv1) + (int)sizeof(INODE) * (int)auxArgv2 + idMapa ;
                        printf("\n\n idMapa: %i - posArq: %i", idMapa, posArq);
                        //printf("\n (int)sizeof(INODE) * idDirRaiz: %i", (int)sizeof(INODE) * idDirRaiz);
                        sprintf (auxENT, "%c", idInode-1);                       //Não implementado
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&auxENT, sizeof(char), 1, direArquivo);

                    //Atualiza Bloco Pai
                    posArq = 0;
                        //idMapa = buscaIdMapa(argv, idDirRaiz);
                        fseek(direArquivo, 0, SEEK_SET);
                        posArq = 3 + retornaCeil((int)auxArgv1) + 13 * (idPai + 1);
                        //printf("\n\n idMapa: %i - posArq: %i", idMapa, posArq);
                        //printf("\n (int)sizeof(INODE) * idDirRaiz: %i", (int)sizeof(INODE) * idDirRaiz);
                        //sprintf (auxENT, "%c", idInode-1);                       //Não implementado
                        fseek(direArquivo, posArq++, SEEK_SET);
                        fwrite(&posicaoVetorBloco, sizeof(char), 1, direArquivo);
                }
            }
        } 
    }
    //fclose(direArquivo);

    return 0;
}





int     achaInodoLivre          (char** argv)                           //Acha o INODO livre
{
    char auxArgv1, auxArgv2, auxArgv3;
	int idInode = 0, posArq = 1, contX = 0, contY = 0, aux;
    FILE *arquivo;
    arquivo = fopen(argv[1],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq++, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        //printf("\n auxArgv1: %i - auxArgv2: %i", auxArgv1, auxArgv2);

        posArq = 3 + retornaCeil(auxArgv1); // + auxArgv2 * sizeof(INODE);
        fseek(arquivo, posArq++, SEEK_SET);
        fread(&aux, sizeof(int), 1, arquivo); 
    
        //printf("\n posArq2: %i \t- auxArgv3: %i", posArq, auxArgv3);
        idInode = 0; 
        contY = 0;
        for(contX = 0; contX < auxArgv2; contX++)
        {   
            //printf("\n posArq3: %i \t- auxArgv3: %i\n contX: %d \t- contY: %d ", posArq, auxArgv3, idInode, contY);
            if ((aux == 0x00) || (aux == 0))
            {
                //printf("\n SAINDO: %d", idInode + 1);
                fclose(arquivo);
                return idInode + 1;                                            //Indice do diretorio raiz
            }
            posArq = 5 + retornaCeil(auxArgv1) + (int)sizeof(INODE) * (contX + 1);
            
            fseek(arquivo, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(int), 1, arquivo);
            idInode = idInode + 1; 
            contY = contY + 1;
        }
    }
    fclose(arquivo);
    printf("\n Sem espaço no INODO");
    return 0;  
}
int   criaSistemaArquivos       (char** argv)                           //Cria o sistema de arquivos dentro do arquivo .bin
{
    int aux;
    verificaArquivo(argv);                                                //Chama a verificação do arquivo .bin

    FILE *arquivo;                        
    arquivo = fopen(argv[1],"r+b");
    if (arquivo!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        // CRIA SISTEMA DE ARQUIVO      - init "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
        // init fs.bin 5 10 2
        INFOINODE novoINFO;
        int pos = 0, posD, trocaBaseTB, trocaBaseNB, trocaBaseNI, trocaBase, contInode, contMapaBit, contBloco, contX;
        float ceilMax = 0, auxCeil;
        char auxHex, auxSize;

        fseek(arquivo, pos, SEEK_SET);                                          //Entra no arquivo na primeira posição
        //Transforma a char do argv em Hexadecimal

        trocaBaseTB = (int)strtol(argv[2], NULL, 10);                           //Troca base do Tamanho do Bloco
        novoINFO.tamBloco = trocaBaseTB;
        

        trocaBaseNB = (int)strtol(argv[3], NULL, 10);                           //Troca base do Numero de Blocos
        novoINFO.numBloco = trocaBaseNB;

        trocaBaseNI = (int)strtol(argv[4], NULL, 10);                           //Troca base do Numero de Inodes
        novoINFO.numInode = trocaBaseNI;
        fwrite(&novoINFO.tamBloco, sizeof(char), 1, arquivo);   
        fwrite(&novoINFO.numBloco, sizeof(char), 1, arquivo);   
        fwrite(&novoINFO.numInode, sizeof(char), 1, arquivo);  

        ceilMax = retornaCeil((int)trocaBaseNB);
        //printf("\n Tamanho do Bloco: %i\n Numero de Bloco: %i\n Numero de Inodes: %i\n Numero Ceil: %f", trocaBaseTB, trocaBaseNB, trocaBaseNI, ceilMax);

        novoINFO.mapaBits   = (char*)malloc((int)ceilMax * (int)sizeof(char));                    //Aloca o Mapa de Bits com N/8 posições

        for(contMapaBit = 0; contMapaBit < ceilMax; contMapaBit++)
        {  
            novoINFO.mapaBits[contMapaBit]    =   (char)strtol("0", NULL, 10);          //Recebe o mapa de bits
            //printf("\nMapa de Bits[%i]: %X, %i", contMapaBit, novoINFO.mapaBits[contMapaBit], novoINFO.mapaBits[contMapaBit]);
            fwrite(&novoINFO.mapaBits[contMapaBit], sizeof(char), 1, arquivo);   
        }
        novoINFO.vetorInode = (INODE*)malloc(trocaBaseNI * (int)sizeof(INODE));              //Aloca o Vetor de Inode com I posições
        for(contInode = 0; contInode < trocaBaseNI; contInode++)
        {   
            //printf("\n Dentro do for para o Inode[%i]", contInode+1);
            novoINFO.vetorInode[contInode].IS_USED  =   0x00;
            fwrite(&novoINFO.vetorInode[contInode].IS_USED, sizeof(char), 1, arquivo);  

            novoINFO.vetorInode[contInode].IS_DIR   =   0x00;
            fwrite(&novoINFO.vetorInode[contInode].IS_DIR, sizeof(char), 1, arquivo);   
            
            for(contX = 0; contX < 10; contX++)
            {   
                novoINFO.vetorInode[contInode].NAME[contX] = 0x00;
                fwrite(&novoINFO.vetorInode[contInode].NAME[contX], sizeof(char), 1, arquivo);   
            }
           
            novoINFO.vetorInode[contInode].SIZE = 0x00;
            fwrite(&novoINFO.vetorInode[contInode].SIZE, sizeof(char), 1, arquivo);    

            for(contX = 0; contX < 3; contX++)                                          //Blocos diretos
            {   
                novoINFO.vetorInode[contInode].DIRECT_BLOCKS[contX] =  0x00;
                fwrite(&novoINFO.vetorInode[contInode].DIRECT_BLOCKS[contInode], sizeof(char), 1, arquivo); 
            }
            for(contX = 0; contX < 3; contX++)                                          //Blocos indiretos
            {   
                novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[contX] = 0x00;
                fwrite(&novoINFO.vetorInode[contInode].INDIRECT_BLOCKS[contInode], sizeof(char), 1, arquivo); 
            }
            for(contX = 0; contX < 3; contX++)                                          //Blocos duplamente indiretos
            {   
                novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[contX] = 0x00;
                fwrite(&novoINFO.vetorInode[contInode].DOUBLE_INDIRECT_BLOCKS[contInode], sizeof(char), 1, arquivo); 
            }  
        }
        novoINFO.indDir                 =   0x00;                                       //Posiciona o indice do diretorio raiz
        fwrite(&novoINFO.indDir, sizeof(char), 1, arquivo);  
        trocaBase = trocaBaseTB * trocaBaseNB;  
        novoINFO.vetorBloco = (char*)malloc(trocaBase * (int)sizeof(char));                  //Aloca o Vetor de Blocos com T * N Posições
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
    aux = addPastaRaiz(argv);                                              //inicia diretorio /

    return 0;
}
double   retornaCeil            (double numInodes)                      //Retorna a ceil para o N/8 numero de Blocos
{
    double divide = numInodes/8, result;
    result = ceil(divide);
    //printf("\nEntrada: %f\nDivide: %f\nCeil: %f", numInodes, divide, result);         //Debug da função

    return result;
}
int     addPastaRaiz            (char** argv)                           //Adiciona a pasta raiz
{
    // ADICIONA DIRETORIO           - addDir "nome arquivo.bin" "bytes do bloco" "Qt. de Blocos" "Qt. Inodes"
    // ADICIONA DIRETORIO           - addDir fs.bin /etc
    int posArq = 0, trocaBaseNB, trocaBaseTB, trocaBaseNI, contX; 
    char auxENT[10];

    verificaArquivo(argv);                                                      //Chama a verificação do arquivo .bin
    FILE *arquivoRaiz;
    arquivoRaiz = fopen(argv[1],"r+b");
    if (arquivoRaiz != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        trocaBaseTB = (int)strtol(argv[2], NULL, 10);                                   //Converte entrada
        trocaBaseNB = (int)strtol(argv[3], NULL, 10);                                   //Converte entrada
        trocaBaseNI = (int)strtol(argv[4], NULL, 10);                                   //Converte entrada
        posArq = 3;                                                                      //Atualiza posição de entrada
            sprintf (auxENT, "%c", 0x00);                                                   //Atualiza usado
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);
        posArq = posArq + (int)retornaCeil(trocaBaseNB) -1;
        sprintf (auxENT, "%c", 0x01);                                                   //Atualiza usado
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);
        sprintf (auxENT, "%c", 0x01);                                                   //Atualiza pasta?
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);
        sprintf (auxENT, "%c", 0x2f);                                                   //Atualiza nome diretorio
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);
        for(contX = 0; contX < 9; contX++)
        {
            sprintf (auxENT, "%c", 0x00);                                               //Atualiza o resto do nome do diretorio
            fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
                fwrite(&auxENT, sizeof(char), 1, arquivoRaiz); 
        }
        sprintf (auxENT, "%c", 0x01);                                                   //Atualiza diretorio
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);

        sprintf (auxENT, "%c", 0x00);                                                   //Atualiza bloco direto
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz); 
        for(contX = 0; contX < 2; contX++)
        {
            sprintf (auxENT, "%c", 0x00);                                               //Atualiza bloco direto
            fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
                fwrite(&auxENT, sizeof(char), 1, arquivoRaiz); 
        }
        for(contX = 0; contX < 3; contX++)
        {
            sprintf (auxENT, "%c", 0x00);                                               //Atualiza bloco indireto
            fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
                fwrite(&auxENT, sizeof(char), 1, arquivoRaiz); 
        }
        for(contX = 0; contX < 3; contX++)
        {
            sprintf (auxENT, "%c", 0x00);                                               //Atualiza bloco duplamente indireto
            fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
                fwrite(&auxENT, sizeof(char), 1, arquivoRaiz); 
        } 

        posArq = 3 + (int)retornaCeil(trocaBaseNB) + trocaBaseNI * (int)sizeof(INODE);  //Atualiza posição de entrada
        sprintf (auxENT, "%c", 0x00);                                                   //Atualiza usado
        fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
            fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);        
        sprintf (auxENT, "%c", 0x00);                                                   //Vetor de blocos
        //fseek(arquivoRaiz, posArq++, SEEK_SET);                                           
        //   fwrite(&auxENT, sizeof(char), 1, arquivoRaiz);
    }
    fclose(arquivoRaiz);
    return 0;
}
int     posDiretorioRaiz        (char** argv)                           //Função que retorna Diretorio Raiz
{	
    char auxArgv1, auxArgv2, auxHEX[10];
	int idInode = 0, posArq = 1, auxId;
    FILE *arquivo;
    arquivo = fopen(argv[1],"r+b");
    if (arquivo != NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(arquivo, posArq++, SEEK_SET);
        fread(&auxArgv1, sizeof(int), 1, arquivo); 
        fseek(arquivo, posArq++, SEEK_SET);
        fread(&auxArgv2, sizeof(int), 1, arquivo); 
        posArq = posArq + retornaCeil(auxArgv1) + (int)auxArgv2 * sizeof(INODE);
            printf("\n TESTE");
        //printf("\nposArq: %i - Ceil: %i", posArq, (int)retornaCeil(auxArgv1));
        fseek(arquivo, posArq++, SEEK_SET);
            fread(&idInode, sizeof(int), 1, arquivo);
        sprintf (auxHEX, "%c", idInode);
            printf("\n TESTE");
        auxId = (int)strtol(auxHEX, NULL, 16); 

        //printf("\nauxArgv1: %i - auxArgv2: %i - posArq: %i - idInode: %i - auxHEX: %s", auxArgv1, auxArgv2, posArq, idInode, auxHEX);
        
        //return (int)strtol(auxHEX, NULL, 10); 
        return auxId;                 
    }
}
void    verificaArquivo         (char** argv)                           //Função para detectar o arquivo .bin passado como argumento, e cria-lo caso não exista
{    
    char cmdCC[50];
    FILE *novoArquivo;  
    novoArquivo = fopen(argv[1], "r");
    if (novoArquivo != NULL)                                                        //VERIFICA ARQUIVO .bin NO DIRETORIO
    { 
        //printf("\n Arquivo no diretorio");
    }
    else
    {
        //printf("\n Arquivo inexistente");                                                    //Convoca o comando para o sistema
        int aux = sprintf(cmdCC, "touch %s", argv[1]);
        system(cmdCC);
        //printf("\n Arquivo gerado\n\n");
    }
}
int     buscaBloco              (char** argv, int idPai, int idBloc)
{
    int posArq = 0, troca,troca2;
    char idMapa,auxArgv1, auxArgv2, auxArgv3, auxTroca[10];
    FILE *arquivoBuscaBloco;

    arquivoBuscaBloco = fopen(argv[1],"r+b");
    if (arquivoBuscaBloco != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    
        //printf("\n idPai: %i \t idBloc: %i ", idPai, idBloc);
        fseek(arquivoBuscaBloco, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(char), 1, arquivoBuscaBloco); 
        fseek(arquivoBuscaBloco, posArq++, SEEK_SET);
            fread(&auxArgv2, sizeof(char), 1, arquivoBuscaBloco); 
        fseek(arquivoBuscaBloco, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(char), 1, arquivoBuscaBloco);

        posArq = 16 + retornaCeil((int)auxArgv2) + idBloc + (idPai * (int)sizeof(INODE));
        //printf("\n posArq: %i ", posArq);
        //printf("\n retornaCeil: %i", (int)retornaCeil((int)auxArgv2));
        //printf("\n posArq: %i \t idMapa: %c \t idMapa: %c", posArq, idMapa, idMapa);
        fseek(arquivoBuscaBloco, posArq++, SEEK_SET);
            fread(&idMapa, sizeof(int), 1, arquivoBuscaBloco);
        sprintf (auxTroca, "%i", idMapa);
        troca = (int)strtol(auxTroca, NULL, 16); 
        //printf("\n posArq: %i ", posArq);
        troca2 = (int)strtol(auxTroca, NULL, 10); 
        //printf("\n troca: %i \t troca: %c \t troca: %c \t\n troca2: %c \t troca2: %i \t troca2: %i", troca, troca, troca, troca2, troca2, troca2);
        //printf("\n posArq: %i \t idMapa: %c \t idMapa: %c \t decMapa: %i\t decMapa: %c", posArq, idMapa, idMapa, troca, troca);
    }
    fclose(arquivoBuscaBloco);
    return troca2;
}
int     buscaMapa               (char** argv, int idPai, int idMapa)
{
    int posArq = 0, troca, troca2;
    char dadoMapa,auxArgv1, auxArgv2, auxArgv3, auxTroca[10];
    FILE *arquivoBuscaMapa;

    arquivoBuscaMapa = fopen(argv[1],"r+b");
    if (arquivoBuscaMapa != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    
        //printf("\n idPai: %i \t idBloc: %i ", idPai, idBloc);
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(char), 1, arquivoBuscaMapa); 
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv2, sizeof(char), 1, arquivoBuscaMapa); 
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(char), 1, arquivoBuscaMapa);

        posArq = 4 + retornaCeil((int)auxArgv2) + ((int)auxArgv3 * (int)sizeof(INODE)) + idMapa;

        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&dadoMapa, sizeof(int), 1, arquivoBuscaMapa);
        sprintf (auxTroca, "%i", dadoMapa);
        troca = (int)strtol(auxTroca, NULL, 10); 
        troca2 = (int)strtol(auxTroca, NULL, 16); 
        //printf("\n troca: %i \t troca: %c \t troca: %c \t\n troca2: %c \t troca2: %i \t troca2: %i", troca, troca, troca, troca2, troca2, troca2);
    }
    fclose(arquivoBuscaMapa);
    return troca;
}
int     verDupDire              (char** argv, int  idPai)
{
    int tamEntrada = strlen(argv[2]), tamanhoRaiz, idInode = 0, posArq = 0, contX = 1, contY;
    char auxRaiz[tamEntrada], auxRaizRaiz[tamEntrada], auxArquivo[tamEntrada], adicionar[tamEntrada], lido[10];
    char carac, auxArgv1, auxArgv2, auxArgv3, auxHEX[10], auxENT[10];
    int existe = 0;
    FILE *verDup;
    verDup = fopen(argv[1],"r+b");
    if (verDup!=NULL)                                                          //VERIFICA ARQUIVO .bin NO DIRETORIO
    {
        fseek(verDup, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(int), 1, verDup);
        fseek(verDup, posArq++, SEEK_SET);         
            fread(&auxArgv2, sizeof(int), 1, verDup);                           //Numero de Blocos
        fseek(verDup, posArq++, SEEK_SET); 
            fread(&auxArgv3, sizeof(int), 1, verDup);                           //Numero de Inode
        
        posArq = posArq + retornaCeil(auxArgv2) + 2;
        int conAgv1 = auxArgv1, conAgv2 = auxArgv2, conAgv3 = auxArgv3;
        sprintf (auxRaizRaiz, "%c", argv[2][0]);
        while((contX < tamEntrada) && (argv[2][contX] != '/'))              //RAIZRAIZ
        {   
            sprintf (auxRaizRaiz, "%s%c", auxRaizRaiz, argv[2][contX]);
            contX = contX + 1;
        }
        sprintf (auxRaiz, "%c", argv[2][contX]);
        contX = contX + 1;
        while((contX < tamEntrada) && (argv[2][contX] != '/'))               //RAIZ
        {   
            sprintf (auxRaiz, "%s%c", auxRaiz, argv[2][contX]);
            contX = contX + 1;
        }
        if(strlen(auxRaiz) == 0)                                                        //RAIZRAIZ deve ser adicionado
        {
            strcpy(adicionar, auxRaizRaiz);
            idPai = 0;
        }
        else                                                                            //RAIZ deve ser adicionado
        {
            strcpy(adicionar, auxRaiz);

        }

        posArq = 0;
        posArq = 3 + retornaCeil(auxArgv2) + 4;
        contX = 0;
        int idBloc = 0, idMapa = 0 , idNode;
        char carac;
        int nauxArgv3 = auxArgv3;
        for(contY = 0; contY < nauxArgv3; contY++)
        {
            //printf("\n PROXIMO INODE");
            contX = 0;
            sprintf(lido, "/");
            do
            {
                fseek(verDup, posArq++, SEEK_SET); 
                fread(&carac, sizeof(char), 1, verDup);
                //printf("\n carac: %c", carac);
                sprintf(lido, "%s%c", lido, carac);
                contX = contX + 1;
            }while ((contX < 10) && (carac != 0x00));
            if(0 == strcmp(adicionar, lido))
            {
                existe = 1;
                printf("\n Pasta existe\t idPai: %i", idPai);
                return existe;
            }
            
            contY = contY + 1;
            fseek(verDup, 0, SEEK_SET);
            idMapa = buscaBloco(argv, idPai, idBloc);
            idNode = buscaMapa(argv, idPai, idMapa);


            posArq = posArq + 10 + (10 - contX) * (int)idNode;
        }
        printf("\n Não existe");
    }
    fclose(verDup);
    return existe;
}
int     buscaIdMapa             (char** argv, int idPai)
{
    int posArq = 0, troca, troca2, contY = 0, livre = 1, idMapa = 0;
    char dadoMapa,auxArgv1, auxArgv2, auxArgv3, auxTroca[10];
    FILE *arquivoBuscaMapa;

    arquivoBuscaMapa = fopen(argv[1],"r+b");
    if (arquivoBuscaMapa != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    

            //printf("\n idPai: %i \t idBloc: %i ", idPai, idBloc);
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&auxArgv1, sizeof(char), 1, arquivoBuscaMapa); 
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&auxArgv2, sizeof(char), 1, arquivoBuscaMapa); 
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&auxArgv3, sizeof(char), 1, arquivoBuscaMapa);
        
        while((contY < 3) && (livre != 0))
        {
            contY = contY + 1;
            idMapa = buscaBloco (argv, idPai, contY);

            fseek(arquivoBuscaMapa, 0, SEEK_SET);
            posArq = 4 + retornaCeil((int)auxArgv2) + ((int)auxArgv3 * (int)sizeof(INODE)) + idMapa;
            
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&dadoMapa, sizeof(char), 1, arquivoBuscaMapa);
            sprintf (auxTroca, "%i", dadoMapa);
            

            troca = (int)strtol(auxTroca, NULL, 10); 
            troca2 = (int)strtol(auxTroca, NULL, 16); 
            //printf("\n troca: %i \t troca: %c \t troca: %c \t\n troca2: %c \t troca2: %i \t troca2: %i", troca, troca, troca, troca2, troca2, troca2);
            if(dadoMapa == 0)
            {
                printf("\n MAPA DE BITS VAZIO, idMapa: %i", idMapa);
                livre = 0;
            }
        }
        if(contY < 3)
        {   
            printf("\nTeste");
            char auxENT[10];
            int auxMapaAdd;
            posArq = 3 + 1;
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&auxMapaAdd, sizeof(char), 1, arquivoBuscaMapa);

            posArq = 4 + retornaCeil((int)auxArgv2) + 13 + contY;
            sprintf (auxENT, "%c", auxMapaAdd + 1);                       //Não implementado
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                    fwrite(&auxENT, sizeof(char), 1, arquivoBuscaMapa);
        }
    }
    fclose(arquivoBuscaMapa);
    return idMapa;
}
int     buscaVetor              (char** argv)
{
    int posArq = 0, troca, troca2, contY = 0, livre = 1, idMapa = 0;
    char auxArgv1, auxArgv2, auxArgv3, auxTroca[10], dadoMapa = 0;
    FILE *arquivoBuscaMapa;

    arquivoBuscaMapa = fopen(argv[1],"r+b");
    if (arquivoBuscaMapa != NULL)                                                            //VERIFICA ARQUIVO .bin NO DIRETORIO
    {    
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv1, sizeof(char), 1, arquivoBuscaMapa); 
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv2, sizeof(char), 1, arquivoBuscaMapa); 
        fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
            fread(&auxArgv3, sizeof(char), 1, arquivoBuscaMapa);
        
        while((contY < (int)retornaCeil(auxArgv2)) && (dadoMapa < 15))
        {
            fseek(arquivoBuscaMapa, posArq++, SEEK_SET);
                fread(&dadoMapa, sizeof(char), 1, arquivoBuscaMapa);
            sprintf (auxTroca, "%i", dadoMapa);
            

            troca = (int)strtol(auxTroca, NULL, 10); 
            troca2 = (int)strtol(auxTroca, NULL, 16); 
            //printf("\n troca: %i \t troca: %c \t troca: %c \t\n troca2: %c \t troca2: %i \t troca2: %i", troca, troca, troca, troca2, troca2, troca2);
            contY = contY + 1;
        }
    }
    fclose(arquivoBuscaMapa);
    return troca;   
}