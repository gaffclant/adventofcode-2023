#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 512

// Simple function to reverse a string
void reverse(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0, k = len - 1; i < (len / 2); i++, k--) {
        char temp = str[k];
        str[k] = str[i];
        str[i] = temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("File not found: %s", argv[1]);
        return 1;
    }

    size_t linesize = LINESIZE;
    char *line = malloc(linesize);
    int result = 0;
    while (-1 != getline(&line, &linesize, file)) {
        size_t firstnum = strcspn(line, "0123456789");
        int tens = 10 * (line[firstnum] - 48);

        reverse(line);

        size_t lastnum = strcspn(line, "0123456789");
        int ones = (line[lastnum] - 48);

        result += tens + ones;
    }
    printf("%i\n", result);

    fclose(file);
    return 0;
}
