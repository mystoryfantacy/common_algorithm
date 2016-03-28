// 红黑树 定义
// 1. 二叉查找树
// 2. 红链接均为左链接
// 3. 没有任意一个节点同时和两个红链接相连
// 4. 完美黑色平衡，从任一空链接到根节点的路径上的黑链接数量相同

const bool Red = true;
const bool Black = false;

template<typename Key, typename Val>
struct Node {
  Key key;
  Val val;
  Node<Key,Val> *left, *right;
  int N;
  bool color;
  Node(Key key, Val val, int N, bool color) {
    this.key = key;
    this.val = val;
    this.N = N;
    this.color = color;
  }
};

//关键操作1：左旋，右旋， 红色左移， 红色右移
//关键操作2：查找，插入，删除（最大、最小）
//（2）操作过程中要通过（1）保证树的有序性和平衡性
template <typename Key, typename Val>
class RedBlackBST {
  public:
    int size(Node<Key,Val> *h) {
      if (h == NULL) return 0;
      return h->N;
    };
    void put(Key key, Value val) {
      root = put(root,key,val);
      root->color = Black;
    };
    Node<Key,Val>* get(Key key) {
      return get(root,key);
    }
    bool isRed(Node<Key,Val>* h) {
      if (h == NULL) return Black;
      return h->color;
    };
    void deleteMin() {
      if (!isRed(root->left) && !isRed(root->right))
        root->color = Red;
      root = deleteMin(root);
      if (root != NULL) root->color = Black;
    }
    void deleteMax() {
      if (!isRed(root->left) && !isRed(root->right))
        root->color = Red;
      root = deleteMax(root);
      if (root != NULL) root->color = Black;
    }
    void deleteKey(Key key) {
      if (isRed(root->left) && !isRed(root->right))
        root->color = Red;
      root = deleteKey(root, key);
      if (root != NULL) root->color = Black;
    }
    Node<Key,Val>* min(Node<Key,Val>* h) {
      if (h == NULL) return NULL;
      else if (h->left == NULL) return h;
      else return min(h->left);
    }
  protected:
    Node<Key,Val>* rotateLeft(Node<Key,Val> *h) {
      Node<Key,Val>* x = h->right;
      h->right = x->left;
      x->left = h;
      x->color = h->color;
      h->color = Red;
      x->N = h->N;
      h->N = size(h->left) + size(h->right) + 1;
      return x;
    };
    Node<Key,Val>* rotateRight(Node<Key,Val> *h) {
      Node<Key,Val>* x = h->left;
      h->left = x->right;
      x->right = h;
      x->color = h->color;
      h->color = Red;
      x->N = h->N;
      h->N = size(h->left) + size(h->right) + 1;
      return x;
    }
    void flipColors(Node<Key,Val> *h) {
      h->color = !h->color;
      h->right->color = !h->right->color;
      h->left->color = !h->left->color;
    }
    Node<Key,Val>* put(Node<Key,Val>* h, Key key, Val val) {
      if (h == NULL) 
        return new Node<Key,Val>(key,val,1,Red);
      if (key > h->key) h = put(h->right,key,val);
      else if (key < h->key) h = put(h->left,key,val);
      else h->val = val;

      if (!isRed(h->left) && isRed(h->right)) rotateLeft(h);
      if (isRed(h->left) && isRed(h->left->left)) rotateRight(h);
      if (isRed(h->left) && isRed(h->right)) flipColors(h);

      h->N = size(h->left) + size(h->right) + 1;
      return h;
    }
    Node<Key,Val>* get(Node<Key,Val>* h, Key key) {
      while(h != NULL) {
        if (key < h->key) h = h->left;
        else if (key > h->key) h = h->right;
        else if (key == h->key) return h;
      }
      return NULL;
    }
    Node<Key,Val>* moveRedLeft(Node<Key,Val>* h) {
      flipColors(h);
      if (isRed(h->right->left)) {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
      }
      return h;
    }
    Node<Key,Val>* moveRedRight(Node<Key,Val>* h) {
      flipColors(h);
      if (isRed(h->left->left)) {
        h = rotateRight(h);
      }
      return h;
    }
    Node<Key,Val>* deleteMin(Node<Key,Val>* h) {
      if (h == NULL) return NULL;
      Node<Key,Val>* x;
      if (h->left == NULL) {
        delete h;
        return NULL;
      }
      if (!isRed(h->left) && !isRed(h->left->left))
        h = moveRedLeft(h);
      h->left = deleteMin(h->left);
      return balance(h);
    }
    Node<Key,Val>* deleteMax(Node<Key,Val>* h) {
      if (isRed(h->left))
        h = rotateRight(h);
      if (h->right = NULL) {
        delete h;
        return NULL;
      }
      if (!isRed(h->right) && !isRed(h->right->left))
        h = moveRedRight(h);
      h = deleteMax(h->right);
      return balance(h);
    }
    Node<Key,Val>* deleteKey(Node<Key,Val>* h, Key key) {
      if (key < h->key) {
        if (!isRed(h->left) && !isRed(h->left->left))
          h = moveRedLeft(h);
        h = deleteKey(h->left, key);
      }
      else {
        if (isRed(h->left))
          h = rotateRight(h);
        if (key == h->key && h->right == NULL) {
          delete h;
          return NULL;
        }
        if (!isRed(h->right) && !isRed(h->right->left))
          h = moveRedRight(h);
        if (key == h->key) {
          Node<Key,Val>* min_key = min(h->right);
          h->key = min_key->key;
          h->val = min_key->val;
          h->right = deleteMin(h->right);
        }
        else h->right = deleteKey(h->right, key);
      }
      return balance(h);
    }
    Node<Key,Val>* balance(Node<Key,Val>* h) {
      if (isRed(h->right)) h = rotateLeft(h);
      if (isRed(h->left) && isRed(h->left->left))
        h = rotateRight(h);
      if (isRed(h->left) && isRed(h->right))
        flipColors(h);
      h->N = size(h->left) + size(h->right) + 1;
      return h; 
    }

  private:
    Node<Key,Val>* root;
};

