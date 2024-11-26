//Unit Test Module Four Milestone
//Steven Anderson

// Uncomment the next line to use precompiled headers
#include "pch.h"

//needed for file uploading, math, and other function in the tests
#include <fstream>
#include <functional>
#include <iostream>
#include <cmath>

using namespace std;

//class for testing squared and cubed test
// needed to pass int parameter to tests
class TestParam :public ::testing::TestWithParam<int> {
};

//class for testing other math equations to pass int parameter
class MathTest :public ::testing::TestWithParam<int> {
};

// class environment for testing 
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    //populate with entries
    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    //populate with entries
    add_entries(5);

    //check to make sure the collection isn't empty
    ASSERT_FALSE(collection->empty());

    //check to make sure the collection size is equal to 5
    ASSERT_EQ(collection->size(), 5);
}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxIsGreaterOrEqualToSize) {
    //populate with entries
    add_entries(11);

    //check to make sure the size is greater than 0
    ASSERT_TRUE(collection->max_size() >= 0);
    //check to make sure the size is greater than 1
    ASSERT_TRUE(collection->max_size() >= 1);
    //check to make sure the size is greater than 5
    ASSERT_TRUE(collection->max_size() >= 5);
    //check to make sure the size is greater than 10
    ASSERT_TRUE(collection->max_size() >= 10);
}
//  Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterOrEqualToSize) {
    //populate with entries
    add_entries(11);

    //check to make sure the capacity is greater than 0
    ASSERT_TRUE(collection->capacity() >= 0);
    //check to make sure the capacity is greater than 1
    ASSERT_TRUE(collection->capacity() >= 1);
    //check to make sure the capacity is greater than 5
    ASSERT_TRUE(collection->capacity() >= 5);
    //check to make sure the capacity is greater than 10
    ASSERT_TRUE(collection->capacity() >= 10);
}
//  Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection) {
    //populate with entries
    add_entries(1);

    //create previousSize to save current size of collection
    size_t previousSize = collection->size();

    //use resize to change the size of collection to 15
    collection->resize(15);

    //check to make sure that collection is now greater than it was before resize
    ASSERT_TRUE(collection->size() > previousSize);
}
//  Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection) {
    //populate with entries
    add_entries(15);

    //use previousSize to save the current size of collection
    size_t previousSize = collection->size();

    //use resize to change the size of collection to 1
    collection->resize(1);

    //check to make sure that collection is now less than it was before resize
    ASSERT_TRUE(collection->size() < previousSize);
}
//  Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingCollectionToZero) {
    //populate with entries
    add_entries(15);

    //use previousSize to save the current size of collection
    size_t previousSize = collection->size();
    collection->resize(0);
    ASSERT_TRUE(collection->size() == 0);
}
//  Create a test to verify clear erases the collection
TEST_F(CollectionTest, VerifyClearErasesCollection) {
    //populate with entries
    add_entries(15);

    //use clear to clear the collection
    collection->clear();

    //check to make sure that the collection is now empty and size is now 0
    ASSERT_TRUE(collection->size() == 0);
}
//  Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VerifyEraseBeginEndErasesCollection) {
    //populate with entries
    add_entries(15);

    //use erase to erase all entries between the begin and end of collection
    collection->erase(collection->begin(), collection->end());

    //check to make sure that the collection is now empty and size is now 0
    ASSERT_TRUE(collection->size() == 0);
}
//  Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize) {
    //populate with entries
    add_entries(15);
    
    //use previousCapacity to save the current capacity of collection
    size_t previousCapacity = collection->capacity();
    
    //use previousSize to save the current size of collection
    size_t previousSize = collection->size();

    //use reserve to change the capacity of collection to 20
    collection->reserve(20);

    //check to make sure that the size hasn't changed after using reserve
    ASSERT_TRUE(collection->size() == previousSize);

    //check to make sure the capacity has increased after using reserve to reserve 20
    ASSERT_TRUE(collection->capacity() > previousCapacity);
}
//  Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
//  This is a negative test
TEST_F(CollectionTest, VeriftyIndexOutOfRangeException) {
    //populate with entries
    add_entries(5);

    //check to make sure an exception is thrown when trying to access collection outside
    //it's current range
    EXPECT_THROW(collection->at(15), std::out_of_range);
}

//Test to  verify multplication of the size with resize
//positive test
TEST_F(CollectionTest, VeriftyMultiplicationWithResize) {
    //populate with entries
    add_entries(15);
    
    //use previousSize to save the current size of collection
    size_t previousSize = collection->size();
    //resize collection multiplying the current size by 4
    collection->resize(previousSize * 4);
    //check to ensure new size is 60 the product of 15 and 4
    ASSERT_TRUE(collection->size() == 60);
}

//Test to verify that you can't reseve past the max size of collection
//negative test
TEST_F(CollectionTest, VerifyLengthErrorException) {
    //populate with entries
    add_entries(15);

    //check to make sure a length_error exception is thrown when trying to reserve one place past 
    // the max_size of collection
    ASSERT_THROW(collection->reserve(collection->max_size() + 1), std::length_error);
}

//Extra test to try using ASSERT_FALSE
//
//negative test
TEST_F(CollectionTest, EnsureAddingToPreviousSizeIsNotCumulative) {
    //populate with entries
    add_entries(15);

    //use previousSize to save the current size of collection
    size_t previousSize = collection->size();

    //use resize with previoussize to add 10
    collection->resize(previousSize + 10);
    //use resize with previoussize to add 10
    collection->resize(previousSize + 10);

    //code will only apply one of the resizes since it was adding to the saved 
    // previousSize size instead of to collection
    //check to ensure the size isn't both resizes combined
    ASSERT_FALSE(collection->size() == 35);
}

//Hash data Test
static TEST(HashTest) {
    //saving key string
    string key = "Test data";
    // copying the key for testing
    string previousKey = key;

    //create the hasher using std::hash
    hash<string> hasher;

    // hash the key using the hasher and assign to hashValue
    size_t hashValue = hasher(key);

    //print the hash value
    cout << "Hash Value: " << hashValue << endl << endl;

    //overwrite key with the hashValue
    key = hashValue;

    //assert that the key isn't the same as the original string
    ASSERT_FALSE(key == previousKey);
}

//file test
static TEST(FileLoadingTest) {
    // opening the file
    ifstream file("Info.txt", ios::in);

    //vector to store information from the file
    vector<string> fileLines;

    // while the file is open if else
    if (file.is_open()) {
        //variable to store line
        string line;
        //while loop until it runs out of lines in the file
        while (std::getline(file, line)) {
            //load line into vector
            fileLines.push_back(line);
        }
        // ASSERT TRUE test to ensure file line was read correctly
        ASSERT_TRUE(fileLines[2] == "Test line 3");
        //close file
        file.close();
    }
    // else if the file fails to load
    else {
        //error message
        cerr << "Error opening file" << endl;
    }

    //test to ensure the file is closed
    ASSERT_FALSE(file.is_open());
}

//Quadratic equation test
TEST(QuadTest) {
    //variables in the equation (coefficients)
    double a, b, c;

    //assign value
    a = 1;
    b = 8;
    c = 12;
    //a quadratic with these variables should equal x = (-2), (-6)

    //results for quadratic
    double result1, result2;

    //run quadratic equation for both positive and negative
    result1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    result2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

    //Assert true test to ensure final results are the right answer
    ASSERT_TRUE(result1 == -2 && result2 == -6);
}

//test for trigonmetric equation
TEST(TrigonometricTest) {
    //varaibles for test
    double result, degrees;

    //get result of sin(x) = 0.5 in radians
    result = asin(0.5);

    //get degrees rounded up
    degrees = round(result * 180 / 3.1415);

    //expect equal expecting degrees to equal 30 degrees
    EXPECT_EQ(degrees, 30);
}

//parameter test for squared numbers
TEST_P(TestParam, EquationTestSquared) {
    //get parameter number
    int number = GetParam();

    //create result multiplying number by itself
    int result = number * number;

    //print original number and result
    cout << "Number: " << number << endl << "Result: " << result << endl;
    
    //expect equal for result and number to the power of 2
    EXPECT_EQ(result, pow(number, 2));
}

//parameter test for cubed numbers
TEST_P(TestParam, EquationTestCubed) {
    //get parameter number
    int number = GetParam();

    //create result multiplying number by itself twice
    int result = number * number * number;

    //print original number and result
    cout << "Number: " << number << endl << "Result: " << result << endl;
    
    //expect equal for result and number to power of 3
    EXPECT_EQ(result, pow(number, 3));
}

//parameter test for true test
TEST_P(MathTest, EquationTestTrue) {
    //get parameter number
    int number = GetParam();

    //create result of number * 5
    int result = number * 5;

    //Assert True for result of number times 5, True test
    ASSERT_TRUE(result == number * 5);
}

//parameter test for false test
TEST_P(MathTest, EquationTestFalse) {
    //get parameter number
    int number = GetParam();

    //ASSERT False test for number without changing it
    ASSERT_FALSE(number == number * 5);
}

//Initialize the parameter tests for TestParam
INSTANTIATE_TEST_CASE_P(ParameterTests, TestParam, ::testing::Values(1, 2, 3, 4));

//initialize the parameter tests for MathTest
INSTANTIATE_TEST_CASE_P(MathEquationTests, MathTest, ::testing::Values(1, 2));
