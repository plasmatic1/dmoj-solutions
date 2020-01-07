import re
for i in xrange(5):
    print '%d' % sum(map(lambda w: len(w) > 3, re.split('[ \']', re.sub('[^a-z\' ]', '', raw_input()))))