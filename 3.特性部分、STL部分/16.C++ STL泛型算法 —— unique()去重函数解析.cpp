
//16.C++ STL泛型算法 —— unique()去重函数解析

//unique:
它的功能是 元素去重;/此处的删除，并不是真的删除，而是指重复元素的位置被不重复的元素给占领了/，所以在执行去重之前，需要排序

//unique函数原型：
有三个参数，且前两个参数类型为迭代器，最后一个参数类型可以看作是bool类型：
iterator unique(iterator it_1,iterator it_2,bool MyFunc);

前两个参数是迭代器begin()和end()，第三个参数是函数参数，判断 迭代器所指对象 大小的方法，一般可以忽略；

//源码剖析
template <class ForwardIterator>
ForwardIterator unique (ForwardIterator first, ForwardIterator last)  //跑一下就知道怎么运行的，比较简单
{
  if (first==last) return last;

  ForwardIterator result = first;
  while (++first != last)
  {
    if (!(*result == *first)) 
      *(++result)=*first;
  }
  return ++result;
}

例子：1,2,2,3,3,3,4,5,6,6;
输出：1,2,3,4,5,6,4,5,6,6;  返回的是迭代器指向位置[6]，然后再删除6到end()的数据，返回begin()就行了,/注意：这的删除用erase，需要配合unique使用

//总结

1,unique()是STL泛型算法库中的去重函数,/功能是可以去除相邻重复元素。
2,由于unique()去除的是相邻重复元素,/因此，若初始状态容器无序，则在使用前首先要进行排序sort()。
3,unique()的去重原理是:/通过使用下一个不重复的元素替换重复元素完成删除，未删除的元素的相对次序保持不变。
4,unique()函数返回一个迭代器,/指向不重复序列的下一个元素位置
5,/unique()函数通常和erase()函数一起使用，来达到真正删除容器中重复元素的目的。
