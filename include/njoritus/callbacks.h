#ifndef NJORITUS_CALLBACKS_H
#define NJORITUS_CALLBACKS_H

#include <stdio.h>

typedef void (*CallbackFunctionT)(int);

typedef union {
  CallbackFunctionT function;
  void *data;
} CallbackUnionT;

typedef enum { CALLBACK_TYPE_FUNCTION, CALLBACK_TYPE_DATA } CallbackTypeT;

typedef struct {
  CallbackUnionT callback;
  CallbackTypeT type;
} GeneralCallbackT;

static void setCallbackFunction(GeneralCallbackT *p_general_callback,
                                CallbackFunctionT func) {
  p_general_callback->callback.function = func;
  p_general_callback->type = CALLBACK_TYPE_FUNCTION;
}

static void setCallbackData(GeneralCallbackT *p_general_callback, void *data) {
  p_general_callback->callback.data = data;
  p_general_callback->type = CALLBACK_TYPE_DATA;
}

static int isCallbackData(GeneralCallbackT *p_general_callback) {
  return p_general_callback->type == CALLBACK_TYPE_DATA;
}

static int isCallbackFunction(GeneralCallbackT *p_general_callback) {
  return p_general_callback->type == CALLBACK_TYPE_FUNCTION;
}

#endif // NJORITUS_CALLBACKS_H
