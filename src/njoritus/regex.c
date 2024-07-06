#include <njoritus/regex.h>
/**
 * @brief
 *
 * @param this
 * @param cp_pattern_config
 * @return int
 */
int compileNjoritusRegex(NjoritusRegex *this, const PatternConfig *
                                        cp_pattern_config) {

    if (this == NULL || cp_pattern_config == NULL) {
        return EXIT_FAILURE;
    }

    this->m_cp_pattern_config = cp_pattern_config;

    return compileRegexWrapper(&this->m_regex_wrapper,
        this->m_cp_pattern_config->m_p_pattern);
}

/**
 * @brief
 *
 * @param this
 * @param cp_pattern_config
 * @return int
 */
int recompileNjoritusRegex(NjoritusRegex *this,
    const PatternConfig * cp_pattern_config) {
    cleanupNjoritusRegex(this);
    return compileNjoritusRegex(this, cp_pattern_config);
}

/**
 * @brief
 *
 * @param this
 * @param cp_text
 * @return int
 */
int matchNjoritusRegex(NjoritusRegex *this, const char *cp_text) {
    if (isNjoritusRegexCompiled(this) == FALSE) {
        fprintf(stderr, "Regex is not compiled.\n");
        return -1;
    }
    if (this->m_cp_pattern_config != NULL &&
                    this->m_cp_pattern_config->m_semantic_checker != NULL) {
        return this->m_cp_pattern_config->m_semantic_checker(
                                &this->m_regex_wrapper, cp_text, NULL);
    }

    return rawMatchRegexWrapper(&this->m_regex_wrapper, cp_text);
    // if (isNjoritusRegexCompiled(this) == FALSE) {
    //     fprintf(stderr, "Regex is not compiled.\n");
    //     return -1;
    // }

    // if (this->m_cp_pattern_config != NULL &&
    //     this->m_cp_pattern_config->m_semantic_checker != NULL) {
    //     return this->m_cp_pattern_config->
    //         m_semantic_checker(&this->m_regex, cp_text);
    // }

    // regmatch_t matches[1];
    // int status = regexec(&this->m_regex, cp_text, 1, matches, 0);

    // if (status == REG_NOMATCH ||  status == REG_NOERROR) {
    //     return status;
    // }

    // const int BUFFER_SIZE = 256;
    // char errbuf[BUFFER_SIZE];
    // regerror(status, &this->m_regex, errbuf, sizeof(errbuf));
    // fprintf(stderr, "Regex match failed: %s\n", errbuf);
    // return status;
}

/**
 * @brief
 *
 * @param this
 * @return int
 */
int isNjoritusRegexCompiled(NjoritusRegex *this) {
    return isRegexWrapperCompiled(&this->m_regex_wrapper);
}

/**
 * @brief
 *
 * @param this
 */
void cleanupNjoritusRegex(NjoritusRegex * this) {
    if (isNjoritusRegexCompiled(this)) {
        cleanupRegexWrapper(&this->m_regex_wrapper);
    }
}


void emptyInitilizeNjoritusRegex(NjoritusRegex * this) {
    if (this == NULL) {
        return;
    }
    emptyInitilizeRegexWrapper(&this->m_regex_wrapper);
}
