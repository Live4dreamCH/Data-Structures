﻿// 数据结构实验4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

template <class T>
class BinaryTreeNode	//已完成
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
	BinaryTreeNode<T>* leftchild()const
	{
		return left;
	}
	BinaryTreeNode<T>* rightchild()const
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
	void setValue(const T& val)	//离家最近的路（当时舍友在放歌，觉得好听就随手记下来了233）
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
class BinaryTree	//未实现
{
protected:
	BinaryTreeNode<T>* root;
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
	T &visit()
	{
		return root->data;
	}
	BinaryTreeNode<T>*& Root() { return root; }
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
		if (root == 0)
			return;
		visit();
		PreOrder(root->leftchild());
		PreOrder(root->rightchild());
	}
	void InOrder(BinaryTreeNode<T> *r)
	{
		if (root == 0)
			return 0;
		InOrder(root->leftchild());
		visit();
		InOrder(root->rightchild());
	}
	void PostOrder(BinaryTreeNode<T> *r)
	{
		if (root == 0)
			return 0;
		PostOrder(root->leftchild());
		PostOrder(root->rightchild());
		visit();
	}
	//void LevelOrder(BinaryTreeNode<T> *r)
	//{
	//}
};

int main()
{
	return 233;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
