#include <thor-shield/dec.h>
#include <telebot.h>
#include <dec.h>
#include <njoritus/query_classifier.h>

int main() {
    apr_pool_t *pool = NULL;


    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return EXIT_FAILURE;
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return EXIT_FAILURE;
    }

    gchar * p_token = loadSecret("mjorn");

    if(p_token == NULL) {
        return EXIT_FAILURE;
    }

    QueryClassifierConfig config;
    initQueryClassifierConfig(&config, pool);
    addPatternTypePair(&config,
        "([-+]?[1-8]?[0-9](\\.[0-9]+)?|90(\\.0+)?),\\s*([-+]?(1[0-7][0-9]|[0-9]?[0-9])"
        "(\\.[0-9]+)?|180(\\.0+)?)",
        QUERY_TYPE_LAT_LONG);
    addPatternTypePair(&config, "([A-Za-z\\s]+)", QUERY_TYPE_CITY_NAME);
    QueryClassifier classifier;
    initQueryClassifier(&classifier, pool, &config);
    const int LENGTH = 256;
    char input[LENGTH];
    apr_file_t *in_file;
    apr_status_t status = apr_file_open_stdin(&in_file, pool);
    if (status != APR_SUCCESS) {
        fprintf(stderr, "Could not open standard input\n");
        terminateQueryClassifierConfig(&config);
        terminateQueryClassifier(&classifier);
        apr_pool_destroy(pool);
        apr_terminate();
        return EXIT_FAILURE;
    }
    while(1) {
        apr_size_t len = sizeof(input) - 1;

        printf("Enter a line (type 'end' to terminate): ");
        status = apr_file_gets(input, (int)len, in_file);
        if (status != APR_SUCCESS) {
            fprintf(stderr, "Error reading input. Terminating...\n");
            break;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Check if the input is "end"
        if (strcmp(input, "end") == 0) {
            printf("Terminating...\n");
            break;
        }
        int result = proccessQuery(&classifier, input);

        if (result == QUERY_TYPE_CITY_NAME) {
            printf("You entered a city: %s\n", input);
        } else if (result == QUERY_TYPE_LAT_LONG) {
            printf("You entered a lat long: %s\n", input);
        }
        else {
            printf("You entered a not understand: %s\n", input);
        }
    }


    terminateQueryClassifierConfig(&config);
    terminateQueryClassifier(&classifier);
    apr_pool_destroy(pool);

    apr_terminate();
    return EXIT_SUCCESS;
}
