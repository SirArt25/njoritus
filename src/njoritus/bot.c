#include <njoritus/bot.h>
#include <njoritus/response_functions/get_response_weather.h>
#include <njoritus/response_manager.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <thor-shield/dec.h>
#include <unistd.h>
#include <utilities.h>

extern volatile sig_atomic_t atomic_running;

/**
 * @brief
 *
 * @param this
 * @return int
 */
int setupNjoritusBot(NjoritusBot *this) {
  if (this == NULL) {
    return EXIT_FAILURE;
  }

  apr_pool_t *p_pool = NULL;
  if (initializePool(&p_pool, NULL) != APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  char *p_token = loadSecret("mjorn", p_pool);
  if (p_token == NULL) {
    apr_pool_destroy(p_pool);
    return EXIT_FAILURE;
  }
  if (telebot_create(&this->m_handler, p_token) != TELEBOT_ERROR_NONE) {
    printf("Telebot create failed\n");
    purgePointer(p_token, strlen(p_token));
    apr_pool_destroy(p_pool);
    return EXIT_FAILURE;
  }

  if (telebot_get_me(this->m_handler, &this->m_user) != TELEBOT_ERROR_NONE) {
    printf("Failed to get this information\n");
    purgePointer(p_token, strlen(p_token));
    destroyNjoritusBot(this);
    apr_pool_destroy(p_pool);
    return EXIT_FAILURE;
  }

  printf("ID: %d\n", this->m_user.id);
  printf("First Name: %s\n", this->m_user.first_name);
  printf("User Name: %s\n", this->m_user.username);

  telebot_put_me(&this->m_user);
  purgePointer(p_token, strlen(p_token));
  apr_pool_destroy(p_pool);
  return EXIT_SUCCESS;
}

/**
 * @brief
 *
 * @param this
 */
void destroyNjoritusBot(NjoritusBot *this) {
  if (this != NULL) {
    telebot_destroy(this->m_handler);
  }
}

static int createResponseManager(ResponseManager *p_response_manager,
                                 apr_pool_t *p_parent_pool) {
  if (p_response_manager == NULL) {
    return EXIT_FAILURE;
  }

  if (initializeResponseManager(p_response_manager, p_parent_pool) !=
      APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  registerResponseFunction(p_response_manager, "/getweather",
                           responseGetWeather);
  registerResponseFunction(p_response_manager, "/start", responseStart);
  registerResponseFunction(p_response_manager, "/help", responseHelp);

  return EXIT_SUCCESS;
}

static int getResponseString(ResponseManager *p_response_manager,
                             apr_pool_t *p_parent_pool, char *p_text,
                             char **p_str, int string_size) {
  if (p_response_manager == NULL || p_parent_pool == NULL || p_text == NULL ||
      p_str == NULL) {
    return EXIT_FAILURE;
  }
  const char *cp_key = getResponseKeyFromQuery(p_response_manager, p_text);
  ResponseFunction response_function = NULL;
  if (cp_key != NULL) {
    response_function = getResponseFunctionFromKey(p_response_manager, cp_key);
  }
  if (response_function == NULL) {
    snprintf(*p_str, string_size, "<i>%s</i>", p_text);
    return EXIT_SUCCESS;
  }
  removeSubstring(p_text, cp_key);
  p_text = trimWhitespace(p_text);
  return response_function(p_text, p_parent_pool,
                           createCallbackData((void *)*p_str, p_parent_pool));
}

/**
 * @brief
 *
 * @param this
 * @return int
 */
int runNjoritusBot(NjoritusBot *this, apr_pool_t *p_parent_pool) {
  if (this == NULL) {
    return EXIT_FAILURE;
  }

  apr_pool_t *p_pool = NULL;
  if (initializePool(&p_pool, p_parent_pool) != APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  ResponseManager response_manager;
  if (createResponseManager(&response_manager, p_pool) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  int index;
  int count;
  int offset = -1;
  telebot_error_e ret;
  telebot_message_t message;
  telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};
  while (atomic_running) {
    telebot_update_t *updates;
    const int LIMIT = 20;
    const int TIMEOUT = 0;
    const int ALLOWED_UPDATES_COUNT = 0;
    ret = telebot_get_updates(this->m_handler, offset, LIMIT, TIMEOUT,
                              update_types, ALLOWED_UPDATES_COUNT, &updates,
                              &count);
    if (ret != TELEBOT_ERROR_NONE) {
      continue;
    }
    printf("Number of updates: %d\n", count);
    for (index = 0; index < count; index++) {
      message = updates[index].message;
      if (message.text == NULL) {
        offset = updates[index].update_id + 1;
        continue;
      }
      const int STRING_SIZE = 4096;
      char str[STRING_SIZE];
      memset(str, 0, STRING_SIZE);
      char *p_str = str;
      if (getResponseString(&response_manager, p_pool, message.text, &p_str,
                            STRING_SIZE) != EXIT_SUCCESS) {
        destroyResponseManager(&response_manager);
        return cleanupAndTerminate(NO_TERMINATE, p_pool, EXIT_SUCCESS);
      }
      ret = telebot_send_message(this->m_handler, message.chat->id, p_str,
                                 "HTML", false, false,
                                 updates[index].message.message_id, "");
      if (ret != TELEBOT_ERROR_NONE) {
        printf("Failed to send message: %d \n", ret);
      }
      offset = updates[index].update_id + 1;
    }
    telebot_put_updates(updates, count);
    sleep(1);
  }
  destroyResponseManager(&response_manager);
  return cleanupAndTerminate(NO_TERMINATE, p_pool, EXIT_SUCCESS);
}
