#include <apr.h>
#include <apr_file_io.h>
#include <apr_pools.h>
#include <njoritus/core.h>
#include <signal.h>
#include <stddef.h>

// Flag to control the loop
volatile sig_atomic_t atomic_running = TRUE;

/**
 * @brief
 *
 * @return int
 */
int initializeAPR() {
  int status = apr_initialize();

  if (status != APR_SUCCESS) {
    fprintf(stderr, "Failed to initialize APR\n");
  }

  return status;
}

int initialize() {
  signal(SIGINT, handleSigint);
  return initializeAPR();
}

/**
 * @brief
 *
 * @param sig
 */
void handleSigint(int sig) {
  if (sig == SIGINT) {
    atomic_running = FALSE;
  }
}
