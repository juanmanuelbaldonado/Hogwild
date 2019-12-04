#include <cmath>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "glm.hpp"
#include "reader.hpp"
#include "solver.hpp"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;
typedef std::chrono::high_resolution_clock Clock;


int main(int argc, char *argv[]){
    // Supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("train-files", po::value<string>(), "Training dataset files")
        ("test-files", po::value<string>(), "Testing dataset files")
        ("regression", po::value<string>()->default_value("logistic"), "Testing dataset files")
        ("eta", po::value<double>()->default_value(0.01), "learning rate")
        ("lambda", po::value<double>()->default_value(0), "L2 regularization coefficient")
        ("epochs", po::value<unsigned int>()->default_value(1), "number of epochs")
        ("nworkers", po::value<unsigned int>()->default_value(1), "number of workers")
        ("bits", po::value<unsigned int>()->default_value(22), "Size in bits of the parameter vector")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    string train_path = vm["train-files"].as<string>();
    string test_path;
    if (vm.count("test-files")){
        test_path = vm["test-files"].as<string>();
    } else {
        test_path = train_path;
        cout << "No test files provided. "
             << "Using input files as test files" << endl;
    }
    unsigned int bits = vm["bits"].as<unsigned int>();
    double eta = vm["eta"].as<double>();
    double lambda = vm["lambda"].as<double>();
    unsigned int nepochs = vm["epochs"].as<unsigned int>();
    unsigned int nworkers = vm["nworkers"].as<unsigned int>();

    cout << "Fiting estimator.." << endl;
    Reader training_dataset(train_path);
    auto start = Clock::now();
    GLM estimator(LOGISTIC, bits, lambda, eta);
    Hogwild(estimator, training_dataset, nepochs, nworkers);
    auto end = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    cout << "Time: " << duration.count() << endl;
    cout << "Done." << endl;
    cout << "Testint estimator.." << endl;
    Reader test_dataset(train_path);
    test(estimator, test_dataset);
}

