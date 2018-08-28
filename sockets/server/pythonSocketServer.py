from __future__ import print_function

import socketserver
import mysql.connector
from mysql.connector import errorcode
import time
from datetime import datetime, date, timedelta
import re



class MySensorDataHandler(socketserver.StreamRequestHandler):

    def handle(self):
        cnx = mysql.connector.connect(user='jamster', password='1MckiD4', host='localhost', database='tempANDrelHsensors')
        cnx.database = 'tempANDrelHsensors'

        myTime = datetime.now()
        print(myTime.year, myTime.month, myTime.day, myTime.hour, myTime.minute, myTime.second, myTime.microsecond)
        print(myTime)

        # self.data = self.request.recv(1024).strip()
        self.data = self.rfile.readlines()

        data = []
        for i in range(len(self.data)):
            tmpROW = self.data[i].decode("utf-8")
            tmpROW = re.sub('[\r\n]', '', tmpROW)
            data.append(tmpROW)

        tblName = data[0]
        print(tblName)
        TABLES = {}
        TABLES[tblName] = (
            "CREATE TABLE `{}` ("
            "   `measurementID` BIGINT(100) NOT NULL AUTO_INCREMENT,"
            "   `date` TIMESTAMP(2) NOT NULL,"
            "   `relative_humidity` DOUBLE NOT NULL,"
            "   `temperatureC` DOUBLE NOT NULL,"
            "   `temperatureF` DOUBLE NOT NULL,"
            "   PRIMARY KEY (`measurementID`),"
            "   UNIQUE INDEX `measurementID_UNIQUE` (`measurementID` ASC) VISIBLE"
            ") ENGINE=InnoDB".format(tblName)
        )


        cursor = cnx.cursor()
        try:
            print("Creating table {}: ".format(tblName), end='')
            cursor.execute(TABLES[tblName])
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_TABLE_EXISTS_ERROR:
                print("already exists")
            else:
                print(err.msg)
        else:
            print("OK!")

        
        add_datapt = ("INSERT INTO `{}` "
                      "(date, relative_humidity, temeratureC, temperatureF) "
                      "VALUES (%(date_time_pt)s, %(relH)s, %(tC)s, %(tF)s)".format(tblName))

        aDataPT = {
            'date_time_pt': myTime,
            'relH': data[1],
            'tC': data[2],
            'tF': data[3],
        }

        cursor.execute(add_datapt, aDataPT)
        cnx.commit()

        add_datapt2 = ("INSERT INTO `allTestSensors` "
                       "(date, relativeHumidity, temperatureF, temperatureC, sensorID) "
                       "VALUES (%(dateINFO)s, %(relH)s, %(tF)s, %(tC)s, %(senID)s)")
        
        aDataPT2 = {
            'dateINFO': myTime,
            'relH': data[1],
            'tF': data[3],
            'tC': data[2],
            'senID': data[0],
        }

        cursor.execute(add_datapt2, aDataPT2)
        cnx.commit()

        print(data)

        cursor.close()
        cnx.close()



if __name__ == "__main__":
    HOST, PORT = "192.168.1.238", 5000

    print("started server!")

    server = socketserver.TCPServer((HOST, PORT), MySensorDataHandler)

    server.serve_forever()