#include <deque>
#include <iostream>

using namespace std;

int main(){
  deque<int> dq;

  dq.push_back(1);
  dq.push_back(2);
  dq.push_back(3);
  cout << dq.front() << endl;

  dq.pop_front();
  cout << dq.front() << endl;  
}
