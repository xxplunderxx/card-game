/*
CSCI 240         Program 9     Fall 2020

Programmer: Jacob Eul
 Programming Partner: Caitlyn Hensley

Section: 0001

Date Due: Nov 24 2020

Purpose: calculate fractions
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

class Rational {
public:
  int numerator;
  int denominator;

  Rational();
  Rational(int, int);

  void displayFloat();
  void displayFraction();
  void display();

  void setNumerator(int);
  void setDenominator(int);
  void setRational(int, int);

  Rational add(int, int);
  Rational subtract(int, int);
  Rational multiply(int, int);
  Rational divide(int, int);

private:
  void reduce();
  int GCD(int, int);
  int LCM(int, int);
};

int main() {
  cout << "***** Testing the constructors *****" << endl << endl;
  cout << endl;

  cout << "the default constructor produces ";
  Rational r1;
  r1.displayFraction();
  cout << endl;
  cout << endl;

  cout << "The alternate constructor with 11, 30 produces ";
  Rational r2(11, 30);
  r2.display();
  cout << endl;

  cout << "                          with  2, 30 produces ";
  Rational r3(2, 30);
  r3.display();
  cout << endl;

  cout << "                          with  5, 6  produces ";
  Rational r4(5, 6);
  r4.display();
  cout << endl;

  cout << "                          with  3, 7  produces ";
  Rational r5(3, 7);
  r5.display();
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "*****Testing the set methods *****" << endl;
  cout << endl;

  cout << "setNumerator(8) changes ";
  r3.displayFraction();
  cout << " to ";
  r3.setNumerator(8);
  r3.displayFraction();
  cout << endl;
  cout << endl;

  cout << "setDenominator(73) changes ";
  r4.displayFraction();
  cout << " to ";
  r4.setDenominator(73);
  r4.displayFraction();
  cout << endl;
  cout << endl;

  cout << "setRational(4, 6) changes ";
  r1.displayFraction();
  cout << " to ";
  r1.setRational(4, 6);
  r1.displayFraction();
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "***** Testing the add method *****" << endl;
  cout << endl;

  r4.displayFraction();
  cout << " + 3/7 = ";
  Rational r6 = r4.add(3, 7);
  r6.display();
  cout << endl;
  cout << endl;

  r6.displayFraction();
  cout << " + 3/7 = ";
  r6 = r6.add(3, 7);
  r6.display();
  cout << endl;
  cout << endl;

  r3.displayFraction();
  cout << " + 1/2 = ";
  Rational r7 = r3.add(1, 2);
  r7.display();
  cout << endl;
  cout << endl;

  r1.displayFraction();
  cout << " + 15/16 = ";
  Rational r8 = r1.add(15, 16);
  r8.display();
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "***** Testing the subtract method *****" << endl;
  cout << endl;

  r6.displayFraction();
  cout << " - 5/7 = ";
  Rational r9 = r6.subtract(5, 7);
  r9.display();
  cout << endl;
  cout << endl;

  r7.displayFraction();
  cout << " - 3/6 = ";
  Rational r10 = r7.subtract(3, 6);
  r10.display();
  cout << endl;
  cout << endl;

  r8.displayFraction();
  cout << " - 101/117 = ";
  Rational r11 = r8.subtract(101, 117);
  r11.display();
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "***** Testing the multiply method *****" << endl;
  cout << endl;

  r9.displayFraction();
  cout << " * 1/1 = ";
  Rational r12 = r9.multiply(1, 1);
  r12.display();
  cout << endl;
  cout << endl;

  r10.displayFraction();
  cout << " * 7/30 = ";
  Rational r13 = r10.multiply(7, 30);
  r13.display();
  cout << endl;
  cout << endl;

  r11.displayFraction();
  cout << " * 2/4 = ";
  Rational r14 = r11.multiply(2, 4);
  r14.display();
  cout << endl;
  cout << endl;
  cout << endl;

  cout << "***** Testing the divide method *****" << endl;
  cout << endl;

  r9.displayFraction();
  cout << " / 5/8 = ";
  Rational r15 = r9.divide(5, 8);
  r15.display();
  cout << endl;
  cout << endl;

  r13.displayFraction();
  cout << " / 5/15 = ";
  Rational r16 = r13.divide(5, 15);
  r16.display();
  cout << endl;
  cout << endl;

  r5.displayFraction();
  cout << " / 2/4 = ";
  Rational r17 = r5.divide(2, 4);
  r17.display();
  cout << "\n\n\n";
}

Rational::Rational() {
  numerator = 1;
  denominator = 1;
}

Rational::Rational(int _numer, int _denom) {
  setRational(_numer, _denom);
  reduce();
}

void Rational::displayFloat() {
  cout << fixed << setprecision(5) << (float)numerator / (float)denominator;
}

void Rational::displayFraction() {
  cout << numerator << "/" << denominator;
}

void Rational::display() {
  displayFraction();
  cout << "     or     ";
  displayFloat();
}

void Rational::setNumerator(int _numer) {
  numerator = _numer;
  reduce();
}

void Rational::setDenominator(int _denom) {
  denominator = _denom;
  reduce();
}

void Rational::setRational(int _numer, int _denom) {
  numerator = _numer;
  denominator = _denom;
  reduce();
}

Rational Rational::add(int _numer, int _denom) {
  int lcm = LCM(denominator, _denom);
  int newNumeratorLeft = numerator * (lcm / denominator);
  int newNumeratorRight = _numer * (lcm / _denom);
  Rational sum(newNumeratorLeft + newNumeratorRight, lcm);
  return sum;
}

Rational Rational::subtract(int _numer, int _denom) {
  int lcm = LCM(denominator, _denom);
  int newNumeratorLeft = numerator * (lcm / denominator);
  int newNumeratorRight = _numer * (lcm / _denom);
  Rational diff(newNumeratorLeft - newNumeratorRight, lcm);
  return diff;
}

Rational Rational::multiply(int _numer, int _denom) {
  Rational product(numerator * _numer, denominator * _denom);
  return product;
}

Rational Rational::divide(int _numer, int _denom) {
  Rational quotient(numerator * _denom, denominator * _numer);
  return quotient;
}

void Rational::reduce() {
  int gcd = GCD(numerator, denominator);
  numerator /= gcd;
  denominator /= gcd;
}

int Rational::GCD(int val1, int val2)
{
  int remainder, num1, num2;
  //set variables num1 and num2 to the two passed in values
  num1 = val1;
  num2 = val2;
  //continue dividing num1 by num2 until a remainder of 0 is found
  while (true)
  {
    //find the remainder when num1 is divided by num2
    remainder = num1 % num2;
    //if the remainder is 0, get out of the loop
    if (remainder == 0)
      break;
    //set num1 to the current num2 value
    num1 = num2;
    //set num2 to the remainder
    num2 = remainder;
  }//end while
//After the loop is done executing, the variable num2 will contain the
//greatest common divisor.
  return num2;
}

int Rational::LCM(int val1, int val2)
{
  int num1, num2, lcm;
  //set variables num1 and num2 to the two passed in values
  num1 = val1;
  num2 = val2;
  //set lcm to the first passed in value
  lcm = num1;
  //while lcm is less than or equal to the product of num1 and num2
  while (lcm <= num1 * num2)
  {
    //if the remainder of lcm divided by num1 is 0 and
    //   the remainder of lcm divided by num2 is 0, get out of the loop
    if (lcm % num1 == 0 and lcm % num2 == 0)
      break;
    //increment lcm by 1
    lcm++;
  }//end while
//return the least common multiple
  return lcm;
}
