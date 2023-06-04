#include <iostream>
#include <fstream>
#include <csignal>
#include "ivf_pq_hnsw.h"

using namespace ivfhnsw;

int main() {
    size_t code_size = 32;
    size_t num_centroids = 128;
    size_t vecsize = 1*1000*1000;
    size_t vecdim = 128;

    IndexIVF_HNSW *index = new IndexIVF_HNSW(vecdim, num_centroids, code_size, 8);
    index->do_opq = true;

    std::cout << "init index\n" << std::flush;

    float* mass = new float[vecsize * vecdim];
    std::ifstream input("/tmp/sift_base.fvecs", std::ios::binary);
    input.read((char *) mass, vecsize * vecdim * sizeof(float));
    input.close();

    uint32_t* ids = new uint32_t [vecsize];

    for (int i = 0; i < vecsize; i++) {
        ids[i] = i;
    }

    index->build_quantizer(vecsize, mass);
    index->train_pq(10*1000, mass);
    index->add_batch(vecsize, mass, ids);

    delete [] ids;
    delete [] mass;

    std::cout << "Done indexing. Sleeping now.\n";

    sleep(10000);

    return 0;
}