#! env python

import os, os.path, re
import datetime
import math

SFlag = True	# sort output
NFlag = False	# just list names

CutOffDate = datetime.datetime.now() - datetime.timedelta( days=2 )

def StripMicrosec( timestamp ): return timestamp .replace( microsecond=0 ) # http://stackoverflow.com/questions/7999935/python-datetime-to-string-without-microsecond-component
def TimestampFromFile( filename ): return datetime.datetime.fromtimestamp( os.path.getmtime( filename ))
def MidnightTonight(): return datetime.datetime.now().replace( hour=0, minute=0, second=0 )

def NumberFromSuffix( s ): 
	try: return int( s[ 2: ])
	except: return 0

class ListItem( object ):

	def __init__( self, filename ):
		self.Filename = filename
		self.Modtime =  StripMicrosec( TimestampFromFile( filename ) )

	def __cmp__( self, other ): return cmp( self.Modtime, other.Modtime )
	def __str__(self): return "%s %s" % (self.Modtime, self.Filename)

def Main( args ):
	global SFlag, NFlag, CutOffDate 

	Folders = []

	for arg in args:
		if arg.startswith("-"):
			if arg == "-n":	# just list files (for debugging)
				NFlag = True

			elif arg == "-s":		# turn off sorting
				SFlag = False

			# flags to set cutoff date

			elif arg == "-f":	# set cutoff date to match an existing file (or folder)
				filename = arg[ 2: ]
				CutOffDate = TimestampFromFile( filename )

			elif arg.startswith("-d"):	# set cutoff date to days before now
				# these days are 24 hours back from now
				count = min( NumberFromSuffix( arg ), 1 )
				CutOffDate = datetime.datetime.now() - datetime.timedelta( days=count )

			elif arg.startswith("-m"):	# set cutoff date to minutes before now
				count = math.min( NumberFromSuffix( arg ), 1 )
				CutOffDate = datetime.datetime.now() - datetime.timedelta( minutes=count )

			elif arg.startswith("-today"):		# set cutoff date to midnight localtime today
				CutOffDate = MidnightTonight()

			elif arg.startswith("-yesterday"):	# set cutoff date to midnight localtime yesterday
				CutOffDate = MidnightTonight() - datetime.timedelta( days=1 )
			
			elif arg.endswith("days"):			# set cutoff date to midnight localtime one or more days back
				count = 0
				try: 
				    count = int( arg[ 1 : -4 ])
				except: 
					print "Don't understand arg:", arg
					return

				CutOffDate = MidnightTonight() - datetime.timedelta( days=count )
			
			else:
				print "Bad command line switch:", arg
		else:
			Folders.append( arg );

	if not Folders:
		Folders = ["."]

	for folder in Folders:
		Search( folder )

def Search( root ):
	Items = []

	for folder, subs, filenames in os.walk( root ):
		for basename in filenames:
			filename = os.path.join( folder, basename )

			if NFlag:
				print filename
				continue

			item = ListItem( filename )

			if CutOffDate and item.Modtime < CutOffDate:
				continue # exclude this item

			Items.append( item )
			if not SFlag:
				print item

	if SFlag and not NFlag:
		Items.sort( reverse=True )
		for item in Items:
			print item


if __name__ == "__main__":
	import sys

	Main( sys.argv[ 1: ])