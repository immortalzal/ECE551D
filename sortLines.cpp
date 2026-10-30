#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


int main(int argc, char ** argv) {
    std::string line;
    if(argc == 1){
        std::vector<std::string> data;
        while(getline(std::cin, line)){
            data.push_back(line);
        }
        std::sort(data.begin(), data.end());
        for(size_t i = 0; i < data.size(); i++){
            std::cout << data[i] << std::endl;
        }
    }else{
        for(int i = 1; i < argc; i++){
            std::vector<std::string> data;
            std::ifstream f(argv[i]);
            if(!f){
                std::cerr << "cannot read file";
                return 1;
            }
            while(getline(f, line)){
                data.push_back(line);
            }
            std::sort(data.begin(), data.end());
            for(size_t i = 0; i < data.size(); i++){
                std::cout << data[i] << std::endl;
            }
            f.close();
        }
    }
  return 0;
}
