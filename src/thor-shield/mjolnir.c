#include <mjolnir.h>

const SecretSchema mjolnir = {
    "com.example.ServiceOnly", // Unique names for mjolnir
    SECRET_SCHEMA_NONE,        // No flags for mjolnir
    {
        { "service", SECRET_SCHEMA_ATTRIBUTE_STRING }, // Service name
        { "NULL", 0 },
    }
};


void securePrint(const char* pData) {
    if (pData == NULL) return;

    if (isatty(fileno(stdout))) {
        printf("%s\n", pData);

        // Use volatile to prevent compiler optimizations from removing the memory cleaning
        volatile char *p = (volatile char *)pData;
        size_t len = strlen(pData);

        // Overwrite the sensitive data immediately after using it
        while (len) {
            *p++ = 0;
            len--;
        }
    } else {
        fprintf(stderr, "Secure printing is only allowed to terminal outputs.\n");
    }
}
