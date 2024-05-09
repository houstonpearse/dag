function test () {
    a=$(mktemp)
    ./$1 < tests/test$2.txt > a
    if diff a tests/test$2-out.txt; then 
        echo "✅ Test $2 Passed"
    else
        echo "❌ Test $2 Failed"
    fi
    rm a
}
for i in $(seq 1 $2)
do
    test $1 $i
done