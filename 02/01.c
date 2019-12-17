#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 1000000

void testInstructions(int * instructions) {

    int idx = 0;
    while(idx < 160) {
        printf("Instruction n%d: %d\n", idx, instructions[idx]);
        idx++;
    }

    return;
}

int readInstructions(int * dest, FILE * fp) {
    char currInstruction[5];
    char currChar;

    fp = fopen("input.txt", "r");

    if(fp == NULL) {
        printf("File could not be open at %s", "input.txt");
        return -1;
    }

    currChar = fgetc(fp);
    int currInstPos = 0;
    int instIndex = 0;

    while(currChar != EOF){
        if(isdigit(currChar)) {
            currInstruction[currInstPos] = currChar;
            currInstPos++;
        } else if (currChar == ',' || currChar == '\n') {
            currInstruction[currInstPos] = '\0';
            dest[instIndex] = atoi(currInstruction);
            instIndex++;

            currInstPos = 0;
            memset(currInstruction, '\0', 5);
        }
        currChar = fgetc(fp);
    }

    fclose(fp);
}

int instructionCalc(int op, int a, int b) {
    if(op == 1){
        return a + b;
    } else {
        return a * b;
    }
}

void processInstructions(int * instructions) {
    int idx = 0;
    int calc;
    int dest;

    while(instructions[idx] != -1) {
        dest = instructions[idx + 3];
        calc = instructionCalc(instructions[idx], instructions[idx+1], instructions[idx+2]);
        instructions[dest] = calc;
        idx += 4;
    }
}

void printInstructions(int * instructions, char * filename) {
    int idx = 0;
    FILE * fd = fopen(filename, "w");

    fprintf(fd, "%d", instructions[idx]);
    idx++;

    while(instructions[idx] != -1) {
        fprintf(fd, ",%d", instructions[idx]);
        idx++;
    }
}

void swapPositions(int * instructions) {
    instructions[1] = 12;
    instructions[2] = 2;
}


int main() {

    FILE *fp;
    int instructions[MAXCHAR];
    memset(instructions, -1, MAXCHAR);
    
    if(readInstructions(instructions, fp) == -1){
        return -1;
    }

    swapPositions(instructions);

    processInstructions(instructions);

    printInstructions(instructions, "output.txt");

    return 0;
}