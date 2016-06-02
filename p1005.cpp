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

struct tnode {
    bool fset;
    int vsum, vset;
    tnode *l, *r;
} T[1 << 18];
unsigned C;

inline void tset(tnode *p, unsigned L, unsigned R, int v) {
    p->fset = true;
    p->vsum = v * (int) (R - L + 1);
    p->vset = v;
}

inline void tpull(tnode *p) {
    p->vsum = p->l->vsum + p->r->vsum;
}

inline void tpush(tnode *p, unsigned L, unsigned M, unsigned R) {
    if (p->fset) {
        p->fset = false;
        tset(p->l, L, M, p->vset);
        tset(p->r, M + 1, R, p->vset);
    }
}

void tmod(tnode *p, unsigned L, unsigned R, unsigned l, unsigned r, int v) {
    if (L == l && R == r) {
        tset(p, L, R, v);
        return;
    }
    unsigned M = (L + R) >> 1;
    tpush(p, L, M, R);
    if (l > M)
        tmod(p->r, M + 1, R, l, r, v);
    else if (r <= M)
        tmod(p->l, L, M, l, r, v);
    else {
        tmod(p->l, L, M, l, M, v);
        tmod(p->r, M + 1, R, M + 1, r, v);
    }
    tpull(p);
}

int tqry(tnode *p, unsigned L, unsigned R, unsigned l, unsigned r) {
    if (L == l && R == r)
        return p->vsum;
    unsigned M = (L + R) >> 1;
    tpush(p, L, M, R);
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
        o->vsum = D[L];
        return o;
    }
    unsigned M = (L + R) >> 1;
    o->l = tbuild(L, M);
    o->r = tbuild(M + 1, R);
    tpull(o);
    return o;
}

unsigned N, M, R;

int main() {
    N = guns();
    M = guns();
    for (R = 1; R < N; R <<= 1);
    for (unsigned i = 1; i <= N; ++i)
        D[i] = gint();
    tnode *p = tbuild(1, R);
    while (M--) {
        unsigned a, b;
        switch (gupr()) {
        case 'M':
            a = guns();
            b = guns();
            tmod(p, 1, R, a, b, gint());
            break;
        case 'Q':
            a = guns();
            b = guns();
            pint(tqry(p, 1, R, a, b));
            break;
        }
    }
    return 0;
}

