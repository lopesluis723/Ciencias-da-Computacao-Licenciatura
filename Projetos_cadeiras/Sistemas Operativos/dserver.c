/* dserver.c -- servidor com cache FIFO, FIFO por PID e persistência em disco */

#include <stdio.h>      // printf, fprintf, FILE*, fopen, fscanf, fprintf
#include <stdlib.h>     // exit, atoi
#include <string.h>     // memset, strncpy, strcmp
#include <fcntl.h>      // open, O_RDONLY, O_WRONLY
#include <unistd.h>     // write, read, close, fork, execlp, _exit, mkfifo, unlink
#include <sys/stat.h>   // mkfifo permissions
#include <sys/wait.h>   // wait, waitpid
#include "defs.h"      // operações, Msg, nomes de FIFO, limites

#define DBFILE "meta.db"  // nome do ficheiro de persistência

// --- Estrutura que representa um documento em memória ---
// 'deleted' == 1 significa que a meta-informação foi removida
typedef struct {
    int key;                          // identificador único
    char title[MAX_TITLE];            // título do documento
    char authors[MAX_AUTHORS];        // autores do documento
    int year;                         // ano de publicação
    char path[MAX_PATH];              // caminho para o ficheiro de texto
    int deleted;                      // flag: 0=ativo, 1=removido
} Doc;

// --- Variáveis globais ---
static Doc docs[MAX_DOCS];            // array principal de documentos em memória
static int doc_count = 0;             // quantos documentos estão armazenados
static int next_key = 1;              // próximo identificador (incremental)

// --- Cache FIFO de índices em 'docs' ---
static int cache_limit = 0;           // máximo de entradas na cache
static int cache_idx[MAX_DOCS];       // armazena índices em 'docs'
static int cache_count = 0;           // quantas entradas há atualmente na cache

// --- Função find_doc ---
// Procura o índice em 'docs' que corresponde a 'key'.
// Retorna o índice ou -1 se não encontrar ou se estiver 'deleted'.
static int find_doc(int key) {
    for (int i = 0; i < doc_count; i++) {
        if (docs[i].key == key && docs[i].deleted == 0) // se chave coincidir e não removido
            return i;
    }
    return -1;
}

// --- Função cache_add ---
// Insere um índice 'idx' na cache, evitando duplicados.
// Se a cache estiver cheia (cache_count == cache_limit), evict o mais antigo (posição 0).
static void cache_add(int idx) {
    // verifica duplicado
    for (int i = 0; i < cache_count; i++) {
        if (cache_idx[i] == idx)
            return; // já está na cache
    }
    if (cache_count < cache_limit) {
        // há espaço: insere no fim
        cache_idx[cache_count++] = idx;
    } else if (cache_limit > 0) {
        // cache cheia: remove o primeiro (FIFO)
        for (int j = 1; j < cache_count; j++) {
            cache_idx[j-1] = cache_idx[j]; // shift left
        }
        cache_idx[cache_count-1] = idx;  // novo no fim
    }
}

// --- Função cache_remove ---
// Remove um índice 'idx' da cache, deslocando elementos para manter compactação.
static void cache_remove(int idx) {
    for (int i = 0; i < cache_count; i++) {
        if (cache_idx[i] == idx) {
            // remove slot i e shift remaining
            for (int j = i+1; j < cache_count; j++) {
                cache_idx[j-1] = cache_idx[j];
            }
            cache_count--; // diminui contagem
            return;
        }
    }
}

// --- Função load_persistence ---
// Lê 'meta.db' linha a linha, recria 'docs[]' e popula cache com entradas não removidas.
static void load_persistence() {
    FILE *f = fopen(DBFILE, "r");  // abre em modo leitura
    if (!f) return;                  // se não existir, retorna

    // lê até EOF ou até esgotar espaço em 'docs'
    while (!feof(f) && doc_count < MAX_DOCS) {
        int key, year, deleted;
        char title[MAX_TITLE], authors[MAX_AUTHORS], path[MAX_PATH];
        
        // fscanf usa delimitadores '|' e '' para ler campos
        int n = fscanf(f,
            "%d|%199[^|]|%199[^|]|%d|%63[^|]|%d\n",
            &key, title, authors, &year, path, &deleted);
        if (n == 6) {  // leu todos os campos corretamente
            // preenche struct em docs
            docs[doc_count].key     = key;
            strncpy(docs[doc_count].title,   title,   MAX_TITLE);
            strncpy(docs[doc_count].authors, authors, MAX_AUTHORS);
            docs[doc_count].year    = year;
            strncpy(docs[doc_count].path,    path,    MAX_PATH);
            docs[doc_count].deleted = deleted;

            // se não removido, adiciona à cache
            if (!deleted) cache_add(doc_count);

            // atualiza next_key para evitar colisões
            if (key >= next_key) next_key = key + 1;

            doc_count++;  // incrementa contagem de documentos
        }
    }
    fclose(f);  // fecha o ficheiro
}

// --- Função append_persistence ---
// Anexa uma linha de metainformação no final de 'meta.db'.
static void append_persistence(const Doc *d) {
    FILE *f = fopen(DBFILE, "a"); // abre em modo append
    if (!f) return;
    fprintf(f, "%d|%s|%s|%d|%s|%d\n",
        d->key, d->title, d->authors, d->year, d->path, d->deleted);
    fclose(f);
}

// --- Função send_response ---
// Envia struct Msg 'resp' para FIFO do cliente identificado por 'pid'.
static void send_response(const Msg *resp, pid_t pid) {
    char fifo[64];
    // monta nome de FIFO baseado no pid do cliente
    snprintf(fifo, sizeof(fifo), CLIENT_FIFO_TEMPLATE, pid);
    int fd = open(fifo, O_WRONLY); // abre para escrita
    if (fd < 0) return;            // erro: provavelmente cliente não criou FIFO
    write(fd, resp, sizeof(*resp));
    close(fd);
}

int main(int argc, char *argv[]) {
    // --- leitura de argumento cache_size ---
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <folder> <cache_size>\n", argv[0]);
        exit(1);
    }
    cache_limit = atoi(argv[2]);  // converte segundo argumento em inteiro

    // --- inicialização das FIFOs ---
    mkfifo(SERVER_FIFO, 0666);    // cria FIFO do servidor (ignora se já existente)

    // --- carrega dados persistidos ---
    load_persistence();
    int active = 0;
    for (int i = 0; i < doc_count; i++)
        if (!docs[i].deleted) active++;
    printf("[dserver] iniciado: %d docs (ativos: %d), cache_limit=%d, next_key=%d\n",    // Isto é importante alterar ou descobrir se ponho 3 docs e a informação dos ativos ou simplesmento ponho 2 docs e ignoro a informacao dos ativos
        doc_count, active, cache_limit, next_key);

    // --- loop principal de atendimento ---
    while (1) {
        Msg msg, resp;
        memset(&resp, 0, sizeof(resp)); // zera toda a struct de resposta
        int in = open(SERVER_FIFO, O_RDONLY); // abre FIFO para leitura (bloqueia)
        if (in < 0) { perror("open servidor"); exit(1); }
        // lê o pedido completo
        if (read(in, &msg, sizeof(msg)) != sizeof(msg)) {
            close(in); continue; // leitura incompleta, ignora
        }
        close(in);
        resp.op = msg.op;           // setar tipo de operação na resposta

        // --- OP_ADD: indexar documento ---
        if (msg.op == OP_ADD) {
            Doc d;
            d.key   = next_key++;      // atribui chave incremental
            strncpy(d.title,   msg.title,   MAX_TITLE);
            strncpy(d.authors, msg.authors, MAX_AUTHORS);
            d.year  = msg.year;
            strncpy(d.path,    msg.path,    MAX_PATH);
            d.deleted = 0;
            docs[doc_count] = d;       // armazena novo doc em memória
            append_persistence(&d);    // grava em disco
            cache_add(doc_count);      // coloca na cache
            resp.key = d.key;          // retorna chave ao cliente
            doc_count++;
        }

        // --- OP_QUERY: consulta metainformação ---
        else if (msg.op == OP_QUERY) {
            int idx = find_doc(msg.key);
            if (idx >= 0) {
                cache_add(idx);         // move para cache (hot)
                Doc *d = &docs[idx];
                resp.key = d->key;
                strcpy(resp.title,   d->title);
                strcpy(resp.authors, d->authors);
                resp.year = d->year;
                strcpy(resp.path,    d->path);
            }
        }

        // --- OP_DELETE: remove metainformação ---
        else if (msg.op == OP_DELETE) {
            int idx = find_doc(msg.key);
            if (idx >= 0) {
                docs[idx].deleted = 1;  // marca removido
                cache_remove(idx);      // retira da cache
                // regrava todo o DBFILE para refletir remoção
                FILE *f = fopen(DBFILE, "w");
                for (int i = 0; i < doc_count; i++) {
                    Doc *d = &docs[i];
                    fprintf(f, "%d|%s|%s|%d|%s|%d\n",
                        d->key, d->title, d->authors, d->year, d->path, d->deleted);
                }
                fclose(f);
                resp.key = msg.key;
            }
        }

        // --- OP_LINES: contar linhas com keyword usando pipe+grep ---
        else if (msg.op == OP_LINES) {
            int idx = find_doc(msg.key);
            if (idx >= 0) {
                cache_add(idx);
                int p[2]; pipe(p);     // cria pipe: p[0]=read, p[1]=write
                if (fork() == 0) {
                    close(p[0]);       // filho não lê
                    dup2(p[1], STDOUT_FILENO); // redireciona stdout para pipe
                    execlp("grep","grep","-c", msg.keyword,
                           docs[idx].path, NULL);
                    _exit(1);          // se falhar
                }
                close(p[1]);          // pai não escreve
                char buf[32];
                int n = read(p[0], buf, sizeof(buf)-1);
                buf[n] = '\0';
                resp.count = atoi(buf);// converte contagem
                close(p[0]);
                wait(NULL);           // espera filho terminar
            }
        }

         // --- OP_SEARCH: pesquisa concorrente ---
         else if (msg.op == OP_SEARCH) {
            // Inicia a lista de resultados como "["
            char list[MAX_RESULTS] = "[";
            int first = 1;          // controla vírgula antes de elementos
            int launched = 0;       // quantos docs já “lançámos” para grep
            int processed = 0;      // quantos slots (docs) já contabilizados
            int active = 0;         // quantos filhos grep estão ativos
            pid_t pids[MAX_DOCS];   // PIDs dos filhos pendentes
            int keys_arr[MAX_DOCS]; // keys correspondentes a cada PID

            // 1) Loop principal: até termos tentado todos os docs
            while (processed < doc_count) {
                // 1.1) Lança até msg.nprocs filhos simultâneos
                while (active < msg.nprocs && launched < doc_count) {
                    if (!docs[launched].deleted) {
                        pid_t c = fork();
                        if (c == 0) {
                            // filho executa grep silencioso
                            execlp("grep", "grep", "-q",
                                   msg.keyword, docs[launched].path, NULL);
                            _exit(1);
                        }
                        // no pai, guarda PID e a key correspondente
                        pids[active]     = c;
                        keys_arr[active] = docs[launched].key;
                        active++;
                    }
                    launched++;
                    processed++;
                }

                // 1.2) Espera que qualquer um desses filhos termine
                int st;
                pid_t w = wait(&st);

                // 1.3) Encontra o índice i cujo pids[i] == w
                int i;
                for (i = 0; i < active; i++) {
                    if (pids[i] == w) break;
                }

                // 1.4) Se encontrou a keyword (exit code 0), anexa a key
                if (WIFEXITED(st) && WEXITSTATUS(st) == 0) {
                    if (!first) {
                        strcat(list, ",");
                    }
                    first = 0;
                    char tmp[16];
                    snprintf(tmp, sizeof(tmp), "%d", keys_arr[i]);
                    strcat(list, tmp);
                }

                // 1.5) Remove o slot i do pool, compactando os arrays
                for (int j = i; j < active - 1; j++) {
                    pids[j]     = pids[j+1];
                    keys_arr[j] = keys_arr[j+1];
                }
                active--;
            }

            // 2) Drena quaisquer filhos que ainda estejam ativos
            while (active > 0) {
                int st;
                pid_t w = wait(&st);
                int i;
                for (i = 0; i < active; i++) {
                    if (pids[i] == w) break;
                }
                if (WIFEXITED(st) && WEXITSTATUS(st) == 0) {
                    if (!first) {
                        strcat(list, ",");
                    }
                    first = 0;
                    char tmp[16];
                    snprintf(tmp, sizeof(tmp), "%d", keys_arr[i]);
                    strcat(list, tmp);
                }
                for (int j = i; j < active - 1; j++) {
                    pids[j]     = pids[j+1];
                    keys_arr[j] = keys_arr[j+1];
                }
                active--;
            }

            // Fecha o colchete e copia para resp.results
            strcat(list, "]");
            strcpy(resp.results, list);
        }

        // --- OP_SHUTDOWN: termina servidor ---
        else if (msg.op == OP_SHUTDOWN) {
            send_response(&resp, msg.pid);
            unlink(SERVER_FIFO);          // remove FIFO
            printf("[dserver] a terminar...\n");
            exit(0);
        }

        // envio final de resposta para qualquer op
        send_response(&resp, msg.pid);
    }
    return 0;
}
//TESTE A VER SE FOI