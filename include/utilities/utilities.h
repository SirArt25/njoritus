#ifndef NJORD_UTILITY_H
#define NJORD_UTILITY_H
#include <stddef.h>
#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>

typedef enum {
    IMMEDIATE_TERMINATE,
    NO_TERMINATE
} TerminationType;




void purgePointer(volatile void *data, size_t len);
int openStdin(apr_pool_t *p_pool, apr_file_t **p_in_file);
int fileGets(char * p_str, int len, apr_file_t * p_file);
int cleanupAndTerminate(TerminationType terminate, apr_pool_t *p_parent_pool,
                                                                    int c_val);
int readInput(char * input, int length, apr_file_t * in_file);
#endif // NJORD_UTILITY_H
