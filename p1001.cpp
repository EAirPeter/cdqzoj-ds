#include <cstdio>

using namespace std;

inline int gint() {
    int c;
    while ((c = getchar()) < '-');
    int f = 0;
    bool t = false;
    if (c == '-')
        t = true;
    else
        f = c & 0x0f;
    while ((c = getchar()) >= '0')
        f = f * 10 + (c & 0x0f);
    return t ? -f : f;
}

inline int gupr() {
    int c;
    while ((c = getchar()) < 'A');
    return c;
}

inline void pint(int x) {
    if (!x) {
        putchar('0');
        putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[16];
    int c = 0;
    while (x) {
        s[c++] = (char) ((x % 10) | 0x30);
        x /= 10;
    }
    while (c--)
        putchar(s[c]);
    putchar('\n');
}

struct tnode {
    int v;
    tnode *l, *r;
} T[2000000];

int C;
int D[100001];

tnode *tbuild(int L, int R) {
    tnode *o = T + C++;
    if (L == R) {
        o->v = D[L];
        return o;
    }
    int M = (L + R) >> 1;
    if (L <= M)
        o->l = tbuild(L, M);
    if (M < R)
        o->r = tbuild(M + 1, R);
    return o;
}

tnode *tmod(tnode *p, int L, int R, int k, int v) {
    tnode *o = T + C++;
    tnode *t = o;
    while (L < R) {
        int M = (L + R) >> 1;
        if (k > M) {
            L = M + 1;
            o->l = p->l;
            o->r = T + C++;
            p = p->r;
            o = o->r;
        }
        else {
            R = M;
            o->l = T + C++;
            o->r = p->r;
            p = p->l;
            o = o->l;
        }
    }
    o->v = v;
    return t;
}

int tqry(tnode *p, int L, int R, int k) {
    while (L < R) {
        int M = (L + R) >> 1;
        if (k > M) {
            L = M + 1;
            p = p->r;
        }
        else {
            R = M;
            p = p->l;
        }
    }
    return p->v;
}

int N, M;
tnode *F[100001];

int main() {
    N = gint();
    M = gint();
    for (int i = 1; i <= N; ++i)
        D[i] = gint();
    F[0] = tbuild(1, N);
    for (int i = 1; i <= M; ++i) {
        int a, b;
        switch (gupr()) {
        case 'M':
            a = gint();
            b = gint();
            F[i] = tmod(F[i - 1], 1, N, a, b);
            break;
        case 'Q':
            a = gint();
            b = gint();
            pint(tqry(F[b], 1, N, a));
            F[i] = F[i - 1];
            break;
        }
    }
    return 0;
}

