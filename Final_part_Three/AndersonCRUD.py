from pymongo import MongoClient
from bson.objectid import ObjectId

import json

# create class animal shelter to allow use of CRUD file
class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):

        # Connection Variables
        #
        #USER = 'aacuser'
        #PASS = 'Animal123'
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30035
        DB = 'AAC'
        COL = 'animals'
        #
        # Initialize Connection
        #
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (username,password,HOST,PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
        
        print("Connected test")

# Complete this create method to implement the C in CRUD.
    def create(self, createData):
        #if create data is not empty
        if createData is not None:
            #cursor is the result of using the animals database with insert and create data
            cursor = self.database.animals.insert(createData)  # data should be dictionary 
            #if cursor is not empty status is true
            if cursor is not None:
                status = True
            #else status is false
            else:
                status = False
            # return the status
            return status
        # else raise exception
        else:
            raise Exception("Nothing to save, because data parameter is empty")

# Create method to implement the R in CRUD.
    def read(self, readData):
        # create cursor
        cursor = []
        # if read data value is not empty
        if readData is not None:
            # search through the database for the readData entry and assign to cursor
            cursor = self.database.animals.find(readData)
            # return cursor
            return cursor
        # else if user inputs no criteria        
        else:
            raise Exception("Enter a criteria to search")
        
# method implementaion of the U in CRUD
    def update(self, searchData, updateData):
        # if the search data is not empty
        if searchData:
            # result is the results of using the update many command with search and update data on the database animals
            result = self.database.animals.update_many(searchData, {"$set": updateData})
            # result update is the modified count number using result
            resultUpdate = ("Docs updated: " + json.dumps(result.modified_count))        
            # return the result update
            return resultUpdate
        # else raise exception
        else:
            raise Exception("No Record Found")
        print("Data Updated")

# method implementaion of the D in CRUD
    def delete(self, deleteData):
        # if the delete data is not empty
        if deleteData is not None:
            # result is the result of using delete many on the animals database with the parameter of delete data
            result = self.database.animals.delete_many(deleteData)
            # result delete is the deleted count using result
            resultDelete = "Docs deleted: " + json.dumps(result.deleted_count)
            # if no data was deleted print error
            if resultDelete == 0:
                print("Error, didn't find document")
            return resultDelete
        # else raise exception
        else:
            raise Exception("Nothing to Delete")
        print("Data Deleted")

# method implementaion for deleting one entry
    def deleteOne(self, deleteOneData):
        # if the delete one data is not empty
        if deleteOneData is not None:
            # result is the delete one result using the animals database and delte one data
            result = self.database.animals.delete_one(deleteOneData)
            # resultDelete is the raw results of the deleted data
            resultDelete = "Document deleted: " + json.dump(result.raw_results)
            resultDeleteNumber = json.dump(result.deleted_count)
            #if no data was deleted print error message
            if resultDeleteNumber == 0:
                print("Error, no file found")
            # return the resultDelete
            return resultDelete
        # else raise exception
        else:
            raise Exception("No Entry Found to Delete")
        print ("Data Deleted")

# method implementation for updating one entries
# uses self and takes in search and update data from user
    def updateOne (self, searchData, updateData):
        # if the search data is not empty
        if searchData is not None:
            # result is the update many result using the animal database and the search and update data
            result = self.database.animals.update_one(searchData, {"$set": updateData})
            # return the raw results
            return json.dumps(result.raw_results)
        # else raise exception
        else:
            raise Exception("Update Failed: Check Parameters")

# method implementation for creating multiple entries
    def createMany(self, createManyData):
        if createManyData is not None:
            return self.collection.insert_many(createManyData)
        # else raise exception
        else:
            raise Exception("Creation Failed: Check Parameters")

# method implementation for replacing an entry
# uses self and takes in data for searching and replacing
    def replace(self, searchData, replaceData): 
        # if the searchData is not empty
        if searchData is not None:
            # replaces one entry if found in the animals database using replace_one
            result = self.database.animals.replace_one(searchData, replaceData)
            # return the raw results 
            return json.dumps(result.raw_results)
        # else raise exception
        else:
            raise Exception("Failed to Replace Data")

