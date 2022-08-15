import re
import string

#creating a dictionary with all the items and their frequency
itemFrequency = dict()

#Prints the items purchased and their frequency
def printTable():
    #Opening the file, using the entire path to my file because I was having issues without the entire path
    salesFile = open("C:/Users/hatch/Dropbox/SNHU/june 22/ComputerLanguages/Project3/IOFiles/inputFile.txt", "r")

    #Looping through the file and importing all the items into a dictionary
    for records in  salesFile:
        if records.rstrip("\n") in itemFrequency.keys():
            itemFrequency[records.rstrip("\n")] += 1
        else:
            itemFrequency[records.rstrip("\n")] = 1

    salesFile.close() #closing the file

    for key, value in itemFrequency.items():
        print("{}: {}" .format(key, value))

#Finds an item in the dictionary and returns the number of times it was purchaesd
def findItem(key):
    #Opening the file, using the entire path to my file because I was having issues without the entire path
    salesFile = open("C:/Users/hatch/Dropbox/SNHU/june 22/ComputerLanguages/Project3/IOFiles/inputFile.txt", "r")

    #Looping through the file and importing all the items into a dictionary
    for records in  salesFile:
        if records.rstrip("\n") in itemFrequency.keys():
            itemFrequency[records.rstrip("\n")] += 1
        else:
            itemFrequency[records.rstrip("\n")] = 1

    salesFile.close() #closing the file

    return itemFrequency[key.capitalize()] if key.capitalize() in itemFrequency.keys() else -1 #Returns the number of times that item was purchased if it exists, otherwise returns -1

#Exports the sorted data into a file
def exportData():
    #Opening the file, using the entire path to my file because I was having issues without the entire path
    salesFile = open("C:/Users/hatch/Dropbox/SNHU/june 22/ComputerLanguages/Project3/IOFiles/inputFile.txt", "r")

    #Looping through the file and importing all the items into a dictionary
    for records in  salesFile:
        if records.rstrip("\n") in itemFrequency.keys():
            itemFrequency[records.rstrip("\n")] += 1
        else:
            itemFrequency[records.rstrip("\n")] = 1

    salesFile.close() #closing the file

    #opening the file
    frequencyFile = open("C:/Users/hatch/Dropbox/SNHU/june 22/ComputerLanguages/Project3/IOFiles/frequency.dat", "w")
   
    #looping throught the dictionary and writing to file
    for key, value in itemFrequency.items():
        newValue = value * '*'
        frequencyFile.write(key + newValue + '\n')

    #closing the file
    frequencyFile.close()
