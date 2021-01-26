CXX = g++
CXXFLAGS = -Wall -Wextra -L. -g -std=c++11
INPUT_LIB = input
LINK_FLAGS = -fPIC -shared 
LIB_CPPS = string.cpp field.cpp ip.cpp port.cpp
LIB = firewall
EXEC= firewall.exe
MAIN = main.cpp
RM = rm -f

all:${EXEC}

$(LIB):
	$(CXX) ${CXXFLAGS} ${LINK_FLAGS} ${LIB_CPPS} -o lib${LIB}.so

${EXEC}: ${LIB} 
	$(CXX) ${CXXFLAGS} ${MAIN} -o ${EXEC} -l$(LIB) -l$(INPUT_LIB)

clean:
	${RM} ${LIB} ${EXEC}