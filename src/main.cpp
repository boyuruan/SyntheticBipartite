#include "Graph.h"

int getNextChar(const char *para) {
    int i = 0;
    while (para[i] == ' ') {
        i++;
    }
    if (para[i] != '-') {
        printf("error occurs in parameter format %s\n", para);
        exit(1);
    }
    return i;
}

void getNextWord(const char *para, char *word) {
    while (*para == ' ') {
        para++;
    }
    while (*para != '\0') {
        *word = *para;
        word++;
        para++;
    }
    *word = '\0';
}

struct Para parse_args(int argc, char **argv) {
    Para rtn;
    int upperLevel = 0;
    int lowerLevel = 0;
    int bloomSize = 0;
    int overLap = 0;
    double prob = 1.0;
    char file[255];
    int i = 0;
    int cnt = 1;
    char para[31];
    char *arg;
    printf("Input parameters are:\n\n");
    while (cnt < argc) {
        arg = argv[cnt++];
        i = getNextChar(arg);
        getNextWord(arg + i + 1, para);
        arg = argv[cnt++];
        printf("%s:\t", para);
        if (strcmp(para, "n1") == 0) {
            upperLevel = atoi(arg);
            printf("%d\n", upperLevel);
        } else if (strcmp(para, "n1") == 0) {
            lowerLevel = atoi(arg);
            printf("%d\n", lowerLevel);
        } else if (strcmp(para, "bloom") == 0) {
            bloomSize = atoi(arg);
            printf("%d\n", bloomSize);
        } else if (strcmp(para, "overlap") == 0) {
            overLap = atoi(arg);
            printf("%d\n", overLap);
        } else if (strcmp(para, "prob") == 0) {
            prob = atof(arg);
            printf("%.2lf\n", prob);
        } else if (strcmp(para, "file") == 0) {
            getNextWord(arg, file);
            printf("%s\n", file);
        }
    }

    rtn.upperLevel = upperLevel;
    rtn.lowerLevel = lowerLevel;
    rtn.bloomSize = bloomSize;
    rtn.overLap = overLap;
    rtn.prob = prob;
    strcpy(rtn.file, file);

    return rtn;
}

int main(int argc, char **argv) {
    struct Para paras = parse_args(argc, argv);

    return 0;
}