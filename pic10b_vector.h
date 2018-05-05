#include <iostream>   // std::ostream, std::cout
#include <string>

namespace Pic10b{

    template <class T>
    class vector{
      private:
        T* the_data;
        size_t the_size;
        size_t the_capacity;

        static const int INIT_CAP = 10;


      public:
        /** ************************* THE BIG 4 ************************* **/
        vector() 
        : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {

            the_data = new T[the_capacity];
        }

        vector( const vector& source )
        : the_data(nullptr), the_size(source.the_size), 
            the_capacity(source.the_capacity) {

            the_data = new T[the_capacity];

            // Deep copy of internal array
            for ( int i = 0 ; i < the_size ; ++i ){
                the_data[i] = source.the_data[i];
            }
        }

        vector& operator=( const vector& rhs ) {
            if ( this != &rhs ) {     // Self-assignment?
                // Release old memory and request more 
                delete[] the_data;
                the_data = new T[rhs.the_capacity];

                // Shallow copy non-pointers
                the_size = rhs.the_size;
                the_capacity = rhs.the_capacity;

                // Deep copy internal array
                for ( int i = 0 ; i < the_size ; ++i )
                    the_data[i] = rhs.the_data[i];
            }
            return *this;
        }

        ~vector(){
            delete[] the_data;
        }

        /** *********************** OTHER MEMBERS *********************** **/
        bool empty() const {
            return the_size == 0;
        }

        size_t size() const {
            return the_size;
        }

        size_t capacity() const {
            return the_capacity;
        } 

        T front() const {
            return *the_data;
        }

        T back() const {
            return *(the_data + the_size - 1);
        } 

        T at( size_t index ) const {
            if ( index < the_size )
                return the_data[index];
            return the_data[0];
        }

        T& operator[]( size_t index ){
            return the_data[index];
        }

        T operator[]( size_t index ) const {
            return the_data[index];
        }

        bool operator<(const vector<T>& a) const {
            return a.squared_norm() > squared_norm();
        }

        bool operator==(const vector<T>& a) const {
            return  a.squared_norm() == squared_norm();
        }

        T operator*(const vector<T>& a) const {
            T product = 0;
            for (int i = 0; i < the_size; ++i){
                product += this->operator[](i) * a[i];
            }
            return product;
        }

        vector<T>& operator*=(const int a){
            for (int i = 0; i < the_size; ++i){
                this->operator[](i) = this->operator[](i) * a;
            }
            return *this;
        }

        vector<T>& operator*=(const std::string a){
            for (int i = 0; i < the_size; ++i){
                this->operator[](i) = a + this->operator[](i);
            }
            return *this;
        }

        vector<T>& operator+=(const vector<T>& a){
            for (int i = 0; i < the_size; ++i){
                this->operator[](i) = this->operator[](i) + a[i];
            }
            return *this;
        }

        void dump_data_to( std::ostream& out ) const {
            out << "Vector (dump): ";
            for ( size_t i = 0 ; i < the_capacity ; ++i )
                out << the_data[i] << ' ';
            out << '\n';
        }
        void dump_data() const {
            dump_data_to( std::cout );
        }

        void push_back( T new_value ){
            if ( the_size == the_capacity ) 
                reserve( the_capacity + 1 );     // `the_data` is reassigned

            the_data[the_size++] = new_value;
        }

        // This implementation does not shrink the vector (ever)
        void pop_back(){
            if ( the_size > 0 )
                --the_size;
        }

        T squared_norm() const{
            T norm = 0;
            for (int i = 0; i < the_size; ++i){
                norm += (this->operator[](i))*(this->operator[](i));
            }
            return norm;
        }

      private:
        //Other members [private]
        void reserve( size_t new_capacity ){
            if ( new_capacity > the_capacity ) {
                if ( new_capacity <= 2 * the_capacity )
                    new_capacity = 2 * the_capacity;

                T* old_location = the_data;

                the_data = new T[new_capacity];
                the_capacity = new_capacity;

                for ( size_t i = 0 ; i < the_size ; ++i )
                    the_data[i] = old_location[i];

                delete old_location;
            }
        }
    }; // end Pic10b::vector
} // end Pic10b namespace


/** ************************ OTHER FUNCTIONS ************************ **/
template <class T>
std::ostream& operator<<( std::ostream& out, const Pic10b::vector<T>& v ){
    for ( size_t i = 0 ; i < v.size() ; ++i )
        out << v[i] << ' ';
    return out;
}

std::ostream& operator<<( std::ostream& out, const Pic10b::vector<std::string>& v ){
    out << "[";
    for ( size_t i = 0 ; i < v.size() ; ++i )
        out << v[i] << ", ";
    out << "]";
    return out;
}

template <class T>
void print_vector( const Pic10b::vector<T>& v ){
    if ( v.empty() )
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n' ;
} 

template <class T>
T operator+(T lhs, const T& rhs) {
	return lhs += rhs;
}

template <class T>
T operator*(T lhs, const int rhs) {
    T temp = lhs;
	return temp *= rhs;
}

template <class T>
T operator*(const int lhs, T rhs) {
    T temp = rhs;
	return temp *= lhs;
}

template <class T>
T operator*(T lhs, const std::string rhs) {
    T temp = lhs;
	return temp *= rhs;
}

template <class T>
T operator*(const std::string lhs, T rhs) {
    T temp = rhs;
	return temp *= lhs;
}

template <class T>
bool operator>(const T& a, const T& b) {
	return (!(a < b) && !(a == b));
}

template <class T>
bool operator<=(const T& a, const T& b) {
	return (a < b || a == b);
}

template <class T>
bool operator>=(const T& a, const T& b) {
	return !(a < b);
}

template <class T>
bool operator!=(const T& a, const T& b) {
	return !(a == b);
}

bool operator==(const Pic10b::vector<std::string>& lhs, const Pic10b::vector<std::string>& rhs){
            if (lhs.capacity() != rhs.capacity())
                return false;
            for (int i = 0; i < lhs.capacity(); ++i){
                if (lhs[i] != rhs[i]){
                    return false;
                }
            }
            return  true;
        }

bool operator!=(const Pic10b::vector<std::string>& a, const Pic10b::vector<std::string>& b) {
	return !(a == b);
}