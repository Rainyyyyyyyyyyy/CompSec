import time
import threading as thr


EVENT = thr.Event()   

def producer():   
    while True:
        print("Thread(producer): Initializing the event")
        EVENT.set()   
        time.sleep(1)
        
def consumer():   
    while True:
        print("Thread(consumer): Waiting for the event")
        EVENT.wait()    
        EVENT.clear()  
        print("Thread(consumer): Got the event")


PRODUCER_THREAD = thr.Thread(target=producer)
CONSUMER_THREAD = thr.Thread(target=consumer)
PRODUCER_THREAD.start()
CONSUMER_THREAD.start()

try:
    PRODUCER_THREAD.join()
    CONSUMER_THREAD.join()
