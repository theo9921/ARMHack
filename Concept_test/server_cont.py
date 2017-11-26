import urllib2
import time

while (True):
    f =  urllib2.urlopen('http://10.25.2.118:8080')
    print f.read()
    time.sleep(1)
