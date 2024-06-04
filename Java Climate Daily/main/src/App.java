import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        long startTime;
        long endTime;
        ArrayList<ClimateRecord> records = new ArrayList<>();
        Scanner sc = new Scanner(new File("climate-daily.csv"));
        int x = 5;
        sc.useDelimiter(",");
        sc.nextLine();
        while (sc.hasNextLine()) {
            boolean isValid = true;
            String[] line = sc.nextLine().split(",");
            if (line.length == 6) { 
                for (String i : line) {
                    if (i.compareTo("") == 0) { // If even one of the values in the properties is empty then it is ignored
                        isValid = false;
                    }
                }
            }
            else { // If the line has less than 6 entries then that means it does not have values in all of its properties so it is ignored
                isValid = false;
            } 
            if (isValid == true){ // Check to make sure that the data has passed the checks to ensure a value in all of its properties 
                ClimateRecord record = new ClimateRecord(line[0], Integer.parseInt(line[1]), Float.parseFloat(line[2]), Float.parseFloat(line[3]), Float.parseFloat(line[4]), Float.parseFloat(line[5]));
                records.add(record);
            }
        }
        sc.close();
        Helper.findHighestPrecip(records); // Initial calls to satisfy conditions of task 3
        Helper.findHighestSpeed(records);
        Helper.findHighestFluc(records);
        System.out.println();
        System.out.println("      1. Average Month Max Gust Speed"); // Creating GUI format for task 4
        System.out.println("      2. Average Month Precipitation");
        System.out.println("      3. Month Minimum Temperature");
        System.out.println("      4. Month Maximum Temperature");
        System.out.println("      5. Average Month Mean Temperature");
        System.out.println("      6. All Weather Records Between A Chosen Start and End Date");
        System.out.println("      0. End Program");
        System.out.println();

        Scanner input = new Scanner(System.in);
        System.out.print("Please enter a number to select the type of report generated: ");
        String choice = input.nextLine();
        while (choice.compareTo("0") != 0) {
            switch(choice){ // Switch block to continue until 0 is chosen
                case "1":
                    startTime = System.currentTimeMillis();
                    Helper.printAverageMonthSpeed(records);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break; 
                case "2":
                    startTime = System.currentTimeMillis();
                    Helper.printAverageMonthPrecip(records);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break;
                case "3":
                    startTime = System.currentTimeMillis();
                    Helper.printMonthMinTemp(records);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break;
                case "4":
                    startTime = System.currentTimeMillis();
                    Helper.printMonthMaxTemp(records);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break;
                case "5":
                    startTime = System.currentTimeMillis();
                    Helper.printAverageMeanTemp(records);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break;
                case "6":
                    boolean isValid = true; // Validity checks to ensure valid start and end date
                    System.out.print("Please enter the start date in the form YYYY-MM-DD: ");
                    String start = input.nextLine();
                    System.out.print("Please enter the end date in the form YYYY-MM-DD: ");
                    String end = input.nextLine();
                    if (start.compareTo(end) > 0){ /// Check if start date is later than end date
                        isValid = false;
                        System.out.println("Invalid inputs, start date cannot be later than end date");
                    }
                    String[] first = records.get(0).getDate().split(" ");
                    if (first[0].compareTo(start) > 0) {  // Check if start date is outside of range
                        isValid = false;
                        System.out.println("Invalid start date, outside of range");
                    }
                    String[] last = records.get(records.size()-1).getDate().split(" ");
                    if (end.compareTo(last[0]) > 0) { // Check if end date is outside of range
                        isValid = false;
                        System.out.println("Invalid end date, outside of range");
                    }
                    while (isValid == false) {
                        isValid = true;
                        System.out.print("Please enter the start date in the form YYYY-MM-DD: ");
                        start = input.nextLine();
                        System.out.print("Please enter the end date in the form YYYY-MM-DD: ");
                        end = input.nextLine();
                        if (start.compareTo(end) > 0){
                            isValid = false;
                            System.out.println("Invalid inputs, start date cannot be later than end date");
                        }
                        first = records.get(0).getDate().split(" ");
                        if (first[0].compareTo(start) > 0) { 
                            isValid = false;
                            System.out.println("Invalid start date, outside of range");
                        }
                        last = records.get(records.size()-1).getDate().split(" ");
                        if (end.compareTo(last[0]) > 0) {
                            isValid = false;
                            System.out.println("Invalid end date, outside of range");
                        }
                    }
                    startTime = System.currentTimeMillis();
                    Helper.displayDataRange(records, start, end);
                    endTime = System.currentTimeMillis();
                    System.out.println("Total execution time (seconds): " + (float)(endTime - startTime)/1000);
                    break;
                default:
                    System.out.println("That is not a valid choice");
            }
            System.out.println();
            System.out.println("      1. Average Month Max Gust Speed");
            System.out.println("      2. Average Month Precipitation");
            System.out.println("      3. Month Minimum Temperature");
            System.out.println("      4. Month Maximum Temperature");
            System.out.println("      5. Average Month Mean Temperature");
            System.out.println("      6. All Weather Records Between A Chosen Start and End Date");
            System.out.println("      0. End Program");
            System.out.println();
    
            System.out.print("Please enter a number to select the type of report generated: ");
            choice = input.nextLine();
        }
        input.close();
    }
}

// Helper class to organize functions used by the program 
class Helper {
    public static void findHighestPrecip(ArrayList<ClimateRecord> records) { // Searches for month with highest precipitation and prints the answer
        String[] line = records.get(0).getDate().split("-");
        String currentMonth = line[0] + "-" + line[1];
        String highestMonth = currentMonth;
        float highestPrecip = records.get(0).getPrecip();
        float newPrecip = highestPrecip; 

        int i = 1;
        line = records.get(i).getDate().split("-");
        while (i < records.size()){
            currentMonth = line[0] + "-" + line[1];
            while ((currentMonth.compareTo((line[0] + "-" + line[1])) == 0) && i < records.size()-1){
                newPrecip += records.get(i).getPrecip();
                i += 1;
                line = records.get(i).getDate().split("-");
            }
            if (newPrecip > highestPrecip) {
                highestPrecip = newPrecip;
                highestMonth = currentMonth;
            }
            newPrecip = records.get(i).getPrecip();
            i += 1;
        }
        System.out.println("The highest total precipitation of a month was " + String.format("%.1f", highestPrecip) + " and occurred in the month of " + highestMonth);
    }

    public static void findHighestSpeed(ArrayList<ClimateRecord> records) { // Searches for day with the highest max gust speed and displays the speed and day
        int highestSpeed = records.get(0).getMaxGust();
        String date = records.get(0).getDate();
        for (ClimateRecord record : records) {
            if (record.getMaxGust() > highestSpeed) {
                highestSpeed = record.getMaxGust();
                date = record.getDate();
            }
        }
        String[] line = date.split(" ");
        date = line[0];
        System.out.println("The highest max gust speed was " + highestSpeed + " and occurred on " + date);
    }

    public static void findHighestFluc(ArrayList<ClimateRecord> records) { // Searches for day with the highest temperature fluctuation (max temp - min temp) and displays fluctuation and day
        float newFluc = records.get(0).getMaxTemp() - records.get(0).getMinTemp();
        float highestFluc = newFluc;
        String date = records.get(0).getDate();
        for (ClimateRecord record : records) {
            newFluc = record.getMaxTemp() - record.getMinTemp();
            if (newFluc > highestFluc) {
                highestFluc = newFluc;
                date = record.getDate();
            }
        }
        String[] line = date.split(" ");
        date = line[0];
        System.out.println("The largest temperature fluctuation was " + highestFluc +  " and occurred on " + date);
    }

    public static void printAverageMonthPrecip(ArrayList<ClimateRecord> records) { // Function to display the average precipitation of each month
        System.out.println("Date\tAvg Precipitation");
        System.out.println("-----------------");
        float precipitation = 0;
        int count = 0;
        String[] line = records.get(0).getDate().split("-");
        String month = line[0] + "-" + line[1];
        String currentMonth = month;
        for (ClimateRecord record : records) {
            line = record.getDate().split("-");
            month = line[0] + "-" + line[1];
            if (month.compareTo(currentMonth) == 0){
                precipitation += record.getPrecip();
                count += 1;
            }
            else {
                System.out.println(currentMonth + "\t" + String.format("%.2f", precipitation/count));
                precipitation = 0;
                count = 0;
            }
            currentMonth = month; 
        }
    }

    public static void printAverageMonthSpeed(ArrayList<ClimateRecord> records) { // Function to display the average max gust speed of each month
        System.out.println("Date\tAvg Max Gust Speed");
        System.out.println("-----------------");
        float speed = 0;
        int count = 0;
        String[] line = records.get(0).getDate().split("-");
        String month = line[0] + "-" + line[1];
        String currentMonth = month;
        for (ClimateRecord record : records) {
            line = record.getDate().split("-");
            month = line[0] + "-" + line[1];
            if (month.compareTo(currentMonth) == 0){
                speed += record.getMaxGust();
                count += 1;
            }
            else {
                System.out.println(currentMonth + "\t" + String.format("%.2f", speed/count));
                speed = 0;
                count = 0;
            }
            currentMonth = month; 
        }
    }

    public static void printAverageMeanTemp(ArrayList<ClimateRecord> records) { // Function to display the average mean temperature of each month
        System.out.println("Date\tAvg Mean Temp");
        System.out.println("-----------------");
        float temp = 0;
        int count = 0;
        String[] line = records.get(0).getDate().split("-");
        String month = line[0] + "-" + line[1];
        String currentMonth = month;
        for (ClimateRecord record : records) {
            line = record.getDate().split("-");
            month = line[0] + "-" + line[1];
            if (month.compareTo(currentMonth) == 0){
                temp += record.getMeanTemp();
                count += 1;
            }
            else {
                System.out.println(currentMonth + "\t" + String.format("%.1f", temp/count));
                temp = 0;
                count = 0;
            }
            currentMonth = month; 
        }
    }

    public static void printMonthMinTemp(ArrayList<ClimateRecord> records) { // Function to display the minimum temperature of each month
        System.out.println("Date\tMin Temp");
        System.out.println("-----------------");
        float temp = records.get(0).getMinTemp();
        String[] line = records.get(0).getDate().split("-");
        String month = line[0] + "-" + line[1];
        String currentMonth = month;
        for (ClimateRecord record : records) {
            line = record.getDate().split("-");
            month = line[0] + "-" + line[1];
            if (month.compareTo(currentMonth) == 0){
                if (temp > record.getMinTemp()) {
                    temp = record.getMinTemp();
                }
            }
            else {
                System.out.println(currentMonth + "\t" + String.format("%.1f", temp));
                temp = record.getMinTemp();
            }
            currentMonth = month; 
        }
    }

    public static void printMonthMaxTemp(ArrayList<ClimateRecord> records) { // Function to display the minimum temperature of each month
        System.out.println("Date\tMax Temp");
        System.out.println("-----------------");
        float temp = records.get(0).getMaxTemp();
        String[] line = records.get(0).getDate().split("-");
        String month = line[0] + "-" + line[1];
        String currentMonth = month;
        for (ClimateRecord record : records) {
            line = record.getDate().split("-");
            month = line[0] + "-" + line[1];
            if (month.compareTo(currentMonth) == 0){
                if (temp < record.getMaxTemp()) {
                    temp = record.getMaxTemp();
                }
            }
            else {
                System.out.println(currentMonth + "\t" + String.format("%.1f", temp));
                temp = record.getMaxTemp();
            }
            currentMonth = month; 
        }
    }

    public static void displayDataRange(ArrayList<ClimateRecord> records, String start, String end) {
        System.out.println("Date\t\tMax Gust Speed\tPrecipitation\t\tMin Temp\tMax Temp\tMean Temp");
        System.out.println("------------------------------------------------------------------------------------------------");
        boolean begin = false;
        int i = 0;
        while ((begin == false) && i < records.size()){
            String[] line = records.get(i).getDate().split(" ");
            if (line[0].compareTo(start) >= 0) {
                begin = true;
                ClimateRecord group = records.get(i);
                System.out.println(group.getDate() + "\t\t" + group.getMaxGust() + "\t\t" + group.getPrecip() + "\t\t" + group.getMinTemp() + "\t\t" + group.getMaxTemp() + "\t\t" + group.getMeanTemp());
            }
            i += 1;
        }
        String[] line = records.get(i).getDate().split(" ");
        if (line[0].compareTo(end) >= 0) {
            begin = false;
        }
        while ((begin == true) && i < records.size()) {
            ClimateRecord group = records.get(i);
            System.out.println(group.getDate() + "\t\t" + group.getMaxGust() + "\t\t" + group.getPrecip() + "\t\t" + group.getMinTemp() + "\t\t" + group.getMaxTemp() + "\t\t" + group.getMeanTemp());
            line = records.get(i).getDate().split(" ");
            if (line[0].compareTo(end) >= 0) {
                begin = false;
            }
            i += 1;
        }
    }
}