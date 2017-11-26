from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
import socket

data = ' '

class MyHandler(BaseHTTPRequestHandler):


    def do_POST(self):
        print("input request received")
        self.send_header('Content-type', 'text/plain')
        self.send_header('Content-Length', 0)
        self.end_headers()
        self.wfile.write('')
        global data 
        data = str(self.rfile.read(int(self.headers.getheader('content-length'))))
        print (data)
        return
        
    
    def do_GET(self):
        print("retrival request received")
        global data
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.send_header('Content-Length', len(data))
        self.end_headers()
        self.wfile.write(data)
        return
        
##----------------------------------------------
def run():
    httpd = HTTPServer(('10.25.2.118', 8080), MyHandler)
    print "HTTP server running on port 8080"
    print "Your IP address is: ", socket.gethostbyname(socket.gethostname())
    httpd.serve_forever()
 
if __name__ == '__main__':
    run()
