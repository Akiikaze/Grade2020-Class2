#include <bits/stdc++.h>


using namespace std;

int f[1200][1200];
int si[1200];
int main(){
	int N,V;
	cin>>N>>V;
	int v[N+4],w[N+4];
	for(int i=1;i<=N;i++){
		cin>>v[i]>>w[i];
	}
	for(int i=1;i<=N;i++){
		for(int j=0;j<=V;j++){
		    if(j>=v[i])//�ܷ��� 
			f[i][j]=max(f[i-1][j],f[i][j-v[i]]+w[i]);//Ҫô���ţ�Ҫô��һ��-->����һ������ 
			else
			f[i][j]=f[i-1][j];//�Ų���
		}
	}	
	cout<<f[N][V]<<endl;
	
//һά���������
//��01������ȫ��ͬ������ʹ�õ��Ƶķ�ʽ���ϸ���si������
//������Ҫsi[j-v[i]]����������Ʒi���ѱ����µ�״̬ 
 
	for(int i=1;i<=N;i++){
		for(int j=v[i];j<=V;j++){
			si[j]=max(si[j],si[j-v[i]]+w[i]);
		}
	}
	cout<<si[V]<<endl;
	
	return 0;
}
