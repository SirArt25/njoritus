#include <stdio.h>
#include <apr_general.h>
#include <apr_pools.h>
#include <string.h>
#include <unistd.h>
#include <telebot.h>

int main() {
    char message[] = "Hello, C17!";
    printf("%s\n", message);
    apr_pool_t *pool = NULL;

    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Failed to initialize APR\n");
        return 1;
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Failed to create memory pool\n");
        apr_terminate();
        return 1;
    }

    // printf("Welcome to njoritus\n");

    // FILE *fp = fopen(".token", "r");
    // if (fp == NULL)
    // {
    //     printf("Failed to open .token file\n");
    //     return -1;
    // }

    // char token[1024];
    // if (fscanf(fp, "%s", token) == 0)
    // {
    //     printf("Failed to read token\n");
    //     fclose(fp);
    //     return -1;
    // }
    // printf("Token: %s\n", token);
    // fclose(fp);

    // telebot_handler_t handle;
    // if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
    // {
    //     printf("Telebot create failed\n");
    //     return -1;
    // }

    // telebot_user_t me;
    // if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
    // {
    //     printf("Failed to get bot information\n");
    //     telebot_destroy(handle);
    //     return -1;
    // }

    // printf("ID: %d\n", me.id);
    // printf("First Name: %s\n", me.first_name);
    // printf("User Name: %s\n", me.username);
    // telebot_destroy(handle);

    printf("Memory pool created successfully!\n");
    apr_pool_destroy(pool);
    apr_terminate();

    return 0;
}
