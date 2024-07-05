#include <njoritus/query_classifier.h>
#include <regex.h>

apr_status_t initQueryClassifier(QueryClassifier *this, apr_pool_t *p_main_pool,
        const QueryClassifierConfig *cp_config) {
    apr_status_t status = apr_pool_create(&this->m_p_pool, p_main_pool);

    if (status != APR_SUCCESS) {
        return status;
    }

    this->m_query_classifier_config = cp_config;

    if (status != APR_SUCCESS) {
        apr_pool_destroy(this->m_p_pool);
        return status;
    }

    return APR_SUCCESS;
}

void terminateQueryClassifier(QueryClassifier *this)
{
    if (this != NULL && this->m_p_pool != NULL) {
        apr_pool_destroy(this->m_p_pool);
    }
}


QueryType proccessQuery(QueryClassifier *this, const char * cp_text) {
    if (this == NULL || cp_text == NULL) {
        return QUERY_TYPE_UNKNOWN;
    }

    if (this->m_query_classifier_config == NULL) {
        return QUERY_TYPE_UNKNOWN;
    }

    NjoritusRegex regex;
    regex.is_compiled = 0;

    int size = getQueryCount(this->m_query_classifier_config);

    for (int i = 0; i < size; i++)
    {
        PatternTypePair* p_pair = atQueryClassifierConfig(
                this->m_query_classifier_config, i);

        if (p_pair == NULL) {
            cleanupNjoritusRegex(&regex);
            return QUERY_TYPE_UNKNOWN;
        }

        recompileNjoritusRegex(&regex, p_pair->m_p_pattern);
        if (matchNjoritusRegex(&regex, cp_text) == 1) {
            cleanupNjoritusRegex(&regex);
            return p_pair->type;
        }
    }
    return QUERY_TYPE_UNKNOWN;
}
