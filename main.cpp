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

    static void place_down_right(node *right_word,node *parent, node *runner){
      while (runner!=NULL){
        parent=runner;
        runner=runner->right;
      }
      parent->right=right_word;
    }

    static void insert_word(node *parent, node *runner, const string &s,unsigned int freq){
            while (runner!=NULL){  
                    parent=runner;  
                    if (s>runner->word) runner=runner->right;  
                    else runner=runner->left;  
            }  
            if (s>parent->word){  
                    parent->right= new node (s,freq);  
                   // if (parent->right==NULL) exit(3);  
            }  
            else {  
                  parent->left= new node (s,freq);  
                  // if (parent->left==NULL) exit(3);  
            }  

    }

    static void find_word_and_parent(node *parent, node *runner,const string &s){
      while (runner!=NULL){
        if (s>runner->word) {parent=runner; runner=runner->right;}
        else if (s<runner->word) {parent=runner; runner=runner->left;}
        else break;
      }
    }

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
                find_word_and_parent(parent_s1, runner_s1, s1);//this seems to work fine
                node *parent_s2=root;//parent of runner  
                node *runner_s2=root;//runner points to s2  
                find_word_and_parent(parent_s2, runner_s2, s2); //for some reason this doesn't work  
                if (runner_s1==NULL) return ;  
                unsigned int freq1=runner_s1->freq;  
                if (runner_s1==root){  
                        if (runner_s1->left!=NULL){  
                                root=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                place_down_right(runner_s1->right, temppar, temprun); 
                        }  
                        else root=runner_s1->right;  
                }  
                else if (parent_s1->left==runner_s1){ //runner is left child  
                        if (runner_s1->left!=NULL) {  
                                parent_s1->left=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                place_down_right(runner_s1->right, temppar, temprun); 
                        }  
                        else parent_s1->left=runner_s1->right;  
                }  
                else { // runner is right child  
                        if (runner_s1->left!=NULL){  
                                parent_s1->right=runner_s1->left;  
                                node *temppar=runner_s1->left;  
                                node *temprun=runner_s1->left;  
                                place_down_right(runner_s1->right, temppar, temprun);  
                        }  
                        else parent_s1->right=runner_s1->right;  
                }  
                delete runner_s1 ; runner_s1=NULL;  
                if (runner_s2==NULL) {  
                        if (root==NULL) {root= new node (s2,freq1);/* if (root==NULL) exit(3);*/}  
                        node *temppar=root;  
                        node *temprun=root;  
                        insert_word(temppar, temprun, s2, freq1);  
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