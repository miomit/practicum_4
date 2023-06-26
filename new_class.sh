touch ./source/header/$1.h
echo "#include \"./header/$1.h\"
#include <stdlib.h>" > ./source/$1.c

echo "#include <assert.h>
#include <stdio.h>" > ./test/header/$1_test.h

echo "#include \"./header/$1_test.h\"
#include \"../source/header/$1.h\"" > ./test/$1_test.c