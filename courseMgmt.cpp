#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

class Admin;
class Node;
int ctr=0;

class Criteria
{		int marksMin[2];
		int seats[2];
	public:
		void print();
		void set();
		friend void setCriteria( Criteria* C, Admin A);
		friend void updateSeats( Criteria* C, Node* N);
};

void Criteria::print()
{	cout<<"\n\t====================  ADMISSION CRITERIA  ===================\n";
	cout<<"\n\tSCIENCE STREAM\n";
	cout<<"\tCut-off: "<<marksMin[0]<<"%"<<endl;
	cout<<"\tNumber of seats available: "<<seats[0]<<endl;
	cout<<"\n\tCOMMERCE STREAM\n";
	cout<<"\tCut-off: "<<marksMin[1]<<"%"<<endl;
	cout<<"\tNumber of seats available: "<<seats[1]<<endl;
	cout<<"\n\t=============================================================\n";
}

void Criteria::set()
{	cout<<"\n\t=================  SET ADMISSION CRITERIA  ==================\n";
	cout<<"\nSCIENCE STREAM\n";
	cout<<"Enter the cut-off marks: ";
	cin>>marksMin[0];
	cout<<"Enter the number of seats: ";
	cin>>seats[0];
	cout<<"\nCOMMERCE STREAM\n";
	cout<<"Enter the cut-off marks: ";
	cin>>marksMin[1];
	cout<<"Enter the number of seats: ";
	cin>>seats[1];
	cout<<"\nCriteria successfully set!\n";
	ctr=1;
	cout<<"\n\t=============================================================\n";
}

class Admin
{		string username;
		string password;
	public:
		void setUserLogin();
		int validateLogin();
		friend void setCriteria( Criteria* C, Admin A);
};

void Admin::setUserLogin()
{	cout<<"\n\t==================  SET ADMIN CREDENTIALS  ==================\n";
	cout<<"\nEnter the username: ";
	cin>>username;
	cout<<"Enter the password: ";
	cin>>password;
	password.push_back('s');
	cout<<"Appended 's' at the end of password!\n";
	cout<<"\n\t=============================================================\n";
}

int Admin::validateLogin()
{	cout<<"\n\t=======================  ADMIN LOGIN  =======================\n";
	string uName, pass;
	int result=0;
	cout<<"\nEnter the username: ";
	cin>>uName;
	try
	{	if(uName.compare(username)==0)
		{	cout<<"Enter the password: ";
			cin>>pass;
			try
			{	if(pass.compare(password)==0)
					result=1;
				else 
					throw("Invalid password!");
			}
			catch(const char* msg2)
			{	cout<<endl<<msg2<<endl;
				cout<<"Login failed!\n";
			}
		}
		else
			throw("Username does not exist!!");
	}
	catch(const char* msg1)
	{	cout<<endl<<msg1<<endl;
		cout<<"Invalid Login Attempt!\n";
	}
	cout<<"\n\t=============================================================\n";
	return result;
}

void setCriteria( Criteria* C, Admin A)
{	//Set criteria and number of seats for each stream
	if(A.validateLogin()==1)
		C->set();
	else
		cout<<"\nUnable to set criteria and seats!\n";
}

class Student
{	protected:
		string name;
        	int marks[5];
        	int prefCode;
        	int stream;
        	//1 - Science, 2 - commerce
	public:
        	virtual void setStudent()=0;
        	void printStudent();
};      

void Student::printStudent()
{	cout<<"Name: "<<name<<endl;
    	cout<<"Marks in 5 subjects: ";
    	for(int i=0; i<5; i++)
        	cout<<marks[i]<<" ";
    	cout<<"\nThe preferred stream: ";
    	if(prefCode==1)  
        	cout<<"Science\n";
   	else
        	cout<<"Commerce\n";
	cout<<"The alloted stream is: ";
	if(stream==1)  
        	cout<<"Science\n";
    	else if(stream==2)
        	cout<<"Commerce\n";
    	else
        	cout<<"No stream alloted!\n";
    	cout<<endl;
}

class Node: public Student
{   public:
        int data;
        int left;
        int right;
        int height;
        int parent;
        void setStudent();
        Node();
	friend void updateSeats( Criteria* C, Node* N);
};

void Node::setStudent()
{	int i=0;
    	cout<<"Enter the name: ";
	cin>>name;
	cout<<"Enter the marks in 5 subjects: ";
	while(i<5)
    	{   try
	    {   cin>>marks[i];
	        if(marks[i]<0 || marks[i]>100)
	            throw("Marks must be in range 1-100!\n");
            else 
	           i++;
	           
	    }
	    catch(const char* msg)
	    {    cout<<endl<<msg<<endl; }
	    
    	}
	cout<<"\nStreams: 1. Science\t2. Commerce\n";
	cout<<"Enter the preferred stream: ";
	cin>>prefCode;
}

Node::Node()
{	left=-1; right=-1; height=1; parent=-1; 
	stream=-1; prefCode=-1;
	for(int i=0; i<5; i++)
		marks[i]=0;
	name="";
}

void updateSeats( Criteria* C, Node* N)
{	int total=0;
	for(int i=0; i<5; i++)
		total+=N->marks[i];
	float avg=total/5;
	cout<<"\nCut-off secured: "<<avg<<"%\n";
	switch(N->prefCode)
	{	case 1: if(avg>=C->marksMin[0])
			{	if(C->seats[0]>0)
				{	N->stream=1;
					C->seats[0]--;
				        cout<<"Science stream alloted!\n";
			        }
			        else
			            	cout<<"No seats left in science stream!\n";
			}
			else
			        cout<<"Cut-off not sufficient for science stream!\n";
			break;
		case 2: if(avg>=C->marksMin[1])
			{	if(C->seats[1]>0)
			        {   N->stream=2;
			    	    C->seats[1]--;
			    	    cout<<"Commerce stream alloted!\n";
			        }
			        else
			            cout<<"No seats left in commerce stream!\n";
			}
			else
			        cout<<"Cut-off not sufficient for commerce stream!\n";
			break;
	}
}

map<int,Node> AVLtree;
int N=0, p=-1, q=-1, root=0;
int rl,rr;
Admin A;
Criteria C;

void leftRot(int i,int a=1)
{	int temp=AVLtree[i].right;
	int p=AVLtree[i].parent;
    	AVLtree[i].parent=temp;
    	if(p!=-1)
    	{	if(a)
        		AVLtree[p].right=temp;
        	else   
        		AVLtree[p].left=temp;
        		AVLtree[temp].parent=p;
    	}
    	AVLtree[i].right=AVLtree[temp].left;
    	AVLtree[AVLtree[temp].left].parent=i;
    	AVLtree[temp].left=i;
    	AVLtree[i].height=1+max(AVLtree[AVLtree[i].left].height,AVLtree[AVLtree[i].right].height);
    	AVLtree[temp].height=1+max(AVLtree[AVLtree[temp].left].height,AVLtree[AVLtree[temp].right].height);     
    	if(i==root)
    	{	AVLtree[temp].parent=-1;
    		root=temp;        
    	}   
}

void rightRot(int i,int a =1)
{	int temp=AVLtree[i].left;
	int p=AVLtree[i].parent;  
    	AVLtree[i].parent=temp;
    	if(p!=-1)
    	{	if(a)
        		AVLtree[p].left=temp;
        	else
        		AVLtree[p].right=temp;
        		AVLtree[temp].parent=p;
    	}
    	AVLtree[i].left=AVLtree[temp].right;
    	AVLtree[AVLtree[temp].right].parent=i;
    	AVLtree[temp].right=i;
    	AVLtree[i].height=1+max(AVLtree[AVLtree[i].left].height,AVLtree[AVLtree[i].right].height);
    	AVLtree[temp].height=1+max(AVLtree[AVLtree[temp].left].height,AVLtree[AVLtree[temp].right].height);
    	if(i==root) 
    	{	AVLtree[temp].parent=-1;
    		root=temp;
    	}
}

void balance(int i)
{	int a,b;
    	if(i==-1)
    		return;
    	if((AVLtree[AVLtree[i].left].height-AVLtree[AVLtree[i].right].height)>1)
    	{	if(AVLtree[AVLtree[AVLtree[i].left].left].height>=AVLtree[AVLtree[AVLtree[i].left].right].height)
    			rightRot(i);
    		else 
    		{	leftRot(AVLtree[i].left,0);
    			rightRot(i);
        	}
    	}
    	else if(AVLtree[AVLtree[i].right].height-AVLtree[AVLtree[i].left].height>1)
    	{	if(AVLtree[AVLtree[AVLtree[i].right].right].height>=AVLtree[AVLtree[AVLtree[i].right].left].height)
    			leftRot(i);
    	else 
    	{	rightRot(AVLtree[i].right,0);
    		leftRot(i);
    	}
    }
}

int max(int a,int b) { return(a>b)?a:b; }

void  insert(int i,int key,int p,int c=-1)
{	if(AVLtree.size()<=1)
	{   Node r;
       	r.data=key;
        r.parent=p;
        r.setStudent();
	updateSeats(&C, &r);
        AVLtree.insert(pair<int,Node>(N,r));
        N++; 
        return;
    }
    if(i==-1)
    {	Node r;
    	r.data=key;
    	r.parent=p;
    	r.setStudent();
    	updateSeats(&C, &r);
    	AVLtree.insert(pair<int,Node>(N,r));
    	if(c==1)
        	AVLtree[p].left=N;
        else if(c==0)
        	AVLtree[p].right=N;
        else    
            root=N;
        N++;
        return;
    }
    if(key<AVLtree[i].data)
    	insert(AVLtree[i].left,key,i,1);
   	else if(key>AVLtree[i].data)
    	insert(AVLtree[i].right,key,i,0);
    else
    	cout<<"ID Already Exists!!"<<endl;
    	AVLtree[i].height=1+max(AVLtree[AVLtree[i].left].height,AVLtree[AVLtree[i].right].height);
    	balance(i);
}

void inOrder(int i)
{	if(i!=-1)
    	{	inOrder(AVLtree[i].left);
    		cout<<"ID: "<<AVLtree[i].data<<endl;
    		AVLtree[i].printStudent();
    		inOrder(AVLtree[i].right);
    	}
}

void preOrder(int i)
{	if(i!=-1)
   	{	cout<<AVLtree[i].data<<" ";
       		preOrder(AVLtree[i].left);        
       		preOrder(AVLtree[i].right);
   	}
}

void postOrder(int i)  
{	if(i!=-1)
   	{	postOrder(AVLtree[i].left);
       		postOrder(AVLtree[i].right);
       		cout<<AVLtree[i].data<< " ";
   	}
}

int main()
{	Node a;
	int ch=1, key, opt;
	a.data=-1;
	a.height=0;
    	AVLtree[-1]=a;	
    	cout<<"\t\t\tSCHOOL COURSE MANAGEMENT SYSTEM\n\n";
	do
	{	cout<<"\n\t======================  MAIN   MENU  =======================\n";
		cout<<"\n\t[1] SET ADMINISTRATOR CREDENTIALS (Administrator only)";
		cout<<"\n\t[2] CREATE ADMISSION  CRITERIA (Administrator only)";
		cout<<"\n\t[3] ENTER STUDENT'S DATA ";
		cout<<"\n\t[4] DISPLAY CRITERIA FOR SELECTION";
		cout<<"\n\t[5] DISPLAY ALL  STUDENT'S REGISTERED";
		cout<<"\n\t[6] QUIT";
		cout<<"\n\t=============================================================\n";
		cout<<"\n\nEnter your choice: ";
		cin>>opt;
		switch(opt)
		{	case 1: A.setUserLogin();
			    	break;
			case 2: setCriteria(&C, A);
				break;
			case 3: cout<<"\n\t====================  STUDENT DETAILS  ======================\n";
			        if(ctr==1)
			        {	cout<<"\nEnter Student ID: ";
                  	    		cin>>key;
                  	    		insert(root,key,-1);
			        }
			        else
			        	cout<<"\nCriteria not set! Can't admit students!\n";
                  		cout<<"\n\t=============================================================\n";
                  		break;
			case 4: C.print();
		    		break;
			case 5: cout<<"\n\t=====================  STUDENT'S LIST  ======================\n";
			        if(N==0)
			        	cout<<"\nThere are no students!\n";
			        else
			        {	cout<<"\nInOrder Traversal\n"<<endl;
                	    		inOrder(root);
			            	cout<<"\nPreOrder Traversal of IDs"<<endl<<"\t";
            		    		preOrder(root);
            		    		cout<<"\n\nPostOrder Traversal of IDs"<<endl<<"\t";
                	    		postOrder(root);
			        }
                		cout<<"\n\n\t=============================================================\n";
                		break;
			case 6: break;
			default:cout<<"Invalid choice!!\n";
				break;
		}
	}while(opt!=6);
	cout<<"\n\t=============================================================\n";
	cout<<"\n\t\t\t     END OF INTERACTION\n";
	cout<<"\n\t=============================================================\n";
	return 0;
}
