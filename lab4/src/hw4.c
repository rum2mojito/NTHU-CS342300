#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define P_NUM 5
#define LEFT (philosopher_number + P_NUM - 1) % P_NUM
#define RIGHT (philosopher_number + 1) % P_NUM

typedef enum state { THINKING, HUNGRY, EATING } state_t;

state_t p_state[5] = {THINKING, THINKING, THINKING, THINKING, THINKING};
pthread_mutex_t mutex;
pthread_cond_t cond_var[5];
pthread_t p[5];
int arg[5] = {0, 1, 2, 3, 4};

void hw4_init();
void philosopher(void *philosopher_number_p);
void pick_up_fork(int philosopher_number);
void return_fork(int philosopher_number);
void think(int philosopher_number);
void eat(int philosopher_number);
int test(int philosopher_number);

int main() {
  hw4_init();

  return 0;
}

void hw4_init() {
  printf("HW4 INIT...\r\n");
  pthread_mutex_init(&mutex, NULL);
  for (int i = 0; i < 5; i++) {
    pthread_cond_init(&cond_var[i], NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_create(&p[i], NULL, philosopher, &arg[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(p[i], NULL);
  }
}

void philosopher(void *philosopher_number_p) {
  int philosopher_number = *(int *)philosopher_number_p;
  // thinking
  think(philosopher_number);
  // hungry
  pick_up_fork(philosopher_number);
  // eating
  eat(philosopher_number);
  // end eating
  return_fork(philosopher_number);
}

void pick_up_fork(int philosopher_number) {
  printf("Philosopher %d is now HUNGRY and trying to pick up forks.\n",
         philosopher_number);
  // set philosopher state
  pthread_mutex_lock(&mutex);
  p_state[philosopher_number] = HUNGRY;
  pthread_mutex_unlock(&mutex);

  // testing
  int flag = test(philosopher_number);
  if (flag == 0) {
    printf("Philosopher %d can’t pick up forks and start waiting.\n",
           philosopher_number);
  }
  pthread_mutex_lock(&mutex);
  if (p_state[philosopher_number] != EATING) {
    pthread_cond_wait(&cond_var[philosopher_number], &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

void return_fork(int philosopher_number) {
  printf("Philosopher %d returns forks and then starts TESTING %d and %d.\n",
         philosopher_number, LEFT, RIGHT);
  pthread_mutex_lock(&mutex);
  p_state[philosopher_number] = THINKING;
  test(LEFT);
  test(RIGHT);
  pthread_mutex_unlock(&mutex);
}

int test(int philosopher_number) {
  if (p_state[philosopher_number] == HUNGRY && p_state[LEFT] != EATING &&
      p_state[RIGHT] != EATING) {
    p_state[philosopher_number] = EATING;
    pthread_cond_signal(&cond_var[philosopher_number]);
    return 1;
  }
  return 0;
}

void think(int philosopher_number) {
  int thinking_time = (rand() % 3) + 1;
  printf("Philosopher %d is now THINKING for %d seconds.\n", philosopher_number,
         thinking_time);
  sleep(thinking_time);
}

void eat(int philosopher_number) {
  printf("Philosopher %d is now EATING.\n", philosopher_number);
  int eating_time = (rand() % 3) + 1;
  sleep(eating_time);
}
