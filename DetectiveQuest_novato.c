#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para representar um cômodo/sala na mansão
typedef struct sala {
    char nome[50];
    struct sala *esquerda;
    struct sala *direita;
} Sala;

// Função que cria, de forma dinâmica, uma sala com nome.
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    // Verifica se a alocação foi bem-sucedida
    if (nova == NULL) {
        perror("Falha na alocacao de memoria");
        exit(EXIT_FAILURE);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função que permite a navegação do jogador pela árvore.
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVoce esta na %s.\n", atual->nome);

        // caso não tenha mais caminhos
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Voce chegou ao fim da exploracao. Nao ha mais caminhos.\n");
            break;
        }

        printf("Escolha um caminho: (e) esquerda, (d) direita, (s) sair: ");

        if (scanf(" %c", &escolha) != 1) {
             // Tratamento de erro
             printf("Erro ao ler a entrada. Encerrando.\n");
             break;
        }

        if (escolha == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao ha caminho a esquerda!\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Nao ha caminho a direita!\n");
        } else if (escolha == 's') {
            printf("Exploracao encerrada.\n");
            break;
        } else {
            printf("Opção invalida.\n");
        }
    }
}


int main() {
    // Criação das salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* escritorio = criarSala("Escritorio");
    Sala* porao = criarSala("Porao");
    Sala* quarto = criarSala("Quarto de Hospedes");

    // Conectando os cômodos

    // Nível 1: Hall de Entrada
    hall->esquerda = porao; // Porão é o fim do caminho
    hall->direita = salaEstar;

    // Nível 2: Sala de Estar
    salaEstar->direita = cozinha;
    salaEstar->esquerda = hall; // Volta para o Hall

    // Nível 3: Cozinha
    cozinha->direita = biblioteca;
    cozinha->esquerda = salaEstar; // Volta para a Sala de Estar

    // Nível 4: Biblioteca
    biblioteca->direita = escritorio;
    biblioteca->esquerda = cozinha; // Volta para a Cozinha

    // Nível 5: Escritório
    escritorio->direita = quarto;
    escritorio->esquerda = biblioteca; // Volta para a Biblioteca

    // Nível 6: Quarto de Hospedes
    quarto->direita = jardim; // Jardim(fim do caminho)
    quarto->esquerda = escritorio; // Volta para o Escritório

    printf("=== Detective Quest ===\nBem-vindo a mansao misteriosa!\n");
    explorarSalas(hall);



    return 0;
}