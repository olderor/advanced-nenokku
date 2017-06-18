//
//  main.cpp
//  advanced-nenokku
//
//  Created by olderor on 17.06.17.
//  Copyright © 2017 Bohdan Yevchenko. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

struct state {
    int len, link;
    std::vector<int> next;
    state(const int len, const int link) : len(len), link(link) {
        next.resize('z' - 'a' + 2);
    }
};

char character;
std::vector<state> states;
int previous = 0;

void add(const int char_code) {
    int cur = static_cast<int>(states.size());
    states.push_back(state(states[previous].len + 1, -1));

    int state_with_path = previous;
    while (
      state_with_path != -1 && states[state_with_path].next[char_code] == 0) {
        states[state_with_path].next[char_code] = cur;
        state_with_path = states[state_with_path].link;
    }

    if (state_with_path == -1) {
        previous = cur;
        states[previous].link = 0;
        return;
    }

    int next = states[state_with_path].next[char_code];
    if (states[next].len == states[state_with_path].len + 1) {
        previous = cur;
        states[previous].link = next;
        return;
    }

    int clone = static_cast<int>(states.size());
    states.push_back(state(states[state_with_path].len + 1, states[next].link));
    states[clone].next = states[next].next;
    while (state_with_path != -1 &&
      states[state_with_path].next[char_code] == next) {
        states[state_with_path].next[char_code] = clone;
        state_with_path = states[state_with_path].link;
    }
    previous = cur;
    states[previous].link = clone;
    states[next].link = clone;
}

bool find() {
    int state = 0;
    character = getchar();
    int code;
    while (character != '\n' && character != EOF) {
        if ('A' <= character && character <= 'Z') {
            code = character - 'A';
        } else {
            code = character - 'a';
        }
        state = states[state].next[code];
        if (state == 0) {
            while (character != '\n' && character != EOF) {
                character = getchar();
            }
            return false;
        }
        character = getchar();
    }
    return true;
}

void add() {
    character = getchar();
    int code;
    while (character != '\n' && character != EOF) {
        if ('A' <= character && character <= 'Z') {
            code = character - 'A';
        } else {
            code = character - 'a';
        }
        add(code);
        character = getchar();
    }
}

int main() {
    states.push_back(state(0, -1));

    char command;
    character = 'a';
    while (character != EOF) {
        command = getchar();
        character = getchar();
        if (command == '?') {
            if (find()) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else {
            add();
        }
    }

    return 0;
}
