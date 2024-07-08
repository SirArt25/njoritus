#ifndef NJORITUS_BOT_H
#define NJORITUS_BOT_H

#include <apr_pools.h>
#include <telebot.h>

typedef struct {
  telebot_handler_t m_handler;
  telebot_user_t m_user;
} NjoritusBot;

int setupNjoritusBot(NjoritusBot *this);
void destroyNjoritusBot(NjoritusBot *this);
int runNjoritusBot(NjoritusBot *this, apr_pool_t *p_parent_pool);

#endif // NJORITUS_BOT_H
