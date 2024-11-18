#include <bits/stdc++.h>
using namespace std;
class vectorClk
{
  vector<int> clock;
  int pid;

public:
  vectorClk(int size, int pid)
  {
    clock.resize(size, 0);
    this->pid = pid;
  }
  void internalEvent()
  {
    clock[pid]++;
  }
  vector<int> send_mess()
  {
    clock[pid]++;
    return clock;
  }
  void rec_mess(vector<int> rec_clk)
  {
    for (int i = 0; i < clock.size(); i++)
      clock[i] = max(clock[i], rec_clk[i]);
    clock[pid]++;
  }
  void displayClk()
  {
    cout << "Vector Clock for process" << pid << ": (";
    for (int i : clock)
      cout << i << " ";
  }
};
int main()
{
  vectorClk p0(2, 0), p1(2, 1);
  p0.internalEvent();
  auto t1 = p0.send_mess();
  p1.rec_mess(t1);
  p1.internalEvent();
  auto t2 = p1.send_mess();
  p0.rec_mess(t2);
  p0.internalEvent();
  p0.displayClk();
  p1.displayClk();
  return 0;
}