#include <stdio.h>

/*
 * Super Trunfo - Nivel Novato
 * O programa cadastra duas cartas, calcula atributos derivados
 * e compara as cartas usando UM atributo escolhido no codigo.
 */

/* Atributos disponiveis para comparacao */
#define ATRIBUTO_POPULACAO 1
#define ATRIBUTO_AREA 2
#define ATRIBUTO_PIB 3
#define ATRIBUTO_DENSIDADE 4
#define ATRIBUTO_PIB_PER_CAPITA 5

/*
 * Escolha do atributo feita diretamente no codigo.
 * Troque a constante abaixo para testar outros atributos.
 * Exemplo: ATRIBUTO_AREA ou ATRIBUTO_DENSIDADE.
 */
#define ATRIBUTO_ESCOLHIDO ATRIBUTO_POPULACAO

/* Estrutura que representa uma carta do jogo */
typedef struct {
    char estado[3];                /* Sigla do estado: 2 letras + '\0' (ex: "SP") */
    char codigo[10];               /* Codigo da carta (ex: "A01") */
    char nomeCidade[60];           /* Nome da cidade */
    int populacao;                 /* Habitantes */
    float area;                    /* Area em km2 */
    float pib;                     /* PIB total da cidade */
    int pontosTuristicos;          /* Quantidade de pontos turisticos */
    float densidadePopulacional;   /* Populacao / Area */
    float pibPerCapita;            /* PIB / Populacao */
} Carta;

/*
 * Faz a leitura dos dados de UMA carta.
 * Tambem calcula os dois atributos derivados:
 * - densidade populacional
 * - PIB per capita
 */
void cadastrarCarta(Carta *carta, int numeroCarta) {
    /* Titulo para facilitar a leitura na hora do cadastro */
    printf("\n=== Cadastro da Carta %d ===\n", numeroCarta);

    /* Leitura da sigla do estado */
    printf("Estado (sigla, ex: SP): ");
    scanf("%2s", carta->estado);

    /* Leitura do codigo da carta */
    printf("Codigo da carta (ex: A01): ");
    scanf("%9s", carta->codigo);

    /* Leitura do nome da cidade (aceita espacos) */
    printf("Nome da cidade: ");
    scanf(" %59[^\n]", carta->nomeCidade);

    /* Leitura dos atributos numericos principais */
    printf("Populacao: ");
    scanf("%d", &carta->populacao);

    printf("Area (km2): ");
    scanf("%f", &carta->area);

    printf("PIB: ");
    scanf("%f", &carta->pib);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &carta->pontosTuristicos);

    /* Calculo da densidade populacional = populacao / area */
    carta->densidadePopulacional = carta->populacao / carta->area;

    /* Calculo do PIB per capita = PIB / populacao */
    carta->pibPerCapita = carta->pib / carta->populacao;
}

/* Exibe todos os dados de uma carta, inclusive os calculados */
void exibirResumoCarta(const Carta *carta, int numeroCarta) {
    printf("\nCarta %d - %s (%s)\n", numeroCarta, carta->nomeCidade, carta->estado);
    printf("Codigo: %s\n", carta->codigo);
    printf("Populacao: %d\n", carta->populacao);
    printf("Area: %.2f km2\n", carta->area);
    printf("PIB: %.2f\n", carta->pib);
    printf("Pontos turisticos: %d\n", carta->pontosTuristicos);
    printf("Densidade populacional: %.2f hab/km2\n", carta->densidadePopulacional);
    printf("PIB per capita: %.2f\n", carta->pibPerCapita);
}

/*
 * Formata o valor de exibicao do atributo comparado.
 * Populacao aparece sem casas decimais.
 * Os demais atributos aparecem com 2 casas.
 */
void exibirValorAtributo(int atributo, float valor) {
    if (atributo == ATRIBUTO_POPULACAO) {
        printf("%.0f", valor);
    } else {
        printf("%.2f", valor);
    }
}

int main(void) {
    /* Duas cartas que serao preenchidas pelo usuario */
    Carta carta1;
    Carta carta2;

    /*
     * Variaveis auxiliares da comparacao:
     * - valorCarta1 e valorCarta2 recebem o atributo selecionado
     * - nomeAtributo guarda o texto para impressao na tela
     */
    float valorCarta1 = 0.0f;
    float valorCarta2 = 0.0f;
    const char *nomeAtributo = "";

    /* Cadastro das duas cartas */
    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    /* Mostra os dados para o usuario conferir */
    exibirResumoCarta(&carta1, 1);
    exibirResumoCarta(&carta2, 2);

    /*
     * Define qual atributo sera comparado, de acordo com
     * o valor de ATRIBUTO_ESCOLHIDO (constante no topo do arquivo).
     */
    switch (ATRIBUTO_ESCOLHIDO) {
        case ATRIBUTO_POPULACAO:
            nomeAtributo = "Populacao";
            valorCarta1 = (float)carta1.populacao;
            valorCarta2 = (float)carta2.populacao;
            break;
        case ATRIBUTO_AREA:
            nomeAtributo = "Area";
            valorCarta1 = carta1.area;
            valorCarta2 = carta2.area;
            break;
        case ATRIBUTO_PIB:
            nomeAtributo = "PIB";
            valorCarta1 = carta1.pib;
            valorCarta2 = carta2.pib;
            break;
        case ATRIBUTO_DENSIDADE:
            nomeAtributo = "Densidade Populacional";
            valorCarta1 = carta1.densidadePopulacional;
            valorCarta2 = carta2.densidadePopulacional;
            break;
        case ATRIBUTO_PIB_PER_CAPITA:
            nomeAtributo = "PIB per capita";
            valorCarta1 = carta1.pibPerCapita;
            valorCarta2 = carta2.pibPerCapita;
            break;
        default:
            /* Protecao caso o valor da constante seja invalido */
            printf("\nAtributo invalido para comparacao.\n");
            return 1;
    }

    /* Cabecalho do resultado da comparacao */
    printf("\n=== Comparacao de cartas (Atributo: %s) ===\n", nomeAtributo);

    /* Exibe o valor do atributo da carta 1 */
    printf("Carta 1 - %s (%s): ", carta1.nomeCidade, carta1.estado);
    exibirValorAtributo(ATRIBUTO_ESCOLHIDO, valorCarta1);
    printf("\n");

    /* Exibe o valor do atributo da carta 2 */
    printf("Carta 2 - %s (%s): ", carta2.nomeCidade, carta2.estado);
    exibirValorAtributo(ATRIBUTO_ESCOLHIDO, valorCarta2);
    printf("\n");

    /*
     * Regra especial:
     * - Para densidade populacional, MENOR valor vence.
     * Regra geral:
     * - Para os outros atributos, MAIOR valor vence.
     */
    if (ATRIBUTO_ESCOLHIDO == ATRIBUTO_DENSIDADE) {
        /* Menor densidade vence */
        if (valorCarta1 < valorCarta2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nomeCidade);
        } else if (valorCarta2 < valorCarta1) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nomeCidade);
        } else {
            /* Mesmo valor nas duas cartas */
            printf("Resultado: Empate!\n");
        }
    } else {
        /* Maior valor vence para os demais atributos */
        if (valorCarta1 > valorCarta2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nomeCidade);
        } else if (valorCarta2 > valorCarta1) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nomeCidade);
        } else {
            /* Mesmo valor nas duas cartas */
            printf("Resultado: Empate!\n");
        }
    }

    /* Encerramento normal do programa */
    return 0;
}
