$ gcc file\_processor\_svr.c -o file\_processor\_svr

$ ./file\_processor\_svr

$ gcc file\_processor\_clnt.c -o file\_processor\_clnt

$ ./file\_processor\_clnt <input\_file> <mode>

$ ./file\_processor\_clnt test.txt count

1번째 줄 전송...

1번째 줄 결과 수신: Line 1: 11 chars, 2 words

2번째 줄 전송...

2번째 줄 결과 수신: Line 2: 14 chars, 4 words



=== 처리 통계 ===

처리 모드: count

처리한 줄 수: 2줄

소요 시간: 0.01초

$ ./file\_processor\_svr

1번째 줄 처리 중...

2번째 줄 처리 중...

서버 종료

$ ./file\_processor\_clnt test.txt upper

1번째 줄 전송...

1번째 줄 결과 수신: Line 1: HELLO WORLD

2번째 줄 전송...

2번째 줄 결과 수신: Line 2: THIS IS A TEST



=== 처리 통계 ===

처리 모드: upper

처리한 줄 수: 2줄

소요 시간: 0.01초



1번째 줄 처리 중...

2번째 줄 처리 중...

서버 종료



$ ./file\_processor\_clnt test.txt lower

1번째 줄 전송...

1번째 줄 결과 수신: Line 1: hello world

2번째 줄 전송...

2번째 줄 결과 수신: Line 2: this is a test



=== 처리 통계 ===

처리 모드: lower

처리한 줄 수: 2줄

소요 시간: 0.01초



1번째 줄 처리 중...

2번째 줄 처리 중...

서버 종료



$ ./file\_processor\_clnt test.txt reverse

1번째 줄 전송...

1번째 줄 결과 수신: Line 1: dlroW olleH

2번째 줄 전송...

2번째 줄 결과 수신: Line 2: tseT a si sihT



=== 처리 통계 ===

처리 모드: reverse

처리한 줄 수: 2줄

소요 시간: 0.01초



1번째 줄 처리 중...

2번째 줄 처리 중...

서버 종료







