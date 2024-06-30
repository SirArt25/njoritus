#include <stdio.h>
#include <apr_general.h>
#include <apr_pools.h>
// The main function is the entry point of the C program
int main() {
    // Define a character array (string) and initialize it with a message
    char message[] = "Hello, C17!";
    
    // Print the message to the standard output (console)
    printf("%s\n", message);
    
    // Declare a variable to store the status of APR operations
    apr_status_t status;
    
    // Declare a pointer to an APR memory pool
    apr_pool_t *pool;

    // Initialize the Apache Portable Runtime (APR) library
    status = apr_initialize();
    
    // Check if the initialization was successful
    if (status != APR_SUCCESS) {
        // If not, print an error message and return with a non-zero status
        fprintf(stderr, "Failed to initialize APR\n");
        return 1;
    }
    // Create a memory pool using APR
    status = apr_pool_create(&pool, NULL);
    
    // Check if the memory pool creation was successful
    if (status != APR_SUCCESS) {
        // If not, print an error message, terminate APR, and return with a non-zero status
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return 1;
    }

    // If the memory pool was created successfully, print a success message
    printf("Memory pool created successfully!\n");

    // Destroy the memory pool to free up resources
    apr_pool_destroy(pool);

    // Terminate the APR library to clean up and release resources
    apr_terminate();
    
    // Return 0 to indicate that the program finished successfully
    return 0;
}
