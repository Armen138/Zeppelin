#ZEP_VERSION := $(shell git describe)
ZEP_VERSION = 'pre-git'
CXX_FLAGS = -Wall -fexceptions  -std=c++0x -g -c -I../glfw/deps/ `pkg-config --cflags glfw3`  -D'ZEP_VERSION="$(ZEP_VERSION)"'
#CXX_FLAGS_WIN32 = -Wall -fexceptions  -std=c++0x -g -c -I../v8/include -I./win32.ext/glfw/include -I./win32.ext/glew/include -I./win32.ext/curl/include -I./win32.ext/include -D'JSGMVERSION="$(JSGM_VERSION)"' -DCURL_STATICLIB
#CXX_LDFLAGS = -lcurl -framework Cocoa -framework CoreVideo -framework IOKit -framework OpenGL  `pkg-config --libs glfw3`
CXX_LDFLAGS = -lcurl `pkg-config --libs --static glfw3`
#CXX_LDFLAGS_WIN32 = ../v8/out/ia32.release/obj.target/tools/gyp/libv8_base.ia32.a ../v8/out/ia32.release/obj.target/tools/gyp/libv8_snapshot.a ./win32.ext/glfw/lib-mingw/libglfw.a -Bstatic -static-libgcc -static-libstdc++ -L./win32.ext/curl/lib -lcurl -lidn -lrtmp -lssh2 -lcrypto -lwldap32 -lssl  -lz -lwinmm -lws2_32 -lpthread -lopengl32

OBJS = main zeppelin image http color storage
#localstorage xhr canvas color image jsgm
OUTFILE = zeppelin
OUTFILE_WIN32 = zeppelin.exe
all :
	$(foreach OBJ,$(OBJS),$(CXX) $(CXX_FLAGS) src/$(OBJ).cpp -o $(OBJ).o;)
	$(CXX) -o $(OUTFILE) $(foreach OBJ,$(OBJS),$(OBJ).o) $(CXX_LDFLAGS)

win32 :
	$(foreach OBJ,$(OBJS),$(CXX) $(CXX_FLAGS_WIN32) $(OBJ).cpp -o $(OBJ).o;)
	$(CXX) -o $(OUTFILE_WIN32) $(foreach OBJ,$(OBJS),$(OBJ).o) $(CXX_LDFLAGS_WIN32)

clean :
	$(foreach OBJ,$(OBJS),rm $(OBJ).o;)
	rm $(OUTFILE)
