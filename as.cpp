#include<iostream>
#include<fstream>
using namespace std;
#define LS line[start]
//the difficulty is to deal with the .org psedo op
int64_t hex2dec(string hex){
    	int64_t result = 0;		//res = res << 4 + hex[i]
    	int64_t adder  = 0;
    	for(char c: hex){
		result = result << 4;
		if(c == ' ') 			adder = 0;
		else if(c >= '0' && c <= '9') 	adder = c - '0';
		else 				adder = c - 'a' + 10;
		result += adder;
    	}
    	return result;
}

string getAddress(string line){
	string s = "";
	for(char c: line){
		if(c == ':') break;
		else s += c;
	}
	return s;
}

bool check(string s){
	/*three cases:
		1. label 2.  ... 3.  empty line
	*/
	int len = s.length();
	if(s[len -1] == ':' || s[len - 1] == '.' || len == 0) return false;
	return true;
}

int main(int argc, char ** argv)
{
	ifstream in;
	in.open("asm.txt");
	string line;
	//start at line 7 
	int n = 7;
	while(n--)getline(in,line);
	int64_t oldAddr = -4;
	int64_t newAddr = 0;	//good: the difference is 4(no .org)
	while(getline(in,line))
	{
		if(!check(line)) continue;
		//when meet a .org psedo op, fill the space with nop
		newAddr = hex2dec(getAddress(line));
		int64_t diff = newAddr - oldAddr;
		if(diff > 4){	//need to insert nop first
			for (int i = diff >> 2; i > 0 ; i--)
				cout<<"00000013"<<endl;			
		}
		else{	//a normal inst line
			int start = 0;
			while(line[start] != ':') start ++;
			while(!isdigit(LS) && !(LS >= 'a' && LS <= 'f')) start ++;
			for(int i = start; i < start + 8; i++)
				cout<<line[i];
			cout<<endl;
		}
		//if(diff == 4) 
		oldAddr = newAddr;
	}
}
