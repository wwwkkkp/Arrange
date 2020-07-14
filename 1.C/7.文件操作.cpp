
//文件操作：fopen fclose fread fwrite fseek ftell fgetc 这些函数都是#include<stdio.h> (也在iostream中)头文件中，和fiostream 中的 open get read write seekg tellg close函数功能一样，注意区别

//打开文件fopen函数
FILE * fopen(const char * path,const char * mode);

path:要打开的文件路径
mode:打开方式

文件使用方式由r,w,a,t,b,+六个字符拼成，各字符的含义是：
	r（read）： 读
	w（write）： 写
	a（append）： 追加 //在文本后面追加信息，而不是覆盖信息
	t（text）： 文本文件，可省略不写
	b（banary）： 二进制文件
	+: 读和写
	

//关闭文件 fclose()函数
int fclose(FILE *stream)
stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了要被关闭的流。
返回值：如果流成功关闭，则该方法返回零。如果失败，则返回 EOF。

//读写文件数据块fread() , fwrite()函数
fread(buffer,size,count,fp); 
fwrite(buffer,size,count,fp);

buffer：是一个指针，对fread来说，它是读入数据的存放地址。对fwrite来说，是要输出数据的地址。  //指向代码对应存储地址
size：要读写的字节数；
count:要进行读写多少个size字节的数据项；
fp:文件型指针。//指向文件的指针

例如：fread(fa,4,5,fp); 其意义是从fp所指的文件中，每次读4个字节(一个实数)送入数组fa中，连续读5次，即读5个实数到fa中。
返回值：fwrite()如果调用成功，返回第三个参数的值，如上面那个函数，成功返回5。
		fread(buf,sizeof(buf),1,fp);    读取成功时：当读取的数据量正好是sizeof(buf)个Byte时，返回值为1(即count)，否则返回值为0(读取数据量小于sizeof(buf))
		fread(buf,1,sizeof(buf),fp);    读取成功返回值为实际读回的数据个数(单位为Byte) //见综合实例
		fread整体还是返回的第三个参数，但是要注意第三个参数等于1的情况

写操作fwrite()后必须关闭流fclose()。

写数据
#include <stdio.h>
#include <stdlib.h>
int main ()
{
  FILE * pFile;
  int buffer[] = {1, 2, 3, 4};
  if((pFile = fopen ("myfile.txt", "wb"))==NULL)
  {
      printf("cant open the file");
      exit(0);
  }
  //可以写多个连续的数据(这里一次写4个)
  fwrite (buffer , sizeof(int), 4, pFile);
  fclose (pFile);
  return 0;
}

读数据
#include <stdio.h>
#include <stdlib.h>
 
int main () {
    FILE * fp;
    int buffer[4];
    if((fp=fopen("myfile.txt","rb"))==NULL)
    {
      printf("cant open the file");
      exit(0);
    }
    if(fread(buffer,sizeof(int),4,fp)!=4)   //可以一次读取
    {
        printf("file read error\n");
        exit(0);
    }
 
    for(int i=0;i<4;i++)
        printf("%d\n",buffer[i]);
    return 0;
}


写结构体
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    int age;
    char name[30];
}people;
 
int main ()
{
    FILE * pFile;
    int i;
    people per[3];
    per[0].age=20;strcpy(per[0].name,"li");  //char数组要用strcpy赋值
    per[1].age=18;strcpy(per[1].name,"wang");
    per[2].age=21;strcpy(per[2].name,"zhang");
 
    if((pFile = fopen ("myfile.txt", "wb"))==NULL)
    {
        printf("cant open the file");
        exit(0);
    }
 
    for(i=0;i<3;i++)
    {
        if(fwrite(&per[i],sizeof(people),1,pFile)!=1) //注意第一个参数是地址
            printf("file write error\n");
    }
    fclose (pFile);
    return 0;
}

读结构体
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    int age;
    char name[30];
}people;
 
int main () {
    FILE * fp;
    people per;
    if((fp=fopen("myfile.txt","rb"))==NULL)
    {
      printf("cant open the file");
      exit(0);
    }
 
    while(fread(&per,sizeof(people),1,fp)==1)   //如果读到数据，就显示；否则退出
    {
        printf("%d %s\n",per.age,per.name);
    }
    return 0;
}

综合实例：
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
	FILE *filp = NULL;
	char fileDir[] = "D:\\test.txt"; 
	char dataPtr[] = "Helloworld";
	printf("sizeof(dataPtr) = %ld\n",sizeof(dataPtr));
	filp = fopen(fileDir,"w+");  /* 可读可写，不存在则创建 */
	int writeCnt = fwrite(dataPtr,sizeof(dataPtr),1,filp);  /* 返回值为1 */
	//int writeCnt = fwrite(dataPtr,1,sizeof(dataPtr),filp);  /* 返回值为11 */
	printf("writeCnt = %d\n",writeCnt);
	fclose(filp);
 
	FILE *fp = NULL;
	fp = fopen(fileDir,"r");
	char buffer[256];
	int readCnt = fread(buffer,sizeof(buffer),1,fp);  /* 返回值为0 */ //因为读到了11个数，是小于buffer的大小的，所以返回0，如果正好是buffer的大小，返回1
	//int readCnt = fread(buffer,1,sizeof(buffer),fp);  /* 返回值为11 */ //返回读到数的大小	
	printf("readCnt = %d\n",readCnt);
	fclose(fp);
	
	printf("%s\n",buffer);
	exit(0);
}

注意：本例中定义了两个FILE变量，一个用于write，一个用于read，write写完后要close掉，然后再打开，然后读。如果直接使用一个FILE变量，会出错！  																			//因为进行一次读写操作之后，文件指针位置已经发生了变化

//文件随机访问fseek()函数
int fseek(FILE * stream, long offset, int whence);
函数说明：fseek()用来移动文件流的读写位置.
返回值：正常返回0，异常返回	-1

参数：

	参数stream 为已打开的文件指针。
	参数offset 是偏移量，该参数表示要从起始点开始要移动的距离，该参数必须是一个long类型的值，可以为正(前移)，可以为负(向后移)，或者为0(保持不动)。
	参数 whence 是模式，该参数确定起始点。根据ANSI标准，在stdio.h头文件中规定了几个表示模式的明示标量(manifest constant)。如下表所示：

模式			 偏移量的起始点
SEEK_SET	 文件开始处
SEEK_CUT	 文件当前位置
SEEK_END	 文件末尾



fseek(fp, 0L, SEEK_SET);       //定位至文件开始处
fseek(fp, 10L, SEEK_SET);      //定位至文件中的第10个字节
fseek(fp, 2L. SEEK_CUR);      //从文件当前位置前移2个字节
fseek(fp, 0L, SEEK_END);       //定位至文件结尾
fseek(fp, -10L, SEEK_END);      //从文件结尾处回退10个字节



//文件随机访问ftell()函数
函数原型：long ftell(FILE * stream);
函数说明：ftell() 函数用来获取文件读写指针的当前位置
参数：stream 为已打开的文件指针
返回值：成功则返回当前的读写位置，失败返回 -1。


			/*

			ftell()函数返回指定流的当前文件指针的位置。在文件末尾移动文件指针后，

			我们可以使用ftell()函数获取文件的总大小。可以使用SEEK_END常量来将文件指针移动文件末尾。

			*/
#include <stdio.h>  
int main() 
{
    FILE *fp;
 
    fp = fopen("myfile.txt", "r");
    fseek(fp, 0L, SEEK_END);
 
    int length = ftell(fp); //返回文件大小
 
    fclose(fp);
    printf("Size of file: %d bytes\n", length);

}

//由文件中读取一个字符fgetc()函数
int fgetc(FILE * stream);
函数说明：fgetc()从参数stream 所指的文件中读取一个字符， 若读到文件尾而无数据时便返回EOF.
返回值：getc()会返回读取到的字符, 若返回EOF 则表示到了文件尾.

#include <stdio.h>
int main()
{
	FILE *fp;
	int c;
	fp = fopen("myfile.txt", "r");
	while((c = fgetc(fp)) != EOF)
	printf("%c", c);
	printf("\n");
	fclose(fp);
}

