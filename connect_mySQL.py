import pymysql
import serial
import time

BAUD_RATES = 115200  
# COM_PORT = '/dev/ttyUSB0'
COM_PORT = 'COM3'
ser = serial.Serial(COM_PORT, BAUD_RATES)

while True:
	db = pymysql.connect("localhost","root","0000","Test")

	cursor = db.cursor()

	data_raw = ser.read(220) # put data into data_raw
	print(data_raw)

	uS = data_raw[31:35].decode("ISO-8859-1") # select uS number
	pH = data_raw[149:153].decode("ISO-8859-1") # select pH number
	Water = int(data_raw[184:187].decode("ISO-8859-1"))*0.1 # select Water number
	Water = str(Water) # change Water's type to string
	print(uS)
	print(pH)
	print(Water)
	
	print("="*20)
	
	localtime = time.strftime("%Y-%m-%d %H:%M:%S" , time.localtime()) # set time

	s = localtime + ',' + uS +','+ pH + ',' + Water	#  link all data and use ',' to split

	sql = """INSERT INTO data (datetime,uS,pH,percent) VALUES (%s,%s,%s,%s)""" # insert data to database
	data = s.split(',') # split string s
	print(data)

        

	#update data to database

	cursor.execute(sql,data) 
	db.commit()



	db.close() # close database

