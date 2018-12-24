@echo off
:C&R
cls
del out.exe
echo [...] compiling...
gcc main.c Printer.c Engine.c Evaluator.c ForbiddenMove.c MoveGenerator.c Tools.c -o out
if exist out.exe (
	echo [:-^)] compile succeeded!
	echo [...] start out.exe...
	.\out.exe
) else (
	echo [:-^(] compile failed.
)
echo [...] waiting
pause
goto C&R
