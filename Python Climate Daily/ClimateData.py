class ClimateData:
    def __init__(self, date, maxGust, precip, minTemp, maxTemp, meanTemp):
        self.date = date
        self.maxGust = maxGust
        self.precip = precip
        self.minTemp = minTemp
        self.maxTemp = maxTemp
        self.meanTemp = meanTemp

class ClimateDataValues:
    def __init__(self):
        self._values = []

    def add(self, data): # Function to add data to list
        self._values.append(data)
        return data 
    
    def findMonthPrecip(self, month): # Helper function to find the total precipitation of an entire month, inputs a string in the form YYYY/MM. Used for finding month with highest precipitation

        precipitation = 0
        for i in self._values:
            if month in i.date:
                precipitation += i.precip
        return precipitation
    
    def printAverageMonthPrecip(self): # Function to print the average precipitation of each month

        print("Date\tAvg Precipitation")
        print("-----------------")
        precipitation = 0
        count = 0
        line = self._values[0].date.split("-")
        month = line[0] + "-" + line[1]
        currentMonth = month
        for i in self._values:
            line = i.date.split("-")
            month = line[0] + "-" + line[1]
            if month == currentMonth:
                precipitation += i.precip
                count += 1
            else:
                precipitation = round(precipitation/count, 2)
                print(f"{currentMonth}\t{precipitation}")
                precipitation = 0
                count = 0
            currentMonth = month

    def printAverageMonthSpeed(self): # Function to print the average max gust speed of each month

        print("Date\tAvg Max Gust Speed")
        print("-----------------")
        speed = 0
        count = 0
        line = self._values[0].date.split("-")
        month = line[0] + "-" + line[1]
        currentMonth = month
        for i in self._values:
            line = i.date.split("-")
            month = line[0] + "-" + line[1]
            if month == currentMonth:
                speed += i.maxGust
                count += 1
            else:
                speed = speed/count
                print(f"{currentMonth}\t{speed:.2f}")
                speed = 0
                count = 0
            currentMonth = month
    
    def printMonthMinTemp(self): # Function to print the minimum temperature of each month

        print("Date\tMin Temp")
        print("-----------------")
        minTemp = self._values[0].minTemp
        line = self._values[0].date.split("-")
        month = line[0] + "-" + line[1]
        currentMonth = month
        for i in self._values:
            line = i.date.split("-")
            month = line[0] + "-" + line[1]
            if month == currentMonth:
                if (minTemp > i.minTemp):
                    minTemp = i.minTemp
            else:
                print(f"{currentMonth}\t{minTemp}")
                minTemp = i.minTemp
            currentMonth = month
    
    def printMonthMaxTemp(self): # Function to print the maximum temperature of each month

        print("Date\tMax Temp")
        print("-----------------")
        maxTemp = self._values[0].maxTemp
        line = self._values[0].date.split("-")
        month = line[0] + "-" + line[1]
        currentMonth = month
        for i in self._values:
            line = i.date.split("-")
            month = line[0] + "-" + line[1]
            if month == currentMonth:
                if (maxTemp == None or maxTemp < i.maxTemp):
                    maxTemp = i.maxTemp
            else:
                print(f"{currentMonth}\t{maxTemp}")
                maxTemp = i.maxTemp
            currentMonth = month
    
    def printAverageMonthMeanTemp(self): # Function to print the average mean temperature of each month

        print("Date\tAvg Mean Temp")
        print("-----------------")
        meanTemp = 0
        count = 0
        line = self._values[0].date.split("-")
        month = line[0] + "-" + line[1]
        currentMonth = month
        for i in self._values:
            line = i.date.split("-")
            month = line[0] + "-" + line[1]
            if month == currentMonth:
                meanTemp += i.meanTemp
                count += 1
            else:
                meanTemp = round(meanTemp/count, 1)
                print(f"{currentMonth}\t{meanTemp}")
                meanTemp = 0
                count = 0
            currentMonth = month
    
    def displayDataRange(self, start, end): # Display all weather records from a given start and end date
        print("Date\t\tMax Gust Speed\tPrecipitation\t\tMin Temp\tMax Temp\tMean Temp")
        print("------------------------------------------------------------------------------------------------")
        begin = False
        i = 0
        while begin == False and i < len(self._values):
            line = self._values[i].date.split(" ")
            if line[0] >= start:
                begin = True
                group = self._values[i]
                print(f"{group.date}\t\t{group.maxGust}\t\t{group.precip}\t\t{group.minTemp}\t\t{group.maxTemp}\t\t{group.meanTemp}")
            i += 1
        line = self._values[i].date.split(" ")
        if line[0] >= end:
            begin = False
        while begin == True and i < len(self._values):
            group = self._values[i]
            print(f"{group.date}\t\t{group.maxGust}\t\t{group.precip}\t\t{group.minTemp}\t\t{group.maxTemp}\t\t{group.meanTemp}")
            line = self._values[i].date.split(" ")
            if line[0] >= end:
                begin = False
            i += 1
        return

    def findHighestPrecip(self): # Function used to find the highest precipitation of a single month from data, returns precipitation level (rounded to one decimal) as well as the month

        line = self._values[0].date.split("-")
        currentMonth = line[0] + "-" + line[1]
        highestMonth = currentMonth
        highestPrecip = self._values[0].precip
        newPrecip = self._values[0].precip

        i = 1
        while i < len(self._values):
            line = self._values[i].date.split("-")
            currentMonth = line[0] + "-" + line[1]
            newPrecip = self.findMonthPrecip(currentMonth)
            if newPrecip > highestPrecip:
                highestPrecip = newPrecip
                highestMonth = currentMonth
            i += 1
            while (line[0] + "-" + line[1]) == currentMonth and i < len(self._values):
                line = self._values[i].date.split("-")
                i += 1
        return round(highestPrecip,1), highestMonth
    
    def findHighestSpeed(self): # Function to find the day with the highest max gust speed, returns speed and local date

        highestSpeed = self._values[0].maxGust
        localDate = self._values[0].date
        for i in self._values: 
            if i.maxGust > highestSpeed:
                highestSpeed = i.maxGust
                localDate = i.date
        line = localDate.split(" ")
        localDate = line[0]
        return highestSpeed, localDate
    
    def findLargestFluctuation(self): # Function to find the day with the highest fluctuating temperature based on max and min temp, returns fluctuation and local date

        largestFluc = self._values[0].maxTemp - self._values[0].minTemp
        localDate = self._values[0].date
        for i in self._values:
            if (i.maxTemp - i.minTemp) > largestFluc:
                largestFluc = i.maxTemp - i.minTemp
                localDate = i.date
        line = localDate.split(" ")
        localDate = line[0]
        return round(largestFluc,1), localDate

    def displayMonthData(self, month): # Function used for testing
        for i in self._values:
            if month in i.date:
                print(f"{i.date}, {i.maxGust}, {i.precip}, {i.minTemp}, {i.maxTemp}, {i.meanTemp}")
        return