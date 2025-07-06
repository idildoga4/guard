namespace IoTSensorAPI.Models
{
    public class SensorData
    {
        public int Id { get; set; }
        public int DeviceId { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
