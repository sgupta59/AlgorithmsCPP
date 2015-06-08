#include <new>
#include <stdio.h>
 
class Test {
private:
    char *mData;
    size_t mDataLength;
 
    // Disallow use of the default new operator!
    static void *operator new( std::size_t ) ;
 
public:
    Test( const char *data, size_t dataLength ) : mData( nullptr ), mDataLength( dataLength ) {
        // We have a special allocator so we can keep our data close.  The mData pointer
        // should point to a space directly after the end of our this pointer.  We can
        // then move the passed data into that memory.
        //
        // NOTE: this is scary.  Don't do this in production code.
        mData = (char *)(((unsigned char *)this) + sizeof( Test ));
        ::memcpy( mData, data, dataLength );
    }
 
    ~Test() {
        // Note: we don't have to free the mData pointer because it's taken care of for
        // us by our custom allocation functions.
    }
 
    const char *GetData() const { return mData; }
 
    static void *operator new( std::size_t size, unsigned short extra ) {
        return ::operator new( size + extra );
    }
 
    static void operator delete( void *memory, unsigned short extra ) {
        operator delete( memory );
    }
 
    static void operator delete( void *memory ) {
        ::operator delete( memory );
    }
};
 
int main( void )
{
    const char *kStr = "This is my crazy string";
    unsigned short len = static_cast< unsigned short >( ::strlen( kStr ) + 1 );   // Allocate an extra byte for the null terminator
     
    Test *t = new (len) Test( kStr, len );
    ::printf( "Test lives at 0x%p\nIts data lives at 0x%p and is %s", t, t->GetData(), t->GetData() );
    delete t;
 
    return 0;
}