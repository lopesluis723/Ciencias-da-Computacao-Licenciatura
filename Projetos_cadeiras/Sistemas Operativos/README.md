# Trabalho-de-SO
Desenvolvimento de um sistema cliente-servidor em C utilizando FIFOs (named pipes) para comunicação entre processos. O servidor mantém um índice de documentos em memória com persistência em ficheiro, permitindo adicionar, consultar e remover documentos. O sistema inclui ainda funcionalidades de contagem de linhas e pesquisa de palavras-chave em paralelo através da criação de processos (`fork`), bem como um mecanismo simples de cache FIFO para otimizar o acesso aos dados.

