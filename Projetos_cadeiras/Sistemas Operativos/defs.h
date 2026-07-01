// defs.h -- definições comuns
#ifndef DEFS_H
#define DEFS_H

#include <sys/types.h>    // para pid_t

// nomes dos FIFOs
#define SERVER_FIFO          "/tmp/server_fifo"
#define CLIENT_FIFO_TEMPLATE "/tmp/client_fifo_%d"

// códigos das operações
#define OP_ADD      1   // indexar documento
#define OP_QUERY    2   // consultar meta-info
#define OP_DELETE   3   // apagar meta-info
#define OP_LINES    4   // contar linhas com keyword
#define OP_SEARCH   5   // procurar keyword em todos docs
#define OP_SHUTDOWN 6   // terminar servidor

// limites
#define MAX_DOCS      100
#define MAX_TITLE     200
#define MAX_AUTHORS   200
#define MAX_PATH      64
#define MAX_KEYWORD   64
#define MAX_RESULTS  512  // string para resultados

// estrutura única para pedido e resposta
typedef struct {
    int   op;                 // operação
    pid_t pid;                // PID do cliente
    int   key;                // usado em QUERY, DELETE, LINES
    int   year;               // usado em ADD
    int   count;              // resposta para OP_LINES
    int   nprocs;             // usado em OP_SEARCH
    char  title[MAX_TITLE];   // ADD
    char  authors[MAX_AUTHORS];// ADD
    char  path[MAX_PATH];     // ADD
    char  keyword[MAX_KEYWORD];// LINES/SEARCH
    char  results[MAX_RESULTS];// resposta para OP_SEARCH
} Msg;

#endif // DEFS_H