#include <thor-shield/dec.h>

void readSecret(const char *label) {
    GError *error = NULL;

    // Retrieve the secret
    gchar *retrieved_token = secret_password_lookup_sync(
        SECRET_SCHEMA_COMPAT_NETWORK,
        NULL,           // Cancellable
        &error,
        "service", "my_service",
        NULL);

    if (error) {
        fprintf(stderr, "Error retrieving secret: %s\n", error->message);
        g_error_free(error);
    } else if (retrieved_token) {
        printf("Retrieved secret: %s\n", retrieved_token);
        secret_password_free(retrieved_token);
    } else {
        printf("No secret found.\n");
    }
}
