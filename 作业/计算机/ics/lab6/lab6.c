#include <stdio.h>

int moda_b(int,int);
int mul(int a,int b)
{
    int ans=0;
    while(b--)
    {
        ans+=a;
    }
    return ans;
}
int div(int a,int b)
{
    int ans=0;
    int temp=a;
    while(temp>=b)
    {
        ans++;
        temp-=b;
    }
    return ans;
}
void dectobin( int n,int b_arr[] )
{
    int k=1,i,temp;
    int j=0;
    temp = n;
    while(temp)
    {
        i = moda_b(temp,2);
        b_arr[j++] = i;
        temp = div(temp,2);
    }
}
int lab1(int a,int b)
{
    int ans=0;
    int b_arr[16]={0};
    dectobin(a,b_arr);
    for(int i=0;i<8;i++)
    {
        int temp=b_arr[i];
        b_arr[i]=b_arr[15-i];
        b_arr[15-i]=temp;
    }
    for(int i=16-b;i<16;i++)
    {
        if(b_arr[i])
        {
            ans++;
        }
    }
    return ans;
}

int moda_b(int a,int b)
{
    int b_temp=b;
    int mod_ans;
    while(a>=b_temp)
    {
        b_temp+=b;
    }
    b_temp-=b;
    mod_ans=a-b_temp;
    return mod_ans;
}

int lab2(int p,int q, int n)
{
    //printf("%d\n",moda_b(56,3));
    int f_1=1,f_2=1,f_n;
    int f_1_t,f_2_t;
    while(n>1)
    {
        f_2_t=moda_b(f_2,p);
        f_1_t=moda_b(f_1,q);
        //printf("%d ",f_2_t);
        //printf("%d\n",f_1_t);
        f_n=f_1_t+f_2_t;
        f_2=f_1;    
        f_1=f_n;
        n--;
    }
    return f_n;
}

int lab3(int n,char arr[])
{
    int maxl=0,maxl_l=1;
    char tmp=arr[0];
    for(int i=1;i<n;i++)
    {
        if(arr[i]==tmp)
        {
            maxl_l++;
        }
        else
        {
            if(maxl_l>maxl)
            {
                maxl=maxl_l;
            }
            maxl_l=1;
            tmp=arr[i];
        }
    }
    if(maxl_l>maxl)
    {
        maxl=maxl_l;
    }
    return maxl;
}

int lab4(int *a,int *b,int score[])
{
    int temp;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15-i;j++)
        {
            if(score[j+1]<score[j])
            {
                temp=score[j];
                score[j]=score[j+1];
                score[j+1]=temp;
            }
        }
    }
    for(int i=8;i<16;i++)
    {
        if(score[i]>=85)
        {
            if(i>=12)
                (*a)++;
            else 
                (*b)++;
        }
        else if(score[i]>=75)
            (*b)++;
    }
    return 0;
}

int main()
{
    FILE* fp;
	fp = fopen("D:\\CandC++ program\\c code\\test.txt", "r");
	if (fp == NULL)
	{
		printf("file is error.");
		return -1;
	}

    //lab1;
    int b_arr[16]={0};
    int a1,a2,b1,b2,a3,b3;
    fscanf(fp, "%d %d", &a1,&b1);
    fscanf(fp, "%d %d", &a2,&b2);
    fscanf(fp, "%d %d", &a3,&b3);
    printf("%d\n",lab1(a1,b1));
    printf("%d\n",lab1(a2,b2));
    printf("%d\n",lab1(a3,b3));



    
    //lab2
    int p1,q1,n_2_1,p2,q2,n_2_2,p3,q3,n_2_3;
    fscanf(fp,"%d%d%d%d%d%d%d%d%d",&p1,&q1,&n_2_1,&p2,&q2,&n_2_2,&p3,&q3,&n_2_3);
    printf("%d\n",lab2(p1,q1,n_2_1));
    printf("%d\n",lab2(p2,q2,n_2_2));
    printf("%d\n",lab2(p3,q3,n_2_3));


    //lab3
    int n_3_1,n_3_2,n_3_3;
    char arr_1[10],arr_2[10],arr_3[10];
    fscanf(fp,"%d",&n_3_1);
    fgetc(fp);
    for(int i=0;i<n_3_1;i++)
    {
        fscanf(fp,"%c",&arr_1[i]);
    }
    printf("%d\n",lab3(n_3_1,arr_1));

    fscanf(fp,"%d",&n_3_2);
    fgetc(fp);
    for(int i=0;i<n_3_2;i++)
    {
        fscanf(fp,"%c",&arr_2[i]);
    }
    printf("%d\n",lab3(n_3_2,arr_2));

    fscanf(fp,"%d",&n_3_3);
    fgetc(fp);
    for(int i=0;i<n_3_3;i++)
    {
        fscanf(fp,"%c",&arr_3[i]);
    }
    printf("%d\n",lab3(n_3_3,arr_3));
    
    
    //lab4
    int score1[16];
    int a_1=0,b_1=0;
    for(int i=0;i<16;i++)
    {
        fscanf(fp,"%d",&score1[i]);
    }
    lab4(&a_1,&b_1,score1);
    for(int i=0;i<16;i++)
    {
        printf("%d ",score1[i]);
    }
    printf("\n");
    printf("%d %d",a_1,b_1);
    printf("\n");
    
    int score2[16];
    int a_2=0,b_2=0;
    for(int i=0;i<16;i++)
    {
        fscanf(fp,"%d",&score2[i]);
    }
    lab4(&a_2,&b_2,score2);
    for(int i=0;i<16;i++)
    {
        printf("%d ",score2[i]);
    }
    printf("\n");
    printf("%d %d",a_2,b_2);
    printf("\n");

    int score3[16];
    int a_3=0,b_3=0;
    for(int i=0;i<16;i++)
    {
        fscanf(fp,"%d",&score3[i]);
    }
    lab4(&a_3,&b_3,score3);
    for(int i=0;i<16;i++)
    {
        printf("%d ",score3[i]);
    }
    printf("\n");
    printf("%d %d",a_3,b_3);
    printf("\n");
    return 0;
}
