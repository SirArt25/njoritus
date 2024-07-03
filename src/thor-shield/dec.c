#include <thor-shield/dec.h>

gchar * loadSecret(const char * cpSeviceName) {
    GError *pGerror = NULL;

    gchar * pToken = secret_password_lookup_sync(
        &mjolnir, NULL,
        &error,
        "service", cpSeviceName,
        NULL);

    if (error) {
        fprintf(stderr, "Error retrieving secret: %s\n", error->message);
        g_error_free(error);
        return NULL;
    }
    return pToken;
}
