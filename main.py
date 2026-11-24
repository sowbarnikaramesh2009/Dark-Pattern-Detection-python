import serial
import time

# Connect Arduino
arduino = serial.Serial('COM3', 9600, timeout=1)

time.sleep(2)

print("DIGITAL DARK PATTERN DETECTOR")
print("--------------------------------")

def detect_pattern(message):

    text = message.lower()

    urgency_words = [
        "only 1 item left",
        "only one item left",
        "limited time",
        "hurry",
        "offer ends soon",
        "act now"
        "last item"
        "few items left"
    ]

    hidden_charge_words = [
        "extra charges",
        "hidden charges",
        "additional fee",
        "service fee"
    ]

    forced_action_words = [
        "subscribe now",
        "must buy",
        "buy now"
    ]

    if any(word in text for word in urgency_words):
        return "DARK|Urgency"

    elif any(word in text for word in hidden_charge_words):
        return "DARK|Hidden Charges"

    elif any(word in text for word in forced_action_words):
        return "DARK|Forced Action"

    else:
        return "SAFE"


while True:

    message = input("\nEnter shopping message: ")

    if message.lower() == "exit":
        break

    result = detect_pattern(message)

    print("Detection Result:", result)

    arduino.write((result + "\n").encode())

    print("Result sent to Arduino!")

arduino.close()
