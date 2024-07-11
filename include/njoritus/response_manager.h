#ifndef NJORD_RESPONSE_MANAGER_H
#define NJORD_RESPONSE_MANAGER_H

#include <apr_general.h>
#include <apr_hash.h>
#include <apr_strings.h>
#include <njoritus/callbacks.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*ResponseFunction)(const char *, apr_pool_t *, GeneralCallbackT *);

typedef struct {
  apr_pool_t *m_p_pool;
  apr_hash_t *m_p_hashmap;
} ResponseManager;

int initializeResponseManager(ResponseManager *this, apr_pool_t *p_parent_pool);
void registerResponseFunction(ResponseManager *this, const char *cp_key,
                              ResponseFunction func);
ResponseFunction getResponseFunctionFromKey(ResponseManager *this,
                                            const char *cp_key);
ResponseFunction getResponseFunctionFromQuery(ResponseManager *this,
                                              const char *cp_query);
const char *getResponseKeyFromQuery(ResponseManager *this,
                                    const char *cp_query);
void destroyResponseManager(ResponseManager *this);

#endif // NJORD_RESPONSE_MANAGER_H
