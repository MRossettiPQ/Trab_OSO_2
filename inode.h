#ifndef inode_h
#define inode_h

typedef struct 
{
    unsigned char IS_USED;                                              // 0x01 se utilizado, 0x00 se livre
    unsigned char IS_DIR;                                               // 0x01 se diretorio, 0x00 se arquivo
    char NAME[10];                                                      // Nome do arquivo/dir
    char SIZE;                                                          // Tamanho do arquivo/dir em bytes
    unsigned char DIRECT_BLOCKS[3];                                     // 
    unsigned char INDIRECT_BLOCKS[3];                                   // NÃO PRECISA IMPLEMNTAR
    unsigned char DOUBLE_INDIRECT_BLOCKS[3];                            // NÃO PRECISA IMPLEMNTAR
} INODE;

#endif /* inode_h */