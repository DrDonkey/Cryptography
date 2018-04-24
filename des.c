#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#ifndef MESLEN
#define MESLEN 64
#endif

// functions
int * lshift(int arr[], int len, int n, int *lshifted); // lshift arr of len by n and store to lshifted

char * hexToBin(char arr[], int len);
void printIntArr(int [], int len);

int * intdup(int const * src, size_t len); // duplicate int array from source to ...
int * keyFromPC2(int *C, int *D, int len, int *K);
unsigned int int_to_bin(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_bin(k / 2)));
}
// 0123456789ABCDEF 133457799BBCDFF1
// global variables
char HEXMES[16];
char HEXKEY[16];
char *K;
char *M;
int L[MESLEN/2];
int R[MESLEN/2];
// matrices
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

int L0[] = {
    1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 1,1,0,0, 1,1,0,0, 1,1,1,1, 1,1,1,1
};
int R0[] = {
    1,1,1,1, 0,0,0,0, 1,0,1,0, 1,0,1,0, 1,1,1,1, 0,0,0,0, 1,0,1,0, 1,0,1,0
};
int K1[] = {
    0,0,0,1,1,0, 1,1,0,0,0,0, 0,0,1,0,1,1, 1,0,1,1,1,1, 1,1,1,1,1,1, 0,0,0,1,1,1, 0,0,0,0,0,1, 1,1,0,0,1,0
};
int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};
int S1[] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
};

int S2[] = {
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
};

int S3[] = {
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 5, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
};

int S4[] = {
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
};

int S5[] = {
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
};

int S6[] = {
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
};

int S7[] = {
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
};

int S8[] = {
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 3, 15, 12, 9, 0, 3, 5, 6, 11
};

int P[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 23, 30, 6,
    22, 11, 4, 25
};

int IP_1[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9,  49, 17, 57, 25
};

// start of main
int main(int argc, char const *argv[])
{
    // initialization things: 
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


    int *L1, L2, *L3, *L4, *L5, *L6, *L7, *L8, *L9, *L10, *L11, *L12, *L13, *L14, *L15, *L16;
    int *R1, *R2, *R3, *R4, *R5, *R6, *R7, *R8, *R9, *R10, *R11, *R12, *R13, *R14, *R15, *R16;
    int *RL;
    int *result;
    int location;

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
    // getting C1-16 and D1-16
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

    // malloc'ing for L and R:
    {
        L1 = malloc(sizeof(L0));
        R1 = malloc(sizeof(R0));
        RL = malloc(64 * sizeof(int)); // to store R16L16
        result = malloc(64 * sizeof(int)); // to store final encrypted value(in bin)
    }

    // calculating L and R upto 16
    {
        L1 = R0;
        R1 = calculateR(L0, R0, K1);
        L2 = R1;
        R2 = calculateR(L1, R1, K2);
        L3 = R2;
        R3 = calculateR(L2, R2, K3);
        L4 = R3;
        R4 = calculateR(L3, R3, K4);
        L5 = R4;
        R5 = calculateR(L4, R4, K5);
        L6 = R5;
        R6 = calculateR(L5, R5, K6);
        L7 = R6;
        R7 = calculateR(L6, R6, K7);
        L8 = R7;
        R8 = calculateR(L7, R7, K8);
        L9 = R8;
        R9 = calculateR(L8, R8, K9);
        L10 = R9;
        R10 = calculateR(L9, R9, K10);
        L11 = R10;
        R11 = calculateR(L10, R10, K11);
        L12 = R11;
        R12 = calculateR(L11, R11, K12);
        L13 = R12;
        R13 = calculateR(L12, R12, K13);
        L14 = R13;
        R14 = calculateR(L13, R13, K14);
        L15 = R14;
        R15 = calculateR(L14, R14, K15);
        L16 = R15;
        R16 = calculateR(L15, R15, K16);
    }

    // R16L16
    for(i = 0; i < 32; i++)
    {
        RL[i] = R16[i];
    }
    for(; i < 32; i++)
    {
        RL[i] = L16[i];
    }

    // Applying IP-1 to R16L16
    for(i = 0; i < 64; i++)
    {
        location = IP_1[i];
        result[i] = RL[location];
    }


    // freeing malloc'ed
    {
        free(K);
        free(M);
    }
    return 0;
}
// end of main

void printIntArr(int intArr[], int len) // prints int array of length len
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("%d", intArr[i]);
    }
    printf("\n");
}

char * hexToBin(char arr[], int len) // hex to binary of hex length len
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

int * calculateR(int *L, int *R, int *K) //L0 ^ fun(E(R0) ^ K1)
{
    int i, index, sRowNo, sColNo, num, pos = 0;
    int row, col;
    int *store, *tmp;
    int *final;
    store = malloc(48 * sizeof(int));
    final = malloc(32 * sizeof(int));
    tmp = malloc(32 * sizeof(int));

    for(i = 0; i < 48; i++)
    {
        index = E[i] - 1;
        store[i] = R[index] ^ K[i];
    }
    // S Boxing
    {
        i = 0;
        pos = 0;
        // S1
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S1[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;

        // S2
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S2[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S3
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S3[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S4
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S4[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S5
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S5[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S6
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S6[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S7
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S7[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
        // S8
        row = (store[pos] * 10) + store[pos + 5];
        col = (store[pos+1] * 1000) + (store[pos+2] * 100) + (store[pos+3] * 10) + store[pos+4];
        num = bin_to_int(S8[16*(row-1)+col]);
        pos += 6;

        tmp[i+3] = num % 10;
        num /= 10;
        tmp[i+2] = num % 10;
        num /= 10;
        tmp[i+1] = num % 10;
        num /= 10;
        tmp[i] = num;
        i += 4;
    }

    // calculating final R
    for(i = 0; i < 32; i++)
    {
        final[i] = L[i] ^ final[i];
    }
    return final;
}
int bin_to_int(int n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}