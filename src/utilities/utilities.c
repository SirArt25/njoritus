#include <stdlib.h>
#include <utilities.h>

/**
 * @brief
 *
 * @param data
 * @param len
 */
void purgePointer(volatile void *data, size_t len) {

  if (data == NULL) {
    return;
  }

  volatile char *p_vol_data = (volatile char *)data;

  while (len) {
    *p_vol_data++ = 0;
    len--;
  }
}

/**
 * @brief
 *
 * @param p_parent_pool
 * @param terminate
 * @param c_val
 * @return int
 */
int cleanupAndTerminate(TerminationType terminate, apr_pool_t *p_parent_pool,
                        int c_val) {
  if (p_parent_pool != NULL) {
    apr_pool_destroy(p_parent_pool);
  }

  if (terminate == IMMEDIATE_TERMINATE) {
    apr_terminate();
  }
  return c_val;
}

/**
 * @brief
 *
 * @param p_pool
 * @param p_in_file
 * @return int
 */
int openStdin(apr_pool_t *p_pool, apr_file_t **p_in_file) {
  if (p_pool == NULL || p_in_file == NULL) {
    return EXIT_FAILURE;
  }
  apr_status_t status = apr_file_open_stdin(p_in_file, p_pool);
  if (status != APR_SUCCESS) {
    fprintf(stderr, "Could not open standard input\n");
  }
  return status;
}

/**
 * @brief
 *
 * @param p_str
 * @param len
 * @param p_file
 * @return int
 */
int fileGets(char *p_str, int len, apr_file_t *p_file) {
  if (p_str == NULL || p_file == NULL) {
    return EXIT_FAILURE;
  }
  apr_status_t status = apr_file_gets(p_str, len, p_file);
  if (status != APR_SUCCESS) {
    fprintf(stderr, "Error reading input. Terminating...\n");
  }
  return status;
}

/**
 * @brief
 *
 * @param input
 * @param length
 * @param in_file
 * @return int
 */
int readInput(char *input, int length, apr_file_t *in_file) {
  apr_status_t status = fileGets(input, length - 1, in_file);

  if (status != APR_SUCCESS) {
    return status;
  }

  input[strcspn(input, "\n")] = '\0';

  return status;
}
