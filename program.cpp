#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <istream>
#include <cmath>

using namespace std;

// Global Constant Variables (For Risk Calucaltion)
// Age Brakets (For Risk Calucaltion)
const int FirstAgeBracketCeiling = 34;
const int SecondAgeBracketCeiling = 39;
const int ThirdAgeBracketCeiling = 44;
const int FourthAgeBracketCeiling = 49;
const int FifthAgeBracketCeiling = 54;
const int SixthAgeBracketCeiling = 59;
const int SeventhAgeBracketCeiling = 64;
const int EighthAgeBracketCeiling = 69;
const int NinthAgeBracketCeiling = 74;
// Cholestrol Backets (For Risk Calucaltion)
const int FirstCholBracketCeiling = 160;
const int SecondCholBracketCeiling = 199;
const int ThirdCholBracketCeiling = 239;
const int FourthCholBracketCeiling = 279;
// HDL Brackets (For Risk Calucaltion)
const int FirstHDLBracketCeiling = 60;
const int SecondHDLBracketCeiling = 50;
const int ThirdHDLBracketCeiling = 40;
// SBP Brackets (For Risk Calucaltion)
const int FirstSBPBracketCeiling = 120;
const int SecondSBPBracketCeiling = 129;
const int ThirdSBPBracketCeiling = 139;
const int FourthSBPBracketCeiling = 159;


// Stand Alone Function Prototypes:
char displayMenu();


// Beginning of FactorSet Class.
// This class stores all the risk factor varaibles and related functions.
class FactorSet
{

    private:
    // All risk factor variables as private attributes
    char gender;
    double age;
    double chole;
    double hdl;
    double sbp;
    char hyperTest;
    char smoker;

    // Public Functions Start Here:
    public:

    // Setting up the next pointer attribute for linked list.
    FactorSet * next;

    // Defining the Accessor "Get" functions to access private attributes.
    char getGender() const      {return gender;}
    double getAge() const       {return age;}
    double getChole() const     {return chole;}
    double getHDL() const       {return hdl;}
    double getSBP() const       {return sbp;}
    char getHyperTest() const   {return hyperTest;}
    char getSmoker() const      {return smoker;}

    // Defining Mutator "Set" functions to set private variables.
    void setGender  (char inputGender)      {gender = inputGender;}
    void setAge (double inputAge)           {age = inputAge;}
    void setChole (double inputChole)       {chole = inputChole;}
    void setHDL (double inputHDL)           {hdl = inputHDL;}
    void setSBP (double inputSBP)           {sbp = inputSBP;}
    void setHyperTest (char inputHyper)     {hyperTest = inputHyper;}
    void setSmoker (char inputSmoker)       {smoker = inputSmoker;}

    // Default Contructor
    FactorSet();

    // The main Conctructor that takes the risk variables and makes them isntance attributes.
    FactorSet(char inputGen, int inputAge, double inputChole, double inputHDL, double inputSBP, char inputHyperTest, char inputSmoker);

    // Copy Constructor here:
    FactorSet(const FactorSet &set);

    // Calculate Risk function that takes constant reference and computes the risk.
    // It is just a function (and not a stored attribute) to avoid stale data.
    double calRisk(const FactorSet &) const;

    // Overloading the Assignment Operator.
    FactorSet& operator=(const FactorSet &right);

    // The stream operator is set as friend, so it can access private attributes
    friend ostream &operator<<(ostream& out, const FactorSet &set);

};

// FactorSet Defintions Start Here:
// NOTE: The only method (of either FactorSet or NodeList) not defined immidiately after the class
// is the calRisk function. The calRisk was excessively long, so I moved it the very bottom to avoid
// taking up to much space.

// Default Constructor sets calues to 0 or Null Character
FactorSet::FactorSet()
{
    gender = '\0';
    age = 0;
    chole = 0;
    hdl = 0;
    sbp = 0;
    hyperTest = '\0';
    smoker = '\0';
}

// This is the main constructor that is always used to push risk factors into a FactorSet instance.
FactorSet::FactorSet(char inputGen, int inputAge, double inputChole, double inputHDL, double inputSBP, char inputHyperTest, char inputSmoker)
{
    setGender(inputGen);
    setAge(inputAge);
    setChole(inputChole);
    setHDL(inputHDL);
    setSBP(inputSBP);
    setHyperTest(inputHyperTest);
    setSmoker(inputSmoker);

    // Next set to NULL since each created is at the end of the list
    next = NULL;
}

// Copy Constructor
FactorSet::FactorSet(const FactorSet &set)
{
    // First checking if the instances (operands) are the same.
    if (this != &set)
    {
    // Setting all the risk factors equal using the accessor and mutator functions.
    this->setGender(set.getGender());
    this->setAge(set.getAge());
    this->setChole(set.getChole());
    this->setHDL(set.getHDL());
    this->setSBP(set.getSBP());
    this->setHyperTest(set.getHyperTest());
    this->setSmoker(set.getSmoker());

    // "next" pointer must be unique so we must create a pointer rather than copy one.
    this->next = new FactorSet;
    }
}

// Defintion of Operator Overloading for Assignment Operator.
FactorSet& FactorSet::operator=(const FactorSet &right)
{
    // First checking if the instances (operands) are the same.
    if (this != &right)
    {
    // Setting all the risk factors equal using the accessor and mutator functions.
    this->setGender(right.getGender());
    this->setAge(right.getAge());
    this->setChole(right.getChole());
    this->setHDL(right.getHDL());
    this->setSBP(right.getSBP());
    this->setHyperTest(right.getHyperTest());
    this->setSmoker(right.getSmoker());

    // "next" pointer must be unique so we must create a pointer rather than copy one.
    this->next = new FactorSet;
    }
    return *this;
}


// Defintion of Operator Overloading for o-Stream Operator.
ostream &operator<<(ostream& out, const FactorSet &set)
{
    
    out<<set.getGender()<<' '<<set.getAge()<<' '<<set.getChole()<<' '<<set.getHDL()<<' '
    <<set.getSBP()<<' '<< set.getHyperTest()<<' '<< set.getSmoker()<<' '<<set.calRisk(set)<<endl;

    return out;
}


// This begins the NodeList Class:
// This class handles the linked lists and input functions.
class NodeList
{
    private:
    // Setting up the head variable for linked list.
    FactorSet * head;


    // Public Atrributes and Functions Start here:
    public:

    // Default constructor marks head as NULL to mark new list.
    NodeList()      { head = NULL; }

    // Destructor
    ~NodeList();

    // Function to add to the linked list of FactorSet.
    void addToList(char inputGen, int inputAge, double inputChole, double inputHDL, double inputSBP, char inputHyperTest, char inputSmoker);

    // Function for printing all the factor risks from linked list.
    void printAll();

    // Console Input Function Stub.
    void uploadConsole(NodeList &list);

    // Upload from file function
    void uploadFile(string fileName, NodeList &list);
};

NodeList::~NodeList()
{
    // Deleting Dynamically Allocated Memory
    if (head == NULL)
    {
        // Nothing Needs Deleting
    }
    else 
    {
        // Set up two pointers to help delete all the dynamic memory
        FactorSet* last = head->next;
        FactorSet* previousPtr = head;
        // While last is not null (at the end of the list):
        while (last != NULL)
        {
            // Delete the pointer before last
            delete previousPtr;
            // Set that now equal to last (the next pointer)
            previousPtr = last;
            // Move last down the list
            last = last->next;
        }
        // Once last is null, then the previous pointer is the last item
        // And so just need to delete that last one
        delete previousPtr;
    }
}

//Function for printing out factor sets. (Uses Overloaded Ostream Operator)
void NodeList::printAll()
{
    // If head is NULL then nothing has been added to the list yet, since
    // head is only NULL before an addToList method is called
    if (head == NULL)
    {
        cout<<"Nothing to print.";
    }
    else
    {
        // If head is not NULL then something is on the list.
        // First, we create a temporary pointer last and set it to the head.
        FactorSet * last = head;
        while (last != NULL)
        {
            // First, print the instance out. When it first enters the loop
            // it is on head, so it prints the first instance.
            cout<<*last;
            cout<<'\n';
            // Then it moves last to that instance's "next" which is the address of
            // the next instance.  Then that address is set to last's value, thus
            // moving last down the list.  Repeated until next is NULL, which is the 
            // last FactorSet on the list.
            last = last->next;
        }

    }

}

// This defines the addToList Function.
void NodeList::addToList(char inputGen, int inputAge, double inputChole, double inputHDL, double inputSBP, char inputHyperTest, char inputSmoker)
{
    // First, check if the list is empty
    // If head is NULL, then the list was just made.
    // This is from NodeList default contructor setting head = NULL when created
    if(head == NULL) 
    {
        // Creates first object in list.
        head = new FactorSet(inputGen, inputAge, inputChole, inputHDL, inputSBP, inputHyperTest, inputSmoker);
    }
    else
    {
        // Head FactorSet instance already exists, so now adding to the list.
        // This first line creates a temporary pointer called last.
        FactorSet * last = head;
        // The while loop then moves last along the list until it is at the last input.
        while (last->next != NULL)
        {
            last = last->next;
        }
        // This then sets the 'next' variable euqal to a new factorset pointer, thus having
        // the list extended, as the last factorset now points to another one.
        last->next = new FactorSet(inputGen, inputAge, inputChole, inputHDL, inputSBP, inputHyperTest, inputSmoker);
    }

}

// This is the uploadConsole function. It (like the uploadFile method) verifies data before 
// it is added to the linked list.
void NodeList::uploadConsole(NodeList &list)
{
    // consoleActive is a bool that serves to keep menu open until user choices to close it (set to False).
    bool consoleActive = true;
    // consoleChoice is asked at the end of the loop to let user switch consoleActive to false.
    char consoleChoice;
    while (consoleActive)
    {
        // Asking for Gender
        cout<<endl;
        // Have genderString to take answer and cut it to a char (stored in gender)
        char gender;
        string genderString;
        // Do While loop asks for answer, used do-while so executes once
        do {
            cout<<"Please enter gender: (male or female) "<<endl;
            cout<<"Also can accept: (m or f)"<<endl;
            cin>>genderString;
            // Used .at(0) to cut genderString into gender char variable for validation
            gender = genderString.at(0);
            
            // Validates asnwer.
            if (toupper(gender) != 'M' && toupper(gender) != 'F') {
                cout<<endl<<"Error.  Please enter a valid input for gender."<<endl;
            }
        }
        while (toupper(gender) != 'M' && toupper(gender) != 'F');
        cout<<endl<<"..."<<endl;
        
        // Asking about age
        double age;
        do {
            cout<<"Please enter age: (Between 20 and 79)"<<endl;
            cin>>age;
            // Age is rounded
            age = round(age);
            // The age must be between the age of 20 years old and 79 years old.
            if (age<20 || age>79) {
                cout<<endl<<"Error.  Please enter a valid input for age."<<endl;
            }
        }
        // Mentioned before, age must be between the age of 20 years old and 79 years old.
        while (age<20 || age>79);
        cout<<endl<<"..."<<endl;

        // Asking about cholestrol
        double chol;
        do {
            cout<<endl<<"Please enter cholestrol level: (integer above 0)"<<endl;
            cin>>chol;
            // Cholestrol is rounded
            chol = round(chol);
            // Cholestrol must be above 0, since negative cholestrol doesn't exist.
            if (chol<0) {
                cout<<"Error.  Please enter a valid input for cholestrol."<<endl;
            }
        }
        // Cholestrol must be above 0, since negative cholestrol doesn't exist.
        while (chol<0);
        cout<<endl<<"..."<<endl;        

        // Asking about HDL
        double hdl;
        do {
            cout<<"Please enter HDL: (integer above 0)"<<endl;
            cin>>hdl;
            // HDL rounded
            hdl = round(hdl);
            // HDL must be above 0, since negative HDL doesn't exist.
            if (hdl<0) {
                cout<<"Error.  Please enter a valid input for HDL."<<endl;
            }
        }
        // HDL must be above 0, since negative HDL doesn't exist.
        while (hdl<0);
        cout<<endl<<"..."<<endl;         

        // Asking about SBP
        double sbp;
        do {
            cout<<"Please enter SBP: (integer above 0)"<<endl;
            cin>>sbp;
            // SBP rounded
            sbp = round(sbp);
            // SBP must be above 0, since negative SBP doesn't exist.
            if (sbp<0) {
                cout<<"Error.  Please enter a valid input for SBP."<<endl;
            }
        }
        // SBP must be above 0, since negative SBP doesn't exist.
        while (sbp<0);
        cout<<endl<<"..."<<endl;     

        // Asking about Hypertension Test 
        char hyperTreat;
        string hyperTreatString;      
        // HyperTreatString collects the answer, and hyperTreat is used to validate, as shown below:
        do {
            cout<<"Recieving Hypertension Treatment: (yes or no) "<<endl;
            cout<<"Also can accept: (y or n)"<<endl;
            // Reads answer into HyperString
            cin>>hyperTreatString;
            // Uses .at(0) to get first letter for validation
            hyperTreat = hyperTreatString.at(0);
            if (toupper(hyperTreat) != 'Y' && toupper(hyperTreat) != 'N') {
                cout<<endl<<"Error.  Please enter a valid input for Hypertension Treatment."<<endl;
            }
        }
        while (toupper(hyperTreat) != 'Y' && toupper(hyperTreat) != 'N');
        cout<<endl<<"..."<<endl;
        
        // Asking about Smoking
        char smoker;
        string smokerString;
        // smokerString used for collecting answer, smoker used for validation.
        do {
            cout<<"Smoker: (yes or no) "<<endl;
            cout<<"Also can accept: (y or n)"<<endl;
            cin>>smokerString;
            // .at(0) used to get first letter and save it into smoker for validation.
            smoker = smokerString.at(0);
            if (toupper(smoker) != 'Y' && toupper(smoker) != 'N') {
                cout<<endl<<"Error.  Please enter a valid input for Smoking."<<endl;
            }
        }
        while (toupper(smoker) != 'Y' && toupper(smoker) != 'N');
        cout<<endl<<"..."<<endl;

        // Adding individual to linked list now that all inputs validated.
        // list is the NodeList instance passed by reference, so these are sent into function
        // and then passed into a FactorSet function to create the object, then list adds it to
        // linked list.
        list.addToList(gender, age, chol, hdl, sbp, hyperTreat, smoker);

        // Then reasks user if they want to add another set or return to menu:
        do {
            cout<<endl<<"Indiviual Successfully Added."<<endl<<"Please select an option: (1 or 2)"<< endl;
            cout<<"1. Add an additional individual"<<endl;
            cout<<"2. Return to Main Menu"<<endl;
            cin>>consoleChoice;
            // consoleChoice captures choice and is then tested.
        } while (consoleChoice != '1' && consoleChoice != '2');
        if (consoleChoice == '2') {
            consoleActive = false;
        }
    }
}


// This is the function for uploading sets from a file.
void NodeList::uploadFile(string fileName, NodeList &list)
{
    // First, defines variables for caputring data and validating data:
    string genderString;
    char gender;
    double age;
    double chol;
    double hdl;
    double sbp;
    string hyperString;
    char hyperTreat;
    string smokeString;
    char smoker;
    ifstream riskFile;
    char trash;
    double riskNum;

    // rowCounter used to notify user what rows are valid and which were ignored because of errors.
    int rowCounter = 1;

    // Setting up file and eliminating header row
    string lineTrash;
    // String arguement used to find file in directory.
    riskFile.open(fileName.c_str());
    if (!(riskFile)) {
        cout<<"Error, No File Found."<<"\n\n";
        return;
    }
    
    // This getline removes the first row, which is the column names.
    getline(riskFile,lineTrash);
    cout<<endl;

    // Looping through the file to read the contents
    while (riskFile >> genderString) {

        // It reads the first input into a a string then uses .at(0) to get first letter for validation.
        gender = genderString.at(0);
        if (!(toupper(gender) == 'M' || toupper(gender) == 'F')) {
            // The code here is ONLY run if an error exists.
            // This error is read
            cout<<endl<<"Error, Gender input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
            }

        // Age Array Code
        riskFile >> age;
        age = round(age);
        riskFile >> trash;
        if (age<20 || age >79) {
            // The code here is ONLY run if an error exists.
            cout<<endl<<"Error, Age input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }

        // Cholestrol Array Code
        riskFile >> chol;
        chol = round(chol);
        if (chol<=0) {
            // The code here is ONLY run if an error exists.
            cout<<endl<<"Error, Cholestrol input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }
        riskFile >> trash; 

        // HDL Array Code
        riskFile >> hdl;
        hdl = round(hdl);
        if (hdl<=0) {
            // The code here is ONLY run if an error exists.
            cout<<endl<<"Error, HDL input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }
        riskFile >> trash; 

        // SBP Array Code
        riskFile >> sbp;
        sbp = round(sbp);
        if (sbp<=0) {
            // The code here is ONLY run if an error exists.
            cout<<endl<<"Error, SBP input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }
        riskFile >> trash; 

        // Hypertension Array Code
        riskFile >> hyperString;
        hyperTreat = hyperString.at(0);
        if (!(toupper(hyperTreat) == 'Y' || toupper(hyperTreat) == 'N')) {
            // The code here is ONLY run if an error exists.
            cout<<endl<<"Error, Hypertension Treatment input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }

        // Smoking Code (1st checks if missing last value at the end, then runs)
        if (riskFile.peek() == '\n') {
            // This code is ONLY read if the smoking input was missing (since an enter was the next character)
            cout<<endl<<"Error, File missing the smoker input for row "<<rowCounter<<".  Moving to next row..."<<endl;
            // Row Counter added to since this row has ended.
            // No getline because the row is over.
            rowCounter++;
            // continue is called to restart this loop for the next row.
            continue;
        }
        // If character is there, then this is run: (still need validation for character)
        riskFile >> smokeString;
        smoker = smokeString.at(0);
        // Uses same tactic as before, .at(0) in order to get the first character.
        if (!(toupper(smoker) == 'Y' || toupper(smoker) == 'N')){
            // This code ONLY run if the input is invalid.
            cout<<endl<<"Error, Smoker input for row "<<rowCounter<<" invalid.  Moving to next row..."<<endl;
            // Row counter is added to, because an error means this row is thrown away.
            rowCounter++;
            // This getline is then used to trash the rest of the line.
            getline(riskFile,lineTrash);
            // continue is called to restart this loop for the next row.
            continue;
        }

        // When all are verfied, it is put into the linked list with the addToList function.
        // This again, passes these inputs to a Constructor so a FactorSet is made then adds it 
        // to the linked list.
        list.addToList(gender, age, chol, hdl, sbp, hyperTreat, smoker);

        cout<<endl<<"Row "<<rowCounter<<" Successfully Inputted!"<<endl;
        rowCounter++;
    }
    cout<<endl;
    riskFile.close();
}


// Beginning main() function:
int main() {

    // Openning the Main Menu
    // menuActive is used to keep loop running until exit is chosen
    // or an invalid answers make menuErrors hit 5.
    bool menuActive = true;
    char choice;
    int menuErrors = 0;
    // This instance of NodeList will serve as the linked list of FactorSets.
    NodeList list;

    // Being Menu:
    while (menuActive) {
    // Displays Menu:
    choice = displayMenu();
        if (choice == '1') {
            // Input File option was picked:
            cout<<"Please enter the file name: \n";
            string fileName;
            cin>>fileName;
            // Function run to find file and begin verification, list passes itself
            // as reference so that the valid instances become part of the linked list
            list.uploadFile(fileName, list);
        }
        
        else if (choice == '2') {
            // Input Console option was picked:
            list.uploadConsole(list);
        }

        else if (choice == '3') {
            // Display Risk Factor option was picked:
            list.printAll();
        }

        else if (choice == '4') {
            // Exit was picked:
            cout<<"Exiting..."<<endl;
            menuActive = false;
        }

        else {
            // This code is run if user inputs anything other than 1, 2, 3, or 4.
            cout<<"Error. Please enter a valid number. 5 incorrect input attempts will close program. \n\n";
            // MenuErrors added to.
            menuErrors++;
            // If menu errors exceed 5 then the program closes.
            if (menuErrors >= 5) {
                cout<<"Too many incorrect menu inputs.  Program now exiting..."<<endl;
                menuActive = false;
            }
        }

    }

    return 0;
}


// DISPLAYING MENU FUNCTION BELOW:
char displayMenu() {
    cout<<"Please select an item by typing its associated number:" << "\n\n";

    cout<<"1. Input File"<<"\n";
    cout<<"2. Input Console"<<"\n";
    cout<<"3. Display All Risks"<<"\n";
    cout<<"4. Exit"<<"\n";

    cout<<"Select an option (1-5): "<< endl;
    // choice is read in and then returned:
    char choice;
    cin>>choice;
    return choice;
}


// Beginnning the Calculating Risk Function:
// (Moved to end because of length to avoid messiness)
double FactorSet::calRisk(const FactorSet & facSet) const
{
    // All FactorSet atrributes of risk factors read into variables for calculation.
    double score = 0;
    char gender = facSet.getGender();
    double age = facSet.getAge();
    double chol = facSet.getChole();
    double hdl = facSet.getHDL();
    double sbp = facSet.getSBP();
    char hyperTenTest = facSet.getHyperTest();
    char smoker = facSet.getSmoker();

    // This begins Male Section (Split into if gender = Male or Female)
    // Score Added based on the Age Braket and Cholestrol Bracket someone falls into.
    // Smoker then also added to score.
    if (toupper(gender) == 'M') {
        if (age <= FirstAgeBracketCeiling) {
            score -= 9;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=4;
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=7;
            }
            else if (chol <= FourthCholBracketCeiling) {
                score+=9;
            }
            else                  {
                score+=11;
            }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {
                score+=8;
            }
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SecondAgeBracketCeiling) {
            score -= 4;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=4; 
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=7; 
            }
            else if (chol <= FourthCholBracketCeiling) {
                score+=9;
            }
            else                  {
                score+=11;
            }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {
                score+=8;
            }
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= ThirdAgeBracketCeiling) {
            score += 0;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=3; 
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=5; 
            }
            else if (chol <= FourthCholBracketCeiling) {
                score+=6;
            }
            else                  {
                score+=8;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {
                score+=5;
            }
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= FourthAgeBracketCeiling) {
            score += 3;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=3; 
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=5; 
            }
            else if (chol <= FourthCholBracketCeiling) {
                score+=6;
            }
            else                  {
                score+=8;
            }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=5;}            
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= FifthAgeBracketCeiling) {
            score += 6;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=2; 
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=3; 
            }
            else if (chol <= FourthCholBracketCeiling) {
                score+=4;
            }
            else                  {
                score+=5;
            }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=3;}            
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SixthAgeBracketCeiling) {
            score += 8;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {score+=2; 
            }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=3;
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=4;
                }
            else                  {
                score+=5;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=3;}   
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SeventhAgeBracketCeiling) {
            score += 10;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=2;
                }
            else                  {
                score+=3;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}   
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= EighthAgeBracketCeiling) {
            score += 11;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=1;
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=2;
                }
            else                  {
                score+=3;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= NinthAgeBracketCeiling) {
            score += 12;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=0; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=0; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=1;
                }
            else                  {
                score+=1;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}
        }

        // No Age Bracket above 74
        else {
            score += 13;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=0; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=0; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=1;
                }
            else                  {
                score+=1;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}
        }

        // HDL Section
        // Global Constants contain the specific HDL Brackets.
        if (hdl >= FirstHDLBracketCeiling) {
            score--;
        }
        else if (hdl >= SecondHDLBracketCeiling) {
            score+=0;
        }
        else if (hdl >= ThirdHDLBracketCeiling) {
            score++;
        }
        else {
            score+=2;
        }

        // SBP and Hyper Tension Section Section
        // Global Constants contain the specific SBP Brackets.
        if (toupper(hyperTenTest) == 'N')
            if (sbp <= SecondSBPBracketCeiling) {
                score+=0;
            }
            else if (sbp <= FourthSBPBracketCeiling) {
                score++;
            }
            else {score+=2;}

        // This is for no Hypertension Treatment
        else {
            if (sbp <= FirstSBPBracketCeiling) { 
                score += 0;
                }
            else if (sbp <= SecondSBPBracketCeiling) { 
                score += 1;
                }
            else if (sbp <= FourthSBPBracketCeiling) { 
                score += 2;
                }
            else {
                score+=3;
                }

        }
    }

    // FEMALE SECTION
    else {
        // Global Constants contain the specific Age and Cholestrol Brackets.
        if (age <= FirstAgeBracketCeiling) {
            score -= 7;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=4; }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=8; }
            else if (chol <= FourthCholBracketCeiling) {
                score+=11;
                }
            else                  {
                score+=13;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=9;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SecondAgeBracketCeiling) {
            score -= 3;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=4; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=8; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=11;
                }
            else                  {
                score+=13;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=9;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= ThirdAgeBracketCeiling) {
            score += 0;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=3; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=6; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=8;
                }
            else                  {
                score+=10;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=7;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= FourthAgeBracketCeiling) {
            score += 3;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {score+=3; }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=6; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=8;
                }
            else                  {
                score+=10;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=7;}            
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= FifthAgeBracketCeiling) {
            score += 6;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {score+=2; }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=4; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=5;
                }
            else                  {
                score+=7;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=4;}            
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SixthAgeBracketCeiling) {
            score += 8;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=2; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=4; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=5;
                }
            else                  {
                score+=7;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=4;}   
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= SeventhAgeBracketCeiling) {
            score += 10;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=2; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=3;
                }
            else                  {
                score+=4;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=2;}   
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= EighthAgeBracketCeiling) {
            score += 12;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=2; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=3;
                }
            else                  {
                score+=4;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=2;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        else if (age <= NinthAgeBracketCeiling) {
            score += 14;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=2;
                }
            else                  {
                score+=2;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}
        }

        // Global Constants contain the specific Age and Cholestrol Brackets.
        // This is for above the age of 79.
        else {
            score += 16;

            if (chol >= FirstCholBracketCeiling && chol <= SecondCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= ThirdCholBracketCeiling) {
                score+=1; 
                }
            else if (chol <= FourthCholBracketCeiling) {
                score+=2;
                }
            else                  {
                score+=2;
                }

            // If they are a smoker
            if (toupper(smoker) == 'Y') {score+=1;}
        }

        // HDL Section
        // Global Constants contain the specific HDL Brackets.
        if (hdl >= FirstHDLBracketCeiling) {
            score--;
        }
        else if (hdl >= SecondHDLBracketCeiling) {
            score+=0;
        }
        else if (hdl >= ThirdHDLBracketCeiling) {
            score++;
        }
        else {
            score+=2;
        }

        // SBP and Hyper Tension Section Section - For Women
        // Global Constants contain the specific SBP Brackets.
        if (toupper(hyperTenTest) == 'N')
            if (sbp <= FirstSBPBracketCeiling) {
                score+=0;
            }
            else if (sbp <= SecondSBPBracketCeiling) {
                score++;
            }
            else if (sbp <= ThirdSBPBracketCeiling) {
                score+=2;
            }
            else if (sbp <= FourthSBPBracketCeiling) {
                score+=3;
            }
            else {
                score+=4;
            }

        // This is for no Hypertension Treatment
        else {
            if (sbp <= FirstSBPBracketCeiling) { 
                score += 0; 
                }
            else if (sbp <= SecondSBPBracketCeiling) { 
                score += 3;
                }
            else if (sbp <= ThirdSBPBracketCeiling) { 
                score += 4;
                }
            else if (sbp <= FourthSBPBracketCeiling) { 
                score += 5;
                }
            else {
                score+=6;
                }
        }
    }

    // This makes sure score is positive, since can't have negative score.
    if (score < 0) {
        score = 0;
    }
    
    // Return score
    return score;
}
