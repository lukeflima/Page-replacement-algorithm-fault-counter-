#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

std::stringstream output;

int main(int argc, char const *argv[])
{
    ///Ler entrada
    std::fstream f("input",  std::ifstream::in);

    size_t memSize;
    f >> memSize;

    std::vector<int> mem(memSize,0);

    int temp;
    std::vector<int> pages;
    while(!f.eof()) {
        f >> temp;
        pages.push_back(temp);
    }

    //####################################################################

    //FIFO
    int falts = 0, memIndex = 0;
    for(auto page: pages){
        if(std::find(mem.begin(), mem.end(), page) == mem.end()){ //  se não estiver na memoria
            ++falts;
            mem[memIndex] = page;
            memIndex = (memIndex + 1) % memSize;
        }
    }

    std::cout << "FIFO " << falts << '\n';
    output << "FIFO " << falts << '\n';
    //####################################################################

    //OTM
    for(auto &v: mem) v = 0; // zerando memória
    falts = memIndex = 0;
    for(int i = 0; i < pages.size(); i++){
        if(std::find(mem.begin(), mem.end(), pages[i]) == mem.end()){ //  se não estiver na memoria
            ++falts;
            if(!mem[memIndex]){ // se estiver lugar vazio na memória
                mem[memIndex] = pages[i];
                memIndex = (memIndex + 1) % memSize;
            }else{
                std::vector<int> delay;
                std::copy(mem.begin(), mem.end(), std::back_inserter(delay));
                std::for_each(delay.begin(), delay.end(), [&pages,i](auto &p){
                    p = std::distance(pages.begin() + i, std::find(pages.begin() + i, pages.end(), p)); // calcula o tempo
                });

                //calcula o máximos dos tempo e substitui a página
                mem[std::distance(delay.begin(), std::max_element(delay.begin(), delay.end()) )] = pages[i];
            }
        }
    }

    std::cout << "OTM " << falts << '\n';
    output << "OTM " << falts << '\n';
    //###################################################################

    //LRU
    for(auto &v: mem) v = 0; // zerando memória
    falts = memIndex = 0;
    for(int i = 0; i < pages.size(); i++){
        if(std::find(mem.begin(), mem.end(), pages[i]) == mem.end()){ //  se não estiver na memoria
            ++falts;
            if(!mem[memIndex]){
                mem[memIndex] = pages[i];
                memIndex = (memIndex + 1) % memSize;
            }else{
                std::vector<int> delay;
                std::copy(mem.begin(), mem.end(), std::back_inserter(delay));
                std::for_each(delay.begin(), delay.end(), [&pages,i](auto &p){ // calcula o tempo
                    p = std::distance(pages.rbegin() + (pages.size() - i - 1), std::find(pages.rbegin() + (pages.size() - i - 1), pages.rend(), p));
                });

                //calcula o máximos dos tempo e substitui a página
                mem[std::distance(delay.begin(), std::max_element(delay.begin(), delay.end()) )] = pages[i];
            }
        }
    }

    std::cout << "LRU " << falts << '\n';
    output << "LRU " << falts << '\n';

    std::ofstream out("output", std::ofstream::out);
    out << output.str();

    return 0;
}