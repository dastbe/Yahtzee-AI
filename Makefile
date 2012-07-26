.PHONY: scripts project

default: scripts project

clean:
	rm data/*_file.txt
	rm bin/yai
	rm obj/*

project: project/main.cpp obj/diceroll.o obj/choice.o obj/myai.o obj/playercard.o obj/state.o
	g++ -o bin/yai project/main.cpp obj/myai.o obj/diceroll.o obj/choice.o obj/playercard.o obj/state.o

obj/diceroll.o: project/diceroll.cpp project/diceroll.h
	g++ -c project/diceroll.cpp -o obj/diceroll.o

obj/choice.o: project/choice.cpp project/choice.h
	g++ -c project/choice.cpp -o obj/choice.o

obj/myai.o: project/myai.cpp project/myai.h project/gameai.h
	g++ -c project/myai.cpp -o obj/myai.o

obj/playercard.o: project/playercard.cpp project/playercard.h
	g++ -c project/playercard.cpp -o obj/playercard.o

obj/state.o: project/state.cpp project/state.h
	g++ -c project/state.cpp -o obj/state.o

test: scripts
	g++ -o bin/yai -D _TEST_ project/main.cpp	

scripts:
	python scripts/build_keep_set_combinations.py > data/ksb_file.txt
	python scripts/build_expected_value_file.py > data/ev_file.txt
