src=$(wildcard ./*.c)
obj=$(patsubst %.c,%.o,$(src))

target=app
$(target):$(obj)
	gcc $^ -o $@
#	gcc $(obj) -o $(target)

%.o:%.c
	gcc -c $< -o $@

#main.o:main.c
#	gcc main.c -c
#
#add.o:add.c
#	gcc add.c -c
#
#sub.o:sub.c
#	gcc sub.c -c
#
#mul.o:mul.c
#	gcc mul.c -c

hello:
	echo "hello,makefile"

.PHONY:clean
clean:
	-rm $(obj) $(target) -f

