#include "customAssert.h"

void customAssert( int check ){

    if( check < 0 )
    {
        printf( "failed\n" );
    } else
    {
        printf( "succeeded\n" );
    }
    

}