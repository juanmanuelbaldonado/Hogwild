#include <vector>
#include <random>
#include <pthread.h>
#include "utils.cpp"
#include "estimator.cpp"

using namespace std;
mt19937 RandomNumberGenerator;


struct worker_args{
    unsigned int worker_id;
    unsigned int size;
    double sample_rate;
    unsigned int maxiters;
    // atomic<int> global_consumed;
    ModelSpec* model;
    CSVReader* dataset;
    Estimator* estimator;
};

void* worker_routine(void* voidArgs){
    struct worker_args *args;
    args = (struct worker_args *) voidArgs;
    mt19937 RandomNumberGenerator(0);
    bernoulli_distribution sample(args->sample_rate);

    std::string path = "../ADMM/data/avazu/train";
    CSVReader dataset(path, ',');
    // args->dataset = &dataset;

    int consumed = 0;
    int sample_size = 10 * 1000000;
    double residual_sum = 0;
    int log_every = 100000;

    cout << "Here " << args->worker_id << endl;
    cout << "Started training.." << endl;

    for(int iter = 0; iter < 10; iter++){
        dataset.restart();
        for (size_t i = 0; i < sample_size; i++){
            if (sample(RandomNumberGenerator)){
                Row row = dataset.get();
                Observation obs(row, *(args->model));
                residual_sum += args->estimator->fit(obs);
                consumed++;
            }
            if ((i % log_every) == 0){
                if (args->worker_id == 0){
                    cout << "Worker " <<  args->worker_id 
                         << " consumed " << consumed << " observations | "
                         << "Fetures " << args->estimator->feature_count() << " | " 
                         << "Avg residual: " << (residual_sum / log_every) << endl;
                    residual_sum = 0;
                }
            } 
            dataset.next();
        }
    };
    pthread_exit(NULL);
}



/*
 * HOGWILD solver.
 * @param size: size in bits of the estimator parameter vector.
 * @param eta: learning rate
 * @param lambda: L1 regularization coefficient.
 * @param model: model specification.
 * @param maxiters: number of iterations.
 * 
 * @return record as a vector of strings.
 */
Estimator Hogwild(unsigned int size, double eta, double lambda, int nworkers,
                  ModelSpec model, Regression& regression, double sample_rate,
                  unsigned int maxiters, CSVReader& dataset){
    // 1. Initialize local estimator & local variables.
    Estimator estimator(regression, size, lambda, eta);
    // 2. Intialize threads
    worker_args args[nworkers];
    pthread_t workers[nworkers];
    for(int worker_id = 0; worker_id < nworkers; worker_id++){
        args[worker_id].worker_id = worker_id;
        args[worker_id].size = size;
        args[worker_id].sample_rate = sample_rate;
        args[worker_id].maxiters = maxiters;
        args[worker_id].model = &model;
        args[worker_id].dataset = &dataset;
        args[worker_id].estimator = &estimator;
        int status = pthread_create(&workers[worker_id], NULL, worker_routine,
                                    &args[worker_id]);
        if (status) {
            cout << "Error:unable to create thread," << status << endl;
            exit(-1);
        }
    }
    for(int worker_id = 0; worker_id < nworkers; worker_id++){
        pthread_join(workers[worker_id], NULL);    
    }
    cout << "Done" << endl;
};
