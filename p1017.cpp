#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

struct tnode {
    bool v, fli, rev, nul;
    int op, cl, fop, fcl, z;
    tnode *c[2];
    void flip() {
        if (nul)
            return;
        fli ^= 1;
        swap(op, fop);
        swap(cl, fcl);
    }
    void reverse() {
        if (nul)
            return;
        rev ^= 1;
        swap(op, fcl);
        swap(cl, fop);
    }
    void push() {
        if (fli) {
            v ^= 1;
            c[0]->flip();
            c[1]->flip();
            fli = false;
        }
        if (rev) {
            c[0]->reverse();
            c[1]->reverse();
            swap(c[0], c[1]);
            rev = false;
        }
    }
    void update() {
        op = c[0]->op;
        cl = c[0]->cl;
        if (v)
            ++op;
        else if (op)
            --op;
        else
            ++cl;
        int pa = min(op, c[1]->cl);
        op += c[1]->op - pa;
        cl += c[1]->cl - pa;
        fop = c[0]->fop;
        fcl = c[0]->fcl;
        if (!v)
            ++fop;
        else if (fop)
            --fop;
        else
            ++fcl;
        int fpa = min(fop, c[1]->fcl);
        fop += c[1]->fop - fpa;
        fcl += c[1]->fcl - fpa;
        z = c[0]->z + 1 + c[1]->z;
    }
} T[100000], *S[100000], nil, *root;

int N, M, C, R;
char SS[100001];

tnode *tbuild(int l, int r) {
    if (l > r)
        return &nil;
    tnode *p = &T[C++];
    if (l == r) {
        p->v = SS[l] == '(';
        p->c[0] = p->c[1] = &nil;
    }
    else {
        int m = (l + r) >> 1;
        p->v = SS[m] == '(';
        p->c[0] = tbuild(l, m - 1);
        p->c[1] = tbuild(m + 1, r);
    }
    p->update();
    return p;
}

void tgetk(tnode *p, int k) {
    R = 0;
    for (;;) {
        S[R++] = p;
        p->push();
        int z = p->c[0]->z + 1;
        if (k < z)
            p = p->c[0];
        else if (k > z) {
            p = p->c[1];
            k -= z;
        }
        else
            break;
    }
}

tnode *tsplay(tnode *r, int k) {
    tgetk(r, k);
    tnode *p = S[--R];
    while (R) {
        if (R == 1) {
            tnode *o = S[--R];
            int d = o->c[1] == p;
            o->c[d] = p->c[d ^ 1];
            p->c[d ^ 1] = o;
            o->update();
            p->update();
        }
        else {
            tnode *o = S[--R];
            tnode *oo = S[--R];
            int d = o->c[1] == p;
            int dd = oo->c[1] == o;
            if (d == dd) {
                oo->c[d] = o->c[d ^ 1];
                o->c[d ^ 1] = oo;
                o->c[d] = p->c[d ^ 1];
                p->c[d ^ 1] = o;
            }
            else {
                oo->c[dd] = p->c[d];
                p->c[d] = oo;
                o->c[d] = p->c[dd];
                p->c[dd] = o;
            }
            oo->update();
            o->update();
            p->update();
            if (R) {
                tnode *ooo = S[R - 1];
                ooo->c[ooo->c[1] == oo] = p;
            }
        }
    }
    return p;
}

void trange(int l, int r) {
    if (l == 1 && r == root->z) {
        R = 0;
        S[R++] = root;
    }
    else if (l == 1) {
        root = tsplay(root, r + 1);
        R = 0;
        S[R++] = root;
        S[R++] = root->c[0];
    }
    else if (r == root->z) {
        root = tsplay(root, l - 1);
        R = 0;
        S[R++] = root;
        S[R++] = root->c[1];
    }
    else {
        root = tsplay(root, l - 1);
        root->c[1] = tsplay(root->c[1], r - l + 2);
        R = 0;
        S[R++] = root;
        S[R++] = root->c[1];
        S[R++] = root->c[1]->c[0];
    }
}

int query(int l, int r) {
    trange(l, r);
    tnode *p = S[--R];
    return ((p->op + 1) >> 1) + ((p->cl + 1) >> 1);
}

void flip(int l, int r) {
    trange(l, r);
    tnode *p = S[--R];
    p->flip();
    while (R)
        S[--R]->update();
}

void reverse(int l, int r) {
    trange(l, r);
    tnode *p = S[--R];
    p->reverse();
    while (R)
        S[--R]->update();
}

int main() {
    nil.nul = true;
    nil.c[0] = nil.c[1] = &nil;
    scanf("%d%d%s", &N, &M, SS);
    root = tbuild(0, N - 1);
    while (M--) {
        int o, l, r;
        scanf("%d%d%d", &o, &l, &r);
        switch (o) {
            case 0:
                printf("%d\n", query(l, r));
                break;
            case 1:
                flip(l, r);
                break;
            case 2:
                reverse(l, r);
                break;
        }
    }
    return 0;
}

