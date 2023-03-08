# 在编写C++程序时候踩得一些坑
## const
stl中的set为有序容器,类必须定义有“顺序”,重载operator<
```
constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator< to operands
	    return (_Left < _Right);
	}
};
```
根据stl中的源码，可知自定义的 operator左值右值均为 const；</br>
因此在自定义类重载 < 时需要
```
bool operator<(const CLASS& c) const{

}
```
错误的写成
```
bool operator<(const CLASS& c){

}
```
