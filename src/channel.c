#include "../include/channel.h"

void channel_init(channel *ch)
{
    ch->front = ch->rear = ch->count = 0;
    pthread_mutex_init(&ch->mutex, NULL);
    pthread_cond_init(&ch->notEmpty, NULL);
    pthread_cond_init(&ch->notFull, NULL);
}

void channel_send(channel *ch, int value)
{
    pthread_mutex_lock(&ch->mutex);

    while (ch->count == CHANNEL_SIZE)
    {
        pthread_cond_wait(&ch->notFull, &ch->mutex);
    }

    ch->buffer[ch->rear] = value;
    ch->rear = (ch->rear + 1) % CHANNEL_SIZE;
    ch->count++;

    pthread_cond_signal(&ch->notEmpty);
    pthread_mutex_unlock(&ch->mutex);
}

int channel_receive(channel *ch)
{
    pthread_mutex_lock(&ch->mutex);

    while (ch->count == 0)
    {
        pthread_cond_wait(&ch->notEmpty, &ch->mutex);
    }

    int value = ch->buffer[ch->front];
    ch->front = (ch->front + 1) % CHANNEL_SIZE;
    ch->count--;

    pthread_cond_signal(&ch->notFull);
    pthread_mutex_unlock(&ch->mutex);

    return value;
}

void channel_destroy(channel *ch)
{
    pthread_mutex_destroy(&ch->mutex);
    pthread_cond_destroy(&ch->notEmpty);
    pthread_cond_destroy(&ch->notFull);
}
