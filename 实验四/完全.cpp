// ���ݽṹʵ��4.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include <iostream>
//#include<cstdlib>
//#include<ctime>
using namespace std;

template <class T>
class BinaryTreeNode	//�����
{
	//friend class binarytree <t>;
	//friend class binarysearchtree <t>;
	T data;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
public:
	BinaryTreeNode() {}
	BinaryTreeNode(const T &ele)
	{
		data = ele;
		left = right = 0;
	}
	BinaryTreeNode(const T &ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r)
	{
		data = ele;
		left = l;
		right = r;
	}
	~BinaryTreeNode() {}
	T value() const
	{
		return data;
	}
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& Node)
	{
		this = Node;
	}
	BinaryTreeNode<T>* &leftchild()
	{
		return left;
	}
	BinaryTreeNode<T>* &rightchild()
	{
		return right;
	}
	void setLeftchild(BinaryTreeNode<T>* l)
	{
		left = l;
	}
	void setRightchild(BinaryTreeNode<T>* r)
	{
		right = r;
	}
	void setValue(const T& val)	//��������·����ʱ�����ڷŸ裬���ú��������ּ�������233��
	{
		data = val;
	}
	bool isLeaf()const
	{
		if (right == 0 && left == 0)
			return true;
		return false;
	}
};

template <class T>
class BinaryTree	//δ��ȫʵ��
{
protected:
	BinaryTreeNode<T> *root;
public:
	BinaryTree()
	{
		root = 0;
	}
	BinaryTree(BinaryTreeNode<T>* r)
	{
		root = r;
	}
	~BinaryTree()
	{
		DeleteBinaryTree(root);
	}
	bool isEmpty()const
	{
		return root->isLeaf();
	}
	T visit(BinaryTreeNode<T> *&r)
	{
		return r->value();
	}
	BinaryTreeNode<T>* &Root() { return root; }
	//BinaryTreeNode<T>* Parent(BinaryTreeNode<T> *current)
	//{
	//}
	//BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T> *current)
	//{
	//}
	//BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T> *current)
	//{
	//}
	void CreatTree(const T &data, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree)
	{
		root = new BinaryTreeNode<T>(data, leftTree.Root(), rightTree.Root());
	}
	void CreatTree(BinaryTreeNode<T> *&r)
	{
		root = r;
	}
	void DeleteBinaryTree(BinaryTreeNode<T> *r)
	{
		delete root;
		root = 0;
	}
	void PreOrder(BinaryTreeNode<T> *r)
	{
		if (this->root == 0)
			return;
		visit(r);
		PreOrder(root->leftchild());
		PreOrder(root->rightchild());
	}
	void InOrder(BinaryTreeNode<T> *r)
	{
		if (r == 0)
			return;
		InOrder(r->leftchild());
		visit(r);
		InOrder(r->rightchild());
	}
	void PostOrder(BinaryTreeNode<T> *r)
	{
		if (root == 0)
			return 0;
		PostOrder(root->leftchild());
		PostOrder(root->rightchild());
		visit(r);
	}
	//void LevelOrder(BinaryTreeNode<T> *r)
	//{
	//}
};

template<class T>
class BSTree :public BinaryTree<T>
{
	int len, n;
public:
	//BSTree():BinaryTree(){}
	//~BSTree(){}
	BinaryTreeNode<T> *search(BinaryTreeNode<T> *subroot, const T &k)
	{
		BinaryTreeNode<T> *t = 0;
		if (subroot == 0)
		{
			return t;
		}
		if (k == subroot->value())
			return subroot;
		else if (k < subroot->value())
			t = search(subroot->leftchild(), k);
		else
			t = search(subroot->rightchild(), k);
		return t;
	}
	float searchlen(BinaryTreeNode<T> *subroot, int h = 0)
	{
		if (subroot == this->root)
		{
			len = n = h = 0;
		}
		if (subroot == 0)
			return 0;
		n++;
		h++;
		len += h;
		searchlen(subroot->leftchild(), h);
		searchlen(subroot->rightchild(), h);
		return (len / (float)n);
		;
	}
	void insert(BinaryTreeNode<T> *&root, const T&k)
	{
		if (root == 0)
			root = new BinaryTreeNode<T>(k);
		else
		{
			if (k < root->value())
				insert(root->leftchild(), k);
			else if (k == root->value())
				insert(root->rightchild(), k);
			else
				insert(root->rightchild(), k);
		}
	}
	bool Delete(const T&k)
	{
		BinaryTreeNode<T> *c = search(this->root, k);
		if (c == 0)
			return false;
		BinaryTreeNode<T> *p = parent(k);
		if (c->leftchild() == 0 || c->rightchild() == 0)
		{
			if (p == 0)
			{
				if (c->leftchild() == 0)
					this->root = c->rightchild();
				else
					this->root = c->leftchild();
			}
			else
			{
				if (c->leftchild() == 0)
				{
					if (c == p->leftchild())
						p->leftchild() = c->rightchild();
					else
						p->rightchild() = c->rightchild();
				}
				else
				{
					if (c == p->leftchild())
						p->leftchild() = c->leftchild();
					else
						p->rightchild() = c->leftchild();
				}
			}
		}
		else
		{
			BinaryTreeNode<T> *less = c->leftchild();
			BinaryTreeNode<T> *lp = c;
			while (less->rightchild())
			{
				lp = less;
				less = less->rightchild();
			}
			lp->setRightchild(0);
			if (p == 0)
			{
				if (less != c->leftchild())
					less->setLeftchild(c->leftchild());
				if (less != c->rightchild())
					less->setRightchild(c->rightchild());
				this->root = less;
			}
			else
			{
				if (less != c->leftchild())
					less->setLeftchild(c->leftchild());
				if (less != c->rightchild())
					less->setRightchild(c->rightchild());
				if (c == p->leftchild())
					p->leftchild() = less;
				else
					p->rightchild() = less;
			}
		}
		*this;
		c->setLeftchild(0);
		c->setRightchild(0);
		delete c;
		return true;
	}
	BinaryTreeNode<T> *parent(const T&k)
	{
		//if (subroot == 0)
		//	return 0;
		//BinaryTreeNode<T> *t = 0;
		//if (k == subroot->value())
		//	return subroot;
		//else if (k < subroot->value())
		//	t = search(subroot->leftchild(), k);
		//else
		//	t = search(subroot->rightchild(), k);
		//return t;

		BinaryTreeNode<T> *p, *c;
		c = this->root;
		p = 0;
		while (c)
		{
			if (k == c->value())
				return p;
			p = c;
			if (k < c->value())
				c = c->leftchild();
			else
				c = c->rightchild();
		}
		return p;
	}
	void visit(BinaryTreeNode<T> *&r)
	{
		cout << r->value() << ends;
	}
	void InOrder(BinaryTreeNode<T> *r)
	{
		if (r == 0)
			return;
		InOrder(r->leftchild());
		visit(r);
		InOrder(r->rightchild());
	}
};

int main()
{
	BSTree<int> T;
	int n;
	char c;
	do
	{
		cin >> n;
		c = cin.get();
		T.insert(T.Root(), n);
	} while (c != '\n');
	T.InOrder(T.Root());
	cout << endl;
	cout << "ƽ���������ȣ�" << T.searchlen(T.Root()) << endl;
	cin >> n;
	if (T.Delete(n))
		T.InOrder(T.Root());
	else
		cout << "��" << n << endl;
	return 233;
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
