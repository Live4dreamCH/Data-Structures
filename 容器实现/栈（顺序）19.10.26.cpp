#include <iostream>
using namespace std;

template<class T>
class stack	//���ڴ������У�ջ����󳤶ȼ�Ϊ���������ʹ��˳��ջ
{
	int MaxSize;
	T* base;
	int top;
public:
	stack(int size)
	{
		if (size < 0)
		{
			cerr << "���Ȳ���Ϊ����";
			exit(0);
		}
		else
		{
			MaxSize = size;
			base = new T[MaxSize];
			if (base == NULL)
			{
				cerr << "����ʧ�ܣ�";
				exit(0);
			}
			else
			{
				top = 0;
				cout << "����ջ�ɹ�������Ϊ" << MaxSize << endl;
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
	~stack()	//�ݻ�ջ
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
	void clear()	//���Ԫ��
	{
		top = 0;
	}
	int len()const	//�󳤶�
	{
		return top;
	}
	void push(T &e)
	{
		if (IsFull())
			cout << "ջ�������޷����룡" << endl;
		else
			base[top++] = e;
	}
	T pop()			//���ز�ɾ��ջ��Ԫ��
	{
		if (IsEmpty())
			cout << "ջΪ�գ��޷�������" << endl;
		else
			return base[--top];
	}
	T GetTop()	//������ջ��Ԫ�أ�����ɾ��
	{
		if (IsEmpty())
			cout << "ջΪ�գ��޷���ȡ��" << endl;
		else
			return base[top - 1];
	}
	T add()			//��ջ����ħ��233
	{
		T sum = 0;
		for (int i = 0; i < top; i++)
		{
			sum += base[i];
		}
		return sum;
	}
	void print()	//������
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