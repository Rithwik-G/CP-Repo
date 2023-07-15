if [[ $* == *g* ]]
then
	g++-12 testgen.cpp -o gen -fsanitize=undefined
fi
if [[ $* == *b* ]]
then
	g++-12 bruteforce.cpp -o brute -fsanitize=undefined
fi
if [[ $* == *o* ]]
then
	g++-12 Lifeguards-Plat.cpp -fsanitize=undefined
fi
for ((i = 1; i <= 100; ++i)); do
	echo $i
	./gen $i > in
	./a.out < in > out1
	./brute < in > out2
	diff -w out1 out2 || break

done