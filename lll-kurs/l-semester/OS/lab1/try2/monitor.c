#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex;    // МЬЮТЕКС  
pthread_cond_t cond;      // УСЛОВИЕ  (оно выступает событием)


void *thread1_function(void *arg) {
  while (1){
    while(pthread_mutex_trylock(&mutex)!=0){} // ожидание разблокировки мьютекса
    //в случае успеха pthread_mutex_trylock() возвращает 0 и блокирует мьютекс
    //если мьютекс уже заблокирован, то возвращает отличное от нуля значение
    printf("Поток 1: блокировка мьютекса.\n");
    // Отправка события потоку 2
    printf("Поток 1: Отправка события потоку 2\n");
    pthread_cond_signal(&cond); // событие
    pthread_mutex_unlock(&mutex);
    printf("Поток 1: разблокировка мьютекса.\n");
    sleep(1);
  }
  return NULL;
}

void *thread2_function(void *arg) {
  while (1) {
    while(pthread_mutex_trylock(&mutex)!=0){}
    printf("Поток 2: блокировка мьютекса.\n");
    // Ожидание события
    pthread_cond_wait(&cond, &mutex);
        // разблокирует мьютекс и ждёт COND
        // после получения COND снова блокирует мьютекс и идёт дальше
        // фактом получение COND выступает pthread_cond_signal(&cond)
            // который достаётся потоку, который "поймал условия первее всех"
    printf("Поток 2: Событие получено\n");
    pthread_mutex_unlock(&mutex);
    printf("Поток 2: разблокировка мьютекса\n.");
    sleep(1);
  }
  return NULL;
}


/* т.к. обмен событием происходит в бесконечном цикле
    прервать программу остаётся только через KeyboardInterrupt,
    то есть комбинацию клавиш в консоли Ctrl+C
*/
int main() {
    pthread_t thread1, thread2;

      // Инициализация мьютекса и условия(события)
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
      // Создание потоков
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);
      // Запуск потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
      // уничтожение переменных мьютекса и условия(события)   
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;


