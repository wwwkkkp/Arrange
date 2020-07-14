
//17.《C++实现大数加减乘除四则运算（基于STL）》

//也就是字符串的加减乘除，这里只说除法，顺便说一下减法：

见图
1,小数除大数，直接返回0
2,若两数长度相等，判断大小，左操作数小，返回0
3,不是上述情况，我们需要开始计算
4,/首先计算两数长度之差，作为基准
5,/给除数第一次加上长度之差p个零，记为N1；第二次加p-1个零，记为N2；直到不加零，计算后结束
6,我们每次计算将被除数减去N1，差为M1，给减的次数后加p个零，结果为R1，将结果入栈；
7,/M1减去N2，给减的次数后加p-1个零，结果为R2，将结果入栈
···
8,直到N为除数，计算够减的次数
9,最后将R1+R2+···Rn得到最终结果


// 功能函数：判断字符串大小
bool isBig(string& lhs, string rhs)
{
	int lhsLen = lhs.length();
	int rhsLen = rhs.length();

	if (lhsLen > rhsLen)
	{
		return true;
	}
	else if (lhsLen < rhsLen)
	{
		return false;
	}
	else
	{
		if (lhs > rhs)
		{
			return true;
		}
		else if (lhs < rhs)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

// 大数除法
BigInt operator/(const BigInt & lhs, const BigInt & rhs)
{
	string greatNum = lhs.strDigit;
	string lessNum = rhs.strDigit;

	int lhsLen = lhs.strDigit.length();
	int rhsLen = rhs.strDigit.length();

	if (lhsLen < rhsLen) // 除数大，直接返回0
	{
		return string("0");
	}
	else if (lhsLen == rhsLen)
	{
		for (size_t i = lhsLen - 1 , j = rhsLen - 1
			; i >= 0 && j >= 0; --i, --j)
		{
			if (lhs.strDigit[i] >= rhs.strDigit[j])
			{
				continue;
			}
			// 左操作数小，直接返回0
			else if (lhs.strDigit[i] < rhs.strDigit[j])
			{
				return string("0");
			}
		}
	}

	int index = lhsLen - rhsLen; // 得到基准值
	BigInt rhstmp = rhs;
	BigInt lhstmp = lhs;
	stack<BigInt> NumStack; // 存储结果的栈
	for (; index >= 0; index--)
	{
		int k = index;
		while (k > 0)
		{
			rhstmp.strDigit += '0'; // 给除数后添加 0 
			k--;
		}

		// 除数大，返回
		if (isBig(rhstmp.strDigit, lhstmp.strDigit))
		{
			rhstmp.strDigit.clear();
			rhstmp = rhs;
			continue;
		}

		BigInt result("");
		BigInt count(""); // 存储每次够减的次数

		do
		{
			result = lhstmp - rhstmp; /*// 执行大数减法*/
			if (!isBig(result.strDigit, rhstmp.strDigit)) 
			{
				lhstmp.strDigit = result.strDigit; //看看当前减数中有几个被减数
				count = count + BigInt("1");
				break;
			}
			lhstmp.strDigit = result.strDigit;
			count = count + BigInt("1");
			
			// 直到右操作数即除数小，或左操作数为0，全部整除
		} while (isBig(result.strDigit, rhstmp.strDigit) ||
		 strcmp(lhstmp.strDigit.c_str(), "0")); 


		k = index;
		while (k > 0)
		{
			// 给够减的次数后添加 0，得出一轮结果
			count.strDigit = count.strDigit + "0";
			k--;
		}
		// 将结果入栈
		NumStack.push(count);
		
	   // 清空右操作数，进行下次运算
		rhstmp.strDigit.clear();
		rhstmp = rhs;
	}
	if (NumStack.size() == 1)
	{
		return NumStack.top();
	}
	/* 对栈的操作，和大数乘法相同 */
	BigInt res("");
	BigInt reslhs("");
	BigInt resrhs("");
	while (!NumStack.empty())
	{
		if (res.strDigit.length() != 0)
		{
			NumStack.push(res);
		}
		resrhs = NumStack.top();
		NumStack.pop();
		reslhs = NumStack.top();
		NumStack.pop();
		res = reslhs + resrhs;
	}
	return res.strDigit;
}


//减法，自己写的，只写了大数减小数的情况：
int main() {
	
	string s1, s2;
	cin >> s1 >> s2;
	int n1 = s1.size();
	int n2 = s2.size();
	int a = n1 - n2;
	string s(a,'0');
	s2 = s + s2;  //小数前面补0，使两数相等长度
	string s3(n1, '0');
	for (int i = n1 - 1; i >= 0; i--) {
		int b = s1[i] - s2[i];
		if (b < 0) {
			s1[i - 1]--; //需要借位
			b += 10;
		}
		s3[i] = b + '0';
	}
	while (s3[0]<='0'||s3[0]>'9')
		s3.erase(0, 1);
	cout << s3 << endl;
	return 0;
}