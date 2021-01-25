#include <iostream>

// namespaces are easy to create
// just use the "namespace" keyword and the name of the namespace after that
// namespaces are mostly used to avoid any classes with te same name
// many developers might create the same class / struct names

// when you want to use the namespace and all of its class mebers
// we can do so by using the keyword "using" followed by the name of the namespace.

// using namespace MyMath;

namespace MyMath
{
    // creating a template means we can give the class a select type we want to work with.
    // we can also give the template a select few types that it can support.
    // however that requires us to write the class multiple times with said type.
    // you would write template<float> and all of the variables / classes with T should be replaced with float

    // if you're curious, then here is a simple syntax:

    // template<class T>
    // class Foo { T variable; };
    
    // template<>
    // class Foo<float> { float variable; };

    // here we're basically specifying what happens when our class is a float template
    // for reference: https://docs.microsoft.com/en-us/cpp/cpp/template-specialization-cpp?view=msvc-160


    // NOTE : you will probalby come across where some poeple write "template<typename T>"
    //        this is no different than writing class, it all comes down to personal preference

    // EXTRA: it is also possible to have a template inside a template... I know my brain hurts too

    template<class T>
    class Vector2
    {
public:
        T x, y;

        Vector2<T>()
        {
            x = 0;
            y = 0;
        }

        Vector2<T>(const T x_, const T y_)
        {
            x = x_;
            y = y_;
        }

        // operator overloading is basically us defining what happens when we use operators between this class and itself or others
        // eks. Vector3 + Vector3
        // operators that can be overriden:
        // +, -, *, /, %, =, ==, >=, <=, >, <, !=, <=>, &&, ||, &, |, !, etc...
        
        // this webiste is quite a useful reference for operators
        // https://en.cppreference.com/w/cpp/language/operators

        // this is how we override operators
        // after writing what the function returns, follow it up by the "operator" keyword
        // then, the operator you want to override

        Vector2<T>& operator+=(const Vector2<T>& vec)
        {
            x += vec.x;
            y += vec.y;

            return *this;
        }

        // you are not reqired to know what the keyword "friend" means
        // but for those who are curious:
        // "Friends defined inside class body are inline and are hidden from non-ADL lookup"
        // basically we have access to everything from the Vector2 class, and is hidden from argument dependent lookup (ADL)

        friend Vector2<T> operator+(Vector2<T> vec1, const Vector2<T> vec2)
        {
            // since we already have made an operator overloading function for adding
            // we can use the += override function
            vec1 += vec2;
            return vec1;
        }
    };

    class Matrix2x2
    {
public:
        Vector2<float> upperLine, lowerLine;
        // | 0, 0 |
        // | 0, 0 |
    };
}

// we need to use the namespace if we want to avoid writing "MyMath::Vector2<float>" all the time
using namespace MyMath;

// of course you will not use the main function when in unreal
// but think of it as the UObject::Begin function
int main()
{
    // in order to tell the template what type we want
    // we write the class name and <...> between these angle brackets we write the type
    Vector2<float> vec{ Vector2<float>(10.8f, 3.45f) };
    Vector2<float> vec2{ Vector2<float>(-2.0f, 1.0f) };

    Vector2<float> vec3{ vec + vec2 };

    // NOTE : if you want to add a Vector2<int> and a Vector2<float>, you can't
    //        our class doesn't support adding different template types

    std::cout << '[' << vec3.x << ", " << vec3.y << "]\n";
    
    // TASK : write a << overloader, so we can add the two vectors directly in the "std::cout" line
    // and it must print the vector. NOT the x and y seperatly
    // std::cout << vec3 << std::endl;
    // using something like this in unreal won't work. instead of returning "std::istream" return a "std::string" insted
    // then use: UE_LOG(Log, TEXT("%s", vec3));


    // TASK : edit Matrix2x2 so it has a template


    // ADVANCED TASK : overload the * operator and mutliply the matrix with a vector

    // How is matrix multiplication done?
    // | 1,  2 | * (-1, 1)  <- here we multiply the x of the vector with the first column, then y with the second column
    // | 0, -1 |               then add them together: 1 * -1 + 2 * 1

    // do that for both of the rows. the function will return a Vector2<int>
    // print the vector and you will get this in the console: [1, -1]

    return 0;
}
