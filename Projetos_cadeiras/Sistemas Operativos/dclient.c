/* dclient.c -- cliente simples com FIFO por PID */

#include <stdio.h>      // printf, fprintf
#include <stdlib.h>     // exit, atoi
#include <string.h>     // strcmp, strcpy, memset
#include <fcntl.h>      // open, O_* flags
#include <unistd.h>     // getpid, write, read, close, unlink, mkfifo
#include <sys/stat.h>   // mkfifo permissions
#include "defs.h"      // definições de Msg, OP_*, FIFO names

// usage: exibe instruções de uso e encerra com código de erro
static void usage(const char *p) {
    fprintf(stderr,
      "Uso:\n"
      "  %s -a \"title\" \"authors\" year path\n"
      "  %s -c key\n"
      "  %s -d key\n"
      "  %s -l key keyword\n"
      "  %s -s keyword nprocs\n"
      "  %s -f\n", p,p,p,p,p,p);
    exit(1);
}

int main(int argc, char *argv[]) {
    // Verifica número mínimo de argumentos
    if (argc < 2)
        usage(argv[0]);  // sai se falta argumento

    Msg msg;
    memset(&msg, 0, sizeof(msg));  // zera todos os campos
    msg.pid = getpid();            // armazena o PID do cliente no pedido

    // Interpretação dos argumentos para montar o pedido 'msg'
    if (strcmp(argv[1], "-a") == 0 && argc == 6) {
        // OP_ADD: indexar documento
        msg.op = OP_ADD;
        strcpy(msg.title,   argv[2]);      // título
        strcpy(msg.authors, argv[3]);      // autores
        msg.year = atoi(argv[4]);          // ano, string->int
        strcpy(msg.path,    argv[5]);      // caminho do ficheiro
    }
    else if (strcmp(argv[1], "-c") == 0 && argc == 3) {
        // OP_QUERY: consultar meta-info
        msg.op = OP_QUERY;
        msg.key = atoi(argv[2]);           // chave do documento
    }
    else if (strcmp(argv[1], "-d") == 0 && argc == 3) {
        // OP_DELETE: apagar meta-info
        msg.op = OP_DELETE;
        msg.key = atoi(argv[2]);
    }
    else if (strcmp(argv[1], "-l") == 0 && argc == 4) {
        // OP_LINES: contar linhas com keyword
        msg.op = OP_LINES;
        msg.key = atoi(argv[2]);
        strcpy(msg.keyword, argv[3]);
    }
    else if (strcmp(argv[1], "-s") == 0 && argc == 4) {
        // OP_SEARCH: procurar keyword em todos docs, nprocs paralelo
        msg.op = OP_SEARCH;
        strcpy(msg.keyword, argv[2]);      // termo de busca
        msg.nprocs = atoi(argv[3]);        // número de processos
    }
    else if (strcmp(argv[1], "-f") == 0 && argc == 2) {
        // OP_SHUTDOWN: terminar servidor
        msg.op = OP_SHUTDOWN;
    }
    else {
        // caso inválido
        usage(argv[0]);
    }

    // --- Preparação do FIFO único para este cliente ---
    char client_fifo[64];
    // monta nome: /tmp/client_fifo_<pid>
    snprintf(client_fifo, sizeof(client_fifo),
             CLIENT_FIFO_TEMPLATE, msg.pid);
    // cria o FIFO se não existir
    mkfifo(client_fifo, 0666);

    // --- Envio do pedido ao servidor ---
    // garante que o FIFO do servidor existe
    mkfifo(SERVER_FIFO, 0666);
    // abre em escrita (bloqueia até servidor abrir leitura)
    int sfd = open(SERVER_FIFO, O_WRONLY);
    write(sfd, &msg, sizeof(msg));  // envia toda a struct Msg
    close(sfd);

    // --- Receção da resposta ---
    Msg resp;
    int cfd = open(client_fifo, O_RDONLY);   // lê do FIFO do cliente
    read(cfd, &resp, sizeof(resp));         // lê a struct de resposta
    close(cfd);
    unlink(client_fifo);                    // apaga o FIFO do cliente

    // --- Impressão do resultado conforme a operação ---
    switch (resp.op) {
      case OP_ADD:
        printf("Document %d indexed\n", resp.key);
        break;
      case OP_QUERY:
        printf("Title: %s\nAuthors: %s\nYear: %d\nPath: %s\n",
               resp.title, resp.authors, resp.year, resp.path);
        break;
      case OP_DELETE:
        printf("Index entry %d deleted\n", resp.key);
        break;
      case OP_LINES:
        printf("%d\n", resp.count);
        break;
      case OP_SEARCH:
        printf("%s\n", resp.results);
        break;
      case OP_SHUTDOWN:
        printf("Server is shutting down\n");
        break;
    }

    return 0;
}
