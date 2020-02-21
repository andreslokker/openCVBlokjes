GCC       =   g++
SRCDIR    =   src
OBJDIR    =   obj
SOURCE    =   $(wildcard ${SRCDIR}/*.cpp)
OBJ       =   $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(subst $(SRCDIR)/, ,$(SOURCE))))
#define libs to use
LIBS      =   -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_videoio
TARGET    =   application

.PHONY: all clean

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(GCC) $(CPPFLAGS) -c $^ -o $@

$(TARGET): $(OBJ)
	$(GCC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR) 