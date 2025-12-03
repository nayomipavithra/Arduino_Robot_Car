
Line Following, Obstacle Avoiding & Bluetooth Controlled Robot Car

This project involves the development of an intelligent robot car using an Arduino Nano microcontroller, IR line sensors, ultrasonic sensor, servo motor, L298N motor driver, and an HC-05 Bluetooth module. The system is capable of following a line, avoiding obstacles, and operating in manual mode through Bluetooth commands from a mobile device. The robot continuously reads sensor inputs to determine the correct movement and adjusts its direction or speed based on the environment.

Key features of the project:

Line Following:
The robot uses two IR sensors to detect the black path on a white surface. Based on the input from the sensors, the system adjusts the motor directions to keep the robot accurately following the line.

Obstacle Avoidance:
An ultrasonic sensor mounted on a servo motor scans the surroundings to detect obstacles. When an obstacle is detected within a predefined distance, the robot analyses left and right directions and chooses the safer path to avoid collisions.

Bluetooth Manual Control:
A Bluetooth module (HC-05) allows the user to manually control the robot using a mobile application. Commands such as forward, backward, left, right, and stop can be sent wirelessly, providing full manual control when needed.

Servo-Assisted Scanning:
The ultrasonic sensor is attached to a servo motor that rotates to predefined angles to check the environment on both sides. This helps the robot make accurate decisions when navigating around obstacles.

Dual Mode Operation:
The robot supports both automatic and manual modes. In automatic mode, it performs line following combined with obstacle avoidance. In manual mode, the user can take control through Bluetooth commands.

Motor Control with L298N:
The L298N motor driver is used to control the direction and speed of the DC motors, enabling smooth movement and accurate directional changes.

This project is ideal for demonstrating autonomous navigation, path-following behavior, wireless robot control, and smart obstacle detection using a combination of sensors and motor control techniques.
