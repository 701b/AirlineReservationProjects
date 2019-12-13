#define _CRT_SECURE_NO_WARNINGS

#include "reservation.h"

#define BLACK 0
#define RED 1

#define SPACE_SIZE 2

int compare(const void* a, const void* b) {
	RESERVATION n1 = *(RESERVATION*)a;
	RESERVATION n2 = *(RESERVATION*)b;
	if (n1.reservationNumber < n2.reservationNumber)
		return -1;
	if (n1.reservationNumber > n2.reservationNumber)
		return 1;
	return 0;

}

void LeftRotate(RESERVATION_RECORD* reservationRecord, RBT_NODE* x) {
	if (!x || !x->right) return;

	RBT_NODE* x_right = x->right;
	x->right = x_right->left;

	if (x->right != NULL)
		x->right->parent = x;

	x_right->parent = x->parent;

	if (x->parent == NULL)
		reservationRecord->root = x_right;
	else if (x == x->parent->left)
		x->parent->left = x_right;
	else
		x->parent->right = x_right;

	x_right->left = x;
	x->parent = x_right;
}
void RightRotate(RESERVATION_RECORD* reservationRecord, RBT_NODE* x) {
	if (!x || !x->left) return;

	RBT_NODE* x_left = x->left;
	x->left = x_left->right;

	if (x_left->right != NULL)
		x_left->right->parent = x;

	x_left->parent = x->parent;

	if (x_left->parent == NULL)
		reservationRecord->root = x_left;
	else if (x == x->parent->left)
		x->parent->left = x_left;
	else
		x->parent->right = x_left;

	x_left->right = x;
	x->parent = x_left;
}

void fixinsert(RESERVATION_RECORD* rbt, RBT_NODE* z) {
	// 위반 가능성은 다음 두 가지다.
	// z == root일때, 그냥 z를 black으로 바꿔주면 된다.
	// z->parent == red면 red-red violation으로 문제가 생긴다.
	// red-red violation을 z->parent가 black이 되거나 root가 될 때까지 위로 올린다.
	RBT_NODE* y;
	while (z->parent != NULL && z->parent->color == RED)
	{
		//case 123 z->parent == z->parent->parent->left
		if (z->parent == z->parent->parent->left) {
			// case 1 삼촌 y == red
			y = z->parent->parent->right;
			if (y && y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				// case 2 y == black (y == NIL일 가능성 있음) && z == z->parent->right
				if (z == z->parent->right)
				{
					z = z->parent;
					LeftRotate(rbt, z);
				}
				// case 3 z == z->parent->left
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotate(rbt, z->parent->parent);
			}
		}
		// case 456 z->parent == z->parent->parent->right
		else
		{
			// case 1 삼촌 y == red
			y = z->parent->parent->left;
			if (y && y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				// case 2 y == black (y == NIL일 가능성 있음) && z == z->parent->left
				if (z == z->parent->left)
				{
					z = z->parent;
					RightRotate(rbt, z);
				}
				// case 3 z == z->parent->right
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(rbt, z->parent->parent);
			}
		}
	}
	rbt->root->color = BLACK;
}
void fixdelete(RESERVATION_RECORD* rbt, RBT_NODE* x, RBT_NODE* xp)
{
	// x가 NIL일 수 있다.
	// x가 red면 간단하게 해결된다.
	// x가 black일때가 문제다.
	RBT_NODE* w;
	// 삭제된 y->parent 와 x 둘다 red일경우 이것도 심각한 문제는 아니다.
	while (x != rbt->root && (x == NULL || x->color == BLACK))
	{
		// 문제는 black이다.
		// x에 extra black을 부여하면 x는 double black 또는 red + black
		// x가 NIL이면서 double black일 수 있다.
		// x가 extra black인데 w가 NIL일 가능성은 없다. RBT이기 때문
		// case 1234 x가 parent의 left
		if (x) xp = x->parent;

		if ((!x && x == xp->left) || (x && x == x->parent->left)) {
			if (x) xp = x->parent;
			w = xp->right;
			// case 1 w == red
			if (w->color == RED) {
				w->color = BLACK;
				xp->color = RED;
				LeftRotate(rbt, xp);
				if (x) w = x->parent->right;
				else w = xp->right;
			}
			// case 2 w == black && w->left == w->right == black
			if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
				w->color = RED;
				if (x) x = x->parent;
				else x = xp;
			}

			else
			{
				// case 3 w == black && w->left == red
				if (!w->right || w->right->color == BLACK)
				{
					if (w->left) w->left->color = BLACK;
					w->color = RED;
					RightRotate(rbt, w);
					if (x) w = x->parent->right;
					else w = xp->right;
				}
				// case 4 w == black && w->right == red
				if (x) w->color = x->parent->color;
				else w->color = xp->color;
				if (x) x->parent->color = BLACK;
				else xp->color = BLACK;
				if (w->right) w->right->color = BLACK;
				if (x) LeftRotate(rbt, x->parent);
				else LeftRotate(rbt, xp);
				x = rbt->root;
			}
		}
		// case 5678 x가 parent의 right
		else {
			if (x) w = x->parent->left;
			else w = xp->left;
			// case 1 w == red
			if (w->color == RED) {
				w->color = BLACK;
				if (x)x->parent->color = RED;
				else xp->color = RED;
				if (x)RightRotate(rbt, x->parent);
				else RightRotate(rbt, xp);
				if (x)w = x->parent->left;
				else w = xp->left;
			}
			// case 2 w == black && w->right == w->left == black
			if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK)) {
				w->color = RED;
				if (x)x = x->parent;
				else x = xp;
			}

			else
			{
				// case 3 w == black && w->right == red
				if (!w->left || w->left->color == BLACK)
				{
					if (w->right) w->right->color = BLACK;
					w->color = RED;
					LeftRotate(rbt, w);
					if (x)w = x->parent->left;
					else w = xp->left;
				}
				// case 4 w == black && w->left == red
				if (x)w->color = x->parent->color;
				else w->color = xp->color;
				if (x)x->parent->color = BLACK;
				else xp->color = BLACK;
				if (w->left) w->left->color = BLACK;
				if (x)RightRotate(rbt, x->parent);
				else RightRotate(rbt, xp);
				x = rbt->root;
			}
		}
	}
	if (x) x->color = BLACK;
}

RBT_NODE* generateRBTNode(RESERVATION* reservation)
{
	RBT_NODE* rbtNode = malloc(sizeof(RBT_NODE));

	rbtNode->reservation = reservation;
	rbtNode->color = RED;
	rbtNode->parent = NULL;
	rbtNode->left = NULL;
	rbtNode->right = NULL;

	return rbtNode;
}

RESERVATION* generateReservation(RESERVATION_RECORD* reservationRecord, const char* firstName, const char* lastName, int sex, PATH* path)
{
	RESERVATION* reservation = malloc(sizeof(RESERVATION));

	reservation->firstName = firstName;
	reservation->lastName = lastName;
	reservation->sex = sex;
	reservation->path = path;
	// 1 부터 차례대로 reservation Number로 설정
	reservation->reservationNumber = reservationRecord->nextReservationNumber++;

	return reservation;
}

RESERVATION_RECORD* generateReservationRecord()
{
	RESERVATION_RECORD* reservationRecord = malloc(sizeof(RESERVATION_RECORD));

	reservationRecord->root = NULL;
	reservationRecord->nextReservationNumber = 1;

	return reservationRecord;
}

RESERVATION* addToRecord(RESERVATION_RECORD* reservationRecord, const char* firstName, const char* lastName, int sex, PATH* path)
{
	RBT_NODE* z = generateRBTNode(generateReservation(reservationRecord, firstName, lastName, sex, path));
	RBT_NODE* x, * y;
	y = NULL;
	x = reservationRecord->root;
	while (x != NULL) {
		y = x;
		if (compare(z->reservation, x->reservation) < 0)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL) {
		reservationRecord->root = z;
	}
	else {
		if (compare(z->reservation, y->reservation) < 0) {
			y->left = z;
		}
		else {
			y->right = z;
		}
	}
	z->left = NULL;
	z->right = NULL;
	z->color = RED;
	fixinsert(reservationRecord, z);

	return z->reservation;
}
RBT_NODE* RBTFind(RBT_NODE* root, RESERVATION* reservation)
{
	if (!root) return NULL;
	if (compare(root->reservation, reservation) == 0) {
		return root;
	}
	else if (compare(root->reservation, reservation) < 0) {
		return RBTFind(root->right, reservation);
	}
	else {
		return RBTFind(root->left, reservation);
	}
}

RBT_NODE* RBTMin(RBT_NODE* root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}

RBT_NODE* RBTSuccessor(RBT_NODE* root)
{
	if (root->right != NULL) {
		return RBTMin(root->right);
	}
	RBT_NODE* parent = root->parent;
	while (parent != NULL && root == parent->right)
	{
		root = parent;
		parent = root->parent;
	}
	return parent;
}

void copyRBTNode(RBT_NODE* dst, RBT_NODE* src)
{
	dst->reservation = src->reservation;
}

int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation)
{
	RBT_NODE* y = NULL;
	RBT_NODE* x = NULL;
	RBT_NODE* xp = NULL;
	RBT_NODE* now = RBTFind(reservationRecord->root, reservation);

	if (!now) return 0;

	if (now->left == NULL || now->right == NULL) {
		y = now;
	}
	else {
		y = RBTSuccessor(now);
	}

	if (y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	if (x) x->parent = y->parent;

	if (y->parent == NULL) {
		reservationRecord->root = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
		xp = y->parent;
	}
	else {
		y->parent->right = x;
		xp = y->parent;
	}

	if (y != now) {
		//now->data = y->data;
		copyRBTNode(now, y);
	}
	// 문제가 되는 경우는 red인 경우만이다.
	if (y->color == BLACK) {
		fixdelete(reservationRecord, x, xp);
	}

	if (y) free(y);
	return 1;
}

void printRBTRecursion(RBT_NODE* node, int space)
{
	space += SPACE_SIZE;

	if (node->right != NULL)
	{
		printRBTRecursion(node->right, space);
	}

	for (int i = 0; i < space - SPACE_SIZE; i++)
	{
		printf(" ");
	}

	if (node->color == RED)
	{
		changeColor(LIGHT_RED, BLACK);
	}

	printf("%d\n", node->reservation->reservationNumber);

	changeColor(LIGHT_WHITE, BLACK);

	if (node->left != NULL)
	{
		printRBTRecursion(node->left, space);
	}
}

void printTree(RESERVATION_RECORD* reservationRecord)
{
	printRBTRecursion(reservationRecord->root, 0);
}

void subArrayFromRecord(RBT_NODE* root, LINKED_LIST* linkedList) {
	if (root == NULL)
		return;
	subArrayFromRecord(root->left, linkedList);
	addToList(linkedList, root->reservation);
	subArrayFromRecord(root->right, linkedList);
}

LINKED_LIST* listFromRecord(RESERVATION_RECORD* reservationRecord)
{
	LINKED_LIST* linkedList = generateLinkedList();

	subArrayFromRecord(reservationRecord->root, linkedList);

	return linkedList;
}

void subTreeTraversal(RBT_NODE* root, int depth, int* depth_max, int* cnt) {
	if (root == NULL)
		return;

	subTreeTraversal(root->left, depth + 1, depth_max, cnt);
	if (depth > (*depth_max)) {
		(*depth_max) = depth;
	}
	(*cnt)++;
	subTreeTraversal(root->right, depth + 1, depth_max, cnt);
}

char* printTreeTraversal(RESERVATION_RECORD* reservationRecord) {
	char* result = calloc(45, sizeof(char));
	int* depth_max = (int*)malloc(sizeof(int));
	int* cnt = (int*)malloc(sizeof(int));
	*depth_max = *cnt = 0;

	subTreeTraversal(reservationRecord->root, 1, depth_max, cnt);

	sprintf(result, "%d of nodes, height of the tree: %d\n", (*cnt), (*depth_max));

	free(cnt); free(depth_max);

	return result;
}

char* reservationToStr(RESERVATION* reservation)
{
	char buffer[200] = "";
	char temp[200] = "";
	char* result;

	// 예약번호
	{
		int length;
		sprintf(temp, "%d", reservation->reservationNumber);
		length = strlen(temp);

		for (int i = 0; i < MAX_SPACE_OF_RESERVATION_NUMBER - length; i++)
		{
			strcat(temp, " ");
		}

		strcat(buffer, temp);
	}

	// 이름과 성
	{
		int length;
		sprintf(temp, "%s %s", reservation->firstName, reservation->lastName);
		length = strlen(temp);

		for (int i = 0; i < MAX_SPACE_OF_NAME - length; i++)
		{
			strcat(temp, " ");
		}

		strcat(buffer, temp);
	}

	// path 정보
	{
		char* pathStr = pathToStr(reservation->path, getStrOfSeatClass(((FLIGHT*)getFirstFromList(reservation->path->flightList))->seatClass));

		strcat(buffer, pathStr);
		free(pathStr);
	}

	result = calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(result, buffer);
	
	return result;
}
