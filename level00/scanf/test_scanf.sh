#!/bin/bash

echo "=== 📝 Test automatique scanf vs ft_scanf ==="

for i in {1..50}
do
    echo "🔹 Test $i"
    echo "$i Hello X" | ./scanf_test scanf > std_out.txt
    echo "$i Hello X" | ./scanf_test ft > ft_out.txt

    if diff std_out.txt ft_out.txt > /dev/null
    then
        echo "✅ Test $i OK"
    else
        echo "❌ Test $i FAILED"
        echo "🔎 Différence :"
        diff std_out.txt ft_out.txt
    fi

    echo "----------------------"
done

rm -f std_out.txt ft_out.txt
