// On Windows with MinGW: cc sudoku.c -std=c23; ./a.exe

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_TESTCASES 6

// Boards are stored as 82-character strings. The 82nd character is '\0'.
// '0' represents a blank square. '1' represents the number 1, '2' represents
// the number 2, and so on.
char at(char board[82], int r, int c) { return board[r*9 + c]; }

// Set index i of `result` to `true` if the cell at (r, c) in `board` cannot
// be set to the character representing the number i. Else, leave it untouched.
// Do this for all i from 0 to 9 inclusive.
//
// For example, if there is a 5 at row (2, 3) then
// `find_disallowed(board, 2, 7, result)` will set `result[5]` to `false`.
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

// True if and only if indices i and j lie in the same box.
bool same_box(int i, int j) { return i/27 == j/27 && (i%9)/3 == (j%9)/3; }

// True if and only if this is a solved board.
bool solved(char board[82]) {
    for (int i = 0; i < 81; i++) {
        for (int j = 0; j < 81; j++) {
            if (i == j) { continue; }
            int r1 = i/9, c1 = i%9;
            int r2 = j/9, c2 = j%9;
            if (r1 == r2 && board[i] == board[j]) { return false; }
            if (c1 == c2 && board[i] == board[j]) { return false; }
            if (same_box(i, j) && board[i] == board[j]) { return false; }
        }
    }
    return true;
}

// Backtracking helper function.
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

// Driver function.
bool solve(char board[82]) { return helper(board, 0, 0); }

int main(int argc, [[maybe_unused]] char* argv[argc+1]) {
    const char* testcases[NUM_TESTCASES] = {
        "000000304005001000000690100809010000200000000000700006000003010001080290003065400",
        "530070000600195000098000060800060003400803001700020006060000280000419005000080079",
        "800000000003600000070090200050007000000045700000100030001000068008500010090000400",
        "000000039000010005003005800008009006070020000100400000009008050020000600400700000",
        "002800000030060007100000040600090000050600009000057060000300100070006008400000020",
        "600008940900006100070040000200610000000000200089002000000060005000000030800001600",
    };
    const char *expected[NUM_TESTCASES] = {
       "197258364465371829382694157839516742276849531514732986748923615651487293923165478",
       "534678912672195348198342567859761423426853791713924856961537284287419635345286179",
       "812753649943682175675491283154237896369845721287169534521974368438526917796318452",
       "751864239892317465643295871238179546974526318165483927319648752527931684486752193",
       "742835691539461287186972543618293754257684319394157862825349176971526438463718925",
       "625178943948326157371945862257619384463587291189432576792863415516294738834751629",
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
    return EXIT_SUCCESS;
}
