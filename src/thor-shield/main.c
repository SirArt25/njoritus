#include <stdio.h>
#include <apr_general.h>
#include <apr_pools.h>
#include <string.h>
#include <unistd.h>
#include <telebot.h>


int main() {
    char message[] = "Hello, thor-shield";
    printf("%s\n", message);
    return 0;
}
