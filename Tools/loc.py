#! env python

import os, os.path, re
import datetime
import math

Extensions = [".cs", ".xaml"]

def ValidExtension( filename ):
	base, ext = os.path.splitext( filename )
	return ext in Extensions

SFlag = False	# sort output [unimplemented]
NFlag = False	# just list names
VFlag = False	# list all filenames, not just summaries

def CountLines( filename ):
	count = 0
	for line in file( filename ):
		count += 1
	return count

class ListItem( object ):
	def __init__( self, filename ):
		self.Filename = filename
		self.Basename, self.Extension = os.path.splitext( filename )
		self.Loc = CountLines( filename )
	# def __cmp__( self, other ): return cmp( self.Modtime, other.Modtime )
	def __str__(self): return "%s %d" % (self.Basename, self.Loc)

def Main( args ):
	global SFlag, NFlag, VFlag

	Folders = []

	for arg in args:
		if arg.startswith("-"):
			if arg == "-n":	# just list files (for debugging)
				NFlag = True

			elif arg == "-s":		# turn off sorting
				SFlag = True

			elif arg == "-v":		# verbose
				VFlag = True

			else:
				print "Bad command line switch:", arg

		else:
			Folders.append( arg );

	if not Folders:
		Folders = [ "PhoenixConnection", "PhoenixControlLibrary", "PhoenixLibrary", "SharedLibrary" ]
		# curdir = os.path.curdir()
		# Folders = [ os.path.join( curdir, folder ) for folder in folders ]

	for folder in Folders:
		items = Search( folder )
		print folder, items
		for item in items:
			print item
			# print item.value(), item.key()


def Search( root ):
	Items = {}
	for extension in Extensions: Items[ extension ] = 0

	for folder, subs, filenames in os.walk( root ):
		for basename in filenames:
			pathname = os.path.join( folder, basename )

			if ValidExtension( basename ):
				if NFlag or VFlag:
					print pathname
				if NFlag:
					continue

				item = ListItem( pathname )
				if VFlag:
					print item
				Items[ item.Extension ] += item.Loc

	return Items


if __name__ == "__main__":
	import sys

	Main( sys.argv[ 1: ])