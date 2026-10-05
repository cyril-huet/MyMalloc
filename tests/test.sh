#!/bin/bash

PASSED=0
FAIL=0

run_program()
{
    if [ "$(uname -s)" = "Darwin" ]; then
        DYLD_LIBRARY_PATH=.. "$@"
    else
        LD_PRELOAD=../libmalloc.so "$@"
    fi
}

for f in malloc/*[^.c]; do
    if run_program "./$f"; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in calloc/*[^.c]; do
    if run_program "./$f"; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in realloc/*[^.c]; do
    if run_program "./$f"; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in free/*[^.c]; do
    if run_program "./$f"; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

echo ""
echo "Test Real Program:"
echo ""

if run_program /bin/ls >/dev/null 2>&1; then
    echo "Test ls passed"
    PASSED=$((PASSED + 1))
else
    echo "Test ls failed"
    FAIL=$((FAIL + 1))
fi

if run_program /bin/cat Makefile >/dev/null 2>&1; then
    echo "Test cat passed"
    PASSED=$((PASSED + 1))
else
    echo "Test cat failed"
    FAIL=$((FAIL + 1))
fi

if run_program /bin/echo "Hello World" >/dev/null 2>&1; then
    echo "Test echo passed"
    PASSED=$((PASSED + 1))
else
    echo "Test echo failed"
    FAIL=$((FAIL + 1))
fi

echo ""
echo "PASSED: $PASSED"
echo "FAIL: $FAIL"