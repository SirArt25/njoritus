#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <thor-shield/enc.h>
#include <thor-shield/dec.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [--enc label token-folder service-name | --dec service-name]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--enc") == 0) {
        if (argc != 5) {
            printf("Usage for --enc: %s --enc <label> <token-folder> <service-name>\n", argv[0]);
            return 1;
        }
        const char *pLabel = argv[2];
        const char *pToken_folder = argv[3];
        const char *pService_name = argv[4];

        char * pToken = readTokenFromFile(pToken_folder);

        if(pToken == NULL)
            return 1;

        if(saveSecret(pLabel, pToken, pService_name) == FALSE)
            return 1;
    } else if (strcmp(argv[1], "--dec") == 0) {
        if (argc != 3) {
            printf("Usage for --dec: %s --dec <service-name>\n", argv[0]);
            return 1;
        }
        const char *service_name = argv[2];
        gchar* pToken = loadSecret(service_name);

        if(pToken == NULL)
            return 1;

        securePrint(pToken);
    } else {
        printf("Unknown argument: %s\n", argv[1]);
        printf("Usage: %s [--enc label token-folder service-name | --dec service-name]\n", argv[0]);
        return 1;
    }
    return 0;
}
