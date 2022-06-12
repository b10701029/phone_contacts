#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <string.h> 
class cms{
    char num[30],name[30],mail[30],address[30];
    public:
        void showMenu();
        void add(){
            cout << "Enter the number:" << endl;
            cin>>num;
            cout << "Enter the name:" << endl;
            cin>>name;
            cout << "Enter the mail:" << endl;
			cin>>mail;
            cout << "Enter the address:" << endl;
			cin>>address;
        }
        char* getName()
        {
    		return name;
    	}
    	char* getNumber()
        {
    		return num;
    	}
    	char* getAddress()
    	{
    		return address;
    	}
    	char* getMail()
    	{
    		return mail;
    	}
    	void save_contact();
    	void show_all_contacts();
    	void delete_a_contact();
    	void edit_contact();
    	void display_contact();
    	void clean_contact();
    	void call_contact();
    	void show_contact()
    	{
    		cout<<endl<<"Number: "<<num;
    		cout<<endl<<"Name: "<<name;
    		cout<<endl<<"Mail: "<<mail;
    		cout<<endl<<"Address: "<<address<<endl;
    		cout<<endl<<"=================================================\n"<<endl;
    	}
};
cms c;
fstream newFile;
void cms::save_contact(){
    newFile.open("Contact.txt", ios::out | ios::app);
    c.add();
    c.show_contact();
    newFile.write((char*)&c,sizeof(cms));
    newFile.close();
    cout<<endl<<"Contact has been created"<<endl;
}

void cms::display_contact()
{
	char num[30];
    cout<<"\tcontact number: ";
    cin>>num;
	bool found;
	newFile.open("Contact.txt",ios::in);
	while(newFile.read((char*)&c,sizeof(cms)))
	{
		if(strcmp(num,c.getNumber())==0) 
		{
			c.show_contact();
			found=true;
		}
	}
	newFile.close();
	if(found == false){
		cout<<endl<<endl<<"\tNo number found!!!"<<endl;
	}
}
void cms::showMenu()
{
    cout << "***Welcome to Contact Management System ***" << endl;
    cout << "MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "[1] Add a new Contact" << endl;
    cout << "[2] List all Contacts" << endl;
    cout << "[3] Search for Contact" << endl;
    cout << "[4] Edit a Contact" << endl;
    cout << "[5] Delete a Contact" << endl;
    cout << "[6] Delete all the Contact" << endl;
    cout << "[7] Call the Contact" << endl;
    cout << "[0] Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter the choice:" << endl;
}
void cms::show_all_contacts()
{
	bool found=false;
	cout<<"\t-------------------LIST OF CONTACTS-------------------"<<endl;
	newFile.open("Contact.txt",ios::in);
	while(newFile.read((char*)&c,sizeof(cms)))
	{
		c.show_contact();
		found=true;
	}
	newFile.close();
	if(found==false)
		cout<<endl<<endl<<"\tNo any contact!!!"<<endl;
}
void cms::edit_contact()
{
	char num[30];
	bool found=false;
	cout<<"Enter the number of contact to edit:";
    cin>>num;
	newFile.open("Contact.txt",ios::in|ios::out);
	while(newFile.read((char*)&c,sizeof(cms)) && found==false)
	{
		if(strcmp(num,c.getNumber())==0)
		{
			c.show_contact();
            cout<<"\nPlease enter the new details of contact: "<<endl;
			c.add();
			long unsigned int pos=-1*sizeof(c);
			newFile.seekp(pos,ios::cur);
			newFile.write((char*)&c,sizeof(cms));
			cout<<endl<<endl<<"\t Contact updated!!!"<<endl;
			found=true;
			break;
		}
	}
	newFile.close();
	if(found==false)
		cout<<endl<<endl<<"\tContact Not Found..."<<endl;
}

void cms::delete_a_contact()
{
	char num[30];
	cout<<endl<<"Please enter the number you want to delete: ";
	cin>>num;
	newFile.open("Contact.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Delete.txt",ios::out);
	newFile.seekg(0,ios::beg);
	while(newFile.read((char*)&c,sizeof(cms)))
	{
		if(strcmp(num,c.getNumber())!=0)
		{
			fp2.write((char*)&c,sizeof(cms));
		}
	}
	fp2.close();
	newFile.close();
	remove("Contact.txt");
	rename("Delete.txt","Contact.txt");
	cout<<endl<<endl<<"\tContact Deleted..."<<endl;
}
void cms::call_contact()
{
	int cc;
	char num[30];
	bool found=false;
	c.show_all_contacts();
	cout<<endl<<"Please enter the number you want to call: ";
	cin>>num;
	newFile.open("Contact.txt",ios::in|ios::out);
	while(newFile.read((char*)&c,sizeof(cms)) && found==false)
	{
		if(strcmp(num,c.getNumber())==0)
		{
			cout<<"\t     =     "<<endl;
			cout<<"\t    ===    "<<endl;
			cout<<"\t   =====   "<<endl;
			cout<<"\t  ======== "<<endl;
			cout<<"\t =========="<<endl;
			cout<<"\t Calling!!!"<<c.getName()<<endl;
			cout<<"\t =========="<<endl;
			cout<<"\t  ======== "<<endl;
			cout<<"\t   =====   "<<endl;
			cout<<"\t    ===    "<<endl;
			cout<<"\t     =     "<<endl;
			found=true;
			cout<<endl<<"Cancel Calling ==>>press number 1"<<endl;
			cin>>cc;
			if(cc==1) 
				break;	 
		}
	}
	if(found==false)
		cout<<endl<<endl<<"\tContact Not Found..."<<endl;
} 
void cms::clean_contact()
{
	newFile.open("Contact.txt", ofstream::out | ofstream::trunc);
	cout<<endl<<endl<<"\tIt is empty in here."<<endl;
	newFile.close();	
}
int main() {
    
    int select = 0;    
    while (true){
        c.showMenu();
        cout << "input number[]" << endl;
        cin >> select;      
        switch (select) {
                case 1:    
                    c.save_contact();
                    break;
                case 2:
                    c.show_all_contacts();
    		        break;    
                case 3:
        			c.display_contact();  
        			break;
        		case 4:
        		    c.edit_contact();
    		        break;
        		case 5:
        		    c.delete_a_contact();
    		        break;
				case 6:     
	                c.clean_contact();
	                break;	
				case 7:
					c.call_contact();
					break;	
                case 0:     
                    cout << "Thank you for using our service." << endl;
                    exit(0);    
                    return 0;
            }
    }
}

