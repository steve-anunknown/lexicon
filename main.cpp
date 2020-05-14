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

  lexicon() : root ( nullptr ) {std::cout<<"constructor check\n";};
  ~lexicon() { purge(root) ; }

  void insert(const std::string &s) {
    if (root==nullptr) root = new node (s, 1, nullptr, nullptr, nullptr);
    else insert(root, s);
    std::cout<<"done\n";
  }
  
  int lookup(const std::string &s)const { return rec_lookup(root, s); }
  
  int depth(const std::string &s)const {
    bool found=false;
    return rec_depth(root, s, found);
  }
  
  void replace(const std::string &s1, const std::string &s2){
    node *node_s1=rec_find(root,s1);
    node *node_s2=rec_find(root,s2);
    if (node_s1==root)
    if (node_s1==nullptr) return;
    if (node_s1!=nullptr && node_s2==nullptr){
      //remove s1 and insert s2 with s1's frequency
      int freq=node_s1->frequency-1;
      remove (node_s1);
      insert (root, s2);
      rec_find(root,s2)->frequency+=freq;
    }
    if (node_s1!=nullptr && node_s2!=nullptr){
      //remove s1 and update s2's frequency to s1.freq+s2.freq
      node_s2->frequency+=node_s1->frequency;
      remove (node_s1);
    }
  }

  friend std::ostream & operator << (std::ostream &out , const lexicon &l){
    print(out, l.root);
    return out;
  }

  private:


  static void print (std::ostream &out, node *t){
    if (t!=nullptr){
      print(out,t->left);
      out<<t->word<<' '<<t->frequency<<std::endl;
      print(out,t->right);
    }
  }


  static void remove(node *t){
    //if t has 2 children check
      //replace with t->left
    //if t has 1 child check
      //replace with only child
    if (t==nullptr) return;
    else if (t->parent==nullptr){
      if (t->left!=nullptr && t->right!=nullptr){
        std::string right_word=t->right->word;
        t=t->left;
        insert(t, right_word);
      }
      else if (t->left!=nullptr && t->right==nullptr) t=t->left;
      else if (t->left==nullptr && t->right!=nullptr) t=t->right;
    }
    else if (t->parent!=nullptr){
      if (!is_left_child(t)) {
        if (t->left!=nullptr && t->right!=nullptr){
          std::string right_word=t->right->word;
          t->parent->right=t->left;
          insert(t->parent, right_word);
        }
        else if (t->left!=nullptr && t->right==nullptr) t->parent->right=t->left;
        else if (t->left==nullptr && t->right!=nullptr) t->parent->right=t->right;
        delete t;
      }
      else {
        if (t->left!=nullptr && t->right!=nullptr){
          std::string right_word=t->right->word;
          t->parent->left=t->left;
          insert(t->parent, right_word);
        }
        else if (t->left!=nullptr && t->right==nullptr) t->parent->left=t->left;
        else if (t->left==nullptr && t->right!=nullptr) t->parent->left=t->right;
        delete t;
      }
    }
  }
  
  static bool is_left_child(node *t){
    if (t==nullptr) return false;
    if (t->parent->left==t) return true;
    else return false;
    }

  node * rec_find(node *t,const std::string &s){
    if (t!=nullptr){
      if (s==t->word) return t;
      else if (s>t->word) return rec_find(t->right, s);
      else return rec_find(t->left, s); 
    }
    else return nullptr;
  }
  
  int rec_depth(node *t,const std::string s, bool &flag)const {
    if (t==nullptr) {flag=false; return 0;}
    else if (s==t->word) {flag=true; return 1;} 
    else if (s>t->word) {
       int result=rec_depth(t->right, s, flag);
       (flag==true)? ++result : result=0;
       return result;
       }
    else  {
       int result=rec_depth (t->left, s, flag);
       (flag==true)? ++result : result=0;
       return result;
       }
  }
  
  int rec_lookup(node *t, const std::string &s)const{
    if (t==nullptr) return 0;
    else if (s>t->word) return rec_lookup(t->right, s);
    else if (s<t->word) return rec_lookup(t->left, s);
    else  return t->frequency;
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
};

#ifndef CONTEST
int main (){
  lexicon l;
  l.insert("the");
  l.insert("boy");
  l.insert("and");
  l.insert("the");
  l.insert("wolf");

  std::cout<<l.lookup("the")<<"\n";
  std::cout<<l.depth("and")<<"\n";

  std::cout<<l;

  l.replace("boy", "wolf");
  std::cout<<l;

  std::cout<<l.depth("and");

  return 0;
}
#endif