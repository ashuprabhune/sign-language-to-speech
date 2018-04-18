import threading
import serial
import stomp
import random

class SerialReader_MQ(threading.Thread):

    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
        self.exit = False
        self.ser = serial.Serial('COM4', 9600)
        self.temp = []

    def quit(self):
        self.exit = True

    def run(self):
        count=random.randint(25,41)
        while not self.exit:
            if count == 0:
                self.storetoMQ(self.temp)
                self.temp = []
                count = random.randint(25,41)
            else:
                self.temp.append(self.ser.readline())
                count = count -1
        self.ser.close()

    def storetoMQ(self,datax):
        conn = stomp.Connection()
        conn.set_listener('', MyListener())
        conn.start()
        conn.connect('admin', 'admin', wait=True)

        conn.subscribe(destination='/queue/bitsplease', id=1, ack='auto')
        finalstring = ''
        for dp in datax:
            finalstring = finalstring + dp.decode('utf-8', 'ignore')

        conn.send(body=finalstring, destination='/queue/bitsplease')

        conn.disconnect()

class MyListener(stomp.ConnectionListener):
    def on_error(self, headers, message):
        print('received an error "%s"' % message)
    def on_message(self, headers, message):
        print('received a message "%s"' % message)