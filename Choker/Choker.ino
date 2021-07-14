#include<SoftwareSerial.h> // 블루투스 통신 사용 라이브러리

SoftwareSerial TestSerial(3, 2); // 3, 2 pin을 불루투스 핀으로 사용

int piezo = 9; // 피에조 부저
int curTime = 0; // millis 현재 시간
int pastTime = 0; // millis 과거 시간
int minVal = 265; // 최저값
int maxVal = 402; // 최고값
double x, y, z; // 축

void setup() {
  // 시리얼 통신의 속도를 9600으로 설정
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  //블루투스와 아두이노의 통신속도를 9600으로 설정
  TestSerial.begin(9600);
  
  pinMode(piezo, OUTPUT); // 피에조 사용
}

void loop() { //코드를 무한반복합니다.
  curTime = millis(); // 현재 시간 입력
  int xRead = analogRead(A2); // A2 값 읽기
  int yRead = analogRead(A1); // A1 값 읽기
  int zRead = analogRead(A0); // A0 값 읽기

  // x 구하는 코드
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

  //TestSerial.print(x);
  Serial.println(x); // x값 확인용 serial 모니터 사용
  
  if (x > 170) { // 거북목이 심할때
     TestSerial.print(1);  // 블루투스 통신으로 1을 보냄
     if (curTime > pastTime + 300) { // 0.3초가 지나면
      tone(piezo, 392); // 솔
      pastTime = curTime; // 과거값에 현재값 넣기
    }
  }

  else if (x >= 150 && x <= 170) { // 거북목이 보통
    TestSerial.print(2); // 블루투스 통신으로 2를 보냄
    if (curTime > pastTime + 500) { // 0.5초가 지나면
      tone(piezo, 256); // 도
      pastTime = curTime; // 과거값에 현재값 넣기
    }
   }
  else {
    TestSerial.print(3); // 블루투스 통신으로 3을 보냄
      noTone(piezo); // 소리끄기
    }
  delay(1000); // 딜레이 1초 주기
}
