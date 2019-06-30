#ifndef biblioteca_h
#define biblioteca_h

    //
    #define _POSIX_SOURCE
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>                                                 //strlen
    #include <stdlib.h>                                                 //strlen
    #include <math.h>
    //
    #include <sys/types.h>
    #include <sys/socket.h>
    //Importa bibliote SSL
    #include <openssl/evp.h>                                            // 
    #include <openssl/ssl.h>                                            // 
    #include <openssl/rsa.h>                                            // 
    #include <openssl/x509.h>                                           //
    //Importa arquivos pasta 
    #include "inode.h"                                                  // 
    #include "sha256.c"                                                 //
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
        char                tamBloco;
        char                numBloco;
        char                numInode;
        char                mapaBits[2];
        INODE               vetorInode[2];
        char                indDir;
        char                vetorBloco[10];
    } INFOINODE;

    #define B_POR_INODE   	5
    #define N_INODE       	10
    #define B_LIVRES   		N_INODE
    #define B_DADOS     	N_INODE
    #define ARQUIVO			0
    #define DIRETORIO		1


#endif /* biblioteca_h */