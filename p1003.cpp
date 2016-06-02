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

int N, M;
int F[100001], D[100001];

void fmod(int k, int v) {
    while (k <= N) {
        F[k] += v;
        k += k & -k;
    }
}

int fqry(int k) {
    int x = 0;
    while (k) {
        x += F[k];
        k ^= k & -k;
    }
    return x;
}

int main() {
    N = gint();
    M = gint();
    for (int i = 1; i <= N; ++i)
        fmod(i, D[i] = gint());
    while (M--) {
        int a, b;
        switch (gupr()) {
        case 'M':
            a = gint();
            b = gint();
            fmod(a, b - D[a]);
            D[a] = b;
            break;
        case 'Q':
            a = gint();
            b = gint();
            pint(fqry(b) - fqry(a - 1));
            break;
        }
    }
    return 0;
}

