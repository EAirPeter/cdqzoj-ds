#include <algorithm>
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

struct tnode {
    int vmax;
    unsigned vcnt;
    tnode *l, *r;
} T[262144];
unsigned C;

inline unsigned tcnt(tnode *p, unsigned L, unsigned R, int v) {
    unsigned vcnt = 0;
    while (L < R) {
        unsigned M = (L + R) >> 1;
        if (v > p->l->vmax) {
            L = M + 1;
            p = p->r;
        }
        else {
            vcnt += p->vcnt - p->l->vcnt;
            R = M;
            p = p->l;
        }
    }
    return vcnt + (p->vmax > v);
}

inline void tpull(tnode *p, unsigned M, unsigned R) {
    p->vmax = max(p->l->vmax, p->r->vmax);
    p->vcnt = p->l->vcnt + tcnt(p->r, M + 1, R, p->l->vmax);
}

inline void tmod(tnode *p, unsigned L, unsigned R, unsigned k, int v) {
    static tnode *q[20];
    static unsigned m[20], r[20];
    unsigned c = 0;
    while (L < R) {
        unsigned M = (L + R) >> 1;
        q[c] = p;
        m[c] = M;
        r[c] = R;
        ++c;
        if (k > M) {
            L = M + 1;
            p = p->r;
        }
        else {
            R = M;
            p = p->l;
        }
    }
    p->vmax = v;
    while (c--)
        tpull(q[c], m[c], r[c]);
}

int D[200000];

tnode *tbuild(unsigned L, unsigned R) {
    tnode *o = T + C++;
    if (L == R) {
        o->vmax = D[L];
        o->vcnt = 1;
        return o;
    }
    unsigned M = (L + R) >> 1;
    o->l = tbuild(L, M);
    o->r = tbuild(M + 1, R);
    tpull(o, M, R);
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
        unsigned a;
        int b;
        switch (gupr()) {
        case 'M':
            a = guns();
            b = gint();
            tmod(p, 1, R, a, b);
            break;
        case 'Q':
            puns(p->vcnt);
            break;
        }
    }
    return 0;
}

