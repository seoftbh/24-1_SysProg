CC=gcc		# 컴파일러
CFLAGS=-I.	# 컴파일러 옵션 (현재 디렉터리에서 헤더 파일 찾기)

# 실행 파일 이름 정의
EXECUTABLES = setbuf setvbuf

# 모든 실행 파일을 빌드
all: $(EXECUTABLES)
# all: dbcreate rdlock wrlock

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

# clean 명령으로 생성된 실행 파일 삭제
clean: 
	rm -f $(EXECUTABLES)
	# rm -f dbcreate rdlock wrlock

# 실행 방법
# $ make		# 컴파일 실행
# $ make clean	# 컴파일된 모든 파일 삭제
