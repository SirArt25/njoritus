#include <thor-shield/mjolnir.h>

const SecretSchema mjolnir = {
    "com.example.ServiceOnly", // Unique names for mjolnir
    SECRET_SCHEMA_NONE,        // No flags for mjolnir
    {
        { "service", SECRET_SCHEMA_ATTRIBUTE_STRING }, // Service name
        { "NULL", 0 },
    }
};
