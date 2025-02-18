from flask import Flask, render_template, request
import requests

# Replace with the IP address of your ESP32-CAM
ESP32_IP = "http://192.168.1.100"

app = Flask(__name__)

@app.route("/")
def index():
    # Serve the control panel webpage from templates/index.html
    return render_template("index.html")

@app.route("/move", methods=["GET"])
def move():
    # Retrieve the direction parameter from the URL
    direction = request.args.get("dir")
    if direction:
        # Log the command in the server console
        print("Received command:", direction)
        try:
            # Forward the command to the ESP32's /move endpoint
            response = requests.get(f"{ESP32_IP}/move", params={"dir": direction})
            print("ESP32 Response:", response.text)
            return f"Command '{direction}' sent. ESP32 response: {response.text}"
        except Exception as e:
            print("Error sending command:", e)
            return f"Error sending command: {e}", 500
    return "No command provided", 400

if __name__ == "__main__":
    # Run the Flask server on all available IP addresses on port 5000
    app.run(host="0.0.0.0", port=5000, debug=True)
