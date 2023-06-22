//DANIEL DEAN ASUNCION
//dasunc2, 671785728
//CS 474
//PROJECT 4

#include <iostream>
#include <typeinfo>
#include "node.h"
#include "linked_list.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class SPLInstructions {
public:
    void NEWID();

};

class SPLObject : public SPLInstructions {
private:
    string identifier;

    int SPLValue1;
    linked_list SPLValue2;

    string identifierType;

public:

    SPLObject() {

    }

    SPLObject(string id) {
        identifier = id;
    }
    
    void NEWID() {
        identifierType = "None";
        SPLValue2;
    }

    void COMBINE(int id) {
        if (identifierType == "SPLInteger") {
            cout << "Error. Cannot COMBINE into an integer. Must be uninitialized identifier or type list.";
            return;
        }

        if (identifierType == "None") {
            linked_list lnew;
            SPLValue2 = lnew;
            identifierType = "SPLList";
        }
        else {
            //cout << "List already created" << endl;
        }

        SPLValue2.prepend(id);
    }

    void COMBINE(node* id) {
        if (identifierType == "SPLInteger") {
            cout << "Error. Cannot COMBINE into an integer. Must be uninitialized identifier or type list.";
            return;
        }

        if (identifierType == "None") {
            linked_list lnew;
            SPLValue2 = lnew;
            identifierType = "SPLList";
        }
        else {
            //cout << "List already created" << endl;
        }

        SPLValue2.prepend(id);
    }

    void COPY(node* value) {
        SPLValue2.set_head(value);
        identifierType = "SPLList";
    }

    void COPY(linked_list value) {
        SPLValue2 = value;
        identifierType = "SPLList";
    }

    void HEAD(linked_list id) {
        if (id.return_head() == NULL) {
            linked_list temp;
            setObjectValue(temp);
            identifierType = "None";
        }

        if (id.return_head()->dataType == "struct node *") {
            SPLValue2.~linked_list();
            SPLValue2.set_head(id.return_head()->data.nval);

            identifierType = "SPLList";
        }
        else if (id.return_head()->dataType == "int") {
            SPLValue2.~linked_list();
            linked_list temp;
            SPLValue2 = temp;

            setObjectValue(id.return_head()->data.ival);
            identifierType = "SPLInteger";
        }
        else {
            cout << "Invalid object." << endl;
                return;
        }
    }

    void HEAD(node* id) {
        if (id == NULL) {
            linked_list temp;
            setObjectValue(temp);
            identifierType = "None";
        }

        if (id->dataType == "struct node *") {
            SPLValue2.~linked_list();
            SPLValue2.set_head(id->data.nval);

            identifierType = "SPLList";
        }
        else if (id->dataType == "int") {
            SPLValue2.~linked_list();
            linked_list temp;
            SPLValue2 = temp;

            setObjectValue(id->data.ival);
            identifierType = "SPLInteger";
        }
        else {
            cout << "Invalid object." << endl;
            return;
        }
    }

    void TAIL(linked_list id) {
        if (id.return_head() == NULL) {
            identifierType = "SPLList";
        }
        else {
            linked_list temp_list = id;
            temp_list.headless_list();
            setObjectValue(temp_list);
            identifierType = "SPLList";
        }
    }

    void TAIL(node* id) {
        if (id == NULL) {
            identifierType = "SPLList";
        }
        else {
            linked_list temp_list;
            temp_list.set_head(id);
            temp_list.headless_list();
            setObjectValue(temp_list);
            identifierType = "SPLList";
        }
    }

    void ASSIGN(int value) {
        linked_list temp;
        SPLValue2.~linked_list();
        SPLValue2 = temp;

        identifierType = "SPLInteger";
        SPLValue1 = value;
    }

    void CHS() {
        SPLValue1 *= -1;
    }

    void ADD(int value) {
        SPLValue1 = SPLValue1 + value;
    }
    //////////////HELPER FUNCTIONS BELOW//////////////
    void setObjectValue(linked_list value) {
        SPLValue2 = value;
    }

    void setObjectValue(int value) {
        SPLValue1 = value;
    }

    void deleteList() {
        if (identifierType == "SPLList") {
            SPLValue2.~linked_list();
            linked_list temp;
            SPLValue2 = temp;
        }
    }

    void deleteObjectValue() {
        SPLValue2.~linked_list();
        linked_list temp;
        SPLValue2 = temp;

        identifierType = "None";
    }

    node* callListCopy() {
        if (SPLValue2.return_head() == NULL) {
            linked_list temp;
            return temp.return_head();
        }

        linked_list copiedList = SPLValue2;
        return copiedList.return_head();
    }

    linked_list callHeadlessList() {
        linked_list temp = SPLValue2;
        temp.headless_list();
        return temp;
    }

    string returnIdentifier() {
        return identifier;
    }

    int returnIdentifierValue1() {
        return SPLValue1;
    }

    node* returnIdentifierValue2() {
        return SPLValue2.return_head();
    }

    string returnIdentifierType() {
        return identifierType;
    }

    void printIdentifier() {
        if (identifierType == "SPLInteger") {
            cout << identifier << ":" << SPLValue1 << endl;
        }
        else if (identifierType == "SPLList") {
            if (SPLValue2.return_head() == NULL) {
                cout << identifier << ":" << "[]" << endl;
            }
            else {
                cout << identifier << ":";
                print(SPLValue2.return_head());
                cout << endl;
            }
        }
        else {
            cout << identifier << ":" << endl;
        }
    }

};

class SPLInterpreter {
private:
    unordered_map<string, SPLObject> identifierTable;
    int programCounter;
    vector<string> splFile;

public:
    SPLInterpreter() {
        programCounter = 0;
    }

    void resetInterpreter() {
        identifierTable.clear();
        programCounter = 0;
    }

    void getFileName() {

        string file;
        string str;

        cout << "***WARNING***" << endl;
        cout << "Please make sure that the LAST LINE of code in the .spl file is an HLT." << endl;
        cout << "Any additional empty lines of code after HLT will result the program to crash.\n" << endl;

        cout << "Please enter a valid spl filename with the file extesion .spl:" << endl;
        cin >> file;

        ifstream in(file);

        while (getline(in, str)) {
            if (str.size() > 0) {
                splFile.push_back(str);
            }
        }
    }

    void incrementPC() {
        programCounter = programCounter + 1;
    }

    void commandL() {
        //string line = splFile[programCounter];
        //char* token = strtok(line, " ");

        string s = splFile[programCounter];
        int n = s.length();

        char* line= new char[n + 1];
        strcpy(line, s.c_str());
        char* token = strtok(line, " ");

        vector<string> word;

        if (s == "HLT") {
            cout << "\nReached the end of .spl file. Restarting index.\n";
            resetInterpreter();
            return;
        }

        while (token != NULL) {
            word.push_back(token);
            token = strtok(NULL, " ");
        }

        string instruction = word[(word.size() - 1)];

        if (instruction != "IF") {
            if (instruction == "NEWID") {
                callNEWID(word);
            }
            else if (instruction == "ASSIGN") {
                callASSIGN(word);
            }
            else if (instruction == "COMBINE") {
                callCOMBINE(word);
            }
            else if (instruction == "COPY") {
                callCOPY(word);
            }
            else if (instruction == "HEAD") {
                callHEAD(word);
            }
            else if (instruction == "TAIL") {
                callTAIL(word);
            }
            else if (instruction == "CHS") {
                callCHS(word);
            }
            else if (instruction == "ADD") {
                callADD(word);
            }
            else {
                cout << "Instruction not valid." << endl;
            }

            cout << "PC: " << programCounter << endl;
            incrementPC();
        }
        else {
            callIF(word);
        }

        for (auto& it : identifierTable) {
            it.second.printIdentifier();
        }
    }

    void commandA() {
        string s = splFile[programCounter];

        while (s != "HLT") {
            int n = s.length();

            char* line = new char[n + 1];
            strcpy(line, s.c_str());
            char* token = strtok(line, " ");

            vector<string> word;

            while (token != NULL) {
                word.push_back(token);
                token = strtok(NULL, " ");
            }

            string instruction = word[(word.size() - 1)];

            if (instruction != "IF") {
                if (instruction == "NEWID") {
                    callNEWID(word);
                }
                else if (instruction == "ASSIGN") {
                    callASSIGN(word);
                }
                else if (instruction == "COMBINE") {
                    callCOMBINE(word);
                }
                else if (instruction == "COPY") {
                    callCOPY(word);
                }
                else if (instruction == "HEAD") {
                    callHEAD(word);
                }
                else if (instruction == "TAIL") {
                    callTAIL(word);
                }
                else if (instruction == "CHS") {
                    callCHS(word);
                }
                else if (instruction == "ADD") {
                    callADD(word);
                }
                else {
                    cout << "Instruction not valid." << endl;
                }

                incrementPC();
                s = splFile[programCounter];
            }
            else {
                callIF(word);
                s = splFile[programCounter];
            }
        }
        cout << "PC: " << programCounter + 1 << endl;

        for (auto& it : identifierTable) {
            it.second.printIdentifier();
        }
    }

    void callNEWID(vector<string> inputList) {
        SPLObject newid(inputList[0]);
        newid.NEWID();

        identifierTable[inputList[0]] = newid;
    }

    void callASSIGN(vector<string> inputList) {
        string identifier = inputList[0];
        int value = stoi(inputList[1]);

        cout << value << endl;

        identifierTable[identifier].ASSIGN(value);
    }

    void callCOMBINE(vector<string> inputList) {
        string id = inputList[0];
        string list = inputList[1];

        if (identifierTable[id].returnIdentifierType() == "SPLInteger") {
            identifierTable[list].COMBINE(identifierTable[id].returnIdentifierValue1());
        }
        else if (identifierTable[id].returnIdentifierType() == "SPLList") {
            node* temp = identifierTable[id].returnIdentifierValue2();
            identifierTable[list].COMBINE(temp);
     
        }
    }

    void callCOPY(vector<string> inputList) {
        string list1 = inputList[0];
        string list2 = inputList[1];

        if (identifierTable[list1].returnIdentifierType() == "None") {
            identifierTable[list2].deleteList();
        }
        else {
            identifierTable[list2].deleteList(); 
            identifierTable[list2].COPY(identifierTable[list1].returnIdentifierValue2());
        }
    }

    void callHEAD(vector<string> inputList) {
        string id1 = inputList[0];
        string id2 = inputList[1];

        identifierTable[id2].deleteObjectValue();
        linked_list temp;
        temp.set_head(identifierTable[id1].returnIdentifierValue2());
        identifierTable[id2].HEAD(temp);
    }

    void callTAIL(vector<string> inputList) {
        string id1 = inputList[0];
        string id2 = inputList[1];

        identifierTable[id2].deleteObjectValue();
        linked_list temp;
        temp.set_head(identifierTable[id1].returnIdentifierValue2());
        identifierTable[id2].TAIL(temp);
    }

    void callCHS(vector<string> inputList) {
        string id = inputList[0];

        if (identifierTable[id].returnIdentifierType() == "None" or identifierTable[id].returnIdentifierType() == "SPLList") {
            cout << "Error. Cannot perform instruction on type Linked List or typeless identifiers." << endl;
            return;
        }
        else {
            identifierTable[id].CHS();
        }
    }

    void callADD(vector<string> inputList) {
        string id1 = inputList[0];
        string id2 = inputList[1];

        if (identifierTable[id1].returnIdentifierType() == "None" or identifierTable[id1].returnIdentifierType() == "SPLList" or
            identifierTable[id2].returnIdentifierType() == "None" or identifierTable[id2].returnIdentifierType() == "SPLList") {
            cout << "Error. Cannot perform instruction on type Linked List or typeless identifiers." << endl;
            return;
        }
        else {
            identifierTable[id1].ADD(identifierTable[id2].returnIdentifierValue1());
        }
    }

    void callIF(vector<string> inputList) {
        string id = inputList[0];
        int index = stoi(inputList[1]);

        string idType = identifierTable[id].returnIdentifierType();
        if (idType == "SPLInteger") {
            int idVal = identifierTable[id].returnIdentifierValue1();
            if (idVal == 0) {
                programCounter = index;
            }
        }
        else if (idType == "SPLList") {
            node* idVal = identifierTable[id].returnIdentifierValue2();
            if (idVal == NULL) {
                programCounter = index;
            }
        }
        else {
            incrementPC();
        }
    }
};

int main()
{
    SPLInterpreter interpreter;
    interpreter.getFileName();
    
    char userInput;
    bool quit = false;

    while (quit != true) {
        cout << "\n\nPlease enter your command\n\n";
        cout << "'l' to execute a line of code line by line starting from line 0\n";
        cout << "'a' to execute the whole spl file until HLT instruction is encountered\n";
        cout << "'q' to exit the program\n\n";

        cin >> userInput;

        switch (userInput) {
        case 'a':
            cout << endl;
            interpreter.commandA();
            break;
        case 'l':
            cout << endl;
            interpreter.commandL();
            break;
        case 'q':
            quit = true;
            break;

        default:
            cout << "Invalid command." << endl;
        }

    }

    cout << "\nExiting the program..." << endl;

    return 0;
}   


