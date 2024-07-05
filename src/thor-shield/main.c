#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <enc.h>
#include <dec.h>
#include <utilities.h>

int exit_pool_destroy(apr_pool_t *p_parent_pool, const int c_val);


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [--enc label token-folder service-name | --dec service-name key-path]\n", argv[0]);
        return EXIT_FAILURE;
    }
    apr_pool_t *p_parent_pool = NULL;
    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return EXIT_FAILURE;
    }
    if (apr_pool_create(&p_parent_pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "--enc") == 0) {
        const size_t ARG_COUNT = 5;
        if (argc != ARG_COUNT) {
            printf("Usage for --enc: %s --enc <label> <token-folder> <service-name>\n", argv[0]);
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
        }
        const char *p_label = argv[2];
        const char *p_token_folder = argv[3];
        const char *p_service_name = argv[4];

        char * p_token = readTokenFromFile(p_parent_pool,
            p_token_folder);

        if(p_token == NULL) {
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
        }

        if(saveSecret(p_label, p_token, p_service_name) == FALSE) {
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
        }
    } else if (strcmp(argv[1], "--dec") == 0) {
        if (argc != 4) {
            printf("Usage for --dec: %s --dec <service-name> <key-path>\n", argv[0]);
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
        }
        const char *service_name = argv[2];
        const char *key_path = argv[3];

        gchar* p_token = loadSecret(service_name);

        if(p_token == NULL) {
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
        }

        if(secureExport(p_parent_pool, p_token, key_path) == EXIT_FAILURE) {
            purgePointer(p_token);
            return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);;
        }
    } else {
        printf("Unknown argument: %s\n", argv[1]);
        printf("Usage: %s [--enc label token-folder service-name | --dec service-name key-path]\n", argv[0]);
        return exit_pool_destroy(p_parent_pool, EXIT_FAILURE);
    }
    return exit_pool_destroy(p_parent_pool, EXIT_SUCCESS);
}

int exit_pool_destroy(apr_pool_t *p_parent_pool, const int c_val) {
    apr_pool_destroy(p_parent_pool);
    apr_terminate();
    return c_val;
}
