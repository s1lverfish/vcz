#include <bits/stdc++.h>

using namespace std;

int main(int args, char** argv){
	int len = strlen(argv[1]);


	assert(argv[1][len-1] == 'z' && argv[1][len-2] == 'c' && argv[1][len-3] == 'v' && argv[1][len-4] == '.');

	ifstream programfile;
	programfile.open(argv[1]);

	vector<string> program;
	string s;

	while(programfile.is_open() && programfile >> s){
		program.push_back(s);
	}

	string insert = "vector<string> program_code = {";
	for(string ss : program){
		insert += '\"';
		insert += ss;
		insert += '\"';
		insert += ',';
	}
	insert.pop_back();
	insert += "};";

	ofstream out;
	ifstream vcz;
	out.open("tmp");
	vcz.open("vcz_base.cpp");

	string line;
	getline(vcz, line);
	out << line << '\n';
	getline(vcz, line);
	out << line << '\n';

	out << insert << '\n';
	getline(vcz,line);
	while(getline(vcz, line)){
		out << line << '\n';
	}

	vcz.close();
	out.close();

	system("mv tmp vcz_base.cpp");

	string call = "g++ vcz_base.cpp -o ";
	call += argv[1];
	call.pop_back();
	call.pop_back();
	call.pop_back();
	call.pop_back();
	call += " -DCOMPILE";

	len = call.size();
	char *callstr = new char[len];

	for(int i = 0; i < len; ++i) callstr[i] = call[i];

	system(callstr);

	return 0;
}
