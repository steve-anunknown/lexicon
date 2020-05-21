#include <iostream>  
#include <string>  
  
using namespace std;  
  
class lexicon {  
    struct node {  
            string word;  
            unsigned int freq;  
            node *left,*right;  
            node (const string &s,unsigned int f):word(s),freq(f),left(NULL),right(NULL){};  
    };  
  
    node *root;  
    static void purge (node *t){  
            if (t==NULL) return ;  
            purge (t->left);  
            purge(t->right);  
            delete t;  
            t=NULL;  
    }  
    static void print (ostream &out, node *t){  
            if (t==NULL) return;  
            print(out,t->left);  
            out<<t->word<<' '<<t->freq<<endl;  
            print(out,t->right);  
            return ;  
    }  
  
    public:  
    lexicon():root(NULL){}  
    ~lexicon(){ purge (root) ; root=NULL; }  
  
    void insert (const string &s){  
            if (root==NULL) { root=new(nothrow) node (s,1); if (root==NULL) exit(2); return ; }  
            node *parent=root;  
            node *runner=root;  
            while (runner!=NULL){  
                parent=runner;  
                if (s>runner->word) runner=runner->right;  
                else if (s<runner->word) runner=runner->left;  
                else {++(runner->freq); return ;}  
            }  
            if (s>parent->word){  
                parent->right=new(nothrow) node (s,1);   
                if(parent->right==NULL) exit(2);  
                }  
                else { 
                  parent->left=new(nothrow) node (s,1);  
                  if(parent->left==NULL) exit(2);  
                }  
    }  
  
    int lookup(const string &s)const {  
            node *runner=root;  
            while (runner!=NULL){  
                    if (s>runner->word) runner=runner->right;  
                        else if (s<runner->word) runner=runner->left;  
                        else  return runner->freq;  
                }  
                return 0;  
        }  
  
        int depth (const string &s)const {  
                node *runner=root;  
                int result=1;  
                while (runner!=NULL){  
                        if (s>runner->word){ runner=runner->right; ++result;}  
                        else if (s<runner->word){ runner=runner->left; ++result;}  
                        else  return result;  
                }  
                return 0;  
        }  
  
        void replace (const string &s1, const string &s2){  
                if (s1==s2) return ;  
                node* parent_s1=root;//parent of runner  
                node* runner_s1=root;//runner points to s1  
                while (runner_s1!=NULL){  
                        if (s1>runner_s1->word){parent_s1=runner_s1; runner_s1=runner_s1->right;}  
                        else if (s1<runner_s1->word){parent_s1=runner_s1; runner_s1=runner_s1->left;}  
                        else  break;  
                }  
                node *parent_s2=root;//parent of runner  
                node *runner_s2=root;//runner points to s2  
                while (runner_s2!=NULL){  
                        if (s2>runner_s2->word){parent_s2=runner_s2; runner_s2=runner_s2->right;}  
                        else if (s2<runner_s2->word){parent_s2=runner_s2; runner_s2=runner_s2->left;}  
                        else  break;  
                }  
                if (runner_s1==NULL) return ;  
                unsigned int freq1=runner_s1->freq;  
                if (runner_s1==root){  
                        if (runner_s1->left!=NULL){  
                                root=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                while (temprun!=NULL){  
                                        temppar=temprun;  
                                        temprun=temprun->right;  
                                }  
                                temppar->right=runner_s1->right;  
                        }  
                        else root=runner_s1->right;  
                }  
                else if (parent_s1->left==runner_s1){ //runner is left child  
                        if (runner_s1->left!=NULL) {  
                                parent_s1->left=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                while (temprun!=NULL){  
                                        temppar=temprun;  
                                        temprun=temprun->right;  
                                }  
                                temppar->right=runner_s1->right;  
                        }  
                        else parent_s1->left=runner_s1->right;  
                }  
                else { // runner is right child  
                        if (runner_s1->left!=NULL){  
                                parent_s1->right=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                while (temprun!=NULL){  
                                        temppar=temprun;  
                                        temprun=temprun->right;  
                                }  
                                temppar->right=runner_s1->right;  
                        }  
                        else parent_s1->right=runner_s1->right;  
                }  
                delete runner_s1 ; runner_s1=NULL;  
                if (runner_s2==NULL) {  
                        if (root==NULL) {root= new node (s2,freq1);/* if (root==NULL) exit(3);*/}  
                        node *temppar=root;  
                        node *temprun=root;  
                        while (temprun!=NULL){  
                                temppar=temprun;  
                                if (s2>temprun->word) temprun=temprun->right;  
                                else temprun=temprun->left;  
                        }  
                        if (s2>temppar->word){  
                                temppar->right= new node (s2,freq1);  
                               // if (temppar->right==NULL) exit(3);  
                        }  
                        else {  
                                temppar->left= new node (s2,freq1);  
                               // if (temppar->right==NULL) exit(3);  
                        }  
                }  
                else  runner_s2->freq+=freq1;  
        }  
  
        friend ostream & operator << (ostream &out, const lexicon &l){  
                print(out, l.root);  
                return out;  
        }  
};  
#ifndef CONTEST  
int main (){  
        lexicon l;  
  
        l.insert("the");  
        l.insert("boy");  
        l.insert("and");  
        l.insert("the");  
        l.insert("wolf");  
  
        cout<<l<<endl;  
          
        cout<<l.lookup("and")<<' '<<l.depth("and")<<"\n";  
        cout<<l.lookup("boy")<<' '<<l.depth("boy")<<"\n";  
        cout<<l.lookup("the")<<' '<<l.depth("the")<<"\n";  
        cout<<l.lookup("wolf")<<' '<<l.depth("wolf")<<"\n";  
        cout<<l.lookup("dummy")<<' '<<l.depth("dummy")<<"\n";  
  
        l.replace("and","dummy");  
        cout<<l.lookup("wolf")<<' '<<l.depth("wolf")<<"\n";  
        cout<<l.lookup("dummy")<<' '<<l.depth("dummy")<<"\n";  
        cout<<l<<"\n";  
  
        l.replace("boy","dummy");  
        cout<<l.lookup("wolf")<<' '<<l.depth("wolf")<<"\n";  
        cout<<l.lookup("dummy")<<' '<<l.depth("dummy")<<"\n";  
        cout<<l<<"\n";  
  
        l.replace("the","dummy");  
        cout<<l.lookup("wolf")<<' '<<l.depth("wolf")<<"\n";  
        cout<<l.lookup("dummy")<<' '<<l.depth("dummy")<<"\n";  
        cout<<l<<"\n";  
        l.replace("wolf","dummy");  
        cout<<l.lookup("wolf")<<' '<<l.depth("wolf")<<"\n";  
        cout<<l.lookup("dummy")<<' '<<l.depth("dummy")<<"\n";  
  
        cout<<l<<endl;  
  
        return 0;  
}  
#endif  