#include <thor-shield/enc.h>

int saveSecret(const char * cpLabel, const char * cpToken,
                 const char * cpSeviceName) {
    GError *pGerror = NULL;
    gboolean result = secret_password_store_sync(
        &mjolnir,
        SECRET_COLLECTION_DEFAULT,
        cpLabel,
        cpToken,
        NULL,
        &pGerror,
        "service", cpSeviceName,
        NULL);

    if (pGerror) {
        fprintf(stderr, "Error storing secret: %s\n", error->message);
        g_error_free(error);
        return FALSE;
    }

    return result;
}
