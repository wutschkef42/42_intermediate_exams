

#include <stdio.h>
#include <stdlib.h>

typedef struct		s_node
{
	int				data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


/*
 * Appends rightList to the end of leftList
 *
 *	1) Get last node of leftList
 *	2) Connect it with first node of rightList
 *	3) Get last node of rightList
 *	4) Connect it with head of the list
 *
*/
t_node	*concat(t_node *leftList, t_node *rightList)
{
	t_node	*leftLast;
	t_node	*rightLast;

	if (!leftList)
		return (rightList);
	if (!rightList)
		return (leftList);

	// get last elements of dll, O(1)
	leftLast = leftList->left;
	rightLast = rightList->left;
	
	// connect last of leftList with first of rightList
	leftLast->right = rightList;
	rightLast->left = leftLast;

	// make circular
	leftList->left = rightLast;
	rightLast->right = leftList;
	
	return (leftList);
}

/*
 * Converts binary search tree to circular doubly linked list
 * Returns head of dll
 *
 *	1) Recursively convert left sub-tree to dll -> leftList
 *	2) Recursively convert right sub-tree to dll -> rightList
 *	3) Make circular dll of root of the tree, l/r point to itself
 *	4) Append leftList and list of single root node
 *	5) Append 4) and rightList
 *
*/
t_node	*bst2dll(t_node *root)
{
	t_node	*leftList;
	t_node	*rightList;

	if (!root)
		return (NULL);
	// recursively convert left and right subtrees
	leftList = bst2dll(root->left);
	rightList = bst2dll(root->right);

	// make dll of root
	root->left = root->right = root;
	return (concat(concat(leftList, root), rightList));
}

t_node	*make_node(int data)
{
	t_node	*new;

	if(!(new = malloc(sizeof(t_node))))
		return (NULL);
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	print_dll(t_node *head)
{
	t_node	*tmp;

	printf("The resulting list is:\n");
	tmp = head;
	do
	{
		printf("%d ", tmp->data);
		tmp = tmp->right;
	} while (tmp != head);
	printf("\n");
}

int		main()
{
	t_node	*root = make_node(15);
	root->left = make_node(10);
	root->right = make_node(20);
	root->left->left = make_node(5);
	root->left->right = make_node(12);
	root->right->left = make_node(17);
	root->right->right = make_node(25);

	t_node	*dll = bst2dll(root);
	print_dll(dll);
	
	return(0);
	
}
