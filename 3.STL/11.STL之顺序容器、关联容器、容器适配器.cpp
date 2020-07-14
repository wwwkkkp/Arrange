

//11.STL之顺序容器、关联容器、容器适配器

STL六大组件
1,容器（Containers）：各种数据结构，如Vector,List,Deque,Set,Map,用来存放数据，STL容器是一种Class Template,就体积而言，这一部分很像冰山载海面的比率。
2,算法（Algorithms）：各种常用算法如Sort,Search,Copy,Erase，从实现的角度来看，STL算法是一种Function Templates。
3,迭代器（Iterators）：扮演容器与算法之间的胶合剂，是所谓的“泛型指针”，共有五种类型，以及其它衍生变化，从实现的角度来看，迭代器是一种将：Operators*,Operator->,Operator++,Operator–等相关操作予以重载的Class Template。所有STL容器都附带有自己专属的迭代器——是的，只有容器设计者才知道如何遍历自己的元素，原生指针（Native pointer）也是一种迭代器。
4,仿函数（Functors）： 即函数对象，行为类似函数，可作为算法的某种策略（Policy）,从实现的角度来看，仿函数是一种重载了Operator()的Class 或 Class Template。一般函数指针可视为狭义的仿函数。
5,配接器（适配器）（Adapters）：一种用来修饰容器（Containers）或仿函数（Functors）或迭代器（Iterators）接口的东西，例如:		    /STL提供的Queue和Stack，虽然看似容器，其实只能算是一种容器配接器，因为它们的底部完全借助Deque，所有操作有底层的Deque供应/。改变Functor接口者，称为Function Adapter;改变Container接口者，称为Container Adapter;改变Iterator接口者，称为Iterator Adapter。配接器的实现技术很难一言蔽之，必须逐一分析。
6,分配器（Allocators）：即空间配置器，负责空间配置与管理，从实现的角度来看，配置器是一个实现了动态空间配置、空间管理、空间释放的Class Template。


//顺序容器（序列式容器）
顺序性容器 是一种各元素之间有顺序关系的线性表，是一种线性结构的可序群集.
1,vector是表示可变大小数组的序列容器，底层是内存可进行二倍扩容的数组。
2,就像数组一样，vector也采用的连续存储空间来存储元素。
3,/当新元素插入时候，这个数组需要被重新分配大小为了增加存储空间。其做法是，分配一个新的数组，然后将全部元素移到这个数组。就时间而言，这是一个相对代价高的任务/，
4,与其它动态序列容器相比（deques, lists and forward_lists）,/ vector在访问元素的时候更加高效，在末尾添加和删除元素相对高效。/

需要注意的是,/一旦引起空间重新配置，之前指向原vector的所有迭代器就都失效了，这一点在工程中容易引起bug。/


//deque

双端队列中的元素可以从两端弹出，其限定插入和删除操作在表的两端进行。
在前面和后面添加元素时都不需要移动其它块的元素。

1,两端都能快速插入元素和删除元素（vector只在尾端快速进行此类操作）。
2,存取元素时，deque的内部结构会多一个间接过程，所以元素的存取和迭代器的动作会稍稍慢一些。
3,迭代器需要在不同区块间跳转，所以必须是特殊的智能型指针，非一般指针。
4,在对内存区块有所限制的系统中，deque可以内含更多元素，因为它使用不止一块内存。//duque内存可以不连续
5,deque的内存区块不再被使用时，会被释放。deque的内存大小是可缩减的。

//list
访问随机元素不如vector快，随机的插入元素比vector快,/对每个元素分配空间，所以不存在空间不够，重新分配的情况/,
/list可以快速地在所有地方添加删除元素，但是只能快速地访问最开始与最后的元素。/


//容器适配器
STL提供了三种容器适配器：stack，queue，priority_queue;/stack和queue的低层都是用duque实现的，因为duque足够大，能快速删除插入头尾元素
适配器并不是一类容器，因为它们并没有提供与元素的保存形式有关的真正数据结构实现，并且适配器不支持迭代器。

//关联容器
关联容器和顺序容器的根本不同在于：关联容器中的元素是按关键字来保存和访问的，
map中的元素是一些关键字-值（key-value）对：关键字起到索引的作用，值则表示索引相关联的数据；
set中每个元素只包括一个关键字，set支持高效的关键字查询操作-检查一个给定关键字是否在set中。set相当于可以自动排序的vector，且不能有重复的关键字



关联性容器
按关键字有序保存元素
map set multimap multiset

无需集合
unordered_map unordered_set unordered_multimap unordered_multiset


multi- :允许出现重复的关键字