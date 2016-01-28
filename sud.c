// cc -std=c11 sud.c -o sud

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool should_exclude(const uint8_t i, const uint8_t j, const uint8_t* const s) {
    return (i/9 == j/9) || ((i-j)%9 == 0) || (i/27 == j/27 && (i%9)/3 == (j%9)/3);
}

uint8_t find(const uint8_t c, const uint8_t* const s) {
    uint8_t i = 0;
    for (; i < 81; i++)
        if (s[i] == c)
            return i;
    return i;
}

void print(const uint8_t* const s) {
    for (uint8_t l = 0; l < 3; l++) {
        for (uint8_t i = 0; i < 3; i++) {
            for (uint8_t j = 0; j < 3; j++) {
                for (uint8_t k = 0; k < 3; k++) {
                    printf("%d ", s[k + 3*j + 9*i + 27*l] - '0');
                }
                printf("| ");
            }
            printf("\n");
        }
        printf("------+-------+-------+\n");
    }
}

void r(const uint8_t* const s) {
    uint8_t i = find('0', s);
    if (i == 81) {
        print(s);
        exit(0);
    }

    bool exclude[9] = {false};
    for (uint8_t j = 0; j < 81; j++) {
        if (s[j] != '0' && should_exclude(i, j, s)) {
            exclude[s[j] - '1'] = true;
        }
    }

    for (uint8_t m = 0; m < 9; m++) {
        if (!exclude[m]) {
            uint8_t t[81];
            memcpy(t, s, 81);
            t[i] = m + '1';
            r(t);
        }
    }
}

int main(int argc, const char const *argv[]) {
    if (argc == 2) {
        uint8_t s[81] = {0};
        memcpy(s, argv[1], 81);
        r(s);
    }
    fprintf(stderr, "Usage: sudoku puzzle\n");
    fprintf(stderr, "where puzzle is an 81 character string representing the puzzle read left-to-right, top-to-bottom, and 0 is a blank\n");
    return 1;
}

// 530070000600195000098000060800060003400803001700020006060000280000419005000080079