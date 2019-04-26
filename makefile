main = CourseProjectV9.o
dependent = main.o rank.o error.o score.o editscore.o incount.o filegen.o cli.o
CompileAll: $(dependent) pch.h
	g++ -pedantic-errors -std=c++11 $(dependent) -o exeOut
main.o: pch.h CourseProjectV9.cpp
	g++ -pedantic-errors -std=c++11 -c CourseProjectV9.cpp -o main.o
rank.o: pch.h GiveRank.cpp
	g++ -pedantic-errors -std=c++11 -c GiveRank.cpp -o rank.o
error.o: pch.h myerrorcheckingfunctions.cpp
	g++ -pedantic-errors -std=c++11 -c myerrorcheckingfunctions.cpp -o error.o
score.o: pch.h ScoreOperations.cpp
	g++ -pedantic-errors -std=c++11 -c ScoreOperations.cpp -o score.o
editscore.o: pch.h EditScoreORDQ.cpp
	g++ -pedantic-errors -std=c++11 -c EditScoreORDQ.cpp -o editscore.o
incount.o: pch.h InfoFileInputPlusCount.cpp
	g++ -pedantic-errors -std=c++11 -c InfoFileInputPlusCount.cpp -o incount.o
filegen.o: pch.h FileGeneration.cpp
	g++ -pedantic-errors -std=c++11 -c FileGeneration.cpp -o filegen.o
cli.o: pch.h CLI.cpp
	g++ -pedantic-errors -std=c++11 -c CLI.cpp -o cli.o
                                                                    
