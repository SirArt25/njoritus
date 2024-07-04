#include <enc.h>

int saveSecret(const char * cpLabel, const char * cpToken,
                 const char * cpSeviceName) {
    GError *pGerror = NULL;

    gboolean result = secret_password_store_sync(
        &mjolnir, SECRET_COLLECTION_DEFAULT,
        cpLabel, cpToken, NULL,
        &pGerror,
        "service", cpSeviceName,
        NULL);

    if (pGerror) {
        fprintf(stderr, "Error storing secret: %s\n", pGerror->message);
        g_error_free(pGerror);
        return FALSE;
    }

    return result;
}


char * readTokenFromFile(const char *pPath) {

    FILE *fp = fopen(pPath, "r");
    if (fp == NULL) {
        printf("Failed to open %s file\n", pPath);
        return NULL;
    }

    char * pToken = (char *)malloc(1024 * sizeof(char));

    if (fscanf(fp, "%1023s", pToken) != 1) {
        printf("Failed to read token\n");
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return pToken;
}
