from py_lib.logger import Logger
from py_lib.thread import Worker

import socket
from time import sleep
from typing import Callable

class Tcp_Handle:
    def __init__(self, ip: str, port: int) -> None:
        self.__host = (ip, port)
        self.client = None
        self.__clbk = []
        self.__logger = Logger()

    def __del__(self):
        self.disconnect()

    def connect(self):
        """
        Try to connect to host until success
        """
        self.disconnect()
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.settimeout(2)
        try:
            self.client.connect(self.__host)
            self.connected = True
        except Exception as e:
            self.__logger.error(f"Fail to connect to server (Error: {e})")

    def disconnect(self):
        if self.client:
            self.client.close()
            self.client = None
        self.connected = False
    
    def addCallback(self, clbk: Callable):
        """
        Called everytime receiving message

        clbk(msg: str)
        """
        self.__clbk.append(clbk)

    @Worker.employ
    def listen(self):
        """
        Auto reconnect and read forever
        """
        while True:
            while True:
                self.connect()
                if self.connected:
                    break
                sleep(1)

            data_buf = ""
            while True:
                try:
                    recv = self.client.recv(1024)
                    print(f"receive _{recv}_")
                    if not recv:
                        self.__logger.error(f"Server disconnected!")
                        break
                except ConnectionResetError:
                    print(f"Server disconnected!")
                    break
                except socket.timeout:
                    print(f"Socket time out")
                    continue

                data_buf += recv.decode()
                while "\r\n\r\n" in data_buf:
                    id = data_buf.index("\r\n\r\n")
                    msg = data_buf[:id]
                    data_buf = data_buf[id+4:]

                    try:
                        for clbk in self.__clbk:
                            clbk(msg)
                    except Exception as e:
                        self.__logger.error(f"Message error (Msg: {msg}) (Error: {e})")

    def send(self, cmd: str):
        """
        Send command to tcp server (cmd + \\r\\n\\r\\n)
        """
        cmd += "\r\n\r\n"
        self.client.sendall(cmd.encode('UTF-8'))
        print("SEND", cmd)