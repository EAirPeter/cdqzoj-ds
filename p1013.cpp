#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

struct tnode {
    bool nul;
    int v;
    unsigned s, t, z;
    tnode *c[2];
    void update() {
        z = c[0]->z + 1 + c[1]->z;
        s = c[0]->s + t + c[1]->s;
    }
} T[100000], *S[100000], *F[100001], nil;

unsigned N, M, C, R;
unsigned X;
unsigned U[100001];

void tgetk(tnode *p, unsigned k) {
    R = 0;
    for (;;) {
        S[R++] = p;
        unsigned z = p->c[0]->z + 1;
        if (k < z)
            p = p->c[0];
        else if (k > z) {
            p = p->c[1];
            k -= z;
        }
        else
            break;
    }
}

void tgetv(tnode *p, int v) {
    R = 0;
    while (!p->nul) {
        S[R++] = p;
        if (v < p->v)
            p = p->c[0];
        else if (v > p->v)
            p = p->c[1];
        else
            break;
    }
}

tnode *tsplay() {
    tnode *p = S[--R];
    while (R) {
        if (R == 1) {
            tnode *o = S[--R];
            int d = o->c[1] == p;
            o->c[d] = p->c[d ^ 1];
            p->c[d ^ 1] = o;
            o->update();
            p->update();
        }
        else {
            tnode *o = S[--R];
            tnode *oo = S[--R];
            int d = o->c[1] == p;
            int dd = oo->c[1] == o;
            if (d == dd) {
                oo->c[d] = o->c[d ^ 1];
                o->c[d ^ 1] = oo;
                o->c[d] = p->c[d ^ 1];
                p->c[d ^ 1] = o;
            }
            else {
                oo->c[dd] = p->c[d];
                p->c[d] = oo;
                o->c[d] = p->c[dd];
                p->c[dd] = o;
            }
            oo->update();
            o->update();
            p->update();
            if (R) {
                tnode *ooo = S[R - 1];
                ooo->c[ooo->c[1] == oo] = p;
            }
        }
    }
    return p;
}

tnode *merge(tnode *p1, tnode *p2) {
    if (p1->nul)
        return p2;
    if (p2->nul)
        return p1;
    tgetk(p1, (p1->z + 1) >> 1);
    p1 = tsplay();
    tgetv(p2, p1->v);
    p2 = tsplay();
    unsigned s = p1->c[1]->s + p1->t;
    if (p2->v > p1->v) {
        tnode *p3 = p2->c[0];
        p2->c[0] = &nil;
        p2->update();
        X += s * p3->s;
        p1->c[0] = merge(p1->c[0], p3);
        p1->c[1] = merge(p1->c[1], p2);
    }
    else if (p1->v > p2->v) {
        tnode *p3 = p2->c[1];
        p2->c[1] = &nil;
        p2->update();
        X += s * p2->s;
        p1->c[0] = merge(p1->c[0], p2);
        p1->c[1] = merge(p1->c[1], p3);
    }
    else {
        X += s * p2->c[0]->s;
        p1->t += p2->t;
        p1->c[0] = merge(p1->c[0], p2->c[0]);
        p2->c[1] = merge(p1->c[1], p2->c[1]);
    }
    p1->update();
    return p1;
}

unsigned ufs(unsigned x) {
    static unsigned u[100000];
    int c = 0;
    while (U[x] != x) {
        u[c++] = x;
        x = U[x];
    }
    while (c)
        U[u[--c]] = x;
    return x;
}

int main() {
    nil.nul = true;
    nil.c[0] = nil.c[1] = &nil;
    scanf("%u%u", &N, &M);
    for (unsigned i = 1; i <= N; ++i) {
        U[i] = i;
        F[i] = &T[C++];
        scanf("%d", &(F[i]->v));
        F[i]->c[0] = F[i]->c[1] = &nil;
        F[i]->t = 1;
        F[i]->update();
    }
    while (M--) {
        unsigned a, b;
        scanf("%u%u", &a, &b);
        if (ufs(a) == ufs(b)) {
            puts("-1");
            continue;
        }
        X = 0;
        F[U[a]] = merge(F[U[a]], F[U[b]]);
        U[U[b]] = U[a];
        printf("%u\n", X);
    }
    return 0;
}

