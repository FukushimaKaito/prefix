/*-----------------
追加課題 gccコンパイル時 -lm忘れるとできん．
------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#define SIbase 1000
#define BNbase 1024

int decimalprefix(char *dst, int dlen, char *srcstr)
{
    int flag = 0;
    double srcnum;
    double tmpnum;

    char prefixH[9] = "KMGTPEZY";
    char prefixL[9] = "munpfazy";
    srcnum = strtod(srcstr, NULL);
    if (srcnum == HUGE_VAL)
    {
        perror("overflow");
        exit(1);
    }
    else if (srcnum == 0 && errno == ERANGE)
    {
        perror("underflow");
        exit(1);
    }

    if (fabs(srcnum) >= (double)SIbase)
    {
        for (int i = 0; i < 8; i++)
        {
            if (fabs(srcnum) >= pow(SIbase, i + 1) && fabs(srcnum) <= pow(SIbase, i + 2))
            {
                tmpnum = srcnum / pow((float)SIbase, i + 1);
                //using SI
                snprintf(dst, sizeof(dst), "%.2lf%c", tmpnum, prefixH[i]);
                //using BN
                //snprintf(dst, sizeof(dst), "%.2lf%ci", tmpnum, prefixH[i]);
                flag = 1;
                break;
            }
        }
    }
    else if (fabs(srcnum) < 1)
    {
        for (int i = 0; i < 8; i++)
        {
            if (fabs(srcnum) >= (1 / pow(SIbase, i + 1)) && fabs(srcnum) >= (1 / pow(SIbase, i + 2)))
            {
                tmpnum = srcnum * pow((float)SIbase, i + 1);
                //using SI
                snprintf(dst, sizeof(dst), "%.2lf%c", tmpnum, prefixL[i]);
                //using BN
                //snprintf(dst, sizeof(dst), "%.2lf%ci", tmpnum, prefixL[i]);
                flag = 1;
                break;
            }
        }
    }
    else
    {
        snprintf(dst, sizeof(dst), "%.2lf", srcnum);
        flag = 1;
    }

    if (flag == 0)
    {
        printf("Input Error Out of Range:");
    }

    return 0;
}
int main()
{
    int ik;
    char ibuf[BUFSIZ];
    char obuf[BUFSIZ];
    while (fgets(ibuf, BUFSIZ, stdin) != NULL)
    {
        ik = decimalprefix(obuf, BUFSIZ, ibuf);
        fprintf(stdout, "%*s <- %s", 8, obuf, ibuf);
    }
    perror("fgets is NULL!");
    exit(1);
}
