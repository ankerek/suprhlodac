#include <stdio.h>

int main() {
    FILE * f = popen( "ls -l | tr -s ' ' | cut -d ' ' -f9 | tail -n +2", "r" );
    if ( f == 0 ) {
        fprintf( stderr, "Could not execute\n" );
        return 1;
    }
    const int BUFSIZE = 1000;
    char buf[ BUFSIZE ];
    while( fgets( buf, BUFSIZE,  f ) ) {
        fprintf( stdout, "%s", buf  );
    }
    pclose( f );
}