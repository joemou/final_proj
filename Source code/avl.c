#include <gtk/gtk.h>
#include "basic_func.h"
#include "avl.h"

#define debug g_print("debug %d\n", __LINE__)

void create(node **head, const char *name, int game_played,float feiled_goal_percentage,float three_point_percentage,float points_per_game,float steal_per_game){
  node *temp = (node *)malloc(sizeof(node));
  
  strcpy(temp->name, name);
  temp->game_played = game_played;
  temp->feiled_goal_percentage = feiled_goal_percentage;
  temp->three_point_percentage = three_point_percentage;
  temp->points_per_game = points_per_game;
  temp->steal_per_game = steal_per_game;

  temp->next = NULL;
  temp->left = NULL;
  temp->right = NULL;
  temp->height = 1;

  if(*head==NULL){
    *head = temp;
  }
  else{
    temp->next = *head;
    *head = temp;
  }
}

/*for AVL tree https://www.youtube.com/watch?v=jDM6_TnYIqE*/

// void printInorder(struct node* node) {
//   if (node == NULL){
//     return;
//   }
//   printInorder(node->left);
//   printf("%s %d %.2f %.2f %.2f %.2f\n",node->name,node->game_played,node->feiled_goal_percentage,node->three_point_percentage,node->points_per_game,node->steal_per_game);
//   printInorder(node->right);
// }

int height(struct node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

struct node *RR(struct node *y) {
  node *x = y->left;
  node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct node *LL(struct node *x) {
  node *y = x->right;
  node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(struct node *root) {
  if (root == NULL)
    return 0;
  return height(root->left) - height(root->right);
}

struct node *insert(struct node *root, struct node *node) {
  if (root == NULL)
    return node;

  int flag = strcmp(node->name,root->name);

  if (flag < 0){
    root->left = insert(root->left, node);
  }
  else if (flag > 0){
    root->right = insert(root->right, node);
  }
  else{
    g_print("name exist\n");
    return node; // node with same name already exists
  }
  // Update height of this node
  root->height = 1 + max(height(root->left), height(root->right));

  // Check the balance factor and rotate the tree if necessary
  int balance = getBalance(root);

  //right rotation
  if (balance > 1 && strcmp(node->name, root->left->name) < 0)
    return RR(root);
  //left rotation
  if (balance < -1 && strcmp(node->name, root->right->name) > 0)
    return LL(root);
  //left-right rotation
  if (balance > 1 && strcmp(node->name, root->left->name) > 0) {
    root->left = LL(root->left);
    return RR(root);
  }
  //right-left rotaion
  if (balance < -1 && strcmp(node->name, root->right->name) < 0) {
    root->right = RR(root->right);
    return LL(root);
  }
  //if balance no rotation
  return root;
}

struct node *min_name(struct node *node) {
  struct node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

struct node *delete(struct node **head,struct node *point,struct node *root, const char *name) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (strcmp(name,root->name)<0)
    root->left = delete(head,point,root->left, name);
  else if (strcmp(name,root->name)>0)
    root->right = delete(head,point,root->right, name);
  //when find it(flag==0)
  else {
    //just has one child and no child
    if ((root->left == NULL) || (root->right == NULL)) {
      struct node *temp = root->left ? root->left : root->right;


      //deal with linkedlist part
      //no child
      if (temp == NULL) {
        temp = root;

        node *temp2 = point;
        node *prev = NULL;
        if(root==temp2){
          (*head) = (*head)->next;
        }
        else{
          while(temp2!=root){
            prev = temp2;
            temp2 = temp2->next;
          }
          prev->next = temp2->next;
        }

        root = NULL;
      }
      //one child 
      else{

        //cuz next cannot *root = *temp;
        strcpy(root->name, temp->name);
        root->right = temp->right;
        root->left = temp->left;
        root->height = temp->height;

        //deal with linkedlist part
        node *temp2 = point;
        node *prev = NULL;
        if(temp==point){
          (*head) = (*head)->next;
        }
        else{
          while(temp2!=temp){
            prev = temp2;
            temp2 = temp2->next;
          }
          prev->next = temp2->next;
        }

      }
    }
    //two children 
    else {

      //find the right child then its leftest side(i norder) making it banlance
      struct node *temp = min_name(root->right);

      //copy the temp data and rewrite root
      strcpy(root->name, temp->name);
      root->game_played = temp->game_played;

      //delete the copied node
      root->right = delete(head, point, root->right, temp->name);
      
    }

  }

  //rebanlance the tree
  if (root == NULL)
    return root;

  root->height = 1 + max(height(root->left),height(root->right));


  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) > 0){
    printf("aa\n");
    return RR(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    printf("bb\n");
    root->left = LL(root->left);
    return RR(root);
  }

  if (balance < -1 && getBalance(root->right) < 0){
    printf("%d\n",balance);
    return LL(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    printf("dd\n");
    root->right = RR(root->right);
    return LL(root);
  }

  return root;
}

void print_player(node *node) {
  printf("%s %d %.2f %.2f %.2f %.2f\n",node->name,node->game_played,node->feiled_goal_percentage,node->three_point_percentage,node->points_per_game,node->steal_per_game);
} 

struct node *AVL_STRING_SEARCH(node *root, const char *name) {
  if(root==NULL){
    return root;
  }
  
  int flag = strcmp(name, root->name);
  
  if(flag==0){
    return root;
  }
  else if(flag<0){
    return AVL_STRING_SEARCH(root->left, name);
  }
  else{
    return AVL_STRING_SEARCH(root->right, name);
  }
}

void print_linklist(node *head) {
  node *temp = head;
  printf("\n");
  while(temp!=NULL){
    printf("%s %d %.2f %.2f %.2f %.2f\n",temp->name,temp->game_played,temp->feiled_goal_percentage,temp->three_point_percentage,temp->points_per_game,temp->steal_per_game);
    temp = temp->next;
  }
}