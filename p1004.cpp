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

const unsigned MDU = 1000000007;

struct tnode {
    unsigned vl, vr, vsum, vany, vadj;
    tnode *l, *r;
} T[400000];
unsigned C;

inline void tpull(tnode *p) {
    p->vl = p->l->vl;
    p->vr = p->r->vr;
    p->vsum = (p->l->vsum + p->r->vsum) % MDU;
    p->vany = (p->l->vany + p->r->vany + (unsigned)
        (((unsigned long long) p->l->vsum * p->r->vsum % MDU))) % MDU;
    p->vadj = (p->l->vadj + p->r->vadj + (unsigned)
        (((unsigned long long) p->l->vr * p->r->vl % MDU))) % MDU;
}

unsigned D[200001];

tnode *tbuild(unsigned L, unsigned R) {
    tnode *o = T + C++;
    if (L == R) {
        o->vl = o->vr = o->vsum = D[L];
        return o;
    }
    unsigned M = (L + R) >> 1;
    o->l = tbuild(L, M);
    o->r = tbuild(M + 1, R);
    tpull(o);
    return o;
}

void tmod(tnode *p, unsigned L, unsigned R, unsigned k, unsigned v) {
    static tnode *q[20];
    unsigned m = 0;
    while (L < R) {
        q[m++] = p;
        unsigned M = (L + R) >> 1;
        if (k > M) {
            L = M + 1;
            p = p->r;
        }
        else {
            R = M;
            p = p->l;
        }
    }
    p->vl = p->vr = p->vsum = v;
    while (m--)
        tpull(q[m]);
}

unsigned tqryany(tnode *p, unsigned L, unsigned R, unsigned l, unsigned r,
    unsigned &vsum)
{
    if (L == l && R == r) {
        vsum = p->vsum;
        return p->vany;
    }
    unsigned M = (L + R) >> 1;
    if (l > M)
        return tqryany(p->r, M + 1, R, l, r, vsum);
    if (r <= M)
        return tqryany(p->l, L, M, l, r, vsum);
    unsigned lsum, rsum;
    unsigned vany = tqryany(p->l, L, M, l, M, lsum) +
        tqryany(p->r, M + 1, R, M + 1, r, rsum);
    vsum = (lsum + rsum) % MDU;
    return (vany + (unsigned) (((unsigned long long) lsum * rsum % MDU))) % MDU;
}

unsigned tqryadj(tnode *p, unsigned L, unsigned R, unsigned l, unsigned r,
    unsigned &vl, unsigned &vr)
{
    if (L == l && R == r) {
        vl = p->vl;
        vr = p->vr;
        return p->vadj;
    }
    unsigned M = (L + R) >> 1;
    if (l > M)
        return tqryadj(p->r, M + 1, R, l, r, vl, vr);
    if (r <= M)
        return tqryadj(p->l, L, M, l, r, vl, vr);
    unsigned lr, rl;
    unsigned vadj = tqryadj(p->l, L, M, l, M, vl, lr) +
        tqryadj(p->r, M + 1, R, M + 1, r, rl, vr);
    return (vadj + (unsigned) (((unsigned long long) lr * rl % MDU))) % MDU;
}

unsigned N, M, R;

const int MDN = 1000000007;

int main() {
    N = guns();
    M = guns();
    for (R = 1; R < N; R <<= 1);
    for (unsigned i = 1; i <= N; ++i) {
        int c = gint() % MDN;
        D[i] = (unsigned) (c < 0 ? c + MDN : c);
    }
    tnode *p = tbuild(1, R);
    while (M--) {
        unsigned a, b;
        int c;
        unsigned x, y;
        switch (gupr()) {
        case 'A':
            a = guns();
            b = guns();
            puns(tqryadj(p, 1, R, a, b, x, y));
            break;
        case 'M':
            a = guns();
            c = gint() % MDN;
            tmod(p, 1, R, a, (unsigned) (c < 0 ? c + MDN : c));
            break;
        case 'Q':
            a = guns();
            b = guns();
            puns(tqryany(p, 1, R, a, b, x));
            break;
        }
    }
    return 0;
}

