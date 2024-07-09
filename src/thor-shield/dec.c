#include <dec.h>

/**
 * @brief
 *
 * @param cp_sevice_name
 * @return char*
 */
char *loadSecret(const char *cp_sevice_name, apr_pool_t *p_parent_pool) {
  if (p_parent_pool == NULL) {
    return NULL;
  }
  const char *cp_key_type = "user";

  key_serial_t key =
      keyctl_search(KEY_SPEC_SESSION_KEYRING, cp_key_type, cp_sevice_name, 0);
  if (key == -1) {
    fprintf(stderr, "Error retrieving secret\n");
    return NULL;
  }
  const size_t TOKEN_SIZE = 1024;
  char *p_buffer = apr_pcalloc(p_parent_pool, TOKEN_SIZE);
  size_t len = keyctl_read(key, p_buffer, TOKEN_SIZE);
  if (len == -1) {
    fprintf(stderr, "Error retrieving secret\n");
    return NULL;
  }

  if (len < TOKEN_SIZE) {
    p_buffer[len] = '\0';
  } else {
    p_buffer[TOKEN_SIZE - 1] = '\0';
  }
  return p_buffer;
}
