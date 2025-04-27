#include <iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<cstring>
using namespace std;
void encoder(string, long long int& x, int);
long long int decoder(long long int, long long int);
void charcounter(char para[], int parasize, char character[], int counters[], int size = 96);
void charset(char character[], int size = 96);
void displaytable(string character, int counters[], int size = 96);
struct tree {
string need;
int info;
tree* left;
tree* parent;
tree* right;
};
struct node {
string code;
string character;
int frequency;
node* next;
tree* ptr;
};
class list {
private:
node* head;
public:
list() {
head = NULL;
}
void reset()
{
head = NULL;
}
node* returnhead() { return head; }
void deleteNODE(string c)
{
node* p;
node* q;
for (q = 0, p = head; p != 0 && p->character != c; q = p, p = p->next)
{
;
}
if (q == 0)
{
head = head->next;
}
else {
q->next = p->next;
}
}
void deletenode(node* address)
{
node* p;
node* q;
for (q = 0, p = head; p != 0 && p != address; q = p, p = p->next)
{
;
}
if (q == 0)
{
head = head->next;
}
else {
q->next = p->next;
}
}
bool checkingduplicate()
{
node* p = head;
while (p != 0)
{
if (p->frequency == p->next->frequency)
{
return true;
}
p = p->next;
}
return false;
}
void addcodetonode(node* add)
{
}
void push(string c, int freq, string co = "", tree* pt = NULL) {
node* p;
p = new node;
p->frequency = freq;
p->character = c;
p->code = co;
p->next = head;
p->ptr = pt;
head = p;
}
void insAfter(node* x, int oldvalue, string c, int freq, string co = "", tree* pt =
NULL) {
node* p;
for (p = head; p != 0 && (p->frequency != oldvalue || p != x); p = p->next)
{
;
}
node* q = new node;
q->frequency = freq;
q->character = c;
q->code = co;
q->ptr = pt;
q->next = p->next;
p->next = q;
}
void Place(string c, int freq, string co = "", tree* pt = NULL) {
node* q = NULL;
node* p;
for (p = head; p != NULL && freq > p->frequency; p = p->next)
{
q = p;
}
if (q == NULL)
{
push(c, freq, co, pt);
}
else
{
insAfter(q, q->frequency, c, freq, co, pt);
}
}
void display() {
node* p = head;
while (p != NULL)
{
cout << p->character << " : " << p->frequency << " : " << p->code
<< endl;
p = p->next;
}
}
int nodecounter() {
node* p = head;
int count = 0;
while (p != NULL)
{
count++;
p = p->next;
}
return count;
}
int displaylastelement() {
node* p = head;
if (p != 0)
{
return p->frequency;
}
}
node* getDesirednode(int freq, string c)
{
node* p = head;
while (p != 0)
{
if (freq == p->frequency && c == p->character)
{
return p;
}
p = p->next;
}
return NULL;
}
node* removelast() {
node* p = head;
if (p != 0)
{
head = p->next;
return p;
}
}
};
tree* setbase(string cx, string cy, int x, int y);
tree* makeRighttree(tree* node, string x, int y);
tree* makelefttree(tree* node, string x, int y);
void traverse(tree* root);
bool alphasearch(string c, char x);
string search(tree* root, char x);
tree* addleaf(tree* node, int freq, string c);
tree* addtree(tree* root, tree* child);
tree* makeleaf(node* x);
void assigningcodes(tree* root, list x);
string encodedstring(list x, char arr[], int size);
list arrtolist(char arr[], int counters[], int size = 96);
int digitcal(long long int number);
long long int placemaker(long long int x);
tree* HuffmanNewTree(list);
int main() {
cout << "Enter Option to Proceed : " << endl;
cout << "Press 1 to Decode " << endl;
cout << "Press 2 to Encode " << endl;
cout << "Press 3 to Compression Ration " << endl;
int choice;
int binsize = 0;
char arr[] = "My name is nabeel ahmed";
int size = strlen(arr);
cin >> choice;
if (choice == 1) {
ifstream cdfi("CodeFile.bin", ios::binary);
cdfi.seekg(0, ios::end);
int filesize = cdfi.tellg();
int arraysize = filesize / 8;
long long int* x = new long long int[arraysize];
cdfi.seekg(0, ios::beg);
for (int i = 0; i < arraysize; i++)
{
cdfi.read((char*)(&x[i]), sizeof(x[i]));
}
for (int i = 0; i < arraysize; i++)
{
cout << x[i];
}
cout << endl;
char freqarr2[86] = { NULL };
int freqc2[86] = { NULL };
char freqarr[1000];
ifstream freqtable("frequencyTable.txt");
while (!freqtable.eof())
{
freqtable.getline(freqarr, 1000);
}
int c = 0;
for (int i = 0, j = 0; i < strlen(freqarr); j++, i += 2)
{
freqarr2[j] = freqarr[i];
int k = i;
k++;
c++;
freqc2[j] = freqarr[k] - 48;
}
list freqtablist;
for (int i = c - 1; i >= 0; i--)
{
string c = "";
c += freqarr2[i];
freqtablist.push(c, freqc2[i]);
}
tree* root = HuffmanNewTree(freqtablist);
traverse(root);
assigningcodes(root, freqtablist);
freqtablist.display();
node* head = freqtablist.returnhead();
string final = "";
long long int y = 0;
for (int i = 0; i < arraysize; i++)
{
long long int pace = placemaker(x[i]);
for (int j = 0; j < digitcal(x[i]); j++)
{
long long int number = x[i] / pace;
number = number % 10;
y = number + (y * 10);
head = freqtablist.returnhead();
while (head != 0)
{
long long int cd = 0;
encoder(head->code, cd, 0);
if (cd == y)
{
final += head->character;
y = 0;
}
head = head->next;
}
pace = pace / 10;
}
}
cout << "--------------------------------------" << endl;
cout << final << endl;
}
else {
char chararray[96];
int counters[96] = { NULL };
charset(chararray);
charcounter(arr, size, chararray, counters, 96);
list mylist = arrtolist(chararray,counters);
tree* root = HuffmanNewTree(mylist);
traverse(root);
assigningcodes(root, mylist);
string mystring = encodedstring(mylist, arr, size);
int stringsize = mystring.length();
cout << mystring << endl;
int longsize = (stringsize / 19) + 1;
long long int* x = new long long int[longsize];
binsize = longsize;
for (int i = 0; i < longsize; i++)
{
x[i] = 0;
}
for (int i = 0; i < longsize; i++)
{
encoder(mystring, x[i], i * 19);
}
for (int i = 0; i < longsize; i++)
{
cout << x[i];
}
int tosavesize = mylist.nodecounter();
char* arrtosave = new char[tosavesize];
int* counterstosave = new int[tosavesize];
node* head = mylist.returnhead();
for (int i = 0; i < tosavesize; i++)
{
arrtosave[i] = head->character[0];
counterstosave[i] = head->frequency;
head = head->next;
}
ofstream freqtable("frequencyTable.txt");
for (int i = 0; i < tosavesize; i++)
{
freqtable << arrtosave[i] << counterstosave[i];
}
freqtable.close();
cout << endl;
ofstream codefile("CodeFile.bin", ios::binary);
for (int i = 0; i < longsize; i++)
{
codefile.write((char*)(&x[i]), sizeof(x[i]));
}
codefile.close();
}
if(choice == 3){
int datacomp = (size*8)/binsize;
}
system("pause");
return 0;
}
void encoder(string y, long long int& x, int startingpoint)
{
for (int j = startingpoint; j < (startingpoint + 19); j++)
{
if (j > y.length())
{
break;
}
else if (y[j] == '1')
{
x = 1 + (x * 10);
}
else if (y[j] == '2')
{
x = 2 + (x * 10);
}
}
}
long long int decoder(long long int number, long long int place)
{
long long int x = 0;
x = number / place;
if (x < 10)
{
return x;
}
else {
x = x % 10;
return x;
}
}
void charcounter(char para[], int parasize, char character[], int counters[], int size)
{
for (int i = 0; i < size; i++)
{
for (int j = 0; j < parasize; j++)
{
if (character[i] == para[j])
{
counters[i]++;
}
}
}
}
void charset(char character[], int size) {
for (int i = 0, j = 32; i < 96; j++, i++)
{
character[i] = j;
}
}
void displaytable(string character, int counters[], int size)
{
for (int i = 0; i < size; i++)
{
if (counters[i] != 0 && character[i] != ' ')
{
cout << character[i] << " : " << counters[i] << " " << endl;
}
else if (counters[i] != 0 && character[i] == ' ')
{
cout << "Space" << " : " << counters[i] << " " << endl;
}
}
}
tree* HuffmanNewTree(list mylist)
{
list secondlist;
node* head = mylist.returnhead();
tree* root;
root = setbase(head->character, head->next->character, head->frequency,
head->next->frequency);
secondlist.push(root->need, root->info, "", root);
head = head->next->next;
while (true)
{
if (head == NULL)
{
break;
}
else if (head->frequency == head->next->frequency)
{
root = setbase(head->character, head->next->character,
head->frequency, head->next->frequency);
secondlist.Place(root->need, root->info, "", root);
head = head->next->next;
}
else {
secondlist.Place(head->character, head->frequency);
head = head->next;
}
}
head = secondlist.returnhead();
string* mystring = new string[secondlist.nodecounter()];
int number = 0;
while (true)
{
if (secondlist.checkingduplicate())
{
if (head == NULL || head->next == NULL)
{
break;
}
else if (head->frequency == head->next->frequency)
{
root = addtree(head->ptr, head->next->ptr);
secondlist.Place(root->need, root->info, "", root);
secondlist.deletenode(head);
mystring[number] = head->next->character;
number++;
head = head->next->next;
}
else
{
head = head->next;
}
}
}
for (int i = 0; i < number; i++)
{
secondlist.deleteNODE(mystring[i]);
}
head = secondlist.returnhead();
node* mynode ;
while (head != NULL)
{
mynode = head;
if (mynode->ptr == NULL)
{
root = makeleaf(mynode);
mynode->ptr = root;
}
head = head->next;
}
head = secondlist.returnhead();
root = NULL;
mynode = secondlist.removelast();
node* secondlastelementoflist = secondlist.removelast();
root = addtree(mynode->ptr, secondlastelementoflist->ptr);
head = head->next->next;
while (head != NULL)
{
mynode = secondlist.removelast();
root = addtree(root, mynode->ptr);
head = head->next;
}
return root;
}
tree* setbase(string cx, string cy, int x, int y) {
string s1 = "";
s1 += cx;
string s2 = "";
s2 += cy;
tree* p = new tree;
tree* l = new tree;
tree* r = new tree;
l->info = x;
r->info = y;
l->need = cx;
r->need = cy;
l->left = NULL;
l->right = NULL;
r->left = NULL;
r->right = NULL;
int sum = x + y;
s1 += s2;
p->need = s1;
p->info = sum;
p->left = l;
p->right = r;
return p;
}
tree* makeRighttree(tree* node, string x, int y) {
string s1 = "";
s1 += node->need;
string s2 = "";
s2 += x;
tree* p = new tree;
tree* r = new tree;
r->info = y;
r->need = s2;
r->right = NULL;
r->left = NULL;
int sum = node->info + y;
string s = s1 + s2;
p->need = s;
p->info = sum;
p->left = node;
p->right = r;
return p;
}
tree* makelefttree(tree* node, string x, int y) {
string s1 = "";
s1 += node->need;
string s2 = "";
s2 += x;
tree* p = new tree;
tree* r = new tree;
r->info = y;
r->need = s2;
r->right = NULL;
r->left = NULL;
int sum = node->info + y;
string s = s1 + s2;
p->need = s;
p->info = sum;
p->right = node;
p->left = r;
return p;
}
void traverse(tree* root) {
if (root != NULL)
{
cout << root->need << " : " << root->info << endl;
traverse(root->left);
traverse(root->right);
}
}
bool alphasearch(string c, char x) {
int size = c.length();
for (int i = 0; i < size; i++)
{
if (c[i] == x)
{
return true;
}
}
return false;
}
string search(tree* root, char x) {
string code = "";
while (true)
{
if (alphasearch(root->need, x))
{
if (alphasearch(root->left->need, x) && root->left != NULL)
{
code += "1";
root = root->left;
}
else if (alphasearch(root->right->need, x) && root->right != NULL)
{
code += "2";
root = root->right;
}
}
if (root->left == NULL && root->right == NULL)
{
break;
}
}
//cout<<root->need<<" : "<<root->info<<endl;
cout << endl;
return code;
}
tree* addleaf(tree* node, int freq, string c)
{
if (freq > node->info)
{
return makeRighttree(node, c, freq);
}
else if (freq < node->info)
{
return makelefttree(node, c, freq);
}
}
tree* addtree(tree* root, tree* child)
{
tree* parent = new tree;
parent->info = root->info + child->info;
parent->need = root->need + child->need;
if (root->info > child->info)
{
parent->left = child;
parent->right = root;
}
else {
parent->left = root;
parent->right = child;
}
return parent;
}
tree* makeleaf(node* x) {
tree* ftree = new tree;
ftree->info = x->frequency;
ftree->need = x->character;
ftree->left = NULL;
ftree->right = NULL;
return ftree;
}
void assigningcodes(tree* root, list x)
{
node* head = x.returnhead();
while (head != 0)
{
char y = head->character[0];
head->code = search(root, y);
head = head->next;
}
}
string encodedstring(list x, char arr[], int size)
{
string mystring2 = "";
node* head = x.returnhead();
for (int i = 0; i < size; i++)
{
while (head != 0)
{
if (head->character[0] == arr[i])
{
mystring2 += head->code;
}
head = head->next;
}
head = x.returnhead();
}
return mystring2;
}
list arrtolist(char arr[], int counters[], int size ) {
string character = arr;
list mylist;
bool check = false;
for (int i = 0; i < 96; i++)
{
if (counters[i] != 0)
{
string newone = "";
newone += character[i];
if (!check)
{
mylist.push(newone, counters[i]);
check = true;
}
else
{
mylist.Place(newone, counters[i]);
}
}
}
return mylist;
}
int digitcal(long long int number)
{
int cnt = 1;
jump:
long long int digit = number / 10;
if (digit > 0)
{
cnt++;
number = digit;
goto jump;
}
return cnt;
}
long long int placemaker(long long int x)
{
long long int y = 1;
for (int i = 0; i < digitcal(x) - 1; i++)
{
y *= 10;
}
return y;
}