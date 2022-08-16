#include<iostream>
#include<fstream>
#include<regex>
using namespace std;
int64_t hex2dec(string & hex)
{
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

string getAddress(string & line)
{
	string s = "";
	for(char c: line){
		if(c == ':') break;
		s += c;
	}
	return s;
}

bool check(string & s)
{
	/*	four bad cases:	1. label 2.  ... 3.  empty line 4. unimp	*/
	int len = s.length();
	if(len == 0 || s[len -1] == ':' || s[len - 1] == '.' || s.substr(len - 5) == "unimp") return false;
	return true;
}

int main(int argc, char ** argv)
{
	ifstream in;
	in.open("asm.txt");
	if(in.fail()){
		cout << "open file asm.txt failed!\n";
		exit(1);
	}
	string line;
	int n = 7;
	while(n--)getline(in,line);		//start at line 7
	int64_t oldAddr = -4;
	int64_t newAddr = 0;			//good: the difference is 4(no .org)
	while(getline(in,line))
	{
		if(!check(line))continue;
		newAddr = hex2dec(getAddress(line));
		int64_t diff = newAddr - oldAddr;
		if(diff > 4)
		{				//need to insert nop first
			for (int64_t i = diff >> 2 ; i > 1 ; i--)
				cout<<"00000013"<<endl;			
		}
		regex inst("[0-9a-f]{8}");
		smatch m;
		auto ret = regex_search(line, m, inst, regex_constants::match_default);
		for(auto &a : m)
			cout<<a;
		cout<<endl;
		oldAddr = newAddr;
	}
	in.close();
}
