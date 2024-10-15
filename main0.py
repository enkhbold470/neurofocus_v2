import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import csv

# Constants
SERIAL_PORT = '/dev/tty.usbserial-10'
BAUD_RATE = 9600
MAX_X_RANGE = 100  # The range of x-axis to display at any given time

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Initialize empty lists to store data
x_vals = []
sensorValue1_data = []

# Create a function to read and process data from Arduino
def read_and_process_data():
    line = ser.readline().decode('utf-8').strip()
    print(line)

    sensorValues = line.split(', ')
    x_vals.append(float(sensorValues[0]))  # Time
    sensorValue1_data.append(int(sensorValues[1]))  # Sensor value from analog pin A0

    # Print the received values
    print(f'Time: {sensorValues[0]}, Sensor 1: {sensorValues[1]}')

# Create a function to update the plot
def update_plot(frame):
    read_and_process_data()

    # Clear the plot
    ax.clear()

    # Plot sensor data
    ax.plot(x_vals, sensorValue1_data, label='Sensor 1')
    ax.set_xlabel('Time')
    ax.set_ylabel('Sensor Values')
    ax.legend()

    # Adjust x-axis limits for scrolling effect
    if len(x_vals) > MAX_X_RANGE:
        ax.set_xlim(x_vals[-MAX_X_RANGE], x_vals[-1])  # Show the last MAX_X_RANGE data points
    else:
        ax.set_xlim(0, MAX_X_RANGE)

# Create a function to save data to a CSV file when the plot window is closed
def on_close(event):
    with open('arduino_data.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Time', 'Sensor1'])
        for x, s1 in zip(x_vals, sensorValue1_data):
            writer.writerow([x, s1])

# Register the callback function for when the plot window is closed
fig, ax = plt.subplots()
fig.canvas.mpl_connect('close_event', on_close)

# Set up the animation
ani = FuncAnimation(fig, update_plot, interval=1)

# Show the plot
plt.show()
