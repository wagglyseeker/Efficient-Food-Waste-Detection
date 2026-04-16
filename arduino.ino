#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Pin definitions for the motor drivers
#define LEFT_MOTOR_FORWARD 15
#define LEFT_MOTOR_BACKWARD 4
#define RIGHT_MOTOR_FORWARD 0
#define RIGHT_MOTOR_BACKWARD 12

String htmlPage = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 Robot Control</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f4f4f9;
            color: #333;
            text-align: center;
            margin: 0;
            padding: 0;
        }

        h1 {
            margin-top: 50px;
            font-size: 36px;
            color: #222;
        }

        .container {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            flex-direction: column;
        }

        button {
            background-color: #6200ea;
            color: #fff;
            border: none;
            padding: 15px 20px;
            margin: 5px;
            font-size: 16px;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            transition: background-color 0.3s, transform 0.3s;
        }

        button:hover {
            background-color: #3700b3;
            transform: translateY(-2px);
        }

        button:active {
            transform: translateY(2px);
        }
    </style>
    <script>
        function sendCommand(cmd) {
            console.log(cmd)
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/' + cmd, true);
            xhr.send();
        }
    </script>
</head>

<body>
    <div class="container">
        <h1>ESP8266 Robot Control</h1>
        <div class="controls" style="display: flex; flex-direction:column; width:250px">
            <div style="display: flex; justify-content:center">
            <button onmousedown="sendCommand('forward')"  onmouseup="sendCommand('stop')" ontouchstart="sendCommand('forward')" ontouchend="sendCommand('stop')">▲</button>
            </div>
            <div style="display: flex; justify-content:space-around">
                <button onmousedown="sendCommand('left')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('left')" ontouchend="sendCommand('stop')">◀</button>
                <button onmousedown="sendCommand('stop')" ontouchstart="sendCommand('stop')">■</button>
                <button onmousedown="sendCommand('right')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('right')" ontouchend="sendCommand('stop')">▶</button>
            </div>
            <div>
                <button onmousedown="sendCommand('backward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('backward')" ontouchend="sendCommand('stop')">▼</button>
            </div>
            
        </div>
    </div>

    <script>

        document.addEventListener('keydown',(e) =>{
            e.preventDefault();

            if(e.key == "w" || e.key == "ArrowUp"){
                sendCommand('forward')
            }else if (e.key == "a" || e.key == "ArrowLeft") {
                sendCommand('left')
            } else if (e.key == "s" || e.key == "ArrowDown") {
                sendCommand('backward')
            } else if (e.key == "d" || e.key == "ArrowRight") {
                sendCommand('right')
            }
        })

        document.addEventListener('keyup',(e) =>{
            e.preventDefault();

            sendCommand('stop')
        })
    </script>
</body>

</html>
)=====";

// Functions to control the motors
void move_forward() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

void move_backward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  digitalWrite(14, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

void turn_left() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW); // Left wheels move backward
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH); // Right wheels move forward
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(14, HIGH);
  server.send(200, "text/plain", "Turning Left");
}

void turn_right() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);  // Left wheels move forward
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW); // Right wheels move backward
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(14, HIGH);
  server.send(200, "text/plain", "Turning Right");
}

void stop_movement() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(14, LOW);
  server.send(200, "text/plain", "Stopped");
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Set up motor control pins
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(14, OUTPUT);

  // Set ESP8266 as an Access Point
  WiFi.softAP("ESP_Robot_Control", "password123");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

  // Set up web server routes for movement
  server.on("/", []() { server.send(200, "text/html", htmlPage); });
  server.on("/forward", move_forward);
  server.on("/backward", move_backward);
  server.on("/left", turn_left);
  server.on("/right", turn_right);
  server.on("/stop", stop_movement);

  server.begin();  // Start the web server
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests
}