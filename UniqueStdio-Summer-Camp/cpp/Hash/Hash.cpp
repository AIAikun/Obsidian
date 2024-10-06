unordered_map<elemType_1, elemType_2> var_name; //声明一个没有任何元素的哈希表， 
//其中elemType_1和elemType_2是模板允许定义的类型，如要定义一个键值对都为int的哈希表： 
unordered_map<int, int> map;

unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} }; //如果知道要创建的哈希表的元素个数时，也可以在初始化列表中指定元素个数 
unordered_map<int, int> hmap{ {{1,10},{2,12},{3,13}},3 };

mapName[key] = value; //在相同key中新的值会覆盖旧的值
napName.insert({key,value}); //在相同key中第二次插入会失败 
//不能一次添加多个键值对...

unordered_map<int, int> mapName{ {1,10},{2,12},{3,13} }; unordered_map<int, int> mapName1(mapName);

unordered_map<int, int> mapName{ {1,10},{2,12},{3,13} }; unordered_map<int, int>::iterator iter_begin = mapName.begin(); unordered_map<int, int>::iterator iter_end = mapName.end(); hmap.erase(iter_begin); //删除开始位置的元素 
hmap.erase(iter_begin, iter_end); //删除开始位置和结束位置之间的元素  
hmap.erase(3); //删除key==3的键值对

hmap.clear()

mapName[key] = value;//在相同key中新的值会覆盖旧的值

unordered_map<int, int> mapName{ {1,10},{2,12},{3,13} }; 
int elem = hmap.at(3);

unordered_map<int, int> mapName{ {1,10},{2,12},{3,13} }; unordered_map<int, int>::iterator iter; iter = mapName.find(2); //返回key==2的迭代器，可以通过iter->second访问该key对应的元素 
//if(iter != mapName.end()) cout << iter->second;
int pos = mapName.bucket(key);
