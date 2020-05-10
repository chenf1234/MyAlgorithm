#include <iostream>
#include <set>
using namespace std;
int main(){
    set<int> s;
    pair<set<int>::iterator,bool> i=s.insert(1);
    cout<<i.second<<" "<<*(i.first)<<endl;
    i=s.insert(1);
    cout<<i.second<<" "<<*(i.first)<<endl;
    set<int>::iterator it=s.begin();
    cout<<*it<<endl;
}