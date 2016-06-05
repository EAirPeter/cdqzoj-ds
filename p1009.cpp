#include <cmath>
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

struct lnode {
    int v[1000];
    unsigned s;
    lnode *p;
} L[1000];
unsigned C;

void ldel(lnode *p, unsigned k) {
    while (k > p->s) {
        k -= p->s;
        p = p->p;
    }
    for (unsigned i = k; i < p->s; ++i)
        p->v[i - 1] = p->v[i];
    --p->s;
}

int lqry(lnode *p, unsigned k) {
    while (k > p->s) {
        k -= p->s;
        p = p->p;
    }
    return p->v[k - 1];
}

unsigned N, M, S;

lnode *lzip(lnode *p) {
    while (p && !p->s)
        p = p->p;
    lnode *o = p;
    while (p) {
        while (p->p && p->s + p->p->s <= S) {
            for (unsigned i = 0; i < p->p->s; ++i)
                p->v[p->s++] = p->p->v[i];
            p->p = p->p->p;
        }
        p = p->p;
    }
    return o;
}

int main() {
    N = guns();
    M = guns();
    S = (unsigned) (sqrt((double) N) + 1);
    lnode *p = L + C++;
    lnode *o = p;
    for (unsigned i = 0, j = 0; i < N; ++i) {
        if (j == S) {
            o->s = S;
            o->p = L + C++;
            o = o->p;
            j = 0;
        }
        o->v[j++] = gint();
    }
    o->s = N % S;
    if (!o->s)
        o->s = S;
    while (M--) {
        switch (gupr()) {
        case 'D':
            ldel(p, guns());
            p = lzip(p);
            break;
        case 'Q':
            pint(lqry(p, guns()));
            break;
        }
    }
    return 0;
}

