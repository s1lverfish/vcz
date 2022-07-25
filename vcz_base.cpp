#include <bits/stdc++.h>
using namespace std;
vector<string> program_code = {"R","x","y",";","W","ADD","$x","$y",";",";"};

typedef long long bigint;

map<string, function<void(vector<string>::iterator&)>> func;
map<string,	bigint> var; 


bigint ret = -1;

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
	while(*it != ";"){
		string s = *it;
		if(s[0] == '$'){
			s = string(s.begin()+1, s.end());
			cout << var[s] << '\n';
		}else if(func.find(s) != func.end()){
			func[s](it);
			it--;
			cout << ret << '\n';
		}else{
			cout << s << '\n';
		}
		++it;
	}
	++it;
	return;
}

bigint convert(string s){
	bigint sign = (s[0] != '-') - (s[0] == '-'), val = 0, mul = 1;
	while(s.size() && s.back() != '-'){
		val += mul*(s.back() - '0');	
		mul *= 10;
		s.pop_back();
	}
	return val;
}

void add(vector<string>::iterator &it){
	++it;
    bigint sum = 0;
	while(*it != ";"){
		string s = *it;

		if(s[0] == '$'){
			s = string(s.begin()+1, s.end());
			sum += var[s];
		}else if(func.find(s) != func.end()){
			func[s](it);
			it--;
			sum += ret;
		}else{
			sum += convert(s);
		}
		++it;
	}
	ret = sum;
	++it;
	return;
}

void creo(vector<string>::iterator &it){
	++it;
	string vcur = *it;
	assert(isalpha(vcur[0]));
	assert(var.find(vcur) == var.end());
	++it;
	while(*it != ";"){
		string s = *it;
		if(s[0] == '$'){
			s = string(s.begin()+1, s.end());
			var[vcur] = var[s];
		}else if(func.find(s) != func.end()){
			func[s](it);
			it--;
			var[vcur] = ret;
		}else{
			var[vcur] = convert(s);
		}
		++it;
	}
	++it;
	return;
}

int run(vector<string> &program){
	auto it = program.begin();
	while(it != program.end()){
		if(func.find(*it) == func.end()) return 0;
		func[*it](it);
	}
	return 1;
}

int main(int args, char** argv){

	func["R"] = read;
	func["W"] = write;
	func["CREO"] = creo;
	func["ADD"] = add;

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
