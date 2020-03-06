GCC       =   g++
SRCDIR    =   src
OBJDIR    =   obj
WARNINGS  =   -Wall -Wextra -Wconversion
SOURCE    =   $(wildcard ${SRCDIR}/*.cpp) 
OBJ       =   $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(subst $(SRCDIR)/, ,$(SOURCE))))
DEPS      =   $(OBJ:.o=.d)
#define libs to use
LIBS      =   -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_photo -pthread
TARGET    =   application

.PHONY: all clean

all: $(OBJDIR) $(TARGET)
-include $(DEPS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(GCC) $(CPPFLAGS) $(WARNINGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

$(TARGET): $(OBJ)
	$(GCC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR) 