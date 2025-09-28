CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc -Isrc/utils -Isrc/structs

objects = main.o printer.o course.o transcript.o

grader: $(objects)
	$(CC) $(CFLAGS) -o grader $(objects)

printer.o: src/utils/printer.c src/utils/printer.h src/globals.h
	$(CC) $(CFLAGS) -c $< -o $@

course.o: src/structs/course.c src/structs/course.h \
		src/utils/printer.h src/globals.h
	$(CC) $(CFLAGS) -c $< -o $@

transcript.o: src/structs/transcript.c src/structs/transcript.h \
		src/structs/course.h src/globals.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: src/main.c src/structs/course.h src/structs/transcript.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f grader $(objects)
