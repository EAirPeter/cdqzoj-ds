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
    unsigned s;
    tnode *l, *r;
} T[4000000];
unsigned C;

tnode *tadd(tnode *p, unsigned L, unsigned R, unsigned k) {
    tnode *o = T + C++;
    tnode *t = o;
    while (L < R) {
        if (p)
            o->s = p->s + 1;
        else
            o->s = 1;
        unsigned M = L + ((R - L) >> 1);
        if (k > M) {
            L = M + 1;
            if (!o->r)
                o->r = T + C++;
            if (p) {
                o->l = p->l;
                p = p->r;
            }
            o = o->r;
        }
        else {
            R = M;
            if (!o->l)
                o->l = T + C++;
            if (p) {
                o->r = p->r;
                p = p->l;
            }
            o = o->l;
        }
    }
    if (p)
        o->s = p->s + 1;
    else
        o->s = 1;
    return t;
}

inline unsigned tzl(tnode *p) {
    return !p ? 0 : p->l ? p->l->s : 0;
}

unsigned tqry(tnode *pl, tnode *pr, unsigned L, unsigned R, unsigned s) {
    while (L < R) {
        unsigned M = L + ((R - L) >> 1);
        unsigned lz = tzl(pr) - tzl(pl);
        if (s > lz) {
            s -= lz;
            L = M + 1;
            if (pl)
                pl = pl->r;
            if (pr)
                pr = pr->r;
        }
        else {
            R = M;
            if (pl)
                pl = pl->l;
            if (pr)
                pr = pr->l;
        }
    }
    return L;
}

unsigned N, M;
tnode *F[100001];

int main() {
    N = guns();
    M = guns();
    for (unsigned i = 1; i <= N; ++i)
        F[i] = tadd(F[i - 1], 0U, -1U, guns_());
    while (M--) {
        unsigned a = guns();
        unsigned b = guns();
        puns_(tqry(F[a - 1], F[b], 0U, -1U, guns()));
    }
    return 0;
}

