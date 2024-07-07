#include <njoritus/regex_wrapper.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief
 *
 * @param this
 * @param cp_pattern
 * @return int
 */
int compileRegexWrapper(RegexWrapper *this, const char * cp_pattern) {

    if (this == NULL || cp_pattern == NULL) {
        return EXIT_FAILURE;
    }

    int status = regcomp(&this->m_regex, cp_pattern, REG_EXTENDED);

    if (status != 0) {
        const int BUFFER_SIZE = 256;
        char errbuf[BUFFER_SIZE];
        regerror(status, &this->m_regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile m_regex: %s\n", errbuf);
        this->m_is_compiled = FALSE;
        return EXIT_FAILURE;
    }

    this->m_is_compiled = TRUE;
    return EXIT_SUCCESS;
}

/**
 * @brief
 *
 * @param this
 */
void emptyInitilizeRegexWrapper(RegexWrapper *this) {
    if (this == NULL) {
        return;
    }
    this->m_is_compiled = FALSE;
}

/**
 * @brief
 *
 * @param this
 * @param cp_pattern_config
 * @return int
 */
int recompileRegexWrapper(RegexWrapper *this, const char * cp_pattern_config) {
    cleanupRegexWrapper(this);
    return compileRegexWrapper(this, cp_pattern_config);
}

/**
 * @brief
 *
 * @param this
 * @return int
 */
int isRegexWrapperCompiled(const RegexWrapper *this) {
    return this->m_is_compiled;
}

/**
 * @brief
 *
 * @param this
 */
void cleanupRegexWrapper(RegexWrapper *this) {
    if (isRegexWrapperCompiled(this)) {
        regfree(&this->m_regex);
        this->m_is_compiled = FALSE;
    }
}

int rawMatchRegexWrapper(RegexWrapper *this, const char *cp_text)
{
    if (isRegexWrapperCompiled(this) == FALSE) {
        return -1;
    }

    regmatch_t matches[1];
    int status = regexec(&this->m_regex, cp_text, 1, matches, 0);

    if (status == REG_NOMATCH ||  status == REG_NOERROR) {
        return status;
    }

    const int BUFFER_SIZE = 256;
    char errbuf[BUFFER_SIZE];
    regerror(status, &this->m_regex, errbuf, sizeof(errbuf));
    fprintf(stderr, "Regex match failed: %s\n", errbuf);
    return status;
}
