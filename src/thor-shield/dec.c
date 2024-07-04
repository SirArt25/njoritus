#include <dec.h>

gchar * loadSecret(const char * cpSeviceName) {
    GError *pGerror = NULL;

    gchar * pToken = secret_password_lookup_sync(
        &mjolnir, NULL,
        &pGerror,
        "service", cpSeviceName,
        NULL);

    if (pGerror) {
        fprintf(stderr, "Error retrieving secret: %s\n", pGerror->message);
        g_error_free(pGerror);
        return NULL;
    }
    return pToken;
}
