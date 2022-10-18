// 0.1 Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях. Позиции битов нумеруются с 0.

#include <iostream>
using namespace std;
int count_ones(unsigned long int a)
{
  unsigned long int i = 1;
  int counter = 0;
 while(i<=a)
 {
  if( (a&i) != 0)
  {
    counter++;
  }
  
  i = i<<2;
 }
 return counter;
}

int main()
{
  unsigned long int a; 
  cin>>a;
  cout << count_ones(a);
}