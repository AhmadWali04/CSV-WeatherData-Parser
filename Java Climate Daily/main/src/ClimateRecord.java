public class ClimateRecord {
    // Initialize Fields
    String date;
    int maxGust;
    float precip;
    float minTemp;
    float maxTemp;
    float meanTemp;

    ClimateRecord(String date, int maxGust, float precip, float minTemp, float maxTemp, float meanTemp) { // Constructor
        this.date = date;
        this.maxGust = maxGust;
        this.precip = precip;
        this.minTemp = minTemp;
        this.maxTemp = maxTemp;
        this.meanTemp = meanTemp;
    }   

    public String getDate(){
        return date;
    }

    public int getMaxGust() {
        return maxGust;
    }

    public float getPrecip() {
        return precip;
    }

    public float getMinTemp() {
        return minTemp;
    }

    public float getMaxTemp() {
        return maxTemp;
    }

    public float getMeanTemp() {
        return meanTemp;
    }
}
