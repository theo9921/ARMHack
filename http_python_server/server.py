from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
import socket
 
class MyHandler(BaseHTTPRequestHandler):
 
    # HTTP REQUESTS HERE
 
 
 
def run():
    httpd = HTTPServer(('', 8080), MyHandler)
    print "HTTP server running on port 8080"
    print "Your IP address is: ", socket.gethostbyname(socket.gethostname())
    httpd.serve_forever()
 
if __name__ == '__main__':
    run()
 
