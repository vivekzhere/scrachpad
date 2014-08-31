#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import httplib
import threading

from socket import socket
 
PORT_NUMBER = 8080
class test_server:
    def __init__(self):
        self.ip = "192.168.56.11"
        self.test_server_timer()

    def tcp_test(self, server_info):
         cpos = server_info.find(':')
         try:
             sock = socket()
             sock.connect((server_info[:cpos], int(server_info[cpos+1:])))
             sock.close
             return True
         except:
             return False
    
    def test_server_timer(self):
        if self.tcp_test("192.168.56.11:80"):
            self.ip = "192.168.56.11"
        else:
            self.ip = "192.168.56.12"
        threading.Timer(1, self.test_server_timer).start()

    def get_server(self):
        return self.ip

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
    server_detail = test_server()
    #Handler for the GET requests
    def do_GET(self):
        
        type_index = self.requestline.find(' ')
        request_type = self.requestline[:type_index]
        url_index = self.requestline[type_index+1:].find(" ")
        request_url = self.requestline[type_index+1:][:url_index]

        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()

        ip = self.server_detail.get_server()
        print "Request to Server : ", ip, "\n"

        try:
            conn = httplib.HTTPConnection(ip)
            if request_type == "POST":
                content_len = int(self.headers.getheader('content-length', 0))
                post_body = self.rfile.read(content_len)
                conn.request(request_type, request_url, post_body)
            else:
                conn.request(request_type, request_url)
            r1 = conn.getresponse()
        except:
            print "Connection Failed\n"
            conn.close()
            return
        data1 = r1.read()
        conn.close()

        # Send the html message
        self.wfile.write(data1)
        
        return
    def do_POST(self):
        self.do_GET()
        return

try:
    #Create a web server and define the handler to manage the
    #incoming request
    server = HTTPServer(('', PORT_NUMBER), myHandler)
    print 'Started httpserver on port ' , PORT_NUMBER
    
    #Wait forever for incoming htto requests
    server.serve_forever()

except KeyboardInterrupt:
    print '^C received, shutting down the web server'
    server.socket.close()
