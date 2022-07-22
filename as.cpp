#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char ** argv)
{
	ifstream in;
	in.open("asm.txt");
	string line;
	//start at line 7. Observing the output file asm.txt and you will know where 7 comes from
	int n = 7;
	while(n--)getline(in,line);
  
	while(getline(in,line))
	{
    if(line.length() == 0) continue;                //skip empty lines
    if(line[line.length() - 1] == ':') continue;    //label

		for(int i = 6; i < 14; i++)
			cout<<line[i];
		cout<<endl;
	}
}
