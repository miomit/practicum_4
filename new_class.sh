touch ./source/header/$1.h
echo "#include \"./header/$1.h\"
#include <stdlib.h>" > ./source/$1.c