#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// ===== helpers de teste (não fazem parte da entrega) =====
static void liberarEstradaTeste(Estrada *E) {
    if (!E) return;
    Cidade *p = E->Inicio;
    while (p) { Cidade *nx = p->Proximo; free(p); p = nx; }
    free(E);
}

static int listaEstaOrdenada(const Estrada *E) {
    if (!E || !E->Inicio) return 1;
    const Cidade *p = E->Inicio;
    while (p->Proximo) {
        if (p->Posicao > p->Proximo->Posicao) return 0;
        p = p->Proximo;
    }
    return 1;
}

static int contarNos(const Estrada *E) {
    int c = 0; const Cidade *p = E->Inicio;
    while (p) { c++; p = p->Proximo; }
    return c;
}

static void imprimirEstrada(const Estrada *E) {
    if (!E) { puts("Estrada NULL"); return; }
    printf("T=%d, N=%d\n", E->T, E->N);
    const Cidade *p = E->Inicio;
    while (p) {
        printf("  %d -> %s\n", p->Posicao, p->Nome);
        p = p->Proximo;
    }
}

// ================== testes ==================
int main(void) {
    int passou = 0, total = 0;

    // teste01 (válido)
    total++;
    Estrada *E1 = getEstrada("Teste01.txt");
    if (E1 && E1->T == 10 && E1->N == 2 && listaEstaOrdenada(E1) && contarNos(E1) == 2) {
        puts("[OK] teste01: leitura/validacao/ordem");
        passou++;
    } else {
        puts("[FAIL] teste01");
    }
    imprimirEstrada(E1);
    liberarEstradaTeste(E1);

    // teste02 (válido)
    total++;
    Estrada *E2 = getEstrada("Teste02.txt");
    if (E2 && E2->T == 20 && E2->N == 4 && listaEstaOrdenada(E2) && contarNos(E2) == 4) {
        puts("[OK] teste02: leitura/validacao/ordem");
        passou++;
    } else {
        puts("[FAIL] teste02");
    }
    imprimirEstrada(E2);
    liberarEstradaTeste(E2);

    // teste calcularMenorVizinhanca 1
    total++;
    double menor1 = calcularMenorVizinhanca("Teste01.txt");
    if (menor1 == 3.5) { 
        printf("[OK] Menor vizinhança Teste01: %.1f\n", menor1);
        passou++;
    } else {
        printf("[FAIL] Menor vizinhança Teste01: %.1f (esperado 3.5)\n", menor1);
    }

    // teste calcularMenorVizinhanca 2
    total++;
    double menor2 = calcularMenorVizinhanca("Teste02.txt");
    if (menor2 == 3.5) { 
        printf("[OK] Menor vizinhança Teste02: %.1f\n", menor2);
        passou++;
    } else {
        printf("[FAIL] Menor vizinhança Teste02: %.1f (esperado 3.5)\n", menor2);
    }

    // teste cidadeMenorVizinhanca 1
    total++;
    char *cidade1 = cidadeMenorVizinhanca("Teste01.txt");
    if (cidade1 != NULL && strcmp(cidade1, "Birnin Zana") == 0) {
        printf("[OK] Cidade Teste01: %s\n", cidade1);
        passou++;
        free(cidade1);
    } else {
        printf("[FAIL] Cidade Teste01: %s (esperado Birnin Zana)\n", 
               cidade1 ? cidade1 : "NULL");
        if (cidade1) free(cidade1);
    }

    // teste cidadeMenorVizinhanca 2
    total++;
    char *cidade2 = cidadeMenorVizinhanca("Teste02.txt");
    if (cidade2 != NULL && strcmp(cidade2, "L'pur") == 0) {
        printf("[OK] Cidade Teste02: %s\n", cidade2);
        passou++;
        free(cidade2);
    } else {
        printf("[FAIL] Cidade Teste02: %s (esperado L'pur)\n", 
               cidade2 ? cidade2 : "NULL");
        if (cidade2) free(cidade2);
    }

    
    // inválido (opcional): Xi fora do intervalo ou duplicado → deve retornar NULL
    total++;
    Estrada *Ei = getEstrada("testes/invalido_Xi_fora.txt");
    if (Ei == NULL) { puts("[OK] invalido_Xi_fora: retornou NULL"); passou++; }
    else { puts("[FAIL] invalido_Xi_fora: deveria ser NULL"); liberarEstradaTeste(Ei); }

    printf("\nResumo: %d/%d testes passaram.\n", passou, total);
    return 0;
}
