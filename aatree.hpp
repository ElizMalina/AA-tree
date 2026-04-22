
#ifndef AATREE_H
#define AATREE_H

struct AANode {
  int data;
  int level;
  AANode* left;
  AANode* right;
  AANode(int x) noexcept : data(x), level(1), left(this), right(this) {}

  AANode() noexcept : data(0), level(0), left(this), right(this) {}
  static AANode NilAANode;
};

class AATree {
 private:
  AANode* root;
  AANode* NIL;

  void clear(AANode* t) {
    if (t == NIL || t == nullptr) {
      return;
    }
    clear(t->left);
    clear(t->right);
    delete t;
  }

  void skew(AANode*& t) {
    if (t == NIL) {
      return;
    }
    if (t->left->level == t->level) {
      AANode* L = t->left;
      t->left = L->right;
      L->right = t;
      t = L;
    }
  }

  void split(AANode*& t) {
    if (t == NIL) {
      return;
    }
    if (t->right->right->level == t->level) {
      AANode* R = t->right;
      t->right = R->left;
      R->left = t;
      t = R;
      t->level++;
    }
  }

 public:
  AATree() {
    NIL = &AANode::NilAANode;
    root = NIL;
  }

  ~AATree() {
    clear(root);
    root = NIL;
  }

  void insert(AANode*& t, int val) {
    if (t == NIL) {
      t = new AANode(val);
      t->left = t->right = NIL;
    } else {
      if (val < t->data) {
        insert(t->left, val);
      } else if (val > t->data) {
        insert(t->right, val);
      } else {
        return;
      }

      skew(t);
      split(t);
    }
  }

  void remove(AANode*& t, int val) {
    if (t == NIL) {
      return;
    }
    if (val < t->data) {
      remove(t->left, val);
    } else if (val > t->data) {
      remove(t->right, val);
    } else {
      if (t->left != NIL && t->right != NIL) {
        AANode* s = t->right;
        while (s->left != NIL) {
          s = s->left;
        }
        t->data = s->data;
        remove(t->right, s->data);
      } else {
        AANode* tmp = t;
        if (t->left != NIL) {
          t = t->left;
        } else {
          t = t->right;
        }
        delete tmp;
        return;
      }
    }

    if (t->left->level < t->level - 1 || t->right->level < t->level - 1) {
      t->level--;
      if (t->right->level > t->level) {
        t->right->level = t->level;
      }
      skew(t);
      skew(t->right);
      skew(t->right->right);
      split(t);
      split(t->right);
    }
  }

  void add(int X) { insert(root, X); }

  void erase(int X) { remove(root, X); }

  bool finde(int X) {
    AANode* curr = root;
    while (curr != NIL) {
      if (curr->data == X) {
        return true;
      }
      if (X < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return false;
  }

  int getRootLevel() { return (root == NIL) ? 0 : root->level; }
};

#endif
