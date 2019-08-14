/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node *top = t -> right;
    t -> right = top -> left;
    top -> left = t;

    t -> height = max(heightOrNeg1(t -> left), heightOrNeg1(t -> right)) + 1;
    top -> height = max(heightOrNeg1(top -> left), heightOrNeg1(top -> right)) + 1;
    t = top;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node *top = t -> left;
    t -> left = top -> right;
    top -> right = t;

    t -> height = max(heightOrNeg1(t -> left), heightOrNeg1(t -> right)) + 1;
    top -> height = max(heightOrNeg1(top -> left), heightOrNeg1(top -> right)) + 1;
    t = top;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int balanceFactor = heightOrNeg1(subtree -> left) - heightOrNeg1(subtree -> right);
    int leftBalanceFactor;
    int rightBalanceFactor;
    if (balanceFactor == -2) {
      rightBalanceFactor = heightOrNeg1(subtree -> right -> left) - heightOrNeg1(subtree -> right -> right);
      if (rightBalanceFactor == 1) {
        rotateRightLeft(subtree);
      } else {
        rotateLeft(subtree);
      }
    } else if (balanceFactor == 2) {
      leftBalanceFactor = heightOrNeg1(subtree -> left -> left) - heightOrNeg1(subtree -> left -> right);
      if (leftBalanceFactor == -1) {
        rotateLeftRight(subtree);
      } else {
        rotateRight(subtree);
      }
    }


}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{

  if (subtree == NULL) {
    subtree = new Node(key, value);
  }

  if (key < subtree -> key) {
    insert(subtree -> left, key, value);
    rebalance(subtree);
  } else if (subtree -> key < key) {
    insert(subtree -> right, key, value);
    rebalance(subtree);
  } else {
    subtree->height = max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right)) + 1;
    return;
  }

  subtree->height = max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right)) + 1;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
      remove(subtree -> left, key);
      rebalance(subtree);
    } else if (key > subtree->key) {
      remove(subtree -> right, key);
      rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
          delete subtree;
          subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {

          Node* current = subtree -> left;
          while (current -> right -> right != NULL) {
            current = current -> right;
          }
          Node* iOP = current -> right;
          swap(subtree, iOP);
          current -> right = iOP -> left;

          delete iOP;
          iOP = NULL;

        } else {
          if (subtree -> left != NULL) {
            Node* temp = subtree;
            subtree = subtree -> left;
            delete temp;
            temp = NULL;
          } else {
            Node* temp = subtree;
            subtree = subtree -> right;
            delete temp;
            temp = NULL;
          }
        }
        // your code here
    }
}
