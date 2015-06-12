#include "MyList.h"

template<class T>
void MyList<T>::double_space() {//数组大小不够的时候将数组大小翻倍的操作。
	T *b;
	int i=0;
	b = new T [2*size];
	for (i=0;i<size;++i) {
		b[i] = a[i];
	}
	size *= 2;
	delete a;
	a = b;
} 

template<class T>
MyList<T>::MyList(int num):size(num) {//创建空间为num的空数组 
	len=0;
	a = new T [size];
}
 
template<class T>
MyList<T>::MyList(int num, const T &item):size(num),len(num) {//将item重复num次填入数组中。
	int i=0;
	a = new T [size];
	for (i=0;i<size;++i) {
		a[i] = item;
	}
}

template<class T>
MyList<T>::MyList(const MyList &l) {//拷贝构造函数，深复制另外一个MyList。
	int i=0;
	size = l.size;
	len = l.size;
	a = new T [size];
	for (i=0;i<size;++i) {
		a[i]=l.a[i];
	}
}

template<class T>
MyList<T>::MyList(T* arr, int num){//以arr的前len个元素构造数组
	int i=0;
	size = num;
	len = num;
	a = new T [size];
	for (i=0;i<size;++i) {
		a[i] = arr[i];
	}
}

template <class T>
void MyList<T>::push(const T &item) {//将item添加在MyList最后。
	if (len==size) {
		double_space();
	}
	a[len]=item;
	++len;
}

template <class T>
T MyList<T>::pop(){//将MyList中最后一个元素删除，并返回这个删除的元素。
	--len;
	return a[len];
}

template <class T>
void MyList<T>::insert(int index, const T &item){//将item插入到place处。
	if (index>=len||index<0) throw rngexp(index);
	int i=0;
	if (len==size) double_space();
	for (i=len;i>index;--i) {
		a[i]=a[i-1];
	}
	a[index] = item;
	++len;
}

template <class T>
void MyList<T>::clean(){//清空数组。
	len = 0;
	delete [] a;
	a = new T [100];
	size = 100;
}

template <class T>
int MyList<T>::get_size() const {//返回MyList中元素的数量。
	return len;
}

template <class T>
void MyList<T>::erase(int start, int end) { //删除MyList中第start到第end位的元素，包括两边。
	int i=0;
	for (i=0;i<=len-start;++i) {
		a[start+i]=a[end+i+1];
	}
	len -= end-start+1;
}

template <class T>
T MyList<T>::get_item(int index){//返回第index个元素
	return a[index];
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end){//返回MyList中第start到第end位的元素，包括两边。
	
	if (start>=len||start<-len) throw rngexp(start);
	
	if (end>=len||end<-len) throw rngexp(end);
	int i=0;
	int s=0,e=0;
	s=(len+start)%len;
	e=(len+end)%len;
	if (s>e) {
		MyList<T> tmp(0);
		return tmp;		
	}
	MyList<T> tmp(e-s+1);
	for (i=0;i<=e-s+1;++i) {
		tmp.push(a[s+i]);
	}
	return tmp;
	
}

template <class T>
int MyList<T>::count(const T &item){//返回MyList中和item相等的元素的个数。
	int i=0,cnt=0;
	for (i=0;i<len;++i) {
		if (item==a[i]) ++cnt;
	}
	return cnt;
}

template <class T>
void MyList<T>::remove(const T &item) {//删除MyList中第一个和item相等的元素。
	int i=0;
	for (i=0;i<len;++i) {
		if (item==a[i]) break;
	}
	erase(i,i);
}

template <class T> 
MyList<T> operator+ (const MyList<T> &l1,const MyList<T> &l2){ //合并两个MyList
	int i=0;
	int len1=0,len2=0;
	len1=l1.get_size();
	len2=l2.get_size();
	MyList<T> sum(len1+len2);
	for (i=0;i<len1;++i) {
		sum.push(l1[i]);
	}
	for (i=0;i<len2;++i) {
		sum.push(l2[i]);
	}
	return sum;	
}

template<class T>
MyList<T> operator+ (const MyList<T> &l1, const T &item){ //同push(T item)，但不修改l1，返回一个新数组 
	MyList<T> tmp(l1);
	tmp.push(item);
	return tmp;
}

template <class T>
MyList<T> &MyList<T>::operator = (const MyList<T> &l){//赋值
	int i=0;
	delete [] a;
	size = l.get_size();
	len = size;
	a = new T [size];
	for (i=0;i<size;++i) {
		a[i]=l[i];
	}
	return *this;
}

template <class T>
MyList<T> &MyList<T>::operator += (const T &item){//同push(T item)
	if (len==size) {
		double_space();
	}
	a[len]=item;
	++len;	
}

template <class T>
MyList<T> &MyList<T>::operator += (const MyList &l){//将一个MyList加入到本个MyList之后。
	int i=0;
	for (i=0;i<l.get_size();++i) {
		push(l[i]);
	}
}

template <class T> 
ostream & operator<<(ostream &os, const MyList<T> &obj){
	int i=0;
	for (i=0;i<obj.get_size();++i) {
		if (i==0) os<<'[';
		if (i<obj.get_size()-1) os<<obj[i]<<','<<' ';
		if (i==obj.get_size()-1) os<<obj[i]<<']';
	}
	return os;	
}

template<class T>
T &	MyList<T>::operator [](int index) const {//未检测下标越界！ 
	if (index>=len||index<0) throw rngexp(index);
	return a[index];
}

template <class T>
void MyList<T>::sort(bool less) {//实现一个快速排序或归并排序，若less=true，按照从小到大排列，否则按从大到小排列
	qsort(0,len-1);
	if (!less) reverse();
}

template <class T>
void MyList<T>::qsort (int low , int high) {
	int mid;
	if (low>=high) return;
	mid = divide(low,high);
	qsort (low,mid-1);
	qsort (mid+1,high);	
}

template <class T>
int MyList<T>::divide (int low , int high){
	int tmp;
	tmp = a[low];
	
	do {
		while (low<high&&a[high]>=tmp) --high;
		if (low<high) {
			a[low]=a[high];
			++low;
		}
		while (low<high&&a[low]<=tmp) ++low;
		if (low<high) {
			a[high]=a[low];
			--high;
		}
	} while (low<high);
	a[low] = tmp;
	return low;	
}

template <class T>
void MyList<T>::reverse(){//将MyList的元素倒过来。
	MyList<T> tmp(*this);
	int i=0;
	for (i=0;i<len;++i) {
		a[i] = tmp[len-i-1];
	}
}






