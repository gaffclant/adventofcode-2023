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

    // Program start
    size_t linesize = LINESIZE;
    char *line = malloc(linesize);
    int result = 0;
    // loop over the lines
    while (-1 != getline(&line, &linesize, file)) {
        char *words[9] = {"one", "two",   "three", "four", "five",
                          "six", "seven", "eight", "nine"};
        size_t firstidx = strcspn(line, "0123456789");
        reverse(line);
        size_t lastidx = strlen(line) - strcspn(line, "0123456789") - 1;
        reverse(line);
        int tens = (line[firstidx] - 48);
        int ones = (line[lastidx] - 48);

        if (firstidx == strlen(line)) {
            lastidx = 0;
        }

        for (size_t i = 0; i < 9; i++) {
            char *firstword = strstr(line, words[i]);
            char *lastword = strstr(line, words[i]);
            if (!firstword) {
                continue;
            }

            while (strstr(lastword + strlen(words[i]), words[i])) {
                lastword = strstr(lastword + strlen(words[i]), words[i]);
            }

            if (firstidx > (size_t)(firstword - line)) {
                firstidx = firstword - line;
                tens = i + 1;
            }
            if (lastidx <= (size_t)(lastword - line)) {
                lastidx = lastword - line;
                ones = i + 1;
            }
        }
        result += tens * 10 + ones;
    }

    printf("%i\n", result);

    fclose(file);
    return 0;
}
