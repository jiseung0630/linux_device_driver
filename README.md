# Device Driver

### 실습 방법
1) ubuntu에서 각 폴더로 진입
2) vi Makefile로 진입
3) 리눅스 커널 폴더 경로 확인 및 변경 ->
   ```bash
   KDIR = /home/ubuntu/kernel/linux
   ```
4) raspberry pi와 ubuntu를 nfs를 통해 mount
5) make명령어를 통해 .ko파일 생성
6) make명령어를 통해 raspberry pi 에 .ko파일 과 app파일 생성
7) mknod로 파일 시스템 노드 생성
    ```bash 
    ex) mknod /dev/ledkey c 230 0
    ```
9) lsmod로 현재 커널에 로드된 모듈 확인
     ```bash
    ex) insmod ledkey.ko
     ```
10) insmod로 커널에 직접 로드 
11) 앱 파일을 실행 하여 실행 확인
12) rmmod로 모듈 해제
