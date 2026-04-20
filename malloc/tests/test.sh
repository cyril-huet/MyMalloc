#!/bin/bash

PASSED=0
FAIL=0

for f in malloc/*[^.c]; do
    LD_PRELOAD=../libmalloc.so ./$f
    if [ $? -eq 0 ]; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in calloc/*[^.c]; do
    LD_PRELOAD=../libmalloc.so ./$f
    if [ $? -eq 0 ]; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in realloc/*[^.c]; do
    LD_PRELOAD=../libmalloc.so ./$f
    if [ $? -eq 0 ]; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

for f in free/*[^.c]; do
    LD_PRELOAD=../libmalloc.so ./$f
    if [ $? -eq 0 ]; then
        PASSED=$((PASSED + 1))
    else
        FAIL=$((FAIL + 1))
    fi
done

echo ""
echo "Test Real Program:"
echo ""

if [ -n "LD_PRELOAD=../libmalloc.so ls" ]; then
    echo "Test ls passed"
    PASSED=$((PASSED + 1))
else
    FAIL=$((FAIL + 1))
fi

if [ -n "LD_PRELOAD=../libmalloc.so cat Makefile" ]; then
    echo "Test cat passed"
    PASSED=$((PASSED + 1))
else
    FAIL=$((FAIL + 1))
fi


if [ -n "LD_PRELOAD=../libmalloc.so echo \"Hello World\"" ]; then
    echo "Test echo passed"
    PASSED=$((PASSED + 1))
else
    FAIL=$((FAIL + 1))
fi

echo ""
echo "PASSED: $PASSED"
echo "FAIL: $FAIL"
