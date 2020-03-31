#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void parseString(char *buf, int numOfStr);

void printResult(char *metkaStr, char *operatorStr, char *operandStr, char *commentStr, int numOfStr);

bool checkIfOperatorCorrect(char *str);

char commentSymbol = ';';

int main(void) {
    int numberOfStr = 1;
    const char *pathToFile = "../kek.txt";
    char *line_buf = (char *) malloc(255 * sizeof(char));
    size_t line_buf_size = 0;
    ssize_t line_size;
    FILE *fp = fopen(pathToFile, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", "kek.txt");
        return EXIT_FAILURE;
    }
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0) {
        parseString(line_buf, numberOfStr);
        numberOfStr++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    line_buf = NULL;
    free(line_buf);
    fclose(fp);

    return EXIT_SUCCESS;
}


void appending(char *cArr, const char c) {
    unsigned long len = strlen(cArr);
    cArr[len] = c;

}

bool isEmpty(const char *str) {
    return str == NULL || str[0] == '\0';
}

void parseString(char *buf, int numOfStr) {
    int i = 0;
    const int lenOf = strlen(buf);
    char ch;
    if (buf[0]=='\n'){
        printResult(NULL,NULL,NULL,NULL,numOfStr);
        return;
    }
    //// нахождение метки
    char *metkaStr = (char *) malloc(lenOf * sizeof(char));
    if (buf[0] != ' ' && buf[0]!= commentSymbol) {
        for (i; i < lenOf; i++) {
            ch = buf[i];
            if (ch == ' ') break;
            appending(metkaStr, ch);

        }
        i++;
    }

    //////////

    ch = buf[i];
    //// нахождение первого слова
    while (ch == ' ' && i < lenOf) {
        i++;
        ch = buf[i];
    }
    ////

    char *tempStr = (char *) malloc(lenOf * sizeof(char));
    char *operatorStr = (char *) malloc(lenOf * sizeof(char));
    char *operandStr = (char *) malloc(lenOf * sizeof(char));
    char *commentStr = (char *) malloc(lenOf * sizeof(char));
    bool nextOperand = false;
    for (i; i < lenOf; i++) {
        ch = buf[i];
        if (ch == ' ' || ch == '\n') {
            if (tempStr[0] == commentSymbol) {
                commentStr = ++tempStr;
                tempStr = (char *) malloc(lenOf * sizeof(char));
                continue;
            }
            if (nextOperand) {
                operandStr = tempStr;
                tempStr = (char *) malloc(lenOf * sizeof(char));
                continue;
            }

            if (checkIfOperatorCorrect(tempStr)) {
                operatorStr = tempStr;
                nextOperand = true;
            }
            tempStr = (char *) malloc(lenOf * sizeof(char));
            continue;

        }
        appending(tempStr, ch);
    }
    if (isEmpty(operatorStr) && isEmpty(operandStr)) operatorStr = tempStr;
    if (operatorStr == operandStr) operandStr = NULL;

    printResult(metkaStr, operatorStr, operandStr, commentStr, numOfStr);
    metkaStr = NULL;
    free(metkaStr);
    operatorStr = NULL;
    free(operatorStr);
    tempStr = NULL;
    free(tempStr);
    commentStr = NULL;
    free(commentStr);

}

bool checkIfOperatorCorrect(char *str) {
    if (strcmp(str, "START") == 0 || strcmp(str, "END") == 0 || strcmp(str, "BYTE") == 0 || strcmp(str, "WORD") == 0 ||
        strcmp(str, "RESB") == 0 || strcmp(str, "RESW") == 0) {
        return true;
    }
    return false;
}


void printDataWithMessage(const char *message, char *data) {
    printf("%s", message);
    if (data != NULL) {
        printf("%s", data);
    }

}

void printResult(char *metkaStr, char *operatorStr, char *operandStr, char *commentStr, int numOfStr) {
    printf("%d", numOfStr);
    printf("%s", ") ");
    printDataWithMessage("Метка: ", metkaStr);
    printDataWithMessage(" Оператор: ", operatorStr);
    printDataWithMessage(" Операнд: ", operandStr);
    printDataWithMessage(" Комментарий: ", commentStr);
    printf("\n");
}
