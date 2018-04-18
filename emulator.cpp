#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include<math.h>
using namespace std;
    int memory[65536]; //16 bit for memory ,range0-65536
    map<int,string> prog;
    map<int,string> mem2;
    map<char,int>::iterator itr;
    map<char,int>::iterator itr2;
    map<char,int> reg;
    bool f[8];
    int m;
    int s,b,i;
     int validM(int mmry)  //to check the valid memory location
     {
         if(mmry>=0&&mmry<=65535)
            return 5;
         else
            return 0;
     }
    int todec(string ab)  //conversion of register value into decimal
 {
     int len=ab.length()-1;
     int a=0,i=0,val=0;
     while(len>=0)
     {
         if(ab[len]>=65)
         {
             val=ab[len]-55;
         }
         else
         {
             val=ab[len]-48;
         }
         a=a+(pow(16,i)*val);
         len--;i++;
     }
     return a;
 }
string tohex(int decN)  //hex conversion of decimal
{
int temp,rem,q = decN;
int i=1,j;
string hexN="";
int t=(decN>255)?4:2;
while(t!=0)
{
temp = q % 16;
//To convert integer into character
if( temp < 10)
temp =temp + 48;
else
temp = temp + 55;
hexN=char(temp)+hexN;
q = q / 16;
t=t-1;
}
return hexN;
}
string tohex2(int decN)
{
int temp,rem,q = decN;
int i=1,j;
string hexN="";
int t=4;
while(t!=0)
{
temp = q % 16;
//To convert integer into character
if( temp < 10)
temp =temp + 48;
else
temp = temp + 55;
hexN=char(temp)+hexN;
q = q / 16;
t=t-1;
}
return hexN;
}
int operand_find(string str)  //to match the operand
 {
        if(str=="MOV")
        {
        return 0;
        }
        else if(str=="STAX")
        {
            return 1;
        }
        else if(str=="XCHG")
        {
            return 2;
        }
        else if(str=="ADD")
        {
            return 3;
        }
        else if(str=="DCR")
        {
            return 4;
        }
        else if(str=="INX")
        {
            return 5;
        }
        else if(str=="CMA")
        {
            return 6;
        }
        else if(str=="CMP")
        {
            return 7;
        }
        else if(str=="DAD")
        {
            return 8;
        }
        else if(str=="SUB")
        {
            return 9;
        }
        else if(str=="MVI")
        return 10;
        else if(str=="ADI")
        return 11;
        else if(str=="SUI")
        return 12;
        else if(str=="INR")
            return 13;
        else if(str=="DCX")
            return 14;
        else if(str=="LDA")
        return 20;
        else if(str=="LHLD")
        return 21;
        else if(str=="STA")
        return 22;
        else if(str=="LXI")
        return 23;
        else if(str=="JMP")
        return 25;
        else if(str=="SHLD")
        return 24;
        else if(str=="JC")
        return 26;
        else if(str=="JNC")
        return 27;
        else if(str=="JZ")
        return 28;
        else if(str=="JNZ")
        return 29;
        else if(str=="SET")
        return 30;
        else if(str=="HLT")
        return 31;
        else
        return -1;
 }
void fswap(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}
int val(string str)
{
    int mi;
    int p=str.find(" ",0);
    str=str.substr(0,p);
    int i=operand_find(str);
    if(i==13||i==14)
    {
        mi=1;
    }
    else
        mi=i/10+1;
        return mi;
}
void pii()  //to show the register values
    {
        map<int,string>::iterator mtr;
        for(mtr=prog.begin();mtr!=prog.end();mtr++)
            cout<<tohex2(mtr->first)<<":"<<mtr->second<<endl;

    }
 void work()
 {
        map<int,string>::iterator itr9;
        map<char,int>::iterator itra;
        itr9=prog.find(m);
        string str=itr9->second;
        int p = str.find(" ", 0);
        string str1=str.substr(0,p);
        string str2;
        int op=operand_find(str1);
        map<char,int>::iterator itr3;

        map<char,int>::iterator itr4;
        i++;
        if(op==-1)
        {

            cout<<"COMMAND IS INVALID!!!"<<endl;
            exit(0);
        }
        else if(op==0)
        {
            str2=str.substr(p+1,str.length());
            itr=reg.find(str2[0]);
            itr2=reg.find(str2[2]);
            if(itr==reg.end()||itr2==reg.end())
            {
                cout<<"**INVALID operand**";
                exit(0);
            }
            itr->second=itr2->second;
        }
        else if(op==1)
        {
            str2=str.substr(p+1,str.length());
            itr=reg.find(str2[0]);
            itr2=reg.find(str2[0]+1);
            string mem=tohex(itr->second)+tohex(itr2->second);
            int no=todec(mem);
            itr3=reg.find('A');
            memory[no]=itr3->second;
        }
        else if(op==2)
        {itr=reg.find('D');
        itr2=reg.find('E');
        itr3=reg.find('H');
        itr4=reg.find('L');
        fswap(itr->second,itr3->second);
        fswap(itr2->second,itr4->second);
        }
        else if(op==3)
        {
            itr=reg.find('A');
            itr2=reg.find(str[p+1]);
            if(itr2==reg.end())
            {
                cout<<"**INVALID operand**";
                exit(0);
            }
            itr->second=itr->second+itr2->second;
            if(itr->second==0)
                f[6]=true;
            if((itr->second)>=256)
            {
                itr->second=itr->second%256;
                f[0]=true;
                f[7]=true;
            }
        }
        else if(op==4)
        {
            itr=reg.find(str[p+1]);
            if(itr==reg.end())
            {
                cout<<"**INVALID operand**";
                exit(0);
            }
            itr->second=itr->second-1;
            if(itr->second==0)
                f[6]=true;
        }
        else if(op==5)
        {
            string tmp;
            itra=reg.find(str[p+1]+1);
            tmp=tohex(itra->second);
            itr=reg.find(str[p+1]);
            tmp=tohex(itr->second)+tmp;
            int tem=todec(tmp);
            tem=tem+1;
            if((tem)>65535)
            {
		f[0]=true;
		f[4]=true;
                itra->second=0;
                itr->second=0;
            }
        }
        else if(op==6)
        {
            itr=reg.find('A');
            //if(itr->second<128)
            {
                itr->second=255-itr->second;

            }

        }
        else if(op==7)
        {
            itr=reg.find('A');
            itr2=reg.find(str[p+1]);
            if(itr->second<itr2->second)
            {
                f[0]=true;
            }
            else if(itr->second==itr2->second)
            {
                f[6]=true;
            }
            else
            {
                f[0]=false;
                f[6]=false;
            }
        }
        else if(op==8)
        {
        itr=reg.find(str[p+1]);
        itr2=reg.find(str[p+1]+1);
        itr3=reg.find('H');
        itr4=reg.find('L');
        string mem1=tohex(itr->second)+tohex(itr2->second);
        string mem2=tohex(itr3->second)+tohex(itr4->second);
	int res;
	res=todec(mem1)+todec(mem2);
        if(itr2->second+itr4->second>128)
        {
            f[4]=true;
        }
	if(res>65535)
	{
	res=res%65536;
	f[0]=true;
	}
	itr3->second=res/256;
	itr4->second=res%256;
	}
        else if(op==9)
        {
            itr=reg.find('A');
            itr2=reg.find(str[p+1]);
            itr->second=itr->second-itr2->second;
            if(itr->second==0)
                f[6]=true;

            if((itr->second)<0)
            {
                itr->second=256+itr->second;
                f[0]=true;
                f[7]=true;
            }
            else
                f[0]=false;

        }
        else if(op==10)
        {
            char op=str[p+1];
            int com=str.find(",",0);
            string st1=str.substr(com+1,com+3);
            itr=reg.find(op);
            itr->second=todec(st1);
        }
        else if(op==11)
        {
            string st1=str.substr(p+1,str.length());
            itr=reg.find('A');
            itr->second=itr->second+todec(st1);
            if(itr->second==0)
                f[6]=true;
            if((itr->second)>=256)
            {
                itr->second=itr->second%256;
                f[0]=true;
            }

        }
        else if(op==12)
        {
            string st1=str.substr(p+1,str.length());
            itr=reg.find('A');
            itr->second=itr->second-todec(st1);
            if((itr->second==0))
                f[6]=true;
            if((itr->second)<0)
            {
                itr->second=256+itr->second;
                f[0]=true;
                f[7]=true;
            }

        }
        else if(op==13)
        {
            itr=reg.find(str[p+1]);
            itr->second=itr->second+1;
            if((itr->second)>=256)
            {
                itr->second=itr->second%256;
            }

        }
      else if(op==14)
        {
            string tmp;
            itra=reg.find(str[p+1]+1);
            tmp=tohex(itra->second);
            itr=reg.find(str[p+1]);
            tmp=tohex(itr->second)+tmp;
            int tem=todec(tmp);
            tem=tem-1;
            if((tem)<0)
            {
                itra->second=256-itra->second;
                itr->second=256-itr->second;
            }

        }
        else if(op==20)
        {
            itr=reg.find('A');
            int com=str.find(" ",0);
            string st=str.substr(com+1,str.length());
            int fl=validM(todec(st));
            if(fl==0)
            {
                cout<<"**invalid memory";
                exit(0);
            }
            itr->second=memory[todec(st)];
        }
        else if(op==21)
        {
            string st=str.substr(p+1,str.length());
            int fl=validM(todec(st));
            if(fl==0)
            {
                cout<<"**invalid memory";
                exit(0);
            }

            itr=reg.find('H');
            itr2=reg.find('L');
            itr->second=memory[todec(st)];
            itr2->second=memory[todec(st)+1];
        }
        else if(op==22)
        {
            itr=reg.find('A');
            int com=str.find(" ",0);
            string st=str.substr(com+1,str.length());
            int fl=validM(todec(st));
            if(fl==0)
            {
                cout<<"**invalid memory";
                exit(0);
            }
            memory[todec(st)]=itr->second;

        }
        else if(op==23)
        {
            int po=str.find(",",0);
            string st=str.substr(po+1,str.length());
            int fl=validM(todec(st));
            if(fl==0)
            {
                cout<<"**invalid memory";
                exit(0);
            }
            itr=reg.find(str[p+1]);
            itr2=reg.find(str[p+1]+1);
            itr->second=todec(st)/256;
            itr2->second=todec(st)%256;
        }
        else if(op==24)
        {
            string st=str.substr(p+1,str.length());
            int fl=validM(todec(st));
            if(fl==0)
            {
                cout<<"**invalid memory";
                exit(0);
            }
            itr=reg.find('H');
            itr2=reg.find('L');
            memory[todec(st)]=itr->second;
            memory[todec(st)+1]=itr2->second;

        }
        else if(op==25)
        {
                string st=str.substr(p+1,str.length());
                int temp=todec(st);
                m=temp;
        }
        else if(op==26)
        {
            string st=str.substr(p+1,str.length());
            int tem=todec(st);
            if(f[0]==1)
            {
                m=tem;
            }
            else
                m=m+val(str);
        }
        else if(op==27)
        {
            string st=str.substr(p+1,str.length());
            int tem=todec(st);
            if(f[0]==0)
            {
                m=tem;
            }
            else
                m=m+val(str);
        }
        else if(op==28)
        {
            string st=str.substr(p+1,str.length());
            int tem=todec(st);
            if(f[6]==1)
            {
                m=tem;
            }
            else
                m=m+val(str);
        }
        else if(op==29)
        {
            string st=str.substr(p+1,str.length());
            int tem=todec(st);
            if(f[6]==0)
            {
                m=tem;
            }
            else
                m=m+val(str);
        }
        else if(op==30)
        {
            string st=str.substr(p+1,str.length());
            int op=st.find(",",0);
            string st1=st.substr(0,op);
            string st2=st.substr(op+1,st.length());
            memory[todec(st1)]=todec(st2);
        }
        else if(op==31)
        {
            return;
        }
        if(!(op>=25&&op<30))
        {m=m+val(str);}
        else if(s==0&&!(op>=25&&op<30))
        {
            m=m+val(str);

        }
        if(s==0&&b>=i){
            work();
        }


    }
    void print()
    {
    cout<<"\n****OUTPUT****\n"<<endl;
    map<char,int>::iterator itr100;
    for(itr100=reg.begin();itr100!=reg.end();itr100++)
    {
        cout<<itr100->first<<" :"<<tohex(itr100->second)<<endl;
    }
    int ak;
    for(ak=1000;ak<65536;ak++)
    {
        if(memory[ak]!=0)
        {
            cout<<tohex2(ak)<<":"<<tohex(memory[ak])<<endl;
        }
    }
    cout<<"C"<<"    "<<"P"<<"   "<<"AC"<<"  "<<"Z"<<"   "<<"S"<<"    "<<endl;
    cout<<f[0]<<"    "<<f[2]<<"   "<<f[4]<<"  "<<f[6]<<"   "<<f[7]<<"    "<<endl;
    }

int main(int argc,char *argv[])
{
    int l=0;
    string str;int mi=0;m=0,s=0;
    for(i=65;i<70;i++)
    {
        reg.insert(pair<char,int>(i,0));
    }
    reg.insert(pair<char,int>('H',0));
    reg.insert(pair<char,int>('L',0));
    if(argc==2)
     {
        std::ifstream input(argv[1]);
        if(!input)
        {
          cout<<"**FILE NOT FOUND**";
           exit(0);
        }
		for( std::string line; getline( input, line ); )
        {
        i=0;l++;
        transform(line.begin(),line.end(),line.begin(), ::toupper);
        prog.insert(pair<int,string>(mi,line));
        mi+=val(line);
        }
     }
     else
      {
          cout<<"INPUT THE PROGRAM "<<endl;
       do{
         getline(cin,str);
         i=0;
         l++;
         transform(str.begin(),str.end(),str.begin(), ::toupper);
         prog.insert(pair<int,string>(mi,str));
         mi+=val(str);
         }while(str!="HLT");
      }
      pii();
      int choice;
      cout<<"\n\n1 for all,\n2 for breakpoint,\n3 for step by step\n4 to print at valid loc\n5 to execute\n enter choice  :";
      do
        {

        cin>>choice;
        if(choice==1)
        {
            b=l;
        }
        else if(choice==2)
        {
            cout<<"enter break point : ";
            cin>>b;
        }
        else if(choice==3)
        {
            s=1;
            print();
        }
        else if(choice==4)
        {
            string vv;
            cin>>vv;
            cout<<vv<<":"<<memory[todec(vv)]<<endl;
        }
        else if(choice==5)
        {
            cout<<"THANK YOU"<<endl;
        }

        if(choice<=3)
        work();
        }while(choice!=5);
        print();
return 0;
}
