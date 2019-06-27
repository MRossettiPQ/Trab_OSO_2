#ifndef biblioteca_h
#define biblioteca_h

    //
    #include <stdio.h>
    #include <string.h>                                                 //strlen
    #include <stdlib.h>                                                 //strlen
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

#endif /* biblioteca_h */