#include <thor-shield/dec.h>
#include <telebot.h>
#include <dec.h>

int main() {
    apr_pool_t *pool = NULL;

    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return EXIT_FAILURE;
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return EXIT_FAILURE;
    }

    gchar * p_token = loadSecret("mjorn");

    if(p_token == NULL) {
        return EXIT_FAILURE;
    }

    apr_pool_destroy(pool);

    apr_terminate();
    return EXIT_SUCCESS;
}
