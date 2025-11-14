g++ gen.cpp -o gen.out
g++ ac.cpp -o ac.out
g++ wa.cpp -o wa.out
for ((i=0;;i++))
do
    echo "$i"
    ./gen.out > in.txt
    ./ac.out < in.txt > ac.txt
    ./wa.out < in.txt > wa.txt
    if [ “$?” -ne 0 ]; then
      exit 1
    fi
    { cat in.txt; echo; cat ac.txt; } > case_$i.txt
    diff ac.txt wa.txt || break
done