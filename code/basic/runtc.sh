prog=$1
shift
g++ -O2 -std=c++20 -fsanitize=address -Wall -Wextra -Wshadow ${prog}.cpp -o ${prog}.out
for f in "$@"; do
  out=${prog}_$(basename "$f").out
  echo "input: $f"
  cat "$f"
  echo "output: $out"
  ./${prog}.out < "$f" | tee "$out"
  echo
done