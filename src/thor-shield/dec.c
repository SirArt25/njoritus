#include <dec.h>

/**
 * @brief
 *
 * @param cp_sevice_name
 * @return gchar*
 */
gchar *loadSecret(const char *cp_sevice_name) {
  GError *p_gerror = NULL;

  gchar *p_token = secret_password_lookup_sync(&MJOLNIR, NULL, &p_gerror,
                                               "service", cp_sevice_name, NULL);

  if (p_gerror) {
    fprintf(stderr, "Error retrieving secret: %s\n", p_gerror->message);
    g_error_free(p_gerror);
    return NULL;
  }
  return p_token;
}
