import urllib2
from lxml import html

req = urllib2.Request('https://www.google.com/search?q=patata', headers={ 'User-Agent': 'Mozilla/5.0' })
print urllib2.urlopen(req).read()
