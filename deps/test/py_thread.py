''' Demonstrate the use of python threading'''

import time
import threading

def ThreadFunc():
	for i in range(15):
		print '...Printed from my thread.'
		time.sleep(1)

class MyThread(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
	def run(self):
		for i in range(15):
			print 'printed from MyThread...'
			time.sleep(1)

def createThread():
	print 'Create and run MyThread'
	background = MyThread()
	background.start()
	print  'Main thread continues to run in foreground.'
	for i in range(10):
		print 'printed from Main thread.'
		time.sleep(1)
	print  'Main thread joins MyThread and waits until it is done...'
	background.join() # Wait for the background task to finish
	print  'The program completed gracefully.'
	
	return 0