#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef MESLEN
#define MESLEN 64
#endif
int * lshift(int arr[], int len, int n, int *lshifted); // lshift arr of len by n and store to lshifted

char * hexToBin(char arr[], int len);
void printIntArr(int [], int len);

int * intdup(int const * src, size_t len); // duplicate int array from source to ...
int * keyFromPC2(int *C, int *D, int len, int *K);
// 0123456789ABCDEF 133457799BBCDFF1
char HEXMES[16];
char HEXKEY[16];
char *K;
char *M;
int L[MESLEN/2];
int R[MESLEN/2];
int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    28, 13, 5, 28, 20, 12, 4
};
int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 
};
int main(int argc, char const *argv[])
{
    int i, j, hexcToI[4];
    int Kplus[56];
    int noOfShifts[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1}, count = 0;
    int lenK, lenM;
    int temp;
    int MIP[MESLEN];

    int C0[28], D0[28];
    int *C1, *C2, *C3, *C4, *C5, *C6, *C7, *C8, *C9, *C10, *C11, *C12, *C13, *C14, *C15, *C16;
    int *D1, *D2, *D3, *D4, *D5, *D6, *D7, *D8, *D9, *D10, *D11, *D12, *D13, *D14, *D15, *D16;
    int *K1, *K2, *K3, *K4, *K5, *K6, *K7, *K8, *K9, *K10, *K11, *K12, *K13, *K14, *K15, *K16;
    printf("Enter the hex message(16 hex chars) : ");
    fgets(HEXMES, 18, stdin);
    lenM = strlen(HEXMES) - 1;
    /* we need to convert hex to bin */
    fputs(HEXMES, stdout);

    M = hexToBin(HEXMES, lenM);
    printf("Inside the main\n");
    fputs(M, stdout);
    printf("\n");

    // create L and R out of M
    for (i = 0; i < MESLEN/2; ++i)
    {
        L[i] = (int)(M[i] - '0');
    }
    j = 0;
    for(; i < MESLEN; i++)
    {
        R[j] = (int)(M[i] - '0');
        j++;
    }
    printf("Printing L and R made out of M\n");
    printf("Printing L\n");
    printIntArr(L, MESLEN/2);
    printf("\nPrinting R\n");
    printIntArr(R, MESLEN/2);
    printf("\n");

    printf("Enter the hex key(16)\n");
    fgets(HEXKEY, 18, stdin);
    lenK = strlen(HEXKEY) - 1;
    fputs(HEXKEY, stdout);
    K = hexToBin(HEXKEY, lenK);
    printf("Inside main\n");
    fputs(K, stdout);

    // get Kplus using K and PC1 matrix
    for(i = 0; i < 56; i++)
    {
        temp = PC1[i] - 1;
        Kplus[i] = (int)(K[temp] - '0');
    }
    printf("\nprinting Kplus\n");
    printIntArr(Kplus, 56);

    for (i = 0; i < 28; ++i)
    {
        C0[i] = Kplus[i];
    }
    j = 0;
    for(; i < 56; i++)
    {
        D0[j] = Kplus[i];
        j++;
    }
    printf("Printing C0 and D0\n");
    printIntArr(C0, 28);
    printf("\n");
    printIntArr(D0, 28);
    printf("\n");


    // malloc'ing each C and D and also K's
    {
        
        C1 = malloc(sizeof(C0));
        C2 = malloc(sizeof(C0));
        C3 = malloc(sizeof(C0));
        C4 = malloc(sizeof(C0));
        C5 = malloc(sizeof(C0));
        C6 = malloc(sizeof(C0));
        C7 = malloc(sizeof(C0));
        C8 = malloc(sizeof(C0));
        C9 = malloc(sizeof(C0));
        C10 = malloc(sizeof(C0));
        C11 = malloc(sizeof(C0));
        C12 = malloc(sizeof(C0));
        C13 = malloc(sizeof(C0));
        C14 = malloc(sizeof(C0));
        C15 = malloc(sizeof(C0));
        C16 = malloc(sizeof(C0));
        
        D1 = malloc(sizeof(D0));
        D2 = malloc(sizeof(D0));
        D3 = malloc(sizeof(D0));
        D4 = malloc(sizeof(D0));
        D5 = malloc(sizeof(D0));
        D6 = malloc(sizeof(D0));
        D7 = malloc(sizeof(D0));
        D8 = malloc(sizeof(D0));
        D9 = malloc(sizeof(D0));
        D10 = malloc(sizeof(D0));
        D11 = malloc(sizeof(D0));
        D12 = malloc(sizeof(D0));
        D13 = malloc(sizeof(D0));
        D14 = malloc(sizeof(D0));
        D15 = malloc(sizeof(D0));
        D16 = malloc(sizeof(D0));


        K1 = malloc(sizeof(PC2));
        K2 = malloc(sizeof(PC2));
        K3 = malloc(sizeof(PC2));
        K4 = malloc(sizeof(PC2));
        K5 = malloc(sizeof(PC2));
        K6 = malloc(sizeof(PC2));
        K7 = malloc(sizeof(PC2));
        K8 = malloc(sizeof(PC2));
        K9 = malloc(sizeof(PC2));
        K10 = malloc(sizeof(PC2));
        K11 = malloc(sizeof(PC2));
        K12 = malloc(sizeof(PC2));
        K13 = malloc(sizeof(PC2));
        K14 = malloc(sizeof(PC2));
        K15 = malloc(sizeof(PC2));
        K16 = malloc(sizeof(PC2));
    }
    // getting C1-16 and D1-16
    {
        C1 = lshift(C0, 28, noOfShifts[count], C1);
        D1 = lshift(D0, 28, noOfShifts[count++], D1);
        C2 = lshift(C1, 28, noOfShifts[count], C2);
        D2 = lshift(D1, 28, noOfShifts[count++], D2);
        C3 = lshift(C2, 28, noOfShifts[count], C3);
        D3 = lshift(D2, 28, noOfShifts[count++], D3);
        C4 = lshift(C3, 28, noOfShifts[count], C4);
        D4 = lshift(D3, 28, noOfShifts[count++], D4);
        C5 = lshift(C4, 28, noOfShifts[count], C5);
        D5 = lshift(D4, 28, noOfShifts[count++], D5);
        C6 = lshift(C5, 28, noOfShifts[count], C6);
        D6 = lshift(D5, 28, noOfShifts[count++], D6);
        C7 = lshift(C6, 28, noOfShifts[count], C7);
        D7 = lshift(D6, 28, noOfShifts[count++], D7);
        C8 = lshift(C7, 28, noOfShifts[count], C8);
        D8 = lshift(D7, 28, noOfShifts[count++], D8);
        C9 = lshift(C8, 28, noOfShifts[count], C9);
        D9 = lshift(D8, 28, noOfShifts[count++], D9);
        C10 = lshift(C9, 28, noOfShifts[count], C10);
        D10 = lshift(D9, 28, noOfShifts[count++], D10);
        C11 = lshift(C10, 28, noOfShifts[count], C11);
        D11 = lshift(D10, 28, noOfShifts[count++], D11);
        C12 = lshift(C11, 28, noOfShifts[count], C12);
        D12 = lshift(D11, 28, noOfShifts[count++], D12);
        C13 = lshift(C12, 28, noOfShifts[count], C13);
        D13 = lshift(D12, 28, noOfShifts[count++], D13);
        C14 = lshift(C13, 28, noOfShifts[count], C14);
        D14 = lshift(D13, 28, noOfShifts[count++], D14);
        C15 = lshift(C14, 28, noOfShifts[count], C15);
        D15 = lshift(D14, 28, noOfShifts[count++], D15);
        C16 = lshift(C15, 28, noOfShifts[count], C16);
        D16 = lshift(D15, 28, noOfShifts[count++], D16);
    }
    // printIntArr(C1, 28); works now


    // getting K1- 16 using PC2
    {

        K1 = keyFromPC2(C1, D1, 48, K1);
        K2 = keyFromPC2(C2, D2, 48, K2);
        K3 = keyFromPC2(C3, D3, 48, K3);
        K4 = keyFromPC2(C4, D4, 48, K4);
        K5 = keyFromPC2(C5, D5, 48, K5);
        K6 = keyFromPC2(C6, D6, 48, K6);
        K7 = keyFromPC2(C7, D7, 48, K7);
        K8 = keyFromPC2(C8, D8, 48, K8);
        K9 = keyFromPC2(C9, D9, 48, K9);
        K10 = keyFromPC2(C10, D10, 48, K10);
        K11 = keyFromPC2(C11, D11, 48, K11);
        K12 = keyFromPC2(C12, D12, 48, K12);
        K13 = keyFromPC2(C13, D13, 48, K13);
        K14 = keyFromPC2(C14, D14, 48, K14);
        K15 = keyFromPC2(C15, D15, 48, K15);
        K16 = keyFromPC2(C16, D16, 48, K16);
    }
    // printIntArr(K12, 48);

    for(i = 0; i < MESLEN; i++)
    {
        temp = IP[i];
        printf("i is %d ip is %d M is %c\n", i, IP[i], M[temp-1]);
        MIP[i] = (int) (M[temp-1] - '0');
    }
    printf("\nprinting mip\n");
    printIntArr(MIP, 64);


    // getting L0 and R0 from MIP
    for(i = 0; i < MESLEN / 2; i++)
    {
        L0[i] = MIP[i];
    }
    for(; i < MESLEN; i++)
    {
        R0[i-28] = MIP[i];
    }
    // freeing malloc'ed
    {
        free(K);
        free(M);
    }
    return 0;
}

void printIntArr(int intArr[], int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("%d", intArr[i]);
    }
    printf("\n");
}

char * hexToBin(char arr[], int len)
{
    int i;
    char hexc;
    char *binArray;
    binArray = malloc((len*4)*sizeof(char));
    for(i=0; i<=strlen(arr)-1; i++){
        // if(isalpha(arr[i])) hexc = toupper(arr[i]);
        // else hexc = arr[i];
        hexc = arr[i];
        printf("%c\n", hexc);
        switch(hexc){
            case '0':
                strcat(binArray, "0000");
                break;
            case '1':
                strcat(binArray, "0001");
                break;
            case '2':
                strcat(binArray, "0010");
                break;
            case '3':
                strcat(binArray, "0011");
                break;
            case '4':
                strcat(binArray, "0100");
                break;
            case '5':
                strcat(binArray, "0101");
                break;
            case '6':
                strcat(binArray, "0110");
                break;
            case '7':
                strcat(binArray, "0111");
                break;
            case '8':
                strcat(binArray, "1000");
                break;
            case '9':
                strcat(binArray, "1001");
                break;
            case 'A':
                strcat(binArray, "1010");
                break;
            case 'B':
                strcat(binArray, "1011");
                break;
            case 'C':
                strcat(binArray, "1100");
                break;
            case 'D':
                strcat(binArray, "1101");
                break;
            case 'E':
                strcat(binArray, "1110");
                break;
            case 'F':
                strcat(binArray, "1111");
                break;
        }
    }
    printf("Inside the function\n");
    fputs(binArray, stdout);
    printf("\n");
    return binArray;
}
// lshift arr of len n by n and store in lshifted pointer
int * lshift(int arr[], int len, int n, int *lshifted)
{
    int i, j, temp;
    lshifted = intdup(arr, len);
    for(i = 0; i < n; i++){
        printf("count = %d\n", i);
        temp = lshifted[0];
        for(j = 0; j < len - 1; j++)
        {
            lshifted[j] = lshifted[j+1];
        }
        lshifted[len-1] = temp;
    }
    return lshifted;
}

int * intdup(int const * src, size_t len) // duplicate int array from source to ...
{
   int * p = malloc(len * sizeof(int));
   if(p == NULL) exit(-1);
   memcpy(p, src, len * sizeof(int));
   return p;
}
int * keyFromPC2(int *C, int *D, int len, int *K)
{
    int i = 0, val;
    for(; i < len; i++)
    {
        val = PC2[i];
        if(val <= 28)
            K[i] = C[val-1];
        else
            K[i] = D[val-28-1];
    }
    return K;
}