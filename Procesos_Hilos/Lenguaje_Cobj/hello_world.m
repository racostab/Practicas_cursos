/*
   Description
      Objetive C Hello Word
   Compile
      $ clang -framework Foundation hello_world.m -o hello_world
	  -framework: Specifies a framework to use to compile the program. 
	   Since this program uses Foundation, we include the Foundation framework.

      En Linux
       $ gcc -o hello_world -l objc hello_world.m 

    Ambos compiladores arrojan:
       hello_world: Mach-O 64-bit executable arm64
*/
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    //@autoreleasepool {
        // Solo para clang
        //NSLog(@"Hello, World!");

        // Solo para gcc
        printf("Hello World");
    //}
    return 0;
}
