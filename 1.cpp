#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
struct train//�������Ϣ�ṹ
{
	char place[20];
	char checi[20];
	char chexiang[20];
	int piaonum;
}Train;

struct chengke//����˿���Ϣ�ṹ
{
	char name[20];
	char shengfenzheng[30];
	int level;
}Chengke;

train *X;
chengke *Y;

void menu()//��ҳ��˵���
{
	printf("******************************************\n");
	printf("***********��ӭ��������Ʊϵͳ��**********\n");
	printf("**************1.¼�����Ϣ**************\n");
	printf("**************2.��ѯ��Ϣ******************\n");
	printf("**************3.��Ʊ**********************\n");
	printf("**************4.��Ʊ**********************\n");
	printf("**************5.�ر�**********************\n");
    printf("******************************************\n");
}

void add(train *X)//¼�����Ϣ��ģ��
{
	X=&Train;//��һ��ʼ�Ľṹ�ĵ�ַ����X
	FILE *fp;
	fp=fopen("d:\\train.txt","a+");//�½��ı��ļ�
	printf("������Ҫ��ӵ�·�ߵĸ���:");
	int i,j;
	scanf("%d",&j);
	fflush(stdin);//���������
	for(i=1;i<=j;i++)//ѭ�����������·�ߵ�����
	{
		printf("��%d��·��\n",i);
		printf("�յ�վ��:");
		gets(X[i].place);
		fflush(stdin);
		printf("���κ���:");
		gets(X[i].checi);
		fflush(stdin);
		printf("�������:");
		gets(X[i].chexiang);
		fflush(stdin);
		printf("��Ʊ����:");
		scanf("%d",&X[i].piaonum);
		fflush(stdin);
		fwrite(&X[i],sizeof(train),1,fp);//���������Ϣ�����ļ�
	}
	fclose(fp);
	printf("·������ɹ���\n");
}

void search1(train *X)
{
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","rt");//��ȡ�ļ�
	char a[20];//��ʱ���飬��ų��κ�
	printf("�����복�κ�:");
	scanf("%s",a);
	int i,j;
	if(fp==NULL)
	{
		printf("train.txt not found!\n");
	    exit(1);
	}
	for(i=0;feof(fp)==0;i++)//ѭ���ڶ�ȡȫ����Ϣ�����
	{
		fread(&X[i],sizeof(train),1,fp);
	}
	fclose(fp);
	for(j=0;j<i;j++)
	{
		if(strcmp(a,X[j].checi)==0)//�Ƚϴ�����Ϣ���Ƿ�����Ҫ��
		{
			printf("�յ�վΪ:%s\n",X[j].place);
			printf("�����Ϊ:%s\n",X[j].chexiang);
			printf("��Ʊ��Ϊ:%d\n",X[j].piaonum);
		}
	}
}

void search2(train *X)//���һ����������ʵ�ַ���һ��
{
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","rt");
	char a[20];
	printf("������Ŀ�ĵ���:");
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
			printf("���κ�Ϊ:%s\n",X[j].checi);
			printf("�����Ϊ:%s\n",X[j].chexiang);
			printf("��Ʊ��Ϊ:%d\n",X[j].piaonum);
		}
	}
}

void menu2()//�ڶ����˵�
{
	printf("******************************************\n");
	printf("************��ѡ��������ҵķ�ʽ**********\n");
	printf("************1.ͨ�����κŲ�ѯ**************\n");
	printf("************2.ͨ���յ�վ��ѯ**************\n");
	printf("*****************3.�뿪*******************\n");
	printf("******************************************\n");
	int a;
	do
	{
		printf("���ѡ����:");
		scanf("%d",&a);
		switch(a)//ѡ����������в�ͬ�ķ�֧
		{
		case 1:search1(X);break;
		case 2:search2(X);break;
		case 3:printf("���ڷ���\n");break;
		default:printf("�����������������!\n");
		}
	}
	while(a!=3);//ֻ�е�ѡ���뿪ʱ�Ż᷵���ϸ��˵�������ѭ��ʹ��
}

int xingxi(chengke *Y)
{
	Y=&Chengke;//����Y�ṹ�ĵ�ַ
	FILE *fp;
	fp=fopen("d:\\chengke.txt","a+");//�������޸�һ���ı��ļ�
	printf("������Ҫ�����Ʊ�ĸ���:");
	int i,j;
	scanf("%d",&j);
	fflush(stdin);
	for(i=1;i<=j;i++)
	{
		printf("��%d��Ʊ\n",i);
		printf("������:");
		gets(Y[i].name);
		fflush(stdin);
		printf("���֤������:");
		gets(Y[i].shengfenzheng);
		fflush(stdin);
		printf("��Ҫ�������λ�ȼ���:");
		scanf("%d",&Y[i].level);
		fflush(stdin);
		fwrite(&Y[i],sizeof(chengke),1,fp);//��������Ϣ�������鲢д���ı��ļ�
	}
	fclose(fp);
	return i-1;//���ض���Ʊ�����������������Ʊ���ļ���
}

void ticket(train *X)
{
	char a[20];
	int i,j,k;
	X=&Train;
	FILE *fp;
	fp=fopen("d:\\train.txt","a+");//Ϊ�˺���������Ʊ��
	printf("�������빺��ĳ�Ʊ��Ϣ:\n");
	printf("Ŀ�ĵ���:\n");
	scanf("%s",a);
	for(i=0;feof(fp)==0;i++)
	{
		fread(&X[i],sizeof(train),1,fp);//��ȡ���е���Ϣ��������
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(a,X[j].place)==0)//�ж�Ҫ�����Ʊ�Ƿ��д�·��
		{
			if(X[j].piaonum>0)//��Ʊ���������0���ܹ�Ʊ
			{
				k=xingxi(Y);//k�洢����Ʊ������
				X[j].piaonum=X[j].piaonum-k;
				fwrite(&X[j],sizeof(train),1,fp);
				if(X[j].piaonum>=0)//���ж�����Ʊ��ʣ���Ʊ���Ƿ�>=0
				{
				     printf("����ɹ���");break;
				}
				else
					printf("��Ʊ�����㣬�޷�����");break;
			}
			else
				printf("û����Ʊ������ʧ�ܣ�");break;
		}
		else
			printf("û�и�Ŀ�ĵصĳ�Ʊ������ʧ�ܣ�");break;
	}
	fclose(fp);
}

void Delete(chengke *Y)
{
	Y=&Chengke;
	FILE *fp;
	char a[30];//�洢��������֤��
	int i,j;
	printf("������������֤:");
	scanf("%s",a);
	fp=fopen("d:\\chengke.txt","rt");
	if(fp==NULL)
	{
		printf("chengke.txt not found!\n");
		exit(1);
	}
	for(i=0;feof(fp)==0;i++)//����˿���Ϣ
	{
		fread(&Y[i],sizeof(chengke),1,fp);
	}
	fclose(fp);
	for(j=0;j<i;j++)
	{
		if(strcmp(a,Y[j].shengfenzheng)==0)//���洢�ĳ˿���Ϣ������Ľ��бȶ�
			memset(&Y[j],0,sizeof(train));//������ھ�ɾ�������ж�Ӧ�˿���Ϣʵ����Ʊ
	}
	fp=fopen("d:\\chengke.txt","w+");
	for(i=0;i<=j;i++)
		fwrite(&Y[i],sizeof(chengke),1,fp);//���޸ĺ����������¼���ı�����֮ǰ���ı�ʵ��ɾ��
		fclose(fp);
		printf("�ɹ���Ʊ!\n");
}


int main()
{
	int a;
		do
	{
		menu();
		printf("���ѡ����:");
	    scanf("%d",&a);
		switch(a)//��ͬ��ѡ����벻ͬ��ģ��
		{
		case 1:add(X);
		       break;
		case 2:menu2();break;
		case 3:ticket(X);break;
		case 4:Delete(Y);break;
		case 5:printf("��л����ʹ���ټ�\n");break;
		default:printf("�����������������!\n");
		}
	}
	while(a!=5);//ʹ�ó������ظ�ʹ��
	return 0;
}