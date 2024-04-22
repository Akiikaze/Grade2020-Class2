## [题目描述：多重背包问题II](https://www.acwing.com/problem/content/5/)

有 N种物品和一个容量是 V 的背用。

i 种物品最多有 si 件，每件体积是 vi，价值是 wi。

求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。  
输出最大价值。

#### 输入格式

第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。

接下来有 N 行，每行两个整数 vi, wi，si 用空格隔开，分别表示第 i 件物品的体积和价值和数量。

#### 输出格式

输出一个整数，表示最大价值。

#### 数据范围

0<N≤1000  
0<V≤2000  
0<vi,wi,si≤2000

[[AcWing 4 多包 I(一看就会,懒人专用)+精简代码 -]]

#### 输入样例

```
4 5
1 2 3
2 4 1
3 4 3
4 5 2
```

#### 输出样例

```
10
```

## 基本思考框架

![image.png](https://gitee.com/chzarles/images/raw/master/imgs/006eb5E0gy1g7z0e5ghloj31150fw0ub.jpg)

思路和[多重背包问题I](https://chzarles.github.io/2019/10/15/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92-%E5%A4%9A%E9%87%8D%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98I/)一样，但这题的数据范围变成1000了，非优化写法时间复杂度O(n^3) 接近 1e9

必超时。

## 优化多重背包的优化

**首先**，我们不能用完全背包的优化思路来优化这个问题，因为每组的物品的个数都不一样，是不能像之前一样推导不优化递推关系的。（详情看下面引用的博文）

> 引用我之前写的博客：动态规划-完全背包问题
> 
> **我们列举一下更新次序的内部关系：**
> 
> f\[i , j \] = max( f\[i-1,j\] , f\[i-1,j-v\]+w , f\[i-1,j-2_v\]+2_w , f\[i-1,j-3_v\]+3_w , .....)  
> f\[i , j-v\]= max( f\[i-1,j-v\] , f\[i-1,j-2_v\] + w , f\[i-1,j-2_v\]+2\*w , .....)  
> 由上两式，可得出如下递推关系：  
> f\[i\]\[j\]=max(f\[i,j-v\]+w , f\[i-1\]\[j\])  

**接下来，我介绍一个二进制优化的方法**，假设有一组商品，一共有11个。我们知道，十进制数字 **11** 可以这样表示  

11\=1011(B)\=0111(B)+(11−0111(B))\=0111(B)+0100(B)

正常背包的思路下，我们要求出含这组商品的最优解，我们要枚举12次（枚举装0，1，2....12个）。

现在，如果我们把这11个商品分别打包成含商品个数为1个，2个，4个，4个（分别对应0001,0010,0100,0100）的四个”新的商品 “, 将问题转化为01背包问题，对于每个商品，我们都只枚举一次，那么我们只需要枚举四次 ，就可以找出这含组商品的最优解。 这样就大大减少了枚举次数。

这种优化对于大数尤其明显，例如有1024个商品，在正常情况下要枚举1025次 ， 二进制思想下转化成01背包只需要枚举10次。

## 优化的合理性的证明

**先讲结论：上面的1，2，4，4是可以通过组合来表示出0~11中任何一个数的，还是拿11证明一下（举例一下）：**

**首先，11可以这样分成两个二进制数的组合：**  

11\=0111(B)+(11−0111(B))\=0111(B)+0100(B)

**其中0111通过枚举这三个1的取或不取（也就是对0001(B)，0010(B)，0100(B)的组合），可以表示十进制数0~7( 刚好对应了 1，2，4 可以组合出 0~7 ) , 0~7的枚举再组合上0100(B)( 即 十进制的 4 ) ，可以表示十进制数 0~11。其它情况也可以这样证明。这也是为什么，这个完全背包问题可以等效转化为01背包问题，有木有觉得很奇妙**

## 怎么合理划分一个十进制数?

上面我把11划分为

> 11\=0111(B)+(11−0111(B))\=0111(B)+0100(B)

是因为 0111(B)刚好是小于11的最大的**尾部全为1**的二进制 ( 按照上面的证明，这样的划分没毛病 ) , 然后那个尾部全为1的数又可以 分解为 0000....1 , 0000....10 , 0000....100 等等。

>即n以内的任意一个数 $2^m$ $>=$ n $>=$ $2^p$  $m = p + 1$
>都可以表示为$\sum$ $2^i$ $\ast$ $k$ , $\{ k = 0 ，1  \}$


对应c++代码：

```cpp
     //设有s个商品，也就是将s划分
    for(int k = 1 ; k <= s ;k*=2)
{
    s-=k;
    goods.push_back({v*k,w*k});
}
if(s>0) 
    goods.push_back({v*s,w*s});
```

我写好理解一点 
- 现在能对但时间超了
```cpp
#include <bits/stdc++.h>
using namespace std;
int v,value,num; 
int N,V;
int divi[12];
int f[2000];  //V<2000
int p;  //二进制位数
int main(){
	cin>>N>>V;
	for(int i=1;i<=N;i++){
		cin>>v>>value>>num;
		p=0;
		do{
			p++;
			divi[p]=pow(2,p-1);
			if(num<divi[p]){
				divi[p]=num;	
			}
			num-=divi[p];   //二进制拆分
		}while(num>0);
		//拆完了就按照01背包进行分配
		for(int l=1;l<=p;l++){
			for(int j=V;j>=v*divi[l];j--)
		        f[j]=max(f[j],f[j-v*divi[l]]+value*divi[l]);
		}
	}
	cout<<f[V]<<endl;
	return 0;
}
```
#### 看我手搓一个 
WA?
- 怎么回事呢🤔  -->  结果是`j>=dv[i]写错了写成j>=0 --> 少了判定条件`
- 这下做对了
```cpp
#include <bits/stdc++.h>
using namespace std;
int v,value,num; 
int N,V;
int dv[25000],dvalue[25000];
int f[2000];  //V<2000
int p;  //二进制位数
int main(){
	cin>>N>>V;
	int k=1;//计位(表示二进制划分后的背包有多少‘种’物品)
	for(int i=1;i<=N;i++){
		cin>>v>>value>>num;
		for(p=1;p<=num;p<<=1){   //-->"<<"表示把存储的二进制数左移一格
			dv[k]=p*v;           //例如0001 --> 0010
			dvalue[k]=p*value;
			k++;
			num-=p;
		}
		if(!num==0){   //处理剩下的
			dv[k]=num*v;
			dvalue[k]=num*value;
			k++;
		}
	}
	//拆完了，然后是处理了
	for(int i=1;i<=k;i++){
		for(int j=V;j>=dv[i];j--){
			f[j]=max(f[j],f[j-dv[i]]+dvalue[i]);	
		}
	}
	cout<<f[V]<<endl;
	return 0;
}
```

（复制自acwing）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int N,V,v[1001],w[1001],dp[2001],s[1001]
    int a[25000],b[25000];  //2的12次方大于2000，也就是说一个数最多可以拆成12个，故数组容量乘12 
    cin>>N>>V;        
    memset(dp,0,sizeof(dp));
    for(int i=0;i<N;i++)
        cin>>v[i]>>w[i]>>s[i];
    int total=0;  
    for(int i=0;i<N;i++)
    {
        for(int j=1;j<=s[i];j<<=1)//二进制拆分 
         {
            a[total]=j*w[i];//存价值 
            b[total]=j*v[i];//存容量 
            s[i]-=j;
         }
         if(s[i])//当s[i]>0; 
         {
             a[total]=s[i]*w[i];
             b[total++]=s[i]*v[i];
         }
    }
    for(int i=0;i<total;i++)//01背包 
     for(int j=V;j>=b[i];j--)
      dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
    cout<<dp[V];
    return 0;
}
```

[链接](https://www.acwing.com/solution/content/1024/)

## 终究AC代码：01优化+二进制优化

ac代码

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 2010;
int f[N],n,m;
struct good   //结构体
{
    int w,v;
};

int main()
{
    cin>>n>>m;
    vector<good> Good;
    good tmp;

    //二进制处理
    for(int i = 1 ; i <= n ; i++ )
    {
        int v,w,s;
        cin>>v>>w>>s;
        //坑,k <= s
        for(int k = 1 ; k <= s ; k*=2 )
        {
            s-=k;
            Good.push_back({k*w,k*v});
        }
        if(s>0) Good.push_back({s*w,s*v});
    }

    //01背包优化+二进制
    for(auto t : Good)
        for(int j = m ; j >= t.v ; j--)
            f[j] = max(f[j] , f[j-t.v]+t.w ); //这里就是f[j]


    cout<<f[m]<<endl;
    return 0;

}

作者：Charles__
链接：https://www.acwing.com/solution/content/5527/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```