#include <bits/stdc++.h>
using namespace std;

int N,V;

int f[1200][1200];  //f[I][J]��ʾ����I����Ʒ��J���ռ��µ����ż�ֵ

int si[1200]; //һά����� 

//main ���������Զ���ʼ��Ϊ0�� 

int main(){
	cin>>N>>V;  //����N����Ʒ�������ռ�ΪV 
	int v[1200],w[1200];	//v-->ÿ���������   w-->ÿ������ļ�ֵ 
	for(int i=1;i<=N;i++){
		scanf("%d %d",&v[i],&w[i]);//����-->�ӵ�һ����Ʒ��ʼ��¼ÿ����Ʒ��V��W�������i��ͬ 
	}
	for(int i=0;i<N;i++){
	//	cout<<v[i]<<w[i]<<endl;
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=V;j++){
			f[i][j]=0;
		}
	}
	//�����ǵݹ��˼�룬��ǰ���֤����ʱ��ֵ ���� 0 
	for(int i=1;i<=N;i++){//00�Ѿ���ʼ��Ϊ0�����Կ����ӹ� 
		for(int j=1;j<=V;j++){
			if(j<v[i]){   //���ȿ����ܷ���µ�I����Ʒ 
				f[i][j]=f[i-1][j];//�����ܷ��£����൱�ڶ���i-1����Ʒ��j���ռ��µ���� 
			}else{
				f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+w[i]);//���ܷ��£�����Ƚϲ������ͷ���������� �ĸ���ֵ 
			}
		//	cout<<"f[i][j]="<<f[i][j]<<endl;
		}
	}
	cout<<f[N][V]<<endl;	
	//�����ṩһά����Ľ������:ͨ������ǰ������i-1��״̬����i��״̬ 
	
	for(int i=1;i<=N;i++){
		for(int j=V;j>=v[i];j--){
			si[j]=max(si[j],si[j-v[i]]+w[i]);
		}
	}
	cout<<si[V]<<endl
    return 0;
}
