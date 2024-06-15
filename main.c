#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int digit;              // certainly is one of the digits (1-9)
    bool* possible_digit;   // array of 9, if digit was not ruled out -> index-1 = 1, else index-1 = 0
} cell;

typedef struct {
    cell* data;
} sudoku9x9;

void init_sudoku(sudoku9x9* s);
void destroy_sudoku(sudoku9x9* s);
void print_sudoku(sudoku9x9* s);

int main() {
    sudoku9x9 s;
    init_sudoku(&s);

    // for now sudoku is filled with digits 0-9 over and over
    for (int i = 0; i < 81; i++) 
        s.data[i].digit = i % 10;

    print_sudoku(&s);
    

    destroy_sudoku(&s);
}

void init_sudoku(sudoku9x9* s) {
    s->data = malloc(81 * sizeof(cell));
    if (s->data == NULL) {
        fprintf(stderr, "malloc failed");
        exit(1);
    }

    for (int i = 0; i < 81; i++) {
        s->data[i].possible_digit = malloc(9 * sizeof(bool));
        if (s->data[i].possible_digit == NULL) {
            // free everything allocated so far
            for (int j = 0; j < i; j++)
                free(s->data[j].possible_digit);

            free(s->data);

            fprintf(stderr, "malloc failed");
            exit(1);
        }
    }
}

void destroy_sudoku(sudoku9x9* s) {
    for (int i = 0; i < 81; i++)
        free(s->data[i].possible_digit);
    free(s->data);   
}

void print_sudoku(sudoku9x9* s) {
    for (int i = 0; i < 19; i++)
        if (i % 6 == 0)         // horizontal squares' border
            printf("++===+===+===++===+===+===++===+===+===++\n");
        else if (i % 2 == 0)    // horizontal border that is inside of the squares
            printf("++---+---+---++---+---+---++---+---+---++\n");
        else {
            printf("||");       // vertical squares' border
            for (int j = 0; j < 9; j++) {
                printf(" %i |", s->data[j + i/2 * 9].digit);
                if (j % 3 == 2) printf("|");    // vertical squares' border
            }
            printf("\n");
        }
}