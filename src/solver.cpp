#include "score.cpp"
#include "solver.hpp"

using namespace std;
string STOP = "";


void reader_routine(Reader& dataset, FairQueue<string>& queue,
                    unsigned int epochs, unsigned int nworkers){
    for (unsigned int i = 0; i < epochs; i++){
        dataset.top();
        while (true){
            string s = dataset.getLine();
            queue.push(s);
            try {
                dataset.next();
            } catch(const out_of_range& e){
                break;
            };
        };
    };
    for (size_t worker_id = 0; worker_id < nworkers; worker_id++){
        queue.send(worker_id, STOP);
    }
};


void worker_routine(unsigned int worker_id, Estimator& estimator,
                    FairQueue<string>& queue){
    Scorer scorer;
    while (true){
        string line = queue.pop(worker_id);
        if (line == STOP){
            queue.push(line);
            break;
        }
        Observation obs(line, true);
        double prediction = estimator.predict(obs);
        scorer.add(obs, prediction);
        estimator.fit(obs);
        if ((worker_id == 0) && (scorer.n % 100000 == 1)){
            scorer.show();
        }
    }
};


Estimator Hogwild(Estimator& estimator, Reader& dataset, unsigned int nepochs,
                  unsigned int nworkers){
    FairQueue<string> queue(nworkers);
    thread workers[nworkers];
    // 2. Launch threads
    thread reader (reader_routine, ref(dataset), ref(queue),
                   nepochs, nworkers);
    for(unsigned int wid = 0; wid < nworkers; wid++){
        workers[wid] = thread(worker_routine, wid, ref(estimator), ref(queue));
    };
    reader.join();
    for(unsigned int wid = 0; wid < nworkers; wid++) workers[wid].join();
    return estimator;
};


Scorer test(Estimator& estimator, Reader& reader){
    Scorer scorer;
    string line;
    reader.top();
    while (true){
        line = reader.getLine();
        Observation obs(line, true);
        scorer.add(obs, estimator.predict(obs));
        try {reader.next();}
        catch(const out_of_range& e){break;};
    }
    scorer.show();
    return scorer;
};