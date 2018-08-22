
#ifdef _cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

/* 朴素字符串匹配 */
void func1(char *T, char *P)
{
    int tlength, plength;
    int i, j;

    tlength = strlen(T);
    plength = strlen(P);
    for (i = 0; i < tlength - plength + 1; i++)
    {
        for (j = 0; j < plength; j++)
        {
            if (T[i + j] != P[j])
            {
                break;
            }
        }
        if (j == plength)
            printf("match, s is %d\n", i);
    }
}

/* Rabin-Karp算法 */
/* 辅助函数，递归求幂 */
int func2_pow(int d, int m)
{
    int res;

    if (1 == m)
        return d;

    res = func2_pow(d, m / 2);
    res *= res;
    if (m & 0x00000001)
        return res * d;
    else
        return res;
}

void func2(char *T, int Tlength, char * P, int Plength)
{
    int m, n, h;
    int p = 0, t = 0;
    int i, j;

    m = Plength;
    n = Tlength;
    h = func2_pow(10, m - 1) % 13;
    
    for (i = 0; i < m; i++)
    {
        p = (10 * p + P[i]) % 13;
        t = (10 * t + T[i]) % 13;
    }

    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
            {
                if (P[j] != T[i + j])
                    break;
            }
            if (j == m)
                printf("match, s is %d\n", i);
        }
        if (i != n - m)
        {
            /* C语言求模和数学求模有差异，可能是负数，要处理 */
            t = (10 *(t - T[i] * h) + T[i + m]) % 13;
            if (t < 0)
                t += 13;
        }
    }
}

void main()
{
    char T1[] = "ababa";
    char P1[] = "aba";
    char T2[] = {6, 3, 1, 4, 1, 5, 2};
    char P2[] = {3, 1, 4, 1, 5};

    //func1(T1, P1);
    func2(T2, 7, P2, 5);
}




#ifdef _cplusplus
}
#endif

