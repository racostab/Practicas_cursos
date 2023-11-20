/*
   Description
      Objetive C Hello Word
   Compile
      $ clang -framework Foundation procesos_v1.m -o procesos_v1
	  -framework: Specifies a framework to use to compile the program. 
	   Since this program uses Foundation, we include the Foundation framework.
*/
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // NSLog = printf
        NSLog(@"Hello, World!");
    }
    return 0;
}
