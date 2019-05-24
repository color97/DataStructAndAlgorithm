#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

class Rectangle
{
public:
    explicit Rectangle(size_t pLength, size_t pWidth): length(pLength), width(pWidth)
    {}

    size_t getLength() const { return length;}

    size_t getWidth() const { return width;}
private:
    size_t length;
    size_t width;
};

// Generic findMax, with a function object, C++ style.
// Precondition: a.size( ) > 0.
template <typename Object, typename Comparator>
const Object & findMax( const vector<Object> & arr, Comparator isLessThan )
{
    int maxIndex = 0;

    for( int i = 1; i < arr.size( ); ++i )
        if( isLessThan( arr[ maxIndex ], arr[ i ] ) )
            maxIndex = i;

    return arr[ maxIndex ];
}

class RectangleCompare
{
  public:
    bool operator( )( const Rectangle & lhs, const Rectangle & rhs ) const
    {
        const size_t lhsArea = lhs.getLength() * lhs.getWidth();
        const size_t rhsArea = rhs.getLength() * rhs.getWidth();
        if(lhsArea == rhsArea)
        {
            return (lhs.getLength() + lhs.getWidth()) < (rhs.getLength() * rhs.getWidth());
        }
        else
        {
            return lhsArea < rhsArea;
        }   
    }
};

int main( )
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 10000);

    vector<Rectangle> arr;
    for (size_t i = 0; i < 10; i++)
    {
        arr.push_back(Rectangle(dis(gen), dis(gen)));
    }
    
    auto object = findMax( arr, RectangleCompare{ } );
    cout << object.getLength() << ", "<< object.getWidth() << endl;

    return 0;
}