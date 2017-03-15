// Graham_scan.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ͹���㷨��ʵ��Ӧ��
// ��������һ����СΪPSIZE�����飬����Ԫ���ǵ����꣬���һ�����ǿ������꣬�����㶼����׮����
// ���⣺�������ܱ���׮Χס����������ץס�����������Ƿ���ץס������������׮�ϣ�������������׮�������ϣ������ܱ�ץס��
// ˼·��1����������׮��   --->ѭ���Ƚ�
//       2����������׮�ϣ�������PSIZE����ͬ�ĵ㣬��͹���㷨���͹�ߡ�
//                      (1) ����������͹���� --����ץס
//                      (2) ��������͹����
//                                  a.  �������ڵ�������׮�������� --����ץס
//                                  b.  ����������--��ץ��ס
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
		   return x*t.y-y*t.x;      //��t����ߣ�������ֵ
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
		   A[i+1] = temp;  //������ֳ�����С�Ҵ��������
		   sort(A,left,i);//������߲���
		   sort(A,i+2,right);

	   
	   }


};

class Graham
{
public:
	int number;
	
	int find_boundary(datatype *A,int *B,int N)
	{
		int j=-1; //���͹�������һ����
		int tmp;//�����͹�ߵ����һ����
		B[++j] = 0;
		
	    for(int i=1;i<N;i++) //ɨ����͹��
		{ 
			
			    /*
				    �ڵѿ�������ϵ�ϵ�ɨ��˳���ǣ���-���ң���-����
					����A*(���)B��<0: B��A���ұ�  
					               =0: B��A����  (�ɹ���͹��)
								   >0: B��A�����(�ɹ���͹��)
				*/
			    if(j>0)
				{
					
				   while(j>0 && (A[B[j]]-A[B[j-1]]).det(A[i]-A[B[j]])<0) 
							j--;  //����͹����������һ���㣬ֱ���µ������
				}
					

				B[++j]=i; //�õ��ܹ���͹��
				cout<<"B["<<j<<"] = "<<B[j];
			 
		 }
		
		cout<<"down is OK"<<endl;
		/*
		  ��͹��ɨ��������ϵĵ��Ȼ��B[]��������ϵĵ�ΪA[N-1],������͹��ɨ���
		  A[N-2]��ʼ��
		*/
		for(int i=N-2;i>=0;i--) //ɨ����͹�� 
		{
		   
			    while((A[B[j]]-A[B[j-1]]).det(A[i]-A[B[j]])<0) //�µĵ���͹�����������������γɵıߵ��ұ�
                      j--;  //����͹����������һ���㣬ֱ���µ������

				B[++j]=i; //�µ���������͹������
				cout<<"B["<<j<<"] = "<<B[j];
			 
		 }
		cout<<"up is OK"<<endl;
		return j;//����͹������Ĵ�С
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
     ���ж��Ƿ�����׮��
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
   ��������׮�ϣ����ж��Ƿ���͹����͹����

*/
   if(flag==0) 
 {
   Point* y = sort.quicksort(x,PSIZE);  //quicksort(����������ĸ���)
   for(int i=0;i<PSIZE;i++)  //��ӡ�����մ����ң����µ��������ĵ�����
   {
      cout<<"i = "<<i; 
	  y[i].showXY(); 
   }
		
   Graham graham; // ����һ��graham����
   int convex[PSIZE],number; // convex[]:������͹�����ϵĵ����ţ���������ţ�
   number = graham.find_boundary(y,convex,PSIZE); //�õ�͹�����ϵĵ���
   cout<<"the Points number on boundary is "<<number<<endl;
   
   cout<<"the Points index on boundary is ";
  for(int i=0;i<number;i++)
  {
      
	  cout<<convex[i];
  }
  cout<<endl;
  //�����жϿ����Ƿ���͹����
  for(int i=0;i<number;i++)
  {
      if(y[convex[i]]==dinosaur) //��͹����
	  {
		 /*
		    ������Ҫ�ж��Ƿ���������׮�������� [0 , 1 ,2 ,3 ,...,number-1]
		 */
		  if(i==0)//��Ϊ�����ԭ�� ����������[0]�����򲻿�����������
		  {
		     cout<<"can't catch the dinosaur"<<endl;
		  }
		  else
		  {
		     if(y[convex[i]].ratio(y[convex[(i+1)%number]])==y[convex[i-1]].ratio(y[convex[i]]))//��б��һ��
				 cout<<"the dinosaur can be catched"<<endl;
			 else
                 cout<<"can't catch the dinosaur"<<endl;
		  }
		  
	    
		 break;
	  }
		  
	  if(i==number-1) //����͹����
		  cout<<"the dinosaur can be catched"<<endl;
  }

 }
  
}





