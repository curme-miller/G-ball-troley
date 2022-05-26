import sensor, image, time, ujson
from pid import PID
from pyb import Servo, UART

pan_servo=Servo(1)
tilt_servo=Servo(2)

uart = UART(3,9600)   # P4-TX  P5-RX

pan_servo.calibration(500,2500,500)
tilt_servo.calibration(500,2500,500)

red_threshold  = (13, 49, 18, 61, 6, 47) #红色阈值
green_threshold = (13, 92, 7, -49, 61, 11) #绿色阈值

pan_pid = PID(p=0.07, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
tilt_pid = PID(p=0.05, i=0, imax=90) #脱机运行或者禁用图像传输，使用这个PID
#pan_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID
#tilt_pid = PID(p=0.1, i=0, imax=90)#在线调试使用这个PID

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

def find_max(blobs):    #此函数需要修改，修改为可以追踪不同颜色（红色和绿色）的靶子--<cyb>
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

data = {"pan_output":0}

while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # Take a picture and return the image.

    blobs = img.find_blobs([green_threshold])
    if blobs:
        max_blob = find_max(blobs)
        pan_error = max_blob.cx()-img.width()/2
        tilt_error = max_blob.cy()-img.height()/2

        #print("pan_error: ", pan_error)

        img.draw_rectangle(max_blob.rect()) # rect
        img.draw_cross(max_blob.cx(), max_blob.cy()) # cx, cy

        pan_output=pan_pid.get_pid(pan_error,1)/2
        tilt_output=tilt_pid.get_pid(tilt_error,1)
        data["pan_output"] = pan_output
        

        jsonData = ujson.dumps(data)
        uart.write(jsonData + '\r\n')


        pan_servo.angle(pan_servo.angle()+pan_output)
        tilt_servo.angle(tilt_servo.angle()-tilt_output)
