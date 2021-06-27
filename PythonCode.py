import re
import string

'''
 This function reads the file and puts the products in a dictionary
 with the products are the keys and the amount of times the key appears
 in the file are the values. 
'''
def printsomething():
    # Create dictionary
    items = {'Product': 'Amount'}

    # Open file
    x = open('ProjectThreeInput.txt', 'r')

    '''
    If the product is already in the dictionary, its respective value is
    increased by 1. If it is not, then a new key is added to the dict. 
    '''
    for item in x:
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1
        else:
            items.update({item:1})

    # Close dictionary
    x.close()

    # Prints the dictionary in an easy to read manner
    for key, value in items.items():
        print(key , value)

# Allows the user to search for a specific product value
def PrintMe(v):
    value = 0
    items = {}
    x = open('ProjectThreeInput.txt', 'r')

    for item in x:
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1
        else:
            items.update({item:1})

    x.close()

    print("You sent me: " + v)
    if v in items:
        value = items[v]
    else:
        value = 0;

    return value;
'''
First, this function will create the dictionary. Then it
will create a new file that holds the keys and values.
'''
def Histogram():
    items = {}
    x = open('ProjectThreeInput.txt', 'r')

    for item in x:
        item = item.replace('\n', '')
        if item in items:
            items[item] += 1
        else:
            items.update({item:1})

    x.close()

    with open("frequency.dat", 'w') as newFile:
        for key, value in items.items():
            newFile.write('%s:%s\n'%(key, value))

    newFile.close()
    


    
