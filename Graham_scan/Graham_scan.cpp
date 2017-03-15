// Graham_scan.cpp : 定义控制台应用程序的入口点。
//
// 凸包算法的实际应用
// 条件：有一个大小为PSIZE的数组，数组元素是点坐标，最后一个点是恐龙坐标，其他点都是树桩坐标
// 问题：若恐龙能被树桩围住，则猎人能抓住恐龙，求问是否能抓住？（恐龙在树桩上，或者在两个树桩的连线上，都算能被抓住）
// 思路：1、恐龙在树桩上   --->循环比较
//       2、若不在树桩上，表明有PSIZE个不同的点，用凸包算法求出凸边。
//                      (1) 若恐龙不在凸边上 --》能抓住
//                      (2) 若恐龙在凸边上
//                                  a.  恐龙相邻的两个树桩的连线上 --》能抓住
//                                  b.  不在连线上--》抓不住
#include "stdafx.h"
#include "stdio.h"
#include <iostream>

#define PSIZE 10
using namespace std;


class Point
{
private:
	    double x,y;

public:
	    Point()
		{
		   x=0;
		   y=0;
		}
		Point(double m_x,double m_y)
		{
		    x = m_x;
			y = m_y;
		}
	    Point operator-(const Point &t)
		{
		   Point ret;
		   ret.x = x-t.x;
		   ret.y = y-t.y;
		   return ret;
		}
		bool operator==(const Point &t)
		{
			return (x==t.x && y==t.y);		
		}

		double det(const Point &t)
		{
		   return x*t.y-y*t.x;      //若t在左边，返回正值
		}
	
	    void getXY(double X,double Y)
		{
		   x=X;
		   y=Y;
		}
		void showXY(void)
		{
			cout<<"X is"<<x;
			cout<<"Y is"<<y<<endl;

		}
		bool compare(Point &t)
		{
			if(x!=t.x)
				return x<t.x;
			else
				return y<t.y;
		}
		double ratio(Point &t)
		{
		    return (t.y-y)/(t.x-x);
		}
		
		~Point()
		{
		  // cout<< "Bye,"<< x;
		}

};
typedef Point datatype;
class QuickSort{
public:
	   datatype *quicksort(datatype* A, int n)
	   {
	      sort(A,0,n-1);
		  return A;
	   }
	   void sort(datatype *A,int left,int right)
	   {

	       int i=left-1;
		   Point temp;
		   if(left>=right)
			   return;
		   temp = A[(right+left)/2];
		   A[(right+left)/2] = A[right];
		   A[right] = temp;
		   for(int j=left;j<right;j++)
		   {
			  
		      if(A[j].compare(A[right]))
			  {
				i++;
				temp = A[j];
				A[j] = A[i];
				A[i] = temp; 
			  }
            }
		   temp = A[right];
		   A[right] = A[i+1];
		   A[i+1] = temp;  //将数组分成了左小右大的两部分
		   sort(A,left,i);//快排左边部分
		   sort(A,i+2,right);

	   
	   }


};

class Graham
{
public:
	int number;
	
	int find_boundary(datatype *A,int *B,int N)
	{
		int j=-1; //标记凸边上最后一个点
		int tmp;//标记下凸边的最后一个点
		B[++j] = 0;
		
	    for(int i=1;i<N;i++) //扫描下凸边
		{ 
			
			    /*
				    在笛卡尔坐标系上的扫描顺序是，左-》右，下-》上
					向量A*(叉乘)B，<0: B在A的右边  
					               =0: B跟A共线  (可构成凸包)
								   >0: B在A的左边(可构成凸包)
				*/
			    if(j>0)
				{
					
				   while(j>0 && (A[B[j]]-A[B[j-1]]).det(A[i]-A[B[j]])<0) 
							j--;  //舍弃凸边数组的最后一个点，直到新点在左边
				}
					

				B[++j]=i; //该点能构成凸包
				cout<<"B["<<j<<"] = "<<B[j];
			 
		 }
		
		cout<<"down is OK"<<endl;
		/*
		  下凸边扫描后，最右上的点必然在B[]里，而最右上的点为A[N-1],所以上凸边扫描从
		  A[N-2]开始。
		*/
		for(int i=N-2;i>=0;i--) //扫描上凸边 
		{
		   
			    while((A[B[j]]-A[B[j-1]]).det(A[i]-A[B[j]])<0) //新的点在凸边数组最后的两个点形成的边的右边
                      j--;  //舍弃凸边数组的最后一个点，直到新点在左边

				B[++j]=i; //新点索引存入凸边数组
				cout<<"B["<<j<<"] = "<<B[j];
			 
		 }
		cout<<"up is OK"<<endl;
		return j;//返回凸边数组的大小
	}
};

void main(void)
{
	int flag=0;

    QuickSort sort;
	Point x[PSIZE]={
		Point(-1,2),
		Point(1,1),
		Point(-1,3),
	    Point(4,2),
		Point(-3.5,-3.5),
		Point(4,-3.5),
		Point(4,3),
		Point(-3.5,3),
		Point(2,4),
		Point(0,-4)
	};
  
  
   Point dinosaur = x[PSIZE-1];

  /*
     先判断是否在树桩上
  */
	for(int i=0;i<PSIZE-1;i++)
  {
      if(x[i]==dinosaur)
	  {
		     cout<<"the dinosaur can be catched"<<endl;
		     flag = 1;
			 break;
	  }
		  
	  
  }
 
/*
   若不在树桩上，则判断是否在凸包的凸边上

*/
   if(flag==0) 
 {
   Point* y = sort.quicksort(x,PSIZE);  //quicksort(数组名，点的个数)
   for(int i=0;i<PSIZE;i++)  //打印出按照从左到右，从下到上排序后的点数组
   {
      cout<<"i = "<<i; 
	  y[i].showXY(); 
   }
		
   Graham graham; // 定义一个graham对象
   int convex[PSIZE],number; // convex[]:保存在凸包边上的点的序号（排序后的序号）
   number = graham.find_boundary(y,convex,PSIZE); //得到凸包边上的点数
   cout<<"the Points number on boundary is "<<number<<endl;
   
   cout<<"the Points index on boundary is ";
  for(int i=0;i<number;i++)
  {
      
	  cout<<convex[i];
  }
  cout<<endl;
  //下面判断恐龙是否在凸边上
  for(int i=0;i<number;i++)
  {
      if(y[convex[i]]==dinosaur) //在凸边上
	  {
		 /*
		    接下来要判断是否在相邻树桩的连线上 [0 , 1 ,2 ,3 ,...,number-1]
		 */
		  if(i==0)//因为排序的原因 ，恐龙若在[0]处，则不可能在连线上
		  {
		     cout<<"can't catch the dinosaur"<<endl;
		  }
		  else
		  {
		     if(y[convex[i]].ratio(y[convex[(i+1)%number]])==y[convex[i-1]].ratio(y[convex[i]]))//若斜率一致
				 cout<<"the dinosaur can be catched"<<endl;
			 else
                 cout<<"can't catch the dinosaur"<<endl;
		  }
		  
	    
		 break;
	  }
		  
	  if(i==number-1) //不在凸边上
		  cout<<"the dinosaur can be catched"<<endl;
  }

 }
  
}





