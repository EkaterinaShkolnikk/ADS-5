// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int OperPriority(char sym) {
    if (sym == '(')
        return 0;
    else if (sym == ')')
        return 1;
    else if (sym == '+' || sym == '-')
        return 2;
    else
        return 3;
}

bool Type(char sym) {
    if (sym >= '0' && sym <= '9')
        return true;
    return false;
}


std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string postfix;

    for (char sym : inf) {
        if (Type(sym)) {
            postfix.push_back(sym);
            postfix.push_back(' ');
        } else if (OperPriority(sym) == 0) {
            stack.push(sym);
        } else if (OperPriority(sym) == 1) {
            while (!stack.isEmpty() && OperPriority(stack.get()) != 0) {
                postfix.push_back(stack.get());
                postfix.push_back(' ');
                stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() &&
                (OperPriority(sym) <= OperPriority(stack.get()))) {
                postfix.push_back(stack.get());
                postfix.push_back(' ');
                stack.pop();
            }
            stack.push(sym);
        }
    }

    while (!stack.isEmpty()) {
        postfix.push_back(stack.get());
        postfix.push_back(' ');
        stack.pop();
    }

    if (!postfix.empty()) {
        postfix.pop_back();
    }

    return postfix;
}

    int eval(const std::string& post) {
       TStack<int, 100> stack;

       for (char sym : post) {
           if (Type(sym)) {
               stack.push(sym - '0');
           } else if (sym == '+' || sym == '-' || sym == '/' || sym == '*') {
               int numberTwo = stack.get();
               stack.pop();
               int numberOne = stack.get();
               stack.pop();

               switch (sym) {
                   case '+':
                       stack.push(numberOne + numberTwo);
                       break;
                   case '-':
                       stack.push(numberOne - numberTwo);
                       break;
                   case '*':
                       stack.push(numberOne * numberTwo);
                       break;
                   case '/':
                       stack.push(numberOne / numberTwo);
                       break;
               }
           }
       }

       return stack.get();
   }
