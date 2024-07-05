#include <njoritus/query_classifier_config.h>
#include <stddef.h>

/**
 * @brief
 *
 * @param this
 * @param main_pool
 * @return apr_status_t
 */
apr_status_t  initQueryClassifierConfig(QueryClassifierConfig *this,
            apr_pool_t *p_main_pool) {
    apr_status_t status = apr_pool_create(&this->m_p_pool, p_main_pool);

    if (status != APR_SUCCESS) {
        return status;
    }

    this->m_p_pairs_pattern_type = apr_array_make(this->m_p_pool, 2,
            sizeof(PatternTypePair));

    if (this->m_p_pairs_pattern_type == NULL) {
        apr_pool_destroy(this->m_p_pool);
        return APR_ENOMEM;
    }
    return APR_SUCCESS;
}

apr_status_t addPatternTypePair(QueryClassifierConfig *this,
        const char *p_pattern, QueryType type) {

    PatternTypePair *pair = (PatternTypePair *)
        apr_array_push(this->m_p_pairs_pattern_type);

    if (pair == NULL) {
        return APR_ENOMEM;
    }
    pair->m_p_pattern = p_pattern;
    pair->type = type;

    return APR_SUCCESS;
}


void terminateQueryClassifierConfig(QueryClassifierConfig *this){
    if (this != NULL && this->m_p_pool != NULL) {
        apr_pool_destroy(this->m_p_pool);
    }
}


int getQueryCount(const QueryClassifierConfig *this) {
    if(this == NULL) {
        return -1;
    }
    return this->m_p_pairs_pattern_type->nelts;
}

PatternTypePair* atQueryClassifierConfig(const QueryClassifierConfig *this, int index) {
    if (index < 0 || index >= getQueryCount(this)) {
        return NULL;
    }
    PatternTypePair *pairs = (PatternTypePair *)this->m_p_pairs_pattern_type->elts;
    return &pairs[index];
}
