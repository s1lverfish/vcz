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

	string insert = "vector<string> program_code = {\"W\", \"1444\", \";\"};";
	cout << insert << endl;

	ofstream vcz_base_stream;
	vcz_base_stream.open("vcz_base.cpp");
	vcz_base_stream << insert;
	vcz_base_stream.close();


//	system("g++ vcz_base.cpp -o vcz -DCOMPILE"); 

	return 0;
}
