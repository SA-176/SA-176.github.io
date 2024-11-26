#----------------------------------------------
# Final Project CS 499 Part One
# CS-300 project in python
# Steven Anderson
#----------------------------------------------

#import to work with .csv files
import csv

#class course used to define what a instance of course includes
class Course:
    def __init__(self, course_number, course_name, pre_req=None):
        self.course_number = course_number
        self.course_name = course_name
        # only assigns pre_req if there are values to assign it with
        self.pre_req = pre_req if pre_req is not None else []

# load from file function
def loadFile():

    # variables
    courses = []
    count = 0

    # Using a with statement that will close the file after completion
    # opening the file and assigning it as file
    with open("info.csv", "r") as file: # can switch this line to info.txt to read from as well
        # for each line in the file assign token info with the split part
        for line in file:
            token_info = line.strip().split(",") #defines where to split the file information
            # if statment to assign the various parts of course
            if len(token_info) > 1:
                # load information for number and name of course
                course = Course(course_number=token_info[0], course_name=token_info[1])
                # load information for re requisites
                course.pre_req.extend(token_info[2:]) #[2:] used to slice string to start at index 2
                # add the course to courses
                courses.append(course)
                # increment
                count += 1

    # print statement to print how many courses were loaded
    print(f"Loaded {count} Courses\n")
    # courses is returned
    return courses

def printCourseList(courses):
    # sorting the courses according to the course number
    courses.sort(key=lambda course: course.course_number)

    # printing the list of all courses
    for course in courses:
        print(f"{course.course_number}, {course.course_name}") # print course number and name

def searchCourse(courses, course_number):
    # variable used for if program doesn't find course
    found = False

    # searching and showing details of the course if found
    print("\nCourse Details: \n")
    for course in courses:
        if course.course_number.lower() == course_number.lower():
            # then printing its details
            found = True
            printCourse(course)
            break #break once course is found

    # message printed if course isn't found in list
    if not found:
        print(f"Sorry, course with number: {course_number} was not found\n")

def printCourse(course):
    # variables for number, name and prerequisites
    course_number = course.course_number
    course_name = course.course_name
    prerequisites = course.pre_req

    # print statement for course number, name, then prerequisites
    print(f"{course_number}, {course_name}")
    print("Prerequisites:", " ".join(prerequisites))
    print()

# main function
def main():

    # store all courses in vector array
    courses = []

    # variables for user's choice and string for choice
    choice = 0
    course_number = ""

    # opening message
    print("Course Planner")
    print("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>")

    while choice != 9:
        # showing menu to the users each loop of while
        print("\n1.Load From File")
        print("2.Print Course List")
        print("3.Print Course Information")
        print("9.Exit\n")

        # taking in the user input
        choice = int(input("Enter Choice: "))
        print()

        # interpreting user choice
        if choice == 1:
            # assigns courses with the results of file loaded
            courses = loadFile()
        elif choice == 2:
            # call to print all the lists
            printCourseList(courses)
        elif choice == 3:
            # message and input for user search
            course_number = input("Enter Course Number: ")

            # call search course to find user inputted course number
            searchCourse(courses, course_number)
        elif choice == 9:
            # exit message
            print("Goodbye!")
            print("===============================================================")
        else:
            # default used to catch problems
            print(f"{choice} is not a valid choice\n")

# runs file as a script
if __name__ == "__main__":
    main()