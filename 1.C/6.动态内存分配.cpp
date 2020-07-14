//动态内存分配

//malloc
void *malloc(int num); 
在堆区分配一块大小为num的内存空间（在空间中是连续的），用来存放数据。这块内存空间在函数执行完成后不会被初始化，它们的值是未知的。

返回值：如果分配成功则返回指向被分配内存的指针(此存储区中的初始值不确定，为随机值)，否则返回空指针NULL。当内存不再使用时，应使用free()函数将内存块释放。函数返回的指针一定要适当对齐，使其可以用于任何数据对象。

int *p = (int *)malloc(4*sizeof(int));
assert(p != NULL); //检查是否分配成功

//free
void free( void *memblock );  参数memblock是需要释放的内存块
作用：释放malloc(或calloc、realloc)函数给指针变量分配的内存空间的函数

对于free(p)这句语句，如果p是NULL指针，那么free对p无论操作多少次都不会出问题。如果p不是NULL 指针，那么free 对p连续操作两次就会导致程序运行错误。
注意：使用后该指针变量一定要重新指向NULL，防止野指针出现，有效规避误操作。

使用free()函数时会产生程序崩溃的几种状况：
	越界
	修改了指针的方向
	重复释放已释放的内存
	释放非动态分配的内存


 越界崩溃
int main()
{
    int *p = (int *)malloc(10*sizeof(int));    //申请10个整型单元内存
    for(int i=0;i<=10;i++)    //11个，越界
    {
        p[i]=0;
    }
    free(p);
}

   修改了指针的指向导致崩溃
int main()
{
    int *p = (int *)malloc(10*sizeof(int));  //申请10个整型单元内存
    for(int i=0;i<10;i++)   //未越界，此处正确
    {
        *p=0;
         p++;
    }
    free(p);  //  free崩溃  //p不再指向首地址
}

   重复释放内存导致崩溃
int main()
{
	int *p=(int *)malloc(10*sizeof(int));//p申请10个整型单元内存
	for(int i=0;i<10;i++)
	{
		p[i]=i;
	}
	free(p);
	free(p);//重复释放了内存
	return 0;
}

  释放非动态分配的内存导致崩溃
int main()
{
    int arr[10];  //定义一个数组arr，10个内存单元
    free(arr);   //arr不是动态分配的内存，无法释放
}

 正确用法
  p释放后，重新指向NULL，则再次释放不会产生错误
int main()
{
	int *p=(int *)malloc(10*sizeof(int));//p申请10个整型单元内存
	for(int i=0;i<10;i++)
	{
		p[i]=i;
	}
	free(p);
    p = NULL;
	free(p);  // p此时为NULL指针，此时不会产生产生崩溃
	return 0;
}

//使用calloc()动态分配内存并清零
void *calloc( size_t num,size_t size );
功能： 在内存的动态存储区中分配num个长度为size的连续空间,并初始化为0，函数返回一个指向分配起始地址的指针；如果分配不成功，返回NULL。
使用后要使用 "free(起始地址的指针)" 对内存进行释放

与calloc与malloc的区别：
	calloc在动态分配完内存后，自动初始化该内存空间为零，而malloc不初始化，里边数据是随机值。

//使用realloc重新分配内存块
void *realloc(void *memblock,size_t size);
功能：先判断当前的指针是否有足够size大小的连续空间，如果有，扩大memblock指向的地址，并且将memblock返回，如果空间不够，先按照size指定的大小分配空间，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来memblock所指内存区域（注意：原来指针是自动释放，不需要使用free），同时返回新分配的内存区域的首地址。即重新分配存储器块的地址。


//常见的动态内存错误
	对NULL指针进行解引用操作
	对分配的内存进行操作时越过边界
	释放并非动态分配的内存
	试图释放一块动态分配的内存的一部分以及一块内存被释放之后被继续使用。  //释放一块内存的一部分是不允许的。动态分配的内存必须整块一起释放。
动态分配最常见的错误就是忘记检查所请求的内存是否成功分配。
动态内存分配的第二大错误来源是操作内存时超出了分配内存的边界。

当动态分配的内存不再需要使用时，应该被释放，这样可以被重新分配使用。分配内存但在使用完毕后不释放将引起内存泄漏(memory leak)。

如果一个指针不是从早先的malloc、calloc或realloc函数返回的，它是不能作为参数传递给free函数的。