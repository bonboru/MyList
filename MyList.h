#ifndef ML
#define ML
#include<iostream>
using namespace std;

template<class T>
class MyList{
	
	template<class U> friend MyList<U> operator + (const MyList<U> &l1, const MyList<U> &l2); //合并两个MyList
	template<class U> friend MyList<U> operator + (const MyList<U> &l1, const U &item); //同push(T item)，但不修改l1，返回一个新数组
	template<class U> friend ostream & operator<<(ostream &os, const MyList<U> &obj);

private:
	T *a;
	int size;
	int len;
	void double_space();//数组大小不够的时候将数组大小翻倍的操作。
	void qsort (int low , int high);
	int divide (int low , int high);
public:
	MyList(){
		size = 1000;
		len = 0;
		a = new T [size];
	}
	MyList(int num);//创建空间为num的空数组 
	MyList(int num, const T &item);//将item重复num次填入数组中。
	MyList(const MyList &l);//深复制另外一个MyList。
	MyList(T* arr, int num);//以arr的前len个元素构造数组
	void push(const T &item) ;//将item添加在MyList最后。
	T pop();//将MyList中最后一个元素删除，并返回这个删除的元素。
	void insert(int index, const T &item);//将item插入到place处。
	void clean();//清空数组。
	int get_size() const;//返回MyList中元素的数量。
	void erase(int start, int end); //删除MyList中第start到第end位的元素，包括两边。
	T get_item(int index);//返回第index个元素
	MyList get_item(int start, int end);//返回MyList中第start到第end位的元素，包括两边。
	int count(const T &item);//返回MyList中和item相等的元素的个数。
	void remove(const T &item);//删除MyList中第一个和item相等的元素。
	
	MyList &operator = (const MyList &l);//赋值
	MyList &operator += (const T &item);//同push(T item)
	MyList &operator += (const MyList &l);//将一个MyList加入到本个MyList之后。
	T &operator [](int index) const;//返回第index个元素。
	void sort(bool less=true);//实现一个快速排序或归并排序，若less=true，按照从小到大排列，否则按从大到小排列
	void reverse();//将MyList的元素倒过来。
};

class rngexp {
	public:
		int index;
		const char *message;
		rngexp(int num) : index(num),message("out of range index: ") {};

};
#endif




