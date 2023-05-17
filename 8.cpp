#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <cmath>
#include <string>

using namespace std;

// Пріоритети операцій
map<char, int> priorities = {
    {'+', 1},
    {'-', 1},
    {'^', 2},
};

// Функція, що обчислює вираз
double evaluate(string expression) {
    stack<double> values;
    stack<char> operators;

    for (char c : expression) {
        if (c >= '0' && c <= '9') {
            values.push(c - '0'); // Перетворення символу на цифру
        }
        else if (c == '+' || c == '-' || c == '^') {
            while (!operators.empty() && priorities[operators.top()] >= priorities[c]) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();

                if (op == '+') {
                    values.push(a + b);
                }
                else if (op == '-') {
                    values.push(a - b);
                }
                else if (op == '^') {
                    values.push(pow(a, b));
                }
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();

        if (op == '+') {
            values.push(a + b);
        }
        else if (op == '-') {
            values.push(a - b);
        }
        else if (op == '^') {
            values.push(pow(a, b));
        }
    }

    return values.top();
}

int main() {

    string input_file = "input.clc";
    string output_file = input_file.substr(0, input_file.size() - 4) + ".res"; // Формування назви вихідного файлу

    ifstream fin(input_file); // Відкриття файлу для читання
    ofstream fout(output_file); // Відкриття файлу для запису

    if (!fin.is_open()) {
        cout << "Error opening file " << input_file << endl;
        return 1;
    }

    if (!fout.is_open()) {
        cout << "Error opening file " << output_file << endl;
        return 1;
    }

    string expression;
    getline(fin, expression);

    double result = evaluate(expression);

    fout << result;

    fin.close();
    fout.close();

    return 0;
}