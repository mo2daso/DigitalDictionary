#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<string.h>
#include<fstream>

using namespace std;

struct Node {
    char word[50];
    char meaning[100];
    char synonym[100];
    char partOfSpeech[50];
    Node* left;
    Node* right;
};

Node* root = nullptr;

Node* CreateNode(const char* word, const char* meaning, const char* synonym, const char* partOfSpeech);

Node* InsertNode(Node* root, const char* word, const char* meaning, const char* synonym, const char* partOfSpeech);

void InOrderTraversal(Node* root);

bool SearchWord(Node* root, const char* word);

void UpdateDetails(Node*& root, const char* word, const char* newMeaning, const char* newSynonym, const char* newPartOfSpeech);

Node* DeleteWord(Node* root, const char* word);

Node* DeleteWordInternal(Node* root, const char* word);

Node* FindMinValueNode(Node* root);

void InOrderTraversalToFile(Node* root, ofstream& outFile);

void WriteToFile(const char* word, const char* meaning, const char* synonym, const char* partOfSpeech);

void ReadFromFile();

void MenuHeader();

int main() {
    system("color 0B");

    Beep(2020, 1100);
    char l = 219;

    cout << endl << endl << endl;
    cout << "Loading.";
    cout << endl;
    for (int i = 0; i < 5; i++) {
        Beep(2000, 500);
        cout << l;
    }

    try {
        int choice1;
        char choice2[10], choice3[10];
        bool terminate = false;
        char word[50], meaning[100], synonym[100], partOfSpeech[50];
        cout << endl;

        do {
            system("cls");
            MenuHeader();


            cout << "Enter serial no. from the menu to proceed: ";
            cin >> choice1;

            switch (choice1) {
            case 1:
                do {
                    cout << "\nInput Word: ";
                    cin >> word;
                    cout << "Input Meaning: ";
                    cin.ignore();
                    cin.getline(meaning, sizeof(meaning));
                    cout << "Input Synonym: ";
                    cin.getline(synonym, sizeof(synonym));
                    cout << "Input Part of Speech: ";
                    cin.getline(partOfSpeech, sizeof(partOfSpeech));
                    root = InsertNode(root, word, meaning, synonym, partOfSpeech);
                    WriteToFile(word, meaning, synonym, partOfSpeech);
                    cout << "Enter another word? (yes/no): ";
                    cin >> choice3;
                } while (strcmp(choice3, "yes") == 0 || strcmp(choice3, "Yes") == 0);
                cout << "Words added successfully!" << endl;
                break;
            case 2:
                cout << "\nInput Word: ";
                cin >> word;
                SearchWord(root, word);
                break;
            case 3:
                cout << "\nInput Word: ";
                cin >> word;
                UpdateDetails(root, word, meaning, synonym, partOfSpeech);
                break;
            case 4:
                cout << "\nInput Word: ";
                cin >> word;
                root = DeleteWord(root, word);
                break;
            case 5:
                cout << endl << "Fetching Data." << endl;
                for (int i = 0; i < 5; i++) {
                    Beep(2000, 500);
                    cout << l;
                }
                system("cls");
                MenuHeader();
                cout << "          ______________________________" << endl;
                cout << "         |  __________________________  |" << endl;
                cout << "         | |                          | |" << endl;
                cout << "         | |    COMPLETE DICTIONARY   | |" << endl;
                cout << "         | |__________________________| |" << endl;
                cout << "         |______________________________|" << endl << endl;
                ReadFromFile();
                InOrderTraversal(root);
                break;
            case 6:
                terminate = true;
                strcpy_s(choice2, "no");
                break;
            default:
                cout << endl << "Invalid serial no. entered!" << endl << endl;
            }

            if (!terminate) {
                cout << "Would you like to open the menu again? (yes/no): ";
                cin >> choice2;
                cout << endl;
            }
        } while (strcmp(choice2, "yes") == 0 || strcmp(choice2, "Yes") == 0);
    }
    catch (const exception& e) {
        cerr << "Exception handled: " << e.what() << endl;
    }

    return 0;
}

Node* CreateNode(const char* word, const char* meaning, const char* synonym, const char* partOfSpeech) {
    Node* newNode = new Node();
    strcpy_s(newNode->word, word);
    strcpy_s(newNode->meaning, meaning);
    strcpy_s(newNode->synonym, synonym);
    strcpy_s(newNode->partOfSpeech, partOfSpeech);
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* InsertNode(Node* root, const char* word, const char* meaning, const char* synonym, const char* partOfSpeech) {
    if (root == nullptr) {
        root = CreateNode(word, meaning, synonym, partOfSpeech);
    }
    else if (strcmp(word, root->word) < 0) {
        root->left = InsertNode(root->left, word, meaning, synonym, partOfSpeech);
    }
    else if (strcmp(word, root->word) > 0) {
        root->right = InsertNode(root->right, word, meaning, synonym, partOfSpeech);
    }

    return root;
}

void InOrderTraversal(Node* root) {
    if (root != nullptr) {
        InOrderTraversal(root->left);
        cout << "-----------------------------------" << endl;
        cout << "Word: " << root->word << endl;
        cout << "Meaning: " << root->meaning << endl;
        cout << "Synonym: " << root->synonym << endl;
        cout << "Part of Speech: " << root->partOfSpeech << endl;
        cout << "-----------------------------------" << endl;
        InOrderTraversal(root->right);
        
    }
}

bool SearchWord(Node* root, const char* word) {
    if (root == nullptr) {
        cout << "The word is not in the Dictionary!" << endl;
        return false;
    }
    else if (strcmp(word, root->word) == 0) {
        cout << "_______________________________________________________" << endl << endl;
        cout << "Word: " << root->word << endl;
        cout << "Meaning: " << root->meaning << endl;
        cout << "Synonym: " << root->synonym << endl;
        cout << "Part of Speech: " << root->partOfSpeech << endl;
        cout << "_______________________________________________________" << endl;
        return true;
    }
    else if (strcmp(word, root->word) < 0) {
        return SearchWord(root->left, word);
    }
    else if (strcmp(word, root->word) > 0) {
        return SearchWord(root->right, word);
    }
    return false;
}

void UpdateDetails(Node*& root, const char* word, const char* newMeaning, const char* newSynonym, const char* newPartOfSpeech) {
    if (root == nullptr) {
        cout << "The word is not in the Dictionary!" << endl;
    }
    else if (strcmp(word, root->word) == 0) {
        cout << "_______________________________________________________" << endl << endl;
        cout << "Existing Meaning: " << root->meaning << endl;
        cout << "Enter New Meaning: ";
        cin.ignore();
        cin.getline(root->meaning, sizeof(root->meaning));

        cout << "Existing Synonym: " << root->synonym << endl;
        cout << "Enter New Synonym: ";
        cin.getline(root->synonym, sizeof(root->synonym));

        cout << "Existing Part of Speech: " << root->partOfSpeech << endl;
        cout << "Enter New Part of Speech: ";
        cin.getline(root->partOfSpeech, sizeof(root->partOfSpeech));

        WriteToFile(root->word, root->meaning, root->synonym, root->partOfSpeech);

        cout << "Details updated successfully!" << endl;
        cout << "_______________________________________________________" << endl << endl;
    }
    else if (strcmp(word, root->word) < 0) {
        UpdateDetails(root->left, word, newMeaning, newSynonym, newPartOfSpeech);
    }
    else if (strcmp(word, root->word) > 0) {
        UpdateDetails(root->right, word, newMeaning, newSynonym, newPartOfSpeech);
    }
}

Node* DeleteWord(Node* root, const char* word) {
    bool wordExists = SearchWord(root, word);

    if (!wordExists) {
        return root;
    }

    root = DeleteWordInternal(root, word);

    ofstream outFile("Dictionary.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        exit(1);
    }

    InOrderTraversalToFile(root, outFile);

    cout << "The word is deleted successfully!" << endl;

    outFile.close();

    return root;
}

Node* DeleteWordInternal(Node* root, const char* word) {
    if (root == nullptr) {
        return root;
    }

    if (strcmp(word, root->word) < 0) {
        root->left = DeleteWordInternal(root->left, word);
    }
    else if (strcmp(word, root->word) > 0) {
        root->right = DeleteWordInternal(root->right, word);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = FindMinValueNode(root->right);
        strcpy_s(root->word, temp->word);
        strcpy_s(root->meaning, temp->meaning);
        strcpy_s(root->synonym, temp->synonym);
        strcpy_s(root->partOfSpeech, temp->partOfSpeech);

        root->right = DeleteWordInternal(root->right, temp->word);
    }

    return root;
}

Node* FindMinValueNode(Node* root) {
    Node* curr = root;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

void InOrderTraversalToFile(Node* root, ofstream& outFile) {
    if (root != nullptr) {
        InOrderTraversalToFile(root->left, outFile);
        outFile << root->word << endl;
        outFile << root->meaning << endl;
        outFile << root->synonym << endl;
        outFile << root->partOfSpeech << endl;
        InOrderTraversalToFile(root->right, outFile);
    }
}

void WriteToFile(const char* word, const char* meaning, const char* synonym, const char* partOfSpeech) {
    ofstream myfile("Dictionary.txt", ios::app);
    if (!myfile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        exit(1);
    }

    myfile << word << endl;
    myfile << meaning << endl;
    myfile << synonym << endl;
    myfile << partOfSpeech << endl;

    if (myfile.fail()) {
        cerr << "Error writing to file." << endl;
        exit(1);
    }

    myfile.close();
}

void ReadFromFile() {
    ifstream inputFile("Dictionary.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file for reading." << endl;
        exit(1);
    }

    char word[50], meaning[100], synonym[100], partOfSpeech[50];

    while (inputFile.getline(word, sizeof(word))) {
        inputFile.getline(meaning, sizeof(meaning));
        inputFile.getline(synonym, sizeof(synonym));
        inputFile.getline(partOfSpeech, sizeof(partOfSpeech));

        root = InsertNode(root, word, meaning, synonym, partOfSpeech);
    }

    if (inputFile.fail() && !inputFile.eof()) {
        cerr << "Error reading from file." << endl;
        exit(1);
    }

    inputFile.close();
}

void MenuHeader() {
    cout << endl << endl << endl;

    cout << "\t______ _____ _____ _____ _____ ___   _       ______ _____ _____ _____ _____ _____ _   _   ___  ________   __" << endl;
    cout << "\t|  _  \\_   _|  __ \\_   _|_   _/ _ \\ | |      |  _  \\_   _/  __ \\_   _|_   _|  _  | \\ | | / _ \\ | ___ \\ \\ / /" << endl;
    cout << "\t| | | | | | | |  \\/ | |   | |/ /_\\ \\| |      | | | | | | | /  \\/ | |   | | | | | |  \\| |/ /_\\ \\| |_/ /\\ V / " << endl;
    cout << "\t| | | | | | | | __  | |   | ||  _  || |      | | | | | | | |     | |   | | | | | | . ` ||  _  ||    /  \\ /  " << endl;
    cout << "\t| |/ / _| |_| |_\\ \\_| |_  | || | | || |____  | |/ / _| |_| \\__/\\ | |  _| |_\\ \\_/ / |\\  || | | || |\\ \\  | |  " << endl;
    cout << "\t|___/  \\___/ \\____/\\___/  \\_/\\_| |_/\\_____/  |___/  \\___/ \\____/ \\_/  \\___/ \\___/\\_| \\_/\\_| |_/\\_| \\_| \\_/  " << endl << endl;

    cout << endl << endl;
    cout << "\t\t       ----------------------------MAIN MENU--------------------------" << endl;

    cout << "\t\t ______________________________________ ____________________________________" << endl;
    cout << "\t\t|                                      |                                    |" << endl;
    cout << "\t\t|  (1) Insert Word                     |   (2) Search Word                  |" << endl;
    cout << "\t\t|  (3) Update Details                  |   (4) Delete Word                  |" << endl;
    cout << "\t\t|  (5) Display All Words               |   (6) Exit                         |" << endl;
    cout << "\t\t|______________________________________|____________________________________|" << endl;
    cout << endl << endl;
}




