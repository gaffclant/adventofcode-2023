#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 512

void itergame(char **games, int *mr, int *mg, int *mb) {
    int num = strtol(*games, games, 10);
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

void outeritergame(char **games, int *mr, int *mg, int *mb, char delim) {
    char *gam = malloc(LINESIZE);
    gam = strncpy(gam, *games, strchr(*games, delim) - *games);
    while (strchr(gam, ',')) {
        itergame(&gam, mr, mg, mb);
        gam = strchr(gam, ',') + 2;
    }
    itergame(&gam, mr, mg, mb);
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

    size_t linesize = LINESIZE;
    char *line = malloc(linesize);
    int result = 0;
    while (-1 != getline(&line, &linesize, file)) {
        line = strchr(line, ' ') + 1;
        char *games = malloc(LINESIZE);
        games = strchr(line, ':') + 2;
        int maxred = 0;
        int maxgreen = 0;
        int maxblue = 0;
        while (strchr(games, ';')) {
            outeritergame(&games, &maxred, &maxgreen, &maxblue, ';');
            games = strchr(games, ';') + 2;
        }
        outeritergame(&games, &maxred, &maxgreen, &maxblue, '\n');

        result += maxred * maxgreen * maxblue;
    }

    printf("%i\n", result);

    return 0;
}
