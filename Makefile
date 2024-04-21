twopipes_twochildren: TwoPipesTwoChildren.cpp
	g++ -Wall -o TwoPipesTwoChildren TwoPipesTwoChildren.cpp
	./TwoPipesTwoChildren
twopipes_threechildren: TwoPipesThreeChildren.cpp
	g++ -Wall -o TwoPipesThreeChildren TwoPipesThreeChildren.cpp
	./TwoPipesThreeChildren
#clean target to remove executable files
clean:
	rm -f TwoPipesTwoChildren TwoPipesThreeChildren
					
