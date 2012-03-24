.PHONY: scripts project

default: scripts project

clean:
	rm data/*_file.txt
	rm bin/yai

project:
	g++ -o bin/yai project/main.cpp

test: scripts
	g++ -o bin/yai -D _TEST_ project/main.cpp	

scripts:
	python scripts/build_keep_set_combinations.py > data/ksb_file.txt
	python scripts/build_expected_value_file.py > data/ev_file.txt