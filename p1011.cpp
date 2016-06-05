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

inline unsigned guns() {
    int c;
    while ((c = getchar()) < '0');
    unsigned f = (unsigned) (c & 0x0f);
    while ((c = getchar()) >= '0')
        f = f * 10 + (unsigned) (c & 0x0f);
    return f;
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

inline void puns(unsigned x) {
    if (!x) {
        putchar('0');
        putchar('\n');
        return;
    }
    static char s[16];
    unsigned c = 0;
    while (x) {
        s[c++] = (char) ((x % 10) | 0x30);
        x /= 10;
    }
    while (c--)
        putchar(s[c]);
    putchar('\n');
}

inline unsigned guns_() {
    return ((unsigned) gint()) ^ 0x80000000U;
}

inline void puns_(unsigned x) {
    pint((int) (x ^ 0x80000000U));
}

struct tnode {
    int v;
    tnode *l, *r;
} T[3000000];
unsigned C;

tnode *tmod(tnode *p, unsigned L, unsigned R, unsigned k, int v) {
    tnode *o = T + C++;
    tnode *t = o;
    while (L < R) {
        unsigned M = (L + R) >> 1;
        o->v = p->v + v;
        if (k > M) {
            o->l = p->l;
            o->r = T + C++;
            L = M + 1;
            o = o->r;
            p = p->r;
        }
        else {
            o->l = T + C++;
            o->r = p->r;
            R = M;
            o = o->l;
            p = p->l;
        }
    }
    o->v = p->v + v;
    return t;
}

int tqry(tnode *p, unsigned L, unsigned R, unsigned l, unsigned r) {
    if (L == l && R == r)
        return p->v;
    unsigned M = (L + R) >> 1;
    if (l > M)
        return tqry(p->r, M + 1, R, l, r);
    if (r <= M)
        return tqry(p->l, L, M, l, r);
    return tqry(p->l, L, M, l, M) + tqry(p->r, M + 1, R, M + 1, r);
}

int D[200000];

tnode *tbuild(unsigned L, unsigned R) {
    tnode *o = T + C++;
    if (L == R) {
        o->v = D[L];
        return o;
    }
    unsigned M = (L + R) >> 1;
    o->l = tbuild(L, M);
    o->r = tbuild(M + 1, R);
    o->v = o->l->v + o->r->v;
    return o;
}

unsigned N, M, R;

tnode *F[100001];

int main() {
    N = guns();
    M = guns();
    for (R = 1; R < N; R <<= 1);
    for (unsigned i = 1; i <= N; ++i)
        D[i] = gint();
    F[0] = tbuild(1, R);
    for (unsigned i = 1; i <= M; ++i) {
        unsigned a, b;
        int c;
        switch (gupr()) {
        case 'M':
            a = guns();
            c = gint();
            F[i] = tmod(F[i - 1], 1, R, a, c - D[a]);
            D[a] = c;
            break;
        case 'Q':
            a = guns();
            b = guns();
            pint(tqry(F[guns()], 1, R, a, b));
            F[i] = F[i - 1];
            break;
        }
    }
    return 0;
}

