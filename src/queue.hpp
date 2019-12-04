#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>
#include <queue>
#include <random>
#include <vector>
#include <iostream>
#include <condition_variable>

using namespace std;
#define QUEUE_MAX_SIZE 1024 * 10 // TODO: this should be a parameter
extern mt19937 RandomNumberGenerator;


/*
 * Thread-safe queue implementation.
 */

template <typename T>
class SharedQueue{
private:
    condition_variable available;
    condition_variable room_left;
    deque<T> queue;
    mutex qlock;
public:
    SharedQueue();
    ~SharedQueue();
    void push(T& elem);
    T pop();
};


/*
 * Work-distribution queue. 
 * Each consumer has a dedicated queue and the work is 
 * distributed uniformly among theese.
 */
template <typename T>
class FairQueue{
private:
    unsigned int nworkers;
    vector<SharedQueue<T>> queues;
    uniform_int_distribution<int> distribution;

public:
    FairQueue(unsigned int nworkers, unsigned int hwm=2000);
    ~FairQueue();
    void send(unsigned int worker_id, T& msg);
    void push(T& elem);
    T pop(unsigned int worker_id);
};

#endif