#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
struct train//定义火车信息结构
{
	char place[20];
	char checi[20];
	char chexiang[20];
	int piaonum;
}Train;

struct chengke//定义乘客信息结构
{
	char name[20];
	char shengfenzheng[30];
	int level;
}Chengke;

train *X;
chengke *Y;

void menu()//主页面菜单栏
{
	printf("******************************************\n");
	printf("***********欢迎来到火车售票系统！**********\n");
	printf("**************1.录入火车信息**************\n");
	printf("**************2.查询信息******************\n");
	printf("**************3.订票**********************\n");
	printf("**************4.退票**********************\n");
	printf("**************5.关闭**********************\n");
    printf("******************************************\n");
}

void add(train *X)//录入火车信息的模块
{
	X=&Train;//将一开始的结构的地址赋予X
	FILE *fp;
	fp=fopen("d:\\train.txt","a+");//新建文本文件
	printf("请输入要添加的路线的个数:");
	int i,j;
	scanf("%d",&j);
	fflush(stdin);//清除缓存区
	for(i=1;i<=j;i++)//循环来输入多条路线的数据
	{
		printf("第%d条路线\n",i);
		printf("终点站是:");
		gets(X[i].place);
		fflush(stdin);
		printf("车次号是:");
		gets(X[i].checi);
		fflush(stdin);
		printf("车厢号是:");
		gets(X[i].chexiang);
		fflush(stdin);
		printf("余票量是:");
		scanf("%d",&X[i].piaonum);
		fflush(stdin);
		fwrite(&X[i],sizeof(train),1,fp);//将输入的信息存入文件
	}
	fclose(fp);
	printf("路线增添成功！\n");
}

void search1(train *X)
{
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","rt");//读取文件
	char a[20];//临时数组，存放车次号
	printf("请输入车次号:");
	scanf("%s",a);
	int i,j;
	if(fp==NULL)
	{
		printf("train.txt not found!\n");
	    exit(1);
	}
	for(i=0;feof(fp)==0;i++)//循环在读取全部信息后结束
	{
		fread(&X[i],sizeof(train),1,fp);
	}
	fclose(fp);
	for(j=0;j<i;j++)
	{
		if(strcmp(a,X[j].checi)==0)//比较储存信息中是否有需要的
		{
			printf("终点站为:%s\n",X[j].place);
			printf("车厢号为:%s\n",X[j].chexiang);
			printf("余票量为:%d\n",X[j].piaonum);
		}
	}
}

void search2(train *X)//与第一种搜索方法实现方法一致
{
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","rt");
	char a[20];
	printf("请输入目的地名:");
	scanf("%s",a);
	int i,j;
	if(fp==NULL)
	{
	    printf("train.txt not found!\n");
	    exit(1);
	}
	for(i=0;feof(fp)==0;i++)
	{
		fread(&X[i],sizeof(train),1,fp);
	}
	fclose(fp);
	for(j=0;j<i;j++)
	{
		if(strcmp(a,X[j].place)==0)
		{
			printf("车次号为:%s\n",X[j].checi);
			printf("车厢号为:%s\n",X[j].chexiang);
			printf("余票量为:%d\n",X[j].piaonum);
		}
	}
}

void menu2()//第二个菜单
{
	printf("******************************************\n");
	printf("************请选择你想查找的方式**********\n");
	printf("************1.通过车次号查询**************\n");
	printf("************2.通过终点站查询**************\n");
	printf("*****************3.离开*******************\n");
	printf("******************************************\n");
	int a;
	do
	{
		printf("你的选择是:");
		scanf("%d",&a);
		switch(a)//选择语句来进行不同的分支
		{
		case 1:search1(X);break;
		case 2:search2(X);break;
		case 3:printf("正在返回\n");break;
		default:printf("输入错误，请重新输入!\n");
		}
	}
	while(a!=3);//只有当选择离开时才会返回上个菜单，可以循环使用
}

int xingxi(chengke *Y)
{
	Y=&Chengke;//赋予Y结构的地址
	FILE *fp;
	fp=fopen("d:\\chengke.txt","a+");//创建或修改一个文本文件
	printf("请输入要购买的票的个数:");
	int i,j;
	scanf("%d",&j);
	fflush(stdin);
	for(i=1;i<=j;i++)
	{
		printf("第%d张票\n",i);
		printf("姓名是:");
		gets(Y[i].name);
		fflush(stdin);
		printf("身份证号码是:");
		gets(Y[i].shengfenzheng);
		fflush(stdin);
		printf("需要购买的座位等级是:");
		scanf("%d",&Y[i].level);
		fflush(stdin);
		fwrite(&Y[i],sizeof(chengke),1,fp);//将上述信息存入数组并写进文本文件
	}
	fclose(fp);
	return i-1;//返回订购票的数量，方便后续余票量的计算
}

void ticket(train *X)
{
	char a[20];
	int i,j,k;
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","a+");//为了后续更改余票量
	printf("输入你想购买的车票信息:\n");
	printf("目的地是:\n");
	scanf("%s",a);
	for(i=0;feof(fp)==0;i++)
	{
		fread(&X[i],sizeof(train),1,fp);//读取所有的信息存入数组
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(a,X[j].place)==0)//判断要购买的票是否有此路线
		{
			if(X[j].piaonum>0)//余票量必须大于0才能购票
			{
				k=xingxi(Y);//k存储购买票的数量
				X[j].piaonum=X[j].piaonum-k;
				fwrite(&X[j],sizeof(train),1,fp);
				if(X[j].piaonum>=0)//再判断买完票后剩余的票数是否>=0
				{
				     printf("购买成功！");break;
				}
				else
					printf("余票量不足，无法购买！");break;
			}
			else
				printf("没有余票，购买失败！");break;
		}
		else
			printf("没有该目的地的车票，购买失败！");break;
	}
	fclose(fp);
}

void Delete(chengke *Y)
{
	Y=&Chengke;
	FILE *fp;
	char a[30];//存储输入的身份证号
	int i,j;
	printf("请输入你的身份证:");
	scanf("%s",a);
	fp=fopen("d:\\chengke.txt","rt");
	if(fp==NULL)
	{
		printf("chengke.txt not found!\n");
		exit(1);
	}
	for(i=0;feof(fp)==0;i++)//读入乘客信息
	{
		fread(&Y[i],sizeof(chengke),1,fp);
	}
	fclose(fp);
	for(j=0;j<i;j++)
	{
		if(strcmp(a,Y[j].shengfenzheng)==0)//将存储的乘客信息与输入的进行比对
			memset(&Y[j],0,sizeof(train));//如果存在就删除数组中对应乘客信息实现退票
	}
	fp=fopen("d:\\chengke.txt","w+");
	for(i=0;i<=j;i++)
		fwrite(&Y[i],sizeof(chengke),1,fp);//将修改后的数组重新录入文本覆盖之前的文本实现删除
		fclose(fp);
		printf("成功退票!\n");
}


int main()
{
	int a;
		do
	{
		menu();
		printf("你的选择是:");
	    scanf("%d",&a);
		switch(a)//不同的选择进入不同的模块
		{
		case 1:add(X);
		       break;
		case 2:menu2();break;
		case 3:ticket(X);break;
		case 4:Delete(Y);break;
		case 5:printf("感谢您的使用再见\n");break;
		default:printf("输入错误，请重新输入!\n");
		}
	}
	while(a!=5);//使该程序能重复使用
	return 0;
}