#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 25 19:31:44 2017

@author: tto21
"""

data = ""
#basic server communcations test
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
import socket

class MyHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        print("request received")
        self.send_header('Content-type', 'text/plain')
        self.send_header('Content-Length', 0)
        self.end_headers()
        self.wfile.write('')
        data = self.rfile.read(int(self.headers.getheader('content-length')))
        print (data)
        return
        
##----------------------------------------------
def run():
    httpd = HTTPServer(('', 8080), MyHandler)
    print "HTTP server running on port 8080"
    print "Your IP address is: ", socket.gethostbyname(socket.gethostname())
    httpd.serve_forever()
 
if __name__ == '__main__':
    run()
    
    
    
temp = int(data)
t=np.linspace(1,10,10)

#
def plot_temp():
    plt.plot(t,temp,'-o')
    plt.xlabel("Time")
    plt.ylabel("Temperature")
    
plt.figure(1)
plt.subplot(211)
plot_temp()