/*
    Para compilar no terminal use:
    gcc main.c -o -lssl -lcrypto main
    para executar ./main
*/
#include <stdio.h>
//Importa arquivos pasta
#include "inode.h"                                               // 
#include "sha256.c"                                              // 
//Importa bibliote SSL
#include <openssl/evp.h>                                         // 
#include <openssl/ssl.h>                                         // 
#include <openssl/rsa.h>                                         // 
#include <openssl/x509.h>                                        // 
//Declaração função


//Função principal
int main()
{
    INODE Teste;

    
    Teste.DIRECT_BLOCKS;
    Teste.DOUBLE_INDIRECT_BLOCKS;
    Teste.INDIRECT_BLOCKS;
    Teste.IS_DIR;
    Teste.IS_USED;
    Teste.NAME;
    Teste.SIZE;
    printf("TESTES");
    printf("DIRECT_BLOCKS: %hhn", Teste.DIRECT_BLOCKS);
    printf("DOUBLE_INDIRECT_BLOCKS: %hhn", Teste.DOUBLE_INDIRECT_BLOCKS);
    printf("INDIRECT_BLOCKS: %hhn", Teste.INDIRECT_BLOCKS);
    printf("IS_DIR: %d", Teste.IS_DIR);
    printf("IS_USED: %d", Teste.IS_USED);
    printf("NAME: %s", Teste.NAME);
    printf("SIZE: %d", Teste.SIZE);


    //FILE *pathArquivo;
    //pathArquivo = "/";
    //printSha256(pathArquivo);
	return 0;	
}