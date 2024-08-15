/**
 * Name: Aharon bassous
 * Email: Aharonba123@gmail.com
 */


#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>



namespace ariel
{
    class Complex
    {
    private:
        double real;
        double imag;

    public:
        // Constructors
        Complex() : real(0), imag(0) {}
        Complex(double r, double i) : real(r), imag(i) {}

        // Getters
        double getReal() const { return real; }
        double getImag() const { return imag; }

        // Setters
        void setReal(double r) { real = r; }
        void setImag(double i) { imag = i; }

        // Operator overloading for addition
        Complex operator+(const Complex &other) const
        {
            return Complex(real + other.real, imag + other.imag);
        }

        // Operator overloading for output stream
        friend std::ostream &operator<<(std::ostream &out, const Complex &c)
        {
            out << c.real << " + " << c.imag << "i";
            return out;
        }
    };
}
#endif // COMPLEX_HPP
