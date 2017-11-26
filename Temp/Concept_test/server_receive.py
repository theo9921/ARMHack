#----------Server receive-------
import urllib2

f =  urllib2.urlopen('http://10.25.2.118:8080')
print f.read()
