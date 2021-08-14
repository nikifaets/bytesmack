#include <fstream>
#include <iostream>
#include <string>
#include "HTree.h"
#include <queue>
#include <cassert>
#include <unordered_map>
#include "Encoder.h"
#include "Bitset.h"
#include "Utils.h"
#include "FileReader.h"
#include "Archiver.h"
#include "FilePathManager.h"

int sum(int v){

    int res = 0;
    for(int i=0; i<=v; i++){

        res += i;
    }

    return res;
}

int main(){

    std::vector<byte> inp;

    Archiver archiver;

    std::string arch_name = "hhh";
    std::string fname1 = "CMakeFiles/CMakeDirectoryInformation.cmake";
    std::string fname3 = "archive";
    std::string fname4 = "testt/testrec";
    //std::string fname2 = "../test/text_1"
    std::vector<std::string> files = {fname1, fname4};
    std::string out_dir = "out1";

    FilePathManager h;
    std::vector<std::string> out;
    h.process_filename({fname1, fname4 }, out);
    for(auto& s : out){
        std::cout << s << std::endl;
    }
    archiver.compress(arch_name, files);
    //assert(false);
    archiver.decompress(arch_name, out_dir, out);
    
    return 0;

}