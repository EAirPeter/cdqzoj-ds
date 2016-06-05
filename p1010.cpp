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

void tmod(tnode *p, unsigned L, unsigned R, unsigned k, unsigned v) {
    while (L < R) {
        p->s += v;
        unsigned M = L + ((R - L) >> 1);
        if (k > M) {
            L = M + 1;
            if (!p->r)
                p->r = T + C++;
            p = p->r;
        }
        else {
            R = M;
            if (!p->l)
                p->l = T + C++;
            p = p->l;
        }
    }
    p->s += v;
}

unsigned tqry(tnode *p, unsigned L, unsigned R, unsigned s) {
    while (L < R) {
        unsigned M = L + ((R - L) >> 1);
        if (!p->l || s > p->l->s) {
            if (p->l)
                s -= p->l->s;
            L = M + 1;
            p = p->r;
        }
        else {
            R = M;
            p = p->l;
        }
    }
    return L;
}

unsigned N, M;
unsigned D[100001];

int main() {
    N = guns();
    M = guns();
    tnode *p = T + C++;
    for (unsigned i = 1; i <= N; ++i)
        tmod(p, 0U, -1U, D[i] = guns_(), 1U);
    while (M--) {
        unsigned a, b;
        switch (gupr()) {
        case 'M':
            a = guns();
            b = guns_();
            tmod(p, 0U, -1U, D[a], -1U);
            tmod(p, 0U, -1U, D[a] = b, 1U);
            break;
        case 'Q':
            puns_(tqry(p, 0U, -1U, guns()));
            break;
        }
    }
    return 0;
}

