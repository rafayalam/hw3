#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Node{
    string data;
    Node *next, *prev;
    Node(string n):data(n),next(NULL),prev(NULL){}
};

class DLL{
    private:
        Node *head;
        Node *tail;
        int size;
    public:
        DLL() {
            head = NULL;
            tail = NULL;
        }
        void append(Node*);
        string preToPost(string pre);
        string postToPre(string post);
        void print();
        void printListBackwards();
        Node* getHead(){ return head; }
        Node* getTail(){ return tail; }
};

void DLL::append(Node* newNode) {
    if(head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

bool isOperator(char x) { 
  switch (x) { 
  case '+': 
  case '-': 
  case '/': 
  case '*': 
    return true; 
  } 
  return false; 
}

string DLL::preToPost(string pre) {
    stack<string> s; 
    int length = pre.size(); 
  
    for (int i = length - 1; i >= 0; i--) {
        if (isOperator(pre[i])) { 
            string op1 = s.top(); s.pop(); 
            string op2 = s.top(); s.pop(); 
            string temp = op1 + op2 + pre[i]; 
            s.push(temp); 
        }
        else {
            s.push(string(1, pre[i])); 
        }
    }
    return s.top();
}

string DLL::postToPre(string post) {
    stack<string> s;
    int length = post.size();
 
    for(int i = 0; i < length; i++) {
        if (isOperator(post[i])) {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            string temp = post[i] + op2 + op1;
            s.push(temp);
        }
        else {
            s.push(string(1, post[i]));
        }
    }
    string ans = "";
    while(!s.empty()) {
        ans += s.top();
        s.pop();
    }
    return ans;
}

void DLL::print() {
    Node *cu = head;
    cout << "List:" << endl;
    while (cu!=NULL) {
        cout << cu->data << endl;
        cu=cu->next;
    }
}

void DLL::printListBackwards() {
    Node *cu = tail;
    cout << "Reversed List:" << endl;
    while (cu!=NULL) {
        cout << cu->data << endl;
        cu=cu->prev;
    }
}

string removeSpaces(string str) { 
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            result += str[i];
        }
    }
    return result; 
}

void readFile(ifstream &myfile, DLL &mylist) {
    string str;
    while(getline(myfile, str)) {
        if(str.empty()) {
            continue;
        }
        if(!str.empty()) {
            mylist.append(new Node(removeSpaces(str)));
        }
    }
}

int main() {
    ifstream myfile("input31.txt");
    DLL mylist;
    readFile(myfile, mylist);

    ifstream myinputfile2("command31.txt");
    string line;
    vector<string> commands;
    while(getline(myinputfile2, line)) {
        commands.push_back(line);
    }

    for(int i = 0; i < commands.size(); ++i) {
        if(commands[i] == "printList") {
            mylist.print();
            cout << endl;
        }
        if(commands[i] == "printListBackwards") {
            mylist.printListBackwards();
            cout << endl;
        }
        /*if(commands[i] == "convertList (prefix)") {
            mypostlist.print();
        }*/
    }

    DLL mylist2;
    string pre = "+*ABC";

    cout << mylist2.preToPost(pre);

    cout << endl;

    string post = "AB+CD-*";

    cout << mylist2.postToPre(post);

    return 0;
}