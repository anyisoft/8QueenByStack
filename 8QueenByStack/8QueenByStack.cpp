// 8QueenByStack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"

#define MAXQUEEN 8

struct stack_node {
	int x;
	int y;
	struct stack_node *next;
};
typedef struct stack_node stack_list;
typedef stack_list *link;

link solution = NULL;

int pad [MAXQUEEN][MAXQUEEN] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * 检查皇后是否有相互攻击
 */
int place(int x, int y)
{
	int x1, y1;

	if (x < 0 || y < 0 || x >= MAXQUEEN || y >= MAXQUEEN) {
		return 0;
	}

	if (pad[x][y] != 0) {
		return 0;
	}

	// 检查左上方
	x1 = x-1;
	y1 = y-1;
	while (x1 >= 0 && y1 >= 0) {
		if (pad[x1--][y1--] != 0) {
			return 0;
		}
	}

	// 检查上方
	x1 = x-1;
	y1 = y;
	while (x1 >= 0) {
		if (pad[x1--][y1] != 0) {
			return 0;
		}
	}

	// 检查右上方
	x1 = x-1;
	y1 = y+1;
	while (x1 >= 0 && y1 < MAXQUEEN) {
		if (pad[x1--][y1++] != 0) {
			return 0;
		}
	}

	// 检查右方
	x1 = x;
	y1 = y+1;
	while (y1 < MAXQUEEN) {
		if (pad[x1][y1++] != 0) {
			return 0;
		}
	}

	// 检查右下方
	x1 = x+1;
	y1 = y+1;
	while (x1 < MAXQUEEN && y1 < MAXQUEEN) {
		if (pad[x1++][y1++] != 0) {
			return 0;
		}
	}

	// 检查下方
	x1 = x+1;
	y1 = y;
	while (x1 < MAXQUEEN) {
		if (pad[x1++][y1] != 0) {
			return 0;
		}
	}

	// 检查左下方
	x1 = x+1;
	y1 = y-1;
	while (x1 < MAXQUEEN && y1 >= 0) {
		if (pad[x1++][y1--] != 0) {
			return 0;
		}
	}

	// 检查左方
	x1 = x;
	y1 = y-1;
	while (y1 >= 0) {
		if (pad[x1][y1--] != 0) {
			return 0;
		}
	}

	return 1;
}

link push(link stack, int x, int y)
{
	link new_node;

	new_node = (link)malloc(sizeof(stack_list) );
	if (!new_node) {
		_tprintf(_T("内存分配失败!\n"));
		return NULL;
	}

	new_node->x = x;
	new_node->y = y;
	new_node->next = stack;

	stack = new_node;

	return stack;
}

link pop(link stack, int *x, int *y)
{
	link top;

	if (stack != NULL) {
		top = stack;
		stack = stack->next;
		*x = top->x;
		*y = top->y;
		free(top);
		return stack;
	}
	else {
		*x = -1;
		return NULL;
	}
}

void print_pad(int *pad)
{
	for (int i = 0; i < MAXQUEEN; i++) {
		for (int j = 0; j < MAXQUEEN; j++) {
			printf("%d ", pad[i*MAXQUEEN+j]);
		}
		printf("\n");
	}

	printf("\n");
}

/*
 * 以行为单位，从左至右放置
 * 可以放置，则入栈
 *   第i 行时，栈深度为i+1，列为j
 *   若深度为MAXQUEEN 则已找到一组答案
 * 不可以放置，则增加j 继续尝试
 * 当j >= MAXQUEEN 时，上一行出栈，增加j 重试
 * 当j >= MAXQUEEN 且栈已空时，则所有方案均已检测过
 */
int _tmain(int argc, _TCHAR* argv[])
{
	int solutionCount = 0;
	int stackDepth = 0;
	int stackCol = 0;

	do {
		if (place(stackDepth, stackCol) ) {
			solution = push(solution, stackDepth, stackCol);
			pad[stackDepth][stackCol] = 1;
			stackDepth++;
			stackCol = 0; // 下一行从0 开始
			// print_pad(&pad[0][0]);
		}
		else {
			if (stackDepth>=MAXQUEEN || stackCol >= MAXQUEEN) {
				solution = pop(solution, &stackDepth, &stackCol);
				pad[stackDepth][stackCol] = 0;
				if (stackDepth < 0) {
					break;
				}
				stackCol++; // 从下一列开始尝试
			}
			else {
				stackCol++;
			}
		}
		if (stackDepth == MAXQUEEN) {
			printf("No.%d\n", ++solutionCount);
			print_pad(&pad[0][0]);
		}
	} while (stackDepth < MAXQUEEN || stackCol < MAXQUEEN);

	// print_pad(&pad[0][0]);

	return 0;
}
