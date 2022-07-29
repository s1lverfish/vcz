#include <bits/stdc++.h>
using namespace std;
vector<string> program_code = {"COMPILER_FUNCTION","$0",";"};

typedef long long bigint;

map<string, int> func;
map<string, vector<string>> stored_func;
map<string,	bigint> var; 
string in_string;

bigint ret = -1;

int do_func(vector<string>::iterator &it);

bigint convert(string s){
	bigint sign = (s[0] != '-') - (s[0] == '-'), val = 0, mul = 1;
	while(s.size() && s.back() != '-'){
		val += mul*(s.back() - '0');	
		mul *= 10;
		s.pop_back();
	}
	return val;
}

//evaluate function
bigint eval(vector<string>::iterator &it){
	string s = *it;
	if(s[0] == '$'){
		s = string(s.begin()+1, s.end());
		++it;
		return var[s];
	}else if(func[s]){
		do_func(it);
		return ret;
	}else{
		++it;
		return convert(s);
	}
}

void read(vector<string>::iterator &it){
	++it;
	while(*it != ";"){
		string s = *it;
		assert(isalpha(s[0]));
		assert(var.find(s) == var.end());
		cin >> var[s];
		++it;
	}
	++it;
	return;
}


void write(vector<string>::iterator &it){
	++it;
	while(*it != ";") cout << eval(it) << '\n';
	++it;
	return;
}

void add(vector<string>::iterator &it){
	++it;
    bigint sum = 0;
	while(*it != ";") sum += eval(it);
	ret = sum;
	++it;
	return;
}

void eq(vector<string>::iterator &it){
	++it;
	bigint val = 0;


	return;
}

void creo(vector<string>::iterator &it){
	++it;
	string vcur = *it;
	assert(isalpha(vcur[0]));
	assert(var.find(vcur) == var.end());
	++it;
	while(*it != ";") var[vcur] = eval(it);
	++it;
	return;
}

int run(vector<string> &program){
	auto it = program.begin();
	while(it != program.end()){
		if(func[*it]) do_func(it);
		else return 0;
	}
	return 1;
}

void compile_func(vector<string>::iterator &it){
	++it;	

	string comp = "./comp ";
	if(*it == "$0"){
		comp += in_string;
	}else{
		comp += *it;
	}
	char *str = new char[comp.size()];
	for(int i = 0; i < comp.size(); ++i) str[i] = comp[i];
	//cout << str << '\n';
	system(str);

	while(*it != ";") ++it;
	++it;
	return;
}

int do_func(vector<string>::iterator &it){
	if(*it == "R") read(it);	
	else if(*it == "W") write(it);
	else if(*it == "CREO") creo(it);
	else if(*it == "ADD") add(it);
	else if(*it == "EQ") eq(it);
	else if(*it == "COMPILE_FUNC") compile_func(it);
	else run(stored_func[*it]);
	return 1;
}

int main(int args, char** argv){

	if(args > 1) in_string = argv[1];

func["R"] = func["W"] = func["CREO"] = func["ADD"] = func["EQ"] = func["COMPILE_FUNC"] = 1;

#ifdef COMPILE
	run(program_code);
#else
	if(args == 1){
		string s;
		while(1){
			getline(cin, s);
			vector<string> program;
			string tmp;
			for(char c : s){
				if(c == ' '){
					program.push_back(tmp);
					tmp.clear();
				}else tmp += c;
			}
			program.push_back(tmp);

			run(program);
		}
	}else{

		int len = strlen(argv[1]);


		assert(argv[1][len-1] == 'z' && argv[1][len-2] == 'c' && argv[1][len-3] == 'v' && argv[1][len-4] == '.');

		ifstream programfile;
		programfile.open(argv[1]);

		vector<string> program;
		string s;

		while(programfile.is_open() && programfile >> s){
			program.push_back(s);
		}

		run(program);
	}
#endif

	return 0;
}
