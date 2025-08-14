#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char at(char board[82], int r, int c) { return board[r*9 + c]; }

bool find_disallowed(char board[82], int r, int c, bool result[10]) {
    for (int _r = 0; _r < 9; _r++) {
        result[at(board, _r, c) - '0'] = true;
    }
    for (int _c = 0; _c < 9; _c++) {
        result[at(board, r, _c) - '0'] = true;
    }
    int tlr = r - r%3;
    int tlc = c - c%3;
    for (int _r = tlr; _r < tlr + 3; _r++) {
        for (int _c = tlc; _c < tlc + 3; _c++) {
            result[at(board, _r, _c) - '0'] = true;
        }
    }
}

// bool same_box(int i, int j) { return i/27 == j/27 && (i%9)/3 == (j%9)/3; }
// bool valid(char board[82]) {
//     for (int i = 0; i < 81; i++) {
//         for (int j = 0; j < 81; j++) {
//             if (i == j) { continue; }
//             int r1 = i/9, c1 = i%9;
//             int r2 = j/9, c2 = j%9;
//             if (r1 == r2 && board[i] == board[j]) { return false; }
//             if (c1 == c2 && board[i] == board[j]) { return false; }
//             if (same_box(i, j) && board[i] == board[j]) { return false; }
//         }
//     }
//     return true;
// }

bool helper(char board[82], int r, int c) {
    if (r == 8 && c == 9) {
        return true;
    }
    if (c == 9) {
        r += 1;
        c = 0;
    }
    if (at(board, r, c) != '0') {
        return helper(board, r, c+1);
    }
    bool cant_use[10] = {false};
    find_disallowed(board, r, c, cant_use);
    for (char new = '1'; new <= '9'; new++) {
        if (!cant_use[new - '0']) {
            board[r*9 + c] = new;
            if (helper(board, r, c+1)) {
                return true;
            }
            board[r*9 + c] = '0';
        }
    }
    return false;
}

bool solve(char board[82]) { return helper(board, 0, 0); }

int main() {
    const int NUM_TESTCASES = 2;
    const char* testcases[2] = {
        "000000304005001000000690100809010000200000000000700006000003010001080290003065400",
        "530070000600195000098000060800060003400803001700020006060000280000419005000080079",
    };
    const char *expected[2] = {
       "197258364465371829382694157839516742276849531514732986748923615651487293923165478",
       "534678912672195348198342567859761423426853791713924856961537284287419635345286179", 
    };
    for (int i = 0; i < NUM_TESTCASES; i++) {
        char board[82];
        strncpy(board, testcases[i], 82);

        printf("Testcase %d:\n\nInput: %s\n", i+1, board);
        printf("Expected: %s\n", expected[i]);
        
        if (!solve(board)) {
            printf("Actual: failure: could not solve\n");
        } else if (strncmp(board, expected[i], 81) != 0) {
            printf("Failure. Got: %s\n", board);
        } else {
            printf("Success\n");
        }
        printf("...\n");
    }
}
