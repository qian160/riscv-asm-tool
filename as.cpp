#include<iostream>
#include<fstream>
#include<regex>
using namespace std;

regex addr("[0-9a-f]{1,}");
regex inst("\\s[0-9a-f]{8}\\s");

int64_t hex2dec(string hex)
{
	int64_t res;
	sscanf(hex.c_str(), "%lx", &res);
	return res;
}

string getAddress(string line)
{
	smatch m;
	regex_search(line, m, addr, regex_constants::match_default);
	return m.str();
}

int main(int argc, char ** argv)
{
	ifstream in;
	in.open("asm.txt");
	if(in.fail()){
		cout << "file asm.txt open failed!\n";
		exit(1);
	}
	string line;
	int n = 7;
	while(n--)getline(in,line);				//start at line 7
	int64_t oldAddr = -4;
	int64_t newAddr = 0;					//good when the difference is 4
	while(getline(in,line))
	{
		smatch m;
		regex_search(line, m, inst, regex_constants::match_default);
		if(m.empty())continue;
		newAddr = hex2dec(getAddress(line));
		int64_t diff = newAddr - oldAddr;
		if(diff > 4)
		{						//need to insert nop first
			for (int64_t i = diff >> 2 ; i > 1 ; i--)
				cout<<"00000013"<<endl;			
		}
		cout << m.str().substr(1, 8) << endl;		//the 1st char is \t or ' '
		oldAddr = newAddr;
	}
	in.close();
}
