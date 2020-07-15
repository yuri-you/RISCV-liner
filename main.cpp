#include<iostream>
#include<iomanip>
#include"register.hpp"
#include"instruction_fetch.hpp"
#include"instruction_decode.hpp"
#include"execute.hpp"
#include"memory_access.hpp"
#include"write_back.hpp"
using std::cin;
using std::cout;
int main() {
    MEM doc;
    ID tmp1;
    EX tmp2;
    MA tmp3;
    do {
        tmp1 = doc.fetch();
        tmp2 = tmp1;
        tmp3 = tmp2;
    }
    while(WB(tmp3));
    return 0;
}