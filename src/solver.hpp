#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <thread>
#include <vector>
#include "queue.hpp"
#include "score.hpp"
#include "estimator.hpp"

using namespace std;
extern string STOP;


void reader_routine(Reader& dataset, FairQueue<string>& queue,
                    unsigned int epochs, unsigned int nworkers);


void worker_routine(unsigned int worker_id, Estimator& estimator,
                    FairQueue<string>& queue);


/*
 * Fit an estimator using Hogwild! SGD.
 * @param estimator: estimator to be fitted.
 * @param dataset
 * @param nepochs: number of iteration on the dataset.
 * @param nworkers: number of workers.
 * 
 * @return fitted estimator
 */
Estimator Hogwild(Estimator& estimator, Reader& dataset, unsigned int nepochs,
                  unsigned int nworkers);


Scorer test(Estimator& estimator, Reader& reader);

#endif