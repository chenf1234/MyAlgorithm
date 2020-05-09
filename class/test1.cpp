#include <iostream>
using namespace std;
class test1{
    private:
        int member;
    public:
        test1():member(2){}
        test1& operator++(){
            ++member;
            return *this;
        }
        const test1 operator++(int){
            test1 tmp=*this;
            member++;
            return tmp;
        }
        friend ostream& operator<<(ostream& os,const test1& t){
            os<<t.member<<endl;
            return os;
        }
};
int main(){
    test1 t;
    test1 t1=++t;
    cout<<t1++;
    cout<<++t;
    cout<<t1;
}