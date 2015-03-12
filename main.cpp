#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "fgseg.h"
using namespace std;

int main(int argc, string argv[] )
{
	assert(argc==2);
	uu_display(argv[1]);
    return 0;
}
