

//字符串处理函数：strlen() strcpy()  strncpy() strcat() strncat() strcmp() strncmp() strchr() strrchr() strstr() strdup() strspn() strpbrk() strtok() memset() memcpy() memmove() memcmp()

strlen():计算字符串长度
size_t My_Strlen(const char *s)
{
	const char *sc;
	sc = s;
	while(*sc != '\0')
	{
		sc++;
	}
	return sc - s;
}

strcpy()：字符串赋值
char *My_Strcpy(char *dest,const char *src)
{
	char *tmp = dest;
	while(*dest++ = *src++){}
	return tmp;
}

strncpy():前n个数的赋值
char *My_Strncpy(char *dest,const char *src,size_t n)
{
	char *tmp = dest;
	while( n-- && (*dest++ = *src++)){}
	return tmp;
}

strcat():拼接函数，dest后接上src
char *My_Strcat(char *dest,const char *src)
{
	char *tmp = dest;
	while(*dest != '\0')
	{
		dest++;
	}
	while(*dest++ = *src++){}
	return tmp;
}

strncat():拼接函数，dest接上src的前n个数
char *My_Strncat(char *dest,const char *src,size_t n)
{
	char *tmp = dest;
	while(*dest != '\0')
	{
		dest++;
	}
	while(n-- && (*dest++ = *src++)){}
	return tmp;
}

strcmp():比较大小函数
int My_Strcmp(const char *dest,const char *src)
{
	int tmp = 0;
	while(!(tmp = *dest - *src) && *dest && *src)
	{
		dest++;
		src++;
	}
	if(tmp > 0){return 1;}
	else if(tmp < 0){return -1;}
	else{return 0;}
}

strncmp():比较前n个数的大小
int My_Strncmp(const char *dest,const char *src,size_t n)
{
	int tmp = 0;
	while(n-- && !(tmp = *dest - *src) && *dest && *src)
	{
		dest++;
		src++;
	}
	if(tmp > 0){return 1;}
	else if(tmp < 0){return -1;}
	else{return 0;}
}

strchr():查找字符串s中首次出现字符c的位置,正向查找
char *My_Strchr(const char *src,int c)
{
	while(*src != c)
	{
		if(*src == '\0')
		{
			return NULL;
		}
		src++;
	}
	return (char*)src;
}

strrchr():查找字符串s中首次出现字符c的位置，反向查找
char *My_Strrchr(const char *src,int c)
{
	const char *tmp = src; //const char* 不能改值，但是不能说值不变，地址变了，值也变了
	while(*src != '\0')
	{
		src++;
	}
	while(*src != c)
	{
		if(src ==tmp)
		{
			return NULL;
		}
		src--;
	}
	return (char*)src;
}

strstr()：检查str2是否是str1的子串，如果是，返回该子串在str1的首地址，否则返回NULL
char *My_Strstr(const char *str1,const char *str2)
{
	const char *pstr1 = str1;
	const char *pstr2 = str2;
	if(strlen(str2) == 0){return NULL;}
	if(strlen(str1) < strlen(str2)) {return NULL;}
	while(*pstr1)
	{
		const char *tmp = pstr1;
		while(*tmp == *pstr2 && *tmp != '\0')
		{
			tmp++;
			pstr2++;
		}
		if(*pstr2 == '\0')
		{
			return (char *)pstr1;
		}
		pstr1++;
	}
	return NULL;
}

strdup()：复制函数，但是这个函数不是c语言中的标准函数，不同于strcpy，因为strdup中申请了空间，所以要记得释放空间，
char *My_Strdup(const char *str)
{
	if(str == NULL){ return NULL;}	
	const char *tmp = str;
	int len  =  0;
	while (*tmp)
	{
		len++;
		tmp++;
	}
	char *newstr = (char *)malloc(sizeof(char) * (len + 1));
	char *newtmp = newstr;
	assert(newstr != NULL);
	while (*newstr++ = *str++){}
	return newtmp;
}

strspn():检查str1和str2前多少个数是相等的，或者说 返回 str1 中第一个不在字符串 str2 中出现的字符下标。
size_t My_Strspn(const char *str1, const char *str2)
{
	const char *pstr1 = str1;
	const char *pstr2 = str2;
	int count = 0;
	while (*pstr1)
	{
		if (*pstr2 != *pstr1 && *pstr2 != '\0')
		{
			break;

		}
		pstr1++;
		pstr2++;
		count++;
	}
	return count;
}

strbrk():返回str2第一个字符首次出现在str1中的位置
const char *My_Strpbrk(const char *str1, const char *str2)
{
	const char *pstr1 = str1;
	const char *pstr2 = str2;
	while(*pstr1)
	{
		if(*pstr2 == *pstr1 && *pstr2 != '\0')
		{
			return (char *)pstr1;
		}
		pstr1++;
	}
	return NULL;
}

strtok_s(char *p,const char *s,char **context):分割字符串p,以s为标准，分割完后的字符存在context;

char str[80] = "This is - www.runoob.com - website";
const char s[2] = "-";
char *token;
char *t;
/* 获取第一个子字符串 */
token = strtok_s(str, s,&t);

/* 继续获取其他的子字符串 */
while (token != NULL) {
	printf("%s\n", token);

	token = strtok_s(NULL, s, &t);
}
输出：
This is
 www.runoob.com
 website
 


memset():赋值函数 
char* memset(char* p,int a;sizeof(p));
上面这个函数要注意：a是一个int型的数，所以对char赋值的时候，可以使'a'(ascii码转换),不能是"ab",也不能是指针
a的大小应该是一个字节为单位的，所以p的赋值也是以字节为单位，
int a[3];
memset(a,1,sizeof(a));//a[0]=a[1]=a[2]=0x01010101; memset是以字节为单位赋值的；正确做法：memset(a,0x11,sizeof(a));

memcpy():复制前n个字符
void *My_memcpy(void *str1, const void *str2, size_t n)
{
	char *pstr1 = (char *)str1;
	const char *pstr2 = (char *)str2;
	while(*pstr2 != '\0' && n--)
	{
		*pstr1++ = *pstr2++;
	}
	return (char *)str1;
}

memmove()：也是复制函数，区别在于这个更安全，如果dest和src有位置重叠，就用这个函数，
void *My_memmove(void *dest, const void *src, size_t n)
{
	if(dest <= src) //dest的位置在src前面，就正向赋值
	{
		char *pdest = (char *)dest;
		const char *psrc = (char *)src;
		while(*psrc != '\0' && n--)
		{
			*pdest++ = *psrc++;
		}
	}
	else //dest的位置在sr后面，就反向赋值，画图就明白了
	{
		char *pdest = (char *)dest + n;
		const char *psrc = (char *)src + n;
		while(psrc > src && n--)
		{
			*pdest-- = *psrc--;
		}
	}
	return (char *)dest;
}


memcmp():比较前n个数的大小
int My_memcmp(const void *str1, const void *str2, size_t n)
{
const char *pstr1 = (const char *)str1;
const char *pstr2 = (const char *)str2;
int result = 0;
while(n)
{
	if((result = (*pstr1 - *pstr2)) != 0)
	{
		break;
	}
	pstr1++;
	pstr2++;
	n--;
}
if(result > 0) {result = 1;}
if(result < 0) {result = -1;}
return result;
}




