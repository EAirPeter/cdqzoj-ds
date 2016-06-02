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

void tmod(tnode *p, int L, int R, int k, int v) {
    while (L < R) {
        int M = (L + R) >> 1;
        tnode *o;
        if (k > M) {
            L = M + 1;
            o = p->r;
            p->r = T + C++;
            p = p->r;
        }
        else {
            R = M;
            o = p->l;
            p->l = T + C++;
            p = p->l;
        }
        if (o) {
            p->l = o->l;
            p->r = o->r;
        }
    }
    p->v = v;
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

tnode *F[100001];
int N[100001], R[100001];
int M;

int main() {
    M = gint();
    int m = 0;
    F[0] = T + C++;
    R[0] = 1;
    while(M--) {
        int u;
        switch (gupr()) {
        case 'A':
            ++m;
            F[m] = T + C++;
            N[m] = N[m - 1] + 1;
            if (N[m] > R[m - 1]) {
                R[m] = R[m - 1] << 1;
                F[m]->l = F[m - 1];
            }
            else {
                R[m] = R[m - 1];
                F[m]->l = F[m - 1]->l;
                F[m]->r = F[m - 1]->r;
            }
            tmod(F[m], 1, R[m], N[m], gint());
            break;
        case 'Q':
            pint(tqry(F[m], 1, R[m], gint()));
            break;
        case 'U':
            ++m;
            u = gint();
            F[m] = F[m - u - 1];
            N[m] = N[m - u - 1];
            R[m] = R[m - u - 1];
            break;
        }
    }
    return 0;
}

