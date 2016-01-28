### Building

* C: `cc -std=c11 sud.c -o sud`
* Python: Nothing to be done here.
* Haskell: `ghc --make sud.hs`

### Running

* C: `./sud <puzzle>`
* Python: `python sud.py <puzzle>`
* Haskell: `./sud`, then enter the puzzle and hit `Enter`

`<puzzle>` is an 81-character string, each char of which is between `1` and `9`.

### Some Sudoku puzzles

A few puzzles for testing. I've tried to sort them in increasing order of difficulty, where difficulty is measured by the amount of time  the solvers take to find the solution.

* 530070000600195000098000060800060003400803001700020006060000280000419005000080079. Just a regular puzzle.
* [Arto Inkala's puzzle](http://www.sudokuwiki.org/Arto_Inkala_Sudoku): 800000000003600000070090200050007000000045700000100030001000068008500010090000400. It is claimed to be one of the hardest Sudoku puzzles.
* [Golden Nugget](http://www.sudokusnake.com/goldennugget.php): 000000039000010005003005800008009006070020000100400000009008050020000600400700000. It is claimed to be the one of the hardest Sudoku puzzles.
* [Unsolvable #49](http://www.sudokuwiki.org/Weekly_Sudoku.asp?puz=49): 002800000030060007100000040600090000050600009000057060000300100070006008400000020
* [Unsolvable #28](http://www.sudokuwiki.org/Weekly_Sudoku.asp?puz=28): 600008940900006100070040000200610000000000200089002000000060005000000030800001600

### Benchmarks

As far as I can tell, the C version is blazingly fast on all puzzles.

* [Golden Nugget](http://www.sudokusnake.com/goldennugget.php)
    * CPython takes about 11 seconds to solve it.
    * The C version solves it instantly.
* [Arto Inkala's puzzle](http://www.sudokuwiki.org/Arto_Inkala_Sudoku).
    * CPython takes about 2 seconds to solve it.
    * The C version solves it instantly.
* [Unsolvable #49](http://www.sudokuwiki.org/Weekly_Sudoku.asp?puz=49)
    * CPython takes about 2 minutes (!) to solve it.
    * The C version solves it in about 250 ms. Actually, the C version is blazingly fast on all puzzles as far as I can tell.
* [Unsolvable #28](http://www.sudokuwiki.org/Weekly_Sudoku.asp?puz=28)
    * CPython takes about 37 seconds to solve it.
    * The C version solves it in about 700 ms.

### TODO

* Haskell version is painfully slow everywhere. Need to optimise.
* More languages!

### Credits

* The Python reference implementation was taken from StackOverflow, [here](http://stackoverflow.com/a/201771) (credit: Bill Barksdale)