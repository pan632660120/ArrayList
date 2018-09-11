#include<iostream>
#include<math.h>
#include<string.h>
#include<map>
using namespace std;
template <class T>
class Vector{
	public:
		Vector(int sz = INITIAL_CAPACITY){
			capacity = INITIAL_CAPACITY;
			count = 0;
			array = new T[capacity];
		} 
		~Vector(){
			delete[] array;
		}
		int size() const{
			return count;
		} 
		void clear()
		{
			count = 0;
		}
		bool isEmpty() const{
			return count == 0;
		}
		T get(int index) const
		{
			if(index < 0 || index >= count)
				cerr << "get:index out of range" << endl;
			return array[index];
		}
		void set(int index,T x)
		{
			if(index < 0 || index >= count)
				cerr << "set:index out of range" << endl;
			array[index] = x;
		}
		void insert(int index , T x){
			if(count == capacity)
				resize(2*capacity);
			if(index < 0 || index > count)
				cerr << "insert:index out of range" << endl;
			for(int i = count; i > index; i--)
				array[i] = array[i-1];
			array[index] = x;
			count++;
		}
		void remove(int index){
			if(index < 0 || index >= count)
				cerr << "get:index out of range" << endl;
			for(int i = index; i < count - 1; i++)
				array[i] = array[i+1];
			count--;
		}
		void add(T x){
			insert(count,x);
		}
		T& operator[](int index){
			if(index < 0 || index >= count)
				cerr << "Vector index out of range" << endl;
			return array[index];
		}
		Vector(const Vector<T>& src){
			deepCopy(src);
		}
		Vector<T>& operator=(const Vector<T>& src){
			if(this != &src){
				delete[] array;
				deepCopy(src);
			}
			return *this;
		}
		/*
			**************�����ǡ��������ݽṹ���㷨��************** 
		*/ 
		T deleteMin()
		{//2.2.3.1ɾ��˳�������СԪ�أ���ɾ��Ԫ�������һ��Ԫ����� 
			if(count == 0){
				cerr << "˳����ѿգ�" << endl;
				exit(1);
			}
			T min = array[0];
			int flag = 0;;
			for(int i = 1; i < count; i++)
				if(array[i] < min){
					min = array[i];
					flag = i;
				}
			array[flag] = array[count-1];
			return min;		
		}
		void reverse()
		{//2.2.3.2��˳�������Ԫ�����á�
			T temp;
			for(int i =0,j=count-1; i < j; i++,j--){
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
		void deleteX(T x)
		{//2.2.3.3ɾ�����Ա�������ֵΪx��Ԫ�ء�
			if(count == 0){
				cerr << "˳����ѿգ�" << endl;
				exit(1);
			} 
			/*int total = 0;
			for(int i = 0,j =0; (i < count) && (j < count); i++,j++){
				if(array[i] == x){
					while(array[j] == x && j < count){
						j++;
						total++;
					}
				}
				if(i != j)
					array[i] = array[j];
			}
			count -= total;*/
			int k = 0;
			for(int i = 0; i < count; i++){
				if(array[i] != x){
					array[k] = array[i];
					k++;
				}
			}
			count = k;
		}
		void deleteBetween1(int s , int t)
		{//2.2.3.4������˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨����s��t��Ҫ��s<t��������Ԫ�ء�
			if(count == 0){
				cerr << "˳����ѿգ�" << endl;
				exit(1);
			}
			if(s >= t){
				cerr << "��������" << endl;
				exit(1);
			}
			int total = 0;
			for(int i = 0,j =0; (i < count) && (j < count); i++,j++){
				if(array[j] >= s && array[j] <= t){
					while(array[j] <= t && j < count){
						j++;
						total++;
					}
				}
				if(i != j){
					array[i] = array[j];
				}
			}
			count -= total;
		}
		void deleteBetween2(int s , int t)
		{//2.2.3.5��˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨����s��t��Ҫ��s<t��������Ԫ�ء�
			if(count == 0){
				cerr << "˳����ѿգ�" << endl;
				exit(1);
			}
			if(s >= t){
				cerr << "��������" << endl;
				exit(1);
			}
			int total = 0;
			for(int i = 0,j =0; (i < count) && (j < count); i++,j++){
				while(array[j] >= s && array[j] <= t && j < count){
					j++;
					total++;
				}
				if(i != j){
					array[i] = array[j];
				}
			}
			count -= total;
		}
		void deleteRepet()
		{//2.2.3.6������˳�����ɾ��������ֵ�ظ���Ԫ�ء� 
			if(count == 0){
				cerr << "˳����ѿգ�" << endl;
				exit(1);
			}
			int total = 0;
			for(int i = 0,j = 1; j < count; j++){
				while(array[i] == array[j]){
					j++;
					total++;
				}
				i++;
				array[i] = array[j];
			}
			count -= total;
		}
		static Vector<T>& mergeList(Vector<T>& a , Vector<T>& b)
		{//2.2.3.7�ϲ���������˳����������±�
			int n = a.size() + b.size();
			Vector<T>* newList = new Vector<T>(n);
			int i = 0 , j = 0;
			bool isA = false;
			while(i < a.size() || j < b.size()){
				if(i < a.size() && j < b.size()){
					isA = (a[i] <= b[j])  ? true : false;
				}else if(i >= a.size() && j < b.size()){
					isA = false;
				}else isA = true;
				if(isA){
					newList->add(a[i]);
					i++;
				}else{
					newList->add(b[j]);
					j++;
				}
			}
			return *newList;
		}
		void reserveMN(int m , int n)
		{//2.2.3.8��������m,n���� 
			int k = m+n;
			int temp;
			for(int i = 0 , j = m-1; i < j; i++,j--)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			for(int i = m , j = k-1; i < j; i++,j--)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			for(int i = 0 , j = k-1; i < j; i++,j--)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
		void findX(int x)
		{//2.2.3.9���Ա���Ԫ�ص��������Ұ�˳�򴢴棬Ѱ����ֵΪx��Ԫ�أ����ҵ���������Ԫ��λ���໥�������Ҳ������������в�ʹ����Ԫ���ӵ������� 
			int left = 0 , right = count-1 , mid; 
			while(left <= right){
				mid = (left + right) / 2;
				if(array[mid] == x){
					break;
				}else if(array[mid] > x){
					right = mid - 1;
				}else left = mid + 1;
			}
			int temp;
			if(array[mid] == x){
				if(mid+1 < count){
					temp = array[mid];
					array[mid] = array[mid+1];
					array[mid+1] = temp;	
				}
			}/*else if(mid < count-1){
					insert(mid,x);
			}else insert(mid+1,x);*/
			else if(left > right){
					int i = count - 1;
					if(count == capacity-1)
						resize(2*capacity);
					for(; i > right; i--)
						array[i+1] = array[i];
					array[i+1] = x;
					count++;
			}		
		}
		template<class X>
		static void leftMove(X& R , int p)
		{//2.2.3.10������R��Ԫ��ѭ������p(0<p<n)��λ�á� 
			int n = sizeof(R)/sizeof(R[0]);
			int q = n - p;
			for(int i = 0,j = p-1; i < j; i++,j--){
				R[i] = R[i] ^ R[j];
				R[j] = R[i] ^ R[j];
				R[i] = R[i] ^ R[j];
			}
			for(int i = p,j = n-1; i < j; i++,j--){
				R[i] = R[i] ^ R[j];
				R[j] = R[i] ^ R[j];
				R[i] = R[i] ^ R[j];
			}
			for(int i = 0,j = n-1; i < j; i++,j--){
				R[i] = R[i] ^ R[j];
				R[j] = R[i] ^ R[j];
				R[i] = R[i] ^ R[j];
			}
		}
		template<class E>
		static int findMidNum(E& a , E& b)
		{//2.2.3.11�������ȳ��������λ���� 
			int n = end(a)-begin(a);
			int mid;
			int p = 0 , q = 0;		
			for(int i = 0; i < n; i++){
				if(p < n && q < n){
					if(a[p] <= b[q]){
						mid = a[p];
						p++;
					}else{
						mid = b[q];
						q++;
					}
				}else if(p < n){
					mid = a[p];
					p++;
				}else{
					mid = b[q];
					p++;
				}
			}
			return mid;
		}
		template<class X>
		static int findMainNum(X& a)
		{//2.2.3.12�ҳ�a�е���Ԫ�ء�
			const int n = end(a)-begin(a);
			int count[n];
			memset(count,0,sizeof(count));
			for(int i = 0; i < n; i++)
				count[a[i]]++;
			int max = 0;
			for(int i = 1; i < n; i++){
				if(count[i] > count[max]){
					max = i;
				}
			}
			if(count[max] > n/2)
				return max;
			else return -1;
		}
		//--------------- �ָ��� --------------- 
		private:
			static const int INITIAL_CAPACITY = 10;
			T* array;
			int capacity;
			int count;
			void deepCopy(const Vector<T>& src){
				capacity = src.count+INITIAL_CAPACITY;
				this->array = new T[capacity];
				for(int i = 0; i < src.count; i++)
					array[i] = src.array[i];
				count = src.count;
			}
			void resize(int newsize){
				T* old = array;
				array = new T[newsize];
				for(int i = 0; i < count; i++)
					array[i] = old[i];
				delete[] old;
			}
};
