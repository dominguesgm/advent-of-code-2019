#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 1000

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

int instructionCalc(int * instructions, int op, int a, int b) {
    // printf("Op: %d, valA: %d, valB: %d\n", op, instructions[a], instructions[b]);
    if(a > MAXCHAR - 1 || b > MAXCHAR - 1) return -1;
    if(op == 1){
        return instructions[a] + instructions[b];
    } else {
        return instructions[a] * instructions[b];
    }
}

int processInstructions(int * instructions) {
    int idx = 0;
    int calc;
    int dest;

    while(instructions[idx] != -1) {
        // Opcode 99 halts execution
        if(instructions[idx] == 99) {
            // printf("Process halted on instruction %d, surrounded by %d and %d\n", idx, instructions[idx-1], instructions[idx+1]);
            return 0;
        }
        dest = instructions[idx + 3];
        calc = instructionCalc(instructions, instructions[idx], instructions[idx+1], instructions[idx+2]);
        if(dest > MAXCHAR - 1 || calc == -1) return -1;
        // printf("Writing result %d to address %d\n", calc, dest);
        instructions[dest] = calc;
        idx += 4;
    }
    return 0;
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

    fclose(fd);
}

void swapPositions(int * instructions, int name, int verb) {
    instructions[1] = name;
    instructions[2] = verb;
}

void resetInstructions(int * dest, int * src) {
    memcpy(dest, src, MAXCHAR);
}

void findNounVerb(int * baseInstructions) {
    printf("got here\n");
    int instructions[MAXCHAR];
    

    int name = 0, verb;
    int worked = 0;

    while(name < 1000) {
        verb = 0;
        while(verb < 1000) {
            resetInstructions(instructions, baseInstructions);
            swapPositions(instructions, name, verb);

            processInstructions(instructions);

            if(instructions[0] == 19690720) {
                worked = 1;
                break;
            }

            if(name == 12 && verb == 2) {
                testInstructions(instructions);
                // printf("Tried %d and %d, result %d\n", name, verb, instructions[0]);
            }


            verb++;
        }
        if(instructions[0] == 19690720) {
            break;
        }

        name++;
    }

    printf("Worked: %s", worked ? "yes\n" : "no\n");
    printf("Name: %d\n", name);
    printf("Verb: %d\n", verb);

}

int main() {

    FILE *fp;
    int instructions[MAXCHAR];
    int baseInstructions[MAXCHAR];
    memset(baseInstructions, -1, MAXCHAR);
    
    if(readInstructions(baseInstructions, fp) == -1){
        return -1;
    }

    resetInstructions(instructions, baseInstructions);

    swapPositions(instructions, 12, 2);

    processInstructions(instructions);

    printInstructions(instructions, "output.txt");

    printf("Result is %d\n", instructions[0]);

    findNounVerb(baseInstructions);

    return 0;
}