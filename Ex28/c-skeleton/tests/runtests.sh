echo "Running unit tests:"

for i in tests/*tests
do
    if test -f $i
    then
        if $VALGRIND ./$i 2>> tests/tests.log #I need UNIX system for Valgrind
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""