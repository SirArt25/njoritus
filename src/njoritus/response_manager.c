#include <njoritus/response_manager.h>
#include <utilities.h>

int initializeResponseManager(ResponseManager *this,
                              apr_pool_t *p_parent_pool) {
  if (this == NULL) {
    return -1;
  }
  apr_status_t status = initializePool(&this->m_p_pool, p_parent_pool);

  if (status != APR_SUCCESS) {
    fprintf(stderr, "Could not create memory pool\n");
    return status;
  }

  this->m_p_hashmap = apr_hash_make(this->m_p_pool);
  if (this->m_p_hashmap == NULL) {
    fprintf(stderr, "Could not create hash table\n");
    apr_pool_destroy(this->m_p_pool);
    return APR_ENOMEM;
  }

  return APR_SUCCESS;
}

void registerResponseFunction(ResponseManager *this, const char *cp_key,
                              ResponseFunction func) {
  apr_hash_set(this->m_p_hashmap, apr_pstrdup(this->m_p_pool, cp_key),
               APR_HASH_KEY_STRING, func);
}

ResponseFunction getResponseFunctionFromKey(ResponseManager *this,
                                            const char *cp_key) {
  return apr_hash_get(this->m_p_hashmap, cp_key, APR_HASH_KEY_STRING);
}

const char *getResponseKeyFromQuery(ResponseManager *this,
                                    const char *cp_query) {
  if (this == NULL || cp_query == NULL) {
    return NULL;
  }
  apr_hash_index_t *p_hash_index;
  const void *p_key;
  void *p_value;
  for (p_hash_index = apr_hash_first(this->m_p_pool, this->m_p_hashmap);
       p_hash_index; p_hash_index = apr_hash_next(p_hash_index)) {
    apr_hash_this(p_hash_index, &p_key, NULL, &p_value);
    if (strstr(cp_query, (const char *)p_key)) {
      return p_key;
    }
  }

  return NULL;
}

ResponseFunction getResponseFunctionFromQuery(ResponseManager *this,
                                              const char *cp_query) {
  const char *p_key = getResponseKeyFromQuery(this, cp_query);

  if (p_key == NULL) {
    return NULL;
  }
  return getResponseFunctionFromKey(this, cp_query);
}

void destroyResponseManager(ResponseManager *this) {
  if (this && this->m_p_pool) {
    apr_pool_destroy(this->m_p_pool);
  }
}
