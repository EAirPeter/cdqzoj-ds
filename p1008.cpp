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

inline unsigned guns_() {
    return ((unsigned) gint()) ^ 0x80000000U;
}

struct tnode {
    unsigned vmax, vmin;
    unsigned vcnt, vabs;
    tnode *l, *r;
} T[4000000];
unsigned C;

inline void tpull(tnode *p) {
    tnode *l = p->l && p->l->vcnt ? p->l : NULL;
    tnode *r = p->r && p->r->vcnt ? p->r : NULL;
    if (l && r) {
        p->vmax = p->r->vmax;
        p->vmin = p->l->vmin;
        p->vcnt = p->l->vcnt + p->r->vcnt;
        p->vabs = min(p->r->vmin - p->l->vmax, min(p->l->vabs, p->r->vabs));
    }
    else if (r) {
        p->vmax = p->r->vmax;
        p->vmin = p->r->vmin;
        p->vcnt = p->r->vcnt;
        p->vabs = p->r->vabs;
    }
    else if (l) {
        p->vmax = p->l->vmax;
        p->vmin = p->l->vmin;
        p->vcnt = p->l->vcnt;
        p->vabs = p->l->vabs;
    }
    else
        p->vcnt = 0U;
}

void tins(tnode *p, unsigned L, unsigned R, unsigned k) {
    static tnode *q[40];
    unsigned c = 0;
    while (L < R) {
        unsigned M = L + ((R - L) >> 1);
        q[c++] = p;
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
    if (!p->vcnt) {
        p->vmax = R;
        p->vmin = L;
        p->vcnt = 1;
        p->vabs = 0xffffffffU;
        while (c--)
            tpull(q[c]);
    }
}

void tdel(tnode *p, unsigned L, unsigned R, unsigned k) {
    static tnode *q[40];
    unsigned c = 0;
    while (L < R) {
        unsigned M = L + ((R - L) >> 1);
        q[c++] = p;
        if (k > M) {
            L = M + 1;
            if (!p->r)
                return;
            p = p->r;
        }
        else {
            R = M;
            if (!p->l)
                return;
            p = p->l;
        }
    }
    if (p->vcnt) {
        p->vcnt = 0;
        while (c--)
            tpull(q[c]);
    }
}

unsigned N, M;

int main() {
    N = guns();
    M = guns();
    tnode *p = T + C++;
    while (N--)
        tins(p, 0U, -1U, guns_());
    while (M--) {
        switch (gupr()) {
        case 'D':
            tdel(p, 0, -1U, guns_());
            break;
        case 'I':
            tins(p, 0, -1U, guns_());
            break;
        case 'Q':
            if (p->vcnt > 1)
                puns(p->vabs);
            else
                puts("-1");
            break;
        }
    }
    return 0;
}

