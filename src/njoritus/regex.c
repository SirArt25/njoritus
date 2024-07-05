#include <njoritus/regex.h>

int compileNjoritusRegex(NjoritusRegex *this, const char *cp_pattern) {

    int ret = regcomp(&this->regex, cp_pattern, REG_EXTENDED);

    if (ret != 0) {
        const int BUFFER_SIZE = 256;
        char errbuf[BUFFER_SIZE];
        regerror(ret, &this->regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        this->is_compiled = 0;
        return EXIT_FAILURE;
    }
    this->is_compiled = 1;
    return EXIT_SUCCESS;
}

int recompileNjoritusRegex(NjoritusRegex *this, const char *cp_pattern) {
    cleanupNjoritusRegex(this);
    return compileNjoritusRegex(this, cp_pattern);
}

int matchNjoritusRegex(NjoritusRegex *this, const char *cp_text) {
    if (isNjoritusRegexCompiled(this) == 0) {
        fprintf(stderr, "Regex is not compiled.\n");
        return -1;
    }

    regmatch_t matches[1];
    int ret = regexec(&this->regex, cp_text, 1, matches, 0);
    int result = -1;

    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        const int BUFFER_SIZE = 256;
        char errbuf[BUFFER_SIZE];
        regerror(ret, &this->regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex match failed: %s\n", errbuf);
        result = -1;
    }
    return result;
}

int isNjoritusRegexCompiled(NjoritusRegex *this) {
    return this->is_compiled;
}

void cleanupNjoritusRegex(NjoritusRegex * this) {
    if (isNjoritusRegexCompiled(this)) {
        regfree(&this->regex);
        this->is_compiled = 0;
    }
}
