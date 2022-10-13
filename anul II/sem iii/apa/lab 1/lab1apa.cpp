
using namespace std;

int fib1it = 0;
int fib2it = 0;
int fib3it = 0;

int fib1(int num){
	int a = 1,b = 1;

	for(int i = 0; i < num; i++){
		b = a + b;
		a = b - a;
		fib1it+=6;
	}

	return b;
}

int fib2(int num){
	if(num < 2){
		fib2it++;
		return 1;
	}
	return fib2(num - 1) + fib2(num - 2);
}

float fib3(int n){
	int i = 1;
	int j = 0;
	int k = 0;
	int h = 1;
	int t;
	while(n  > 0){
		if(n % 2 != 0){
			t = j * h;
			j = i * h + j * k + t;
			i = i * k + t;
			fib3it+= 11;
		}
		t = h * h;
		h = 2 * k * h + t;
		k = k * k + t;
		n = n / 2;
		fib3it += 11;
	}

	return j;
}

int main(){
	fib1(40);
	fib2(40);
	fib3(40);
	cout << fib1it << endl << fib2it << endl << fib3it << endl; 
	return 0;
}
