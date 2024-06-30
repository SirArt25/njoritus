#include <stdio.h>
#include <apr_general.h>
#include <apr_pools.h>

int main() {
    char message[] = "Hello, C17!";
    printf("%s\n", message);
    apr_pool_t *pool = NULL;

    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return 1;
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return 1;
    }

    printf("Memory pool created successfully!\n");
    apr_pool_destroy(pool);
    apr_terminate();

    return 0;
}
