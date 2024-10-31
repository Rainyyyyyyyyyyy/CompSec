#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

bool ready = false;

void *t1(void *arg){
  while(1){
    pthread_mutex_lock(&mutex);
    printf("Поток 1: Блокировка мьютекса.\n");
    if (ready == 1)
    {
      pthread_mutex_unlock(&mutex);
      printf("Поток 1: Разблокировка мьютекса.\n");
      continue;
    }
    ready = 1;
    printf("Поток 1: Отправка события.\n"); 
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}
void *t2(void *arg){
  while(1){
    pthread_mutex_lock(&mutex);
    while (ready == 0)
    {
      pthread_cond_wait(&cond, &mutex);
      printf("Поток 2: Событие получено.\n");
    }
    ready = 0;
    printf("Поток 2: Разблокировка мьютекса\n\n");
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}

int main() {
    pthread_t thread1, thread2;

  // Инициализация мьютекса и условия
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
  // Создание потоков
    pthread_create(&thread1, NULL, t1, NULL);
    pthread_create(&thread2, NULL, t2, NULL);
  // запуск потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
  // очистка переменных мьютекса и состояния
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}

