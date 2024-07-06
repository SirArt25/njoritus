#include <thor-shield/dec.h>
#include <telebot.h>
#include <utilities.h>
#include <njoritus/user_interface.h>

int main() {
    apr_pool_t *pool = NULL;

    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return EXIT_FAILURE;
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        return cleanupAndTerminate(IMMEDIATE_TERMINATE, NULL, EXIT_FAILURE);
    }

    // TODO Write token Load for telebot
    //
    // gchar * p_token = loadSecret("mjorn");

    // if(p_token == NULL) {
    //     return EXIT_FAILURE;
    // }

    // purgePointer(p_token, strlen(p_token));

    apr_file_t *in_file = NULL;

    if (openStdin(pool, &in_file) != APR_SUCCESS) {
        return cleanupAndTerminate(IMMEDIATE_TERMINATE, pool, EXIT_FAILURE);
    }

    int status = interactiveInput(in_file, pool);
    return cleanupAndTerminate(IMMEDIATE_TERMINATE, pool, status);
}
