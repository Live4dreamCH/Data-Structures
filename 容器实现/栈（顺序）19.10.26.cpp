#include <iostream>
using namespace std;

template<class T>
class stack	//由于此问题中，栈的最大长度即为物件数，故使用顺序栈
{
	int MaxSize;
	T* base;
	int top;
public:
	stack(int size)
	{
		if (size < 0)
		{
			cerr << "长度不能为负！";
			exit(0);
		}
		else
		{
			MaxSize = size;
			base = new T[MaxSize];
			if (base == NULL)
			{
				cerr << "创建失败！";
				exit(0);
			}
			else
			{
				top = 0;
				cout << "创建栈成功，长度为" << MaxSize << endl;
			}
		}
	}
	stack(const stack &a)
	{
		MaxSize = a.MaxSize;
		MaxSize;
		base = a.base;
		top = a.top;
	}
	~stack()	//摧毁栈
	{
		delete[]base;
	}
	bool IsEmpty()const
	{
		if (top == 0)
			return true;
		return false;
	}
	bool IsFull()const
	{
		if (top == MaxSize)
			return true;
		return false;
	}
	void clear()	//清空元素
	{
		top = 0;
	}
	int len()const	//求长度
	{
		return top;
	}
	void push(T &e)
	{
		if (IsFull())
			cout << "栈已满，无法插入！" << endl;
		else
			base[top++] = e;
	}
	T pop()			//返回并删除栈顶元素
	{
		if (IsEmpty())
			cout << "栈为空，无法弹出！" << endl;
		else
			return base[--top];
	}
	T GetTop()	//仅返回栈顶元素，但不删除
	{
		if (IsEmpty())
			cout << "栈为空，无法获取！" << endl;
		else
			return base[top - 1];
	}
	T add()			//对栈进行魔改233
	{
		T sum = 0;
		for (int i = 0; i < top; i++)
		{
			sum += base[i];
		}
		return sum;
	}
	void print()	//测试用
	{
		/*for (int i = 0; i < top; i++)
		{
			cout << base[i] << ends;
		}
		cout << endl;*/

		cout << '{' << base[0];
		for (int i = 1; i < top; i++)
		{
			cout << ',' << base[i];
		}
		cout << '}' << endl;
	}
};