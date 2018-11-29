#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

struct upcCode{
	string upc,desc;
};
bool operator>(const upcCode &first, const upcCode &second){
	return first.upc>second.upc;
}
bool operator<(const upcCode &first, const upcCode &second){
	return first.upc<second.upc;
}
ostream& operator<<(ostream& os, const upcCode u){
	os<<"UPC Code: "<<u.upc<<endl<<u.desc<<endl;
}
class HashBST {
		BinarySearchTree<upcCode> tree[1000];
		int hashFunction(upcCode& key){
			string s = key.upc;
			int sum=0;
			for(int i =0; i<s.length();i++)
				sum+=(s[i]*(37^i));
			return (sum%1000);
		}

	public:
		HashBST() {		}
		void insert(upcCode& item){
			int location = hashFunction(item);
			tree[location].insert(item);
		}
		upcCode search(upcCode& item){
			int location = hashFunction(item);
			return tree[location].search(item);
		}
		void printQTY(){ //used this to check how many elements were in each BST, turns out the hash function I used is pretty good - each index was at 1000-1100 elements!
			for(int i=0;i<1000;i++)
				cout<<"Nodes at index"<<i<<": "<<tree[i].countNodes()<<endl;
		}	
		~HashBST(){		}
};