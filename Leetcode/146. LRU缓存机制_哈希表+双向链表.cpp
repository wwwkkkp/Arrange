




//146. LRU缓存机制
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥已经存在，则变更其数据值；如果密钥不存在，则插入该组「密钥/数据值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

 

进阶:

你是否可以在 O(1) 时间复杂度内完成这两种操作？

 

示例:

LRUCache cache = new LRUCache( 2 /* 缓存容量 */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4


//哈希表+双向链表


typedef struct list1 *dlist;
struct list1{  //结点
    int k;
    int v;
    dlist f;
    dlist b;
    list1(int a,int b):k(a),v(b),f(NULL),b(NULL){}
};

class LRUCache {
public:
    dlist head=new list1(-1,-1);//头结点尾结点
    dlist rear=new list1(-1,1);
    unordered_map<int,dlist>um;  //哈希表用于存储某个key是否在链表中
    int k=0,s=0;
    LRUCache(int c) {
        k=c;
        head->f=rear;
        rear->b=head;
        s=0;
    }
    
    int get(int key) {
        if(um.find(key)!=um.end())//如果在链表中，就要将这个结点更新到链表最前面，注意，，这里是不用改变哈希表的，因为结点还在链表中，只是位置变了
            return erasetolist(key);
        else return -1;
    }
    
    void put(int key, int value) {
        if(um.find(key)!=um.end()){ //结点已经存在
            erasetolist(key);   //更新结点
            head->f->v=value;	//更新结点的值
            return;
        }
        dlist d=new list1(key,value);  //需要添加的新结点
        if(s<k){
            addtolist(d);  //不够数直接添加        
            s++;
        }
        else{
            auto w=rear->b;
            rear->b->b->f=rear;
            rear->b=rear->b->b;  //够数了要先删除尾结点
            um.erase(w->k);      //从哈希表中删除，  
            addtolist(d);   
        }
        um[key]=head->f;  //更新哈希表
    }
    int erasetolist(int key){  //从原位置删除
        auto w=um[key];
        w->b->f=w->f;
        w->f->b=w->b;
        addtolist(w);
        return w->v;
    }
    void addtolist(dlist w){  //添加到链表中
        
        w->f=head->f;
        head->f->b=w;
        head->f=w;
        w->b=head;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */