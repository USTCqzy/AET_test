#include "aet.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

void test_MSR(std::string work_file) {
    Options* options = new Options();
    options->block_size = 4096;
    options->model = MODEL0;

    // init monitor
    aetInitMonitor(options);

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream infile;
    std::string str;
    std::string op = "";
    infile.open(work_file);
    if( !infile.good()){
        std::cout << "open file fail!" << work_file << std::endl;
        exit(0);
    }
    while(infile.good() && !infile.eof()){
        getline(infile, str);
        if(str == "") continue;
        std::string space_delimiter = ",";
        std::vector<std::string> words{};
        words.clear();
        size_t pos = 0;
        while ((pos = str.find(space_delimiter)) != std::string::npos) {
            words.push_back(str.substr(0, pos));
            str.erase(0, pos + space_delimiter.length());
        }
        words.push_back(str.substr(0, pos));
        int start = strtol(words[4].c_str(), NULL, 10) >> 12; // 4096 Bytes
        int end = (strtol(words[4].c_str(), NULL, 10) + strtol(words[5].c_str(), NULL, 10) - 1) >> 12; // 4096 Bytes
        op = words[3];
        if(op == "Read"){
            for(int index = start; index <= end; index++){
                // record access
                aetAccessUniform(index, false);
            }
        }
        else if(op =="Write"){
            for(int index = start; index <= end; index++){
                // record access
                aetAccessUniform(index, true);
            }
        }
        else{
            std::cout << "error parameter" << op << std::endl;
        }
    }
    infile.close();

    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    printf("loading workload and aet access finished in %.3lf s\n", time);
    fflush(stdout);

    // generate MRC
    start = std::chrono::high_resolution_clock::now();
    size_t test_size = 1 << 39; // 512GB / 4096B / 
    double *mrc = (double *)malloc(sizeof(double) * (test_size >> 5 + 10));
    assert(mrc != NULL);
    aetCalculateMRC(test_size, 32, mrc);
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    printf("calculate MRC finished in %.3lf s\n", time);
    fflush(stdout);

    // print MRC
    int step = 1;
    for (int i = 0; i < 1100 * 1000 * 1000; i = i + step, step = step * 1.5) {
        printf("%d, %.3lf\n", i, mrc[i]);
    }
    fflush(stdout);

    // free monitor
    aetFreeMonitor();
}

int main(const int argc, const char **argv) {
    // get trace file from command line
    if(argc < 2){
        std::cout << "please input trace file" << std::endl;
        exit(0);
    }
    std::string work_file = argv[1];
    test_MSR(work_file);
    return 0;
}