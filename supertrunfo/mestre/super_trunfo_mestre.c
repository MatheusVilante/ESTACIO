#include <stdio.h>

#define TAM_NOME 64

enum Atributo {
    ATR_NENHUM = 0,
    ATR_POPULACAO = 1,
    ATR_AREA = 2,
    ATR_PIB = 3,
    ATR_PONTOS_TURISTICOS = 4,
    ATR_DENSIDADE_DEMOGRAFICA = 5
};

typedef struct {
    char nomePais[TAM_NOME];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica;
} Carta;

void limparBufferEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Consome o restante da entrada */
    }
}

int lerOpcaoInteiraSegura(void) {
    int opcao;

    while (1) {
        if (scanf("%d", &opcao) == 1) {
            limparBufferEntrada();
            return opcao;
        }

        printf("Entrada invalida. Digite um numero inteiro.\n");
        limparBufferEntrada();
        printf("Opcao: ");
    }
}

void calcularDensidade(Carta *c) {
    if (c->area > 0.0f) {
        c->densidadeDemografica = (float)c->populacao / c->area;
    } else {
        c->densidadeDemografica = 0.0f;
    }
}

const char *nomeAtributo(int atributo) {
    switch (atributo) {
        case ATR_POPULACAO:
            return "Populacao";
        case ATR_AREA:
            return "Area";
        case ATR_PIB:
            return "PIB";
        case ATR_PONTOS_TURISTICOS:
            return "Pontos Turisticos";
        case ATR_DENSIDADE_DEMOGRAFICA:
            return "Densidade Demografica";
        default:
            return "Atributo desconhecido";
    }
}

int regraInvertida(int atributo) {
    return atributo == ATR_DENSIDADE_DEMOGRAFICA;
}

float obterValorAtributo(const Carta *c, int atributo) {
    switch (atributo) {
        case ATR_POPULACAO:
            return (float)c->populacao;
        case ATR_AREA:
            return c->area;
        case ATR_PIB:
            return c->pib;
        case ATR_PONTOS_TURISTICOS:
            return (float)c->pontosTuristicos;
        case ATR_DENSIDADE_DEMOGRAFICA:
            return c->densidadeDemografica;
        default:
            return 0.0f;
    }
}

/*
 * Retorna o valor convertido para a soma final.
 * Regra normal: usa o proprio valor.
 * Regra invertida (densidade): multiplica por -1 para que
 * "maior soma vence" continue valido mesmo com "menor vence".
 */
float obterValorParaSoma(const Carta *c, int atributo) {
    float valorBase = obterValorAtributo(c, atributo);
    float fator = regraInvertida(atributo) ? -1.0f : 1.0f;
    return valorBase * fator;
}

void imprimirCartasResumo(Carta a, Carta b) {
    printf("\n=== Cartas Cadastradas ===\n");

    printf("\nCarta 1 - %s\n", a.nomePais);
    printf("Populacao: %d\n", a.populacao);
    printf("Area: %.2f\n", a.area);
    printf("PIB: %.2f\n", a.pib);
    printf("Pontos Turisticos: %d\n", a.pontosTuristicos);
    printf("Densidade Demografica: %.2f\n", a.densidadeDemografica);

    printf("\nCarta 2 - %s\n", b.nomePais);
    printf("Populacao: %d\n", b.populacao);
    printf("Area: %.2f\n", b.area);
    printf("PIB: %.2f\n", b.pib);
    printf("Pontos Turisticos: %d\n", b.pontosTuristicos);
    printf("Densidade Demografica: %.2f\n", b.densidadeDemografica);
}

void imprimirMenuAtributos(int atributoBloqueado) {
    printf("\nEscolha um atributo:\n");

    if (atributoBloqueado != ATR_POPULACAO) {
        printf("1) Populacao\n");
    }
    if (atributoBloqueado != ATR_AREA) {
        printf("2) Area\n");
    }
    if (atributoBloqueado != ATR_PIB) {
        printf("3) PIB\n");
    }
    if (atributoBloqueado != ATR_PONTOS_TURISTICOS) {
        printf("4) Pontos Turisticos\n");
    }
    if (atributoBloqueado != ATR_DENSIDADE_DEMOGRAFICA) {
        printf("5) Densidade Demografica\n");
    }

    printf("Opcao: ");
}

int escolherAtributo(int atributoBloqueado) {
    int opcao;

    while (1) {
        imprimirMenuAtributos(atributoBloqueado);
        opcao = lerOpcaoInteiraSegura();

        switch (opcao) {
            case ATR_POPULACAO:
            case ATR_AREA:
            case ATR_PIB:
            case ATR_PONTOS_TURISTICOS:
            case ATR_DENSIDADE_DEMOGRAFICA:
                if (opcao == atributoBloqueado) {
                    printf("Esse atributo ja foi escolhido. Selecione outro.\n");
                } else {
                    return opcao;
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

void imprimirValoresAtributo(const Carta *a, const Carta *b, int atributo, float valorA, float valorB) {
    if (atributo == ATR_POPULACAO || atributo == ATR_PONTOS_TURISTICOS) {
        printf("%s: %.0f\n", a->nomePais, valorA);
        printf("%s: %.0f\n", b->nomePais, valorB);
    } else {
        printf("%s: %.2f\n", a->nomePais, valorA);
        printf("%s: %.2f\n", b->nomePais, valorB);
    }
}

void compararAtributoIndividual(const Carta *a, const Carta *b, int atributo, float *valorA, float *valorB) {
    int vencedorAtributo = 0; /* 0 = empate, 1 = carta A, 2 = carta B */
    const char *textoRegra = regraInvertida(atributo) ? "menor vence" : "maior vence";

    *valorA = obterValorAtributo(a, atributo);
    *valorB = obterValorAtributo(b, atributo);

    printf("\n[%s]\n", nomeAtributo(atributo));
    imprimirValoresAtributo(a, b, atributo, *valorA, *valorB);
    printf("Regra: %s\n", textoRegra);

    /*
     * Simplificacao didatica permitida:
     * comparacao direta de float com >, < e ==.
     */
    if (regraInvertida(atributo)) {
        if (*valorA < *valorB) {
            vencedorAtributo = 1;
        } else {
            if (*valorB < *valorA) {
                vencedorAtributo = 2;
            } else {
                vencedorAtributo = 0;
            }
        }
    } else {
        if (*valorA > *valorB) {
            vencedorAtributo = 1;
        } else {
            if (*valorB > *valorA) {
                vencedorAtributo = 2;
            } else {
                vencedorAtributo = 0;
            }
        }
    }

    if (vencedorAtributo == 1) {
        printf("Vencedor do atributo: %s\n", a->nomePais);
    } else if (vencedorAtributo == 2) {
        printf("Vencedor do atributo: %s\n", b->nomePais);
    } else {
        printf("Vencedor do atributo: Empate!\n");
    }
}

void compararDoisAtributos(Carta a, Carta b, int atr1, int atr2) {
    float valorA1, valorB1;
    float valorA2, valorB2;
    float somaA, somaB;
    float somaComparacaoA, somaComparacaoB;

    printf("\n=== COMPARACAO FINAL ===\n");
    printf("Comparacao: %s vs %s\n", a.nomePais, b.nomePais);
    printf("Atributos escolhidos: %s e %s\n", nomeAtributo(atr1), nomeAtributo(atr2));

    compararAtributoIndividual(&a, &b, atr1, &valorA1, &valorB1);
    compararAtributoIndividual(&a, &b, atr2, &valorA2, &valorB2);

    /* Soma bruta apenas para exibicao ao usuario. */
    somaA = valorA1 + valorA2;
    somaB = valorB1 + valorB2;

    /*
     * Soma usada na decisao final:
     * atributos com regra invertida entram com sinal negativo.
     */
    somaComparacaoA = obterValorParaSoma(&a, atr1) + obterValorParaSoma(&a, atr2);
    somaComparacaoB = obterValorParaSoma(&b, atr1) + obterValorParaSoma(&b, atr2);

    printf("\nSoma %s: %.2f\n", a.nomePais, somaA);
    printf("Soma %s: %.2f\n", b.nomePais, somaB);

    /* Simplificacao didatica permitida: comparacao direta de float. */
    if (somaComparacaoA > somaComparacaoB) {
        printf("Resultado final: %s venceu!\n", a.nomePais);
    } else if (somaComparacaoB > somaComparacaoA) {
        printf("Resultado final: %s venceu!\n", b.nomePais);
    } else {
        printf("Resultado final: Empate!\n");
    }
}

int main(void) {
    int atributo1;
    int atributo2;

    Carta carta1 = {"Brasil", 203080756, 8515767.0f, 2173666.0f, 85, 0.0f};
    Carta carta2 = {"Canada", 40126954, 9984670.0f, 2140000.0f, 70, 0.0f};

    calcularDensidade(&carta1);
    calcularDensidade(&carta2);

    printf("=== SUPER TRUNFO (NIVEL MESTRE) ===\n");
    imprimirCartasResumo(carta1, carta2);

    printf("\nEscolha o 1o atributo:\n");
    atributo1 = escolherAtributo(ATR_NENHUM);

    printf("\nEscolha o 2o atributo (diferente do primeiro):\n");
    atributo2 = escolherAtributo(atributo1);

    compararDoisAtributos(carta1, carta2, atributo1, atributo2);

    return 0;
}
