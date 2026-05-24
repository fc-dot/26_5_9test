#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<map>
#include<set>
#include<algorithm>//标准算法头文件
#include <ctime>
#include <functional>
using namespace std;
class per 
{
public:
	per(int a, string b) :age(a), name(b) {}; 
	bool operator==(const per& p)
	{
		if (p.age == this->age && p.name == this->name)
			return true;
		else
			return false;
	}
	int age;
	string name;
};
class g 
{
public:
	bool operator()(const per& p1,const per&p2)
	{
		if (p1.age == p2.age/* && p1.name == p2.name*/)
			return true;
		else
			return false;
	}
};
int main()
{
	vector<per>v;
	per p1(12,"a");
	per p2(32,"b");
	per p3(32,"c");
	per p4(52,"d");
	per p5(62,"e");
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	vector<per>::iterator i = adjacent_find(v.begin(), v.end(),g());
	if (i != v.end())
		cout << i->name <<"\t"<<(i+1)->name <<endl;
	else
		cout << "没有找到" << endl;
	bool a=binary_search(v.begin(),v.end(),p2);
	system("pause");
};