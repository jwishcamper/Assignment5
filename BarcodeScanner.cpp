#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
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
int main(){
	
	//testing area
	
	
	
	HashBST b;
	ifstream upcFile;
	clock_t timeStamp;
	double duration;
	BinarySearchTree<upcCode> tree;
	string userInput;
	cout<<"Enter file name: ";
	cin>>userInput;
	upcFile.open(userInput);
	if(!upcFile){
		cout<<"Unable to find "<<userInput<<endl;
		exit(0); }
		
	//BST initialize
	string x,y;
	getline(upcFile,x); //get rid of the first description line
	timeStamp=clock();
	while(getline(upcFile,x)){
		istringstream ss(x);
		getline(ss,x,',');
		getline(ss,y);
		upcCode temp;
		temp.upc=x;
		temp.desc=y;
		tree.insert(temp);
	}
	upcFile.close();
	duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
	cout<<"BST initialize time: "<<fixed<<duration<<"s"<<endl;
	
	//Array initialize
	upcFile.open(userInput);
	int numLines=-1;//accounting for first description line
	timeStamp=clock();
	while(getline(upcFile,x))
		numLines++;
	upcFile.close();
	upcFile.open(userInput);
	upcCode *fullList = new upcCode[numLines];
	getline(upcFile,x); //description line
	for(int i =0;i<numLines;i++){
		getline(upcFile,x);
		istringstream ss(x);
		getline(ss,x,',');
		getline(ss,y);
		upcCode temp;
		temp.upc=x;
		temp.desc=y;
		fullList[i]=temp;
	}
	upcFile.close();
	duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
	cout<<"Array initialize time: "<<fixed<<duration<<"s"<<endl;
		
	//Hash initialize
	upcFile.open(userInput);
	getline(upcFile,x); //get rid of first line in file
	timeStamp=clock();
	while(getline(upcFile,x)){
		istringstream ss(x);
		getline(ss,x,',');
		getline(ss,y);
		upcCode temp;
		temp.upc=x;
		temp.desc=y;
		b.insert(temp);
	}
	upcFile.close();
	duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
	cout<<"Hash initialize time: "<<fixed<<duration<<"s"<<endl;
		
	//b.printQTY();
		
	while(1){
		cout<<"Enter a UPC code(q to exit): ";
		cin>>userInput;
		if(userInput=="q"){
			exit(0);
		}
		
		//BST search
		upcCode forSearch,foundUPC;
		forSearch.upc = userInput;
		forSearch.desc="No item found.";
		timeStamp=clock();
		foundUPC = tree.search(forSearch);
		duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
		cout<<foundUPC;
		cout<<"BST time: "<<fixed<<duration<<"s"<<endl;
		
		//Array search
		timeStamp=clock();
		for(int i =0;i<numLines;i++){
			if(fullList[i].upc==userInput){
				duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
				cout<<"Array time: "<<fixed<<duration<<"s"<<endl;
				break;
			}
		}
		
		//Hash search
		forSearch.upc = userInput;
		forSearch.desc="No item found.";
		timeStamp=clock();
		foundUPC = b.search(forSearch);
		duration=(clock()-timeStamp)/(double) CLOCKS_PER_SEC;
		cout<<"Hash time: "<<fixed<<duration<<"s"<<endl;
	}	
	
	
	
	
	
}