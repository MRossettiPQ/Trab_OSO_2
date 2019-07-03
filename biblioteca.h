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
    void    verificaArquivo         (char** argv);
    
    int     criaSistemaArquivos     (char** argv);
    int     fileSistemaArquivos     (char** argv);
    
    int     posDiretorioRaiz        (char** argv);
    int     achaInodoLivre          (char** argv);
    int     posInode                (char** argv);
    
    int     direSistemaArquivos     (char** argv);
    int     addPastaRaiz            (char** argv);
    int     buscaIdPai              (char** argv);
    int     verDupDire              (char** argv);
    int     buscaBloco              (char** argv, int idPai, int idBloc);
    int     buscaMapa               (char** argv, int idPai, int idMapa);

    double  retornaCeil             (double numInodes);

    typedef struct  
    {
        char                tamBloco;
        char                numBloco;
        char                numInode;
        char                *mapaBits;
        INODE               *vetorInode;
        char                indDir;
        char                *vetorBloco;
    } INFOINODE;

#endif /* biblioteca_h */