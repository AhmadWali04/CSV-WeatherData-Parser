import csv # https://earthly.dev/blog/csv-python/
from ClimateData import ClimateData
from ClimateData import ClimateDataValues
import time

climateList = ClimateDataValues()
with open('climate-daily.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)

    for row in csvreader:
        if "" in row: 
            pass # Choosing to skip data that has missing values
        elif row[1].isnumeric() == False:
            pass
        else:
            data = ClimateData(row[0], int(row[1]), float(row[2]), float(row[3]), float(row[4]), float(row[5]))
            climateList.add(data)

print()

highestPrecip, highestMonth = climateList.findHighestPrecip() # Initial calls to functions to satisfy Task 3
print(f"The highest total precipitation of a month was {highestPrecip} and occurred in the month of {highestMonth}")

highestSpeed, localDate = climateList.findHighestSpeed()
print(f"The highest max gust speed was {highestSpeed} and occurred on {localDate}")

highestFluc, localDate = climateList.findLargestFluctuation()
print(f"The largest temperature fluctuation was {highestFluc} and occurred on {localDate}")

print("""
      1. Average Month Max Gust Speed
      2. Average Month Precipitation
      3. Month Minimum Temperature
      4. Month Maximum Temperature
      5. Average Month Mean Temperature
      6. All Weather Records Between A Chosen Start and End Date
      0. End Program
      """) # Creating GUI for task 4
choice = int(input("Please enter a number to select the type of report generated: "))
while choice != 0: # Code block to satisfy task 4
    match choice: # Switch statement that continues until 0 is chosen
        case 1:
            start_time = time.time()
            climateList.printAverageMonthSpeed()
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case 2:
            start_time = time.time()
            climateList.printAverageMonthPrecip()
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case 3:
            start_time = time.time()
            climateList.printMonthMinTemp()
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case 4:
            start_time = time.time()
            climateList.printMonthMaxTemp()
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case 5:
            start_time = time.time()
            climateList.printAverageMonthMeanTemp()
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case 6:
            isValid = True # Validity checks to ensure valid start and end date
            start = input("Please enter the start date in the form YYYY-MM-DD: ")
            end = input("Please enter the end date in the form YYYY-MM-DD: ")
            if end < start: # Check if start date is later than end date
                isValid = False
                print("Invalid inputs, start date cannot be later than end date")
            first = climateList._values[0].date.split(" ")
            if start < first[0]: # Check if start date is outside of range
                print("Invalid start date, outside of range")
                isValid = False
            last = climateList._values[-1].date.split(" ")
            if end > last[0]: # Check if end date is outside of range
                print("Invalid end date, outside of range")
                isValid = False
            while isValid == False:
                isValid = True
                start = input("Please enter the start date in the form YYYY-MM-DD: ")
                end = input("Please enter the end date in the form YYYY-MM-DD: ")
                if end < start:
                    isValid = False
                    print("Invalid inputs, start date cannot be later than end date")
                first = climateList._values[0].date.split(" ")
                if start < first[0]:
                    print("Invalid start date, outside of range")
                    isValid = False
                last = climateList._values[-1].date.split(" ")
                if end > last[0]:
                    print("Invalid end date, outside of range")
                    isValid = False
            start_time = time.time()
            climateList.displayDataRange(start, end)
            print("Process finished --- %s seconds ---" %(time.time() - start_time))
        case default:
            print("That is not a valid choice")
    print("""
      1. Average Month Max Gust Speed
      2. Average Month Precipitation
      3. Month Minimum Temperature
      4. Month Maximum Temperature
      5. Average Month Mean Temperature
      6. All Weather Records Between A Chosen Start and End Date
      0. End Program
      """)
    choice = int(input("Please enter another number to display a new report or enter 0 to end the program: "))
