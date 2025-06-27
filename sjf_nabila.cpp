#include<iostream>

using namespace std;



int main()
{
      int n,temp,timer=0,min,d,i,j;
      float avgtat=0,avgwt=0,sumtat=0,sumwt=0;

      cout<<"enter no of process"<<endl;
      cin>>n;
      int a[n],b[n],e[n],tat[n],wt[n];

      cout<<"enter arrival times ";
      for(i=0;i<n;i++)
      {
            cin>>a[i];
      }
      cout<<"enter CPU times ";
      for(i=0;i<n;i++)
      {
            cin>>b[i];
      }
      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(b[i]>b[j])
                {
                      temp=a[i];
                      a[i]=a[j];
                      a[j]=temp;

                      temp=b[i];
                      b[i]=b[j];
                      b[j]=temp;
                }
          }
      }
      min=a[0];
      for(i=0;i<n;i++)
      {
            if(min>a[i])
            {
                  min=a[i];
                  d=i;
            }
      }
      timer=min;
      e[d]=timer+b[d];
      timer=e[d];

      for(i=0;i<n;i++)
      {
            if(a[i]!=min)
            {
                  e[i]=b[i]+timer;
                  timer=e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=e[i]-a[i];
            sumtat=sumtat+tat[i];
            wt[i]=tat[i]-b[i];
            sumwt=sumwt+wt[i];
      }
      avgtat=sumtat/n;
      avgwt=sumwt/n;
      cout<<"Process     Waiting-time     Turnaround-time  \n";

    for(i=0;i<n;i++)
    {
    cout<<"P"<<i+1<<"                "<<wt[i]<<"                 "<<tat[i]<<endl;
    }

    cout<<"/n average waiting time: "<<avgwt<< endl;
    cout<<" average turnaround time: "<<avgtat << endl;
}
