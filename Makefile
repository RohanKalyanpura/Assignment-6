build: TwoPipesTwoChildren.cpp
	g++ -o TwoPipesTwoChildren TwoPipesTwoChildren.cpp
run: build
	./TwoPipesTwoChildren
clean:
	rm -f TwoPipesTwoChildren
