CPP = /usr/local/opt/llvm/bin/clang++
CPPFLAGS = -I /usr/local/opt/llvm/include \
			-O3 \
			-std=c++11
LDFLAGS = -L/usr/local/opt/llvm/lib
main: src/main.cpp
	@echo "Building source.."
	$(CPP) $(CPPFLAGS) $^ -o bin/main $(LDFLAGS)

clean:
	@echo "Cleaning up.."
	rm bin/main