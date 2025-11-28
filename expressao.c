#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

float absoluto(float x){
    return (x < 0) ? -x : x;
}

float potencia(float base, int exp){
    float r = 1;
    for(int i=0;i<exp;i++) r *= base;
    return r;
}

float seno(float graus){
    float rad = graus * 3.14159265f / 180.0f;
    float x = rad;
    float x3 = x*x*x;
    float x5 = x3*x*x;
    float x7 = x5*x*x;

    return x - (x3/6.0f) + (x5/120.0f) - (x7/5040.0f);
}

float cosseno(float graus){
    float rad = graus * 3.14159265f / 180.0f;
    float x = rad;
    float x2 = x*x;
    float x4 = x2*x2;
    float x6 = x4*x2;

    return 1 - (x2/2.0f) + (x4/24.0f) - (x6/720.0f);
}

float tangente(float graus){
    return seno(graus) / cosseno(graus);
}

float raiz(float x){
    float r = x/2;
    for(int i=0;i<10;i++){
        r = (r + x/r) / 2.0f;
    }
    return r;
}

float log10_aprox(float x){
    float n = 0;
    while(x > 1){
        x /= 10;
        n++;
    }
    return n;
}

typedef struct {
    char itens[50][512];
    int topo;
} PilhaStr;

void pushStr(PilhaStr *p, char *s){
    strcpy(p->itens[++p->topo], s);
}

char* popStr(PilhaStr *p){
    return p->itens[p->topo--];
}

typedef struct {
    float itens[512];
    int topo;
} PilhaFloat;

void pushFloat(PilhaFloat *p, float v){
    p->itens[++p->topo] = v;
}

float popFloat(PilhaFloat *p){
    return p->itens[p->topo--];
}

char * getFormaInFixa(char *Str){
    static char resultado[512];
    PilhaStr p;
    p.topo = -1;

    char token[50];
    int i = 0;

    while(sscanf(Str + i, "%s", token) == 1){
        i += strlen(token) + 1;

        if(strcmp(token,"+") == 0 ||
           strcmp(token,"-") == 0 ||
           strcmp(token,"*") == 0 ||
           strcmp(token,"/") == 0 ||
           strcmp(token,"%") == 0 ||
           strcmp(token,"^") == 0){

            char b[512], a[512], aux[512];
            strcpy(b, popStr(&p));
            strcpy(a, popStr(&p));

            sprintf(aux,"(%s%s%s)", a, token, b);
            pushStr(&p, aux);
        }
        else if(strcmp(token,"sen") == 0 ||
                strcmp(token,"cos") == 0 ||
                strcmp(token,"tg") == 0 ||
                strcmp(token,"log") == 0 ||
                strcmp(token,"raiz") == 0){

            char a[512], aux[512];
            strcpy(a, popStr(&p));

            sprintf(aux,"%s(%s)", token, a);
            pushStr(&p, aux);
        }
        else {
            pushStr(&p, token);
        }
    }

    strcpy(resultado, popStr(&p));
    return resultado;
}

float getValorPosFixa(char *Str){
    PilhaFloat p;
    p.topo = -1;

    char token[50];
    int i=0;

    while(sscanf(Str + i, "%s", token) == 1){
        i += strlen(token) + 1;

        if(strcmp(token,"+") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, a+b);
        }
        else if(strcmp(token,"-") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, a-b);
        }
        else if(strcmp(token,"*") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, a*b);
        }
        else if(strcmp(token,"/") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, a/b);
        }
        else if(strcmp(token,"%") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, (int)a % (int)b);
        }
        else if(strcmp(token,"^") == 0){
            float b = popFloat(&p), a = popFloat(&p);
            pushFloat(&p, potencia(a,(int)b));
        }
        else if(strcmp(token,"sen") == 0){
            pushFloat(&p, seno(popFloat(&p)));
        }
        else if(strcmp(token,"cos") == 0){
            pushFloat(&p, cosseno(popFloat(&p)));
        }
        else if(strcmp(token,"tg") == 0){
            pushFloat(&p, tangente(popFloat(&p)));
        }
        else if(strcmp(token,"raiz") == 0){
            pushFloat(&p, raiz(popFloat(&p)));
        }
        else if(strcmp(token,"log") == 0){
            pushFloat(&p, log10_aprox(popFloat(&p)));
        }
        else {
            pushFloat(&p, atof(token));
        }
    }

    return popFloat(&p);
}
