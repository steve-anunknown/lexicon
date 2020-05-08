#include <iostream>
#include <string>

class lexicon{
  private:
  struct node {
    std::string word;
    unsigned int frequency;
    node *left,*right,*parent;
    node (const std::string &w,unsigned int f, node *l, node *r,node *p):
      word(w),frequency(f),left(l),right(r),parent(p){};
  };
  node *root;
  public:
  lexicon():root(nullptr){};
  ~lexicon(){ purge(root); }

  void insert(const std::string &s) {
    if (root==nullptr) root = new node (s, 1, nullptr, nullptr, nullptr);
    else insert(root, s);
     }
  int lookup(const std::string &s)const { rec_lookup(root, s); }
  int depth(const std::string &s)const {bool found=false; rec_depth(root, s, found);}
  void replace(const std::string &s1, const std::string &s2){
    if (rec_find(root,s1)==nullptr) return;
    if (rec_find(root,s1)!=nullptr && rec_find(root,s2)==nullptr){

    }
    if (rec_find(root,s1) && rec_find(root,s2)){

    }
  }

  private:
  void remove(node *t, const std::string &s){
  }
  node * rec_find(node *t,const std::string &s){
    if (t!=nullptr){
      if (s==t->word) return t;
      if (s>t->word) return rec_find(t->right, s);
      if (s<t->word) return rec_find(t->left, s); 
    }
    else return nullptr;
  }
  int rec_depth(node *t,const std::string s, bool &flag)const {
    if (t==nullptr) {flag=false; return 0;}
    if (s==t->word) {flag=true; return 1;} 
    if (s>t->word) {
       int result=rec_depth(t->right, s, flag);
       (flag==true)? ++result : 0;
       return result;
       }
    if (s<t->word) {
       int result=rec_depth (t->left, s, flag);
       (flag==true)? ++result : 0;
       return result;
       }
  }
  int rec_lookup(node *t, const std::string &s)const{
    if (t==nullptr) return 0;
    if (s>t->word) rec_lookup(t->right, s);
    if (s<t->word) rec_lookup(t->left, s);
    if (s==t->word) return t->frequency;
  }
  static bool insert(node *t, const std::string &s) {
    if (s < t->word) {
      if (t->left == nullptr) {
      t->left = new node (s, 1, nullptr, nullptr, t);
      return true;
      }
      else
        return insert(t->left, s);
    }
    else if (s > t->word) {
      if (t->right == nullptr) {
      t->right = new node(s, 1, nullptr, nullptr, t);
      return true;
      }
      else
        return insert(t->right, s);
    }
    else {
      ++(t->frequency);
      return true;
    }
  }
  static void purge(node *t){
    if (t!=nullptr){
      purge(t->left);
      purge(t->right);
      delete t;
    }
}