#include <iostream>
#include <string>
using namespace std;
class Copy{
public:
    Copy(int b, string *cstr)
	{
      a=b;
	  str = cstr;
    }
	 Copy()
	{
      a=0;
	  str = new string();
    }
	/*
	Copy(const Copy& C)
	{
	  a = C.a;
	  str = new string(*(C.str));
	}*/
    void show(){
	  cout<< str<<endl;
	  cout<< *str <<endl;
	}
	~Copy(){
	  delete str;
	  cout<<"delete is called"<<endl;
	}
	private:
    int a;
	string* str;
};

int main()
{
  string * t = new string("Hello");
  Copy A(10,t),B;
  B = A;
  //Copy C = A;
  cout<<"A"<<endl;
  A.show();
  cout<<"B"<<endl;
  B.show();
  //cout<<"C"<<endl;
  //C.show();
  return 0;
}  

