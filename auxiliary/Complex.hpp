#ifndef COMPLEX_HPP
#define COMPLEX_HPP

template <typename T>
class Complex {
    public:
        using value_type = T;

        Complex(const T& re = T{}, const T& im = T{}) : Re(re), Im(im) {}
    
        Complex(const Complex<T>&) = default;
        Complex(Complex<T>&&) = default;
        Complex<T>& operator=(const Complex<T>&) = default;
        Complex<T>& operator=(Complex<T>&&) = default;
        ~Complex() = default;

        T GetRe() const {
            return Re;
        }
        T GetIm() const {
            return Im;
        }

        void SetRe(const T& re) {
            Re = re;
        }
        void SetIm(const T& im) {
            Im = im;
        }

        Complex<T> Conj() const {
            return Complex<T>(Re, -Im);
        }

        T Norm() const {
            return Re * Re + Im * Im;
        }

        Complex<T> operator+(const Complex<T>& other) const {
            return Complex<T>(Re + other.Re, Im + other.Im);
        }
        Complex<T> operator+=(const Complex<T>& other) {
            Re += other.Re;
            Im += other.Im;
            return *this;
        }

        Complex<T> operator*(const Complex<T>& other) const {
            return Complex<T>(Re * other.Re - Im * other.Im, Re * other.Im + other.Re * Im);
        }
        template <typename ScalarType>
        Complex<T> operator*(const ScalarType& scalar) const {
            return Complex<T>(Re * scalar, Im * scalar);
        }

        bool operator==(const Complex<T>& other) const {
            return Re == other.Re && Im == other.Im;
        }
        bool operator!=(const Complex<T>& other) const {
            return !(*this == other);
        }
        bool operator<(const Complex<T>& other) const {
            return this->Norm() < other.Norm();
        }
        bool operator>(const Complex<T>& other) const {
            return other < *this;
        }
        bool operator<=(const Complex<T>& other) const {
            return !(*this > other);
        }
        bool operator>=(const Complex<T>& other) const {
            return !(*this < other);
        }

        std::string toString_Complex() const {
            std::ostringstream oss;
            oss << "(" << Re << (Im >= 0 ? "+" : "-") << Im << "i)";
            return oss.str(); 
        }

    private:
        T Re;
        T Im;
};

#endif // COMPLEX_HPP