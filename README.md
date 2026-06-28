<img width="2865" height="1682" alt="image" src="https://github.com/user-attachments/assets/33642f69-5dd4-47d3-9888-9f554db875b8" /># Chameleon Vehicle Interface

ROS2 기반 카멜레온 4WS/4WD 플랫폼 Vehicle Interface 노드

## 개발 환경
- OS: Ubuntu 22.04 (WSL2)
- ROS2: Humble
- Language: C++

## 기능
Autoware에서 출력되는 조향각(AckermannControlCommand)을 
카멜레온 4WS 플랫폼의 전륜/후륜 각도로 변환

## 변환 방식 (Ackermann 기하학)
조향각 δ 입력
↓
회전반경 R = wheel_base / tan(δ)
↓
FL = atan(wheel_base / (R - tread/2))
FR = atan(wheel_base / (R + tread/2))
RL = -FL  (counter-phase, 소회전 모드)
RR = -FR

## 실행 방법
```bash
# 빌드
cd ~/ros2_ws
colcon build --packages-select chameleon_vehicle_interface
source install/setup.bash

# 실행
ros2 run chameleon_vehicle_interface chameleon_vehicle_interface_node

# 테스트 (다른 터미널)
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist \
  "{linear: {x: 2.0}, angular: {z: 0.3}}"
```

## 실행 결과
  1. 노드 실행 화면
<img width="2864" height="1694" alt="시작 부분" src="https://github.com/user-  attachments/assets/1d7f05b6-e153-4214-a67a-c9a77a0ba53b" />

2. 4WS 변환 출력 화면(FL/FR/RL/RR 각도 확인)
<img width="2866" height="1682" alt="실행" src="https://github.com/user-attachments/assets/db945ca0-d614-46a3-b64c-8d0bc88276db" />





## 차량 파라미터
| 파라미터 | 현재값 | 비고 |
|---|---|---|
| wheel_base | 0.5m | 카멜레온 실측 후 교체 예정 |
| wheel_tread | 0.4m | 카멜레온 실측 후 교체 예정 |

## 다음 목표
- [ ] 카멜레온 실제 치수 측정 후 파라미터 업데이트
- [ ] CAN 통신 코드 추가
- [ ] Autoware 실제 토픽(/control/command/control_cmd) 연동
