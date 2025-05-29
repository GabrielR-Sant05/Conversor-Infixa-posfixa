/*
Gabriel Rodrigues dos Santos
Ra: 20235993
Gabriel Mocambani Cason
Ra: 20235899
3° Eng. Comp. 
*/
#include <stdio.h>
#include <ctype.h>

#define TAM 100

struct pilha {
    char elemento[TAM];
    int Topo;
};
typedef struct pilha PILHA;

void PILHA_Inicia(PILHA *p);
int PILHA_Vazia(PILHA *p);
int PILHA_Cheia(PILHA *p);
void PUSH(PILHA *p, char x);
char POP(PILHA *p);
char getTopo(PILHA p);
int isOperator(char c);
int precedence(char c);
void PilhaInfToPos(PILHA *infixa, PILHA *pilhaOperadores, char saida[]);
void Mostrar(PILHA p);

void PILHA_Inicia(PILHA *p) {
    p->Topo = -1;
}

int PILHA_Vazia(PILHA *p) {
    return p->Topo == -1;
}

int PILHA_Cheia(PILHA *p) {
    return p->Topo == TAM - 1;
}

void PUSH(PILHA *p, char x) {
    if (PILHA_Cheia(p)) {
        printf("Pilha Cheia\n");
    } else {
        p->Topo++;
        p->elemento[p->Topo] = x;
    }
}

char POP(PILHA *p) {
    if (PILHA_Vazia(p)) {
        printf("Pilha Vazia\n");
        return '\0';
    } else {
        return p->elemento[p->Topo--];
    }
}

char getTopo(PILHA p) {
    if (p.Topo == -1) {
        return 0;
    } else {
        return p.elemento[p.Topo];
    }
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char c) {
    switch (c) {
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

void PilhaInfToPos(PILHA *infixa, PILHA *pilhaOperadores, char saida[]) {
    int i = 0, j = 0;
    char c;

    while ((c = infixa->elemento[i++]) != '\0') {
        if (isspace(c)) continue;

        if (isalnum(c)) {
            saida[j++] = c;
        } else if (c == '(') {
            PUSH(pilhaOperadores, c);
        } else if (c == ')') {
            while (!PILHA_Vazia(pilhaOperadores) && getTopo(*pilhaOperadores) != '(')
                saida[j++] = POP(pilhaOperadores);
            POP(pilhaOperadores); // remove '('
        } else if (isOperator(c)) {
            while (!PILHA_Vazia(pilhaOperadores) &&
                   precedence(getTopo(*pilhaOperadores)) >= precedence(c)) {
                saida[j++] = POP(pilhaOperadores);
            }
            PUSH(pilhaOperadores, c);
        }
    }

    while (!PILHA_Vazia(pilhaOperadores))
        saida[j++] = POP(pilhaOperadores);

    saida[j] = '\0';  // Finaliza string
}

void Mostrar(PILHA p) {
    for (int i = 0; i <= p.Topo; i++) {
        printf("%c", p.elemento[i]);
    }
    printf("\n");
}

int main() {
    PILHA infx, posfx;
    char infix[TAM], pos[TAM];

    PILHA_Inicia(&infx);
    PILHA_Inicia(&posfx);

    printf("Digite a expressao infixa: ");
    fgets(infix, TAM, stdin);

    // Remover '\n' se estiver no final da string
    int len = 0;
    while (infix[len] != '\0') {
        if (infix[len] == '\n') {
            infix[len] = '\0';
            break;
        }
        len++;
    }

    // Copiar para a pilha infx
    for (int i = 0; infix[i] != '\0'; i++) {
        infx.elemento[i] = infix[i];
        infx.Topo++;
    }
    // Adiciona o caractere nulo manualmente
    infx.elemento[infx.Topo + 1] = '\0';

    printf("Iniciando Conversao\n");
    PilhaInfToPos(&infx, &posfx, pos);
    printf("Conversao finalizada\n");

    printf("Expressao Infixa: ");
    for (int i = 0; i <= infx.Topo; i++) {
        printf("%c", infx.elemento[i]);
    }

    printf("\nExpressao Posfixa: ");
    printf("%s\n", pos);

    return 0;
}
