while true
do
	clear
	rm -f ./out
	echo [Orz] compiling...
	gcc main.c Printer.c Engine.c Evaluator.c ForbiddenMove.c MoveGenerator.c Tools.c -o ./out
	if [ -f ./out ]
	then
		echo [^v^] compile succeeded
		echo [Orz] start ./out
		./out
	else
		echo [QAQ] compile failed
	fi	
	echo [Orz] waiting...
	read
done
