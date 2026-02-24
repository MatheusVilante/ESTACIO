#include <stdio.h>

/* Tamanho maximo para o nome do pais */
#define TAM_NOME 64

/* Opcoes do menu */
#define OP_POPULACAO 1
#define OP_AREA 2
#define OP_PIB 3
#define OP_PONTOS_TURISTICOS 4
#define OP_DENSIDADE 5

/* Estrutura da carta do Super Trunfo */
typedef struct {
    char nomePais[TAM_NOME];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica; /* valor derivado: populacao / area */
} Carta;

/* Calcula a densidade demografica. */
float calcularDensidadeDemografica(int populacao, float area) {
    if (area <= 0.0f) {
        return 0.0f;
    }
    return (float)populacao / area;
}

/* Limpa caracteres restantes da entrada ate o fim da linha. */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* consome o buffer */
    }
}

/* Mostra um resumo da carta para o usuario. */
void imprimirCartaResumo(Carta c) {
    printf("Pais: %s\n", c.nomePais);
    printf("  Populacao: %d\n", c.populacao);
    printf("  Area: %.2f\n", c.area);
    printf("  PIB: %.2f\n", c.pib);
    printf("  Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("  Densidade Demografica: %.2f\n", c.densidadeDemografica);
}

/* Le a opcao do menu com validacao de faixa e de tipo de entrada. */
int lerOpcaoMenu(void) {
    int opcao;
    int leitura;

    while (1) {
        printf("\nEscolha o atributo para comparacao:\n");
        printf("1) Populacao\n");
        printf("2) Area\n");
        printf("3) PIB\n");
        printf("4) Pontos Turisticos\n");
        printf("5) Densidade Demografica\n");
        printf("Opcao: ");

        leitura = scanf("%d", &opcao);

        if (leitura != 1) {
            printf("Entrada invalida. Digite um numero de 1 a 5.\n");
            limparBufferEntrada();
            continue;
        }

        /* Limpa o restante da linha para evitar lixo na proxima leitura. */
        limparBufferEntrada();

        if (opcao < OP_POPULACAO || opcao > OP_DENSIDADE) {
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        return opcao;
    }
}

/* Compara duas cartas conforme o atributo selecionado e mostra o resultado. */
void compararCartas(Carta a, Carta b, int opcao) {
    const char *nomeAtributo = "";
    float valorA = 0.0f;
    float valorB = 0.0f;

    switch (opcao) {
        case OP_POPULACAO:
            nomeAtributo = "Populacao";
            valorA = (float)a.populacao;
            valorB = (float)b.populacao;
            break;
        case OP_AREA:
            nomeAtributo = "Area";
            valorA = a.area;
            valorB = b.area;
            break;
        case OP_PIB:
            nomeAtributo = "PIB";
            valorA = a.pib;
            valorB = b.pib;
            break;
        case OP_PONTOS_TURISTICOS:
            nomeAtributo = "Pontos Turisticos";
            valorA = (float)a.pontosTuristicos;
            valorB = (float)b.pontosTuristicos;
            break;
        case OP_DENSIDADE:
            nomeAtributo = "Densidade Demografica";
            valorA = a.densidadeDemografica;
            valorB = b.densidadeDemografica;
            break;
        default:
            printf("Opcao invalida para comparacao.\n");
            return;
    }

    printf("\nComparacao: %s vs %s\n", a.nomePais, b.nomePais);
    printf("Atributo: %s\n", nomeAtributo);

    if (opcao == OP_POPULACAO || opcao == OP_PONTOS_TURISTICOS) {
        printf("%s: %.0f\n", a.nomePais, valorA);
        printf("%s: %.0f\n", b.nomePais, valorB);
    } else {
        printf("%s: %.2f\n", a.nomePais, valorA);
        printf("%s: %.2f\n", b.nomePais, valorB);
    }

    /*
     * Simplificacao permitida no desafio:
     * para float, usamos comparacao direta (==, <, >) sem epsilon.
     */
    if (opcao == OP_DENSIDADE) {
        /* Regra especial: menor densidade vence */
        if (valorA < valorB) {
            printf("Resultado: %s venceu! (menor densidade)\n", a.nomePais);
        } else {
            if (valorB < valorA) {
                printf("Resultado: %s venceu! (menor densidade)\n", b.nomePais);
            } else {
                printf("Resultado: Empate!\n");
            }
        }
    } else {
        /* Regra geral: maior valor vence */
        if (valorA > valorB) {
            printf("Resultado: %s venceu!\n", a.nomePais);
        } else {
            if (valorB > valorA) {
                printf("Resultado: %s venceu!\n", b.nomePais);
            } else {
                printf("Resultado: Empate!\n");
            }
        }
    }
}

int main(void) {
    int opcao;

    /* Cartas prontas (hardcoded), sem cadastro via usuario */
    Carta carta1 = {"Brasil", 203080756, 8515767.0f, 2173666.0f, 85, 0.0f};
    Carta carta2 = {"Canada", 40126954, 9984670.0f, 2140000.0f, 70, 0.0f};

    /* Calcula a densidade com base na populacao e na area */
    carta1.densidadeDemografica = calcularDensidadeDemografica(carta1.populacao, carta1.area);
    carta2.densidadeDemografica = calcularDensidadeDemografica(carta2.populacao, carta2.area);

    printf("=== SUPER TRUNFO ===\n");
    printf("\nResumo das cartas:\n");
    printf("\nCarta 1:\n");
    imprimirCartaResumo(carta1);
    printf("\nCarta 2:\n");
    imprimirCartaResumo(carta2);

    opcao = lerOpcaoMenu();
    compararCartas(carta1, carta2, opcao);

    return 0;
}
