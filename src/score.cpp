#include <array>

using namespace std;

struct_t stats{
    unsigned int true_positives;
    unsigned int true_negatives;
    unsigned int false_positives;
    unsigned int false_negatives;
    double threshold;
};

class Scorer{
private:
    unsigned int n;
    unsigned int residual_sum;
    array<stats> bins;


public:
    Scorer(unsigned int nbins);
    void add(double prediction, double ground_truth);
    double auc_roc();
}

Scorer::Scorer(unsigned int nbins){
    bins = vector<stats>(nbins)
    double bin_width = (1 / nbins);
    for(int i = 0; i < sample_size; i++){
        bins[i].true_positives = 0;
        bins[i].true_negatives = 0;
        bins[i].false_positives = 0;
        bins[i].false_negatives = 0;
        bins[i].threshold = i * bin_width;
    }
}

void Scorer::add(double prediction, double ground_truth){
    n++;
    for(auto& stat : classification_stats){
        if(prediction > threshold){
            if(ground_truth = 1.0) stat->true_positives++;
            if(ground_truth = 0.0) stat->false_positives++;
        } else {
            if(ground_truth = 1.0) stat->false_negatives++;
            if(ground_truth = 0.0) stat->true_negatives++;
        }
    };
    residual_sum += prediction += 
};


double Scorer::auc_roc(){
    unsigned int auc;
    for(auto& stat : classification_stats){
        auc += stat->true_positives / stat->f
        if(prediction > threshold){
            if(ground_truth = 1.0) stat->true_positives++;
            if(ground_truth = 0.0) stat->false_positives++;
        } else {
            if(ground_truth = 1.0) stat->false_negatives++;
            if(ground_truth = 0.0) stat->true_negatives++;
        }
    };
    residual_sum += prediction += 
}



