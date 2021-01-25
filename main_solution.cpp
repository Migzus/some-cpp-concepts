#include <iostream>

namespace MyMath
{
    template<class T>
    class Vector2
    {
public:
        T x, y;

        Vector2()
        {
            x = 0;
            y = 0;
        }

        Vector2(const T x_, const T y_)
        {
            x = x_;
            y = y_;
        }

        Vector2<T>& operator+=(const Vector2<T>& vec)
        {
            x += vec.x;
            y += vec.y;

            return *this;
        }

        friend Vector2<T> operator+(Vector2<T> vec1, const Vector2<T>& vec2)
        {
            vec1 += vec2;
            return vec1;
        }
    };

    template<class T>
    class Matrix2x2 {};

    template<>
    class Matrix2x2<Vector2<int>>
    {
public:
        Vector2<int> upperLine, lowerLine;

        Matrix2x2() {}

        Matrix2x2(const Vector2<int> upper, const Vector2<int> lower)
        {
            upperLine = upper;
            lowerLine = lower;
        }

        friend Vector2<int> operator*(Matrix2x2<Vector2<int>> mat, const Vector2<int> vec)
        {
            Vector2<int> outputVector;

            outputVector.x = mat.upperLine.x * vec.x + mat.upperLine.y * vec.y;
            outputVector.y = mat.lowerLine.x * vec.x + mat.lowerLine.y * vec.y;

            return outputVector;
        }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
    {
        os << '[' << vec.x << ", " << vec.y << ']';

        return os;
    }
}

using namespace MyMath;

int main()
{
    Vector2<float> vec{ Vector2<float>(10.8f, 3.45f) };
    Vector2<float> vec2{ Vector2<float>(-2.0f, 1.0f) };

    Vector2<float> vec3{ vec + vec2 };

    std::cout << vec3 << std::endl;

    Matrix2x2<Vector2<int>> matrix{ Matrix2x2<Vector2<int>>(Vector2<int>(1, 2), Vector2<int>(0, -1)) };
    Vector2<int> vec4{ Vector2<int>(-1, 1) };
    
    std::cout << matrix * vec4 << '\n';

    return 0;
}
