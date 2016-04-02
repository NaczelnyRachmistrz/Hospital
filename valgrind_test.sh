#Prosty skrypt odpalający valgrinda na testach, ./valgrind_test.sh sciezka_do_testow
make;

for f in ${1}/*.in; do
	echo -e "\e[32m$f:\e[39m";
	valgrind --leak-check=full ./hospital -v <$f > temp.out 2> tempErr.out;
	tail -n 10 tempErr.out;
	done;
rm temp.out;
rm tempErr.out;
make clean;
