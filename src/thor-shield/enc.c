#include <enc.h>

/**
 * @brief
 *
 * @param cp_label
 * @param cp_token
 * @param cp_sevice_name
 * @return int
 */
int saveSecret(const char * cp_label, const char * cp_token,
                 const char * cp_service_name) {
    GError *p_gerror = NULL;

    gboolean result = secret_password_store_sync(
        &mjolnir, SECRET_COLLECTION_DEFAULT,
        cp_label, cp_token,
        NULL, &p_gerror,
        "service", cp_service_name,
        NULL);

    if (p_gerror) {
        fprintf(stderr, "Error storing secret: %s\n", p_gerror->message);
        g_error_free(p_gerror);
        return FALSE;
    }

    return result;
}

/**
 * @brief
 *
 * @param p_parent_pool
 * @param cp_path
 * @return char*
 */
char * readTokenFromFile(apr_pool_t *p_parent_pool, const char *cp_path) {

    if (p_parent_pool == NULL) {
        return NULL;
    }
    apr_pool_t *p_child_pool;
    apr_status_t status = apr_pool_create(&p_child_pool, p_parent_pool);

    if (status != APR_SUCCESS) {
        apr_pool_destroy(p_child_pool);
        return NULL;
    }

    apr_file_t *p_token_file;
    status = apr_file_open(&p_token_file, cp_path,
                    APR_READ, APR_OS_DEFAULT, p_child_pool);

    if (status != APR_SUCCESS || p_token_file == NULL) {
        apr_pool_destroy(p_child_pool);
        return NULL;
    }

    const size_t TOKEN_SIZE = 1024;
    char * p_token = (char *)apr_palloc(p_child_pool, TOKEN_SIZE * sizeof(char));

    if (p_token == NULL) {
        apr_file_close(p_token_file);
        apr_pool_destroy(p_child_pool);
        return NULL;
    }

    apr_size_t len = TOKEN_SIZE * sizeof(char);
    status = apr_file_read_full(p_token_file, p_token, len, &len);
    if (status != APR_SUCCESS && status != APR_EOF) {
        apr_file_close(p_token_file);
        apr_pool_destroy(p_child_pool);
        return NULL;
    }
    apr_file_close(p_token_file);

    char *p_token_parent = (char *)apr_palloc(p_parent_pool, TOKEN_SIZE * sizeof(char));

    if (p_token_parent == NULL) {
        apr_file_close(p_token_file);
        apr_pool_destroy(p_child_pool);
        return NULL;
    }
    apr_cpystrn(p_token_parent, p_token, TOKEN_SIZE * sizeof(char));

    apr_pool_destroy(p_child_pool);

    return p_token_parent;
}
