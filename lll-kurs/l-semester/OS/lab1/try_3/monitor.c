#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

bool ready = false;
bool stop = false;

void *thread1_function(void *arg) {
  while (1){
    printf("\n");
    //printf("start from 1");
    while(pthread_mutex_trylock(&mutex)!=0){} // ожидание разблокировки мьютекса
    //в случае успеха pthread_mutex_trylock() возвращает 0 и блокирует мьютекс
    //pthread_mutex_lock(&mutex);
    printf("Поток 1: блокировка мьютекса.\n");
    //getchar();
    // Отправка события потоку 2
    printf("Поток 1: Отправка события потоку 2\n");
    pthread_cond_signal(&cond); // событие
    pthread_mutex_unlock(&mutex);
    printf("Поток 1: разблокировка мьютекса.\n");
    // Дополнительные действия потока 1
    //getchar();
    sleep(1);
  }
  return NULL;
}
void *thread2_function(void *arg) {
  while (1) {
    //printf("start from 2");
    while(pthread_mutex_trylock(&mutex)!=0){}
    //pthread_mutex_lock(&mutex);   
    printf("Поток 2: блокировка мьютекса.\n");
    //getchar();
    // Ожидание события
    pthread_cond_wait(&cond, &mutex);
    printf("Поток 2: Событие получено\n");
    pthread_mutex_unlock(&mutex);
    printf("Поток 2: разблокировка мьютекса\n.");
    //getchar();
    sleep(1);
  }
  return NULL;
}

int K = 0;
void *t1(void *arg){
  int i=8;
  while(i>0){
    i--;
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
  stop = 1;
  return NULL;
}
void *t2(void *arg){
  while(!stop){
    pthread_mutex_lock(&mutex);
    while (ready == 0)
    {
      pthread_cond_wait(&cond, &mutex);
      printf("Поток 2: Событие получено.\n");
    }
    
    ready = 0;
    printf("Поток 2: Разблокировка мьютекса\n");
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

    //pthread_mutex_unlock(&mutex);
    /*int b=0;
    //int b = pthread_mutex_unlock(&mutex);
    printf("%d", b);    // 0
    pthread_mutex_lock(&mutex);
    printf("%d", b);    // 0
    pthread_mutex_unlock(&mutex);
    b = pthread_mutex_trylock(&mutex);
    printf("%d", b);    // 0
    b = pthread_mutex_trylock(&mutex);
    printf("%d", b);    // 16
    pthread_mutex_unlock(&mutex);
    b = pthread_mutex_trylock(&mutex);
    printf("%d", b);    // 0
    b = pthread_mutex_trylock(&mutex);
    printf("%d", b);    // 16
    pthread_mutex_unlock(&mutex);
    b = pthread_mutex_trylock(&mutex);
    printf("%d", b);    // 0
    return 0;
*/
    //pthread_cond_wait(&cond, &mutex);
    pthread_create(&thread1, NULL, t1, NULL);
    pthread_create(&thread2, NULL, t2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    //pthread_join(thread1, NULL);

    //pthread_create(&thread1, NULL, thread1_function, NULL);
    //pthread_create(&thread2, NULL, thread2_function, NULL);
    //pthread_mutex_unlock(&mutex);
    //t2(NULL);
    //pthread_join(thread2, NULL);
    
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
    printf("HH");

  // Создание потоков
  //pthread_create(&thread1, NULL, thread1_function, NULL);
  //pthread_create(&thread2, NULL, thread2_function, NULL);

  // Ожидание завершения потоков
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Очистка мьютекса и условия
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}

