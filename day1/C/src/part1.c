#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    size_t linesize = 512;
    char *line = malloc(linesize);
    int result = 0;
    while (-1 != getline(&line, &linesize, file)) {
        size_t len = strlen(line);
        char *str = malloc(linesize);
        memcpy(str, line, linesize);

        for (size_t i = 0, k = len - 1; i < (len / 2); i++, k--) {
            char temp = str[k];
            str[k] = str[i];
            str[i] = temp;
        }

        size_t firstnum = strcspn(line, "0123456789");
        size_t lastnum = strcspn(str, "0123456789");

        result += (line[firstnum] - 48) * 10 + (str[lastnum] - 48);
        free(str);
    }
    printf("%i\n", result);

    fclose(file);
    return 0;
}
