#ifndef biblioteca_h
#define biblioteca_h

    //
    #define _POSIX_SOURCE
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>                                                 //strlen
    #include <stdlib.h>                                                 //strlen
    #include  <math.h>
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

    #define B_POR_INODE   	5
    #define N_INODE       	10
    #define B_LIVRES   		N_INODE
    #define B_DADOS     	N_INODE
    #define ARQUIVO			0
    #define DIRETORIO		1


#endif /* biblioteca_h */