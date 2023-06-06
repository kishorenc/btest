#include <iostream>
#include <fstream>
#include <csignal>
#include <faiss/IndexIVFPQ.h>
#include "ivf_pq_hnsw.h"

using namespace ivfhnsw;

void run_sample() {
    int dim = 128;                       // Dimension of the elements
    int max_elements = 100 * 1000;        // Maximum number of elements, should be known beforehand
    size_t num_centroids = 32;
    size_t bytes_per_code = 16;
    size_t bits_per_idx = 8;

    // Generate random data
    std::mt19937 rng;
    rng.seed(47);
    std::uniform_real_distribution<> distrib_real;
    float* data = new float[dim * max_elements];
    for (int i = 0; i < dim * max_elements; i++) {
        data[i] = distrib_real(rng);
    }

    uint32_t* ids = new uint32_t [max_elements];
    for (int i = 0; i < max_elements; i++) {
        ids[i] = i;
    }

    IndexIVF_HNSW *index = new IndexIVF_HNSW(dim, num_centroids, bytes_per_code, bits_per_idx);
    index->do_opq = false;
    index->nprobe = 8;
    index->max_codes = 1000;

    index->build_quantizer(max_elements, data);
    index->train_pq(max_elements, data);
    index->add_batch(max_elements, data, ids);

    auto begin = std::chrono::high_resolution_clock::now();

    // Query the elements for themselves and measure recall
    float correct = 0;
    size_t k = 1;
    float distances[k];
    long labels[k];

    for (int i = 0; i < max_elements; i++) {
        index->search(k, data + i*dim, distances, labels);
        hnswlib::labeltype label = labels[0];
        if (label == i) {
            correct++;
        }
    }
    long long int timeMillis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin).count();
    std::cout << "Time taken: " << timeMillis << "ms" << std::endl;

    float recall = correct / max_elements;
    std::cout << "correct: " << correct << "\n";
    std::cout << "Recall: " << recall << "\n";

    delete[] data;
    delete index;
}

int main() {
//    run_sample();
//    return 0;

    size_t bytes_per_code = 32;
    size_t bits_per_idx = 8;
    size_t num_centroids = 128;
    size_t vecsize = 1*1000*1000;
    size_t vecdim = 128;
    size_t train_size = 10*1000;
    size_t nq = 10000;
    size_t ngt = 100;

    // predict accuracy
    std::cout << "Loading groundtruth" << std::endl;
    std::vector<uint32_t> massQA(nq * ngt);
    {
        std::ifstream gt_input("/tmp/data/sift/sift/sift_groundtruth.ivecs", std::ios::binary);
        readXvec<uint32_t>(gt_input, massQA.data(), ngt, nq);
    }

    // Parse groundtruth
    //===================
    std::cout << "Parsing groundtruth" << std::endl;
    std::vector<std::priority_queue< std::pair<float, uint32_t >>> answers;
    (std::vector<std::priority_queue< std::pair<float, uint32_t >>>(nq)).swap(answers);
    for (size_t i = 0; i < nq; i++) {
        answers[i].emplace(0.0f, massQA[ngt*i]);
    }

    // Load Queries
    //==============
    std::cout << "Loading queries" << std::endl;
    std::vector<float> massQ(nq * vecdim);
    {
        std::ifstream query_input("/tmp/data/sift/sift/sift_query.fvecs", std::ios::binary);
        readXvecFvec<float>(query_input, massQ.data(), vecdim, nq);
        query_input.close();
    }

    IndexIVF_HNSW *index = new IndexIVF_HNSW(vecdim, num_centroids, bytes_per_code, bits_per_idx);
    index->do_opq = false;
    index->nprobe = 64;
    index->max_codes = 10*1000;

    std::cout << "init index\n" << std::flush;

    float* mass = new float[vecsize * vecdim];
    std::ifstream input("/tmp/data/sift/sift/sift_base.fvecs", std::ios::binary);
    readXvecFvec<float>(input, mass, vecdim, vecsize);
    input.close();

    uint32_t* ids = new uint32_t [vecsize];

    for (int i = 0; i < vecsize; i++) {
        ids[i] = i;
    }

    index->build_quantizer(train_size, mass);
    index->train_pq(train_size, mass);
    index->add_batch(vecsize, mass, ids);

    delete [] ids;
    delete [] mass;

    std::cout << "Done indexing. Will compute recall.\n";

    //========
    // Search
    //========
    size_t k = 1;
    size_t correct = 0;
    float distances[k];
    long labels[k];

    for (size_t i = 0; i < nq; i++) {
        index->search(k, massQ.data() + i*vecdim, distances, labels);
        std::priority_queue<std::pair<float, uint32_t >> gt(answers[i]);
        std::unordered_set<uint32_t> g;

        while (gt.size()) {
            g.insert(gt.top().second);
            gt.pop();
        }

        for (size_t j = 0; j < 1; j++) {
            if (g.count(labels[j]) != 0) {
                correct++;
                break;
            }
        }
    }

    //===================
    // Represent results
    //===================
    std::cout << "Recall@" << 1 << ": " << 1.0f * correct / 10000 << std::endl;

    sleep(10000);

    return 0;
}