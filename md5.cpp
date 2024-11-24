#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef union
{
    unsigned w;
    unsigned char b[4];
} MD5union;

typedef unsigned DigestArray[4];

unsigned func0(unsigned abcd[])
{
    return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

unsigned func1(unsigned abcd[])
{
    return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

unsigned func2(unsigned abcd[])
{
    return abcd[1] ^ abcd[2] ^ abcd[3];
}

unsigned func3(unsigned abcd[])
{
    return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned *calctable(unsigned *k)
{
    double s, pwr = pow(2, 32);
    for (int i = 0; i < 64; i++)
    {
        s = fabs(sin(1 + i));
        k[i] = (unsigned)(s * pwr);
    }
    return k;
}

unsigned rol(unsigned r, short N)
{
    unsigned mask1 = (1 << N) - 1;
    return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

unsigned *md5(const char *msg, int mlen)
{
    static DigestArray h0 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    static DgstFctn ff[] = {&func0, &func1, &func2, &func3};
    static short M[] = {1, 5, 3, 7};
    static short O[] = {0, 1, 5, 0};
    static short rot0[] = {7, 12, 17, 22};
    static short rot1[] = {5, 9, 14, 20};
    static short rot2[] = {4, 11, 16, 23};
    static short rot3[] = {6, 10, 15, 21};
    static short *rots[] = {rot0, rot1, rot2, rot3};
    static unsigned kspace[64];
    static unsigned *k;
    static DigestArray h;
    DigestArray abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union
    {
        unsigned w[16];
        char b[64];
    } mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k == NULL)
        k = calctable(kspace);

    for (q = 0; q < 4; q++)
        h[q] = h0[q]; // Initialize

    grps = 1 + (mlen + 8) / 64;
    msg2 = (unsigned char *)malloc(64 * grps);
    memcpy(msg2, msg, mlen);
    msg2[mlen] = (unsigned char)0x80;
    q = mlen + 1;
    while (q < 64 * grps)
    {
        msg2[q] = 0;
        q++;
    }

    MD5union u;
    u.w = 8 * mlen;
    q -= 8;
    memcpy(msg2 + q, &u.w, 4);

    for (grp = 0; grp < grps; grp++)
    {
        memcpy(mm.b, msg2 + os, 64);
        for (q = 0; q < 4; q++)
            abcd[q] = h[q];
        for (p = 0; p < 4; p++)
        {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p];
            o = O[p];
            for (q = 0; q < 16; q++)
            {
                g = (m * q + o) % 16;
                f = abcd[1] + rol(abcd[0] + fctn(abcd) + k[q + 16 * p] + mm.w[g], rotn[q % 4]);
                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p = 0; p < 4; p++)
            h[p] += abcd[p];
        os += 64;
    }

    free(msg2);
    return h;
}

int main()
{
    char msg[1024];
    printf("\n Prakash Koirala \n");

    printf("Enter the string to be encrypted using MD5:\n");
    if (fgets(msg, sizeof(msg), stdin) == NULL)
    {
        printf("Error reading input\n");
        return 1;
    }

    // Remove newline character if present
    msg[strcspn(msg, "\n")] = '\0';
    unsigned *d = md5(msg, strlen(msg));
    MD5union u;

    printf("\nMD5 Encryption Algorithm in C\n\n");
    printf("Input String to be Encrypted using MD5:\n\t%s", msg);
    printf("\n\nThe MD5 hash of the input string is:\n");
    printf("\t= 0x");
    for (int j = 0; j < 4; j++)
    {
        u.w = d[j];
        for (int k = 0; k < 4; k++)
            printf("%02x", u.b[k]);
    }
    printf("\n");
    printf("\nMD5 Encryption Successfully Completed!!!\n\n");

    return 0;
}