#include "Polynomial.cpp"
#include <iostream>

void test();

using namespace std;

int main() {
    test();

    return 0;
}

void test() {
    Term a_one = Term(5, 7);
    Term a_two = Term(3,2);
    Term a_three = Term(4,3);
    Term a_four = Term(-1,-1);

    Term b_one = Term(-3, 7);
    Term b_two = Term(4,0);
    Term b_tree = Term(1,1);
    Term b_four = Term(0, -7);
    Term b_five = Term(-2, 7);
    Term b_six = Term(-2, 8);
    Term b_seven = Term(-6, 2);
    Term b_eight = Term(12, 23);
    Term b_nine = Term(-12, 23);

    Term c_one = Term(-10, 10);
    Term c_two = Term(5,-10);
    Term c_tree = Term(-4,1);
    Term c_four = Term(2, 8);
    Term c_five = Term(7, 9);
    Term c_six = Term(9, -7);
    Term c_seven = Term(-8, -1);

    Polynomial a_poly = Polynomial(nullptr);
    a_poly.addTerm(&a_one);
    a_poly.addTerm(&a_two);
    a_poly.addTerm(&a_three);
    a_poly.addTerm(&a_four);

    Polynomial b_poly = Polynomial(&b_one);
    b_poly.addTerm(&b_two);
    b_poly.addTerm(&b_tree);
    b_poly.addTerm(&b_four);
    b_poly.addTerm(&b_five);
    b_poly.addTerm(&b_six);
    b_poly.addTerm(&b_seven);
    b_poly.addTerm(&b_eight);
    b_poly.addTerm(&b_nine);
    b_poly.addTerm(nullptr);

    Polynomial c_poly = Polynomial(&c_one);
    c_poly.addTerm(&c_two);
    c_poly.addTerm(&c_tree);
    c_poly.addTerm(&c_four);
    c_poly.addTerm(&c_five);
    c_poly.addTerm(&c_six);
    c_poly.addTerm(&c_seven);

    cout << "The first string is: " << a_poly.toString() << endl;
    cout << "The second string is: " << b_poly.toString() << endl;
    cout << "The third string is: " << c_poly.toString() << endl;

    Polynomial first_result = a_poly.add(&b_poly);
    cout << "The first result string after adding them up is: " << first_result.toString() << endl;

    cout << "The final result string after adding them up is: " << first_result.add(&c_poly).toString() << endl;
}
