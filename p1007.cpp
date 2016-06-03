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

struct lnode {
    int v;
    unsigned s;
    lnode *p;
} L[200000];
unsigned C;

lnode *H[1 << 24U];

inline unsigned hash(int v) {
    return ((unsigned) v * 2654435761U) >> 8U;
}

void hmod(int v, unsigned s) {
    lnode **p;
    for (p = &H[hash(v)]; *p && (*p)->v != v; p = &(*p)->p);
    if (*p)
        (*p)->s += s;
    else {
        *p = L + C++;
        (*p)->v = v;
        (*p)->s = s;
    }
}

unsigned hqry(int v) {
    lnode **p;
    for (p = &H[hash(v)]; *p && (*p)->v != v; p = &(*p)->p);
    return *p ? (*p)->s : 0;
}

int D[100001];
unsigned N, M;

int main() {
    N = guns();
    M = guns();
    for (unsigned i = 1; i <= N; ++i) {
        D[i] = gint();
        hmod(D[i], 1U);
    }
    while (M--) {
        unsigned a;
        int b;
        switch (gupr()) {
        case 'M':
            a = guns();
            b = gint();
            hmod(D[a], -1U);
            hmod(D[a] = b, 1U);
            break;
        case 'Q':
            b = gint();
            puns(hqry(b));
            break;
        }
    }
    return 0;
}

