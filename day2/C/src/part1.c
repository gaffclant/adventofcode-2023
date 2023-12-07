#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 512

void itergame(char **games, int *mr, int *mg, int *mb) {
    int num = strtol(*games, games, 10);
    // printf("\titergame:\tgam: %s\tnum: %i\n", *games, num);
    switch ((++*games)[0]) {
    case 'r':
        *mr = num > *mr ? num : *mr;
        break;
    case 'g':
        *mg = num > *mg ? num : *mg;
        break;
    case 'b':
        *mb = num > *mb ? num : *mb;
        break;
    default:
        break;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("File not found: %s\n", argv[1]);
        return 1;
    }
    printf("File opened\n");

    size_t linesize = LINESIZE;
    char *line = malloc(linesize);
    int id = 0;
    int result = 0;
    while (-1 != getline(&line, &linesize, file)) {
        printf("%i\n", result);
        line = strchr(line, ' ') + 1;
        printf("----------\nLine:\t%s", line);
        char *games = malloc(512);
        id = strtol(line, &games, 10);
        games = strchr(games, ':') + 2;
        // printf("Games:\t%s", games);
        int maxred = 0;
        int maxgreen = 0;
        int maxblue = 0;
        while (strchr(games, ';')) {
            char *gam = malloc(LINESIZE);
            gam = strncpy(gam, games, strchr(games, ';') - games);
            // printf("--\nGam:\t%s\n", gam);
            while (strchr(gam, ',')) {
                itergame(&gam, &maxred, &maxgreen, &maxblue);
                gam = strchr(gam, ',') + 2;
            }
            itergame(&gam, &maxred, &maxgreen, &maxblue);
            games = strchr(games, ';') + 2;
        }
        char *gam = malloc(LINESIZE);
        gam = strncpy(gam, games, strchr(games, '\n') - games);
        // printf("--\nGam:\t%s\n", gam);
        while (strchr(gam, ',')) {
            itergame(&gam, &maxred, &maxgreen, &maxblue);
            gam = strchr(gam, ',') + 2;
        }
        itergame(&gam, &maxred, &maxgreen, &maxblue);

        printf("r: %i g: %i b: %i\n", maxred, maxgreen, maxblue);
        if (maxred > 12 || maxgreen > 13 || maxblue > 14)
            continue;
        result += id;
        printf("%i is valid\n", id);
    }

    printf("%i\n", result);

    return 0;
}
