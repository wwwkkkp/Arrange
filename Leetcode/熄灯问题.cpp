
#include <stdio.h>

#include <iostream>


#include <string>

#include<memory>
#include<cstring>


using namespace std;

char  orilinghts[5];
char lights[5];
char result[5];
int  getbit(char c, int i) {

	return (c >> i) & 1;

}
void setbit(char c, int i, int v) {
	if (v) {
		c |= (1 << i);
	}
	else {
		c &= ~(1 << i);
	}
}

void Flipbit(char &c, int i ){
	c ^= (1 << i);
}

void outputresult(int t, char result[]) {
	cout << "pizzzle #" << t << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << getbit(result[i], j);
			if (j < 5)
				cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		for (int i = 0; i < 5; i++) { //输入
			for (int j = 0; j < 6; j++) {
				int s;
				cin >> s;
				setbit(orilinghts[i], j, s);//对应的位是0还是1
			}
		}
			for (int n = 0; n < 64; n++) {
				int switchs = n;
				memcpy(lights, orilinghts, sizeof(orilinghts));
				for (int i = 0; i < 5; ++i) {
					result[i] = switchs;
					for (int j = 0; j < 6; j++) {
						if (getbit(switchs, j)) {  //按键选择，枚举
							if (j > 0)
								Flipbit(lights[i], j - 1);
							Flipbit(lights[i], j);
							if (j < 5)
								Flipbit(lights[i], j + 1);
						}
					}
					if (i < 5)
						lights[i + 1] ^= switchs; //按键下一行的改变
					switchs = lights[i];//这一行的剩余就变成下一行的按键
				}
				if (lights[4] == 0) {
					outputresult(t, result);
					break;
				}
		    }
		
	}
}
