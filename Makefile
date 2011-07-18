
CC=gcc
PROG_NAME=main
INCS=datastruct.h  drawui.h  trackball.h

SRCS=callback.c  drawmenu.c  drawui.c  focallaw.c  main.c  opengl.c  toolbar.c  trackball.c  tree.c

# 从xx.c 文件得到 xx.o 文件
OBJS=${SRCS:.c=.o}

#编译GTK程序时要用到的库
LIBS=libxml-2.0 gtkglext-1.0
#---- 用户修改区域 结束

# -O2
CFLAGS=`pkg-config --cflags ${LIBS}`
LDFLAGS=`pkg-config --libs ${LIBS}`  

all: ${PROG_NAME}

${PROG_NAME}:${OBJS}
	${CC} -o ${PROG_NAME} ${OBJS} ${LDFLAGS}
#注意：上边”${CC}" 的前边有一个TAB键，而不是空格

#如果有头文件进行修改，则自动编译源文件
${OBJS}:${INCS}


.PHONY:clean
clean:
	rm -f *.o  ${PROG_NAME}

rebuild: clean all
