#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Include the channel structure and functions here

void *producer(void *arg) {
  channel *ch = (channel *)arg;
  for (int i = 0; i < 20; i++) {
    channel_send(ch, i);
    printf("Sent: %d\n", i);
    usleep(100000); // Sleep for 100ms
  }
  return NULL;
}

void *consumer(void *arg) {
  channel *ch = (channel *)arg;
  for (int i = 0; i < 20; i++) {
    int value = channel_receive(ch);
    printf("Received: %d\n", value);
    usleep(150000); // Sleep for 150ms
  }
  return NULL;
}

int main() {
  channel ch;
  channel_init(&ch);

  pthread_t prod, cons;

  pthread_create(&prod, NULL, producer, &ch);
  pthread_create(&cons, NULL, consumer, &ch);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  channel_destroy(&ch);

  return 0;
}
  
