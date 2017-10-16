all: create_dict.cpp article_analysis.cpp
	g++ -Wall -Wextra -std=c++11 -o create_dict.run create_dict.cpp
	g++ -Wall -Wextra -std=c++11 -o article_analize.run article_analysis.cpp

create_dict.cpp: create_dict.cpp
	g++ -Wall -Wextra -std=c++11 -o create_dict.run create_dict.cpp

article_analysis.cpp: article_analysis.cpp
	g++ -Wall -Wextra -std=c++11 -o article_analize.run article_analysis.cpp