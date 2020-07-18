#include<iostream>
#include<thread>
#include<string>

using namespace std;

void print(string name){
    cout<<name<<endl;
}

int i;
void calculate(){
    for(int j=0;j<50;++j)
        ++i;
}
int main(){
    string name="Emirhan";
    thread print_name(print,name);
    print_name.join();

    thread c1(calculate);
    thread c2(calculate);
    thread c3(calculate);
    thread c4(calculate);
    
    c1.join();
    c2.join();
    c3.join();
    c4.join();

    cout<<i<<endl;
    return 0;
}