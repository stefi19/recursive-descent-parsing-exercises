# Recursive Descent Parsing Exercises

This repository contains three hand-written recursive descent interpreters in C, each paired with a Flex lexer.

## Contents

- `ex1.c`, `ex1.l` - symbolic polynomial addition/subtraction over `Y`
- `ex2.c`, `ex2.l` - list operations (`head`, `length`, `tail`, `:`, `++`)
- `ex3.c`, `ex3.l` - list transformations (`map inc/dec`, `filter odd/even`, `++`)

## Requirements

- `flex`
- C compiler (`gcc` or `clang`)
- Lex library (`-ll`)

## Build

From this folder:

```bash
cd "/Users/stefi/Desktop/Uni/SEM2/FLT/LAB/Exercises/recursive-descent-parsing-exercises"

flex -o ex1_lex.c ex1.l
gcc -std=c11 -Wall -Wextra -o ex1 ex1.c ex1_lex.c -ll

flex -o ex2_lex.c ex2.l
gcc -std=c11 -Wall -Wextra -o ex2 ex2.c ex2_lex.c -ll

flex -o ex3_lex.c ex3.l
gcc -std=c11 -Wall -Wextra -o ex3 ex3.c ex3_lex.c -ll
```

## Exercise 1: Polynomials

Interpreter for symbolic addition and subtraction over one-variable polynomials.

### Supported monomials

- `i Y ^ i`
- `i Y`
- `Y ^ i`
- `Y`
- `i`

### Example

```bash
printf "(2 Y ^ 3 + 3 Y ^ 2 - Y + 5) + (Y ^ 2 - 4) - (2 Y + 1)\n" | ./ex1
```

Expected output:

```text
2 Y ^ 3 + 4 Y ^ 2 - 3 Y
```

## Exercise 2: Lists (head/length/tail)

List interpreter with:

- `head <listExpr>`
- `length <listExpr>`
- `tail <listExpr>`
- `value : listExpr` (cons)
- `listExpr ++ listExpr` (concatenation)

### Example run

```bash
printf "head [10,20,30]\nlength (1:[2,3])\ntail ([1,2] ++ [3,4])\n" | ./ex2
```

Expected output:

```text
10
3
[2, 3, 4]
```

## Exercise 3: Lists (map/filter)

List interpreter with:

- `map inc <listExpr>`
- `map dec <listExpr>`
- `filter odd <listExpr>`
- `filter even <listExpr>`
- `listExpr ++ listExpr`

### Example run

```bash
printf "map inc [1,2,3]\nfilter odd ([1,2,3] ++ [4,5,6])\n" | ./ex3
```

Expected output:

```text
[2, 3, 4]
[1, 3, 5]
```

## Error handling

All interpreters print:

```text
Syntax Error
```

for invalid input and terminate.

