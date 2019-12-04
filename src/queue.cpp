#include <string>
#include "queue.hpp"

using namespace std;

mt19937 RandomNumberGenerator(0);


template <typename T>
SharedQueue<T>::SharedQueue(){};

template <typename T>
SharedQueue<T>::~SharedQueue(){};

template<typename T>
void SharedQueue<T>::push(T& elem){
    unique_lock<mutex> lock(qlock);
    // If the queue is full, wait.
    while (queue.size() == QUEUE_MAX_SIZE) room_left.wait(lock);
    bool empty = queue.empty();
    queue.push_back(elem);
    lock.unlock();
    if (empty) available.notify_one();
};

template<typename T>
T SharedQueue<T>::pop(){
    unique_lock<mutex> lock(qlock);
    while (queue.empty()) available.wait(lock);
    bool full = queue.size() == QUEUE_MAX_SIZE;
    T elem = queue.front();
    queue.pop_front();
    if (full) room_left.notify_one();
    return elem;
}


template <typename T>
FairQueue<T>::FairQueue(unsigned int nworkers, unsigned int hwm){
    this->nworkers = nworkers;
    distribution = uniform_int_distribution<int> (0, nworkers - 1);
    queues = vector<SharedQueue<T>>(nworkers);
};

template <typename T>
FairQueue<T>::~FairQueue(){};

template<typename T>
void FairQueue<T>::send(unsigned int worker_id, T& msg){
    queues[worker_id].push(msg);
};

template<typename T>
void FairQueue<T>::push(T& elem){
    int worker_id = distribution(RandomNumberGenerator);
    queues[worker_id].push(elem);
};

template<typename T>
T FairQueue<T>::pop(unsigned int worker_id){
    return queues[worker_id].pop();
};

template class FairQueue<string>;
