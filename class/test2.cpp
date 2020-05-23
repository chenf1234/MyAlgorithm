#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main(){
    set<int> s;
    vector<int> v(100);
    //v.reserve(100);
    v.resize(50);;
    //v.push_back(1);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    pair<set<int>::iterator,bool> i=s.insert(1);
    cout<<i.second<<" "<<*(i.first)<<endl;
    i=s.insert(1);
    cout<<i.second<<" "<<*(i.first)<<endl;
    set<int>::iterator it=s.begin();
    cout<<*it<<endl;
}