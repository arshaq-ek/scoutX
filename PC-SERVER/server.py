from flask import Flask, render_template, request
import requests

# Change this to match your ESP32's IP address
ESP32_IP = "192.168.1.8"

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", stream_url=f"http://{ESP32_IP}:81/stream")

@app.route("/move", methods=["GET"])
def move():
    direction = request.args.get("dir")
    if direction:
        print(f"Received command: {direction}")
        try:
            response = requests.get(f"http://{ESP32_IP}/move", params={"dir": direction}, timeout=2)
            print(f"ESP32 Response: {response.text}")
            return f"Command '{direction}' sent. ESP32 response: {response.text}"
        except requests.exceptions.RequestException as e:
            print("Error sending command:", e)
            return f"ESP32 unreachable: {e}", 500
    return "No command provided", 400

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
