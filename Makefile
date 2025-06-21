# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -std=c++17

PROGRAMS = LeastSquares Maximum_BeamSearch Maximum_WithoutBeamSearch

# When running "make"
all:
	@echo Available programs to compile: $(PROGRAMS)
	@echo To compile, enter: make program_name.
	@echo Then, run the program by entering its name.

# Compile individual programs
LeastSquares: LeastSquares.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

Maximum_BeamSearch: Maximum_BeamSearch.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

Maximum_WithoutBeamSearch: Maximum_WithoutBeamSearch.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean
clean:
	del /Q $(PROGRAMS:=.exe) 2> NUL
