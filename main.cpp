#include<fstream>
#include<iostream>
#include<string.h>

std::ifstream f("parse.in");
int n = 0;
char list[100][10];

struct node {
    char token[10];
    double value = 0;
    node *left = nullptr;
    node *right = nullptr;
};

void createTree(node *mNode) {
    strcpy(mNode->token, list[n++]);
    if (!strchr("+-/*", list[n - 1][0])) {
        mNode->left = nullptr;
        mNode->right = nullptr;
    } else if (!isdigit(list[n - 1][1])) {
        node *aux = new node;
        node *aux2 = new node;
        mNode->left = aux;
        mNode->right = aux2;
        createTree(mNode->left);
        createTree(mNode->right);
    }
}

double computeExpression(node *mNode) {
    if (mNode->left == nullptr && mNode->right == nullptr) {
        mNode->value = atof(mNode->token);
        return mNode->value;
    }

    computeExpression(mNode->left);
    computeExpression(mNode->right);

    if (strchr(mNode->token, '+'))
        mNode->value = (mNode->left)->value + (mNode->right)->value;

    if (strchr(mNode->token, '-'))
        mNode->value = (mNode->left)->value - (mNode->right)->value;

    if (strchr(mNode->token, '*'))
        mNode->value = (mNode->left)->value * (mNode->right)->value;

    if (strchr(mNode->token, '/'))
        mNode->value = (mNode->left)->value / (mNode->right)->value;
}

void createList() {
    char x[100];
    f>>x;

    for (int i = 0; i < strlen(x) - 1; i++) {
        if (x[i] == '(' || x[i] == ')')
            strcpy(x + i, x + i + 1);
        else if (x[i] == ' ' && x[i + 1] == ' ')
            strcpy(x + i, x + i + 1);
    }
    strcpy(x + strlen(x) - 1, "");

    for (int i = 0; i < strlen(x); i++)
        list[0][i] = x[i];
}

int main() {
    node *first = new node;
    createList();
    createTree(first);
    computeExpression(first);
    std::cout << first->value;

    f.close();
    return 0;
}
