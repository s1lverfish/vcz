#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
	ll x; cin >> x;
	string s = "";
	ll minus = 268435456;
	while(minus){
		ll times = x / minus;
		s += (char)(times < 10 ? '0' + times : 'a' + times - 10);
		x -= times*minus;
		minus /= 16;
	}


	reverse(s.begin(), s.end());
	for(int i = 0; i < s.size(); i+=2){
		swap(s[i], s[i+1]);
	}

	cout << s << '\n';

}
