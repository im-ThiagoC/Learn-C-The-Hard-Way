echo "Running unit tests:"

for i in tests/*_tests.c
do
    if test $i
    then
        if ./$i 2>> tests/tests.log #I need UNIX system for this
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