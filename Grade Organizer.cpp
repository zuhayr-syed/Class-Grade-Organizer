#include<iostream>
#include<fstream>
#include<string>

class Profile{ //variables
	int stud_num;
	char name[50];
	int math;
	int language;
	int science;
	int social_std;
	int health_gym;
	double avg_per;
	char L_grade;
	char sign;
	void calculate_grade();	//function to calculate_grade grade
public: //public functions
	void getdata();		//function to accept data from user to create student profile
	void showdata() const;	//function to show data of a student on screen
	void class_grades() const; //function to display all student's grades
	int show_num() const; //function to return student number
};
//SPECIFIC MENU OPTION FUNCTIONS
void add_student();	//write txhe record in binary file
void display_student(int);	//accept stud_num and read record from binary file
void edit_student(int);	//accept stud_num and update record of binary file
void remove_student(int);	//accept stud_num and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen
bool IsLoggedIn();

bool IsLoggedIn(){
	std::string username, password, un, pw;
	std::cout<<"\nPlease Login -->";
	std::cout<<"\nEnter User Name: "; std::cin>>username;
	std::cout<<"Enter Password: "; std::cin>>password;

	std::ifstream read("c:\\" + username + ".text");
	getline(read, un);
	getline(read, pw);

	if (un == username && pw == password){
		return true;
	}
	else{
		return false;
	}
}

void intro(){
	std::cout<<"\n\t|===========================|" <<std::endl;
	std::cout<<"\n\n\t\t  ELEMENTARY" <<std::endl;
	std::cout<<"\t\t  ----------";
	std::cout<<"\n\t\tSTUDENT GRADE" <<std::endl;
	std::cout<<"\t\t-------------";
	std::cout<<"\n\t\t  ORGANIZER" <<std::endl;
	std::cout<<"\t\t  ---------";
	std::cout<<"\n\n\n\t [Elementary School Teacher]" <<std::endl;
	std::cout<<"\t|===========================|";
	std::cout<<"\n\nEnter any key to continue..."<<std::endl;
	std::cin.get();
}

void Profile::calculate_grade(){
	avg_per=(math+language+science+social_std+health_gym)/5.0;
	if(avg_per>=90){
		L_grade='A';
		sign='+';
	}
	else if(avg_per>=85){
		L_grade='A';
		sign=' ';
	}
	else if(avg_per>=80){
		L_grade='A';
		sign='-';
	}
	else if(avg_per>=77){
		L_grade='B';
		sign='+';
	}
	else if(avg_per>=73){
		L_grade='B';
		sign=' ';
	}
	else if(avg_per>=70){
		L_grade='B';
		sign='-';
	}
	else if(avg_per>=65){
		L_grade='C';
		sign='+';
	}
	else if(avg_per>=60){
		L_grade='C';
		sign=' ';
	}
	else if(avg_per>=55){
		L_grade='C';
		sign='-';
	}
	else if(avg_per>=50){
		L_grade='D';
		sign=' ';
	}
	else{
		L_grade='F';
		sign=' ';
	}
}

void Profile::getdata(){
	std::cout<<std::endl;
	std::cout<<"\n Student Number (OEN #): ";
	std::cin>>stud_num;
	std::cout<<"\n Student Name: ";
	std::cin.ignore(); //to avoid non-stop loop (stops program to allow user to enter name)
	std::cin.getline(name,20); //to read string name
	std::cout<<"\n Mathematics Grade: ";
	std::cin>>math;
	std::cout<<"\n Language Grade: ";
	std::cin>>language;
	std::cout<<"\n Science Grade: ";
	std::cin>>science;
	std::cout<<"\n Social Studies Grade: ";
	std::cin>>social_std;
	std::cout<<"\n Health/Physical Education Grade: ";
	std::cin>>health_gym;
	calculate_grade();
}

void Profile::showdata() const{
	std::cout<<"\n\t Student Number (OEN #): "<<stud_num;
	std::cout<<"\n\t ----------------------";
	std::cout<<"\n\t Student Name: "<<name;
	std::cout<<"\n\t ------------";
	std::cout<<"\n\t Mathematics Grade: "<<math<<"%";
	std::cout<<"\n\t -----------------";
	std::cout<<"\n\t Language Grade: "<<language<<"%";
	std::cout<<"\n\t --------------";
	std::cout<<"\n\t Science Grade: "<<science<<"%";
	std::cout<<"\n\t -------------";
	std::cout<<"\n\t Social Studies Grade: "<<social_std<<"%";
	std::cout<<"\n\t --------------------";
	std::cout<<"\n\t Health/Physical Education Grade: "<<health_gym<<"%";
	std::cout<<"\n\t -------------------------------";
	std::cout<<"\n\t Overall Average (Percentage): "<<avg_per<<"%";
	std::cout<<"\n\t ----------------------------";
	std::cout<<"\n\t Overall Average (Letter): "<<L_grade;
	std::cout<<"\n\t ------------------------";
}

void Profile::class_grades() const{
	std::cout<<stud_num<<"      "<<name<<"\n\t\t\t\t    "<<math<<"%"<<"     "<<language<<"%"<<"    "<<science<<"%"<<"     "
			<<social_std<<"%"<<"       "<<health_gym<<"%"<<"       "<<avg_per<<"%"<<"       "<<L_grade<<sign<<std::endl;
	std::cout<<"--------------------------------------------------------------------------------------------------"<<std::endl;
}

int  Profile::show_num() const{
	return stud_num;
}

void add_student(){
	Profile st; //creates object
	std::ofstream outFile; //creates and writes to file
	outFile.open("student.dat",std::ios::binary|std::ios::app); //accesses file, opens in binary mode, all output operations are performed at the end of file
	st.getdata(); //get the current data in file
	outFile.write(reinterpret_cast<char *> (&st), sizeof(Profile)); //create binary output in file
	outFile.close(); //close file
	std::cout<<"\n\n--> Student record Has Been Created <--";
	std::cout<<"\n\n\nEnter any key to continue..."<<std::endl;
	std::cin.ignore();
	std::cin.get();
}

void display_student(int find){
	Profile st;
	std::ifstream inFile; //reads from file
	inFile.open("student.dat",std::ios::binary); //open file in binary mode
	if(!inFile){ //if there is no file
		std::cout<<"*** There is no database created *** "<<std::endl<<"Press any key to continue...";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	bool flag=false; //start loop
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Profile))){ //runs loop to go through each student
		if(st.show_num()== find){ //if the student number from user matches to a student number in the file
			st.showdata(); //display that student's data
			flag=true; //end loop
		}
	}
	inFile.close(); //close file
	if(flag==false){ //if no matches of the student number were found in the while loop
		std::cout<<"\n\n** There is no student with this number in the database ***";
	}
	std::cout<<"\n\nEnter any key to continue..."<<std::endl;
	std::cin.ignore();
	std::cin.get();
}

void edit_student(int n){
	bool found=false; //set false
	Profile st;
	std::fstream File; //creates, reads, and writes to the file
	File.open("student.dat",std::ios::binary|std::ios::in|std::ios::out); //opens the file in binary format to: read input, write output
	if(!File){ //if there is no file
		std::cout<<"*** There is no database created *** "<<std::endl<<"Press any key to continue...";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	while(!File.eof() && found==false){ //end of file function to run the while loop (avoids error by attempting to get input past the end of file)
		File.read(reinterpret_cast<char *> (&st), sizeof(Profile)); //searches through each student number in the file
		if(st.show_num()==n) //if the student number from input matches to one in the file
		{
			st.showdata(); //display previous data
			std::cout<<"\n\n--> Update Student Information"<<std::endl;
			st.getdata(); //call getdata() function to ask user for new information
			int pos=(-1)*static_cast<int>(sizeof(st)); //assigning value of negative position
			File.seekp(pos,std::ios::cur); //member function to reposition the file-position pointer by int pos
			File.write(reinterpret_cast<char *> (&st), sizeof(Profile)); //write the binary data into file (replace)
			std::cout<<"\n\n--> Student Information Has Been Updated";
			std::cout<<"\n\n\nEnter any key to continue..."<<std::endl;
			found=true; //end loop
		}
	}
	File.close(); //close the file
	if(found==false){ //if there is no file
		std::cout<<"\n\n Record Not Found ";
	}
	std::cin.ignore();
	std::cin.get();
}

void remove_student(int n){
	Profile st;
	std::ifstream inFile; //reads from file
	inFile.open("student.dat",std::ios::binary); //open file in binary format
	if(!inFile){ //if there is no file found
		std::cout<<"*** There is no database created *** "<<std::endl<<"Press any key to continue...";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	std::ofstream outFile; //creates and writes to file
	outFile.open("Temp.dat",std::ios::out); //create a new temporary file to write output
	inFile.seekg(0,std::ios::beg); //to grab certain data from normal file starting with the beginning position set at 0
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Profile))){ //runs loop to go through each student
		if(st.show_num()!=n){ //if the student number from user does not match to a student number in the file
			outFile.write(reinterpret_cast<char *> (&st), sizeof(Profile)); //write the data in the file
		}
	}
	outFile.close(); //close file
	inFile.close(); //close file
	remove("student.dat"); //delete old file
	rename("Temp.dat","student.dat"); //rename the new file to the previous name
	std::cout<<"\n\n--> Student Has Been Removed";
	std::cout<<"\n\n\nEnter any key to continue..."<<std::endl;
	std::cin.ignore();
	std::cin.get();
}

void class_result(){
	Profile st;
	std::ifstream inFile; //reads from file
	inFile.open("student.dat",std::ios::binary); //open file in binary format
	if(!inFile){ //if there is no file found
		std::cout<<"*** There is no database created *** "<<std::endl<<"Press any key to continue...";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	std::cout<<"\n\n\t\t\t\t\t~~ CLASS GRADES ~~"<<std::endl;
	std::cout<<"==================================================================================================\n";
	std::cout<<"Std.No         Full Name            Math    Lang    Sci    S.Std    Phy.Ed    Avg (%)    Avg (L)"<<std::endl;
	std::cout<<"==================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Profile))){ //runs loop to go through each student
		st.class_grades(); //calls function to list the data at the certain position (lists each student's information in the file)
	}
	std::cout<<"\n\nEnter any key to continue..."<<std::endl;
	std::cin.ignore();
	std::cin.get();
	inFile.close(); //closes the file
}

void result(){
	char ch;
	int rno;
	std::cout<<"\n\n\nSHOW RESULTS";
	std::cout<<"\n------------";
	std::cout<<"\n1. Class Grades";
	std::cout<<"\n\n2. Student Grades";
	std::cout<<"\n\n3. Return to Options";
	std::cout<<"\n\n\nEnter 1-3: ";
	std::cin>>ch;
	switch(ch){ //statement to select one of the many code blocks to be executed depending on user input
	case '1' :
		class_result();
		break;
	case '2' :
		std::cout<<"\n\n\tEnter Student Number (OEN #): ";
		std::cin>>rno;
		display_student(rno); //executes function using the user input
		break;
	case '3' :
		break;
	}
}

void entry_menu(){
	char ch;
	int num;
	std::cout<<"\n\n\nSTUDENT MENU";
	std::cout<<"\n------------";
	std::cout<<"\n1. Add Student";
	std::cout<<"\n\n2. Re-enter Student Information";
	std::cout<<"\n\n3. Remove Student";
	std::cout<<"\n\n4. Return to Options";
	std::cout<<"\n\n\nEnter 1-4: ";
	std::cin>>ch;
	switch(ch){ //statement to select one of the many code blocks to be executed depending on user input
	case '1':
		add_student();
		break;
	case '2':
		std::cout<<"\n\n\tEnter Student Number (OEN #): ";
		std::cin>>num;
		edit_student(num); //executes function using the user input
		break;
	case '3':
		std::cout<<"\n\n\tEnter Student Number (OEN #): ";
		std::cin>>num;
		remove_student(num); //executes function using the user input
		break;
	case '4':
		break;
	}
}

int main(){
	intro(); //show introduction
	//START of login system
	int choice;
	std::cout<< "\n\n\t~~ LOGIN SYSTEM ~~"<<std::endl;
	std::cout<<"1: Register\n2: Login\n\n      Choose Option 1-2: "; std::cin>> choice;
	if (choice == 1){
		std::string username, password; //to take user input
		std::cout<< "\n\n\tSelect A User Name: "; std::cin>>username;
		std::cout<< "\tSelect A Password: "; std::cin>>password;
		std::ofstream file; //represents output file stream and is used to create file and write information to the file
		file.open("c:\\" + username + ".text"); //opens a file using the user's input
		file << username << std::endl << password; //stores information in file
		file.close(); //closes file
		std::cout<<"--> Account successfully created <--\n\n"<<std::endl;
		main(); //restarts program so user can login
	}
	else if (choice == 2){
		int loginAttempt = 0;
		while (loginAttempt < 5){
			bool status = IsLoggedIn(); //calls login function to return either true or false
			if (!status){ //if login is incorrect
				++loginAttempt; //adds to login counter
				std::cout << "\n\nIncorrect Login - your user name/password was incorrect" <<std::endl;
				std::cout<<"Try Again ("<<loginAttempt<<"/5 attempts used)"<<std::endl<<std::endl; //displays number of tries remaining to user
			}
			else{ //if login is successful
				std::cout << "\n* Successfully Logged In *";
				break;
			}
		}
		if (loginAttempt == 5){ //if user reaches maximum number of login attempts
			std::cout << "Too many attempts! Program will now terminate.";
			return 0;
		}
	}
	else{ //if user does not pick any option, starts program again
		std::cout<<"\n\n--> None of the Options Were Selected <--"<<std::endl;
		std::cout<<"\n\n\nEnter any key to try again...\n"<<std::endl;
		std::cin.ignore();
		std::cin.get();
		main();
	}
	//END of login system
	char ch;
	std::cout.setf(std::ios::fixed|std::ios::showpoint); //function sets the decimal places in program by printing floats with a...
														//fixed number of decimals and controlling the trailing zeros (for average calculation)
	std::cout.precision(1); // program outputs decimal number to one decimal place
	do{ //run as long as user input is not 3
		std::cout<<"\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		std::cout<<"\n\n\t\tPROGRAM OPTIONS";
		std::cout<<"\n\n\t1. SHOW RESULTS";
		std::cout<<"\n\n\t2. STUDENT MENU";
		std::cout<<"\n\n\t3. LEAVE";
		std::cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
		std::cout<<"\n\tEnter Option 1-3: ";
		std::cin>>ch;
		switch(ch){ //statement to select one of the many code blocks to be executed depending on user input
		case '1':
			result();
			break;
		case '2':
			entry_menu();
			break;
		case '3':
			std::cout << "\n\n*** Program Terminated ***" <<std::endl;
			break;
		}
	}while(ch!='3');
	return 0;
}
