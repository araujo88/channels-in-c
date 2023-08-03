#include <pthread.h>

#define CHANNEL_SIZE 10 // You can adjust the size of the channel

typedef struct
{
  int buffer[CHANNEL_SIZE];
  int front, rear;
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t notEmpty;
  pthread_cond_t notFull;
} channel;

void channel_init(channel *ch);
void channel_send(channel *ch, int value);
int channel_receive(channel *ch);
void channel_destroy(channel *ch);
