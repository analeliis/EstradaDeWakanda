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

    // inválido (opcional): Xi fora do intervalo ou duplicado → deve retornar NULL
    total++;
    Estrada *Ei = getEstrada("testes/invalido_Xi_fora.txt");
    if (Ei == NULL) { puts("[OK] invalido_Xi_fora: retornou NULL"); passou++; }
    else { puts("[FAIL] invalido_Xi_fora: deveria ser NULL"); liberarEstradaTeste(Ei); }

    printf("\nResumo: %d/%d testes passaram.\n", passou, total);
    return 0;
}
