#include <iostream>
using namespace std;

class lamportsClock{
    int clock;

    public:
    lamportsClock(){
        clock = 0;
    }
    void internalEvent(){
        clock++;
    }
    int send_mess(){
        clock++;
        return clock;
    }
    void rec_mess(int rec_timestamp){
        clock = max(rec_timestamp,clock)+1;
    }
    int getClock(){
        return clock;
    }
};

int main()
{
    lamportsClock p1,p2;
    p1.internalEvent();    
    p1.internalEvent();    
    p1.internalEvent();    
    p1.internalEvent();
    int t1 = p1.send_mess();
    p2.internalEvent();   
    p2.internalEvent();
    p2.rec_mess(t1);
    p2.internalEvent();   
    p2.internalEvent();   
    p2.internalEvent();
    int t2 = p2.send_mess();
    p1.internalEvent();   
    p1.internalEvent();
    p1.rec_mess(t2);

    cout<<"P1 : "<<p1.getClock()<<" P2 : "<<p2.getClock();   

    return 0;
}